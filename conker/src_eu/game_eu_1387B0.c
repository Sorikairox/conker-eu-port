#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1510AFA0(s32 arg0) {
    func_15179008(0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1387B0/func_1510AFC4.s")

s32 func_151152A4(u8 *, s32, s32, s16, s16, s32);

void func_1510B34C(u8 *arg0) {
    f32 x;

    *(f32 *)(arg0 + 0x80) += (3.1415927f * D_800BE9E4) / 50.0f;
    x = cosf(*(f32 *)(arg0 + 0x80)) * 10.0f;
    *(f32 *)(arg0 + 0x60) = *(f32 *)(arg0 + 0) - x;
    *(f32 *)(arg0 + 0) = x;
    if (*(s32 *)(arg0 + 0x7C) == 0) {
        if (*(f32 *)(arg0 + 0x80) >= 3.1415927f) {
            *(s32 *)(arg0 + 0x7C) = 1;
            func_151152A4(arg0, 0x4CA, 0x2EE0, 0xC8, 0x3E8, 4);
        }
    } else if (*(f32 *)(arg0 + 0x80) >= 6.2831855f) {
        *(s32 *)(arg0 + 0x7C) = 0;
        *(f32 *)(arg0 + 0x80) -= 6.2831855f;
        func_151152A4(arg0, 0x4CB, 0x2EE0, 0xC8, 0x3E8, 4);
    }
}
