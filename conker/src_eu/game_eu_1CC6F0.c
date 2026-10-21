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

typedef struct { f32 x, y, z; } V3_1519EFE8;
typedef struct {
    s32 a;
    s32 b;
    V3_1519EFE8 pos;
    s16 x14;
    s16 x16;
    s16 x18;
    s16 x1A;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    s16 x2C;
    s16 x2E;
    f32 x30;
    f32 x34;
    f32 x38;
} Sp_1519EFE8;
extern f32 D_800A90A0;
extern f32 D_800A90A4;
extern f32 D_800A90A8;
extern f32 D_800A90AC;
extern f32 D_800A90B0;

void func_1519EFE8(V3_1519EFE8 *arg0, u16 arg1, f32 arg2, u8 arg3, s32 arg4) {
    Sp_1519EFE8 s;
    s32 i;
    f32 f;

    s.a = 10;
    s.b = 7;
    s.pos = *arg0;
    s.x1C = 10.0f;
    s.x20 = 8.0f;
    s.x14 = 0;
    s.x16 = 0xFF;
    s.x18 = -0x35;
    s.x1A = 0x18;
    s.x2C = 0x32;
    s.x2E = 0x14;
    f = arg2;
    s.x24 = D_800A90A0;
    s.x28 = D_800A90A4;
    s.x30 = D_800A90A8;
    s.x34 = D_800A90AC;
    s.x38 = D_800A90B0;
    i = arg1;
    func_15152700(&s, &i, &f, 1, 0.0f, 0, arg3, arg4);
}

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
