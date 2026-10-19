#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_150B2960(s32 arg0, s32 arg1) {
    return 10;
}

s32 func_1514CBE8(f32, f32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32);
s32 func_151D45A4(f32 *, s32, s32);

void func_150B2974(u8 *arg0, s32 arg1, s32 arg2) {
    f32 sp3C[3];

    sp3C[0] = *(f32 *)(arg0 + 0x14);
    sp3C[1] = *(f32 *)(arg0 + 0x180);
    sp3C[2] = *(f32 *)(arg0 + 0x1C);
    func_1514CBE8(sp3C[0], sp3C[1], *(s32 *)&sp3C[2], 0x43070000, 0, 0xFF, (func_150ADA20() % 15U) + 0x1B, 7, 0, 0.0f, 0, 0xFF);
    func_151D5404((struct17 *)sp3C, 1502.0f, 3000.0f, 0.00033333333f, 0xC, 0xF, 0xFF, 0);
    func_151D45A4(sp3C, 0xFF, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0170/func_150B2A50.s")
