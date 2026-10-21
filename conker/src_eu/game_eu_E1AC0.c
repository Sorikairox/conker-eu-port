#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_150B5568(u8 *arg0);
#endif


s32 func_151482D4(s32, s32);

void func_150B42B0(void) {
    s8 sp24[4];

    func_151482D4(0, 5);
    sp24[0] = 0;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 2;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 4;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 1;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 3;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 5;
    func_151494E0((s32) sp24, 0x18U);
}

s32 func_1000FC18(u16, s16, s16, s16, s32);
void func_15147E64(u8 *);

void func_150B4354(u8 *arg0) {
    func_1000FC18(0x221, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), 0xFA0);
    func_15147E64(arg0);
}

s32 func_1000FC18(u16, s16, s16, s16, s32);
void func_15147E98(u8 *);

void func_150B43C8(u8 *arg0) {
    func_1000FC18(0x221, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), 0xFA0);
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
s32 memcpy(s32 *, s32 *, s32);

u8 *func_150B443C(s32 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s32 u44;
        u8 pad48[0x3C];
        f32 u84;
        f32 u88;
        s8 u8C;
        u8 pad8D[0x3];
        f32 u90;
        s8 u94;
        u8 pad95[0x3];
        f32 u98;
        s32 u9C;
        u8 padA0[0x8];
        s16 uA8;
        s16 uAA;
        s32 uAC;
        u8 padB0[0x1];
        s8 uB1;
    } sp;
    u8 *sp40;
    u8 *temp_v0;

    memcpy(&sp.u44, arg0, 0x40);
    sp.u8C = 0;
    sp.uAA = 2;
    sp.uA8 = 0x1F4;
    sp.u88 = 0.0f;
    sp.uB1 = (s8) arg2;
    sp.u94 = 0;
    sp.u98 = 0.0f;
    sp.u90 = (*(f32 *)((u8 *)arg0 + 0x14)) + (*(f32 *)((u8 *)arg0 + 0x18));
    sp.u84 = sp.u90;
    (*(f32 *)((u8 *)(&sp.u9C) + 0)) = (f32) (*(f32 *)((u8 *)arg1 + 0));
    (*(f32 *)((u8 *)(&sp.u9C) + 4)) = (f32) (*(f32 *)((u8 *)arg1 + 4));
    (*(f32 *)((u8 *)(&sp.u9C) + 8)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
    sp.uAC = 9;
    temp_v0 = func_15147FF0(&sp.u9C, 0x58, 0x24, 7, 7, 7, 0, 0, 0, 0xFFU, 1);
    sp40 = temp_v0;
    if (temp_v0 != NULL) {
        func_1000FA64(0x221U, (s16) (s32) (*(f32 *)((u8 *)arg1 + 0)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 4)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 8)), 0x61A8, 0xFA0U, 0x258, (s32) func_1000EF40, NULL, 0, 8, func_150ADA20() & 0x40);
        memcpy((*(s32 **)((u8 *)sp40 + 0x98)), &sp.u44, 0x58);
    }
    return sp40;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B443C.s")
#endif
typedef struct { f32 x, y, z; } V3s64;
s32 func_150B45C8(u8 *arg0) {
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_a3;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)temp_v0 + 0x1C)) & 1)) {
        return 0;
    }
    var_a2 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a2 -= 1;
            var_a1 = 0;
            if (var_a2 < 0) {
                var_a2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_a3 = (0, temp_v1) + (var_a2 * 0x24); // fakematch: comma flips addu operand order
            (*(s16 *)((u8 *)temp_a3 + 0x1C)) = 0xFF;
            (*(s16 *)((u8 *)temp_a3 + 0x1E)) = (s16) ((*(s16 *)((u8 *)temp_a3 + 0x1E)) - D_800BE9E4);
            if ((*(s16 *)((u8 *)temp_a3 + 0x1E)) < 0) {
                var_a1 = 1;
            }
            (*(f32 *)((u8 *)temp_a3 + 0x10)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0xC)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0x10)));
            (*(f32 *)((u8 *)temp_a3 + 0)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0xC)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0)));
            (*(f32 *)((u8 *)temp_a3 + 4)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0x10)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 4)));
            (*(f32 *)((u8 *)temp_a3 + 8)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0x14)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 8)));
            (*(f32 *)((u8 *)temp_a3 + 0x18)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0x28)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0x18)));
            if ((var_a1 != 0) && (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)))) {
                do {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                    if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                    }
                    (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
            }
        } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        *(V3s64 *)(arg0 + 0x54) = *(V3s64 *)(((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24) + (0, temp_v1)); // fakematch: comma flips addu operand order
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}

#ifdef NON_MATCHING
s32 func_150B4774(u8 *arg0) {
    struct {
        f32 u80;
        f32 u84;
        f32 u88;
    } sp;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 var_f20;
    f32 var_f22;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f6;
    s32 temp_s3;
    s8 temp_v0_5;
    u8 temp_a0;
    u8 temp_t4;
    u8 temp_t6;
    u8 temp_t8;
    u8 *temp_s2;
    u8 *temp_s5;
    u8 *temp_t9;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;

    temp_s2 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s3 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_a0 = (*(u8 *)((u8 *)temp_s2 + 0x50)) + ((func_150ADA20() % (u32) ((*(u8 *)((u8 *)temp_s2 + 0x10)) + 1)) * D_800BE9E4);
    (*(u8 *)((u8 *)temp_s2 + 0x50)) = temp_a0;
    (*(f32 *)((u8 *)temp_s2 + 0x4C)) = (f32) ((func_151423D8((temp_a0 - 0x40) & 0xFF) * (*(f32 *)((u8 *)temp_s2 + 0x18))) + (*(f32 *)((u8 *)temp_s2 + 0x14)));
    (*(f32 *)((u8 *)temp_s2 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0x44)) + ((*(f32 *)((u8 *)temp_s2 + 0x20)) * D_800BE9A4));
    temp_f16 = (*(f32 *)((u8 *)temp_s2 + 0x44));
    if (temp_f16 > 1.0f) {
        temp_f2 = 1.0f / temp_f16;
        var_f20 = D_800BE9A4;
        (*(f32 *)((u8 *)(&sp.u80) + 0)) = (*(f32 *)((u8 *)temp_s2 + 0));
        temp_s5 = arg0 + 0x10;
        (*(s32 *)((u8 *)(&sp.u80) + 4)) = (s32) (*(s32 *)((u8 *)temp_s2 + 4));
        (*(s32 *)((u8 *)(&sp.u80) + 8)) = (s32) (*(s32 *)((u8 *)temp_s2 + 8));
        var_f22 = (*(f32 *)((u8 *)temp_s2 + 0x40));
        temp_f26 = var_f20 * temp_f2;
        temp_f28 = ((*(f32 *)((u8 *)temp_s2 + 0x4C)) - var_f22) * temp_f2;
        do {
            (*(f32 *)((u8 *)temp_s2 + 0x54)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0x54)) + (*(f32 *)((u8 *)temp_s2 + 0x3C)));
            if ((*(f32 *)((u8 *)temp_s2 + 0x54)) > 1.0f) {
                func_150B5568(arg0);
            }
            temp_t9 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(s32 *)((u8 *)temp_t9 + 0)) = (s32) (*(s32 *)((u8 *)temp_s5 + 0));
            (*(s32 *)((u8 *)temp_t9 + 4)) = (s32) (*(s32 *)((u8 *)temp_s5 + 4));
            (*(s32 *)((u8 *)temp_t9 + 8)) = (s32) (*(s32 *)((u8 *)temp_s5 + 8));
            (*(f32 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0xC)) = (f32) (sp.u80 * var_f22);
            (*(f32 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x10)) = (f32) (sp.u84 * var_f22);
            (*(f32 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x14)) = (f32) (sp.u88 * var_f22);
            (*(f32 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x18)) = (f32) (*(f32 *)((u8 *)temp_s2 + 0x2C));
            (*(s16 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x1C)) = 0xFF;
            (*(s16 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x1E)) = (s16) (*(s16 *)((u8 *)temp_s2 + 0x36));
            (*(u8 *)((u8 *)((temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24))) + 0x20)) = (u8) (*(u8 *)((u8 *)temp_s2 + 0x48));
            temp_f0 = func_150ADA68();
            temp_t4 = (*(u8 *)((u8 *)temp_s2 + 0x30));
            var_f6 = (f32) temp_t4;
            if ((s32) temp_t4 < 0) {
                var_f6 += 4294967296.0f;
            }
            temp_t6 = (*(u8 *)((u8 *)temp_s2 + 0x31));
            var_f4 = (f32) temp_t6;
            if ((s32) temp_t6 < 0) {
                var_f4 += 4294967296.0f;
            }
            temp_t8 = (*(u8 *)((u8 *)temp_s2 + 0x48));
            var_f4_2 = (f32) temp_t8;
            if ((s32) temp_t8 < 0) {
                var_f4_2 += 4294967296.0f;
            }
            (*(u8 *)((u8 *)temp_s2 + 0x48)) = (u8) (u32) (var_f4_2 + (var_f6 + (temp_f0 * var_f4)));
            temp_v0 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x10)) + ((*(f32 *)((u8 *)temp_s2 + 0xC)) * var_f20));
            temp_v0_2 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(f32 *)((u8 *)temp_v0_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0)) + ((*(f32 *)((u8 *)temp_v0_2 + 0xC)) * var_f20));
            temp_v0_3 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(f32 *)((u8 *)temp_v0_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0_3 + 4)) + ((*(f32 *)((u8 *)temp_v0_3 + 0x10)) * var_f20));
            temp_v0_4 = temp_s3 + ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24);
            (*(f32 *)((u8 *)temp_v0_4 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0_4 + 8)) + ((*(f32 *)((u8 *)temp_v0_4 + 0x14)) * var_f20));
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v0_5 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v0_5 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v0_5 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            var_f22 += temp_f28;
            var_f20 -= temp_f26;
            (*(f32 *)((u8 *)temp_s2 + 0x44)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 0x44)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s2 + 0x44)) > 1.0f);
        (*(f32 *)((u8 *)temp_s2 + 0x40)) = var_f22;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B4774.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B4BF0.s")

void func_150B5540(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);

    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= 0xFFFD;
    temp_v0[0x1C] |= 1;
}

#ifdef NON_MATCHING
s32 func_15148310(s32 *, f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32, s32, s32);
extern s32 D_8009FFC0;

void func_150B5568(u8 *arg0) {
    struct {
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        u8 padD4[0x4];
        s8 uD8;
        s8 uD9;
        u8 uDA;
        s8 uDB;
        u8 padDC[0x4];
        s32 uE0;
        u8 padE4[0x8];
        s16 uEC;
        s16 uEE;
        u8 padF0[0x5];
        s8 uF5;
        u8 padF6[0xA];
        s32 u100;
        s32 u104;
        s32 u108;
        s32 u10C;
        s32 u110;
        s32 u114;
        s32 u118;
        s8 u11C;
        s8 u11D;
    } sp;
    f32 spB4;
    f32 temp_f12;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f30;
    s32 temp_s1;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_s3;

    temp_s3 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s0 = ((s32 *)((u8 *)&D_8009FFC0 + ((*(u8 *)((u8 *)temp_s3 + 0x38)) * 0x24)));
    sp.u100 = 0;
    sp.u104 = 1;
    sp.u108 = 0x160600;
    sp.u10C = 3;
    sp.u110 = 0x10;
    sp.u114 = 0x80;
    sp.u118 = 0x20;
    sp.u11C = 0;
    sp.u11D = 9;
    sp.uEE = 1;
    sp.uD9 = 6;
    sp.uD8 = 8;
    sp.uDA = (*(u8 *)((u8 *)temp_s3 + 0x24));
    sp.uDB = (s8) (*(s16 *)((u8 *)temp_s3 + 0x26));
    (*(s32 *)((u8 *)(&sp.uE0) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0x10));
    (*(s32 *)((u8 *)(&sp.uE0) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x14));
    (*(s32 *)((u8 *)(&sp.uE0) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x18));
    do {
        temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 8))) + (*(f32 *)((u8 *)temp_s0 + 4));
        temp_s1 = func_150ADA20() & 0xFF;
        temp_s2 = func_150ADA20() & 0xFF;
        temp_f22 = func_151423D8((temp_s1 - 0x40) & 0xFF);
        temp_f24 = func_151423D8(temp_s1 & 0xFF);
        temp_f26 = func_151423D8((temp_s2 - 0x40) & 0xFF);
        temp_f2 = (*(f32 *)((u8 *)temp_s0 + 0));
        temp_f12 = temp_f2 * func_151423D8(temp_s2 & 0xFF);
        temp_f28 = (*(f32 *)((u8 *)temp_s3 + 0)) + (temp_f12 * temp_f22);
        temp_f30 = (*(f32 *)((u8 *)temp_s3 + 4)) - (temp_f2 * temp_f26);
        spB4 = (*(f32 *)((u8 *)temp_s3 + 8)) + (temp_f12 * temp_f24);
        sp.uF5 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x22)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x20));
        sp.uEC = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1E)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x1C));
        sp.uC0 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x10))) + (*(f32 *)((u8 *)temp_s0 + 0xC));
        temp_f18 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x18))) + (*(f32 *)((u8 *)temp_s0 + 0x14));
        sp.uC4 = temp_f20 * temp_f28;
        sp.uD0 = temp_f18;
        sp.uC8 = temp_f20 * temp_f30;
        sp.uCC = temp_f20 * spB4;
        func_15148310(&sp.uE0, &sp.uC0, 0, 1, 7, 0, 0, 0, 0, 0, 0, &sp.u100, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(f32 *)((u8 *)temp_s3 + 0x54)) = (f32) ((*(f32 *)((u8 *)temp_s3 + 0x54)) - 1.0f);
    } while ((*(f32 *)((u8 *)temp_s3 + 0x54)) > 1.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B5568.s")
#endif
void func_150B586C(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 5) {
        func_150B5540(arg0);
    }
}
