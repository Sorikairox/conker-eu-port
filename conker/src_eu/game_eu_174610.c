#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15046F70(f32 *, s32, f32, s32);
s32 func_1504715C(s32, u8 *);
s32 func_15142314(s32, s32, f32 *, u8);

s32 func_15146E00(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 var_a1;

    if ((arg3 != 1) && ((u32)arg3 != 2)) { // fakematch: unsigned cast keeps the compare on a3 (permuter)
        return 0;
    }
    var_a1 = (arg3 == 1) ? 0x13 : 0x17;
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15146EE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15147008.s")

void func_15147128(s32 arg0, s32 arg1, s32 arg2) {
    func_15147168(arg0, arg1, arg2, 0);
}

void func_15147148(s32 arg0, s32 arg1, s32 arg2) {
    func_15147168(arg0, arg1, arg2, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15147168.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_151472D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_151473F4.s")

s32 func_15146E00(f32 *, u8 *, s32, u8);
s32 func_1514CBE8(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
void func_151475B0(u8 *arg0, volatile u8 arg1, s32 arg2) {
    f32 sp44[3];
    s16 sp42;
    u8 **q = &arg0; // fakematch: arg0 reloaded from its home slot
    if (*(s32 *)(*q + 0x1D4) != 0) {
        do {} while (0); // fakematch: permuter
        func_15146E00(sp44, *q, 0, arg1);
        sp42 = (func_150ADA20() % 11U) + 5;
        func_1514CBE8(sp44[0], sp44[1], *(s32 *)&sp44[2], func_150ADA68() * 11.0f, 0, 0xFF, sp42, 0x16, 0, 0.0f, 0, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_1514766C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15147888.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_151479E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15147B48.s")
