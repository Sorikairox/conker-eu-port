#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A1730/func_15173F20.s")

s32 func_15173F20();

void func_151741D0(s32 arg0, s32 arg1) {
    func_15173F20(0, 0, arg0, arg1, 0);
}

s32 func_151149AC(u8);
void func_15174200(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p = (u8 *)func_151149AC(arg2);
    u32 v; // fakematch: named temp fixes the order of the argument setup

    if (p != NULL) {
        v = *(u16 *)(p + 0x54) & 0xFFFF7FFF;
        func_15173F20(v, 1, arg0, arg1, (p - (u8 *)D_800DBEF4) / 0xA0);
    }
}
