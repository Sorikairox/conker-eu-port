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

/* ---------------- P21: runtime flags ----------------
 * port_flag("det") reads ?det=N from the page URL, or PORT_DET=N from the node environment
 * (port/web/boot.sh passes PORT_* through). Absent = 0; present without a value = 1. */
EM_JS(int, __port_flag_js, (const char *name), {
    var n = UTF8ToString(name), v = null;
    if (typeof location !== 'undefined') { var m = new RegExp('[?&]' + n + '(=([^&]*))?(&|$)').exec(location.search); if (m) v = m[2] === undefined ? '1' : m[2]; }
    else if (typeof process !== 'undefined' && process.env) { var e = process.env['PORT_' + n.toUpperCase()]; if (e !== undefined) v = e; }
    return v === null ? 0 : (parseInt(v, 0) || (v === '' ? 1 : 0));
});
int port_flag(const char *name) { return __port_flag_js(name); }
/* P21: print the current wasm/JS call stack (function names only), skipping `skip` frames */
EM_JS(void, __port_js_stack, (int skip, int n), {
    var l = new Error().stack.split('\n').slice(1 + skip, 1 + skip + n);
    out(l.map(function (x) { x = x.trim(); var i = x.indexOf(' ('); return '    ' + (i > 0 ? x.slice(0, i) : x); }).join('\n'));
});
void port_js_stack(int skip, int n) { __port_js_stack(skip, n); }
/* ?noselftest=1: skip the P11 scheduler self-test thread (called from the vbe TU game_main.c) */
int port_selftest_on(void) { return !port_flag("noselftest"); }

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
static struct { const char *name, *what; unsigned n, first_frame, order, dl; } stub_tab[STUB_SLOTS];
static unsigned stub_last = STUB_SLOTS;  /* P23: slot of the latest stub hit */
static unsigned stub_distinct;

static int stub_count(const char *name, const char *what) {
    unsigned h = (unsigned)(uintptr_t)name * 2654435761u % STUB_SLOTS;
    while (stub_tab[h].name && stub_tab[h].name != name) h = (h + 1) % STUB_SLOTS;
    if (!stub_tab[h].name) {
        stub_tab[h].name = name; stub_tab[h].what = what;
        stub_tab[h].first_frame = port_frame_count; stub_tab[h].order = ++stub_distinct;
    }
    stub_last = h;
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
    { extern unsigned port_gu_f2l_calls; port_log("[gu] guMtxF2L calls: %u (P25 PC libgu)\n", port_gu_f2l_calls); }
    port_log("[stubs] %u distinct asm stubs hit, %d calls; ranked by calls (first-hit order, frame):\n",
             n, port_stub_hits);
    for (unsigned i = 0; i < n && (int)i < max; i++)
        port_log("  %3u. %-14s %8u  #%-3u f%-4u %s%s\n", i + 1, stub_tab[idx[i]].name, stub_tab[idx[i]].n,
                 stub_tab[idx[i]].order, stub_tab[idx[i]].first_frame, stub_tab[idx[i]].what,
                 stub_tab[idx[i]].dl ? " [DL]" : "");
    /* P23: the stubs on the frame display-list path: they were handed a pointer into the frame DL buffers
     * and returned it unchanged (pass-through), so their drawing is what is missing from the frame */
    unsigned k = 0;
    for (unsigned i = 0; i < n; i++) if (stub_tab[idx[i]].dl) k++;
    port_log("[stubs] %u on the frame DL path (returned a frame-DL pointer; their output is missing):\n", k);
    for (unsigned i = 0, j = 0; i < n; i++)
        if (stub_tab[idx[i]].dl)
            port_log("  DL %2u. %-14s %8u calls, %8u with a DL pointer  %s\n", ++j, stub_tab[idx[i]].name, stub_tab[idx[i]].n,
                     stub_tab[idx[i]].dl, stub_tab[idx[i]].what);
}

/* P23: mark the latest stub hit as a frame-DL builder (called right after its port_stub_hit) */
void port_stub_mark_dl(void) { if (stub_last < STUB_SLOTS) stub_tab[stub_last].dl++; }

/* P23: return value of an int stub with an int first argument (gen_stubs.py): a0 when it points into the
 * frame DL buffers D_800BEDE8[0..1] (each D_800BEDE8[1] - D_800BEDE8[0] bytes; the stub is a DL builder
 * whose output is simply missing), else 0 as before. */
extern unsigned D_800BEDE8[2];
static unsigned dlret_hits;
void port_stub_mark_dl(void);
int port_stub_dlret(int a0) {
    unsigned a = (unsigned)a0, b0 = D_800BEDE8[0], b1 = D_800BEDE8[1];
    if (b0 && b1 > b0 && a >= b0 && a < b1 + (b1 - b0)) { dlret_hits++; port_stub_mark_dl(); return a0; }
    return 0;
}
unsigned port_stub_dlret_hits(void) { return dlret_hits; }
/* source-detected pass-through stubs (gen_stubs.py): always a0; marked as DL builders when a0 is in range */
int port_stub_pt(int a0) { port_stub_dlret(a0); return a0; }

/* P23: ?gdltrack=N: during VI frame N, log every stub hit with the frame DL write pointer D_800BE9D0
 * (game_45B80.c GDL) and the DL buffers, to find where the frame DL leaves its buffer. */
extern unsigned D_800BE9D0;
void port_camwatch(const char *where); /* P39: pc_overrides.c, ?camwatch=N */
void (*port_stub_trace_hook)(const char *name); /* P49: ?p49walk records the stubs hit inside the walk handler */
void port_stub_hit(const char *name, const char *what) {
    port_stub_hits++;
    if (port_stub_trace_hook) port_stub_trace_hook(name);
    port_camwatch(name);
    { static int gt = -1; if (gt < 0) gt = port_flag("gdltrack");
      if (gt && port_frame_count >= (unsigned)gt && port_frame_count < (unsigned)gt + 8) {
          OSThread *t = port_current_thread();
          port_log("[gdl] %s thread=%d GDL %08X (buf %08X %08X)\n", name, t ? (int)t->id : -1, D_800BE9D0, D_800BEDE8[0], D_800BEDE8[1]);
      } }
    { /* P55: ?gdlzero=N: find where a "G_DL 0" (DE000000 00000000) enters the frame DL: at each stub hit scan the
       * commands written since the previous hit; log the first N finds with the previous / current stub and JS stack */
      static int gz = -1, found; static unsigned last; static const char *prev = "";
      if (gz < 0) gz = port_flag("gdlzero");
      if (gz) {
          unsigned cur = D_800BE9D0, a;
          if (cur < last || cur - last > 0x10000) last = cur > 0x800 ? cur - 0x800 : cur;
          for (a = (last + 7) & ~7u; a + 8 <= cur; a += 8)
              if (*(unsigned *)(uintptr_t)a == 0xDE000000u && *(unsigned *)(uintptr_t)(a + 4) == 0 && found < gz) {
                  found++;
                  port_log("[gdlzero] G_DL 0 at %08X (GDL now %08X) frame %u, between stub %s and stub %s\n", a, cur,
                           port_frame_count, prev, name);
                  port_js_stack(2, 14);
                  if (found == 1) { unsigned b; for (b = a - 0x90; b < a + 0x48 && b + 8 <= cur; b += 8)
                      port_log("[gdlzero]   %08X: %08X %08X\n", b, *(unsigned *)(uintptr_t)b, *(unsigned *)(uintptr_t)(b + 4)); }
              }
          last = cur; prev = name;
      } }
    { /* P78: ?p78null=1: at every stub hit check the null zone (wasm 0x10..0xFF); on the first dirty word log the
       * last 12 stub hits before it (the write happened after the previous one returned) and the JS stack */
      static int nz = -1, done; static const char *ring[12]; static unsigned rfr[12], rn;
      if (nz < 0) nz = port_flag("p78null");
      if (nz && !done) {
          unsigned a;
          for (a = 0x10; a < 0x100; a += 4)
              if (*(volatile unsigned *)(uintptr_t)a) break;
          if (a < 0x100) {
              done = 1;
              port_log("[p78] null zone dirty: null+0x%X = %08X, frame %u, seen at the entry of stub %s; previous hits (newest first):\n",
                       a, *(volatile unsigned *)(uintptr_t)a, port_frame_count, name);
              for (unsigned k = 1; k <= 12 && k <= rn; k++)
                  port_log("[p78]   -%u %s (frame %u)\n", k, ring[(rn - k) % 12], rfr[(rn - k) % 12]);
              port_js_stack(1, 24);
          }
          ring[rn % 12] = name; rfr[rn % 12] = port_frame_count; rn++;
      } }
    if (stub_count(name, what) && stub_logged < PORT_STUB_LOG_MAX) { /* first hit of each stub */
        stub_logged++;
        OSThread *t = port_current_thread();
        port_log("[stub %2d] %s (%s) thread=%d frame=%u\n", stub_logged, name, what, t ? (int)t->id : -1,
                 port_frame_count);
        { static int ss = -1; if (ss < 0) ss = port_flag("stubstack"); /* P21: ?stubstack=1: wasm stack of each first hit */
          if (ss) port_js_stack(3, 9); }
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

/* P25: interrupt state for the cooperative scheduler. Fibers switch only inside blocking libultra
 * calls, so nothing is ever preempted and masking cannot change scheduling; the state is still kept
 * so that the libultra contracts hold: __osDisableInt returns the previous SR.IE (1 or 0) and clears
 * it, __osRestoreInt(m) ORs it back, osSetIntMask returns the previous mask, __osGetSR/__osSetSR and
 * __osSetFpcCsr read and write their registers. */
static u32 pc_sr = 0x1 /* SR_IE */, pc_fpcsr = 0x01000800 /* FPCSR_FS | FPCSR_EV, RM = nearest */;
static OSIntMask pc_intmask = OS_IM_ALL;
u32 __osDisableInt(void) { u32 ie = pc_sr & 1; pc_sr &= ~1u; return ie; }
s32 __osRestoreInt(u32 m) { pc_sr |= m & 1; return 0; } /* game TUs define it returning s32 */
u32 __osGetSR(void) { return pc_sr; }
s32 __osSetSR(u32 v) { pc_sr = v; return 0; }
u32 __osSetFpcCsr(u32 v) { u32 o = pc_fpcsr; pc_fpcsr = v; return o; }
void __osSetCompare(u32 v) { (void)v; } /* CP0 Compare: timers come from the PC clock (osSetTimer) */
/* __osCleanupThread: the return address libultra gives a new thread. The PC fiber entry already
 * destroys a thread whose entry returns; anything that jumps here gets the same. */
void __osCleanupThread(void) { osDestroyThread(NULL); }
/* P19 debug: HEAPDBG builds walk the game heap on every osSetIntMask (the allocator brackets with it)
 * and print a stack at the first broken heap. */
#ifdef PORT_HEAPDBG
int port_heap_check(void); extern int port_heap_quiet;
#endif
OSIntMask osSetIntMask(OSIntMask m) {
    { void port_heapwatch(const char *where); port_heapwatch("osSetIntMask"); }
#ifdef PORT_HEAPDBG
    { static int done, calls; calls++; if (calls >= 108 && calls <= 111) { port_log("[heapdbg] call %d\n", calls); emscripten_log(EM_LOG_CONSOLE | EM_LOG_JS_STACK, "heapdbg"); }
      if (!done) { port_heap_quiet = 1; if (port_heap_check()) { done = 1; port_log("[heapdbg] heap broken at osSetIntMask call %d\n", calls); emscripten_log(EM_LOG_CONSOLE | EM_LOG_JS_STACK, "heapdbg"); } port_heap_quiet = 0; } }
#endif
    { OSIntMask o = pc_intmask; pc_intmask = m; return o; }
}
void __osInitialize_common(void) { port_log("[os] __osInitialize_common\n"); }

/* ---------------- caches / TLB: no-ops (code is native wasm, memory is coherent) ---------------- */

void osInvalICache(void *p, s32 n) { (void)p; (void)n; }
void osInvalDCache(void *p, s32 n) { (void)p; (void)n; }
void osWritebackDCache(void *p, s32 n) { (void)p; (void)n; }
void func_10024190(void *p, s32 n) { (void)p; (void)n; } /* P25: unnamed osWritebackDCache (init_eu_23CC0.s, cache 0x19 loop) */
void osWritebackDCacheAll(void) {}
void osMapTLB(s32 i, OSPageMask m, void *v, u32 e, u32 o, s32 a) { (void)i; (void)m; (void)v; (void)e; (void)o; (void)a; }
void osUnmapTLB(s32 i) { (void)i; }
void osUnmapTLBAll(void) {}
u32 osVirtualToPhysical(void *p) { return (u32)(uintptr_t)p; }
/* __osProbeTLB(vaddr): physical address of a TLB-mapped vaddr, or -1. The PC has no TLB: the mapped
 * 0x16000000 segment is relocated to the n64_seg16 mirror at load time, so every pointer the game
 * holds is already a final (wasm) address, as osVirtualToPhysical above assumes. */
u32 __osProbeTLB(void *p) { return (u32)(uintptr_t)p; }

/* ---------------- time: 46.875 MHz CPU counter from performance.now() ---------------- */

static double t0;
/* P27: pause (tab hidden or the page's pause button). The main loop skips frames and the clock stops,
 * so timers do not all fire at once on resume. */
int port_paused;
static double pause_at, pause_total;
static double now_ms(void) {
    double t = emscripten_get_now();
    if (!t0) t0 = t;
    if (port_paused) t = pause_at;
    return t - t0 - pause_total;
}
EMSCRIPTEN_KEEPALIVE void port_set_paused(int p) {
    double t = emscripten_get_now();
    if (p && !port_paused) pause_at = t;
    else if (!p && port_paused) pause_total += t - pause_at;
    port_paused = p != 0;
}
/* P21: ?det=1 / PORT_DET=1: deterministic clock for node-vs-browser comparisons. Time is
 * frame * 1/60 s plus 1000 ticks (~21 us) per read, so busy-waits still progress; it never depends
 * on the host's speed or on wall time. */
static int det_mode = -1;
extern unsigned port_frame_count;
static OSTime det_now(void) {
    static OSTime vt; static unsigned vf;
    if (vf != port_frame_count) { OSTime f = (OSTime)port_frame_count * (OS_CPU_COUNTER / 60); if (f > vt) vt = f; vf = port_frame_count; }
    return vt += 1000;
}
void port_spin_check(void); /* P19: busy-waits on the clock yield too (pc_sched.c) */
static OSTime raw_time(void) {
    if (det_mode < 0) det_mode = port_flag("det");
    return det_mode ? det_now() : (OSTime)(now_ms() * (OS_CPU_COUNTER / 1000.0));
}
OSTime osGetTime(void) { port_spin_check(); return raw_time(); }
u32 osGetCount(void) { return (u32)osGetTime(); }

#define MAX_TIMERS 16
static struct { OSTimer *t; OSTime due, interval; OSMesgQueue *mq; OSMesg msg; } timers[MAX_TIMERS];

int osSetTimer(OSTimer *t, OSTime countdown, OSTime interval, OSMesgQueue *mq, OSMesg msg) {
    int i;
    for (i = 0; i < MAX_TIMERS; i++)
        if (timers[i].t == t || !timers[i].t) break;
    if (i == MAX_TIMERS) { port_log("[os] out of timers\n"); return -1; }
    timers[i].t = t; timers[i].due = raw_time() + countdown; timers[i].interval = interval;
    timers[i].mq = mq; timers[i].msg = msg;
    { static int n; if ((uintptr_t)msg == 6 && n++ < 3) port_log("[os] pad timer armed: %llu ticks\n", (unsigned long long)countdown); }
    return 0;
}

int osStopTimer(OSTimer *t) {
    for (int i = 0; i < MAX_TIMERS; i++)
        if (timers[i].t == t) { timers[i].t = NULL; return 0; }
    return -1;
}

static void timers_poll(void);
void port_timers_poll(void) { timers_poll(); }
static void timers_poll(void) {
    OSTime now = raw_time();
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
s32 osPiRawReadIo(u32 devAddr, u32 *data);
u32 __port_io_read(u32 a) {
    if ((a & 0xF0000000u) == 0xB0000000u) {   /* P42: KSEG1 cart domain (IO_READ(osRomBase | dev), e.g. func_15001A08's
                                                * ROM 0xD24 check word, 0x98CCE31A): the big-endian ROM word */
        u32 v = 0;
        static int logged;
        osPiRawReadIo(a, &v);
        if (logged++ < 4) port_log("[io] cart read 0x%08X = 0x%08X\n", a, v);
        return v;
    }
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
/* PIF (P19; P27: moved to pc_pif.c with the controllers and the EEPROM): SI_PIF_ADDR_WR64B runs a
 * 64-byte command block from DRAM, RD64B copies PIF RAM back; both post the SI interrupt. */
void port_post_event(int e);
void port_pif_dma(int write, void *d);
void __port_io_write(u32 a, u32 v) {
    int i = io_slot(a, "write");
    if (i >= 0) io_val[i] = v;
    if (a == 0xA4800010 || a == 0xA4800004) {           /* SI_PIF_ADDR_WR64B / RD64B */
        u8 *d = (u8 *)(uintptr_t)__port_io_read(0xA4800000);   /* SI_DRAM_ADDR: osVirtualToPhysical = wasm ptr */
        if ((uintptr_t)d < 0x10000000u) d = (u8 *)port_n64_to_wasm(0x80000000u | (u32)(uintptr_t)d);
        port_pif_dma(a == 0xA4800010, d);
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
        static int nstk;
        port_log("[pi] DMA 0x%08X+0x%X out of ROM (rom %s)\n", dev, size, port_rom ? "loaded" : "missing");
        if (nstk++ < 4) port_js_stack(1, 10); /* P84: who asks for it */
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
    {   /* P46: log the first raw reads (func_15002FB4's 0xA5C check; func_150A16A4's kind-8 trigger reads 0xB0000454) */
        static int n;
        if (n++ < 8) port_log("[pi] raw read 0x%08X = 0x%08X\n", devAddr, v);
    }
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
    { static int lim = -1, n; static u32 lo; if (lim < 0) { lim = port_flag("dmalog"); lo = (u32)port_flag("dmamin"); } /* P21: ?dmalog=N[&dmamin=DEV] logs the first N PI DMAs from DEV up */
      if (n < lim && (dev & 0x0FFFFFFF) >= lo) { OSThread *t = port_current_thread(); n++;
        port_log("[dma] #%d t%d dev %08X dram %08X size %X mq %08X: %08X %08X\n", n, t ? (int)t->id : -1, dev, (u32)(uintptr_t)dram, size,
                 (u32)(uintptr_t)mq, ((u32 *)dram)[0], size > 4 ? ((u32 *)dram)[1] : 0); } }
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
/* P21: the scheduler self-test (port/boot/sched_test.c) counts runs of its own task by data_ptr, since
 * the game submits gfx/audio tasks of its own at the same time */
void *port_sp_watch;
unsigned port_sp_watch_runs;
void osSpTaskStartGo(OSTask *tp) {
    unsigned type = (unsigned)tp->t.type;
    port_sp_tasks_by_type[type & 7]++;
    if (port_sp_watch && (void *)tp->t.data_ptr == port_sp_watch) port_sp_watch_runs++;
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

/* ---------------- controllers: pc_pif.c (P27) ---------------- */
