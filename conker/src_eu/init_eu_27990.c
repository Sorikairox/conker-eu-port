#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"

// EU addresses are in undefined_syms.eu.txt; this file is built -O1
extern OSPifRam __osPfsPifRam;
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 os_si_raw_start_dma(s32, void *); // __osSiRawStartDma
void __osPfsRequestData(u8 cmd);
void game_os_pfs_get_init_data(u8 *pattern, OSContStatus *data); // __osPfsGetInitData
s32 __osPfsGetStatus(OSMesgQueue *queue, int channel);
s32 __osGetId(OSPfs *pfs);
s32 osPfsChecker(OSPfs *pfs);

// osPfsInit
/* was func_10027990 */
s32 os_pfs_init(OSMesgQueue *queue, OSPfs *pfs, int channel) {
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
    ret = os_si_raw_start_dma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    ret = os_si_raw_start_dma(OS_READ, &__osPfsPifRam);
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

extern OSPiHandle *g_os_pi_table; /* __osPiTable; was D_8002AEAC */
OSPiHandle g_os_leo_disk_handle;  /* LeoDiskHandle (.bss; tentative definition, COMMON resolved by undefined_syms: gives the shared lui); was D_80043E50 */
extern OSPiHandle *g_os_disk_handle; /* __osDiskHandle (.bss); was D_80043EC4 */

// osLeoDiskInit (Rare libultrare, GoldenEye src/libultrare/io/leodiskinit.c)
/* was func_10027B50 */
OSPiHandle *os_leo_disk_init(void) {
    s32 sp1c;

    g_os_leo_disk_handle.type = 2;
    g_os_leo_disk_handle.baseAddress = (0xa0000000 | 0x05000000);
    g_os_leo_disk_handle.latency = 3;
    g_os_leo_disk_handle.pulse = 6;
    g_os_leo_disk_handle.pageSize = 6;
    g_os_leo_disk_handle.relDuration = 2;
    IO_WRITE(PI_BSD_DOM2_LAT_REG, g_os_leo_disk_handle.latency);
    IO_WRITE(PI_BSD_DOM2_PWD_REG, g_os_leo_disk_handle.pulse);
    IO_WRITE(PI_BSD_DOM2_PGS_REG, g_os_leo_disk_handle.pageSize);
    IO_WRITE(PI_BSD_DOM2_RLS_REG, g_os_leo_disk_handle.relDuration);
    bzero(&g_os_leo_disk_handle.transferInfo, sizeof(__OSTranxInfo));
    sp1c = __osDisableInt();
    g_os_leo_disk_handle.next = g_os_pi_table;
    g_os_pi_table = &g_os_leo_disk_handle;
    g_os_disk_handle = &g_os_leo_disk_handle;
    __osRestoreInt(sp1c);
    return &g_os_leo_disk_handle;
}
