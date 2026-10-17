#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_118CE0/func_150EB4D0.s")

s32 func_151420F8(s32);

s32 func_150EB5B0(s32 arg0, s32 arg1) {
    if (arg0 == 1) {
        if (D_800BE9F0 == 4) {
            if (func_151420F8(arg1) != 0) {
                return 6;
            }
            return 3;
        }
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return -1;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_118CE0/func_150EB610.s")
