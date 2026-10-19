#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15146E00.s")

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
