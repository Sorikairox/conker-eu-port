#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151A9F80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA054.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA370.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA578.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA64C.s")

void func_151AA720(s32 arg0) {
}

void func_151AA72C(u8 *arg0) {
    s32 temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
    } sp1C;

    temp_v0 = *(s32 *)(arg0 + 0x18);
    sp1C.unk0 = temp_v0;
    sp1C.unk4 = arg0[0x1C];
    func_151482D4((s32)&sp1C, 0xA);
    func_151494E0((s32)&sp1C, 0xA);
    func_1519F928(arg0);
}

void func_151AA780(void) {
    func_1519F970();
}

void func_151AA7A0(void) {
    func_1519F970();
}

void func_151AA7C0(u8 *arg0) {
    s32 temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
    } sp1C;

    temp_v0 = *(s32 *)(arg0 + 0x18);
    sp1C.unk0 = temp_v0;
    sp1C.unk4 = arg0[0x1C];
    func_151482D4((s32)&sp1C, 0xA);
    func_151494E0((s32)&sp1C, 0xA);
    func_1519F928(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA814.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA8BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AAA3C.s")

s32 func_151EFDD0();

s32 func_151AAB54(u8 *arg0) {
    (*(s32 *)((u8 *)arg0 + 0x88)) = 0;
    if (func_150ADA20() & 1) {
        func_10010F88(0xA, 0x55F0U, (s16) ((func_151EFDD0() % 1200) - 0x258), 0U, 0, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x58)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x5C)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x60)), 0x1F4, 0x9C4);
    } else {
        func_10010F88(0xB, 0x55F0U, (s16) ((func_151EFDD0() % 1200) - 0x258), 0U, 0, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x58)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x5C)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x60)), 0x1F4, 0x9C4);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AAC88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AAFFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB06C.s")

void func_151AB100(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    func_151352EC(arg0);
}

void func_151AB128(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    func_1513530C(arg0);
}

s32 func_151AB150(u8 *arg0) {
    s32 ret = 1;
    if (arg0[0x84] == 0) {
        ret = 0;
    }
    arg0[0x84] = 0;
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AABC4.s")

s32 func_151AB36C(u8 *arg0) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C) << 4;
    if (temp_v1 >= 0x100) {
        temp_v1 = 0xFF;
    }
    if (temp_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = temp_v1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB3A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB640.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB730.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB774.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB874.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB954.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABC68.s")

void func_151ABD38(u8 *arg0) {
    s32 pad;
    s32 *temp_v0;

    temp_v0 = (s32 *)(*(u8 **)(arg0 + 0x58) + 0x58);
    if (*(u16 *)(arg0 + 0x5E) != 0) {
        func_100111C8(*(s16 *)(arg0 + 0x5E));
    }
    temp_v0[7] = 0;
    func_151346EC(arg0);
}

void func_151ABD88(u8 *arg0) {
    s32 pad;
    s32 *temp_v0;

    temp_v0 = (s32 *)(*(u8 **)(arg0 + 0x58) + 0x58);
    if (*(u16 *)(arg0 + 0x5E) != 0) {
        func_100111C8(*(s16 *)(arg0 + 0x5E));
    }
    temp_v0[7] = 0;
    func_1513470C(arg0);
}

void func_151ABDD8(void **arg0) {
    func_15141DA4(arg0[0x18 / 4], 0, 4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABE04.s")

void func_151AB920(s32 arg0, s32 arg1) {
}

u8 func_151D8E20(void);
extern f32 D_800A93F4;

void func_151AB930(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        s32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        u8 unk18;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = *(u16 *)(arg0 + 0x84);
    tmp.unkC = 0.0f;
    tmp.unk10 = D_800A93F4;
    tmp.unk14 = 3.0f;
    tmp.unk18 = func_151D8E20();
    temp_v0 = func_151491F4(0x3C, -1, 0xE, 1, 9, 0x1C, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x1C);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABF78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AC304.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AC3B0.s")
