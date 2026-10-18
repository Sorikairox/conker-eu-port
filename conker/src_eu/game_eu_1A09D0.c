#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A09D0/func_15172C50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A09D0/func_15173218.s")

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
