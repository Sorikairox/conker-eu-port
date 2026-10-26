#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_10007BA4(OSThread **); // __osEnqueueAndYield
OSThread *os_pop_thread(OSThread **); // __osPopThread

s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flags) {
    register u32 saveMask;
    register s32 last;

    saveMask = __osDisableInt();
    while (MQ_IS_FULL(mq)) {
        if (flags == OS_MESG_BLOCK) {
            __osRunningThread->state = OS_STATE_WAITING;
            func_10007BA4(&mq->fullqueue);
        } else {
            __osRestoreInt(saveMask);
            return -1;
        }
    }
    last = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[last] = msg;
    mq->validCount++;
    if (mq->mtqueue->next != NULL) {
        osStartThread(os_pop_thread(&mq->mtqueue));
    }
    __osRestoreInt(saveMask);
    return 0;
}
