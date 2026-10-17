#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5870.s")

void func_150C5930(struct102 *arg0) {
    func_15169804(arg0);
}

void func_150C5950(struct102 *arg0) {
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C59C0.s")

void func_150C5A10(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5930(arg0);
}

void func_150C5A3C(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5950(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5BA4.s")

s32 func_150C6088(u8 *arg0) {
    u8 **temp_v1 = (u8 **)(arg0 + 0xC8);

    if (**(s32 **)(arg0 + 0xC8) == 0) {
        return 0;
    }
    *(f32 *)(arg0 + 0x24) = *(f32 *)(*temp_v1 + 0x14);
    *(f32 *)(arg0 + 0x28) = *(f32 *)(*temp_v1 + 0x18);
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(*temp_v1 + 0x1C);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C60D4.s")

void func_150C6174(s32 arg0) {
    func_1514D3B0(arg0, 0x15, 1, 0);
}

void func_150C619C(s32 arg0) {
    func_1514D3B0(arg0, 0x15, 2, 0);
}

void func_150C61C4(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_80088B68[arg0[0x38]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C620C.s")
