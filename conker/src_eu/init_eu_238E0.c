#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_10007BA4(OSThread **); // __osEnqueueAndYield
OSThread *os_pop_thread(OSThread **); // __osPopThread

s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flags) {
    register u32 saveMask;

    saveMask = __osDisableInt();
    while (MQ_IS_EMPTY(mq)) {
        if (flags == OS_MESG_NOBLOCK) {
            __osRestoreInt(saveMask);
            return -1;
        } else {
            __osRunningThread->state = OS_STATE_WAITING;
            func_10007BA4(&mq->mtqueue);
        }
    }
    if (msg != NULL) {
        *msg = mq->msg[mq->first];
    }
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    if (mq->fullqueue->next != NULL) {
        osStartThread(os_pop_thread(&mq->fullqueue));
    }
    __osRestoreInt(saveMask);
    return 0;
}
