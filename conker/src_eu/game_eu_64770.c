#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15036F60(u8 *arg0) {
    s32 i;

    *(f32 **)(arg0 + 0x324) = allocate_memory(0x48, 1, 0, 0);
    bzero(*(f32 **)(arg0 + 0x324), 0x48);
    for (i = 0; i < 3; i++) {
        (*(f32 **)(arg0 + 0x324))[i] = -99999.0f;
        (*(f32 **)(arg0 + 0x324))[i + 3] = -99999.0f;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15036FD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037988.s")
extern s32 D_800C4414;

s32 func_15037B70(s32 arg0, u8 *arg1) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t8;
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg0];
    temp_t8 = temp_v0->unk2F8 & 7;
    if (temp_t8 == 1) {
        (*(f32 *)arg1) = (f32) D_800DBFF0->unk2F8;
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) D_800DBFF0->unk2FC;
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) D_800DBFF0->unk300;
        return 1;
    }
    if (temp_t8 == 2) {
        if (temp_v0->unk5 == 4) {
            temp_f0 = temp_v0->x_position - (f32) (*(s16 *)((u8 *)(&D_800C4414) + 0));
            temp_f2 = temp_v0->z_position - (f32) (*(s16 *)((u8 *)(&D_800C4414) + 4));
            if (62500.0f < ((temp_f0 * temp_f0) + (temp_f2 * temp_f2))) {
                return 1;
            }
        }
        (*(f32 *)arg1) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 0));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 2));
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 4));
        return 1;
    }
    if (temp_t8 == 3) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037CCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_150383B0.s")

#ifdef NON_MATCHING
extern f32 D_800989F8;
void func_15038758(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f0;

    switch (arg5) {                                 /* irregular */
    case 0:
        *arg0 = func_150484A0(arg2, arg4);
        var_f0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
block_9:
        *arg1 = var_f0;
        break;
    case 1:
        *arg0 = func_150484A0(-arg4, arg2);
        var_f0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 2:
        *arg0 = func_150484A0(arg4, -arg2);
        var_f0 = func_150484A0(arg3, sqrtf((arg2 * arg2) + (arg4 * arg4)));
        goto block_9;
    case 3:
        *arg0 = func_150484A0(arg4, -arg3);
        var_f0 = func_150484A0(-arg2, sqrtf((arg3 * arg3) + (arg4 * arg4)));
        goto block_9;
    }
    *arg0 *= D_800989F8;
    *arg1 *= D_800989F8;
    temp_f0 = *arg0;
    if (temp_f0 > 180.0f) {
        *arg0 = temp_f0 - 360.0f;
    }
    temp_f0_2 = *arg1;
    if (temp_f0_2 > 180.0f) {
    s32 pad;
        *arg1 = temp_f0_2 - 360.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15038758.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15038910.s")

void *func_15039D44(s32 arg0, s32 arg1) {
    return &D_80098418[arg1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15039D68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15039CC8.s")

#ifdef NON_MATCHING
s32 func_15039D68(f32 *, f32 *, f32 *, f32 *, f32, f32, s32);

void func_1503A1C0(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 var_f2;
    f32 var_f2_2;
    u8 *temp_v0;

    if (arg0 == 0) {
        func_15039D68(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return;
    }
    temp_v0 = func_15039D44(arg7, arg0);
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 0x10));
    temp_f0 = *arg1;
    if ((((*(f32 *)((u8 *)temp_v0 + 0)) + temp_f12) < temp_f0) || (var_f2 = (*(f32 *)((u8 *)temp_v0 + 4)), (temp_f0 < (var_f2 - temp_f12)))) {
        *arg1 = arg5;
        *arg2 = arg6;
        if (arg3 != NULL) {
            *arg3 = *arg1;
            *arg4 = *arg2;
        }
    } else {
        if (arg3 != NULL) {
            *arg3 = temp_f0;
            *arg4 = *arg2;
            var_f2 = (*(f32 *)((u8 *)temp_v0 + 4));
        }
        if (*arg1 < var_f2) {

        } else {
            temp_f12_2 = (*(f32 *)((u8 *)temp_v0 + 0));
            if (temp_f12_2 < *arg1) {
                var_f2 = temp_f12_2;
            } else {
                var_f2 = *arg1;
            }
        }
        *arg1 = var_f2;
        temp_f12_3 = (*(f32 *)((u8 *)temp_v0 + 8));
        temp_f14 = (*(f32 *)((u8 *)temp_v0 + 0x14));
        temp_f0_2 = *arg2;
        if (((temp_f12_3 + temp_f14) < temp_f0_2) || (var_f2_2 = (*(f32 *)((u8 *)temp_v0 + 0xC)), (temp_f0_2 < (var_f2_2 - temp_f14)))) {
            *arg2 = arg6;
            return;
        }
        if (temp_f0_2 < var_f2_2) {

        } else if (temp_f12_3 < temp_f0_2) {
            var_f2_2 = temp_f12_3;
        } else {
            var_f2_2 = temp_f0_2;
        }
        *arg2 = var_f2_2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A1C0.s")
#endif
#ifdef NON_MATCHING
s32 func_1503DA64(s32 arg0, s32 arg1);
void func_1507C7C0(struct127 *, s16 *, s16 *, s16 *);
/* func_1503A37C (P57, from the m2c draft): object bounds from the skeleton. With a skeleton (+0x1D4) and a model
 * header D_800D1C90[type] (func_1503DA64(type, 0) == 0): joint header+0x26's matrix rows scaled to the header
 * radii (+0x3A u8, +0 s16, +0x30 s8) * y scale +0x150 give the box +0x1A4..+0x1B6 (s16) and the direction bytes
 * +0x1B8..+0x1BA; without: from the position, func_1507C7C0's height and header +0 * y scale. */
void func_1503A37C(struct127 *arg0) {
    u8 *temp_v0_2;
    u8 temp_v0;
    u8 temp_t4;
    struct124 *temp_v1_2;
    struct124 *temp_v1;
    s16 var_t0;
    s16 temp_v1_3;
    s16 temp_v0_3;
    s16 temp_a0;
    f32 var_f8;
    f32 var_f2_4;
    f32 var_f2_3;
    f32 var_f2_2;
    f32 var_f2;
    f32 var_f16;
    f32 var_f14;
    f32 var_f12;
    f32 temp_f6;
    f32 temp_f2;
    f32 temp_f18_4;
    f32 temp_f18_3;
    f32 temp_f18_2;
    f32 temp_f18;
    f32 temp_f16_3;
    f32 temp_f16_2;
    f32 temp_f16;
    f32 temp_f14_3;
    f32 temp_f14_2;
    f32 temp_f14;
    f32 temp_f12_3;
    f32 temp_f12_2;
    f32 temp_f12;
    f32 temp_f0_5;
    f32 temp_f0_4;
    f32 temp_f0_3;
    f32 temp_f0_2;
    f32 temp_f0;
    f32 sp28;
    s32 sp2C;
    s16 sp32;
    s16 sp34;
    s16 sp36;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    f32 sp48;
    f32 sp4C;
    f32 sp50;
    f32 sp54;

    temp_v0 = ((u8 *)arg0)[4];
    if (temp_v0 != 0xFF) {
        if (((*(u8 **)((u8 *)arg0 + 0x1D4)) != NULL) && (D_800D1C90[temp_v0] != NULL)) {
            if (func_1503DA64(temp_v0, 0) == 0) {
                temp_v1 = D_800D1C90[((u8 *)arg0)[4]];
                sp28 = (*(f32 *)((u8 *)arg0 + 0x150));
                temp_t4 = (*(u8 *)((u8 *)temp_v1 + 0x3A));
                temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x1D4)) + ((*(u8 *)((u8 *)temp_v1 + 0x26)) << 6);
                var_f8 = (f32) temp_t4;
                if ((s32) temp_t4 < 0) {
                    var_f8 += 4294967296.0f;
                }
                temp_f6 = var_f8 * sp28;
                sp48 = temp_f6;
                if (temp_f6 != 0.0f) {
                    temp_f12 = (*(f32 *)((u8 *)temp_v0_2 + 0));
                    temp_f14 = (*(f32 *)((u8 *)temp_v0_2 + 4));
                    temp_f16 = (*(f32 *)((u8 *)temp_v0_2 + 8));
                    temp_f18 = (temp_f12 * temp_f12) + (temp_f14 * temp_f14) + (temp_f16 * temp_f16);
                    var_f2 = temp_f18;
                    if (temp_f18 != 0.0f) {
                        var_f2 = sqrtf(temp_f18);
                    }
                    if (var_f2 != 0.0f) {
                        var_f2 = sp48 / var_f2;
                    }
                    sp54 = temp_f12 * var_f2;
                    sp50 = temp_f14 * var_f2;
                    sp4C = temp_f16 * var_f2;
                } else {
                    sp4C = 0.0f;
                    sp50 = 0.0f;
                    sp54 = 0.0f;
                }
                temp_f18_2 = (f32) (*(s16 *)((u8 *)temp_v1 + 0)) * sp28;
                if (temp_f18_2 != 0.0f) {
                    temp_f12_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x10));
                    temp_f14_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x14));
                    temp_f16_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x18));
                    temp_f0 = sqrtf((temp_f12_2 * temp_f12_2) + (temp_f14_2 * temp_f14_2) + (temp_f16_2 * temp_f16_2));
                    var_f2_2 = temp_f0;
                    if (temp_f0 != 0.0f) {
                        var_f2_2 = temp_f18_2 / temp_f0;
                    }
                    sp44 = temp_f12_2 * var_f2_2;
                    sp40 = temp_f14_2 * var_f2_2;
                    sp3C = temp_f16_2 * var_f2_2;
                } else {
                    sp3C = 0.0f;
                    sp40 = 0.0f;
                    sp44 = 0.0f;
                }
                temp_f12_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x20));
                temp_f14_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x24));
                temp_f16_3 = (*(f32 *)((u8 *)temp_v0_2 + 0x28));
                temp_f18_3 = (f32) (*(s8 *)((u8 *)temp_v1 + 0x30)) * sp28;
                if (temp_f18_3 != 0.0f) {
                    temp_f0_2 = sqrtf((temp_f12_3 * temp_f12_3) + (temp_f14_3 * temp_f14_3) + (temp_f16_3 * temp_f16_3));
                    var_f2_3 = temp_f0_2;
                    if (temp_f0_2 != 0.0f) {
                        var_f2_3 = temp_f18_3 / temp_f0_2;
                    }
                    temp_f0_3 = 127.0f / temp_f18_3;
                    var_f12 = temp_f12_3 * var_f2_3;
                    var_f14 = temp_f14_3 * var_f2_3;
                    var_f16 = temp_f16_3 * var_f2_3;
                    ((u8 *)arg0)[0x1B8] = (u8) (s32) (var_f12 * temp_f0_3);
                    ((u8 *)arg0)[0x1B9] = (u8) (s32) (var_f14 * temp_f0_3);
                    ((u8 *)arg0)[0x1BA] = (u8) (s32) (var_f16 * temp_f0_3);
                } else {
                    temp_f0_4 = sqrtf((temp_f12_3 * temp_f12_3) + (temp_f14_3 * temp_f14_3) + (temp_f16_3 * temp_f16_3));
                    var_f2_4 = temp_f0_4;
                    if (temp_f0_4 != 0.0f) {
                        var_f2_4 = 127.0f / temp_f0_4;
                    }
                    var_f14 = 0.0f;
                    var_f12 = 0.0f;
                    var_f16 = 0.0f;
                    ((u8 *)arg0)[0x1B8] = (u8) (s32) (temp_f12_3 * var_f2_4);
                    ((u8 *)arg0)[0x1B9] = (u8) (s32) (temp_f14_3 * var_f2_4);
                    ((u8 *)arg0)[0x1BA] = (u8) (s32) (temp_f16_3 * var_f2_4);
                }
                (*(s16 *)((u8 *)arg0 + 0x1A4)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x30)) + var_f12);
                (*(s16 *)((u8 *)arg0 + 0x1A6)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x34)) + var_f14);
                (*(s16 *)((u8 *)arg0 + 0x1A8)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x38)) + var_f16);
                temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A4));
                (*(s16 *)((u8 *)arg0 + 0x1AA)) = (s16) (s32) ((*(f32 *)((u8 *)temp_v0_2 + 0x34)) + sp40);
                temp_f18_4 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A6));
                (*(s16 *)((u8 *)arg0 + 0x1AC)) = (s16) (s32) (temp_f2 + sp54 + sp44);
                temp_f0_5 = (f32) (*(s16 *)((u8 *)arg0 + 0x1A8));
                (*(s16 *)((u8 *)arg0 + 0x1AE)) = (s16) (s32) (temp_f18_4 + sp50 + sp40);
                (*(s16 *)((u8 *)arg0 + 0x1B0)) = (s16) (s32) (temp_f0_5 + sp4C + sp3C);
                (*(s16 *)((u8 *)arg0 + 0x1B2)) = (s16) (s32) ((temp_f2 - sp54) + sp44);
                (*(s16 *)((u8 *)arg0 + 0x1B4)) = (s16) (s32) ((temp_f18_4 - sp50) + sp40);
                (*(s16 *)((u8 *)arg0 + 0x1B6)) = (s16) (s32) ((temp_f0_5 - sp4C) + sp3C);
            }
        } else {
            temp_v1_2 = D_800D1C90[temp_v0];
            if (temp_v1_2 != NULL) {
                var_t0 = *(s16 *)temp_v1_2;
            } else {
                var_t0 = 0;
            }
            sp2C = (s32) var_t0;
            func_1507C7C0(arg0, &sp36, &sp34, &sp32);
            (*(s16 *)((u8 *)arg0 + 0x1A4)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14));
            temp_v0_3 = (*(s16 *)((u8 *)arg0 + 0x1A4));
            ((u8 *)arg0)[0x2CA] = 0;
            (*(s16 *)((u8 *)arg0 + 0x1AC)) = (s16) temp_v0_3;
            (*(s16 *)((u8 *)arg0 + 0x1B2)) = (s16) temp_v0_3;
            (*(s16 *)((u8 *)arg0 + 0x1A6)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x18)) + (f32) ((s32) (sp36 * 7) / 8));
            (*(s16 *)((u8 *)arg0 + 0x1A8)) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C));
            temp_a0 = (*(s16 *)((u8 *)arg0 + 0x1A8));
            (*(s16 *)((u8 *)arg0 + 0x1B0)) = (s16) temp_a0;
            (*(s16 *)((u8 *)arg0 + 0x1B6)) = (s16) temp_a0;
            (*(s16 *)((u8 *)arg0 + 0x1AA)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x1A6)) + ((f32) sp2C * (*(f32 *)((u8 *)arg0 + 0x150))));
            temp_v1_3 = (*(s16 *)((u8 *)arg0 + 0x1AA));
            (*(s16 *)((u8 *)arg0 + 0x1AE)) = (s16) temp_v1_3;
            (*(s16 *)((u8 *)arg0 + 0x1B4)) = (s16) temp_v1_3;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A37C.s")
#endif

void func_1503A8FC(void) {
    u8 *p;
    p = (u8 *)D_800CC2D0[D_800C3E78].unk1D4 + 0x40;
    *(f32 *)(p + 0x30) = *(f32 *)((u8 *)&D_800CC2D0[D_800C3E78] + 0x174);
    *(f32 *)(p + 0x34) = D_800CC2D0[D_800C3E78].y_position;
    *(f32 *)(p + 0x38) = *(f32 *)((u8 *)&D_800CC2D0[D_800C3E78] + 0x178);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A968.s")

s32 func_15037224();
s32 func_1503A968();
extern u8 D_800C441A;

void func_1503AAE0(void) {
    s32 sp1C;

    sp1C = D_800C441A;
    D_800C441A = 0;
    func_15037224();
    D_800C441A = sp1C;
    func_1503A968();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503AB20.s")

s32 func_150383B0(u8 *, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern s32 D_800C43F0;

void func_1503B9F8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    (*(f32 *)((u8 *)arg0 + 0)) = -99999.0f;
    (*(f32 *)((u8 *)arg0 + 4)) = -99999.0f;
    (*(f32 *)((u8 *)arg0 + 8)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 0)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 4)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 8)) = -99999.0f;
    if (func_15037B70(arg3, arg0) == 0) {
        func_150383B0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
    }
}
