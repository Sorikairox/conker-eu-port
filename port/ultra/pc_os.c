/* PC replacements for the libultra hardware layer: VI, PI (ROM), SP/DP/AI, timers, caches, TLB,
 * interrupts, controllers. Only what the skeleton needs; the real renderer/audio/input come later. */
#include <emscripten.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pc_ultra.h"
#include "../gfx/gfx.h"
#include "pc_mem.h"
#include "../audio/aud.h"
#include <PR/os_exception.h>
#include <PR/os_convert.h>
#include <PR/mbi.h>
#include <PR/os_thread.h>
#include <PR/os_message.h>
#include <PR/os_pi.h>
#include <PR/os_vi.h>
#include <PR/os_time.h>
#include <PR/os_cont.h>
#include <PR/sptask.h>
#include <PR/os_tlb.h>
#include "pc_ultra.h"

/* ---------------- logging & stubs ---------------- */

#define PORT_STUB_LOG_MAX 50
int port_stub_hits;
static int stub_logged;

void port_log(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    fflush(stdout);
}

/* logging from game TUs (vbe memory): the format string lives in game memory, so it is read through
 * the vbe byte accessor first. %s arguments that point into game memory are not converted. */
void port_glog(const char *fmt, ...) {
    char buf[512];
    unsigned i = 0;
    for (; i < sizeof buf - 1 && vbe_ld8(fmt + i); i++) buf[i] = (char)vbe_ld8(fmt + i);
    buf[i] = 0;
    va_list ap;
    va_start(ap, fmt);
    vprintf(buf, ap);
    va_end(ap);
    fflush(stdout);
}

/* native copy of a game (vbe) string, for %s arguments of port_glog; 8-entry ring */
const char *port_gstr(const char *g) {
    static char ring[8][256];
    static unsigned k;
    char *b = ring[k++ & 7];
    unsigned i = 0;
    for (; i < 255 && vbe_ld8(g + i); i++) b[i] = (char)vbe_ld8(g + i);
    b[i] = 0;
    return b;
}

/* per-stub call counters (names are string literals: pointer identity), for the priority list */
#define STUB_SLOTS 4096
static struct { const char *name, *what; unsigned n, first_frame, order; } stub_tab[STUB_SLOTS];
static unsigned stub_distinct;

static int stub_count(const char *name, const char *what) {
    unsigned h = (unsigned)(uintptr_t)name * 2654435761u % STUB_SLOTS;
    while (stub_tab[h].name && stub_tab[h].name != name) h = (h + 1) % STUB_SLOTS;
    if (!stub_tab[h].name) {
        stub_tab[h].name = name; stub_tab[h].what = what;
        stub_tab[h].first_frame = port_frame_count; stub_tab[h].order = ++stub_distinct;
    }
    return ++stub_tab[h].n == 1;
}

static int stub_cmp(const void *a, const void *b) {
    const unsigned *x = a, *y = b;
    if (stub_tab[*x].n != stub_tab[*y].n) return stub_tab[*x].n < stub_tab[*y].n ? 1 : -1;
    return stub_tab[*x].order < stub_tab[*y].order ? -1 : 1;
}

/* ranked list of stub hits (calls into functions that are still asm), most frequent first */
EMSCRIPTEN_KEEPALIVE void port_dump_stubs(int max) {
    static unsigned idx[STUB_SLOTS];
    unsigned n = 0;
    for (unsigned i = 0; i < STUB_SLOTS; i++) if (stub_tab[i].name) idx[n++] = i;
    qsort(idx, n, sizeof idx[0], stub_cmp);
    port_log("[stubs] %u distinct asm stubs hit, %d calls; ranked by calls (first-hit order, frame):\n",
             n, port_stub_hits);
    for (unsigned i = 0; i < n && (int)i < max; i++)
        port_log("  %3u. %-14s %8u  #%-3u f%-4u %s\n", i + 1, stub_tab[idx[i]].name, stub_tab[idx[i]].n,
                 stub_tab[idx[i]].order, stub_tab[idx[i]].first_frame, stub_tab[idx[i]].what);
}

void port_stub_hit(const char *name, const char *what) {
    port_stub_hits++;
    if (stub_count(name, what) && stub_logged < PORT_STUB_LOG_MAX) { /* first hit of each stub */
        stub_logged++;
        OSThread *t = port_current_thread();
        port_log("[stub %2d] %s (%s) thread=%d frame=%u\n", stub_logged, name, what, t ? (int)t->id : -1,
                 port_frame_count);
        if (stub_logged == PORT_STUB_LOG_MAX) port_log("[stub] further first-hits are not logged\n");
    }
}

/* ---------------- ROM ---------------- */

unsigned char *port_rom;
unsigned port_rom_size;

EMSCRIPTEN_KEEPALIVE void port_set_rom(unsigned char *p, unsigned size) {
    port_rom = p;
    port_rom_size = size;
    port_log("[rom] %u bytes at %p, header \"%.20s\"\n", size, (void *)p, (const char *)p + 0x20);
}

/* ---------------- interrupts / CPU ---------------- */

u32 __osDisableInt(void) { return 1; }
s32 __osRestoreInt(u32 m) { (void)m; return 0; } /* game TUs define it returning s32 */
u32 __osGetSR(void) { return 0; }
s32 __osSetSR(u32 v) { (void)v; return 0; }
u32 __osSetFpcCsr(u32 v) { (void)v; return 0; }
/* P19 debug: HEAPDBG builds walk the game heap on every osSetIntMask (the allocator brackets with it)
 * and print a stack at the first broken heap. */
#ifdef PORT_HEAPDBG
int port_heap_check(void); extern int port_heap_quiet;
#endif
OSIntMask osSetIntMask(OSIntMask m) {
    (void)m;
#ifdef PORT_HEAPDBG
    { static int done, calls; calls++; if (calls >= 108 && calls <= 111) { port_log("[heapdbg] call %d\n", calls); emscripten_log(EM_LOG_CONSOLE | EM_LOG_JS_STACK, "heapdbg"); }
      if (!done) { port_heap_quiet = 1; if (port_heap_check()) { done = 1; port_log("[heapdbg] heap broken at osSetIntMask call %d\n", calls); emscripten_log(EM_LOG_CONSOLE | EM_LOG_JS_STACK, "heapdbg"); } port_heap_quiet = 0; } }
#endif
    return OS_IM_ALL;
}
void __osInitialize_common(void) { port_log("[os] __osInitialize_common\n"); }

/* ---------------- caches / TLB: no-ops (code is native wasm, memory is coherent) ---------------- */

void osInvalICache(void *p, s32 n) { (void)p; (void)n; }
void osInvalDCache(void *p, s32 n) { (void)p; (void)n; }
void osWritebackDCache(void *p, s32 n) { (void)p; (void)n; }
void osWritebackDCacheAll(void) {}
void osMapTLB(s32 i, OSPageMask m, void *v, u32 e, u32 o, s32 a) { (void)i; (void)m; (void)v; (void)e; (void)o; (void)a; }
void osUnmapTLB(s32 i) { (void)i; }
void osUnmapTLBAll(void) {}
u32 osVirtualToPhysical(void *p) { return (u32)(uintptr_t)p; }

/* ---------------- time: 46.875 MHz CPU counter from performance.now() ---------------- */

static double t0;
static double now_ms(void) {
    double t = emscripten_get_now();
    if (!t0) t0 = t;
    return t - t0;
}
OSTime osGetTime(void) { return (OSTime)(now_ms() * (OS_CPU_COUNTER / 1000.0)); }
u32 osGetCount(void) { return (u32)osGetTime(); }

#define MAX_TIMERS 16
static struct { OSTimer *t; OSTime due, interval; OSMesgQueue *mq; OSMesg msg; } timers[MAX_TIMERS];

int osSetTimer(OSTimer *t, OSTime countdown, OSTime interval, OSMesgQueue *mq, OSMesg msg) {
    int i;
    for (i = 0; i < MAX_TIMERS; i++)
        if (timers[i].t == t || !timers[i].t) break;
    if (i == MAX_TIMERS) { port_log("[os] out of timers\n"); return -1; }
    timers[i].t = t; timers[i].due = osGetTime() + countdown; timers[i].interval = interval;
    timers[i].mq = mq; timers[i].msg = msg;
    { static int n; if ((uintptr_t)msg == 6 && n++ < 3) port_log("[os] pad timer armed: %llu ticks\n", (unsigned long long)countdown); }
    return 0;
}

int osStopTimer(OSTimer *t) {
    for (int i = 0; i < MAX_TIMERS; i++)
        if (timers[i].t == t) { timers[i].t = NULL; return 0; }
    return -1;
}

static void timers_poll(void) {
    OSTime now = osGetTime();
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (!timers[i].t || now < timers[i].due) continue;
        if (timers[i].mq) osSendMesg(timers[i].mq, timers[i].msg, OS_MESG_NOBLOCK);
        if (timers[i].interval) timers[i].due += timers[i].interval;
        else timers[i].t = NULL;
    }
}

/* ---------------- VI ---------------- */

static OSMesgQueue *vi_mq;
static OSMesg vi_msg;
static u32 vi_count = 1, vi_tick;
static void *vi_cur_fb, *vi_next_fb;

void osCreateViManager(OSPri pri) { (void)pri; }
void osViSetMode(OSViMode *m) { (void)m; }
void osViBlack(u8 b) { (void)b; }
void osViSetSpecialFeatures(u32 f) { (void)f; }
void osViSetEvent(OSMesgQueue *mq, OSMesg msg, u32 retrace) {
    vi_mq = mq; vi_msg = msg; vi_count = retrace ? retrace : 1;
}
void osViSwapBuffer(void *fb) { vi_next_fb = fb; }
void *osViGetCurrentFramebuffer(void) { return vi_cur_fb; }
void *osViGetNextFramebuffer(void) { return vi_next_fb; }

/* one browser frame = one retrace */
void port_vi_retrace(void) {
    timers_poll();
    vi_cur_fb = vi_next_fb;
    if (vi_mq && ++vi_tick >= vi_count) {
        vi_tick = 0;
        osSendMesg(vi_mq, vi_msg, OS_MESG_NOBLOCK);
    }
    port_post_event(OS_EVENT_VI);
}

/* ---------------- RCP registers (P19) ----------------
 * port/tools/vbe.py rcp_io rewrites constant IO_READ / IO_WRITE in game C (0xA4xxxxxx, KSEG1) to these.
 * Modelled: AI_LEN (queued bytes of the audio ring), AI/PI/SI/SP/DP status = idle. Everything else reads
 * back the last value written (0 at start); the first use of each address is logged. */
#define IO_SLOTS 64
static u32 io_addr[IO_SLOTS], io_val[IO_SLOTS];
static int io_n;
static int io_slot(u32 a, const char *what) {
    for (int i = 0; i < io_n; i++) if (io_addr[i] == a) return i;
    if (io_n == IO_SLOTS) return -1;
    port_log("[io] first %s of RCP register 0x%08X\n", what, a);
    io_addr[io_n] = a; io_val[io_n] = 0;
    return io_n++;
}
u32 __port_io_read(u32 a) {
    int i = io_slot(a, "read");
    switch (a) {
    case 0xA4500004: return aud_out_queued() * 4;   /* AI_LEN_REG: bytes left in the current DMA */
    case 0xA450000C: return 0;                      /* AI_STATUS_REG: not full, not busy */
    case 0xA4600010: return 0;                      /* PI_STATUS_REG: idle */
    case 0xA4800018: return 0;                      /* SI_STATUS_REG: idle */
    case 0xA4040010: return 1;                      /* SP_STATUS_REG: halted */
    case 0xA410000C: return 0;                      /* DPC_STATUS_REG */
    }
    return i < 0 ? 0 : io_val[i];
}
/* PIF (P19): the game's own libultra SI code (EEPROM probe/read/write in game_eu_20B220.c etc.,
 * __osSiRawStartDma in init_eu_25AA0.c / game_eu_21E320.c) writes SI_DRAM_ADDR, then
 * SI_PIF_ADDR_WR64B (DRAM -> PIF RAM, the PIF runs the command block) or SI_PIF_ADDR_RD64B
 * (PIF RAM -> DRAM), and waits for the SI interrupt (OS_EVENT_SI). Devices: pad 0 (standard
 * controller, no pak, nothing pressed), pads 1-3 absent, channel 4 = 16K EEPROM (in memory only). */
void port_post_event(int e);
static u8 pif_ram[64];
static u8 eeprom[2048];
static void pif_run(void) {
    int ch = 0, i = 0;
    static int nlog;
    while (i < 63) {
        u8 t = pif_ram[i];
        if (t == 0xFE) break;
        if (t == 0xFF || t == 0xFD) { i++; continue; }
        if (t == 0) { ch++; i++; continue; }
        if (i + 1 >= 63) break;
        int tx = t & 0x3F, rx = pif_ram[i + 1] & 0x3F;
        u8 *c = &pif_ram[i + 2], *r = &pif_ram[i + 2 + tx];
        if (i + 2 + tx + rx > 64) break;
        int ok = 1;
        if (nlog++ < 6) port_log("[pif] ch %d cmd %02X tx %d rx %d\n", ch, c[0], tx, rx);
        if (ch == 0) {                                  /* controller 1 */
            if (c[0] == 0x00 || c[0] == 0xFF) { if (rx >= 3) { r[0] = 0x05; r[1] = 0x00; r[2] = 0x02; } }
            else if (c[0] == 0x01) memset(r, 0, rx);
            else ok = 0;                                /* pak commands: no pak */
        } else if (ch == 4) {                           /* EEPROM 16K */
            if (c[0] == 0x00 || c[0] == 0xFF) { if (rx >= 3) { r[0] = 0x00; r[1] = 0xC0; r[2] = 0x00; } }
            else if (c[0] == 0x04 && tx >= 2) memcpy(r, &eeprom[(c[1] & 0xFF) * 8], rx < 8 ? rx : 8);
            else if (c[0] == 0x05 && tx >= 10) { memcpy(&eeprom[(c[1] & 0xFF) * 8], &c[2], 8); if (rx) r[0] = 0; }
            else ok = 0;
        } else ok = 0;
        if (!ok) pif_ram[i + 1] |= 0x80;                /* no response */
        i += 2 + tx + rx;
        ch++;
    }
    pif_ram[63] = 0;
}
void __port_io_write(u32 a, u32 v) {
    int i = io_slot(a, "write");
    if (i >= 0) io_val[i] = v;
    if (a == 0xA4800010 || a == 0xA4800004) {           /* SI_PIF_ADDR_WR64B / RD64B */
        u8 *d = (u8 *)(uintptr_t)__port_io_read(0xA4800000);   /* SI_DRAM_ADDR: osVirtualToPhysical = wasm ptr */
        if ((uintptr_t)d < 0x10000000u) d = (u8 *)port_n64_to_wasm(0x80000000u | (u32)(uintptr_t)d);
        if (a == 0xA4800010) { for (int k = 0; k < 64; k++) pif_ram[k] = (u8)vbe_ld8(d + k); pif_run(); }
        else for (int k = 0; k < 64; k++) vbe_st8(d + k, pif_ram[k]);
        port_post_event(OS_EVENT_SI);
    }
}

/* ---------------- PI: DMA from the user's ROM, completes immediately ---------------- */

static OSMesgQueue *pi_cmd_mq;
void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 n) {
    (void)pri; (void)cmdBuf; (void)n; pi_cmd_mq = cmdQ;
}
u32 osPiGetStatus(void) { return 0; }

static void rom_copy(u32 dev, void *dst, u32 size) {
    u32 off = dev & 0x0FFFFFFF; /* PI cart domain 0x10000000 */
    if (!port_rom || off + size > port_rom_size) {
        port_log("[pi] DMA 0x%08X+0x%X out of ROM (rom %s)\n", dev, size, port_rom ? "loaded" : "missing");
        memset(dst, 0, size);
        return;
    }
    port_rom_read(dst, off, size); /* big-endian ROM bytes -> vbe game memory */
}

/* P19: libultra osPiRawReadIo (game TU init_eu_26AD0.c; weak via port_prefix.h) polls PI_STATUS and reads
 * IO_READ(osRomBase | devAddr), i.e. a KSEG1 hardware address. Used by the anti-piracy check in
 * func_15002FB4 (ROM word 0xA5C). PC: the big-endian ROM word at the cart-domain offset. */
s32 osPiRawReadIo(u32 devAddr, u32 *data) {
    u32 off = devAddr & 0x0FFFFFFC;
    u32 v = 0;
    if (port_rom && off + 4 <= port_rom_size)
        v = (u32)port_rom[off] << 24 | (u32)port_rom[off + 1] << 16 | (u32)port_rom[off + 2] << 8 | port_rom[off + 3];
    else
        port_log("[pi] raw read 0x%08X out of ROM\n", devAddr);
    *data = v; /* aligned word in game memory: native store = BE value (word-swapped storage) */
    return 0;
}

s32 osPiRawStartDma(s32 dir, u32 dev, void *dram, u32 size) {
    if (dir == OS_READ) rom_copy(dev, dram, size);
    return 0;
}

s32 osPiStartDma(OSIoMesg *mb, s32 pri, s32 dir, u32 dev, void *dram, u32 size, OSMesgQueue *mq) {
    (void)pri;
    if (dir == OS_READ) rom_copy(dev, dram, size);
    if (mb) { mb->hdr.retQueue = mq; mb->dramAddr = dram; mb->devAddr = dev; mb->size = size; }
    if (mq) osSendMesg(mq, (OSMesg)mb, OS_MESG_NOBLOCK);
    return 0;
}

s32 osEPiStartDma(OSPiHandle *h, OSIoMesg *mb, s32 dir) {
    (void)h;
    return osPiStartDma(mb, mb->hdr.pri, dir, mb->devAddr, mb->dramAddr, mb->size, mb->hdr.retQueue);
}

/* ---------------- RSP / RDP / audio: tasks complete at once (Fast3D / audio HLE go here) ---------------- */

static int sp_tasks;
/* RSP tasks. The OSTask lives in game memory: its fields are 32-bit (plain loads). M_GFXTASK goes
 * to the F3DEX2 interpreter (port/gfx), M_AUDTASK to the audio HLE (not written yet). */
unsigned port_sp_tasks_by_type[8];
extern unsigned port_gfx_frame_tasks;
void osSpTaskLoad(OSTask *tp) { (void)tp; }
void osSpTaskStartGo(OSTask *tp) {
    unsigned type = (unsigned)tp->t.type;
    port_sp_tasks_by_type[type & 7]++;
    if (sp_tasks++ < 8)
        port_log("[sp] task %u: type %u%s ucode %08X data_ptr %08X size %u\n", sp_tasks, type,
                 type == M_GFXTASK ? " (gfx)" : type == M_AUDTASK ? " (audio)" : "",
                 (unsigned)(uintptr_t)tp->t.ucode, (unsigned)(uintptr_t)tp->t.data_ptr, (unsigned)tp->t.data_size);
    if (type == M_GFXTASK) { gfx_run_task(tp); port_gfx_frame_tasks++; }
    if (type == M_AUDTASK) aud_run_alist((const uint32_t *)tp->t.data_ptr, (uint32_t)tp->t.data_size); /* port/audio */
    port_post_event(OS_EVENT_SP);
    if (type == M_GFXTASK) port_post_event(OS_EVENT_DP);
}
void port_sp_report(void) {
    port_log("[sp] tasks submitted: %u (gfx %u, audio %u, other %u); gfx: %u DLs, %u commands, %u triangles, %u bad/unset-segment addresses\n", sp_tasks,
             port_sp_tasks_by_type[M_GFXTASK], port_sp_tasks_by_type[M_AUDTASK],
             sp_tasks - port_sp_tasks_by_type[M_GFXTASK] - port_sp_tasks_by_type[M_AUDTASK],
             gfx_stats.dls, gfx_stats.cmds, gfx_stats.tris, gfx_stats.bad_addr + gfx_stats.unset_seg);
}
void osSpTaskYield(void) {}
OSYieldResult osSpTaskYielded(OSTask *tp) { (void)tp; return 0; }
void osDpSetStatus(u32 s) { (void)s; }
/* AI: the buffer (interleaved BE s16 stereo in game memory) goes to the SDL ring (port/audio/aud_out.c) */
static int ai_rate = 22020;
s32 osAiSetNextBuffer(void *p, u32 n) { aud_out_open(ai_rate); aud_out_push_game(p, n / 4); return 0; }
u32 osAiGetStatus(void) { return 0; }
u32 osAiGetLength(void) { return aud_out_queued() * 4; }
s32 osAiSetFrequency(u32 f) { ai_rate = (int)f; return (s32)f; }

/* ---------------- controllers: one pad, nothing pressed (input comes later) ---------------- */

s32 osContInit(OSMesgQueue *mq, u8 *bits, OSContStatus *st) {
    (void)mq;
    vbe_st8(bits, 1);
    for (int i = 0; i < MAXCONTROLLERS; i++) {
        /* sub-word fields of game memory: vbe accessors (port/ultra/pc_mem.h) */
        vbe_st16(&st[i].type, i == 0 ? CONT_TYPE_NORMAL : 0);
        vbe_st8(&st[i].status, 0);
        vbe_st8(&st[i].errno, i == 0 ? 0 : CONT_NO_RESPONSE_ERROR);
    }
    /* P19: the P11 SI shim (one posted message) is gone: the level loader func_15007B3C is C now
     * and starts the first read through func_1501BB20. */
    return 0;
}
s32 osContStartReadData(OSMesgQueue *mq) {
    s32 r = mq ? osSendMesg(mq, NULL, OS_MESG_NOBLOCK) : -1; /* SI transfer done at once */
    { static int n; if (n++ < 3) port_log("[os] osContStartReadData %p: send %d, queue %d/%d\n", (void *)mq, r, mq ? mq->validCount : 0, mq ? mq->msgCount : 0); }
    return 0;
}
void osContGetReadData(OSContPad *pad) {
    { static int n; if (n++ < 3) { u32 *r = (u32 *)port_n64_to_wasm(0x800B1200); u32 *q = (u32 *)(uintptr_t)*r;
        port_log("[os] osContGetReadData #%d; D_800B0DF0 (EU 800B1200) = %08X", n, *r);
        if ((uintptr_t)q >= 0x10000000u) port_log(" -> %08X %08X %08X %08X", q[0], q[1], q[2], q[3]);
        port_log("\n"); } }
    memset(pad, 0, sizeof(OSContPad) * MAXCONTROLLERS);
    for (int i = 1; i < MAXCONTROLLERS; i++) vbe_st8(&pad[i].errno, CONT_NO_RESPONSE_ERROR);
}
