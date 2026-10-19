#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF2B0.s")

extern s32 D_800A2420;
void func_150FF550(u8 *arg0, s16 arg1, u8 *arg2) {
    s32 *sp34;
    u8 *sp30;
    s32 temp_v0;
    if (arg1 == -1) {
        *(f32 *)(arg2 + 0) = *(f32 *)(arg0 + 0x14);
        *(f32 *)(arg2 + 4) = *(f32 *)(arg0 + 0x18);
        *(f32 *)(arg2 + 8) = *(f32 *)(arg0 + 0x1C);
        return;
    }
    temp_v0 = func_15031C4C(arg0, arg1, 0);
    if (temp_v0 == 0) {
        *(f32 *)(arg2 + 0) = *(f32 *)(arg0 + 0x14);
        *(f32 *)(arg2 + 4) = *(f32 *)(arg0 + 0x18);
        *(f32 *)(arg2 + 8) = *(f32 *)(arg0 + 0x1C);
        return;
    }
    sp34 = &D_800A2420;
    sp30 = arg2;
    func_1514654C(arg0, temp_v0, 0, &sp34, &sp30, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF604.s")

void func_150FF808(s32 arg0) {
    func_15031C4C(arg0, 0x82, 0);
}

void func_150FF82C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_15145740(arg0, arg1, arg2, arg3, 0.81100005f);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF9F4.s")

s32 func_150FFC34(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0[4] == 0x98) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FFC60.s")
