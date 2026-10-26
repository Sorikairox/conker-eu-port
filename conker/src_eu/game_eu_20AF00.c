#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    /* 0x00 */ u8 txsize;
    /* 0x01 */ u8 rxsize;
    /* 0x02 */ u8 cmd;
    /* 0x03 */ u8 address;
    /* 0x04 */ u8 data[8];
} __OSContEepromFormat_s86;

typedef struct {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u8 typeh;
    /* 0x05 */ u8 typel;
    /* 0x06 */ u8 status;
    /* 0x07 */ u8 dummy1;
} __OSContRequesFormat_s86;

typedef struct {
    /* 0x00 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} OSPifRam_s86;

extern OSPifRam_s86 D_800E0E60; /* __osEepPifRam (game copy) */
extern u8 D_80042DE0;           /* __osContLastCmd */
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 os_si_raw_start_dma(s32, void *); /* __osSiRawStartDma */
s32 game_eep_status(OSMesgQueue *mq, OSContStatus *data); /* __osEepStatus */
void game_eep_pack_write_data(u8 address, u8 *buffer); /* __osPackEepWriteData */
void game_eep_pack_read_data(u8 address);

/* was func_151DD6F0 */
s32 game_eeprom_read(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
    int i = 0;
    u16 type;
    u8 *ptr;
    OSContStatus sdata;
    __OSContEepromFormat_s86 eepromformat;

    ptr = (u8 *)&D_800E0E60.ramarray;
    __osSiGetAccess();
    ret = game_eep_status(mq, &sdata);
    type = sdata.type & (CONT_EEPROM | CONT_EEP16K);
    if (ret == 0) {
        switch (type) {
            case CONT_EEPROM:
                if (address >= 0x40) {
                    ret = -1;
                }
                break;
            case CONT_EEPROM | CONT_EEP16K:
                if (address >= 0x100) {
                    ret = -1;
                }
                break;
            default:
                ret = 8;
        }
    }
    if (ret != 0) {
        __osSiRelAccess();
        return ret;
    }
    while (sdata.status & CONT_EEPROM_BUSY) {
        game_eep_status(mq, &sdata);
    }
    game_eep_pack_read_data(address);
    ret = os_si_raw_start_dma(OS_WRITE, &D_800E0E60);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = os_si_raw_start_dma(OS_READ, &D_800E0E60);
    D_80042DE0 = 4;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    for (i = 0; i < 4; i++) {
        ptr++;
    }
    eepromformat = *(__OSContEepromFormat_s86 *)ptr;
    ret = (eepromformat.rxsize & 0xC0) >> 4;
    if (ret == 0) {
        for (i = 0; i < 8; i++) {
            *buffer++ = eepromformat.data[i];
        }
    }
    __osSiRelAccess();
    return ret;
}

/* was func_151DD8B4 */
void game_eep_pack_read_data(u8 address) {
    u8 *ptr = (u8 *)&D_800E0E60.ramarray;
    __OSContEepromFormat_s86 eepromformat;
    int i;

    D_800E0E60.pifstatus = 1;
    eepromformat.txsize = 2;
    eepromformat.rxsize = 8;
    eepromformat.cmd = 4;
    eepromformat.address = address;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__OSContEepromFormat_s86 *)(ptr) = eepromformat;
    ptr += sizeof(__OSContEepromFormat_s86);
    ptr[0] = 0xFE;
}
