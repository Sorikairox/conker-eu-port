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

void func_151604E4(void *arg0, s32 arg1, u8 arg2, s32 arg3);

void func_150AFC18(s16 arg0, u8 arg1, s32 arg2) {
    struct {
        s8 unk0;
        s8 unk1;
        s8 unk2;
        s16 unk4;
        s8 unk6;
    } sp18;

    sp18.unk0 = 1;
    sp18.unk1 = -1;
    sp18.unk2 = 2;
    sp18.unk6 = 0;
    sp18.unk4 = arg0;
    func_151604E4(&sp18, 0, arg1, arg2);
}

void func_150AFC70(s32 arg0, s32 arg1) {
    func_150B2290(arg1, arg1 + 0x1ECC0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AFCA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B00D4.s")

s32 func_1516DF0C(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150B0148(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516DF0C(1, 0, 0, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 1, 0, 0, 0, 0, 0xAA, 0xAA, 0xAA, 0xAA, arg2, arg3, 0, arg0, 0xF0, 0x50, 0x50, 1, 4, 0, 1, 0, 0, 0, arg1, 0, (s32) arg4, arg5);
}

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
