#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_8002C170;
extern u8 *D_800E1150;

/* was func_151F0B10 */
void game_os_si_create_access_queue(void) {
    D_8002C170 = 1;
    osCreateMesgQueue(&D_80042E38, &D_800E1150, 1);
    osSendMesg(&D_80042E38, NULL, 0);
}

/* was func_151F0B60 */
void game_os_si_get_access(void) {
    OSMesg dummyMesg;

    if (!D_8002C170) {
        __osSiCreateAccessQueue();
    }
    osRecvMesg(&D_80042E38, &dummyMesg, OS_MESG_BLOCK);
}

/* was func_151F0BA4 */
void game_os_si_rel_access(void) {
    osSendMesg(&D_80042E38, NULL, OS_MESG_NOBLOCK);
}

void os_writeback_dcache(void *, s32); // osWritebackDCache

// __osSiRawStartDma
/* was func_151F0BD0 */
s32 game_os_si_raw_start_dma(s32 direction, void *dramAddr) {
    if (__osSiDeviceBusy()) {
        return -1;
    }
    if (direction == OS_WRITE) {
        os_writeback_dcache(dramAddr, 64);
    }
    IO_WRITE(SI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));
    if (direction == OS_READ) {
        IO_WRITE(SI_PIF_ADDR_RD64B_REG, 0x1FC007C0);
    } else {
        IO_WRITE(SI_PIF_ADDR_WR64B_REG, 0x1FC007C0);
    }
    if (direction == OS_READ) {
        osInvalDCache(dramAddr, 64);
    }
    return 0;
}
