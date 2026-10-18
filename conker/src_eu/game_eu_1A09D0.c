#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A09D0/func_15172C50.s")

s32 func_1517F3B0(s32, s32, s32, s32, s32, s32);
extern s8 D_800DD6E0[];

void func_15173218(s32 arg0) {
    s8 *temp_v0 = D_800DD6E0 + arg0;
    if (*temp_v0 != -1) {
        *temp_v0 = -1;
        func_1517F3B0(0, 0, 0, 0, 1, arg0);
        func_1517F3B0(0, 0, 0, 0x32, 0, arg0);
    }
}

void func_15173298(u8 *arg0, s32 arg1) {
    u8 *t;
    func_150858A0(arg0, arg1, 1);
    *(u16 *)(arg0 + 0x2F8) &= 0xFFEF;
    if (D_800BE9B4 == 0) {
        t = *(u8 **)(arg0 + 0x31C);
        if (t != NULL) {
            t[0x56] = 3;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A09D0/func_15172D80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A09D0/func_151733EC.s")
