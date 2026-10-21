#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_203C50/func_151D6440.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_203C50/func_151D6760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_203C50/func_151D69C8.s")

void func_151D6CA0(s32 arg0, s32 arg1) {
    if (D_800BE9F0 == 6 && D_80038080 == 0) {
        return;
    }
    if (arg1 == 0) {
        arg0 = 0;
    }
    D_800BE574 = arg0;
    if (arg0 != 0) {
        D_800BE575 = arg1;
    } else {
        D_800BE575 = 0;
    }
    if (arg0 == 0 && D_800BE570 != 0) {
        func_100043B4((s32 *)D_800BE570, 3);
        D_800BE570 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_203C50/func_151D6D28.s")
