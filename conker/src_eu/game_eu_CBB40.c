#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800D33E0[];
extern f32 D_800D33F8[];
extern u8 D_800D340C[];
extern s32 D_800D3C60;
void func_1509E330(s32 arg0, u8 *arg1) {
    if (*(s32 *)(arg1 + 4) == 1 && D_800D3C60 == 3) {
        D_800D33E0[*(s32 *)(arg1 + 8)] = (f32)*(s32 *)(arg1 + 0xC) * 0.000015258789f;
        D_800D33F8[*(s32 *)(arg1 + 8)] = (f32)*(s32 *)(arg1 + 0xC) * 0.000015258789f;
        D_800D340C[*(s32 *)(arg1 + 8)] = 1;
    }
}

void func_1509E3C4(s32 arg0, s32 arg1) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CBB40/func_1509E3D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CBB40/func_1509E7EC.s")
