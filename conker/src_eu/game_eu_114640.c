#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E6E30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7104.s")

extern f32 *D_80088DDC;
extern f32 *D_80088DE0;
void func_150E73B4(f32 *arg0) {
    f32 *var_v0;
    f32 temp_f0;

    if (func_150ADA68() < 0.56322235f) {
        var_v0 = D_80088DDC;
    } else {
        var_v0 = D_80088DE0;
    }
    temp_f0 = func_150ADA68();
    arg0[0] = var_v0[0] + ((var_v0[3] - var_v0[0]) * temp_f0);
    arg0[1] = var_v0[1] + ((var_v0[4] - var_v0[1]) * temp_f0);
    arg0[2] = var_v0[2] + ((var_v0[5] - var_v0[2]) * temp_f0);
}

void func_150E7458(s32 arg0) {
    func_1514470C((&D_800D9A20)[func_150ADA20() & 1], arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7498.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E752C.s")

void func_150E764C(f32 *arg0, f32 *arg1) {
    arg0[0] = arg1[5];
    arg0[1] = arg1[6];
    arg0[2] = arg1[7];
}
void func_150E766C(s32 arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    f32 temp_f16;
    f32 temp_f2;

    (*(f32 *)arg3) = func_150484A0((*(f32 *)arg2), (*(f32 *)((u8 *)arg2 + 8)));
    (*(f32 *)((u8 *)arg3 + 8)) = (f32) (func_150ADA68() * 0.09f);
    (*(f32 *)((u8 *)arg3 + 0x10)) = (f32) (func_150ADA68() * 6.2831855f);
    (*(f32 *)((u8 *)arg3 + 0x18)) = (f32) (func_150ADA68() * 0.5f);
    temp_f2 = (*(f32 *)arg2);
    temp_f16 = (*(f32 *)((u8 *)arg2 + 8));
    (*(f32 *)((u8 *)arg3 + 4)) = (f32) (func_150484A0(sqrtf((temp_f2 * temp_f2) + (temp_f16 * temp_f16)), (*(f32 *)((u8 *)arg2 + 4))) - 1.5707964f);
    (*(f32 *)((u8 *)arg3 + 0xC)) = (f32) (func_150ADA68() * 0.07f);
    (*(f32 *)((u8 *)arg3 + 0x14)) = (f32) (func_150ADA68() * 6.2831855f);
    (*(f32 *)((u8 *)arg3 + 0x1C)) = (f32) (func_150ADA68() * 0.5f);
}
void func_150E7764(s32 arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    (*(f32 *)arg3) = func_150484A0((*(f32 *)arg2), (*(f32 *)((u8 *)arg2 + 8)));
    (*(f32 *)((u8 *)arg3 + 8)) = (f32) 0.47123894f;
    (*(f32 *)((u8 *)arg3 + 0x10)) = (f32) (func_150ADA68() * 6.2831855f);
    (*(f32 *)((u8 *)arg3 + 0x18)) = (f32) (func_150ADA68() * 0.2f);
    (*(f32 *)((u8 *)arg3 + 4)) = (f32) -0.5654867f;
    (*(f32 *)((u8 *)arg3 + 0xC)) = (f32) 0.31415927f;
    (*(f32 *)((u8 *)arg3 + 0x14)) = (f32) (func_150ADA68() * 6.2831855f);
    (*(f32 *)((u8 *)arg3 + 0x1C)) = (f32) (func_150ADA68() * 0.15f);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7B20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7C50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7F14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E821C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E856C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E8728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E892C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E89F0.s")

s32 func_150E8DA4(u8 *arg0, s32 arg1) {
    func_15131D98(arg0, arg0 + 0xAC, arg0 + 0xA8, arg0 + 0xAA);
    return 1;
}

s32 memcpy(s32, f32 *, s32);

void func_150E8854(void) {
    struct260 *temp_v0;
    f32 sp30;

    sp30 = 10.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x35, -1, 0U, 0U, (struct37 *)4, 0xFFU, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &sp30, 4);
    }
}

s32 func_150E8EB0(u8 *);
void func_150E8E40(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x28)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x28)) < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((func_150ADA68() * 337.0f) + 201.0f);
        func_150E8EB0(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E8EB0.s")

void func_150E9000(void) {
    struct260 *temp_v0;
    f32 v[3];

    v[0] = 1.2e-07f;
    v[1] = 3.2e-07f;
    v[2] = 0.0f;
    temp_v0 = func_15149130((func_150ADA20() % 41U) + 30, -1, 0x33, -1, 1, 0, 12, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, v, 12);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E909C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E92DC.s")

void func_150E965C(void) {
    struct260 *temp_v0;
    f32 v[3];

    v[0] = 2e-07f;
    v[1] = 1.5e-07f;
    v[2] = 0.0f;
    temp_v0 = func_15149130((func_150ADA20() % 26U) + 5, -1, 0x36, -1, 1, 0, 12, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, v, 12);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E96F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E995C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E9C9C.s")
