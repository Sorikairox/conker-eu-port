#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_1512DC60 */
void camera_shake_reset(u8 *arg0) {
    u8 *temp_v0 = D_800DC6F0[arg0[0x23D]];

    *(s32 *)(temp_v0 + 0x50) = 5;
    *(f32 *)(temp_v0 + 0x54) = 0.0f;
    *(f32 *)(temp_v0 + 0x58) = 0.0f;
    *(f32 *)(temp_v0 + 0x5C) = 0.0f;
    *(f32 *)(temp_v0 + 0x60) = 0.0f;
    *(f32 *)(temp_v0 + 0x2C) = 0.0f;
    *(f32 *)(temp_v0 + 0x28) = -1.0f;
}

#ifdef NON_MATCHING
extern s32 D_80089970;

/* was func_1512D748 */
s32 camera_shake_start(struct108 *arg0, s32 arg1, s32 arg2) {
    f32 sp4;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f10_3;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f4_3;
    f32 var_f6;
    f32 var_f6_2;
    f32 var_f6_3;
    u8 *temp_v0;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t2;
    u8 temp_t4;
    u8 temp_t5;
    u8 temp_t6;
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_t9;
    u8 *temp_v1;

    temp_v0 = D_800DC6F0[arg0->unk23D];
    if (arg0->unk3D4->unk120 == 0) {
        temp_v1 = ((s32 *)((u8 *)&D_80089970 + (arg1 * 0xA)));
        (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) (*(u8 *)((u8 *)temp_v1 + 0));
        temp_t4 = (*(u8 *)((u8 *)temp_v1 + 1));
        var_f4 = (f32) temp_t4;
        if ((s32) temp_t4 < 0) {
            var_f4 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_v0 + 4)) = var_f4;
        temp_t5 = (*(u8 *)((u8 *)temp_v1 + 2));
        var_f10 = (f32) temp_t5;
        if ((s32) temp_t5 < 0) {
            var_f10 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_v0 + 8)) = var_f10;
        temp_t6 = (*(u8 *)((u8 *)temp_v1 + 3));
        var_f6 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_f6 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_v0 + 0xC)) = var_f6;
        temp_t7 = (*(u8 *)((u8 *)temp_v1 + 4));
        var_f4_2 = (f32) temp_t7;
        if ((s32) temp_t7 < 0) {
            var_f4_2 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_v0 + 0x10)) = var_f4_2;
        temp_t8 = (*(u8 *)((u8 *)temp_v1 + 5));
        var_f10_2 = (f32) temp_t8;
        if ((s32) temp_t8 < 0) {
            var_f10_2 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_v0 + 0x14)) = var_f10_2;
        temp_t9 = (*(u8 *)((u8 *)temp_v1 + 6));
        var_f6_2 = (f32) temp_t9;
        if ((s32) temp_t9 < 0) {
            var_f6_2 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_v0 + 0x18)) = var_f6_2;
        temp_t0 = (*(u8 *)((u8 *)temp_v1 + 7));
        var_f4_3 = (f32) temp_t0;
        if ((s32) temp_t0 < 0) {
            var_f4_3 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_v0 + 0x1C)) = var_f4_3;
        temp_t1 = (*(u8 *)((u8 *)temp_v1 + 8));
        var_f10_3 = (f32) temp_t1;
        if ((s32) temp_t1 < 0) {
            var_f10_3 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_v0 + 0x20)) = var_f10_3;
        temp_t2 = (*(u8 *)((u8 *)temp_v1 + 9));
        var_f6_3 = (f32) temp_t2;
        if ((s32) temp_t2 < 0) {
            var_f6_3 += 4294967296.0f;
        }
        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x10));
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0x14));
        temp_f18 = (*(f32 *)((u8 *)temp_v0 + 0x20));
        temp_f12 = temp_f2 + temp_f0;
        temp_f16 = (*(f32 *)((u8 *)temp_v0 + 0x1C));
        (*(f32 *)((u8 *)temp_v0 + 0x24)) = var_f6_3;
        temp_f14 = (*(f32 *)((u8 *)temp_v0 + 0x18)) + temp_f12;
        (*(f32 *)((u8 *)temp_v0 + 0x34)) = temp_f12;
        (*(f32 *)((u8 *)temp_v0 + 0x38)) = temp_f14;
        (*(f32 *)((u8 *)temp_v0 + 0x30)) = temp_f0;
        (*(f32 *)((u8 *)temp_v0 + 0x28)) = 0.0f;
        (*(f32 *)((u8 *)temp_v0 + 0x2C)) = 0.0f;
        (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) (temp_f16 + temp_f14);
        (*(f32 *)((u8 *)temp_v0 + 0x40)) = (f32) (temp_f18 / temp_f0);
        sp4 = (*(f32 *)((u8 *)temp_v0 + 0x24));
        (*(f32 *)((u8 *)temp_v0 + 0x48)) = 0.0f;
        (*(f32 *)((u8 *)temp_v0 + 0x44)) = (f32) ((temp_f18 - sp4) / temp_f2);
        (*(s32 *)((u8 *)temp_v0 + 0x50)) = 0;
        (*(s32 *)((u8 *)temp_v0 + 0x64)) = arg2;
        (*(f32 *)((u8 *)temp_v0 + 0x4C)) = (f32) (sp4 / temp_f16);
    }
    return (s32) temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B470/camera_shake_start.s")
#endif
#ifdef NON_MATCHING
/* was func_1512DEF0 */
void camera_shake_update(u8 *arg0) {
    f32 sp20;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f10;
    f32 var_f14;
    u8 *temp_s0;

    temp_s0 = D_800DC6F0[(*(u8 *)((u8 *)arg0 + 0x23D))];
    if (random_int() & 1) {
        var_f14 = 1.0f;
    } else {
        var_f14 = -1.0f;
    }
    temp_f2 = (*(f32 *)((u8 *)temp_s0 + 0x28));
    if ((temp_f2 != -1.0f) && ((*(s32 *)((u8 *)temp_s0 + 0x50)) != 5) && !((*(s32 *)((u8 *)arg0 + 0x84)) & 0x80000)) {
        sp20 = var_f14;
        (*(f32 *)((u8 *)temp_s0 + 0x54)) = (f32) (sinf(temp_f2 * 0.033333335f * (*(f32 *)((u8 *)temp_s0 + 0)) * 360.0f * 0.017453292f) * (var_f14 * (*(f32 *)((u8 *)temp_s0 + 0x2C))));
        (*(f32 *)((u8 *)temp_s0 + 0x58)) = (f32) (sinf((*(f32 *)((u8 *)temp_s0 + 0x28)) * 0.033333335f * (*(f32 *)((u8 *)temp_s0 + 4)) * 360.0f * 0.017453292f) * (1.0f * (*(f32 *)((u8 *)temp_s0 + 0x2C))));
        (*(f32 *)((u8 *)temp_s0 + 0x5C)) = (f32) (sinf((*(f32 *)((u8 *)temp_s0 + 0x28)) * 0.033333335f * (*(f32 *)((u8 *)temp_s0 + 8)) * 360.0f * 0.017453292f) * (-1.0f * (*(f32 *)((u8 *)temp_s0 + 0x2C))));
        temp_f12 = (*(f32 *)((u8 *)temp_s0 + 0x2C));
        temp_f14 = (*(f32 *)((u8 *)temp_s0 + 0x3C));
        temp_f2_2 = (*(f32 *)((u8 *)temp_s0 + 0x28));
        (*(f32 *)((u8 *)temp_s0 + 0x60)) = (f32) (sinf((*(f32 *)((u8 *)temp_s0 + 0x28)) * 0.033333335f * (*(f32 *)((u8 *)temp_s0 + 0xC)) * 360.0f * 0.017453292f) * (-1.0f * temp_f12));
        if ((temp_f2_2 <= temp_f14) && (temp_f12 >= 0.0f)) {
            if (temp_f2_2 <= (*(f32 *)((u8 *)temp_s0 + 0x30))) {
                if (((*(s32 *)((u8 *)temp_s0 + 0x50)) == 0) && ((*(s32 *)((u8 *)temp_s0 + 0x64)) != 0)) {
                    (*(s32 *)((u8 *)temp_s0 + 0x50)) = 1;
                }
                (*(f32 *)((u8 *)temp_s0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x2C)) + ((*(f32 *)((u8 *)temp_s0 + 0x40)) * D_800BE9A4));
            } else if (temp_f2_2 <= (*(f32 *)((u8 *)temp_s0 + 0x34))) {
                if (((*(s32 *)((u8 *)temp_s0 + 0x50)) == 1) && ((*(s32 *)((u8 *)temp_s0 + 0x64)) != 0)) {
                    (*(s32 *)((u8 *)temp_s0 + 0x50)) = 2;
                }
                (*(f32 *)((u8 *)temp_s0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x2C)) - ((*(f32 *)((u8 *)temp_s0 + 0x44)) * D_800BE9A4));
            } else if (temp_f2_2 <= (*(f32 *)((u8 *)temp_s0 + 0x38))) {
                if (((*(s32 *)((u8 *)temp_s0 + 0x50)) == 2) && ((*(s32 *)((u8 *)temp_s0 + 0x64)) != 0)) {
                    (*(s32 *)((u8 *)temp_s0 + 0x50)) = 3;
                }
            } else if (temp_f2_2 < temp_f14) {
                if (((*(s32 *)((u8 *)temp_s0 + 0x50)) == 3) && ((*(s32 *)((u8 *)temp_s0 + 0x64)) != 0)) {
                    (*(s32 *)((u8 *)temp_s0 + 0x50)) = 4;
                }
                (*(f32 *)((u8 *)temp_s0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x2C)) - ((*(f32 *)((u8 *)temp_s0 + 0x4C)) * D_800BE9A4));
            } else {
                camera_shake_reset(arg0);
            }
            var_f10 = (f32) D_800BE9A0;
            if ((s32) D_800BE9A0 < 0) {
                var_f10 += 4294967296.0f;
            }
            (*(f32 *)((u8 *)temp_s0 + 0x28)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x28)) + var_f10);
            return;
        }
        (*(s32 *)((u8 *)temp_s0 + 0x50)) = 5;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B470/camera_shake_update.s")
#endif