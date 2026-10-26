#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


/* was func_151EFC10 */
s32 game_os_pfs_init_pak(OSMesgQueue *queue, OSPfs *pfs, int channel) {
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

extern OSPifRam g_os_pfs_pif_ram; /* was D_80042D60 */
/* was func_151EFCC4 */
s32 game_os_pfs_get_status(OSMesgQueue *queue, int channel) {
    s32 ret = 0;
    OSMesg dummy;
    u8 pattern;
    OSContStatus data[4];

    __osPfsRequestData(CONT_CMD_REQUEST_STATUS);
    ret = os_si_raw_start_dma(OS_WRITE, &g_os_pfs_pif_ram);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    ret = os_si_raw_start_dma(OS_READ, &g_os_pfs_pif_ram);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    game_os_pfs_get_init_data(&pattern, data);
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
