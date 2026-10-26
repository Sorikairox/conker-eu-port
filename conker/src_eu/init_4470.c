#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_10004470 */
void pi_init_dma_queues(void) {
    int i;
    osCreatePiManager(150, &g_pi_mgr_queue, &g_pi_mgr_msgs, 0xC8);

    for (i = 0; i < 3; i++)
    {
        osCreateMesgQueue(&gMessageQueue[i], &gMessages[i], 1);
    }

    osCreateMesgQueue(&gMessageQueue0, &gMessage0, 300);
    g_pi_io_msg_index = 0;
    g_pi_io_pending = 0;
}

/* was func_10004514 */
s32 rom_dma_read(s32 devAddr, void *dramAddr, u32 size, s32 arg3) {
    OSMesgQueue *msgQueue;
    OSIoMesg tmpIoMsg;
    OSIoMesg *ioMsg;
    s32 sp3c;

    sp3c = __osRunningThread->id - 3;
    if ((size < 0xC8U) && (sp3c == 0)) {
        rom_read_direct(devAddr, dramAddr, size);
        return;
    }
    if ((sp3c >= 4) || ( sp3c < 0)) {
        sp3c = 0;
    }
    if (arg3 == 0) {
        if (g_pi_io_pending != 300) { // messages waiting?
            ioMsg = &g_pi_io_msgs[g_pi_io_msg_index];
            msgQueue = &gMessageQueue0;
            if (g_pi_io_msg_index == 299) { // number of message queues used?
                g_pi_io_msg_index = 0;
            } else {
                g_pi_io_msg_index += 1U;
            }
            g_pi_io_pending += 1U;
        } else {
            return;
        }
    } else {
        ioMsg = &tmpIoMsg;
        msgQueue = &gMessageQueue[sp3c];
    }
    osInvalDCache(dramAddr, size);
    osPiStartDma(ioMsg, 0, 0, devAddr, dramAddr, size, msgQueue);

    if (arg3 != 0) {
        osRecvMesg(msgQueue, 0, OS_MESG_BLOCK);
    }
}

/* was func_10004674 */
void rom_dma_wait_queued(void) {
    int i;
    for (i = 0; i < g_pi_io_pending; i++)
    {
        osRecvMesg(&gMessageQueue0, 0, OS_MESG_BLOCK);
    }

    g_pi_io_pending = 0;
}

/* was func_100046E4 */
void rom_dma_read_chunked(u32 devAddr, u8 *dramAddr, u32 size) {
    OSIoMesg ioMsg;
    OSMesg msg;
    u32 sent;
    u32 chunk;
    s32 idx;

    idx = __osRunningThread->id - 3;
    sent = 0;
    if (idx >= 4 || idx < 0) {
        idx = 0;
    }
    osInvalDCache(dramAddr, size);
    if (size != 0) {
        do {
            if (size - sent < 0x14000) {
                chunk = size - sent;
            } else {
                chunk = 0x14000;
            }
            osPiStartDma(&ioMsg, 0, 0, devAddr, dramAddr, chunk, &gMessageQueue[idx]);
            osRecvMesg(&gMessageQueue[idx], &msg, 1);
            sent += chunk;
            devAddr += chunk;
            dramAddr += chunk;
        } while (sent < size);
    }
}
/* P62: hand-written from the asm. UNVERIFIED by difftest (busy-waits on the PI and reads the cartridge through
 * KSEG1, which neither harness maps); checked by reading against the asm, see docs/port/sessions/P62.md. */
extern vu8 g_pi_direct_read_active;       /* 1 while a direct cartridge read is in progress; was D_8003A8D2 */
extern vu8 g_pi_dma_busy;       /* nonzero while a PI DMA owner holds the bus: wait; was D_8003A8D3 */
extern vu8 g_pi_restart_thread;       /* restart thread g_os_pi_thread after the read; was D_8003A8D5; was D_80035C70 */
extern OSThread g_os_pi_thread; /* was D_80035C70 */

#define CART_WORD(addr) (*(vu32 *)((u32)(addr) | 0xA0000000))

/*
 * Blocking read of `size` bytes (rounded up to even) from cartridge address devAddr (| the ROM base g_os_rom_base)
 * into dramAddr, with uncached 32-bit loads from the PI's KSEG1 window. The cartridge is word-addressed, so a
 * halfword-aligned devAddr is read from the word before it: its low half is the first halfword, then each
 * word is split into the high half (for the halfword at +2) and the low half (for the next one).
 * The copy loops are do / while loops tested on the index after the step (unsigned), like the asm.
 */
/* was func_1000480C */
void rom_read_direct(s32 devAddr, void *dramAddr, u32 size) {
    u32 w;
    u32 i;
    u32 end;

    g_pi_direct_read_active = 1;
    size = (size + 1) & ~1;
    while (g_pi_dma_busy != 0) {
    }
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
    }
    devAddr |= g_os_rom_base;

    if (devAddr & 2) {
        /* first halfword: low half of the word that holds it */
        w = CART_WORD(devAddr - 2);
        size -= 2;
        *(u16 *)dramAddr = (u16)w;
        end = size - 2;
        i = 0;
        if (end != 0) {
            do {
                w = CART_WORD(devAddr + 2 + i);
                *(u16 *)((u8 *)dramAddr + i + 2) = (u16)(w >> 16);
                *(u16 *)((u8 *)dramAddr + i + 4) = (u16)w;
                i += 4;
            } while (i < end);
        }
        if (size & 2) {
            /* last halfword: high half of the next word */
            w = CART_WORD(devAddr + i + 2);
            *(u16 *)((u8 *)dramAddr + i + 2) = (u16)(w >> 16);
        }
    } else {
        end = size - 2;
        i = 0;
        if (end != 0) {
            do {
                *(u32 *)((u8 *)dramAddr + i) = CART_WORD(devAddr + i);
                i += 4;
            } while (i < end);
        }
        if (size & 2) {
            w = CART_WORD(devAddr + i);
            *(u16 *)((u8 *)dramAddr + i) = (u16)(w >> 16);
        }
    }

    g_pi_direct_read_active = 0;
    if (g_pi_restart_thread != 0) {
        osStartThread(&g_os_pi_thread);
    }
}
