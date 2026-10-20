#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


s32 __osSiGetAccess();
s32 __osSiRelAccess();
s32 func_10025B60(s32, s32 *);
void func_151F03CC(void);
extern s32 D_80042DA0;
extern s32 D_80042DDC;
extern u8 D_80042DE0;

s32 func_151F0260(OSMesgQueue *arg0) {
    s32 sp1C;
    s32 sp18;

    sp1C = 0;
    __osSiGetAccess();
    if (D_80042DE0 != 1) {
        func_151F03CC();
        sp1C = func_10025B60(1, &D_80042DA0);
        osRecvMesg(arg0, NULL, 1);
    }
    for (sp18 = 0; sp18 < 0x10; sp18++) {
        *(s32 *)((u8 *)&D_80042DA0 + (sp18 * 4)) = 0xFF;
    }
    D_80042DDC = 0;
    sp1C = func_10025B60(0, &D_80042DA0);
    D_80042DE0 = 1;
    __osSiRelAccess();
    return sp1C;
}

extern s32 D_80042DA0;
extern u8 D_80042DE1;
void func_151F0324(OSContPad *data) {
    u8 *ptr = (u8 *)&D_80042DA0;
    __OSContReadFormat readformat;
    int i;

    for (i = 0; i < D_80042DE1; i++, ptr += sizeof(__OSContReadFormat), data++) {
        readformat = *(__OSContReadFormat *)ptr;
        data->errno = CHNL_ERR(readformat);
        if (data->errno == 0) {
            data->button = readformat.button;
            data->stick_x = readformat.stick_x;
            data->stick_y = readformat.stick_y;
        }
    }
}

extern s32 D_80042DA0;
extern s32 D_80042DDC;
extern u8 D_80042DE1;
void func_151F03CC(void) {
    u8 *ptr = (u8 *)&D_80042DA0;
    __OSContReadFormat readformat;
    int i;

    for (i = 0; i < 16; i++) {
        (&D_80042DA0)[i] = 0;
    }
    D_80042DDC = CONT_CMD_EXE;
    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;
    for (i = 0; i < D_80042DE1; i++) {
        *(__OSContReadFormat *)ptr = readformat;
        ptr += sizeof(__OSContReadFormat);
    }
    *ptr = CONT_CMD_END;
}
