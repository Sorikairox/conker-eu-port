#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12C5F0/func_150FEDE0.s")

extern s32 D_800A23D0;
s32 func_15145EA4(s32 **, s32 *, s32, s32);
extern u8 D_80088F40;
void func_150FF148(u8 *arg0, s32 arg1, s32 arg2) {
    s32 pad;
    s32 *sp20;
    s32 sp1C;
    s32 v;
    v = *(s32 *)(arg0 + 0x1D4) + (D_80088F40 << 6);
    sp20 = &D_800A23D0;
    sp1C = arg2;
    func_15145EA4(&sp20, &sp1C, v, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12C5F0/func_150FF1A8.s")
