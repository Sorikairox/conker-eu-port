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
s32 func_10025B60(s32, void *); /* __osSiRawStartDma */
s32 func_151DDCC0(OSMesgQueue *mq, OSContStatus *data); /* __osEepStatus */
void func_151DDC0C(u8 address, u8 *buffer); /* __osPackEepWriteData */
s32 func_151DDA90(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
    u16 type;
    u8 *ptr = (u8 *)&D_800E0E60.ramarray;
    __OSContEepromFormat_s86 eepromformat;
    OSContStatus sdata;

    __osSiGetAccess();
    ret = func_151DDCC0(mq, &sdata);
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
        func_151DDCC0(mq, &sdata);
    }
    func_151DDC0C(address, buffer);
    ret = func_10025B60(OS_WRITE, &D_800E0E60);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = func_10025B60(OS_READ, &D_800E0E60);
    D_80042DE0 = 5;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ptr += 4;
    eepromformat = *(__OSContEepromFormat_s86 *)ptr;
    ret = (eepromformat.rxsize & 0xC0) >> 4;
    __osSiRelAccess();
    return ret;
}

void func_151DDC0C(u8 address, u8 *buffer) {
    u8 *ptr = (u8 *)&D_800E0E60.ramarray;
    __OSContEepromFormat_s86 eepromformat;
    int i;

    D_800E0E60.pifstatus = 1;
    eepromformat.txsize = 10;
    eepromformat.rxsize = 1;
    eepromformat.cmd = 5;
    eepromformat.address = address;
    for (i = 0; i < 8; i++) {
        eepromformat.data[i] = *buffer++;
    }
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__OSContEepromFormat_s86 *)(ptr) = eepromformat;
    ptr += sizeof(__OSContEepromFormat_s86);
    ptr[0] = 0xFE;
}

s32 func_151DDCC0(OSMesgQueue *mq, OSContStatus *data) {
    s32 ret = 0;
    int i;
    u8 *ptr = (u8 *)D_800E0E60.ramarray;
    __OSContRequesFormat_s86 requestformat;

    for (i = 0; i < 16; i++) {
        D_800E0E60.ramarray[i] = 0;
    }
    D_800E0E60.pifstatus = 1;
    ptr = (u8 *)D_800E0E60.ramarray;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    requestformat.dummy = 0xFF;
    requestformat.txsize = 1;
    requestformat.rxsize = 3;
    requestformat.cmd = 0;
    requestformat.typeh = 0xFF;
    requestformat.typel = 0xFF;
    requestformat.status = 0xFF;
    requestformat.dummy1 = 0xFF;
    *(__OSContRequesFormat_s86 *)ptr = requestformat;
    ptr += sizeof(__OSContRequesFormat_s86);
    *ptr = 0xFE;
    ret = func_10025B60(OS_WRITE, &D_800E0E60);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    D_80042DE0 = 0xFE;
    if (ret != 0) {
        return ret;
    }
    ret = func_10025B60(OS_READ, &D_800E0E60);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    if (ret != 0) {
        return ret;
    }
    ptr = (u8 *)&D_800E0E60;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    requestformat = *(__OSContRequesFormat_s86 *)ptr;
    data->errno = (requestformat.rxsize & 0xC0) >> 4;
    data->type = (requestformat.typel << 8) | requestformat.typeh;
    data->status = requestformat.status;
    return data->errno;
}

#ifdef NON_MATCHING
extern s32 D_800E0EA0;
extern s32 D_800E0EA4;
extern s8 D_800E1002;

void func_151DDE70(void) {
    s32 temp_t5;
    u16 temp_v0;
    u8 *temp_a0;

    temp_a0 = D_800E0EA0 + (D_800E0EA4 * 6);
    (*(s8 *)((u8 *)D_800BE748 + 2)) = (s8) (*(s8 *)((u8 *)temp_a0 + 0));
    (*(s8 *)((u8 *)D_800BE748 + 3)) = (s8) (*(s8 *)((u8 *)temp_a0 + 1));
    D_800E1002 = 0;
    (*(u16 *)((u8 *)D_800BE748 + 0)) = (*(u16 *)((u8 *)temp_a0 + 4)) | ((*(u16 *)((u8 *)D_800BE748 + 0)) & 0x1000);
    if (D_800E0EA4 < 0x1F3) {
        temp_v0 = (*(u16 *)((u8 *)temp_a0 + 8));
        if (D_800BE9E4 < (s32) temp_v0) {
            D_800E1002 = temp_v0 - D_800BE9E4;
        }
    }
    temp_t5 = D_800E0EA4 + 1;
    D_800BE9E4 = (s32) (*(u16 *)((u8 *)temp_a0 + 2));
    D_800E0EA4 = temp_t5;
    if (temp_t5 >= 0x1F3) {
        D_800E0EA4 = 0x1F3;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B2A0/func_151DDE70.s")
#endif