#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AC3F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AC628.s")

s32 func_151AC97C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 8;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = var_v1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AC9B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ACB00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ACBCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ACDC0.s")

s32 func_151ACF9C(f32 *arg0) {
    f32 temp_f0 = arg0[0x4C / 4] * D_800BE9A4;

    arg0[0x2C / 4] += temp_f0;
    arg0[0x30 / 4] += temp_f0;
    return 1;
}

s32 func_151ACFD0(u8 *arg0) {
    s32 var_v0 = 0xFF;
    s16 temp_v1 = *(s16 *)(arg0 + 0x1C);

    if (temp_v1 < 0x10) {
        var_v0 = (s16)(temp_v1 * 16);
    }
    if (var_v0 < arg0[0x5C]) {
        arg0[0x5C] = var_v0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AD010.s")

s32 func_151AD0E8(u8 *arg0, u8 *arg1) {
    s32 ret = 0;

    if (arg0[0x3B] == 1) {
        *arg1 = 1;
        ret = 1;
    }
    return ret;
}

s32 func_151AE958();

void func_151AD110(u8 *arg0) {
    s32 temp = *(s32 *)(*(u8 **)(*(u8 **)(arg0 + 0x1C) + 0x31C) + 0x9C);
    if (temp != 0) {
        func_151AE958(arg0);
    }
    if (arg0) {} // keeps arg0 live past the call (home-slot store); likely a stripped debug macro
}

void func_151AD144(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x1C), (s32)(arg0 + 0x20), (s32)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ACBD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AD724.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ADEDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE61C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE694.s")

void func_151AE814(u8 *arg0) {
    u8 *temp_v0;
    f32 f;

    temp_v0 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x9C));
    f = (*(f32 *)((u8 *)arg0 + 0x3C)) * 0.89f;
    (*(f32 *)((u8 *)temp_v0 + 0x4C)) = f;
    (*(u8 *)((u8 *)temp_v0 + 0x50)) = (*(u16 *)((u8 *)arg0 + 0x76)) >> 8;
    (*(u8 *)((u8 *)temp_v0 + 0x51)) = (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0xAE));
    (*(s16 *)((u8 *)temp_v0 + 0x52)) = 0x14;
    (*(s32 *)((u8 *)temp_v0 + 0x44)) = 0;
    (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x98)) = 0;
    (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x9C)) = NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE86C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE958.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AEB40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AEBF0.s")
