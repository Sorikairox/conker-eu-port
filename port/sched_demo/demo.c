/* Scheduler demo: libultra-style threads + message queues + fake VI retrace in the browser.
 *
 *   idle   (pri 1 -> 0)  starts the others, drops to idle priority and spins forever (like the game's)
 *   game   (pri 10)      blocks on the VI queue every frame, sends a job to the worker
 *   worker (pri 8)       receives jobs, posts results to a 2-entry queue (fills up -> blocks)
 *   logger (pri 12)      receives results; higher priority, so it preempts the worker on each send
 * Checks run at frame 300 and print PASS/FAIL lines. */
#include <stdio.h>
#include "../ultra/pc_ultra.h"
#include <PR/os_vi.h>

static OSThread t_idle, t_game, t_worker, t_logger;
static OSMesgQueue vi_q, job_q, res_q;
static OSMesg vi_buf[1], job_buf[8], res_buf[2];
static int jobs_sent, jobs_done, results_logged, order_errors, last_logged = -1;
static int worker_after_send_ok = 1;
static volatile int idle_spins;

#define CHECK_FRAME 300

static void logger(void *arg) {
    OSMesg m;
    (void)arg;
    for (;;) {
        osRecvMesg(&res_q, &m, OS_MESG_BLOCK);
        int v = (int)(intptr_t)m;
        if (v != last_logged + 1) order_errors++;
        last_logged = v;
        results_logged++;
        if (v % 60 == 0) printf("[logger pri12] result %d (frame %u)\n", v, port_frame_count);
    }
}

static void worker(void *arg) {
    OSMesg m;
    (void)arg;
    for (;;) {
        osRecvMesg(&job_q, &m, OS_MESG_BLOCK);
        int v = (int)(intptr_t)m;
        volatile int acc = 0;
        for (int i = 0; i < 1000; i++) acc += i * v; /* "work" */
        jobs_done++;
        osSendMesg(&res_q, (OSMesg)(intptr_t)v, OS_MESG_BLOCK);
        /* logger has higher priority: it must already have consumed this result */
        if (last_logged != v) worker_after_send_ok = 0;
    }
}

static void game(void *arg) {
    OSMesg m;
    (void)arg;
    osViSetEvent(&vi_q, (OSMesg)0x1234, 1);
    printf("[game pri10] waiting for retrace\n");
    for (;;) {
        osRecvMesg(&vi_q, &m, OS_MESG_BLOCK);
        if ((intptr_t)m != 0x1234) printf("[game] bad VI message %p\n", m);
        osSendMesg(&job_q, (OSMesg)(intptr_t)jobs_sent, OS_MESG_BLOCK);
        jobs_sent++;
        if (port_frame_count == CHECK_FRAME) {
            int ok1 = jobs_done == jobs_sent - 0 || jobs_done == jobs_sent - 1;
            int ok2 = order_errors == 0 && results_logged == jobs_done;
            int ok3 = worker_after_send_ok;
            int ok4 = idle_spins == 0;
            printf("== scheduler demo @ frame %u: jobs sent %d, done %d, logged %d\n", port_frame_count,
                   jobs_sent, jobs_done, results_logged);
            printf("%s  every VI retrace delivered one job to the worker\n", ok1 ? "PASS" : "FAIL");
            printf("%s  results arrive in order through a 2-slot queue\n", ok2 ? "PASS" : "FAIL");
            printf("%s  higher-priority logger preempts the worker on osSendMesg\n", ok3 ? "PASS" : "FAIL");
            printf("%s  idle thread (pri 0) parked, never spun\n", ok4 ? "PASS" : "FAIL");
            port_dump_threads();
        }
    }
}

static void idle(void *arg) {
    (void)arg;
    osCreateMesgQueue(&vi_q, vi_buf, 1);
    osCreateMesgQueue(&job_q, job_buf, 8);
    osCreateMesgQueue(&res_q, res_buf, 2);
    osCreateThread(&t_logger, 4, logger, NULL, NULL, 12);
    osCreateThread(&t_worker, 3, worker, NULL, NULL, 8);
    osCreateThread(&t_game, 2, game, NULL, NULL, 10);
    osStartThread(&t_logger);
    osStartThread(&t_worker);
    osStartThread(&t_game);
    printf("[idle] started 3 threads, dropping to OS_PRIORITY_IDLE\n");
    osSetThreadPri(NULL, OS_PRIORITY_IDLE);
    for (;;) idle_spins++; /* the game's idle loop: never reached */
}

static void boot(void) {
    printf("Conker port: scheduler demo (ASYNCIFY fibers)\n");
    osCreateThread(&t_idle, 1, idle, NULL, NULL, 1);
    osStartThread(&t_idle);
}

int main(void) {
    port_run(boot);
    return 0;
}
