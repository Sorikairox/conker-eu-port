#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// libultra siacs.c (+ sirawdma.c)
extern u32 g_os_si_access_queue_enabled; /* was D_8002C170 */ // __osSiAccessQueueEnabled
extern OSMesg g_os_si_access_buf_boot[1]; /* was D_80042E30 */ // siAccessBuf
void __osSiCreateAccessQueue(void);


void __osSiCreateAccessQueue(void) {
    g_os_si_access_queue_enabled = 1;
    osCreateMesgQueue(&g_os_si_access_queue, g_os_si_access_buf_boot, 1);
    osSendMesg(&g_os_si_access_queue, NULL, OS_MESG_NOBLOCK);
}

void __osSiGetAccess(void) {
    OSMesg dummyMesg;

    if (!g_os_si_access_queue_enabled) {
        __osSiCreateAccessQueue();
    }
    osRecvMesg(&g_os_si_access_queue, &dummyMesg, OS_MESG_BLOCK);
}

void __osSiRelAccess(void) {
    osSendMesg(&g_os_si_access_queue, NULL, OS_MESG_NOBLOCK);
}

void os_writeback_dcache(void *, s32); // osWritebackDCache

// __osSiRawStartDma
/* was func_10025B60 */
s32 os_si_raw_start_dma(s32 direction, void *dramAddr) {
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
