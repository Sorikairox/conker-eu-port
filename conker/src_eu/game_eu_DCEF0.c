#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AF6E0.s")

void func_150AF7C0(s32 arg0, s16 *arg1) {
    func_151CFE48(arg0, (f32)(arg1[4] + arg1[1]), (f32)arg1[1], arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AF808.s")

s32 func_150AFBC4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, *(s32 *)(p + 0xC));
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AFC18.s")

void func_150AFC70(s32 arg0, s32 arg1) {
    func_150B2290(arg1, arg1 + 0x1ECC0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AFCA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B00D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0148.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0290.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0344.s")

void func_150B051C(s32 arg0) {
    if (D_800BE9F0 == 6) {
        func_15179008(0);
        func_150AF6E0(0xE2, 0xE1);
    } else {
        func_150AF6E0(0xDF, 0xDE);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0574.s")

void func_150B07A0(struct102 **arg0) {
    if (*(s32 *)&arg0[0x170 / 4] != 0) {
        func_1516972C(arg0[0x170 / 4]);
    }
}

void func_150B07D0(u8 *arg0) {
    func_150B07A0(arg0);
    func_15132AE0(arg0);
}

void func_150B07FC(u8 *arg0) {
    func_150B07A0(arg0);
    func_15132B0C(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0AEC.s")
