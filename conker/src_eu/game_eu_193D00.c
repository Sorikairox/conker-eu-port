#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_193D00/func_151664F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_193D00/func_15166688.s")

void func_15166774(struct102 *arg0) {
    s32 temp_v0;

    *(s16 *)((u8 *)arg0 + 0x9E) += *(s16 *)((u8 *)arg0 + 0x96) * D_800BE9E4;
    temp_v0 = *(u8 *)((u8 *)arg0 + 0x92);
    temp_v0 -= D_800BE9E4;
    if (temp_v0 <= 0) {
        func_1516972C(arg0);
        return;
    }
    *(u8 *)((u8 *)arg0 + 0x92) = temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_193D00/func_151667D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_193D00/func_15166E28.s")
