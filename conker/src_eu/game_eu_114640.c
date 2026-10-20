#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 memcpy(s32, f32 *, s32);


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

extern s32 D_80088DE4;
void func_150E7498(f32 *arg0) {
    f32 *v;
    f32 t;
    f32 a;
    f32 b;
    f32 c;
    v = ((f32 **)&D_80088DE4)[func_150ADA20() % 6U];
    t = func_150ADA68();
    a = v[0];
    arg0[0] = (v[3] - a) * t + a;

    arg0[1] = (v[4] - (b = v[1])) * t + b;

    arg0[2] = (v[5] - (c = v[2])) * t + c;
}

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

typedef struct { f32 x, y, z; } Vec3_150E892C;
void func_150E892C(Vec3_150E892C *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        Vec3_150E892C unk0;
        f32 unkC;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = *arg0;
    tmp.unkC = 0.0f;
    temp_v0 = func_15149130((arg1 == -1) ? 300 : arg1, -1, 0x28, -1, (arg1 == -1) ? 0 : 1, 0, 0x10, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E89F0.s")

s32 func_150E8DA4(u8 *arg0, s32 arg1) {
    func_15131D98(arg0, arg0 + 0xAC, arg0 + 0xA8, arg0 + 0xAA);
    return 1;
}

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

extern f32 D_800BE9A4;
s32 func_151308E4(void *, s32, s32, u8, s32);
void func_151436B4(f32, f32, f32, f32 *);
void func_150E92DC(u8 *arg0) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x10];
    } sp;
    s32 obj;
    f32 scale;
    u8 *p;
    s32 b;
    f32 r0;
    f32 r1;

    p = arg0 + 0x28;
    *(f32 *)(p + 0x14) += (*(f32 *)(p + 0xC) + func_150ADA68() * *(f32 *)(p + 0x10)) * D_800BE9A4;
    if (*(f32 *)(p + 0x14) > 1.0f) {
        s32 a;

        sp.u51 = 0x16;
        sp.u3C = 0xE01;
        sp.u34 = 0x200005;
        sp.u38 = 0;
        sp.u40 = 0;
        sp.u44 = 0;
        sp.u8C = 0x801E05;
        sp.u94 = 3;
        sp.u95 = 3;
        sp.u96 = 0x1A;
        sp.u97 = -1;
        sp.u70 = 0.0f;
        sp.u74 = 0.0f;
        sp.u78 = 0.0f;
        sp.u88 = 0.0f;
        sp.u4B = 0xFF;
        sp.u50 = 0xFF;
        sp.u52 = 0x1E;
        sp.u54 = 8;
        sp.u7C = 0.0f;
        sp.u84 = 0.0f;
        do {
            scale = 0.9701f;
            sp.u56 = sp.u3E = (func_150ADA20() & 0xF) + 0x28;
            sp.u4F = (func_150ADA20() % 119U) + 0x64;
            sp.u5C = sp.u60 = (func_150ADA68() * 59.0f) + 80.0f;
            sp.u58 = ((func_150ADA68() * 3727.0f) + 99979.0f) * 0.00001f;
            sp.u8C &= ~0xC0;
            if (func_150ADA20() & 1) {
                a = 0x80;
            } else {
                a = 0;
            }
            if (func_150ADA20() & 1) {
                b = 0x40;
            } else {
                b = 0;
            }
            sp.u8C |= (u32)(b | a); // fakematch: the u32 cast picks the or-register order
            sp.u4C = 0x44;
            sp.u4D = 0x3C;
            sp.u4E = 0x27;
            sp.u48 = 0xF;
            sp.u49 = 0x11;
            sp.u4A = 5;
            r0 = func_150ADA68();
            r1 = func_150ADA68();
            func_151436B4(r0 * 6.2831855f, r1 * 6.2831855f, func_150ADA68() * 20.0f, &sp.u64);
            sp.u64 += *(f32 *)(p + 0);
            sp.u68 += *(f32 *)(p + 4);
            sp.u6C += *(f32 *)(p + 8);
            sp.u80 = ((func_150ADA68() * 471.0f) + -1242.0f) * 0.01f;
            obj = func_151308E4(&sp, 0, 4, arg0[0xC], arg0[1]);
            if (obj != 0) {
                memcpy(obj + 0xA8, &scale, 4);
            }
            *(f32 *)(p + 0x14) -= 1.0f;
        } while (*(f32 *)(p + 0x14) > 1.0f);
    }
}

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
