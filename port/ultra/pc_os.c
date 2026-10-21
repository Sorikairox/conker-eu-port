/* PC replacements for the libultra hardware layer: VI, PI (ROM), SP/DP/AI, timers, caches, TLB,
 * interrupts, controllers. Only what the skeleton needs; the real renderer/audio/input come later. */
#include <emscripten.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "pc_ultra.h"
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

void port_stub_hit(const char *name, const char *what) {
    port_stub_hits++;
    if (stub_logged < PORT_STUB_LOG_MAX) {
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
void __osRestoreInt(u32 m) { (void)m; }
u32 __osGetSR(void) { return 0; }
void __osSetSR(u32 v) { (void)v; }
u32 __osSetFpcCsr(u32 v) { (void)v; return 0; }
OSIntMask osSetIntMask(OSIntMask m) { (void)m; return OS_IM_ALL; }
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
    memcpy(dst, port_rom + off, size);
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
void osSpTaskLoad(OSTask *tp) { (void)tp; }
void osSpTaskStartGo(OSTask *tp) {
    if (sp_tasks++ < 3) port_log("[sp] task type %u (not executed yet)\n", (unsigned)tp->t.type);
    port_post_event(OS_EVENT_SP);
    if (tp->t.type == M_GFXTASK) port_post_event(OS_EVENT_DP);
}
void osSpTaskYield(void) {}
OSYieldResult osSpTaskYielded(OSTask *tp) { (void)tp; return 0; }
void osDpSetStatus(u32 s) { (void)s; }
s32 osAiSetNextBuffer(void *p, u32 n) { (void)p; (void)n; return 0; }
u32 osAiGetStatus(void) { return 0; }
u32 osAiGetLength(void) { return 0; }
s32 osAiSetFrequency(u32 f) { return (s32)f; }

/* ---------------- controllers: one pad, nothing pressed (input comes later) ---------------- */

s32 osContInit(OSMesgQueue *mq, u8 *bits, OSContStatus *st) {
    (void)mq;
    *bits = 1;
    for (int i = 0; i < MAXCONTROLLERS; i++) {
        st[i].type = i == 0 ? CONT_TYPE_NORMAL : 0;
        st[i].status = 0;
        st[i].errno = i == 0 ? 0 : CONT_NO_RESPONSE_ERROR;
    }
    return 0;
}
s32 osContStartReadData(OSMesgQueue *mq) {
    if (mq) osSendMesg(mq, NULL, OS_MESG_NOBLOCK); /* SI transfer done at once */
    return 0;
}
void osContGetReadData(OSContPad *pad) {
    memset(pad, 0, sizeof(OSContPad) * MAXCONTROLLERS);
    for (int i = 1; i < MAXCONTROLLERS; i++) pad[i].errno = CONT_NO_RESPONSE_ERROR;
}
