#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BB760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BC03C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BC968.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BCBBC.s")

s32 func_150BD498(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) * 1.1f + arg4;
    if (*(f32 *)(arg0 + 0x48) > -2.0f) {
        *(f32 *)(arg0 + 0x44) = 0.0f;
        *(s32 *)(arg0 + 0x60) &= ~0x6F;
        *(f32 *)(arg0 + 0x48) = 0.0f;
        *(f32 *)(arg0 + 0x4C) = 0.0f;
    } else {
        f32 k = *(f32 *)(arg0 + 0x14);

        *(f32 *)(arg0 + 0x44) *= k;
        *(f32 *)(arg0 + 0x48) = -*(f32 *)(arg0 + 0x48) * k;
        *(f32 *)(arg0 + 0x4C) *= k;
        *(f32 *)(arg0 + 0x50) *= k;
        *(f32 *)(arg0 + 0x54) *= k;
        *(f32 *)(arg0 + 0x58) *= k;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E9450/func_150BD550.s")
