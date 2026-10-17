#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_10007BA4(OSThread **); // __osEnqueueAndYield
void __osDequeueThread(OSThread **, OSThread *);


void osStopThread(OSThread *t) {
    register u32 saveMask = __osDisableInt();
    register u16 state;

    if (t == NULL) {
        state = OS_STATE_RUNNING;
    } else {
        state = t->state;
    }
    switch (state) {
        case OS_STATE_RUNNING:
            __osRunningThread->state = OS_STATE_STOPPED;
            func_10007BA4(NULL);
            break;
        case OS_STATE_RUNNABLE:
        case OS_STATE_WAITING:
            t->state = OS_STATE_STOPPED;
            __osDequeueThread(t->queue, t);
            break;
    }
    __osRestoreInt(saveMask);
}
