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

void func_150E7C50(f32, s16, u8, u8, u8, s16, s16, s32, s32, u8, s32);
s32 func_150E7B20(f32 *, f32, s16, u8, u8, u8, s16, s16, s32, s32, u8, s32);
s32 func_1516547C(s32, s32, s32, s32, s32);
void func_150E9000(void);
void func_150E965C(void);
typedef struct { s32 w[2]; } E7810_V;
extern E7810_V D_80088DFC;

void func_150E7810(u8 arg0, u8 arg1, s32 arg2) {
    E7810_V v;
    f32 pos[2];
    structEU_151D8E18 s;

    if (func_150ADA68() < 0.0042f) {
        v = D_80088DFC;
        if (func_150ADA68() < 0.75000006f) {
            pos[0] = (func_150ADA68() * 300.0f) + -150.0f;
            pos[1] = (func_150ADA68() * 200.0f) + -100.0f;
            func_150E7B20(pos, ((func_150ADA68() * 150.0f) + 200.0f) * 0.1f, (func_150ADA20() % 201U) + 0x1F4, (u8)(((func_150ADA20() & 1) ? 2 : 0) | ((func_150ADA20() & 1) ? 4 : 0)) | 9, (func_150ADA20() % 26U) + 0x64, 0xFF, 0x40, 3, (s32)&v, 2, arg1, arg2);
        } else {
            func_150E7C50(((func_150ADA68() * 100.0f) + 150.0f) * 0.1f, (func_150ADA20() % 201U) + 0x1F4, 9, (func_150ADA20() % 26U) + 0x64, 0xFF, 0x40, 3, (s32)&v, 2, arg1, arg2);
        }
        func_10010F30(0x360, 0x7FFF, 0, 0, 0);
        func_1516547C(1, arg0, 0, arg1, arg2);
        s.unk0 = 1;
        s.unk2 = (func_150ADA20() % 26U) + 0x19;
        s.unk5 = 1;
        s.unk4 = (func_150ADA20() % 6U) + 3;
        s.unk6 = -1;
        func_151D8E18(&s, 0, 0xFF, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7B20.s")

s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);
typedef struct { s32 w[3]; } Vec3E7C50;
extern Vec3E7C50 D_80088E08;
extern Vec3E7C50 D_80088E14;

void func_150E7C50(f32 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u8 arg9, s32 argA) {
    s32 pad[6]; // fakematch: 0x18 unused bytes above the struct
    struct {
        f32 u0;
        f32 u4;
        f32 u8;
        f32 uC;
        s8 u10;
        s16 u12;
        u16 u14;
        s16 u16;
        s16 u18;
        u8 u1A;
        u8 u1B;
        u8 u1C;
        u8 u1D;
        u8 u1E;
        u8 u1F;
        u8 u20;
        u8 u21;
        u8 u22;
        u8 u23;
        s32 u24;
        s32 u28;
        s32 u2C;
        s32 u30;
        s32 u34;
        s32 u38;
        s32 u3C;
        u8 u40;
        u8 u41;
    } sp;
    u8 r;
    Vec3E7C50 a;
    Vec3E7C50 b;

    r = func_150ADA20() & 3;
    sp.u12 = arg1;
    sp.u14 = arg2 & 0xFFF9;
    sp.u16 = arg5;
    sp.u18 = arg6;
    sp.u1A = 5;
    sp.u1B = 0xFF;
    sp.u1C = 0xE6;
    sp.u1D = 0xBE;
    sp.u1E = arg3;
    sp.u1F = 0xFF;
    sp.u20 = 0xFF;
    sp.u21 = 0xFF;
    sp.u22 = 0xFF;
    sp.u23 = arg4;
    sp.u24 = 1;
    sp.u28 = 0;
    sp.u2C = 0;
    sp.u40 = 0;
    sp.u41 = 0xA;
    sp.u30 = 7;
    sp.u34 = 0x3C;
    sp.u38 = 0x80;
    sp.u3C = 0x20;
    sp.uC = arg0;
    sp.u8 = arg0;
    switch (r) {
    case 0:
    case 1:
        a = D_80088E08;
        sp.u10 = a.w[func_150ADA20() % 3U];
        sp.u4 = (func_150ADA68() * 160.0f) + -80.0f;
        switch (r) {
        case 0:
            sp.u14 |= 2;
            sp.u0 = 145.0f - arg0;
            break;
        case 1:
            sp.u0 = arg0 - 145.0f;
        dummy: ; // fakematch: label barrier keeps the swc1 out of the b delay slot
            break;
        }
        break;
    case 2:
    case 3:
        b = D_80088E14;
        sp.u10 = b.w[func_150ADA20() % 3U];
        sp.u0 = (func_150ADA68() * 260.0f) + -130.0f;
        switch (r) {
        case 2:
            sp.u14 |= 4;
            sp.u4 = 110.0f - arg0;
            break;
        case 3:
            sp.u4 = arg0 - 110.0f;
            break;
        }
        break;
    }
    func_151559FC(&sp, 0, arg7, arg8, 0, arg9, argA);
}

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

void func_150E8EB0();
void func_150E8E40(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x28)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x28)) < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((func_150ADA68() * 337.0f) + 201.0f);
        func_150E8EB0(arg0);
    }
}

typedef struct { s32 a, b; } E8EB0_V;
typedef struct { u8 a; u8 p1; s16 b; u8 c; u8 d; s8 e; } E8EB0_S;
extern E8EB0_V D_80088E20;
extern u8 D_800BEE0B;
void func_150E8EB0() {
    E8EB0_V v;
    E8EB0_S s;

    v = D_80088E20;
    func_15169260(&v, 2, 0, 0x1B);
    func_1516547C(0, D_800BEE0B, 0, 0xFF, 1);
    s.a = 1;
    s.b = func_150ADA20() % 21U + 20;
    s.d = 1;
    s.c = func_150ADA20() % 6U + 3;
    s.e = -1;
    func_151D8E18((structEU_151D8E18 *)&s, 0, 0xFF, 1);
    if (D_800DCDC4 != 0) {
        func_150E9000();
    }
    if (D_800DCDC4 != 0) {
        func_150E965C();
    }
    func_10010F30(0x4C8, 0x7FFF, 0x40, 0x200 - (func_150ADA20() & 0x400), 0);
    func_10010F30(0x4CD, 0x5DC0, 0x40, 0x200 - (func_150ADA20() & 0x400), 0);
}

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

s32 func_15133D30(u8 *);

typedef struct { s32 u0; s16 u4; u8 u6; u8 u7; s32 u8; s32 uC; u8 u10, u11, u12, u13, u14, u15, u16, u17; s32 u18; s32 u1C; s16 u20; s16 u22; s16 u24; s16 u26; } E9_S;
s32 func_150E9C9C(u8 *arg0) {
    u8 *p;
    E9_S s;
    f32 f;

    func_15133D30(arg0);
    p = arg0 + 0x170;
    if (*(f32 *)(arg0 + 0x3C) < *(f32 *)(arg0 + 0x170)) {
        if ((*(s32 *)(p + 4) & 0x1F) == 0xA) {
            f = func_150ADA68() * 20.0f + 20.0f;
            s.u6 = 0xB;
            s.u0 = 0x9701;
            s.u4 = 0x64;
            s.u7 = 0;
            s.u8 = 0;
            s.uC = 0;
            s.u10 = 0xFF;
            s.u11 = 0xFF;
            s.u12 = 0xFF;
            s.u13 = 0xFF;
            s.u14 = 0xFF;
            s.u15 = 0xFF;
            s.u18 = 0x3B0003;
            s.u16 = 0;
            s.u17 = 7;
            s.u22 = 0x14;
            s.u24 = 0xC;
            func_1513C73C((s32)&s, 0, 0, (s32)(p + 8), *(f32 *)(arg0 + 0x38), *(f32 *)p + 5.0f, *(f32 *)(arg0 + 0x40), f, f, func_150ADA20() & 0xFF, 0, 0, arg0[0xC], arg0[1]);
        }
        return 0;
    }
    return 1;
}
