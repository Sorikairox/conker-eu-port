#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct { OSThread *next; OSPri priority; } __OSThreadTail;
extern __OSThreadTail D_8002C140; // __osThreadTail
extern OSThread *D_8002C148;      // __osRunQueue
void func_10007BA4(OSThread **);             // __osEnqueueAndYield
void func_10007CC8(OSThread **, OSThread *); // __osEnqueueThread
OSThread *func_10007D14(OSThread **);        // __osPopThread
void func_10007D28(void);                    // __osDispatchThread
void __osDequeueThread(OSThread **, OSThread *);


#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_22D70/__osSetFpcCsr.s")

void osStartThread(OSThread *t) {
    register u32 saveMask = __osDisableInt();

    switch (t->state) {
        case OS_STATE_WAITING:
            t->state = OS_STATE_RUNNABLE;
            func_10007CC8(&D_8002C148, t);
            break;
        case OS_STATE_STOPPED:
            if (t->queue == NULL || t->queue == &D_8002C148) {
                t->state = OS_STATE_RUNNABLE;
                func_10007CC8(&D_8002C148, t);
            } else {
                t->state = OS_STATE_WAITING;
                func_10007CC8(t->queue, t);
                func_10007CC8(&D_8002C148, func_10007D14(t->queue));
            }
            break;
    }
    if (__osRunningThread == NULL) {
        func_10007D28();
    } else if (__osRunningThread->priority < D_8002C148->priority) {
        __osRunningThread->state = OS_STATE_RUNNABLE;
        func_10007BA4(&D_8002C148);
    }
    __osRestoreInt(saveMask);
}

void osSetThreadPri(OSThread *t, OSPri pri) {
    register u32 saveMask = __osDisableInt();

    if (t == NULL) {
        t = __osRunningThread;
    }
    if (t->priority != pri) {
        t->priority = pri;
        if (t != __osRunningThread && t->state != OS_STATE_STOPPED) {
            __osDequeueThread(t->queue, t);
            func_10007CC8(t->queue, t);
        }
        if (__osRunningThread->priority < D_8002C148->priority) {
            __osRunningThread->state = OS_STATE_RUNNABLE;
            func_10007BA4(&D_8002C148);
        }
    }
    __osRestoreInt(saveMask);
}

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 msgCount) {
    mq->mtqueue = (OSThread *)&D_8002C140;
    mq->fullqueue = (OSThread *)&D_8002C140;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = msgCount;
    mq->msg = msg;
}
