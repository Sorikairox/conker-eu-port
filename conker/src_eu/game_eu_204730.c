#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151D6F20(s32 arg0, s32 arg1) {
    if ((D_800BE9F0 == 50) || (D_800BE9F0 == 51)) {
        func_150D6C40(arg0, 0xFF, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204730/func_151D6F64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204730/func_151D71AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204730/func_151D7410.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204730/func_151D75B0.s")

void func_151D767C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *temp = *(u8 **)(arg0 + 0x48);
    func_15169850(arg1, arg2, temp, temp + 4, arg0);
}

extern s32 D_80083AD0;
extern s32 D_80083C50;
u8 *func_1513445C(u8 *, s32, s32, s32);
Gfx *func_151D76BC(Gfx *gdl, u8 *arg1, s32 arg2, s32 arg3, s8 *arg4) {
    if (arg1[0x43] < 0xFF) {
        gSPSegment(gdl++, 8, &D_80083AD0);
    } else {
        gSPSegment(gdl++, 8, &D_80083C50);
    }
    gdl = (Gfx *)func_1513445C((u8 *)gdl, 0xC3, 6, 3);
    gdl = (Gfx *)func_1513445C((u8 *)gdl, 0xC3, 7, 3);
    *arg4 = 1;
    return gdl;
}
