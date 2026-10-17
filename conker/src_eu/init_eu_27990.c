#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"

// EU addresses are in undefined_syms.eu.txt; this file is built -O1
extern OSPifRam __osPfsPifRam;
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 func_10025B60(s32, void *); // __osSiRawStartDma
void __osPfsRequestData(u8 cmd);
void func_1002560C(u8 *pattern, OSContStatus *data); // __osPfsGetInitData
s32 __osPfsGetStatus(OSMesgQueue *queue, int channel);
s32 __osGetId(OSPfs *pfs);
s32 osPfsChecker(OSPfs *pfs);

// osPfsInit
s32 func_10027990(OSMesgQueue *queue, OSPfs *pfs, int channel) {
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

s32 __osPfsGetStatus(OSMesgQueue *queue, int channel) {
    s32 ret = 0;
    OSMesg dummy;
    u8 pattern;
    OSContStatus data[4];

    __osPfsRequestData(CONT_CMD_REQUEST_STATUS);
    ret = func_10025B60(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    ret = func_10025B60(OS_READ, &__osPfsPifRam);
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

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_27990/func_10027B50.s")
