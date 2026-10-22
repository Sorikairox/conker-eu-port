#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_150D513C(u8 *arg0);
extern u8 D_800A4EA8[];
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3870.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3F78.s")

#ifdef NON_MATCHING
f32 func_15143E64(s32);
s32 func_1515C668(s32, s32 *, u8 *);

s32 func_150D44E4(u8 *arg0) {
    struct {
        s32 u7C;
        f32 u80;
        f32 u84;
        s32 u88;
        s32 * u8C;
    } sp;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f12;
    f32 var_f24;
    f32 var_f26;
    f32 var_f2;
    s32 *temp_t6;
    s32 temp_a1;
    s32 var_a0;
    s32 var_t0;
    s8 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_t6 = (*(s32 **)((u8 *)arg0 + 0x98));
    sp.u8C = temp_t6;
    var_t0 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (D_800C35EA != 1) {
        sp.u88 = var_t0;
        var_t0 = sp.u88;
        if (func_1515C668(*temp_t6, &sp.u7C, arg0) != 0) {
            var_f2 = func_15143E64(sp.u7C);
        } else {
            var_f2 = 0.0f;
        }
    } else if (D_800DBFF0->unk5F0 & 4) {
        var_f2 = 0.0f;
    } else {
        var_f2 = 128.0f;
    }
    if (var_f2 < 10.0f) {
        var_f26 = 0.0f;
    } else if (var_f2 > 70.0f) {
        var_f26 = 600.0f;
    } else {
        var_f26 = (var_f2 - 10.0f) * 0.016666668f * 600.0f;
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_f24 = 0.0f;
        var_a0 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
        if (var_a0 < 0) {
            var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
        if (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
            do {
                temp_a1 = var_a0;
                var_a0 -= 1;
                if (var_a0 < 0) {
                    var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                temp_v1 = (temp_a1 * 0x14) + var_t0;
                temp_f16 = (*(f32 *)((u8 *)temp_v1 + 0xC));
                var_f24 += temp_f16;
                if (var_f26 < var_f24) {
                    if (temp_f16 != 0.0f) {
                        temp_f14 = (var_f24 - var_f26) / temp_f16;
                        temp_v0 = (var_a0 * 0x14) + var_t0;
                        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0));
                        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 4));
                        temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
                        (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) (temp_f0 - ((temp_f0 - (*(f32 *)((u8 *)temp_v1 + 0))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) (temp_f2 - ((temp_f2 - (*(f32 *)((u8 *)temp_v1 + 4))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) (temp_f12 - ((temp_f12 - (*(f32 *)((u8 *)temp_v1 + 8))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0xC)) * (1.0f - temp_f14));
                    }
                    var_f24 = var_f26;
                    if (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        do {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                                (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                            }
                            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                        } while (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                    }
                }
            } while (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
        if (var_f24 != 0.0f) {
            var_f12 = 1.0f / var_f24;
        } else {
            var_f12 = 0.0f;
        }
        sp.u80 = var_f12;
        sp.u84 = var_f24;
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_v0 = (*(s8 *)((u8 *)arg0 + 0x2E));
        var_f0 = sp.u84;
        do {
            var_v0 -= 1;
            if (var_v0 < 0) {
                var_v0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v1_2 = (var_v0 * 0x14) + var_t0;
            (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) (var_f0 * ((*(f32 *)((u8 *)sp.u8C + 0x14)) * sp.u80));
            var_f0 -= (*(f32 *)((u8 *)temp_v1_2 + 0xC));
        } while (var_v0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D44E4.s")
#endif
#ifdef NON_MATCHING
s32 func_1513F4E4(s32, s32, s8 *);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142C10(s32, s32, s32, s32, s32, s8 *);
s32 func_15142E24(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *func_15142FBC(s32, s32, s32, s8 *);
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_800914B0;
extern s32 D_800D30BC;

u8 *func_150D4810(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        u8 uD7;
        s16 * uD8;
        u8 padDC[0x4];
        f32 uE0;
        f32 uE4;
        u8 padE8[0x3];
        s8 uEB;
        f32 uEC;
        u8 padF0[0x28];
        f32 * u118;
        u8 pad11C[0x8];
        f32 u124;
        f32 u128;
        f32 u12C;
        f32 u130;
        f32 u134;
        f32 u138;
    } sp;
    f32 sp88;
    s32 *temp_v1_2;
    f32 *temp_v0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f6;
    f32 temp_f8_3;
    f32 var_f14;
    f32 var_f14_2;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f18;
    f32 var_f18_2;
    s16 *temp_t6;
    s16 *temp_t7;
    s16 *temp_t7_2;
    s16 *temp_t7_3;
    s32 temp_a0;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f10_3;
    s32 temp_f4;
    s32 temp_f4_2;
    s32 temp_f4_3;
    s32 temp_f6_2;
    s32 temp_f6_3;
    s32 temp_f6_4;
    s32 temp_f8;
    s32 temp_f8_2;
    s32 temp_f8_4;
    s32 temp_s2;
    s32 var_a0;
    s32 var_t1;
    s32 var_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_t8;
    u8 *temp_v0_2;
    u8 *temp_v1;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *var_s0;
    u8 *var_v0;

    var_s0 = arg1;
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) {

    } else {
        temp_s2 = (*(s32 *)((u8 *)arg0 + 0x94));
        temp_v1 = *(*(u8 ***)((u8 *)arg0 + 0x98));
        if (((*(s32 *)((u8 *)temp_v1 + 0x1D4)) == 0) || (((*(u8 *)((u8 *)temp_v1 + 0x74)) & 0xF) == 0xF)) {

        } else {
            func_151D6310(arg0 + 0x84, arg2, ((*(u8 *)((u8 *)arg0 + 0x25)) * 0x30) + 0xF0, &sp.uD8, &sp.uD7);
            if (sp.uD7 != 0) {
                var_v0 = (*(u8 **)((u8 *)((arg0 + (arg2 * 4))) + 0x84));
                var_v1 = 0;
                if ((((*(u8 *)((u8 *)arg0 + 0x25)) * 2) + 0xA) > 0) {
                    do {
                        (*(s16 *)((u8 *)var_v0 + 8)) = 5;
                        (*(s16 *)((u8 *)var_v0 + 0xA)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 6)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 0x18)) = 0xFFA;
                        (*(s16 *)((u8 *)var_v0 + 0x1A)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 0x16)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 0x28)) = 0x1FA4;
                        (*(s16 *)((u8 *)var_v0 + 0x2A)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 0x26)) = 0;
                        var_v1 += 1;
                        var_v0 += 0x30;
                    } while (var_v1 < (((*(u8 *)((u8 *)arg0 + 0x25)) * 2) + 0xA));
                }
            }
            temp_v0 = func_15144B34((s32) arg2);
            sp.uEB = 1;
            sp.u118 = temp_v0;
            temp_v1_2 = ((u8 *)&D_800A4EA8);
            var_s0 = func_15142FBC(func_1513F4E4(func_15142B7C(func_15142C10(func_15142E24(var_s0, &D_800914B0, 0, 0, 0, 0, 0x78, 0, 0, &sp.uEB, 0x3E), 0xFF, 0xFF, 0xFF, 0xFF, &sp.uEB), 0x200005, 0x1F0600), 0x55, &sp.uEB), D_800D30BC | 0x80000 | 0x2CA0, (*(s32 *)((u8 *)temp_v1_2 + 0x1C)) | (*(s32 *)((u8 *)temp_v1_2 + 0x18)), &sp.uEB);
            var_a0 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
            if (var_a0 < 0) {
                var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            var_t1 = var_a0 - 1;
            if (var_t1 < 0) {
                var_t1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v0_2 = temp_s2 + (var_a0 * 0x14);
            (*(f32 *)((u8 *)(&sp.u124) + 0)) = (*(f32 *)((u8 *)temp_v0_2 + 0));
            (*(s32 *)((u8 *)(&sp.u124) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 4));
            (*(s32 *)((u8 *)(&sp.u124) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 8));
            temp_v1_3 = temp_s2 + (var_t1 * 0x14);
            sp.uE0 = (*(f32 *)((u8 *)temp_v0_2 + 0x10));
            (*(f32 *)((u8 *)(&sp.u130) + 0)) = (*(f32 *)((u8 *)temp_v1_3 + 0));
            (*(s32 *)((u8 *)(&sp.u130) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1_3 + 4));
            (*(s32 *)((u8 *)(&sp.u130) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1_3 + 8));
            sp.uE4 = (*(f32 *)((u8 *)temp_v1_3 + 0x10));
            temp_f26 = sp.u124 - (*(f32 *)((u8 *)sp.u118 + 0));
            temp_f28 = sp.u128 - (*(f32 *)((u8 *)sp.u118 + 4));
            temp_f30 = sp.u12C - (*(f32 *)((u8 *)sp.u118 + 8));
            temp_f22 = sp.u128 - sp.u134;
            temp_f24 = sp.u12C - sp.u138;
            temp_f20 = sp.u124 - sp.u130;
            temp_f14 = (temp_f22 * temp_f30) - (temp_f28 * temp_f24);
            temp_f16 = (temp_f24 * temp_f26) - (temp_f30 * temp_f20);
            temp_f12 = (temp_f20 * temp_f28) - (temp_f26 * temp_f22);
            temp_f6 = (temp_f14 * temp_f14) + (temp_f16 * temp_f16) + (temp_f12 * temp_f12);
            sp88 = temp_f6;
            sp.uEC = temp_f6;
            temp_f10 = (s32) sp.u124;
            if (temp_f6 != 0.0f) {
                temp_f2 = sp.uE0 / sqrtf(temp_f6);
                var_f14 = temp_f14 * temp_f2;
                var_f16 = temp_f16 * temp_f2;
                var_f18 = temp_f12 * temp_f2;
            } else {
                var_f18 = 0.0f;
                var_f14 = 0.0f;
                var_f16 = 0.0f;
            }
            temp_f8 = (s32) sp.u128;
            temp_f6_2 = (s32) var_f14;
            temp_f8_2 = (s32) var_f16;
            temp_f10_2 = (s32) sp.u12C;
            temp_f4 = (s32) var_f18;
            (*(s16 *)((u8 *)sp.uD8 + 0)) = temp_f10 + temp_f6_2;
            (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) (temp_f8 + temp_f8_2);
            (*(s16 *)((u8 *)sp.uD8 + 4)) = (s16) (temp_f10_2 + temp_f4);
            temp_t7 = sp.uD8 + 0x10;
            sp.uD8 = temp_t7;
            *temp_t7 = (s16) temp_f10;
            (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) temp_f8;
            (*(s16 *)((u8 *)sp.uD8 + 4)) = (s16) temp_f10_2;
            temp_t7_2 = sp.uD8 + 0x10;
            sp.uD8 = temp_t7_2;
            (*(s16 *)((u8 *)temp_t7_2 + 0)) = temp_f10 - temp_f6_2;
            (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) (temp_f8 - temp_f8_2);
            (*(s16 *)((u8 *)temp_t7_2 + 4)) = (s16) (temp_f10_2 - temp_f4);
            sp.uD8 += 0x10;
            do {
                temp_f26_2 = sp.u130 - (*(f32 *)((u8 *)sp.u118 + 0));
                temp_f28_2 = sp.u134 - (*(f32 *)((u8 *)sp.u118 + 4));
                temp_f30_2 = sp.u138 - (*(f32 *)((u8 *)sp.u118 + 8));
                temp_f22_2 = sp.u128 - sp.u134;
                temp_f24_2 = sp.u12C - sp.u138;
                temp_f20_2 = sp.u124 - sp.u130;
                temp_f14_2 = (temp_f22_2 * temp_f30_2) - (temp_f28_2 * temp_f24_2);
                temp_f16_2 = (temp_f24_2 * temp_f26_2) - (temp_f30_2 * temp_f20_2);
                temp_f12_2 = (temp_f20_2 * temp_f28_2) - (temp_f26_2 * temp_f22_2);
                temp_f8_3 = (temp_f14_2 * temp_f14_2) + (temp_f16_2 * temp_f16_2) + (temp_f12_2 * temp_f12_2);
                sp88 = temp_f8_3;
                sp.uEC = temp_f8_3;
                temp_f4_2 = (s32) sp.u130;
                if (temp_f8_3 != 0.0f) {
                    temp_f2_2 = sp.uE4 / sqrtf(temp_f8_3);
                    var_f14_2 = temp_f14_2 * temp_f2_2;
                    var_f16_2 = temp_f16_2 * temp_f2_2;
                    var_f18_2 = temp_f12_2 * temp_f2_2;
                } else {
                    var_f18_2 = 0.0f;
                    var_f14_2 = 0.0f;
                    var_f16_2 = 0.0f;
                }
                temp_f6_3 = (s32) sp.u134;
                temp_f8_4 = (s32) var_f14_2;
                temp_f6_4 = (s32) var_f16_2;
                temp_f4_3 = (s32) sp.u138;
                temp_f10_3 = (s32) var_f18_2;
                (*(s16 *)((u8 *)sp.uD8 + 0)) = temp_f4_2 + temp_f8_4;
                (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) (temp_f6_3 + temp_f6_4);
                (*(s16 *)((u8 *)sp.uD8 + 4)) = (s16) (temp_f4_3 + temp_f10_3);
                temp_t7_3 = sp.uD8 + 0x10;
                sp.uD8 = temp_t7_3;
                temp_t6 = temp_t7_3 + 0x10;
                (*(s16 *)((u8 *)temp_t7_3 + 0)) = (s16) temp_f4_2;
                (*(s16 *)((u8 *)temp_t7_3 + 2)) = (s16) temp_f6_3;
                (*(s16 *)((u8 *)temp_t7_3 + 4)) = (s16) temp_f4_3;
                sp.uD8 = temp_t6;
                (*(s16 *)((u8 *)temp_t6 + 0)) = temp_f4_2 - temp_f8_4;
                (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) (temp_f6_3 - temp_f6_4);
                (*(s16 *)((u8 *)temp_t6 + 4)) = (s16) (temp_f4_3 - temp_f10_3);
                sp.uD8 += 0x10;
                (*(s32 *)((u8 *)var_s0 + 0)) = 0x0100600C;
                temp_s0 = var_s0 + 8;
                (*(s16 **)((u8 *)var_s0 + 4)) = (s16 *) (sp.uD8 - 0x60);
                temp_s0_2 = temp_s0 + 8;
                (*(s32 *)((u8 *)temp_s0 + 0)) = 0x06000206;
                (*(s32 *)((u8 *)temp_s0 + 4)) = 0x20806;
                (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0x0604020A;
                (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0x2080A;
                var_s0 = temp_s0_2 + 8;
                temp_a0 = var_t1;
                var_t1 -= 1;
                if (var_t1 < 0) {
                    var_t1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                if (temp_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    temp_t8 = temp_s2 + (temp_a0 * 0x14);
                    (*(f32 *)((u8 *)(&sp.u124) + 0)) = (*(f32 *)((u8 *)temp_t8 + 0));
                    (*(s32 *)((u8 *)(&sp.u124) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
                    temp_v1_4 = temp_s2 + (var_t1 * 0x14);
                    (*(s32 *)((u8 *)(&sp.u124) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
                    (*(f32 *)((u8 *)(&sp.u130) + 0)) = (*(f32 *)((u8 *)temp_v1_4 + 0));
                    (*(s32 *)((u8 *)(&sp.u130) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1_4 + 4));
                    (*(s32 *)((u8 *)(&sp.u130) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1_4 + 8));
                    sp.uE4 = (*(f32 *)((u8 *)temp_v1_4 + 0x10));
                }
            } while (temp_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4810.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4ED0.s")

#ifdef NON_MATCHING
s32 func_1514654C(struct127 *, s32, s32, s32 **, u8 **, s32);
extern s32 D_800A0DA0;
extern s32 D_800A0DAC;

s32 func_150D4FF0(u8 *arg0, u8 *arg1, struct127 *arg2, s32 arg3) {
    s32 *sp34;
    s32 *sp30;
    u8 *sp2C;
    u8 *sp28;

    if (arg2->unk1D4 != NULL) {
        sp30 = &D_800A0DA0;
        sp34 = &D_800A0DAC;
        sp28 = arg0;
        sp2C = arg1;
        if (func_1514654C(arg2, arg3, 0, &sp30, &sp28, 2) != 0) {
            return 1;
        }
        return 0;
    }
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) arg2->x_position;
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) (arg2->y_position + 100.0f);
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) arg2->z_position;
    (*(f32 *)((u8 *)arg1 + 0)) = (f32) arg2->x_position;
    (*(f32 *)((u8 *)arg1 + 4)) = (f32) (arg2->y_position + 100.0f + 500.0f);
    (*(f32 *)((u8 *)arg1 + 8)) = (f32) arg2->z_position;
    return 2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4FF0.s")
#endif
void func_150D50E4(s32 arg0) {
    func_150D513C(arg0);
    func_15147E64(arg0);
}

void func_150D5110(s32 arg0) {
    func_150D513C(arg0);
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
void func_1000FD38(s32, s32, s32);
extern s32 func_150D5634;

void func_150D513C(u8 *arg0) {
    s32 *sp20;
    struct102 *temp_a0;
    struct102 *temp_a0_2;
    u8 *temp_s0;

    temp_s0 = (*(u8 **)((u8 *)arg0 + 0x98));
    if (D_8008FD8C < 5) {
        func_1000FD38(&func_150D5634, temp_s0, 0x5B3);
    }
    sp20 = &func_150D5634;
    func_1000FD38(&func_150D5634, temp_s0, 0x5B4);
    func_1000FD38(&func_150D5634, temp_s0, 0x5BC);
    temp_a0 = (*(struct102 **)((u8 *)temp_s0 + 0xC));
    if (temp_a0 != NULL) {
        func_1516972C(temp_a0);
    }
    temp_a0_2 = (*(struct102 **)((u8 *)temp_s0 + 0x10));
    if (temp_a0_2 != NULL) {
        func_1516972C(temp_a0_2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D513C.s")
#endif
extern f32 D_800A0DE4;
extern u8 D_800A0D90[];
s32 func_150D51D4(u8 *arg0)
{
  u8 *temp_v1;
  *(s16 *)(arg0 + 0x170) -= D_800BE9E4;
  temp_v1 = arg0 + 0x110;
  if (*(s16 *)(arg0 + 0x170) < 0) {
    arg0[0x18] = *(s32 *)&D_800A0D90[(func_150ADA20() & 3) * 4];
    *(s16 *)(arg0 + 0x170) = (func_150ADA20() & 7) + 3;
  }
  *(f32 *)(temp_v1 + 0x48) += (*(f32 *)(arg0 + 0x174) - *(f32 *)(temp_v1 + 0x48)) * D_800A0DE4;
  return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5268.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5634.s")
