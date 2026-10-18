#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *func_1519EEE0(s16 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    u8 *temp_v0;
    temp_v0 = func_15167A68(0x26, arg6, 0x2C, 1, (u8) (s32) arg5, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    (*(s32 *)((u8 *)temp_v0 + 0x18)) = arg3;
    (*(s32 *)((u8 *)temp_v0 + 0x1C)) = arg4;
    (*(s16 *)((u8 *)temp_v0 + 0x20)) = arg0;
    (*(u8 *)((u8 *)temp_v0 + 0x28)) = arg2;
    (*(s32 *)((u8 *)temp_v0 + 0x24)) = arg1;
    (*(s32 *)((u8 *)temp_v0 + 0x10)) = 1;
    (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0;
    return temp_v0;
}

void func_1519EF74(struct102 *arg0) {
    s32 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x10) & 1) {
        var_v0 = 0;
        *(s16 *)((u8 *)arg0 + 0x20) -= D_800BE9E4;
        if (*(s16 *)((u8 *)arg0 + 0x20) < 0) {
            var_v0 = 1;
        }
        if (var_v0 != 0) {
            if (arg0->unk28 == 0) {
                var_v0 = *(s32 *)((u8 *)arg0 + 0x24);
                *(s32 *)(var_v0 + 0x30) = 0;
            }
            func_1516972C(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519EFE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519F0FC.s")

s32 func_1519F294(u8 *arg0) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x170));
    (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * 0.1f);
    (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x1C)) * 0.1f);
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC));
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v1 + 4));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CC6F0/func_1519F2F4.s")

s32 func_1519F474(u8 *arg0) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x110));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x18)) * 10.0f);
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0x1C)) * 10.0f);
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) (*(f32 *)temp_v1);
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v1 + 4));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
    return 1;
}
