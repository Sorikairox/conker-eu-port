#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u16 address;
    /* 0x6 */ u8 data[32];
    /* 0x26 */ u8 datacrc;
} __OSContRamReadFormat;

extern u8 D_80042DE0;  // __osContLastCmd
extern u8 D_80042D60[]; // __osPfsPifRam
extern u8 D_8003BFD0[]; // __MotorDataBuf
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 os_si_raw_start_dma(s32, void *); // __osSiRawStartDma

// libultra motor.c (osMotorStop)
/* was func_10005860 */
s32 os_motor_stop(OSPfs *pfs) {
    int i;
    s32 ret;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;

    __osSiGetAccess();
    D_80042DE0 = 3;
    os_si_raw_start_dma(OS_WRITE, &D_8003BFD0[pfs->channel << 6]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    os_si_raw_start_dma(OS_READ, D_80042D60);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    ptr = D_80042D60;
    if (pfs->channel != 0) {
        for (i = 0; i < pfs->channel; i++) {
            ptr++;
        }
    }
    ramreadformat = *(__OSContRamReadFormat *)ptr;
    ret = (ramreadformat.rxsize & 0xC0) >> 4;
    if (ret == 0 && ramreadformat.datacrc != 0) {
        ret = 4;
    }
    __osSiRelAccess();
    return ret;
}

extern u8 D_8003C0D0[]; // __MotorDataBuf (start)
// libultra motor.c (osMotorStart)
/* was func_10005990 */
s32 os_motor_start(OSPfs *pfs) {
    int i;
    s32 ret;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;

    __osSiGetAccess();
    D_80042DE0 = 3;
    os_si_raw_start_dma(OS_WRITE, &D_8003C0D0[pfs->channel << 6]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    os_si_raw_start_dma(OS_READ, D_80042D60);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    ptr = D_80042D60;
    if (pfs->channel != 0) {
        for (i = 0; i < pfs->channel; i++) {
            ptr++;
        }
    }
    ramreadformat = *(__OSContRamReadFormat *)ptr;
    ret = (ramreadformat.rxsize & 0xC0) >> 4;
    if (ret == 0 && ramreadformat.datacrc != 0xEB) {
        ret = 4;
    }
    __osSiRelAccess();
    return ret;
}
