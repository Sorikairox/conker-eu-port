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

extern OSPifRam_s86 g_eep_pif_ram; /* __osEepPifRam (game copy); was D_800E0E60 */
extern u8 g_os_cont_last_cmd;           /* __osContLastCmd; was D_80042DE0 */
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 os_si_raw_start_dma(s32, void *); /* __osSiRawStartDma */
s32 game_eep_status(OSMesgQueue *mq, OSContStatus *data); /* __osEepStatus */
void game_eep_pack_write_data(u8 address, u8 *buffer); /* __osPackEepWriteData */
/* was func_151DDA90 */
s32 game_eeprom_write(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
    u16 type;
    u8 *ptr = (u8 *)&g_eep_pif_ram.ramarray;
    __OSContEepromFormat_s86 eepromformat;
    OSContStatus sdata;

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
    game_eep_pack_write_data(address, buffer);
    ret = os_si_raw_start_dma(OS_WRITE, &g_eep_pif_ram);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = os_si_raw_start_dma(OS_READ, &g_eep_pif_ram);
    g_os_cont_last_cmd = 5;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ptr += 4;
    eepromformat = *(__OSContEepromFormat_s86 *)ptr;
    ret = (eepromformat.rxsize & 0xC0) >> 4;
    __osSiRelAccess();
    return ret;
}

/* was func_151DDC0C */
void game_eep_pack_write_data(u8 address, u8 *buffer) {
    u8 *ptr = (u8 *)&g_eep_pif_ram.ramarray;
    __OSContEepromFormat_s86 eepromformat;
    int i;

    g_eep_pif_ram.pifstatus = 1;
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

/* was func_151DDCC0 */
s32 game_eep_status(OSMesgQueue *mq, OSContStatus *data) {
    s32 ret = 0;
    int i;
    u8 *ptr = (u8 *)g_eep_pif_ram.ramarray;
    __OSContRequesFormat_s86 requestformat;

    for (i = 0; i < 16; i++) {
        g_eep_pif_ram.ramarray[i] = 0;
    }
    g_eep_pif_ram.pifstatus = 1;
    ptr = (u8 *)g_eep_pif_ram.ramarray;
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
    ret = os_si_raw_start_dma(OS_WRITE, &g_eep_pif_ram);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    g_os_cont_last_cmd = 0xFE;
    if (ret != 0) {
        return ret;
    }
    ret = os_si_raw_start_dma(OS_READ, &g_eep_pif_ram);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    if (ret != 0) {
        return ret;
    }
    ptr = (u8 *)&g_eep_pif_ram;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    requestformat = *(__OSContRequesFormat_s86 *)ptr;
    data->errno = (requestformat.rxsize & 0xC0) >> 4;
    data->type = (requestformat.typel << 8) | requestformat.typeh;
    data->status = requestformat.status;
    return data->errno;
}

extern s32 g_demo_input_buf; /* was D_800E0EA0 */
extern s32 g_demo_input_index; /* was D_800E0EA4 */
extern s8 g_demo_frame_wait; /* was D_800E1002 */

/* was func_151DDE70 */
void demo_input_play_next(void) {
    s32 temp_t5;
    u16 temp_v0;
    u8 *temp_a0;

    temp_a0 = g_demo_input_buf + (g_demo_input_index * 6);
    (*(s8 *)((u8 *)g_pad_states + 2)) = (s8) (*(s8 *)((u8 *)temp_a0 + 0));
    (*(s8 *)((u8 *)g_pad_states + 3)) = (s8) (*(s8 *)((u8 *)temp_a0 + 1));
    g_demo_frame_wait = 0;
    (*(u16 *)((u8 *)g_pad_states + 0)) = (*(u16 *)((u8 *)temp_a0 + 4)) | ((*(u16 *)((u8 *)g_pad_states + 0)) & 0x1000);
    if (g_demo_input_index < 0x1F3) {
        temp_v0 = (*(u16 *)((u8 *)temp_a0 + 8));
        if (g_frame_ticks < (s32) temp_v0) {
            g_demo_frame_wait = temp_v0 - g_frame_ticks;
        }
    }
    temp_t5 = g_demo_input_index + 1;
    g_frame_ticks = (s32) (*(u16 *)((u8 *)temp_a0 + 2));
    g_demo_input_index = temp_t5;
    if (temp_t5 >= 0x1F3) {
        g_demo_input_index = 0x1F3;
    }
}