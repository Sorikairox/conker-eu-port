/* Cooperative libultra threads on Emscripten fibers (ASYNCIFY), driven by emscripten_set_main_loop.
 *
 * Model (docs/port/PLAN.md 3.8, option 1):
 *  - every OSThread gets a fiber (own C stack + asyncify stack). The browser's main context is the
 *    scheduler fiber.
 *  - one browser frame = one VI retrace: post VI/timer messages, then run the highest-priority
 *    runnable thread until it blocks (osRecvMesg on an empty queue, osSendMesg on a full one,
 *    osStopThread, osYieldThread). Waking a higher-priority thread switches to it at once, as
 *    libultra's preemption would. When nothing is runnable, return to the browser.
 *  - priority 0 (OS_PRIORITY_IDLE) is never scheduled: the game's idle thread lowers itself to 0 and
 *    spins in `do {} while (1)`; here it simply parks.
 *  - no preemption: a thread that busy-waits without calling into libultra hangs the tab.
 */
#include <emscripten.h>
#include <emscripten/fiber.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "pc_ultra.h"

#define MAX_THREADS 32
#define C_STACK (256 * 1024)
#define A_STACK (128 * 1024)
#define MAX_SWITCHES_PER_FRAME 200000

enum { P_FREE, P_STOPPED, P_READY, P_RUNNING, P_BLOCKED, P_DEAD };

typedef struct {
    OSThread *t;
    emscripten_fiber_t fiber;
    void *cstack, *astack;
    void (*entry)(void *);
    void *arg;
    int state;
    OSMesgQueue *waitq;
    int waitfull;          /* 1 = blocked sending to a full queue */
    unsigned long long seq; /* FIFO among equal priorities */
    unsigned switches;
} PcThread;

static PcThread threads[MAX_THREADS];
static PcThread *cur;
static emscripten_fiber_t sched_fiber;
static char sched_astack[A_STACK];
static unsigned long long seq_counter;
static int in_main_loop;
unsigned port_frame_count;
void (*port_frame_hook)(void);

/* PC-only pacing: block the calling thread until the next frame. Used where the N64 code would block
 * on a VI message inside a function that is still an asm stub (port/boot/game_entry.c main loop). */
static OSMesgQueue frame_mq;
static OSMesg frame_buf[1];
static int frame_mq_init;
void port_wait_frame(void) {
    if (!frame_mq_init) { osCreateMesgQueue(&frame_mq, frame_buf, 1); frame_mq_init = 1; }
    osRecvMesg(&frame_mq, NULL, OS_MESG_BLOCK);
}

static const char *state_name(int s) {
    static const char *n[] = {"free", "stopped", "ready", "running", "blocked", "dead"};
    return n[s];
}

static PcThread *find(OSThread *t) {
    for (int i = 0; i < MAX_THREADS; i++)
        if (threads[i].state != P_FREE && threads[i].t == t) return &threads[i];
    return NULL;
}

OSThread *port_current_thread(void) { return cur ? cur->t : NULL; }

static void make_ready(PcThread *p) {
    p->state = P_READY;
    p->seq = ++seq_counter;
    p->waitq = NULL;
    p->t->state = OS_STATE_RUNNABLE;
}

static PcThread *pick(void) {
    PcThread *best = NULL;
    for (int i = 0; i < MAX_THREADS; i++) {
        PcThread *p = &threads[i];
        if (p->state != P_READY || p->t->priority <= OS_PRIORITY_IDLE) continue;
        if (!best || p->t->priority > best->t->priority ||
            (p->t->priority == best->t->priority && p->seq < best->seq))
            best = p;
    }
    return best;
}

/* leave the current thread's fiber; returns when the scheduler resumes it */
static void switch_out(void) {
    PcThread *me = cur;
    if (!me) return;
    emscripten_fiber_swap(&me->fiber, &sched_fiber);
}

/* libultra preemption: if a higher-priority thread is ready, let it run now */
static void maybe_preempt(void) {
    if (!cur) return;
    PcThread *n = pick();
    if (cur->t->priority <= OS_PRIORITY_IDLE || (n && n->t->priority > cur->t->priority)) {
        make_ready(cur);
        switch_out();
    }
}

static void fiber_entry(void *arg) {
    PcThread *p = arg;
    p->entry(p->arg);
    port_log("[sched] thread %d returned; destroyed\n", (int)p->t->id);
    p->state = P_DEAD;
    p->t->state = OS_STATE_STOPPED;
    switch_out(); /* never resumed */
}

void port_sched_run(void) {
    for (int n = 0; n < MAX_SWITCHES_PER_FRAME; n++) {
        PcThread *p = pick();
        if (!p) return;
        cur = p;
        p->state = P_RUNNING;
        p->t->state = OS_STATE_RUNNING;
        p->switches++;
        emscripten_fiber_swap(&sched_fiber, &p->fiber);
        cur = NULL;
        if (p->state == P_DEAD) {
            free(p->cstack); free(p->astack);
            memset(p, 0, sizeof *p);
        }
    }
    port_log("[sched] more than %d switches in one frame; yielding to the browser\n", MAX_SWITCHES_PER_FRAME);
}

/* ---------------- threads ---------------- */

void osCreateThread(OSThread *t, OSId id, void (*entry)(void *), void *arg, void *sp, OSPri pri) {
    (void)sp; /* the N64 stack is unused: each fiber has its own C stack */
    PcThread *p = find(t);
    if (p && (p->state == P_RUNNING || p == cur)) {
        port_log("[sched] osCreateThread on a running thread %d\n", (int)id);
        return;
    }
    if (!p)
        for (int i = 0; i < MAX_THREADS && !p; i++)
            if (threads[i].state == P_FREE) p = &threads[i];
    if (!p) { port_log("[sched] out of thread slots\n"); abort(); }
    if (!p->cstack) { p->cstack = malloc(C_STACK); p->astack = malloc(A_STACK); }
    p->t = t; p->entry = entry; p->arg = arg; p->state = P_STOPPED; p->waitq = NULL;
    memset(t, 0, sizeof *t);
    t->id = id; t->priority = pri; t->state = OS_STATE_STOPPED;
    emscripten_fiber_init(&p->fiber, fiber_entry, p, p->cstack, C_STACK, p->astack, A_STACK);
    port_log("[sched] create thread id=%d pri=%d entry=%p\n", (int)id, (int)pri, (void *)entry);
}

void osStartThread(OSThread *t) {
    PcThread *p = find(t);
    if (!p || p->state != P_STOPPED) return;
    make_ready(p);
    maybe_preempt();
}

void osStopThread(OSThread *t) {
    PcThread *p = t ? find(t) : cur;
    if (!p) return;
    p->state = P_STOPPED; p->waitq = NULL; p->t->state = OS_STATE_STOPPED;
    if (p == cur) switch_out();
}

void osDestroyThread(OSThread *t) {
    PcThread *p = t ? find(t) : cur;
    if (!p) return;
    p->state = P_DEAD; p->t->state = OS_STATE_STOPPED;
    if (p == cur) switch_out();
}

void osYieldThread(void) {
    if (!cur) return;
    make_ready(cur);
    switch_out();
}

void osSetThreadPri(OSThread *t, OSPri pri) {
    PcThread *p = t ? find(t) : cur;
    if (!p) return;
    p->t->priority = pri;
    if (p == cur) maybe_preempt();
    else if (cur && p->state == P_READY && pri > cur->t->priority) maybe_preempt();
}

OSPri osGetThreadPri(OSThread *t) {
    PcThread *p = t ? find(t) : cur;
    return p ? p->t->priority : 0;
}

OSId osGetThreadId(OSThread *t) {
    PcThread *p = t ? find(t) : cur;
    return p ? p->t->id : 0;
}

/* ---------------- message queues ---------------- */

static OSThread queue_sentinel; /* mtqueue/fullqueue point here so game code never sees NULL */

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count) {
    mq->mtqueue = &queue_sentinel; mq->fullqueue = &queue_sentinel;
    mq->validCount = 0; mq->first = 0; mq->msgCount = count; mq->msg = msg;
}

/* wake the highest-priority thread blocked on mq in the given direction */
static void wake(OSMesgQueue *mq, int full) {
    PcThread *best = NULL;
    for (int i = 0; i < MAX_THREADS; i++) {
        PcThread *p = &threads[i];
        if (p->state == P_BLOCKED && p->waitq == mq && p->waitfull == full &&
            (!best || p->t->priority > best->t->priority || (p->t->priority == best->t->priority && p->seq < best->seq)))
            best = p;
    }
    if (best) make_ready(best);
}

static int block_on(OSMesgQueue *mq, int full, const char *what) {
    if (!cur) {
        port_log("[sched] %s would block outside a thread (queue %p); returning -1\n", what, (void *)mq);
        return -1;
    }
    cur->state = P_BLOCKED; cur->waitq = mq; cur->waitfull = full; cur->seq = ++seq_counter;
    cur->t->state = OS_STATE_WAITING;
    switch_out();
    return 0;
}

/* P19: real-time freeze fix. Timers fire only at retrace (frame() -> port_vi_retrace), so a game
 * thread that polls a queue with OS_MESG_NOBLOCK (or busy-waits on osGetTime/osGetCount) never left
 * its fiber: the browser main loop callback never returned and the page froze in real time. After
 * SPIN_LIMIT consecutive empty polls the thread delivers due timers and yields; port_sched_run's
 * per-frame switch cap then returns to the browser. */
#define SPIN_LIMIT 4096
static unsigned spin_count;
void port_timers_poll(void);
void port_spin_check(void) {
    if (!cur || ++spin_count < SPIN_LIMIT) return;
    spin_count = 0;
    port_timers_poll();
    make_ready(cur);
    switch_out();
}
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag) {
    while (mq->validCount == 0) {
        if (flag == OS_MESG_NOBLOCK) { port_spin_check(); return -1; }
        if (block_on(mq, 0, "osRecvMesg") < 0) return -1;
    }
    spin_count = 0;
    if (msg) *msg = mq->msg[mq->first];
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    wake(mq, 1);
    maybe_preempt();
    return 0;
}

s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag) {
    while (mq->validCount >= mq->msgCount) {
        if (flag == OS_MESG_NOBLOCK || block_on(mq, 1, "osSendMesg") < 0) return -1;
    }
    mq->msg[(mq->first + mq->validCount) % mq->msgCount] = msg;
    mq->validCount++;
    wake(mq, 0);
    maybe_preempt();
    return 0;
}

s32 osJamMesg(OSMesgQueue *mq, OSMesg msg, s32 flag) {
    while (mq->validCount >= mq->msgCount) {
        if (flag == OS_MESG_NOBLOCK || block_on(mq, 1, "osJamMesg") < 0) return -1;
    }
    mq->first = (mq->first + mq->msgCount - 1) % mq->msgCount;
    mq->msg[mq->first] = msg;
    mq->validCount++;
    wake(mq, 0);
    maybe_preempt();
    return 0;
}

/* ---------------- events ---------------- */

static struct { OSMesgQueue *mq; OSMesg msg; } events[OS_NUM_EVENTS];

void osSetEventMesg(OSEvent e, OSMesgQueue *mq, OSMesg msg) {
    if (e < OS_NUM_EVENTS) { events[e].mq = mq; events[e].msg = msg; }
}

void port_post_event(int e) {
    if (e < OS_NUM_EVENTS && events[e].mq) osSendMesg(events[e].mq, events[e].msg, OS_MESG_NOBLOCK);
}

/* ---------------- main loop ---------------- */

static void frame(void) {
    port_frame_count++;
    if (port_frame_hook) port_frame_hook();
    port_vi_retrace();
    if (frame_mq_init) osSendMesg(&frame_mq, NULL, OS_MESG_NOBLOCK);
    port_sched_run();
    port_video_frame();
}

void port_dump_stubs(int max);
EMSCRIPTEN_KEEPALIVE void port_dump_threads(void) {
    port_dump_stubs(60);
    { void port_mem_null_report(void); port_mem_null_report(); }
    { void port_sp_report(void); port_sp_report(); }
    { void port_icall_report(void); port_icall_report(); }
    for (int i = 0; i < MAX_THREADS; i++) {
        PcThread *p = &threads[i];
        if (p->state == P_FREE) continue;
        extern unsigned char n64_rdram[];
        uintptr_t q = (uintptr_t)p->waitq, r = (uintptr_t)n64_rdram;
        port_log("[sched] thread id=%d pri=%d %s%s switches=%u%s", (int)p->t->id, (int)p->t->priority,
                 state_name(p->state), p->waitq ? (p->waitfull ? " (send)" : " (recv)") : "", p->switches, q ? "" : "\n");
        if (q) port_log(" queue %08X (N64 %08X)\n", (unsigned)q, q >= r && q < r + 0x800000 ? (unsigned)(q - r + 0x80000000u) : 0u);
    }
}

void port_run(port_boot_fn boot) {
    emscripten_fiber_init_from_current_context(&sched_fiber, sched_astack, sizeof sched_astack);
    port_video_init();
    boot();
    in_main_loop = 1;
    emscripten_set_main_loop(frame, 0, 0);
    /* ?timer=1: drive frames from setTimeout (headless Chrome's virtual time throttles rAF) */
    if (EM_ASM_INT({ return typeof location !== 'undefined' && /[?&]timer=1/.test(location.search); }))
        emscripten_set_main_loop_timing(EM_TIMING_SETTIMEOUT, 16);
    /* main() returns; the runtime stays alive (EXIT_RUNTIME=0) and the main loop drives everything */
}
