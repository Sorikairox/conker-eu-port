#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1512DC60(u8 *arg0) {
    u8 *temp_v0 = D_800DC6F0[arg0[0x23D]];

    *(s32 *)(temp_v0 + 0x50) = 5;
    *(f32 *)(temp_v0 + 0x54) = 0.0f;
    *(f32 *)(temp_v0 + 0x58) = 0.0f;
    *(f32 *)(temp_v0 + 0x5C) = 0.0f;
    *(f32 *)(temp_v0 + 0x60) = 0.0f;
    *(f32 *)(temp_v0 + 0x2C) = 0.0f;
    *(f32 *)(temp_v0 + 0x28) = -1.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B470/func_1512D748.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B470/func_1512DEF0.s")
