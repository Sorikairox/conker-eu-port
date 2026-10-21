/* Session P11: runtime check of the converted C scheduler thread func_100049E0 (init_49E0.c, P7,
 * "UNVERIFIED by difftest"). vbe TU (port/Makefile BOOT_SRC): game memory has N64 semantics.
 *
 * A test thread (priority 12, below the scheduler's 13) waits a few frames, then sends one gfx task
 * and one audio task to the scheduler's task queue D_8003B200 (EU 0x8003B560), the queue the game's
 * audio frame func_10009... (init_8F90.c) uses. Path in func_100049E0:
 *   retrace (msg 0) -> takes the task into D_8002AC54, arms the timeout timer D_8003A8E8 (msg 3)
 *   msg 3           -> osSpTaskLoad / osSpTaskStartGo   (PC: gfx_run_task / aud_run_alist)
 *   msg 2 (SP done) -> osSendMesg(task->msgQ, task->msg)
 * The test passes when each task's done message arrives with the right value, within a few frames,
 * and the gfx DL / audio list were really executed (counters in port/gfx and port/audio). */
#include <ultra64.h>
#include <PR/sched.h>

void port_glog(const char *fmt, ...);
#define port_log port_glog
extern unsigned port_frame_count;
extern unsigned port_sp_tasks_by_type[8];
extern OSMesgQueue D_8003B200, D_8003B1E8;  /* audio/"timeout" task queue, gfx task queue */
s32 func_10003C6C(s32 size, s32 tag, s32 align, s32 top, s32 mayFail);

static OSThread st_thread;
static u64 st_stack[0x400];
static OSMesgQueue st_q, st_rq;    /* done messages, retrace messages */
static OSMesg st_buf[4], st_rbuf[2];
static struct { void *next; OSMesgQueue *msgQ; s32 flags; } st_client; /* SchedClient (init_49E0.c) */
extern u16 D_8003B240;              /* the retrace message the scheduler sends to its clients */
void func_100051C8(void *client, OSMesgQueue *q); /* game: add a retrace client (init_50A0.c) */
static unsigned st_retraces, st_badmsg;
/* wait for the next retrace message from the C scheduler (exercises its client loop) */
static void wait_retrace(void) {
    OSMesg m = 0;
    osRecvMesg(&st_rq, &m, OS_MESG_BLOCK);
    st_retraces++;
    if ((u16 *)m != &D_8003B240 || *(u16 *)m != 1) st_badmsg++;
}
int port_sched_test_result = -1;

static int run_one(OSScTask *t, u32 type, u32 *list, u32 bytes, u32 tag) {
    OSMesg m = 0;
    unsigned f0 = port_frame_count, before = port_sp_tasks_by_type[type & 7];
    bzero(t, sizeof(*t));
    t->msgQ = &st_q;
    t->msg = (OSMesg)tag;
    t->flags = type == M_GFXTASK ? 0 : 2;     /* gfx: no OS_SC_SWAPBUFFER */
    t->framebuffer = type == M_GFXTASK ? (void *)list : 0; /* must differ from the VI framebuffers */
    t->list.t.type = type;
    t->list.t.data_ptr = (u64 *)list;
    t->list.t.data_size = bytes;
    /* gfx tasks go through D_8003B1E8 (func_10004DB0 -> func_10004F00, done after SP + DP events,
     * func_10004FE0 -> func_10005020); audio through D_8003B200 (timer msg 3, done on SP event).
     * (A gfx task sent to D_8003B200 crashes func_10005020: its DP event completes a NULL D_8002AC50.) */
    osSendMesg(type == M_GFXTASK ? &D_8003B1E8 : &D_8003B200, (OSMesg)t, OS_MESG_BLOCK);
    while (osRecvMesg(&st_q, &m, OS_MESG_NOBLOCK) == -1) {
        if (port_frame_count - f0 > 30) {
            port_log("[schedtest] type %u: no done message after 30 frames\n", type);
            return 1;
        }
        wait_retrace();
    }
    port_log("[schedtest] type %u: done message %08X after %u frame(s), tasks run %u\n", type, (u32)m,
             port_frame_count - f0, port_sp_tasks_by_type[type & 7] - before);
    return ((u32)m != tag) + (port_sp_tasks_by_type[type & 7] - before != 1);
}

/* walk the allocator's block list (func_10003C6C / func_10003BD0 layout: next, prev, info = tag<<24 |
 * size, data at +0xC) and the free list; check links, bounds and that the blocks tile the heap */
extern void *D_800380B4, *D_800380B8;
extern u32 D_80038098;
extern u8 D_800EA140;
int port_heap_quiet;
int port_heap_check(void) {
    u32 *b = (u32 *)D_800380B4, *prev = 0;
    u32 lo = (u32)&D_800EA140, hi = D_80038098, used = 0, freeb = 0, n = 0, nfree = 0, bad = 0;
    u32 tags[4] = {0};
    if ((u32)b - lo >= 64) { /* the first block is aligned (class 3: 64 bytes) */ port_log("[heap] first block %08X, want %08X\n", (u32)b, lo); bad++; }
    for (; b && n < 100000; b = (u32 *)b[0], n++) {
        u32 size = b[2] & 0xFFFFFF, tag = b[2] >> 24;
        if ((u32)b < lo || (u32)b + 0xC + size > hi + 0x14) { port_log("[heap] block %u %08X size %X out of the heap\n", n, (u32)b, size); bad++; break; }
        if ((u32 *)b[1] != prev) { port_log("[heap] block %u %08X: prev %08X, want %08X\n", n, (u32)b, b[1], (u32)prev); bad++; }
        if (b[0] && b[0] != (u32)b + 0xC + size) { port_log("[heap] block %u %08X size %X: next %08X is not adjacent\n", n, (u32)b, size, b[0]); bad++; }
        if (tag == 0) freeb += size; else used += size;
        if (tag == 0x7E) tags[0]++; else if (tag == 0xFF) tags[1]++; else if (tag) tags[2]++;
        prev = b;
    }
    for (b = (u32 *)D_800380B8; b && nfree < 100000 && !(nfree > 5000 && ++bad); b = (u32 *)b[3], nfree++)
        if (b[2] >> 24) { port_log("[heap] free-list entry %08X has tag %X\n", (u32)b, b[2] >> 24); bad++; break; }
    if (!port_heap_quiet || bad) port_log("[heap] %u blocks (%u free-list), used %u bytes, free %u bytes; tag FF %u, tag 7E %u, other tags %u; %u errors\n",
             n, nfree, used, freeb, tags[1], tags[0], tags[2], bad);
    return bad != 0;
}

/* asset-table walker: the game's func_1502B020 (C) -> func_1502AC88 (C since P7, cache insert
 * func_1502AB04 still asm) against a direct walk with PI DMA (as port/audio/aud_test.c) */
u8 *func_1502B020(s32 *arg0, s32 arg1, ...);
s32 osPiRawStartDma(s32 dir, u32 devAddr, void *dramAddr, u32 size);
int port_asset_check(void) {
    static u32 w[2];
    int bad = 0, a, b;
    static const u8 keys[][2] = {{0x17, 0}, {0x17, 1}, {0x17, 2}, {0x17, 3}, {0, 0}, {1, 0}, {2, 1}, {5, 3}};
    for (a = 0; a < 8; a++) {
        s32 ok = -1;
        u32 p = 0xAB2240, info;
        u32 got = (u32)func_1502B020(&ok, 2, keys[a][0], keys[a][1]);
        for (b = 0; b < 2; b++) { osPiRawStartDma(0, p + 8 * keys[a][b], w, 8); p += w[0]; }
        info = w[1] & 0x0FFFFFFF;
        if (got != (info ? p : 0) || (u32)ok != info) bad++;
        if (a < 4 || got != (info ? p : 0)) port_log("[assettest] (%X,%X): game %08X ok %08X, direct %08X info %08X\n", keys[a][0], keys[a][1], got, ok, p, info);
    }
    if (bad) port_log("[assettest] FAIL (%d failures)\n", bad);
    else port_log("[assettest] PASS (0 failures)\n");
    return bad;
}

static void sched_test_thread(void *arg) {
    OSScTask *t;
    u32 *dl, *al;
    int bad = 0;
    (void)arg;
    osCreateMesgQueue(&st_q, st_buf, 4);
    osCreateMesgQueue(&st_rq, st_rbuf, 2);
    /* func_100050A0 (scheduler init, inside func_15007830) clears the client list, so register only
     * once the scheduler thread has started (it sets D_8003A928 = 4); poll with a 1-frame OS timer */
    {
        static OSTimer tm;
        extern u16 D_8003A928;
        OSMesg m;
        while (D_8003A928 != 4) {
            osSetTimer(&tm, 1, 0, &st_rq, (OSMesg)0);
            osRecvMesg(&st_rq, &m, OS_MESG_BLOCK);
        }
    }
    func_100051C8(&st_client, &st_rq);
    while (port_frame_count < 4) wait_retrace();
    /* the allocator (func_10003C6C, C since P7) supplies the memory: a runtime check of it too */
    t = (OSScTask *)func_10003C6C(sizeof(OSScTask), 0x7E, 2, 0, 0);
    dl = (u32 *)func_10003C6C(16, 0x7E, 2, 0, 0);
    al = (u32 *)func_10003C6C(16, 0x7E, 2, 0, 0);
    port_log("[schedtest] task %08X dl %08X alist %08X\n", (u32)t, (u32)dl, (u32)al);
    if (!t || !dl || !al) { port_log("[schedtest] FAIL (allocation)\n"); port_sched_test_result = 1; return; }
    dl[0] = 0xDF000000; dl[1] = 0;            /* G_ENDDL */
    al[0] = 0x02000000; al[1] = 0x00000100;   /* A_CLEARBUFF dmem 0, 0x100 bytes */
    bad += run_one(t, M_GFXTASK, dl, 8, 0x600D0001);
    bad += run_one(t, M_AUDTASK, al, 8, 0x600D0002);
    bad += port_heap_check();
    bad += port_asset_check();
    port_log("[schedtest] retrace client: %u messages over %u frames, %u bad\n", st_retraces, port_frame_count, st_badmsg);
    bad += st_badmsg != 0 || st_retraces < 4;
    if (bad) port_log("[schedtest] FAIL (%d failures)\n", bad); /* no %s: vbe string literals */
    else port_log("[schedtest] PASS (0 failures)\n");
    port_sched_test_result = bad;
}

void port_sched_test_start(void) {
    osCreateThread(&st_thread, 30, sched_test_thread, 0, (u8 *)st_stack + sizeof(st_stack), 12);
    osStartThread(&st_thread);
}
