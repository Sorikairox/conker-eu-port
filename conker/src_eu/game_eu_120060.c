#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_120060/func_150F2850.s")

s32 func_150F28FC(s32 arg0, s32 arg1) {
    return 0xE;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_120060/func_150F2910.s")

s32 func_150F2960(u8 *arg0) {
    f32 *temp_s0;

    temp_s0 = (f32 *)(arg0 + 0x170);
    *(f32 *)(arg0 + 0x20) = temp_s0[4] * sinf(*(f32 *)(arg0 + 0x170));
    *(f32 *)(arg0 + 0x28) = temp_s0[5] * sinf(temp_s0[1]);
    temp_s0[0] = func_15144B68((temp_s0[2] * D_800BE9A4) + temp_s0[0]);
    temp_s0[1] = func_15144B68((temp_s0[3] * D_800BE9A4) + temp_s0[1]);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_120060/func_150F2A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_120060/func_150F2A98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_120060/func_150F2B20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_120060/func_150F2C20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_120060/func_150F2F14.s")
