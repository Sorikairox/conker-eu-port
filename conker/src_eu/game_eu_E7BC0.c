#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E7BC0/func_150BA3B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E7BC0/func_150BA83C.s")

s32 func_150BA85C(f32 *arg0) {
    arg0[0x114 / 4] += D_800A01FC * D_800BE9A4;
    arg0[0x34 / 4] += arg0[0x110 / 4] * D_800BE9A4;
    arg0[0x38 / 4] += arg0[0x114 / 4] * D_800BE9A4;
    arg0[0x3C / 4] += arg0[0x118 / 4] * D_800BE9A4;
    arg0[0x40 / 4] += arg0[0x11C / 4] * D_800BE9A4;
    arg0[0x44 / 4] += arg0[0x120 / 4] * D_800BE9A4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E7BC0/func_150BA904.s")
