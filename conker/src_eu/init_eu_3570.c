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

extern OSDevMgr_s86 D_8002AEB0;  /* __osViDevMgr */
extern OSThread D_80036F00;      /* viThread */
extern char D_80037130[];        /* viThreadStack */
extern OSMesgQueue D_80038130;   /* viEventQueue (= viThreadStack end) */
extern OSMesg D_80038148[5];     /* viEventBuf */
extern OSIoMesg D_80038160;      /* viRetraceMsg */
extern OSIoMesg D_80038178;      /* viCounterMsg */
extern u16 D_80038190;           /* viMgrMain: static retrace */
extern u64 D_80042D40;           /* __osCurrentTime */
extern u32 D_80042D48;           /* __osBaseCounter */
extern u32 D_80042D4C;           /* __osViIntrCount */
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

    if (D_8002AEB0.active) {
        return;
    }
    __osTimerServicesInit();
    osCreateMesgQueue(&D_80038130, D_80038148, 5);
    D_80038160.hdr.type = OS_MESG_TYPE_VRETRACE;
    D_80038160.hdr.pri = OS_MESG_PRI_NORMAL;
    D_80038160.hdr.retQueue = NULL;
    D_80038178.hdr.type = OS_MESG_TYPE_COUNTER;
    D_80038178.hdr.pri = OS_MESG_PRI_NORMAL;
    D_80038178.hdr.retQueue = NULL;
    osSetEventMesg(OS_EVENT_VI, &D_80038130, &D_80038160);
    osSetEventMesg(OS_EVENT_COUNTER, &D_80038130, &D_80038178);
    oldPri = -1;
    myPri = osGetThreadPri(NULL);
    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(NULL, pri);
    }
    savedMask = __osDisableInt();
    D_8002AEB0.active = TRUE;
    D_8002AEB0.thread = &D_80036F00;
    D_8002AEB0.cmdQueue = &D_80038130;
    D_8002AEB0.evtQueue = &D_80038130;
    D_8002AEB0.acsQueue = NULL;
    D_8002AEB0.dma = NULL;
    D_8002AEB0.edma = NULL;
    osCreateThread(&D_80036F00, 0, os_vi_manager_main, &D_8002AEB0, &D_80037130[0x1000], pri);
    os_vi_init();
    osStartThread(&D_80036F00);
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
    D_80038190 = vc->retraceCount;
    if (D_80038190 == 0) {
        D_80038190 = 1;
    }
    while (TRUE) {
        osRecvMesg(dm->evtQueue, &mesg, OS_MESG_BLOCK);
        switch (((OSIoMesg *) mesg)->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                D_80038190--;
                if (D_80038190 == 0) {
                    vc = __osGetActiveQueue();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    D_80038190 = vc->retraceCount;
                }
                D_80042D4C++;
                count = osGetCount();
                D_80042D40 += count - D_80042D48;
                D_80042D48 = count;
                break;
            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
        }
    }
}
