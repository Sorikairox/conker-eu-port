#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_151436B4(f32, f32, f32, f32 *);
#endif

s32 memcpy(s32, f32 *, s32);


#ifdef NON_MATCHING
extern f32 D_800A16C8;
extern f32 D_800A16CC;
extern f32 D_800A16D0;
extern s32 D_80088DC0;
extern s32 D_80088DCC;
extern s32 D_80088DD4;
extern s32 D_800A1560;

void func_150E6E30(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    struct {
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        u8 pad54[0x8];
        f32 u5C;
        f32 u60;
        f32 u64;
        s32 u68;
        u8 pad6C[0x8];
        f32 u74;
        s16 u78;
        s16 u7A;
        u8 u7C;
        u8 pad7D[0x3];
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
    } sp;
    u8 *sp30;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f8;
    s8 temp_v1;
    s8 temp_v1_2;
    s8 temp_v1_3;
    struct260 *temp_v0;
    u8 *var_v0;

    if ((arg0 != 0) && ((D_800C35EA != 1) || (D_800C3A08 != 9))) {
        var_v0 = ((s32 *)((u8 *)&D_800A1560 + (arg3 * 0x10)));
        if ((func_150ADA68() < (*(f32 *)((u8 *)var_v0 + 0))) && ((*(s8 *)((u8 *)var_v0 + 4)) != -1)) {
            temp_v1 = (*(s8 *)((u8 *)var_v0 + 5));
            if (temp_v1 != -1) {
                sp30 = var_v0;
                (*(s32 (**)())((u8 *)&D_80088DCC + (temp_v1 * 4)))(&sp.u98, arg0, -1);
                var_v0 = sp30;
            } else {
                sp.u98 = 0.0f;
                sp.u9C = 0.0f;
                sp.uA0 = 0.0f;
            }
            temp_v1_2 = (*(s8 *)((u8 *)var_v0 + 4));
            if (temp_v1_2 != -1) {
                sp30 = var_v0;
                (*(s32 (**)())((u8 *)&D_80088DC0 + (temp_v1_2 * 4)))(&sp.u8C);
                var_v0 = sp30;
            } else {
                sp.u8C = 0.0f;
                sp.u90 = 0.0f;
                sp.u94 = 0.0f;
            }
            temp_f0 = sp.u98 - sp.u8C;
            sp.u80 = temp_f0;
            temp_f8 = sp.uA0 - sp.u94;
            sp.u84 = sp.u9C - sp.u90;
            sp.u88 = temp_f8;
            if ((temp_f0 != 0.0f) || (temp_f8 != 0.0f)) {
                temp_v1_3 = (*(s8 *)((u8 *)var_v0 + 6));
                if (temp_v1_3 != -1) {
                    sp30 = var_v0;
                    (*(s32 (**)())((u8 *)&D_80088DD4 + (temp_v1_3 * 4)))(0, &sp.u8C, &sp.u98, &sp.u80, &sp.u3C);
                    var_v0 = sp30;
                } else {
                    sp.u3C = 0.0f;
                    sp.u44 = 0.0f;
                    sp.u4C = 0.0f;
                    sp.u40 = 0.0f;
                    sp.u48 = 0.0f;
                    sp.u50 = 0.0f;
                }
                sp30 = var_v0;
                temp_f16 = func_150ADA68() * D_800A16C8;
                sp.u64 = 0.0f;
                sp.u60 = temp_f16 + D_800A16CC;
                (*(f32 *)((u8 *)(&sp.u68) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u8C) + 0));
                (*(s32 *)((u8 *)(&sp.u68) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u8C) + 4));
                (*(s32 *)((u8 *)(&sp.u68) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u8C) + 8));
                sp.u5C = 0.0f;
                sp.u74 = ((func_150ADA68() * 100.0f) + 150.0f) * D_800A16D0;
                sp.u78 = (*(s16 *)((u8 *)var_v0 + 8));
                sp.u7A = (*(s16 *)((u8 *)var_v0 + 0xA));
                sp.u7C = (*(u8 *)((u8 *)var_v0 + 0xC));
                temp_v0 = func_151491F4((s16) (s32) ((func_150ADA68() * 70.0f) + 30.0f), -1, 0xF, 1U, 0xBU, 0x44, 0xFFU, 1);
                if (temp_v0 != NULL) {
                    memcpy(((struct260 *)((u8 *)temp_v0 + 0x28)), &sp.u3C, 0x44);
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E6E30.s")
#endif
#ifdef NON_MATCHING
s32 func_150E6550(u8 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32); /* P98: asm mtc1 a2 */
f32 func_15144528(f32, f32, f32);

void func_150E7104(u8 *arg0) {
    struct {
        f32 uB4;
        u8 padB8[0x20];
        f32 uD8;
        f32 uDC;
    } sp;
    f32 sp8C;
    f32 sp88;
    f32 temp_f16;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f2;
    f32 var_f24;
    f32 var_f26;
    s32 temp_s1;
    u8 *temp_s0;

    temp_s0 = arg0 + 0x28;
    (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x50)) + ((*(f32 *)((u8 *)arg0 + 0x4C)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x50)) > 1.0f) {
        temp_f2 = 1.0f / (*(f32 *)((u8 *)temp_s0 + 0x28));
        temp_f16 = (*(f32 *)((u8 *)temp_s0 + 0x20)) + D_800BE9A4;
        sp.uD8 = temp_f16 * temp_f2;
        var_f24 = (*(f32 *)((u8 *)temp_s0 + 0x10));
        var_f26 = (*(f32 *)((u8 *)temp_s0 + 0x14));
        sp.uDC = temp_f16;
        sp8C = (*(f32 *)((u8 *)temp_s0 + 0x18)) * D_800BE9A4 * temp_f2;
        sp88 = (*(f32 *)((u8 *)temp_s0 + 0x1C)) * D_800BE9A4 * temp_f2;
        do {
            temp_f20 = sinf(var_f24);
            func_151436B4((*(f32 *)((u8 *)temp_s0 + 0)) + (temp_f20 * (*(f32 *)((u8 *)temp_s0 + 8))), (*(f32 *)((u8 *)temp_s0 + 4)) + (sinf(var_f26) * (*(f32 *)((u8 *)temp_s0 + 0xC))), 5.0f, &sp.uB4);
            temp_f20_2 = func_150ADA68();
            temp_f22 = func_150ADA68();
            temp_s1 = func_150ADA20();
            func_150E6550(temp_s0 + 0x2C, &sp.uB4, (*(f32 *)((u8 *)temp_s0 + 0x38)), ((temp_f20_2 * 300.0f) + 100.0f) * 0.1f, ((temp_f22 * 700.0f) + 300.0f) * 0.1f, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)), (s32) (*(u8 *)((u8 *)temp_s0 + 0x40)), ((u32) temp_s1 % 86U) + 0xAA, (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x3E)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x3C)), -1);
            var_f24 += sp8C;
            var_f26 += sp88;
            sp.uDC -= sp.uD8;
            (*(f32 *)((u8 *)temp_s0 + 0x28)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x28)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x28)) > 1.0f);
        (*(f32 *)((u8 *)temp_s0 + 0x10)) = func_15144528(var_f24, 6.2831855f, 0);
        (*(f32 *)((u8 *)temp_s0 + 0x14)) = func_15144528(var_f26, 6.2831855f, 0);
        (*(f32 *)((u8 *)temp_s0 + 0x20)) = sp.uDC;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E7104.s")
#endif
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

void func_150E752C(f32 *out, u8 *obj)
{
  struct_eu_link *m;
  f32 c;
  f32 r;
  u16 ang;
  if (func_1514F250(*((struct_eu_link **) (obj + 0x2F4)), 0x16, &m) != 0)
  {
    f32 s;
    u8 *p;
    r = (func_150ADA68() * 100.0f) + 80.0f;
    ang = (unsigned char) (func_150ADA20() & 0xFF);
    s = func_151423D8(ang - 0x40);
    c = func_151423D8(ang);
    p = *((u8 **) (((u8 *) m) + 0x10));
    out[0] = (((*((f32 *) (p + 0x38))) * (-80.0f)) + (*((f32 *) (obj + 0x14)))) + (s * r);
    out[1] = (((*((f32 *) (p + 0x3C))) * (-80.0f)) + (*((f32 *) (obj + 0x18)))) + 100.0f;
    out[2] = (((*((f32 *) (p + 0x40))) * (-80.0f)) + (*((f32 *) (obj + 0x1C)))) + (c * r);
  }
  else
  {
    out[0] = *((f32 *) (obj + 0x14));
    out[1] = *((f32 *) (obj + 0x18));
    out[2] = *((f32 *) (obj + 0x1C));
  }
}

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

#ifdef NON_MATCHING
void func_150E821C(u8 *arg0) {
    struct {
        f32 u98;
        f32 u9C;
    } sp;
    f32 temp_f20;
    s32 var_s1;
    s32 var_s2;
    u8 *temp_s0;

    temp_s0 = arg0 + 0x28;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x2C)) + ((*(f32 *)((u8 *)arg0 + 0x28)) * D_800BE9A4));
    if (((*(f32 *)((u8 *)arg0 + 0x2C)) > 1.0f) && ((*(s16 *)((u8 *)temp_s0 + 8)) != (*(s16 *)((u8 *)temp_s0 + 0xA)))) {
loop_3:
        sp.u98 = (*(f32 *)((u8 *)((temp_s0 + ((*(s16 *)((u8 *)temp_s0 + 0xA)) * 8))) + 0x10));
        sp.u9C = (*(f32 *)((u8 *)((temp_s0 + ((*(s16 *)((u8 *)temp_s0 + 0xA)) * 8))) + 0x14));
        temp_f20 = func_150ADA68();
        var_s2 = 0;
        if (func_150ADA20() & 1) {
            var_s2 = 4;
        }
        var_s1 = 0;
        if (func_150ADA20() & 1) {
            var_s1 = 2;
        }
        func_150E7B20(&sp.u98, (temp_f20 * 12.0f) + 30.0f, 0x12C, (var_s1 | var_s2) & 0xFF, (u8) (u32) ((func_150ADA68() * 25.0f) + 100.0f), 0xFFU, 1, 0xFF, 0, 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        func_10010F30(0x360, 0x7FFFU, (u32) ((sp.u98 * 0.43150684f) + 64.0f) & 0xFF, 0, 0U);
        (*(s16 *)((u8 *)temp_s0 + 0xA)) = (s16) ((*(s16 *)((u8 *)temp_s0 + 0xA)) + 1);
        (*(f32 *)((u8 *)temp_s0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 4)) - 1.0f);
        if (((*(f32 *)((u8 *)temp_s0 + 4)) > 1.0f) && ((*(s16 *)((u8 *)temp_s0 + 8)) != (*(s16 *)((u8 *)temp_s0 + 0xA)))) {
            goto loop_3;
        }
    }
    if ((*(s16 *)((u8 *)temp_s0 + 0xA)) >= (*(s16 *)((u8 *)temp_s0 + 8))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E821C.s")
#endif
#ifdef NON_MATCHING
void func_150E856C(f32 arg0, u8 arg1, s32 arg2, u8 *arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, s32 argB) {
    struct {
        s32 u5C;
        s16 u60;
        s8 u62;
        s8 u63;
        s32 u64;
        s32 u68;
        u8 u6C;
        s8 u6D;
        u8 u6E;
        u8 u6F;
        u8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        s32 u74;
        u8 pad78[0x6];
        s16 u7E;
        s16 u80;
    } sp;
    s32 sp58;
    s32 sp54;
    s32 sp4C;
    s32 sp48;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    sp.u7E = 0x14;
    sp.u80 = 0xC;
    sp.u62 = 0x4F;
    sp.u63 = 0;
    if (arg4 == -1) {
        var_v1 = 0;
    } else {
        var_v1 = 1;
    }
    var_v0 = 0;
    if (arg5 != 0) {
        var_v0 = 0x400;
    }
    sp.u5C = var_v0 | var_v1 | 0x9300 | 0x40000;
    if (arg4 == -1) {
        sp.u60 = 0x12C;
    } else {
        sp.u60 = arg4 + 0x14;
    }
    sp.u64 = 0;
    sp.u68 = 0;
    sp.u6D = 0xFF;
    sp.u71 = 0xFF;
    sp.u6C = arg1;
    sp.u6E = arg7;
    sp.u6F = arg8;
    sp.u70 = arg9;
    if (arg6 != 0) {
        var_v0_2 = 2;
    } else {
        var_v0_2 = 1;
    }
    sp.u74 = var_v0_2 + 0x480000;
    sp.u72 = 0;
    sp.u73 = 6;
    if (arg5 != 0) {
        sp58 = 3;
        sp54 = 0xFF;
    } else {
        sp58 = 0;
        sp54 = 0;
    }
    sp48 = func_150ADA20();
    sp4C = func_150ADA20();
    func_1513C650((s32) &sp.u5C, 0U, 0U, arg2, (*(f32 *)((u8 *)arg3 + 0)), (*(f32 *)((u8 *)arg3 + 4)), (*(f32 *)((u8 *)arg3 + 8)), arg0, arg0, (u8) (sp48 & 0xFF), (u8) (((func_150ADA20() & 1) * 2) + (sp4C & 1)), sp58, sp54, 0, (u8) (s32) argA, argB);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E856C.s")
#endif
#ifdef NON_MATCHING
void func_15150258(u8 *, u8, s32);
void func_151D45A4(u8 *, u8, s32);
extern s32 D_800A1660;

void func_150E8728(s32 arg0, u8 arg1, s32 arg2) {
    struct {
        s8 u20;
        u8 pad21[0x1];
        s16 u22;
        s8 u24;
        s8 u25;
        s8 u26;
        u8 pad27[0x1];
        s16 u28;
        s16 u2A;
        s16 u2C;
        s16 u2E;
        s32 u30;
        s32 u34;
        s32 u38;
        u8 pad3C[0x8];
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        s32 u5C;
        s32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        s16 u74;
        s16 u76;
        s16 u78;
        s16 u7A;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        f32 u88;
    } sp;
    s32 temp_a3;
    u8 *temp_t8;

    temp_a3 = arg0 & 0xFF;
    if ((temp_a3 == 4) || (temp_a3 == 5) || (temp_a3 == 6) || (temp_a3 == 7)) {
        temp_t8 = (temp_a3 * 0xC) + &D_800A1660;
        (*(s32 *)((u8 *)(&sp.u84) + 0)) = (s32) (*(s32 *)((u8 *)temp_t8 + 0));
        (*(s32 *)((u8 *)(&sp.u84) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
        (*(s32 *)((u8 *)(&sp.u84) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
        sp.u88 += 200.0f;
        func_151D45A4(&sp.u84, arg1, arg2);
        sp.u28 = 0;
        sp.u2A = 0xFF;
        sp.u2C = -0x40;
        sp.u2E = 0x4D;
        sp.u30 = 0xA;
        sp.u34 = 5;
        (*(s32 *)((u8 *)(&sp.u38) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 0));
        (*(s32 *)((u8 *)(&sp.u38) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 4));
        (*(s32 *)((u8 *)(&sp.u38) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u84) + 8));
        sp.u44 = 252.0f;
        sp.u48 = 117.0f;
        sp.u4C = 308.0f;
        sp.u50 = 256.0f;
        sp.u5C = 4;
        sp.u60 = 7;
        sp.u74 = 0x19;
        sp.u76 = 0xF;
        sp.u78 = 0x64;
        sp.u7A = 0x64;
        sp.u7C = 0xC;
        sp.u7E = 0x14;
        sp.u80 = 0;
        sp.u54 = 699.0f;
        sp.u58 = 511.0f;
        sp.u64 = 27.0f;
        sp.u68 = 0.78200006f;
        sp.u6C = -0.93000007f;
        sp.u70 = 0.73f;
        func_15150258(&sp.u28, arg1, arg2);
        sp.u20 = 1;
        sp.u22 = (func_150ADA20() % 11U) + 0x1E;
        sp.u24 = 8;
        sp.u26 = -1;
        sp.u25 = 1;
        func_151D8E18((structEU_151D8E18 *) &sp.u20, 0, 0xFFU, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E8728.s")
#endif
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

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

void func_150E89F0(u8 *arg0) {
    struct {
        s8 u90;
        s8 u91;
        s8 u92;
        s8 u93;
        f32 u94;
        f32 u98;
        s32 u9C;
        s32 uA0;
        s16 uA4;
        s16 uA6;
        s32 uA8;
        s32 uAC;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        u8 padF8[0x4];
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s8 u100;
        s8 u101;
    } sp;
    f32 temp_f18;
    f32 temp_f6;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((0.099999994f + (func_150ADA68() * 0.0879f)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        sp.uB9 = 0x6C;
        sp.uA4 = 0x5103;
        sp.u9C = 0x200005;
        sp.uBA = 0x73;
        sp.uBC = 2;
        sp.uF4 = 0x80DE07;
        sp.uFC = 8;
        sp.uFD = 6;
        sp.uFE = 0x19;
        sp.uFF = -1;
        sp.u90 = 0;
        sp.u91 = 0;
        sp.uA0 = 0;
        sp.uA8 = 0;
        sp.uAC = 0;
        sp.u100 = -1;
        sp.u101 = 0;
        sp.uBE = 0x73;
        sp.uB0 = 0x24;
        sp.uB1 = 0x22;
        sp.uB2 = 0x11;
        sp.uB3 = 0xFF;
        sp.uB4 = 0x7B;
        sp.uB5 = 0x93;
        sp.uB6 = 0xAA;
        sp.uB8 = 0xFF;
        sp.uC0 = 1.022418f;
        (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0));
        (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s1 + 4));
        (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s1 + 8));
        sp.uD8 = 0.0f;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        do {
            sp.u92 = (func_150ADA20() % 5U) + 4;
            sp.u93 = (func_150ADA20() % 5U) + 4;
            sp.u94 = func_150ADA68() * 13.0f;
            sp.u98 = func_150ADA68() * 13.0f;
            temp_f18 = func_150ADA68() * 40.0f;
            sp.uF4 &= ~0xC0;
            sp.uF0 = (temp_f18 + 68.0f) * 0.001f;
            var_s0 = 0;
            if (func_150ADA20() & 1) {
                var_s0 = 0x80;
            }
            if (func_150ADA20() & 1) {
                var_v0 = 0x40;
            } else {
                var_v0 = 0;
            }
            sp.uF4 |= var_v0 | var_s0;
            sp.uB7 = (func_150ADA20() % 156U) + 0x64;
            sp.uA6 = (func_150ADA20() % 34U) + 0x8D;
            temp_f6 = (func_150ADA68() * 71.0f) + 80.0f;
            sp.uC8 = temp_f6;
            sp.uC4 = temp_f6;
            temp_v0 = func_151307F0(&sp.u9C, 1, 0, 0xC, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, (f32 *) &sp.u90, 0xC);
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E89F0.s")
#endif
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

typedef struct E909C_N { s32 id; s32 pad; f32 w; struct E909C_N *next; } E909C_N;
typedef struct { f32 pos[3]; f32 v[3]; s32 pad[2]; } E909C_S;
extern s32 D_800BEE08;

void func_150E909C(u8 *arg0)
{
  f32 *cam;
  f32 r;
  E909C_S s;
  f32 *p;
  E909C_N *n;
  f32 dx;
  f32 dy;
  f32 dz;
  u8 *o;
  cam = func_15144B34(D_800BEE08);
  p = (f32 *) (arg0 + 0x28);
  p[2] += ((p[0] + (func_150ADA68() * p[1])) * D_800BE9A4) * D_800DCD90;
  while (p[2] > 1.0f)
  {
    r = func_150ADA68() * D_800DCD90;
    n = (E909C_N *) D_800DCDC4;
    while (n->w < r)
    {
      r -= n->w;
      n = n->next;
    }

    func_1514470C(n->id, s.pos);
    dx = s.pos[0] - cam[0];
    dy = s.pos[1] - cam[1];
    dz = s.pos[2] - cam[2];
    if ((((dx * dx) + (dy * dy)) + (dz * dz)) < 3240000.0f)
    {
      s.v[0] = 0.31712f;
      s.v[1] = 1.04651f;
      s.v[2] = 0.0f;
      o = (u8 *) func_15149130((func_150ADA20() % 13U) + 5, -1, 0x34, -1, 1, 0, 0x18, arg0[0xC], arg0[1]);
      if (o != 0)
      {
        memcpy((s32) (o + 0x28), (f32 *) (&s), 0x18);
      }
      goto dummy_label_122314; // fakematch: permuter label, fixes the s-reg order
      dummy_label_122314:
      ;
      ;
    }
    p[2] -= 1.0f;
  }

}

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

typedef struct E96F8_N { s32 id; s32 pad; f32 w; struct E96F8_N *next; } E96F8_N;
extern s32 D_800BEE08;
typedef struct { f32 pos[3]; f32 v[4]; u8 pad1C[0x14]; s32 u30; u8 u34; u8 u35; s32 u38; } E96F8_S;

void func_150E96F8(u8 *arg0)
{
  f32 *cam;
  f32 r;
  f32 *p;
  E96F8_N *n;
  E96F8_S s;
  f32 dx;
  f32 dy;
  f32 dz;
  u8 *o;
  cam = func_15144B34(D_800BEE08);
  p = (f32 *) (arg0 + 0x28);
  p[2] += ((p[0] + (func_150ADA68() * p[1])) * D_800BE9A4) * D_800DCD90;
  while (p[2] > 1.0f)
  {
    r = func_150ADA68() * D_800DCD90;
    n = (E96F8_N *) D_800DCDC4;
    while (n->w < r)
    {
      r -= n->w;
      n = n->next;
    }

    func_1514470C(n->id, s.pos);
    dx = s.pos[0] - cam[0];
    dy = s.pos[1] - cam[1];
    dz = s.pos[2] - cam[2];
    if ((((dx * dx) + (dy * dy)) + (dz * dz)) < 1960000.0f)
    {
      s.v[0] = 0.19324f;
      s.v[1] = 0.31401f;
      s.v[2] = 0.0f;
      s.v[3] = 99999.9f;
      s.u30 = 0;
      s.u34 = 0;
      s.u35 = 0;
      s.u38 = 0;
      o = (u8 *) func_15149130((func_150ADA20() % 13U) + 5, -1, 0x37, -1, 1, 0, 0x3C, arg0[0xC], arg0[1]);
      if (o != 0)
      {
        memcpy((s32) (o + 0x28), (f32 *) (&s), 0x3C);
      }
      goto dummy_label_122314; // fakematch: permuter label, fixes the s-reg order
      dummy_label_122314:
      ;
      ;
    }
    p[2] -= 1.0f;
  }

}

#ifdef NON_MATCHING
extern u8 D_800A16C0;
extern s32 D_800A16C4;

void func_150E995C(u8 *arg0) {
    struct {
        f32 u88;
        u8 pad8C[0x1C];
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        s32 uF8;
        s16 uFC;
        s16 uFE;
        s8 u100;
        u8 pad101[0x3];
        s32 u104;
        s8 u108;
        s8 u109;
        s8 u10A;
        s8 u10B;
        s8 u10C;
        s8 u10D;
        s8 u10E;
        s8 u10F;
        s8 u110;
        u8 pad111[0x1];
        s8 u112;
        u8 pad113[0x1];
        s32 u114;
        s8 u118;
        u8 pad119[0x1];
        s16 u11A;
        s16 u11C;
    } sp;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    s32 temp_v0;
    u8 *temp_s0;

    temp_s0 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s0 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x14)) + (((*(f32 *)((u8 *)temp_s0 + 0xC)) + (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x10)))) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s0 + 0x14)) > 1.0f) {
        sp.uA8 = 0.0f;
        sp.uAC = 1.0f;
        sp.uC4 = 1.0f;
        sp.uC8 = 1.0f;
        sp.uCC = 1.0f;
        sp.uF8 = 0x49E8;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        sp.uE4 = 0.0f;
        sp.uEC = 0.0f;
        sp.u100 = 0;
        sp.u104 = 0;
        sp.u108 = 0xFF;
        sp.u10A = 0;
        sp.u10B = 0;
        sp.u10C = 0;
        sp.u10D = 0;
        sp.u10E = 0;
        sp.u10F = 0;
        sp.u110 = 2;
        sp.u112 = 2;
        sp.u114 = 0;
        sp.u118 = 0;
        sp.u11A = 1;
        sp.u11C = 0xFF;
        do {
            func_150ADA20();
            sp.uFE = (s16) D_800A16C0;
            temp_f2 = ((func_150ADA68() * 351.0f) + 400.0f) * *(s32 *)((u8 *)&D_800A16C4 + (0 * 4)) * 0.001f;
            sp.uB0 = temp_f2;
            sp.uB4 = temp_f2;
            sp.uB8 = func_150ADA68() * 360.0f;
            sp.uBC = func_150ADA68() * 360.0f;
            sp.uC0 = func_150ADA68() * 360.0f;
            sp.uF4 = ((func_150ADA68() * 423.0f) + -1401.0f) * 0.001f;
            func_150ADA20();
            sp.uFC = 0x64;
            sp.uE8 = ((func_150ADA68() * 27374.0f) + -13687.0f) * 0.001f;
            sp.uF0 = ((func_150ADA68() * 27374.0f) + -13687.0f) * 0.001f;
            temp_f20 = func_150ADA68();
            temp_f22 = func_150ADA68();
            func_151436B4(temp_f20 * 6.2831855f, temp_f22 * 6.2831855f, func_150ADA68() * 50.0f, &sp.uD0);
            sp.uD0 += (*(f32 *)((u8 *)temp_s0 + 0));
            sp.uD4 += (*(f32 *)((u8 *)temp_s0 + 4));
            sp.u109 = 8;
            sp.uD8 += (*(f32 *)((u8 *)temp_s0 + 8));
            temp_v0 = func_15132FBC(&sp.uA8, 3, 0xFF, 0x1C, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0x170, &sp.u88, 0x1C);
            }
            (*(f32 *)((u8 *)temp_s0 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x14)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_114640/func_150E995C.s")
#endif
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
