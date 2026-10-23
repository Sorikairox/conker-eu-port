#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
#endif


f32 func_15144A74(u8 *, u8 *);
s32 func_15144E80(u8 *, u8 *, u8 *, u8 *);

void func_1514FBB0(u8 *arg0, u8 *arg1) {
    arg1[0] = 2;
    *(f32 *)(arg1 + 0x28) = *(f32 *)(arg0 + 0x20);
    if ((func_15144E80(arg0 + 0xC, arg1 + 0x10, arg1 + 0x1C, arg1 + 4) != 0) && (func_15144A74(arg1 + 4, arg0) < 0.0f)) {
        *(f32 *)(arg1 + 4) = -*(f32 *)(arg1 + 4);
        *(f32 *)(arg1 + 8) = -*(f32 *)(arg1 + 8);
        *(f32 *)(arg1 + 0xC) = -*(f32 *)(arg1 + 0xC);
    }
}

s32 func_15145128(u8 *, u8 *, void *, void *);
s32 func_15146078(u8 *, s32 *, s32 *);
s32 func_1514FC58(u8 *arg0) {
    s32 f;
    f = arg0[0];
    if (!(f & 1)) {
        if (func_15145128(arg0 + 4, arg0 + 4, 0, 0) == 0) {
            return 0;
        }
        *(f32 *)(arg0 + 4) *= 1000.0f;
        f = arg0[0] |= 1;
        *(f32 *)(arg0 + 8) *= 1000.0f;
        *(f32 *)(arg0 + 0xC) *= 1000.0f;
    }
    if (!(f & 2)) {
        if (func_15146078(arg0 + 4, (s32 *)(arg0 + 0x10), (s32 *)(arg0 + 0x1C)) == 0) {
            return 0;
        }
        f = arg0[0] |= 6;
    }
    if (!(f & 4)) {
        if (func_15145128(arg0 + 0x10, arg0 + 0x10, 0, 0) == 0) {
            return 0;
        }
        if (func_15145128(arg0 + 0x1C, arg0 + 0x1C, 0, 0) == 0) {
            return 0;
        }
        arg0[0] |= 4;
    }
    return 1;
}

s32 func_15143874(s16, f32, f32 *, f32 *);

f32 *func_1514FD78(f32 *arg0, f32 arg1, f32 *arg2) {
    f32 s;
    f32 c;

    func_15143874(func_150ADA20() & 0xFF, arg0[10] * func_150ADA68(), &c, &s);
    arg2[0] = (arg0[1] + (arg0[7] * s + arg0[4] * c)) * arg1;
    arg2[1] = (arg0[2] + (arg0[8] * s + arg0[5] * c)) * arg1;
    arg2[2] = (arg0[3] + (arg0[9] * s + arg0[6] * c)) * arg1;
    return arg2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1514FE68.s")

s32 func_15146078(u8 *, s32 *, s32 *);
s32 func_1514FE68(u8 *, u8 *, s32 *, s32 *, f32, s32, s32);
void func_15150108(u8 *arg0, u8 arg1, s32 arg2) {
    s32 sp34[3];
    s32 sp28[3];
    if (func_15146078(arg0, sp34, sp28) != 0) {
        func_1514FE68(arg0 + 0x10, arg0, sp34, sp28, (*(f32 *)((u8 *)arg0 + 0xC)), (s32) arg1, arg2);
    }
}

s32 func_15145128(u8 *, u8 *, void *, void *);
void func_1515016C(u8 *arg0, u8 arg1, s32 arg2) {
    f32 a[3];
    s32 a1;
    s32 a2;
    f32 b[3];
    s32 b1;
    s32 b2;
    f32 c[3];
    s32 c1;
    s32 c2;
    if (func_15144E80(arg0 + 0xC, (u8 *)a, (u8 *)b, (u8 *)c) != 0) {
        func_15145128((u8 *)a, (u8 *)a, &a1, &a2);
        func_15145128((u8 *)b, (u8 *)b, &b1, &b2);
        func_15145128((u8 *)c, (u8 *)c, &c1, &c2);
        if (func_15144A74((u8 *)c, arg0) < 0.0f) {
            c[0] = -c[0];
            c[1] = -c[1];
            c[2] = -c[2];
        }
        func_1514FE68(arg0 + 0x24, (u8 *)c, (s32 *)a, (s32 *)b, *(f32 *)(arg0 + 0x20), arg1, arg2);
    }
}

s32 func_151A2FC4(u8 *, s16, s16, f32, f32, f32, s32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
void func_15150258(u8 *arg0, u8 arg1, s32 arg2) {
    s32 n;
    n = *(s32 *)(arg0 + 8) + (func_150ADA20() % (u32)(*(s32 *)(arg0 + 0xC) + 1));
    while (n != 0) {
        func_151A2FC4(arg0 + 0x10,
            *(s16 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 2) + 1)),
            *(s16 *)(arg0 + 4) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 6) + 1)),
            *(f32 *)(arg0 + 0x1C) + *(f32 *)(arg0 + 0x20) * func_150ADA68(),
            *(f32 *)(arg0 + 0x24) + *(f32 *)(arg0 + 0x28) * func_150ADA68(),
            *(f32 *)(arg0 + 0x2C) + *(f32 *)(arg0 + 0x30) * func_150ADA68(),
            *(s32 *)(arg0 + 0x34) + (func_150ADA20() % (u32)(*(s32 *)(arg0 + 0x38) + 1)),
            *(f32 *)(arg0 + 0x3C), *(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0x44), *(f32 *)(arg0 + 0x48),
            *(s16 *)(arg0 + 0x4C), *(s16 *)(arg0 + 0x4E), *(s16 *)(arg0 + 0x50), *(s16 *)(arg0 + 0x52),
            *(s16 *)(arg0 + 0x54), *(s16 *)(arg0 + 0x56), *(s8 *)(arg0 + 0x58), arg1, arg2);
        n--;
    }
}

void func_1514FBB0();
void func_151504B4();

void func_1515046C(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    func_1514FBB0(arg0, sp24);
    func_151504B4(sp24, arg1, arg2, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151504B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151506E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15150970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15150D7C.s")

void func_15143794(s16, s16, f32, void *);
#ifdef NON_MATCHING
/* P59: arg 2 (z) is f32 in the definition (src_eu/nm_asm/D5E90.c); wasm needs the exact signature. */
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
#define RAY_Z0(p) (*(f32 *)(p))
#else
s32 func_150ACEA0(f32, f32, s32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
#define RAY_Z0(p) (*(s32 *)(p))
#endif
s32 func_15145C90(s32);

void func_1515128C(u8 *arg0, u8 arg1, s32 arg2) {
    s32 n;
    f32 spC0[3];
    u8 spAC[0x14];
    f32 spA0[3];
    f32 sp9C;
    s32 sp98;
    u8 *hit;

    n = *(s32 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s32 *)(arg0 + 4) + 1));
    while (n != 0) {
        func_15143794(*(s16 *)(arg0 + 0x14) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1)),
            *(s16 *)(arg0 + 0x18) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1A) + 1)), 100.0f, spC0);
        hit = spAC; // fakematch: named pointer to spAC (permuter), both calls use it
        if (func_150ACEA0(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0xC), RAY_Z0(arg0 + 0x10), spC0[0], spC0[1], spC0[2], 0,
                hit, &spA0[0], &spA0[1], &spA0[2], &sp9C, &sp98, 0, 0.0f) != 0) {
            if (func_15145C90(sp98) != 0) {
                if (sp9C < *(f32 *)(arg0 + 0x1C)) {
                    func_151D9B8C(*(u8 *)(arg0 + 0x2C), *(f32 *)(arg0 + 0x20) + *(f32 *)(arg0 + 0x24) * func_150ADA68(),
                        (func_150ADA20() % 156U) + 100, (s32)hit, (struct17 *)spA0,
                        *(s16 *)(arg0 + 0x28) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x2A) + 1)),
                        1, 1, 1, arg1, arg2);
                }
            }
        }
        n--;
    }
}

void func_15143794(s16, s16, f32, void *);
s32 func_1518A930(u8 *, f32 *, f32, f32 *, f32 *, f32, f32, u8, s32, u8, s32, u8, s32);

void func_15151500(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    f32 spBC[3];
    f32 d;
    s32 n;
    f32 spA8[3];
    f32 sp9C[3];

    d = 2.0f * *(f32 *)(arg0 + 0x2C);
    spBC[1] = 0.0f;
    n = func_150ADA20();
    n = *(s32 *)(arg0 + 0) + (n % (u32)(*(s32 *)(arg0 + 4) + 1));
    while (n != 0) {
        spA8[0] = func_150ADA68() * 360.0f;
        spA8[1] = func_150ADA68() * 360.0f;
        spA8[2] = func_150ADA68() * 360.0f;
        func_15143794(*(s16 *)(arg0 + 0x1C) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1E) + 1)),
            *(s16 *)(arg0 + 0x20) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x22) + 1)),
            *(f32 *)(arg0 + 0x24) + *(f32 *)(arg0 + 0x28) * func_150ADA68(), sp9C);
        spBC[0] = func_150ADA68() * d - *(f32 *)(arg0 + 0x2C);
        spBC[2] = func_150ADA68() * d - *(f32 *)(arg0 + 0x2C);
        func_1518A930(arg0 + 8, spA8, *(f32 *)(arg0 + 0x14) + *(f32 *)(arg0 + 0x18) * func_150ADA68(), sp9C, spBC,
            *(f32 *)(arg0 + 0x30) + *(f32 *)(arg0 + 0x34) * func_150ADA68(), *(f32 *)(arg0 + 0x38),
            *(u8 *)(arg0 + 0x3C), *(s16 *)(arg0 + 0x3E) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x40) + 1)),
            arg1, 0, arg2, arg3);
        n--;
    }
}

#ifdef NON_MATCHING
s32 memcpy(s32, f32 *, s32);

void func_1515176C(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 u84;
        f32 u88;
        u8 pad8C[0x4];
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        u8 uB0;
        u8 uB1;
        u16 uB2;
        s16 uB4;
        u8 padB6[0x2];
        s32 uB8;
        s32 uBC;
        s8 uC0;
        s8 uC1;
        s8 uC2;
        s8 uC3;
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
        s32 uF0;
        s8 uF4;
        s8 uF5;
        u8 uF6;
        u8 uF7;
        u8 padF8[0xC];
        s16 u104;
        s16 u106;
        s32 u108;
        s32 u10C;
        u8 u110;
        u8 pad111[0x3];
        f32 u114;
        f32 u118;
        s32 u11C;
        s32 u120;
        u8 u124;
        u8 pad125[0x3];
        s32 u128;
        s32 u12C;
        s32 u130;
        s32 u134;
        u8 u138;
        u8 pad139[0x3];
        s32 u13C;
        s32 u140;
    } sp;
    f32 temp_f16;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 var_s2;
    u8 *temp_v0;

    sp.u104 = (*(s16 *)((u8 *)arg0 + 0x68));
    sp.u106 = (*(s16 *)((u8 *)arg0 + 0x6A));
    sp.uB0 = (*(u8 *)((u8 *)arg0 + 0x34));
    sp.uB1 = (*(u8 *)((u8 *)arg0 + 0x35));
    sp.uB8 = 0;
    sp.uBC = 0;
    sp.uC0 = 0xFF;
    sp.uC1 = 0xFF;
    sp.uC2 = 0xFF;
    sp.uC3 = 0xFF;
    sp.uB2 = (*(u16 *)((u8 *)arg0 + 0x36));
    (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0xC));
    sp.uE4 = 1.0f;
    sp.uE8 = 1.0f;
    sp.uEC = 1.0f;
    sp.uF5 = 0xFF;
    sp.uF0 = (*(s32 *)((u8 *)arg0 + 0x44)) | 0x08000000;
    sp.uF6 = (*(u8 *)((u8 *)arg0 + 0x5C));
    sp.uF7 = (*(u8 *)((u8 *)arg0 + 0x5D));
    sp.uA0 = (*(f32 *)((u8 *)arg0 + 0x6C));
    if (func_15144E80(arg0 + 0x1C, &sp.u138, &sp.u124, &sp.u110) != 0) {
        func_15145128(&sp.u138, &sp.u138, &sp.u134, &sp.u130);
        func_15145128(&sp.u124, &sp.u124, &sp.u120, &sp.u11C);
        func_15145128(&sp.u110, &sp.u110, &sp.u10C, &sp.u108);
        if (func_15144A74(&sp.u110, arg0 + 0x10) < 0.0f) {
            sp.u110 = -(*(f32 *)&(sp.u110));
            sp.u114 = -sp.u114;
            sp.u118 = -sp.u118;
        }
        sp.uA8 = 0.0f;
        sp.u110 = (*(f32 *)&(sp.u110)) * 1000.0f;
        sp.u114 *= 1000.0f;
        sp.u118 *= 1000.0f;
        var_s2 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 2)) + 1)) + (*(s16 *)((u8 *)arg0 + 0));
        if (var_s2 != 0) {
            do {
                temp_s1 = func_150ADA20();
                func_15143874((s16) (temp_s1 & 0xFF), func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x30)), &sp.u84, &sp.u88);
                temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x58))) + (*(f32 *)((u8 *)arg0 + 0x54));
                sp.uB4 = (s16) (s32) ((func_150ADA68() * (f32) (*(s16 *)((u8 *)arg0 + 0x3A))) + (f32) (*(s16 *)((u8 *)arg0 + 0x38)));
                temp_f16 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x40))) + (*(f32 *)((u8 *)arg0 + 0x3C));
                sp.uC8 = temp_f16;
                sp.uC4 = temp_f16;
                sp.uD8 = func_150ADA68() * 360.0f;
                sp.uDC = func_150ADA68() * 360.0f;
                sp.uE0 = func_150ADA68() * 360.0f;
                sp.uF4 = (func_150ADA20() % (u32) ((*(u8 *)((u8 *)arg0 + 0x49)) + 1)) + (*(u8 *)((u8 *)arg0 + 0x48));
                sp.u90 = (((*(f32 *)&(sp.u138)) * sp.u84) + ((*(f32 *)&(sp.u124)) * sp.u88) + sp.u110) * temp_f20;
                sp.u94 = ((sp.u13C * sp.u84) + (sp.u128 * sp.u88) + sp.u114) * temp_f20;
                sp.u98 = ((sp.u140 * sp.u84) + (sp.u12C * sp.u88) + sp.u118) * temp_f20;
                sp.u9C = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x50))) + (*(f32 *)((u8 *)arg0 + 0x4C));
                temp_f20_2 = (*(f32 *)((u8 *)arg0 + 0x70));
                sp.uA4 = (func_150ADA68() * (2.0f * temp_f20_2)) - temp_f20_2;
                temp_f20_3 = (*(f32 *)((u8 *)arg0 + 0x70));
                sp.uAC = (func_150ADA68() * (2.0f * temp_f20_3)) - temp_f20_3;
                temp_s1_2 = func_150ADA20();
                temp_v0 = func_1513D2F0(&sp.uB0, (s32) ((u8 *)&D_800A4AA0), 0x19U, 0U, 0U, 0x17U, (u8) ((func_150ADA20() & 1) + ((temp_s1_2 & 1) * 2)), (*(s32 *)((u8 *)arg0 + 0x60)), (*(s32 *)((u8 *)arg0 + 0x64)), 0x20, (u8) (arg1 & 0xFF), arg2);
                if (temp_v0 != NULL) {
    s32 pad;
                    memcpy(temp_v0 + 0x110, &sp.u90, 0x20);
                }
                var_s2 -= 1;
            } while (var_s2 != 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515176C.s")
#endif
#ifdef NON_MATCHING
void func_15151BE0(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 u88;
        f32 u8C;
        u8 pad90[0x4];
        s32 u94;
        s32 u98;
        u8 u9C;
        u8 pad9D[0x3];
        f32 uA0;
        f32 uA4;
        s32 uA8;
        s32 uAC;
        u8 uB0;
        u8 padB1[0x3];
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        u8 uC4;
        u8 padC5[0x3];
        s32 uC8;
        s32 uCC;
        u8 padD0[0x4];
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        u8 padE8[0x4];
        u8 uEC;
        u8 uED;
        u8 uEE;
        s8 uEF;
        s16 uF0;
        s16 uF2;
        s32 uF4;
        u8 padF8[0x8];
        s16 u100;
        s16 u102;
        s32 u104;
        u8 pad108[0x1];
        s8 u109;
        u8 pad10A[0x2];
        s32 u10C;
    } sp;
    f32 temp_f20;
    s32 temp_s1;
    s32 var_s2;

    if (func_15144E80(arg0 + 0x18, &sp.uC4, &sp.uB0, &sp.u9C) != 0) {
        func_15145128(&sp.uC4, &sp.uC4, &sp.uC0, &sp.uBC);
        func_15145128(&sp.uB0, &sp.uB0, &sp.uAC, &sp.uA8);
        func_15145128(&sp.u9C, &sp.u9C, &sp.u98, &sp.u94);
        if (func_15144A74(&sp.u9C, arg0 + 0xC) < 0.0f) {
            sp.u9C = -(*(f32 *)&(sp.u9C));
            sp.uA0 = -sp.uA0;
            sp.uA4 = -sp.uA4;
        }
        sp.u104 = 1;
        sp.u9C = (*(f32 *)&(sp.u9C)) * 1000.0f;
        sp.uA0 *= 1000.0f;
        sp.uA4 *= 1000.0f;
        sp.u102 = (s16) (*(u8 *)((u8 *)arg0 + 0x55));
        sp.uED = (*(u8 *)((u8 *)arg0 + 0x54));
        sp.uEE = (*(u8 *)((u8 *)arg0 + 0x70));
        sp.uEC = (*(u8 *)((u8 *)arg0 + 0x56));
        sp.uF0 = (*(s16 *)((u8 *)arg0 + 0x9C));
        sp.uF2 = (*(s16 *)((u8 *)arg0 + 0x9E));
        (*(s32 *)((u8 *)(&sp.uF4) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
        (*(s32 *)((u8 *)(&sp.uF4) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
        (*(s32 *)((u8 *)(&sp.uF4) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
        sp.u10C = (*(s32 *)((u8 *)arg0 + 0xA0));
        var_s2 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x4A)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x48));
        if (var_s2 != 0) {
            do {
                temp_s1 = func_150ADA20();
                func_15143874((s16) (temp_s1 & 0xFF), func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x2C)), &sp.u88, &sp.u8C);
                temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x44))) + (*(f32 *)((u8 *)arg0 + 0x40));
                sp.uEF = (func_150ADA20() % (u32) ((*(u8 *)((u8 *)arg0 + 0x72)) + 1)) + (*(u8 *)((u8 *)arg0 + 0x71));
                sp.u109 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x4E)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x4C));
                sp.u100 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x52)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x50));
                sp.uD4 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x34))) + (*(f32 *)((u8 *)arg0 + 0x30));
                sp.uE4 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x3C))) + (*(f32 *)((u8 *)arg0 + 0x38));
                sp.uD8 = (((*(f32 *)&(sp.uC4)) * sp.u88) + ((*(f32 *)&(sp.uB0)) * sp.u8C) + sp.u9C) * temp_f20;
                sp.uDC = ((sp.uC8 * sp.u88) + (sp.uB4 * sp.u8C) + sp.uA0) * temp_f20;
                sp.uE0 = ((sp.uCC * sp.u88) + (sp.uB8 * sp.u8C) + sp.uA4) * temp_f20;
                func_15148310(&sp.uF4, &sp.uD4, 0, (*(s32 *)((u8 *)arg0 + 0x58)), (*(s32 *)((u8 *)arg0 + 0x5C)), (*(s32 *)((u8 *)arg0 + 0x60)), (*(s32 *)((u8 *)arg0 + 0x64)), (*(s32 *)((u8 *)arg0 + 0x68)), (*(s32 *)((u8 *)arg0 + 0x6C)), (*(s32 *)((u8 *)arg0 + 0x74)), (*(s32 *)((u8 *)arg0 + 0x78)), arg0 + 0x7C, 0, arg1 & 0xFF, arg2);
                var_s2 -= 1;
            } while (var_s2 != 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151BE0.s")
#endif
#ifdef NON_MATCHING
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);

void func_15151FA8(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        u8 padD0[0x4];
        u8 uD4;
        u8 uD5;
        u8 uD6;
        s8 uD7;
        s16 uD8;
        s16 uDA;
        s32 uDC;
        u8 padE0[0x8];
        s16 uE8;
        s16 uEA;
        s32 uEC;
        u8 padF0[0x1];
        s8 uF1;
        u8 padF2[0x2];
        s32 uF4;
    } sp;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    s16 temp_s1;
    s16 temp_s2;
    s32 var_s3;

    sp.uEC = 1;
    sp.uEA = (s16) (*(u8 *)((u8 *)arg0 + 0x39));
    sp.uD5 = (*(u8 *)((u8 *)arg0 + 0x38));
    sp.uD6 = (*(u8 *)((u8 *)arg0 + 0x54));
    sp.uD4 = (*(u8 *)((u8 *)arg0 + 0x3A));
    (*(s32 *)((u8 *)(&sp.uDC) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.uDC) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uDC) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.uD8 = (*(s16 *)((u8 *)arg0 + 0x80));
    sp.uDA = (*(s16 *)((u8 *)arg0 + 0x82));
    sp.uF4 = (*(s32 *)((u8 *)arg0 + 0x84));
    var_s3 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x26)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x24));
    if (var_s3 != 0) {
        do {
            temp_s1 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2A)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x28));
            temp_s2 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2E)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x2C));
            temp_f28 = func_151423D8(temp_s2 & 0xFF);
            temp_f22 = func_151423D8((temp_s2 - 0x40) & 0xFF);
            temp_f24 = func_151423D8(temp_s1 & 0xFF);
            temp_f26 = func_151423D8((temp_s1 - 0x40) & 0xFF);
            temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x20))) + (*(f32 *)((u8 *)arg0 + 0x1C));
            sp.uD7 = (func_150ADA20() % (u32) ((*(u8 *)((u8 *)arg0 + 0x56)) + 1)) + (*(u8 *)((u8 *)arg0 + 0x55));
            sp.uF1 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x32)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x30));
            sp.uE8 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x36)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x34));
            sp.uBC = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x10))) + (*(f32 *)((u8 *)arg0 + 0xC));
            temp_f2 = temp_f20 * temp_f28;
            sp.uCC = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x18))) + (*(f32 *)((u8 *)arg0 + 0x14));
            sp.uC0 = temp_f2 * temp_f26;
            sp.uC4 = -temp_f20 * temp_f22;
            sp.uC8 = temp_f2 * temp_f24;
            func_15148310(&sp.uDC, &sp.uBC, 0, (*(s32 *)((u8 *)arg0 + 0x3C)), (*(s32 *)((u8 *)arg0 + 0x40)), (*(s32 *)((u8 *)arg0 + 0x44)), (*(s32 *)((u8 *)arg0 + 0x48)), (*(s32 *)((u8 *)arg0 + 0x4C)), (*(s32 *)((u8 *)arg0 + 0x50)), (*(s32 *)((u8 *)arg0 + 0x58)), (*(s32 *)((u8 *)arg0 + 0x5C)), arg0 + 0x60, 0, arg1 & 0xFF, arg2);
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151FA8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151522DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152A90.s")

void func_15143794(s16, s16, f32, void *);
void func_150CD3C0(void *, u8, u8);
extern void (*D_8008B000[])(u8 *);
typedef struct { f32 v[3]; } V3_2de4;
typedef struct {
    V3_2de4 v;
    f32 p[3];
    f32 a;
    f32 b;
    u8 c[4];
    s32 n;
    f32 x;
    f32 y;
    f32 z;
} S_2de4;

void func_15152DE4(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused slot above the struct (frame size)
    S_2de4 sp;
    s32 n;
    s8 i;

    n = func_150ADA20();
    n = *(s32 *)(arg0 + 0) + (n % (u32)(*(s32 *)(arg0 + 4) + 1));
    sp.v = *(V3_2de4 *)(arg0 + 8);
    sp.a = *(f32 *)(arg0 + 0x24);
    sp.z = *(f32 *)(arg0 + 0x48);
    while (n != 0) {
        func_15143794(*(s16 *)(arg0 + 0x14) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1)),
            *(s16 *)(arg0 + 0x18) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1A) + 1)),
            *(f32 *)(arg0 + 0x1C) + *(f32 *)(arg0 + 0x20) * func_150ADA68(), sp.p);
        sp.b = *(f32 *)(arg0 + 0x28) + *(f32 *)(arg0 + 0x2C) * func_150ADA68();
        sp.n = *(s16 *)(arg0 + 0x32) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x34) + 1));
        sp.x = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x40) * func_150ADA68();
        sp.y = *(f32 *)(arg0 + 0x3C) + *(f32 *)(arg0 + 0x44) * func_150ADA68();
        i = *(s8 *)(arg0 + 0x30);
        if (i != 0xFFFFFFFF) { // unsigned compare: "!= -1" gives beq v0,fp (permuter found -1U)
            D_8008B000[i](sp.c);
        } else {
            sp.c[0] = 0xFF;
            sp.c[1] = 0xFF;
            sp.c[2] = 0xFF;
            sp.c[3] = 0xFF;
        }
        func_150CD3C0(&sp, arg1, (u8)arg2);
        n--;
    }
}

extern u8 D_800A63C0[][3];

void func_1515302C(u8 *arg0) {
    u8 i = func_150ADA20() % 5U;
    u8 *e = D_800A63C0[i];

    arg0[3] = func_150ADA20() % 101U + 0x9B;
    arg0[0] = e[0];
    arg0[1] = e[1];
    arg0[2] = e[2];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151530A8.s")

#ifdef NON_MATCHING
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);

void func_151534E0(u8 *arg0, s32 arg1) {
    struct {
        s32 uA8;
        s32 uAC;
        s32 uB0;
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s8 uC4;
        s8 uC5;
        u8 padC6[0x6];
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        u8 padE0[0x4];
        u8 uE4;
        u8 uE5;
        u8 uE6;
        u8 uE7;
        u8 padE8[0x4];
        s32 uEC;
        u8 padF0[0x8];
        s16 uF8;
        s16 uFA;
        s32 uFC;
        u8 pad100[0x1];
        s8 u101;
    } sp;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    s16 temp_s1;
    s16 temp_s2;
    s32 var_s3;

    sp.uFC = 1;
    sp.uFA = 1;
    sp.uE5 = (*(u8 *)((u8 *)arg0 + 0x38));
    sp.uE6 = (*(u8 *)((u8 *)arg0 + 0x54));
    sp.uE4 = (*(u8 *)((u8 *)arg0 + 0x39));
    sp.uE7 = (*(u8 *)((u8 *)arg0 + 0x55));
    (*(s32 *)((u8 *)(&sp.uEC) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.uEC) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.uEC) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.uA8 = 0;
    sp.uAC = 1;
    sp.uB0 = 0x160600;
    sp.uB4 = 3;
    sp.uB8 = 0x10;
    sp.uBC = 0x80;
    sp.uC0 = 0x20;
    sp.uC4 = 0;
    sp.uC5 = 9;
    var_s3 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x26)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x24));
    if (var_s3 != 0) {
        do {
            temp_s1 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2A)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x28));
            temp_s2 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2E)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x2C));
            temp_f22 = func_151423D8(temp_s2 & 0xFF);
            temp_f24 = func_151423D8((temp_s2 - 0x40) & 0xFF);
            temp_f26 = func_151423D8(temp_s1 & 0xFF);
            temp_f28 = func_151423D8((temp_s1 - 0x40) & 0xFF);
            temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x20))) + (*(f32 *)((u8 *)arg0 + 0x1C));
            sp.u101 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x32)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x30));
            sp.uF8 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x36)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x34));
            sp.uCC = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x10))) + (*(f32 *)((u8 *)arg0 + 0xC));
            temp_f2 = temp_f20 * temp_f22;
            sp.uDC = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x18))) + (*(f32 *)((u8 *)arg0 + 0x14));
            sp.uD0 = temp_f2 * temp_f28;
            sp.uD4 = -temp_f20 * temp_f24;
            sp.uD8 = temp_f2 * temp_f26;
            func_15148310(&sp.uEC, &sp.uCC, 0, (*(s32 *)((u8 *)arg0 + 0x3C)), (*(s32 *)((u8 *)arg0 + 0x40)), (*(s32 *)((u8 *)arg0 + 0x44)), (*(s32 *)((u8 *)arg0 + 0x48)), (*(s32 *)((u8 *)arg0 + 0x4C)), (*(s32 *)((u8 *)arg0 + 0x50)), 0, 0, &sp.uA8, 0, arg1 & 0xFF, 1);
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151534E0.s")
#endif
#ifdef NON_MATCHING
s32 func_15167D84(s32 *, s32, s32, s32, s32, s32);

void func_15153808(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u88;
        u8 pad8C[0x8];
        s16 u94;
        s16 u96;
        s16 u98;
        s16 u9A;
        s16 u9C;
        s16 u9E;
        s16 uA0;
        u8 padA2[0x2];
        s8 uA4;
        s8 uA5;
        s8 uA6;
        s8 uA7;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s8 uB2;
        u8 padB3[0x1];
        u8 uB4;
        u8 uB5;
        u8 uB6;
        u8 uB7;
        s8 uB8;
        s8 uB9;
        s8 uBA;
        u8 padBB[0x1];
        s16 uBC;
    } sp;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    s16 temp_s1;
    s16 temp_s2;
    s32 var_s3;

    sp.u98 = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0));
    sp.u9A = (s16) (s32) (*(f32 *)((u8 *)arg0 + 4));
    sp.u9C = (s16) (s32) (*(f32 *)((u8 *)arg0 + 8));
    sp.uA4 = (s8) (s32) ((*(f32 *)((u8 *)arg0 + 0)) * 256.0f);
    sp.uA5 = (s8) (s32) ((*(f32 *)((u8 *)arg0 + 4)) * 256.0f);
    sp.uA6 = (s8) (s32) ((*(f32 *)((u8 *)arg0 + 8)) * 256.0f);
    sp.uB4 = (*(u8 *)((u8 *)arg0 + 0x3C));
    sp.uB5 = (*(u8 *)((u8 *)arg0 + 0x3C));
    sp.uB8 = 0;
    sp.uB9 = 0;
    sp.uBA = 0;
    sp.uB6 = (*(u8 *)((u8 *)arg0 + 0x3C));
    sp.uB7 = (*(u8 *)((u8 *)arg0 + 0x3D));
    sp.uA7 = (*(s8 *)((u8 *)arg0 + 0x28));
    sp.u94 = 0;
    sp.uBC = (s16) (*(u8 *)((u8 *)arg0 + 0x29));
    sp.u96 = (*(s16 *)((u8 *)arg0 + 0x2E));
    sp.u88 = (*(s32 *)((u8 *)arg0 + 0x38));
    var_s3 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0xE)) + 1)) + (*(s16 *)((u8 *)arg0 + 0xC));
    if (var_s3 != 0) {
        do {
            temp_s1 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x12)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x10));
            temp_s2 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x16)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x14));
            temp_f28 = func_151423D8(temp_s2 & 0xFF);
            temp_f22 = func_151423D8((temp_s2 - 0x40) & 0xFF);
            temp_f24 = func_151423D8(temp_s1 & 0xFF);
            temp_f26 = func_151423D8((temp_s1 - 0x40) & 0xFF);
            temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x1C))) + (*(f32 *)((u8 *)arg0 + 0x18));
            temp_f0 = temp_f20 * temp_f28;
            sp.uB0 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x22)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x20));
            sp.u9E = (s16) (s32) (temp_f0 * temp_f26);
            sp.uA8 = (s16) (s32) (-temp_f20 * temp_f22);
            sp.uA0 = (s16) (s32) (temp_f0 * temp_f24);
            sp.uAA = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x26)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x24));
            sp.uB2 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x2C)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x2A));
            sp.uAC = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x32)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x30));
            sp.uAE = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x36)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x34));
            func_15167D84(&sp.u88, 0, 0, -1, arg1 & 0xFF, arg2);
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15153808.s")
#endif
#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 memcpy(s32, f32 *, s32);

void func_15153BA4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        f32 u8C;
        s32 u90;
        s32 u94;
        u16 u98;
        s16 u9A;
        s32 u9C;
        s32 uA0;
        u8 uA4;
        u8 uA5;
        u8 uA6;
        u8 uA7;
        u8 uA8;
        u8 uA9;
        u8 uAA;
        s8 uAB;
        u8 uAC;
        u8 uAD;
        s16 uAE;
        s16 uB0;
        s16 uB2;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        s32 uC0;
        u8 padC4[0x14];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        s32 uE8;
        u8 padEC[0x4];
        u8 uF0;
        u8 uF1;
        s8 uF2;
        s8 uF3;
        u8 padF4[0x2];
        s8 uF6;
    } sp;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f8;
    s16 temp_s1;
    s16 temp_s2;
    s32 temp_v0;
    s32 var_s3;
    u32 temp_hi;

    temp_hi = func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 2)) + 1);
    sp.u8C = (*(f32 *)((u8 *)arg0 + 0x68));
    sp.uAD = (*(u8 *)((u8 *)arg0 + 4));
    var_s3 = temp_hi + (*(s16 *)((u8 *)arg0 + 0));
    sp.u98 = (*(u16 *)((u8 *)arg0 + 6));
    sp.u94 = (*(s32 *)((u8 *)arg0 + 0xC));
    sp.u9C = 0;
    sp.u90 = (*(s32 *)((u8 *)arg0 + 8));
    sp.uA4 = (*(u8 *)((u8 *)arg0 + 0x1C));
    sp.uA5 = (*(u8 *)((u8 *)arg0 + 0x1D));
    sp.uA6 = (*(u8 *)((u8 *)arg0 + 0x1E));
    sp.uA7 = (*(u8 *)((u8 *)arg0 + 0x1F));
    sp.uA8 = (*(u8 *)((u8 *)arg0 + 0x20));
    sp.uA9 = (*(u8 *)((u8 *)arg0 + 0x21));
    sp.uAA = (*(u8 *)((u8 *)arg0 + 0x22));
    (*(s32 *)((u8 *)(&sp.uC0) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0x38));
    (*(s32 *)((u8 *)(&sp.uC0) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x3C));
    (*(s32 *)((u8 *)(&sp.uC0) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x40));
    sp.uE8 = (*(s32 *)((u8 *)arg0 + 0x5C));
    sp.uAC = (*(u8 *)((u8 *)arg0 + 0x25));
    sp.uF2 = (*(s8 *)((u8 *)arg0 + 0x60));
    sp.uF3 = (*(s8 *)((u8 *)arg0 + 0x61));
    sp.uAE = (*(s16 *)((u8 *)arg0 + 0x26));
    sp.uB0 = (*(s16 *)((u8 *)arg0 + 0x28));
    sp.uF0 = (*(u8 *)((u8 *)arg0 + 0x62));
    sp.uF1 = (*(u8 *)((u8 *)arg0 + 0x63));
    sp.uB2 = (*(s16 *)((u8 *)arg0 + 0x2A));
    sp.uF6 = arg1 & 0xFF;
    sp.uB4 = (*(f32 *)((u8 *)arg0 + 0x2C));
    if (var_s3 != 0) {
        do {
            temp_s1 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x48)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x44));
            temp_s2 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x4A)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x46));
            temp_f24 = func_151423D8(temp_s2 & 0xFF);
            temp_f26 = func_151423D8((temp_s2 - 0x40) & 0xFF);
            temp_f28 = func_151423D8(temp_s1 & 0xFF);
            temp_f22 = func_151423D8((temp_s1 - 0x40) & 0xFF);
            temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x50))) + (*(f32 *)((u8 *)arg0 + 0x4C));
            sp.u9A = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x12)) + 1)) + (*(s16 *)((u8 *)arg0 + 0x10));
            sp.uA0 = (func_150ADA20() % (u32) ((*(s32 *)((u8 *)arg0 + 0x18)) + 1)) + (*(s32 *)((u8 *)arg0 + 0x14));
            temp_f2 = temp_f20 * temp_f24;
            temp_f8 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x34))) + (*(f32 *)((u8 *)arg0 + 0x30));
            sp.uBC = temp_f8;
            sp.uB8 = temp_f8;
            sp.uD8 = temp_f2 * temp_f22;
            sp.uDC = -temp_f20 * temp_f26;
            sp.uE0 = temp_f2 * temp_f28;
            sp.uE4 = (func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x58))) + (*(f32 *)((u8 *)arg0 + 0x54));
            sp.uAB = (func_150ADA20() % (u32) ((*(u8 *)((u8 *)arg0 + 0x24)) + 1)) + (*(u8 *)((u8 *)arg0 + 0x23));
            temp_v0 = func_151307F0(&sp.u90, (*(u8 *)((u8 *)arg0 + 0x64)), 0, 4, arg2 & 0xFF, arg3);
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u8C, 4);
            }
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15153BA4.s")
#endif
typedef struct { f32 v[3]; } V3_3f24;
typedef struct {
    V3_3f24 pos;
    f32 vel[3];
    f32 a;
    f32 b;
    u8 c[9];
    s16 d;
    u16 e;
    f32 f;
    s8 g;
    s16 h;
    s16 i;
} S_3f24;
#ifdef NON_MATCHING
s32 func_15156700(S_3f24 *, u8, s32, u8, s32);
#else
void func_15156700(S_3f24 *, u8, s32, u8, s32);
#endif

void func_15153F24(u8 *arg0, u8 arg1) {
    S_3f24 sp;
    s32 n;
    s16 a;
    s16 b;
    f32 sb;
    f32 cb;
    f32 sa;
    f32 ca;

    n = *(s16 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 2) + 1));
    sp.pos = *(V3_3f24 *)(arg0 + 4);
    sp.c[0] = *(u8 *)(arg0 + 0x28);
    sp.c[1] = *(u8 *)(arg0 + 0x29);
    sp.c[2] = *(u8 *)(arg0 + 0x2A);
    sp.c[3] = *(u8 *)(arg0 + 0x2B);
    sp.c[4] = *(u8 *)(arg0 + 0x2C);
    sp.c[5] = *(u8 *)(arg0 + 0x2D);
    sp.c[6] = *(u8 *)(arg0 + 0x2E);
    sp.c[7] = *(u8 *)(arg0 + 0x2F);
    sp.c[8] = *(u8 *)(arg0 + 0x30);
    sp.e = *(u16 *)(arg0 + 0x36);
    sp.h = *(s16 *)(arg0 + 0x42);
    sp.i = *(s16 *)(arg0 + 0x44);
    while (n != 0) {
        a = *(s16 *)(arg0 + 0x10) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x14) + 1));
        b = *(s16 *)(arg0 + 0x12) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1));
        sb = func_151423D8(b);
        cb = func_151423D8(b - 0x40);
        sa = func_151423D8(a);
        ca = func_151423D8(a - 0x40);
        sp.vel[0] = 10.0f * sb * ca;
        sp.vel[1] = -10.0f * cb;
        sp.vel[2] = 10.0f * sb * sa;
        sp.a = *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * func_150ADA68();
        sp.b = *(f32 *)(arg0 + 0x20) + *(f32 *)(arg0 + 0x24) * func_150ADA68();
        sp.d = *(s16 *)(arg0 + 0x32) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x34) + 1));
        sp.f = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x3C) * func_150ADA68();
        sp.g = *(u8 *)(arg0 + 0x40) + (func_150ADA20() % (u32)(*(u8 *)(arg0 + 0x41) + 1));
        func_15156700(&sp, *(u8 *)(arg0 + 0x46), 0, arg1, 0);
        n--;
    }
}

void func_1515423C(u8 *, s32, s32, u8, s32);

void func_151541F4(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    func_1514FBB0(arg0, sp24);
    func_1515423C(sp24, arg1, arg2, arg3, arg4);
}

s32 func_151DA6F8(struct17 *, s32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_1515423C(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 n;
    f32 spA8[3];

    if (func_1514FC58(arg0) != 0) {
        n = func_150ADA20();
        n = *(s16 *)((u8 *)arg1 + 0x24) + (n % (u32)(*(s16 *)((u8 *)arg1 + 0x26) + 1));
        while (n != 0) {
            func_1514FD78((f32 *)arg0, *(f32 *)((u8 *)arg1 + 0x1C) + *(f32 *)((u8 *)arg1 + 0x20) * func_150ADA68(), spA8);
            func_151DA6F8((struct17 *)arg1, (s32 *)spA8,
                *(f32 *)((u8 *)arg1 + 0x14) + *(f32 *)((u8 *)arg1 + 0x18) * func_150ADA68(),
                *(s16 *)((u8 *)arg1 + 0x2C) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2E) + 1)),
                *(s16 *)((u8 *)arg1 + 0x30) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x32) + 1)),
                *(f32 *)((u8 *)arg1 + 0xC) + *(f32 *)((u8 *)arg1 + 0x10) * func_150ADA68(),
                *(s16 *)((u8 *)arg1 + 0x28) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2A) + 1)),
                func_150ADA68() < *(f32 *)((u8 *)arg1 + 0x38),
                1.7f, 1.7f, 1, *(u8 *)((u8 *)arg1 + 0x34), arg2,
                *(s16 *)((u8 *)arg1 + 0x3C), *(s16 *)((u8 *)arg1 + 0x3E), *(s32 *)((u8 *)arg1 + 0x40), arg3, arg4);
            n--;
        }
    }
}

void func_15143794(s16, s16, f32, void *);
s32 func_151DA6F8(struct17 *, s32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_15154488(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 n;
    s32 spA8[3];

    n = *(s16 *)((u8 *)arg1 + 0x24) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x26) + 1));
    while (n != 0) {
        func_15143794(arg0->unk0 + (func_150ADA20() % (u32)(arg0->unk2 + 1)),
            arg0->unk4 + (func_150ADA20() % (u32)(arg0->unk6 + 1)),
            *(f32 *)((u8 *)arg1 + 0x1C) + *(f32 *)((u8 *)arg1 + 0x20) * func_150ADA68(), spA8);
        func_151DA6F8(arg1, spA8,
            *(f32 *)((u8 *)arg1 + 0x14) + *(f32 *)((u8 *)arg1 + 0x18) * func_150ADA68(),
            *(s16 *)((u8 *)arg1 + 0x2C) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2E) + 1)),
            *(s16 *)((u8 *)arg1 + 0x30) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x32) + 1)),
            *(f32 *)((u8 *)arg1 + 0xC) + *(f32 *)((u8 *)arg1 + 0x10) * func_150ADA68(),
            *(s16 *)((u8 *)arg1 + 0x28) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2A) + 1)),
            func_150ADA68() < *(f32 *)((u8 *)arg1 + 0x38),
            1.7f, 1.7f, 1, *(u8 *)((u8 *)arg1 + 0x34), arg2,
            *(s16 *)((u8 *)arg1 + 0x3C), *(s16 *)((u8 *)arg1 + 0x3E), *(s32 *)((u8 *)arg1 + 0x40), arg3, arg4);
        n--;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154728.s")

s32 func_15154A9C(u8 *arg0) {
    f32 *p;
    f32 s;
    f32 t;
    p = (f32 *)(arg0 + 0x170);
    s = *(f32 *)(arg0 + 0x178) * sqrtf(p[0]);
    *(f32 *)(arg0 + 0x18) = s;
    if (!(*(u8 *)(arg0 + 0x184) & 1)) {
        *(f32 *)(arg0 + 0x1C) = s;
    }
    do { t = p[0]; *(s8 *)(arg0 + 0x70) = (s8)(u32)(p[3] - p[4] * t * t); } while (0); // fakematch: same-line do-while(0) (permuter) keeps &D_800BE9A4 in v1 from the start
    p[0] += D_800BE9A4;
    if (p[1] < p[0]) {
        return 0;
    }
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}

void func_15143794(s16, s16, f32, void *);
#ifdef NON_MATCHING
void func_151C64F4(s32, void *, f32, f32, s32, s32, f32, s32, s32, u8, s32);
#else
void func_151C64F4(s32, void *, f32, s32, s32, s32, f32, s32, s32, u8, s32);
#endif
void func_15154BF4(u8 *arg0, u8 arg1, s32 arg2) {
    s32 sp80[4];
    s32 n;
    n = *(s16 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 2) + 1));
    if (n > 0) {
        do {
            func_15143794(func_150ADA20() & 0xFF, *(s16 *)(arg0 + 0xA) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0xE) + 1)),
                *(f32 *)(arg0 + 0x10) + *(f32 *)(arg0 + 0x14) * func_150ADA68(), sp80);
#ifdef NON_MATCHING
            func_151C64F4(*(s32 *)(arg0 + 4), sp80, *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * func_150ADA68(),
                *(f32 *)(arg0 + 0x20),
                *(u8 *)(arg0 + 0x24) + (func_150ADA20() % (u32)(*(u8 *)(arg0 + 0x25) + 1)),
                *(s16 *)(arg0 + 0x26) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x28) + 1)),
                *(f32 *)(arg0 + 0x2C) + *(f32 *)(arg0 + 0x30) * func_150ADA68(),
                func_150ADA68() < *(f32 *)(arg0 + 0x34), *(s32 *)(arg0 + 0x38), arg1, arg2);
#else
            func_151C64F4(*(s32 *)(arg0 + 4), sp80, *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * func_150ADA68(),
                *(s32 *)(arg0 + 0x20),
                *(u8 *)(arg0 + 0x24) + (func_150ADA20() % (u32)(*(u8 *)(arg0 + 0x25) + 1)),
                *(s16 *)(arg0 + 0x26) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x28) + 1)),
                *(f32 *)(arg0 + 0x2C) + *(f32 *)(arg0 + 0x30) * func_150ADA68(),
                func_150ADA68() < *(f32 *)(arg0 + 0x34), *(s32 *)(arg0 + 0x38), arg1, arg2);
#endif
            n--;
        } while (n > 0);
    }
}

typedef struct { f32 x, y, z; } V3;

s32 func_15154DF4(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, s32 arg5)
{
  s32 obj;
  struct 
  {
    f32 u2C[15];
    s32 u68;
    u8 pad6C[0x8];
    f32 u74;
    f32 u78;
    f32 u7C;
    f32 u80;
    f32 u84;
    f32 u88;
    f32 u8C;
    s32 u90;
    s16 u94;
    s16 u96;
    s8 u98;
    u8 pad99[0x3];
    s32 u9C;
    u8 uA0;
    s8 uA1;
    s8 uA2;
    s8 uA3;
    s8 uA4;
    s8 uA5;
    s8 uA6;
    s8 uA7;
    s8 uA8;
    u8 padA9[0x1];
    s8 uAA;
    u8 padAB[0x1];
    s32 uAC;
    s8 uB0;
    u8 padB1[0x1];
    s16 uB2;
    s16 uB4;
    u8 padB6[0x6];
  } sp;
  f32 temp_f0;
  if (arg1 <= 0.0f)
  {
    return 0;
  }
  sp.u2C[0] = arg1;
  sp.u2C[1] = arg2;
  sp.u2C[3] = 0.0f;
  sp.u2C[7] = 0.0f;
  sp.u2C[8] = 0.0f;
  sp.u2C[5] = 1.0f;
  sp.u2C[6] = 1.0f;
  sp.u2C[2] = arg3;
  sp.u2C[4] = 3.1415927f / arg1;
  sp.u2C[9] = func_150ADA68() * 360.0f;
  sp.u2C[10] = func_150ADA68() * 360.0f;
  temp_f0 = func_150ADA68();
  sp.u2C[12] = 1.0f;
  sp.u2C[13] = 1.0f;
  sp.u2C[14] = 1.0f;
  sp.u2C[11] = temp_f0 * 360.0f;
  *((V3 *) (&sp.u68)) = *((V3 *) arg0);
  sp.u74 = 0.0f;
  sp.u78 = 0.0f;
  sp.u7C = 0.0f;
  temp_f0 = func_150ADA68();
  sp.u84 = 0.0f;
  sp.u80 = (temp_f0 * 26.296001f) + (-13.148001f);
  sp.u88 = (func_150ADA68() * 26.296001f) + (-13.148001f);
  sp.u8C = 0.0f;
  sp.u90 = 0x140;
  sp.u96 = 0x55;
  sp.u98 = 0;
  sp.u9C = 0;
  sp.uA0 = 0xFF;
  sp.uA1 = 0x12;
  sp.uA2 = 0;
  sp.uA3 = 0;
  sp.uA4 = 0;
  sp.uA5 = 0;
  sp.uA6 = 0;
  sp.uA7 = 0;
  sp.uA8 = 2;
  sp.uAA = 0;
  sp.uAC = 0;
  sp.uB0 = 0;
  sp.uB2 = 1;
  sp.uB4 = 0xFF;
  sp.u94 = 0x12C;
  obj = func_15132FBC((u8 *) (&sp.u2C[5]), 0, 0, 0x14, arg4, arg5);
  if (obj != 0)
  {
    memcpy(obj + 0x170, &sp, 0x14);
  }
  return obj;
}

s32 func_15154FF8(u8 *arg0) {
    f32 *p;
    f32 s;

    p = (f32 *)(arg0 + 0x170);
    s = sinf(p[3]);
    *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x1C) = p[1] * s;
    *(s8 *)(arg0 + 0x70) = (s8)(u32)(((u32)p[2] & 0xFF) * s);
    p[0] -= D_800BE9A4;
    if (p[0] <= 0.0f) {
        return 0;
    }
    p[3] += p[4] * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}
