#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BA4B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BA634.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BAA18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BAAC8.s")

extern s32 func_151BB690;

void func_151BB5F4(u8 *arg0) {
    func_1000FA64(0x4A7U, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), 0x2000, 0x320U, 0xC8, (s32) &func_151BB690, arg0, 0, 8, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BB690.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BBBCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC04C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC494.s")

s32 func_150E856C(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151BC56C(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp40;
    f32 sp3C;

    sp3C = func_150ADA68();
    sp40 = func_150ADA20();
    func_150E856C((sp3C * 75.0f) + 75.0f, ((sp40 % 56U) + 0xC8) & 0xFF, arg0, arg1, (func_150ADA20() % 205U) + 0x12B, 1, 1, 0, 0, 0, (s32) arg2, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC624.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC6B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BC920.s")

s32 func_151BCB30(s32 **arg0) {
    s32 *temp_v0 = arg0[0x10];

    if (*temp_v0 == 0) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BCB54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BCBFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BCD44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BD040.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BD7CC.s")

s32 func_151BD86C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);

    if (*(s32 *)temp_v0 == 0) {
        return 0;
    }
    if (arg0[0x2C] != temp_v0[0x3B]) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BD8A8.s")

s32 func_151BD9DC(s16 *arg0) {
    arg0[0x40] = 0;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BD9EC.s")

f32 func_151BDD00(s16 *arg0) {
    s16 temp_v0 = arg0[0x40];
    f32 ret = (f32)temp_v0 * 2 * D_800AAC40 + D_800AAC44;

    arg0[0x40] = temp_v0 + D_800BE9E4;
    return ret;
}

s32 func_15131C7C();

void func_151BDD4C(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0xB0));
    if (((*(s32 *)temp_v0) != 0) && ((*(u8 *)((u8 *)temp_v0 + 4)) != 0xFF)) {
        (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
        (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18));
        (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x1C));
    }
    func_15131C7C();
}

void func_151BDDA4(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3B);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BDDD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BE33C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BE65C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BE6E8.s")

void func_151BE768(struct260 * arg0) {
    func_151BE6E8(arg0);
    func_1514933C(arg0);
}

void func_151BE794(struct260 * arg0) {
    func_151BE6E8(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BE7C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BEA68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BEB08.s")

void func_151BEBB4(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x110), (s32)(arg0 + 0x114), (s32)arg0);
}

void func_151BEBF4(u8 *arg0) {
    u8 *temp_v0 = arg0 + 0x110;

    if (*(s32 *)(arg0 + 0x160) != 0) {
        u8 *temp_v1 = *(u8 **)(temp_v0 + 0x50);

        temp_v1 += 0x28;
        *(s32 *)(temp_v1 + temp_v0[5] * 4 + 8) = 0;
    }
}

void func_151BEC24(struct210 * arg0) {
    func_151BEBF4(arg0);
    func_1513CA6C(arg0);
}

void func_151BEC50(struct210 * arg0) {
    func_151BEBF4(arg0);
    func_1513CAA0(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BEC7C.s")

void func_151BED38(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x180), (s32)(arg0 + 0x184), (s32)arg0);
}

void func_151BED78(u8 *arg0) {
    u8 *temp_v0 = arg0 + 0x170;

    if (*(s32 *)(arg0 + 0x178) != 0) {
        u8 *temp_v1 = *(u8 **)(temp_v0 + 8);

        temp_v1 += 0x28;
        *(s32 *)(temp_v1 + temp_v0[0xC] * 4 + 0x10) = 0;
    }
}

void func_151BEDA8(struct210 * arg0) {
    func_151BED78(arg0);
    func_151411A4(arg0);
}

void func_151BEDD4(struct210 * arg0) {
    func_151BED78(arg0);
    func_151411C4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BEE00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BF0D0.s")

s32 func_151BF244(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    *arg4 = 1;
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BF268.s")

s32 func_151BF444(u8 *arg0) {
    if (arg0[0x127] == 0xFF) {
        return 0;
    }
    if (*(s32 *)arg0 == 0) {
        return 0;
    }
    if (arg0[4] == 0xFF) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BF490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BF678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BF8F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BFDCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151C00DC.s")

void func_151C0154(struct260 * arg0) {
    func_151C00DC(arg0);
    func_1514933C(arg0);
}

void func_151C0180(struct260 * arg0) {
    func_151C00DC(arg0);
    func_15149368(arg0);
}

void func_151C01AC(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x57) {
        func_1516972C(arg0);
    }
}
