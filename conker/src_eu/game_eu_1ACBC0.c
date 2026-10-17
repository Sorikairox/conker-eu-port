#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x1B];
    /* 0x2B */ s8 unk2B;
    /* 0x2C */ u8 pad2C[0x2];
    /* 0x2E */ s16 unk2E;
} struct_eu_1ACBC0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517F3B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517F470.s")

s32 func_1517F51C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_1517F470(arg0, arg1, arg2, arg3) == 0xFF) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517F54C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517F5FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517F910.s")

s32 func_1517F40C(s32 arg0) {
    if ((&D_800DDDB0)[arg0] >= (&D_800DDE28)[arg0]) {
        return 1;
    }
    return 0;
}

void func_1517F448(s32 arg0) {
    if ((&D_800DDDB0)[arg0] != (&D_800DDE28)[arg0]) {
        (&D_800DDDB0)[arg0] += D_800BE9E4;
    }
}

void func_1517F9F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *temp_v0 = D_800DE1C0[arg5];

    temp_v0[0] = arg0;
    temp_v0[1] = arg1;
    temp_v0[2] = arg2;
    D_800DE1CC[arg5] = arg3;
    D_800DE240[arg5] = arg4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FA48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FAD4.s")

void func_1517FC90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    D_800DDE08 = arg1;
    D_800DE1B8 = arg2;
    D_800DE1B9 = 0;
    D_800DE1BA = arg0;
    D_800DE1BB = arg3;
    D_800DE1BC = arg4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FCCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FD24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FD84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FF64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1518010C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15180AF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15181A6C.s")

s32 func_15182238(s32 arg0) {
    if ((&D_800DDDC8)[arg0] == 0.0f) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182270.s")

extern f32 D_800A7690;

void func_15181D70(s32 arg0) {
    f32 *temp_v1;

    (&D_800DDDD8)[arg0] = D_800A7690;
    (&D_800DDDC8)[arg0] = 0.0f;
    temp_v1 = D_800DE218[arg0];
    (*(f32 *)temp_v1) = 0.0f;
    temp_v1[1] = 0.0f;
    (&D_800DDE20)[arg0] = 1;
}

void func_15182338(s32 arg0) {
    (&D_800DDDD8)[arg0] = 0.0;
    (&D_800DDDC8)[arg0] = 0.0f;
    D_800DE218[arg0][0] = 0.0f;
    D_800DE218[arg0][1] = 0.0f;
    (&D_800DDE20)[arg0] = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182388.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182450.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182BE0.s")

void func_15182CB8(struct_eu_1ACBC0 *arg0) {
    arg0->unk2B = arg0->unk2E * arg0->unkE;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182CD8.s")
