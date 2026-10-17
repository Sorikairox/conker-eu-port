#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501BB20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501BBB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501BFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C0D0.s")

void func_1501C15C(u8 arg0) {
    s32 temp_v0 = D_800843F0[arg0];

    if (temp_v0 < 4) {
        D_800BED5C[temp_v0] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C1B0.s")

void func_1501C51C(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        func_1501C15C(i);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C55C.s")
