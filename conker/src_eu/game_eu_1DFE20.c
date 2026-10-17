#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ s32 unk38[1];
} struct_eu_1DFE20_c;

typedef struct {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ struct_eu_1DFE20_c *unk178;
    /* 0x17C */ u8 unk17C;
} struct_eu_1DFE20_d;

typedef struct {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ s32 unk44;
} struct_eu_1DFE20_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ struct_eu_1DFE20_b *unk4C;
} struct_eu_1DFE20;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B2610.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B26B0.s")

void func_151B27BC(s32 arg0) {
    func_151B27DC(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B27DC.s")

void func_151B284C(void *arg0) {
    func_151B27BC(arg0);
    func_1514933C(arg0);
}

void func_151B2878(void *arg0) {
    func_151B27BC(arg0);
    func_15149368(arg0);
}

s32 func_151B28A4(u8 *arg0) {
    struct127 *temp_v0 = *(struct127 **)(arg0 + 0x28);
    s32 ret = 2;
    u8 *temp_v1 = *(u8 **)(arg0 + 0x30);

    if (((temp_v0 - D_800CC2D0) + 1 == temp_v1[0x65]) && (*(s32 *)(temp_v1 + 0x5C) == 1)) {
        return 1;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B28F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B2C40.s")

void func_151B2F00(struct_eu_1DFE20_d *arg0) {
    struct_eu_1DFE20_c *temp_v0 = arg0->unk178;

    if (temp_v0 != NULL) {
        temp_v0->unk38[arg0->unk17C] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B2F24.s")

void func_151B3474(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DFE20/func_151B34B4.s")

void func_151B4D88(void *arg0, void *arg1, s32 arg2, u8 arg3);

void func_151B3550(u8 *arg0, s32 arg1, u8 arg2) {
    func_151B4D88(arg0, arg0 + 0x150, arg1, arg2);
}

void func_151B3580(struct_eu_1DFE20 *arg0) {
    struct_eu_1DFE20_b *temp_v0 = arg0->unk4C;
    if (temp_v0 != NULL) {
        temp_v0->unk44 = 0;
    }
}

void func_151B3598(void *arg0) {
    func_151B3580(arg0);
    func_1514933C(arg0);
}

void func_151B35C4(void *arg0) {
    func_151B3580(arg0);
    func_15149368(arg0);
}

void func_151B35F0(s32 arg0, s32 arg1, u8 arg2) {
    s32 pad;
    s32 temp_a2;

    temp_a2 = arg0 + 0x150;
    func_15169850(arg1, arg2, temp_a2, arg0 + 0x154, arg0);
    func_15169850(arg1, arg2, temp_a2 + 0x14, temp_a2 + 0x18, arg0);
}
