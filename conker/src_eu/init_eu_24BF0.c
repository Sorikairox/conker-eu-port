#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern OSDevMgr D_8002AE90; // __osPiDevMgr
OSMesgQueue *osPiGetCmdQueue(void);


void __osDequeueThread(OSThread **queue, OSThread *t) {
    register OSThread *pred;
    register OSThread *succ;

    pred = (OSThread *)queue;
    succ = pred->next;
    while (succ != NULL) {
        if (succ == t) {
            pred->next = t->next;
            return;
        }
        pred = succ;
        succ = pred->next;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_24BF0/osSetIntMask.s")

s32 osPiStartDma(OSIoMesg *mb, s32 priority, s32 direction, u32 devAddr, void *dramAddr, u32 size,
                 OSMesgQueue *mq) {
    register s32 ret;

    if (!D_8002AE90.active) {
        return -1;
    }
    if (direction == OS_READ) {
        mb->hdr.type = OS_MESG_TYPE_DMAREAD;
    } else {
        mb->hdr.type = OS_MESG_TYPE_DMAWRITE;
    }
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = devAddr;
    mb->size = size;
    mb->piHandle = NULL;
    if (priority == OS_MESG_PRI_HIGH) {
        ret = osJamMesg(osPiGetCmdQueue(), (OSMesg)mb, OS_MESG_NOBLOCK);
    } else {
        ret = osSendMesg(osPiGetCmdQueue(), (OSMesg)mb, OS_MESG_NOBLOCK);
    }
    return ret;
}
