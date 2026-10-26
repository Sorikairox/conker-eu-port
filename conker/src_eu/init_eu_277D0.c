#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_10007BA4(OSThread **);     // __osEnqueueAndYield
OSThread *os_pop_thread(OSThread **); // __osPopThread

s32 osJamMesg(OSMesgQueue *mq, OSMesg msg, s32 flag) {
    register u32 saveMask;
    register OSThread *t;

    saveMask = __osDisableInt();
    while (MQ_IS_FULL(mq)) {
        if (flag == OS_MESG_BLOCK) {
            __osRunningThread->state = OS_STATE_WAITING;
            func_10007BA4(&mq->fullqueue);
        } else {
            __osRestoreInt(saveMask);
            return -1;
        }
    }
    mq->first = (mq->first + mq->msgCount - 1) % mq->msgCount;
    mq->msg[mq->first] = msg;
    mq->validCount++;
    if (mq->mtqueue->next != NULL) {
        t = os_pop_thread(&mq->mtqueue);
        osStartThread(t);
    }
    __osRestoreInt(saveMask);
    return 0;
}

extern OSDevMgr g_os_pi_dev_mgr; /* was D_8002AE90 */ // __osPiDevMgr

OSMesgQueue *osPiGetCmdQueue(void) {
    if (!g_os_pi_dev_mgr.active) {
        return NULL;
    }
    return g_os_pi_dev_mgr.cmdQueue;
}
