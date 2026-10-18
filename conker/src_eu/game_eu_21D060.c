#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21D060/func_151EF850.s")

extern u8 D_80042DE1;
extern OSPifRam D_80042DA0;
void func_151EFA48(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits;

    bits = 0;
    ptr = (u8 *)D_80042DA0.ramarray;
    for (i = 0; i < D_80042DE1; i++, ptr += sizeof(requestformat), data++) {
        requestformat = *(__OSContRequesFormat *)ptr;
        data->errno = CHNL_ERR(requestformat);
        if (data->errno == 0) {
            data->type = (requestformat.typel << 8) | requestformat.typeh;
            data->status = requestformat.status;
            bits |= 1 << i;
        }
    }
    *pattern = bits;
}

extern OSPifRam __osContPifRam;
extern u8 _osContNumControllers;
void func_151EFB18(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;

    for (i = 0; i < 16; i++) {
        __osContPifRam.ramarray[i] = 0;
    }
    __osContPifRam.pifstatus = CONT_CMD_EXE;
    ptr = (u8 *)__osContPifRam.ramarray;
    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;
    for (i = 0; i < _osContNumControllers; i++) {
        *(__OSContRequesFormat *)ptr = requestformat;
        ptr += sizeof(requestformat);
    }
    *ptr = CONT_CMD_END;
}
