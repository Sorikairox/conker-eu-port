#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15046F70(f32 *, s32, f32, s32);
s32 func_1504715C(s32, struct127 *);
s32 func_15142314(s32, s32, f32 *, u8);
s32 func_150EB4D0(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 var_a1;

    if ((arg3 != 1) && ((u32)arg3 != 2)) { // fakematch: unsigned cast keeps the compare on a3 (permuter)
        return 0;
    }
    var_a1 = (arg3 == 1) ? 0x21 : 0x1D;
    func_15142314(*(s32 *)(arg1 + 0x1D4), var_a1, arg0, arg3);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 10.0f;
    sp2C[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046F70(sp2C, 0, arg0[1] - 50.0f, arg2);
}

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
