#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_113D60/func_150E6550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_113D60/func_150E67B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_113D60/func_150E6920.s")

s32 func_150E6D1C(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    s32 temp_v1;

    if (temp_v0 < 8) {
        temp_v1 = temp_v0 << 5;
        if (temp_v1 < arg0[0x5C]) {
            arg0[0x5C] = temp_v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_113D60/func_150E6D50.s")
