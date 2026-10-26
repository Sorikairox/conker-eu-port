#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    u32 active;
    OSThread *thread;
    OSMesgQueue *cmdQueue;
    OSMesgQueue *evtQueue;
    OSMesgQueue *acsQueue;
    s32 (*dma)(s32, u32, void *, u32);
    s32 (*edma)(OSPiHandle *, s32, u32, void *, u32);
} OSDevMgr_s86;

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void *framep;
    /* 0x08 */ OSViMode *modep;
    /* 0x0C */ u32 control;
    /* 0x10 */ OSMesgQueue *msgq;
    /* 0x14 */ OSMesg msg;
} OSViContext_s86;

extern OSDevMgr_s86 g_os_vi_dev_mgr;  /* __osViDevMgr; was D_8002AEB0 */
extern OSThread g_os_vi_thread;      /* viThread; was D_80036F00 */
extern char g_os_vi_thread_stack[];        /* viThreadStack; was D_80037130 */
extern OSMesgQueue g_os_vi_event_queue;   /* viEventQueue (= viThreadStack end); was D_80038130 */
extern OSMesg g_os_vi_event_buf[5];     /* viEventBuf; was D_80038148 */
extern OSIoMesg g_os_vi_retrace_msg;      /* viRetraceMsg; was D_80038160 */
extern OSIoMesg g_os_vi_counter_msg;      /* viCounterMsg; was D_80038178 */
extern u16 g_os_vi_retrace_count;           /* viMgrMain: static retrace; was D_80038190 */
extern u64 g_os_current_time;           /* __osCurrentTime; was D_80042D40 */
extern u32 g_os_base_counter;           /* __osBaseCounter; was D_80042D48 */
extern u32 g_os_vi_intr_count;           /* __osViIntrCount; was D_80042D4C */
void __osTimerServicesInit(void);
void os_vi_init(void);        /* __osViInit */
OSViContext_s86 *__osGetActiveQueue(void); /* __osViGetCurrentContext */
void __osViSwapContext(void);
void __osTimerInterrupt(void);
u32 __osDisableInt(void);
void __osRestoreInt(u32);
void os_vi_manager_main(void *arg);

/* was func_10003570 */
void os_create_vi_manager(OSPri pri) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (g_os_vi_dev_mgr.active) {
        return;
    }
    __osTimerServicesInit();
    osCreateMesgQueue(&g_os_vi_event_queue, g_os_vi_event_buf, 5);
    g_os_vi_retrace_msg.hdr.type = OS_MESG_TYPE_VRETRACE;
    g_os_vi_retrace_msg.hdr.pri = OS_MESG_PRI_NORMAL;
    g_os_vi_retrace_msg.hdr.retQueue = NULL;
    g_os_vi_counter_msg.hdr.type = OS_MESG_TYPE_COUNTER;
    g_os_vi_counter_msg.hdr.pri = OS_MESG_PRI_NORMAL;
    g_os_vi_counter_msg.hdr.retQueue = NULL;
    osSetEventMesg(OS_EVENT_VI, &g_os_vi_event_queue, &g_os_vi_retrace_msg);
    osSetEventMesg(OS_EVENT_COUNTER, &g_os_vi_event_queue, &g_os_vi_counter_msg);
    oldPri = -1;
    myPri = osGetThreadPri(NULL);
    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(NULL, pri);
    }
    savedMask = __osDisableInt();
    g_os_vi_dev_mgr.active = TRUE;
    g_os_vi_dev_mgr.thread = &g_os_vi_thread;
    g_os_vi_dev_mgr.cmdQueue = &g_os_vi_event_queue;
    g_os_vi_dev_mgr.evtQueue = &g_os_vi_event_queue;
    g_os_vi_dev_mgr.acsQueue = NULL;
    g_os_vi_dev_mgr.dma = NULL;
    g_os_vi_dev_mgr.edma = NULL;
    osCreateThread(&g_os_vi_thread, 0, os_vi_manager_main, &g_os_vi_dev_mgr, &g_os_vi_thread_stack[0x1000], pri);
    os_vi_init();
    osStartThread(&g_os_vi_thread);
    __osRestoreInt(savedMask);
    if (oldPri != -1) {
        osSetThreadPri(NULL, oldPri);
    }
}

/* P281: readable C for os_vi_manager_main (libultra viMgrMain, compiled C, 110 insns). Verified with difftest up to the
   N-th osRecvMesg (DIFFTEST_STOPCALL): the loop never returns. */
// vi_manager_main: the VI manager thread. Waits on the event queue: a retrace message swaps the VI context, counts
// down the retrace interval (sending the client's message when it expires and reloading it), counts the interrupt
// and advances __osCurrentTime by the counter ticks since the last retrace; a counter message runs the timers.
/* was func_100036E8 */
void os_vi_manager_main(void *arg) {
    OSDevMgr_s86 *dm = arg;
    OSViContext_s86 *vc;
    OSMesg mesg = NULL;
    u32 count;

    vc = __osGetActiveQueue();
    g_os_vi_retrace_count = vc->retraceCount;
    if (g_os_vi_retrace_count == 0) {
        g_os_vi_retrace_count = 1;
    }
    while (TRUE) {
        osRecvMesg(dm->evtQueue, &mesg, OS_MESG_BLOCK);
        switch (((OSIoMesg *) mesg)->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                g_os_vi_retrace_count--;
                if (g_os_vi_retrace_count == 0) {
                    vc = __osGetActiveQueue();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    g_os_vi_retrace_count = vc->retraceCount;
                }
                g_os_vi_intr_count++;
                count = osGetCount();
                g_os_current_time += count - g_os_base_counter;
                g_os_base_counter = count;
                break;
            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
        }
    }
}
