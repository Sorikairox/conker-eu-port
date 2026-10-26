#include <ultra64.h>

#include "functions.h"
#include "variables.h"

// libultra os/initialize.c, pre-2.0J osInitialize (-O1): no osViClock, Rare/leo tail (PI wait + 64DD detect)
typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;
extern __osExceptionVector __osExceptionPreamble[];
extern u32 D_80042C70; /* __osFinalrom */
u64 osClockRate = 62500000;
u32 __osShutdown = 0;
u32 __OSGlobalIntMask = OS_IM_ALL;
u32 D_8002C070 = 0; // __osLeoPresent?
u32 __osGetSR(void);
void __osSetSR(u32);
void __osSetFpcCsr(u32);
s32 __osSpRawReadIo(u32, u32 *);
s32 __osSpRawWriteIo(u32, u32);
void os_writeback_dcache(void *, s32); /* osWritebackDCache */
void osInvalICache(void *, s32);
void os_map_tlb_rdb(void); /* osMapTLBRdb */
s32 osPiRawReadIo(u32, u32 *);
void bzero(void *, int);
void __osSetHWIntrRoutine(s32, s32 (*)(void));
s32 __osLeoInterrupt(void); /* __osLeoInterrupt */

void __osInitialize_common(void) {
    u32 pifdata;
    u32 clock = 0;
    u32 leostat;
    u32 stat;

    D_80042C70 = TRUE;
    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV | FPCSR_RM_RN);
    while (__osSpRawReadIo(PIF_RAM_END - 3, &pifdata)) {
        ;
    }
    while (__osSpRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) {
        ;
    }
    *(__osExceptionVector *)UT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)XUT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)ECC_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)E_VEC = *__osExceptionPreamble;
    os_writeback_dcache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    os_map_tlb_rdb();
    osPiRawReadIo(4, &clock);
    clock &= ~0xf;
    if (clock != 0) {
        osClockRate = clock;
    }
    osClockRate = osClockRate * 3 / 4;
    if (D_8000030C == 0) {
        bzero(D_8000031C, 0x40);
    }
    stat = IO_READ(PI_STATUS_REG);
    while (stat & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        stat = IO_READ(PI_STATUS_REG);
    }
    if (!((leostat = IO_READ(0x05000508)) & 0xFFFF)) {
        D_8002C070 = 1;
        __osSetHWIntrRoutine(1, __osLeoInterrupt);
    } else {
        D_8002C070 = 0;
    }
}
