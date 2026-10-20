#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1EC610/func_151BEE00.s")

s32 func_151BF0D0(u8 *arg0) {
    func_150A8050(((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0], 0.0f, *(f32 *)(arg0 + 0x120), 0.0f);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][0] = *(f32 *)(arg0 + 0x54);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][1] = *(f32 *)(arg0 + 0x58);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][3][2] = *(f32 *)(arg0 + 0x5C);
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][0][2] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][1][2] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][0] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][1] *= 0.92300004f;
    ((f32 (*)[4][4])(arg0 + 0x7C))[D_800BE9C0][2][2] *= 0.92300004f;
    return 1;
}

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

void func_151C00DC(u8 *arg0) {
    u8 *new_var; // fakematch: pointer temp keeps arg0 out of s-regs (permuter artifact)
    struct102 *temp_a0;
    u8 *v;
    s32 i;
    new_var = arg0 + 0x28;
    if (*(s32 *)new_var != 0) {
        func_1516972C((struct102 *)*(s32 *)new_var);
    }
    v = arg0 + 0x28;
    i = 0;
    do {
        temp_a0 = *(struct102 **)((v + 4) + (i * 4));
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        i = (i + 1) & 0xFF;
    } while (i < 2);
}

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
