#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1512DC60(u8 *arg0) {
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

s32 func_1512D748(struct108 *arg0, s32 arg1, s32 arg2) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B470/func_1512D748.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15B470/func_1512DEF0.s")
