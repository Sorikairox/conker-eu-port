#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"

// EU addresses are in undefined_syms.eu.txt; this file is built -O1
extern OSPifRam __osPfsPifRam;
extern u8 _osLastSentSiCmd; // __osContLastCmd
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 os_si_raw_start_dma(s32, void *); // __osSiRawStartDma
u8 __osContAddressCrc(u16 addr);
u8 __osContDataCrc(u8 *data);
s32 __osPfsGetStatus(OSMesgQueue *queue, int channel);
void os_pack_ram_write_data(int channel, u16 address, u8 *buffer);

s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer, int force) {
    s32 ret;
    int i;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int retry;

    ret = 0;
    ptr = (u8 *)&__osPfsPifRam;
    retry = 2;
    if ((force != TRUE) && (address < 7) && (address != 0)) {
        return 0;
    }
    __osSiGetAccess();
    _osLastSentSiCmd = CONT_CMD_WRITE_MEMPACK;
    os_pack_ram_write_data(channel, address, buffer);
    ret = os_si_raw_start_dma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    do {
        for (i = 0; i < 16; i++) {
            __osPfsPifRam.ramarray[i] = 0xFF;
        }
        __osPfsPifRam.pifstatus = 0;
        ret = os_si_raw_start_dma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ptr = (u8 *)&__osPfsPifRam;
        if (channel != 0) {
            for (i = 0; i < channel; i++) {
                ptr++;
            }
        }
        ramreadformat = *(__OSContRamReadFormat *)ptr;
        ret = CHNL_ERR(ramreadformat);
        if (ret == 0) {
            if (__osContDataCrc(buffer) != ramreadformat.datacrc) {
                ret = __osPfsGetStatus(mq, channel);
                if (ret != 0) {
                    __osSiRelAccess();
                    return ret;
                }
                ret = PFS_ERR_CONTRFAIL;
            }
        }
    } while ((ret == PFS_ERR_CONTRFAIL) && (retry-- >= 0));
    __osSiRelAccess();
    return ret;
}

// __osPackRamWriteData
/* was func_10025E40 */
void os_pack_ram_write_data(int channel, u16 address, u8 *buffer) {
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int i;

    ptr = (u8 *)__osPfsPifRam.ramarray;
    for (i = 0; i < 16; i++) {
        __osPfsPifRam.ramarray[i] = 0;
    }
    __osPfsPifRam.pifstatus = CONT_CMD_EXE;
    ramreadformat.dummy = CONT_CMD_NOP;
    ramreadformat.txsize = CONT_CMD_WRITE_MEMPACK_TX;
    ramreadformat.rxsize = CONT_CMD_WRITE_MEMPACK_RX;
    ramreadformat.cmd = CONT_CMD_WRITE_MEMPACK;
    ramreadformat.address = (address << 5) | __osContAddressCrc(address);
    ramreadformat.datacrc = CONT_CMD_NOP;
    for (i = 0; i < 32; i++) {
        ramreadformat.data[i] = *buffer++;
    }
    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }
    *(__OSContRamReadFormat *)ptr = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = CONT_CMD_END;
}
