#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_10004470(void) {
    int i;
    osCreatePiManager(150, &D_800388B0, &D_800380E0, 0xC8);

    for (i = 0; i < 3; i++)
    {
        osCreateMesgQueue(&gMessageQueue[i], &gMessages[i], 1);
    }

    osCreateMesgQueue(&gMessageQueue0, &gMessage0, 300);
    D_8003A570 = 0;
    D_8003A571 = 0;
}

s32 func_10004514(s32 devAddr, void *dramAddr, u32 size, s32 arg3) {
    OSMesgQueue *msgQueue;
    OSIoMesg tmpIoMsg;
    OSIoMesg *ioMsg;
    s32 sp3c;

    sp3c = __osRunningThread->id - 3;
    if ((size < 0xC8U) && (sp3c == 0)) {
        func_1000480C(devAddr, dramAddr, size);
        return;
    }
    if ((sp3c >= 4) || ( sp3c < 0)) {
        sp3c = 0;
    }
    if (arg3 == 0) {
        if (D_8003A571 != 300) { // messages waiting?
            ioMsg = &D_80038950[D_8003A570];
            msgQueue = &gMessageQueue0;
            if (D_8003A570 == 299) { // number of message queues used?
                D_8003A570 = 0;
            } else {
                D_8003A570 += 1U;
            }
            D_8003A571 += 1U;
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

void func_10004674(void) {
    int i;
    for (i = 0; i < D_8003A571; i++)
    {
        osRecvMesg(&gMessageQueue0, 0, OS_MESG_BLOCK);
    }

    D_8003A571 = 0;
}

void func_100046E4(u32 devAddr, u8 *dramAddr, u32 size) {
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
#ifdef NON_MATCHING
/* P62: hand-written from the asm. UNVERIFIED by difftest (busy-waits on the PI and reads the cartridge through
 * KSEG1, which neither harness maps); checked by reading against the asm, see docs/port/sessions/P62.md. */
extern vu8 D_8003A8D2;       /* 1 while a direct cartridge read is in progress */
extern vu8 D_8003A8D3;       /* nonzero while a PI DMA owner holds the bus: wait */
extern vu8 D_8003A8D5;       /* restart thread D_80035C70 after the read */
extern OSThread D_80035C70;

#define CART_WORD(addr) (*(vu32 *)((u32)(addr) | 0xA0000000))

/*
 * Blocking read of `size` bytes (rounded up to even) from cartridge address devAddr (| the ROM base D_80000308)
 * into dramAddr, with uncached 32-bit loads from the PI's KSEG1 window. The cartridge is word-addressed, so a
 * halfword-aligned devAddr is read from the word before it: its low half is the first halfword, then each
 * word is split into the high half (for the halfword at +2) and the low half (for the next one).
 * The copy loops are do / while loops tested on the index after the step (unsigned), like the asm.
 */
void func_1000480C(s32 devAddr, void *dramAddr, u32 size) {
    u32 w;
    u32 i;
    u32 end;

    D_8003A8D2 = 1;
    size = (size + 1) & ~1;
    while (D_8003A8D3 != 0) {
    }
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
    }
    devAddr |= D_80000308;

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

    D_8003A8D2 = 0;
    if (D_8003A8D5 != 0) {
        osStartThread(&D_80035C70);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_4470/func_1000480C.s")
#endif
