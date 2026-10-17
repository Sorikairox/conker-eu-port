#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF2B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF604.s")

void func_150FF808(s32 arg0) {
    func_15031C4C(arg0, 0x82, 0);
}

void func_150FF82C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_15145740(arg0, arg1, arg2, arg3, D_800A24EC);
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_150FF840.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_151000EC.s")

s32 func_15145EA4(s32 **, s32 *, s32, s32);
extern s32 D_800A2500;

void func_1510015C(u8 *arg0, s32 arg1, s32 arg2) {
    s32 *sp1C;
    s32 sp18;

    sp1C = &D_800A2500;
    sp18 = arg2;
    func_15145EA4(&sp1C, &sp18, (*(s32 *)((u8 *)arg0 + 0x1D4)) + (D_80088BB0 << 6), 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_151001BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_15100248.s")

void func_151002AC(s32 arg0, u8 *arg1, s32 arg2) {
    u8 temp_v0 = arg1[4];
    if (((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) && !(*(s32 *)(arg1 + 0x94) & 0x80)) {
        func_1508220C(arg1, 4, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12CAC0/func_15100304.s")
