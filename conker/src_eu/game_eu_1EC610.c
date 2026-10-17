#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BEE00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF0D0.s")

s32 func_151BF244(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    *arg4 = 1;
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF268.s")

s32 func_151BF444(u8 *arg0) {
    if (arg0[0x127] == 0xFF) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BF8F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BFDCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151C00DC.s")

void func_151C0154(struct260 * arg0) {
    func_151C00DC(arg0);
    func_1514933C(arg0);
}

void func_151C0180(struct260 * arg0) {
    func_151C00DC(arg0);
    func_15149368(arg0);
}

void func_151C01AC(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x57) {
        func_1516972C(arg0);
    }
}
