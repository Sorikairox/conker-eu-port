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

extern OSPiHandle *D_8002AEAC; /* __osPiTable */
OSPiHandle D_80043E50;  /* LeoDiskHandle (.bss; tentative definition, COMMON resolved by undefined_syms: gives the shared lui) */
extern OSPiHandle *D_80043EC4; /* __osDiskHandle (.bss) */

// osLeoDiskInit (Rare libultrare, GoldenEye src/libultrare/io/leodiskinit.c)
OSPiHandle *func_10027B50(void) {
    s32 sp1c;

    D_80043E50.type = 2;
    D_80043E50.baseAddress = (0xa0000000 | 0x05000000);
    D_80043E50.latency = 3;
    D_80043E50.pulse = 6;
    D_80043E50.pageSize = 6;
    D_80043E50.relDuration = 2;
    IO_WRITE(PI_BSD_DOM2_LAT_REG, D_80043E50.latency);
    IO_WRITE(PI_BSD_DOM2_PWD_REG, D_80043E50.pulse);
    IO_WRITE(PI_BSD_DOM2_PGS_REG, D_80043E50.pageSize);
    IO_WRITE(PI_BSD_DOM2_RLS_REG, D_80043E50.relDuration);
    bzero(&D_80043E50.transferInfo, sizeof(__OSTranxInfo));
    sp1c = __osDisableInt();
    D_80043E50.next = D_8002AEAC;
    D_8002AEAC = &D_80043E50;
    D_80043EC4 = &D_80043E50;
    __osRestoreInt(sp1c);
    return &D_80043E50;
}
