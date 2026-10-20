#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


s32 func_151EFC10(OSMesgQueue *queue, OSPfs *pfs, int channel) {
    s32 ret = 0;

    __osSiGetAccess();
    ret = __osPfsGetStatus(queue, channel);
    __osSiRelAccess();
    if (ret != 0) {
        return ret;
    }
    pfs->queue = queue;
    pfs->channel = channel;
    pfs->status = 0;
    ret = __osGetId(pfs);
    if (ret != 0) {
        return ret;
    }
    ret = osPfsChecker(pfs);
    pfs->status |= PFS_INITIALIZED;
    return ret;
}

extern OSPifRam D_80042D60;
s32 func_151EFCC4(OSMesgQueue *queue, int channel) {
    s32 ret = 0;
    OSMesg dummy;
    u8 pattern;
    OSContStatus data[4];

    __osPfsRequestData(CONT_CMD_REQUEST_STATUS);
    ret = func_10025B60(OS_WRITE, &D_80042D60);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    ret = func_10025B60(OS_READ, &D_80042D60);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    func_1002560C(&pattern, data);
    if (((data[channel].status & CONT_CARD_ON) != 0) && ((data[channel].status & CONT_CARD_PULL) != 0)) {
        return PFS_ERR_NEW_PACK;
    }
    if ((data[channel].errno != 0) || ((data[channel].status & CONT_CARD_ON) == 0)) {
        return PFS_ERR_NOPACK;
    }
    if ((data[channel].status & CONT_ADDR_CRC_ER) != 0) {
        return PFS_ERR_CONTRFAIL;
    }
    return ret;
}
