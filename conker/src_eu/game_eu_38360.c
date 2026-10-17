#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_1500ABA0(s32 arg0) {
    bzero(&D_800BE4A0, 60);
    func_1502B8E0(&D_800BE4A0, 60, 3, 12, arg0, 10);
    bzero(&D_800DDA90, 240);
    bzero(&D_800DD478, 1560);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500AC14.s")
// GOTO hell
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500AD84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500AF08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500B1F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500B3B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500B714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500B8F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500BAB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500BC7C.s")

void func_1500BE40(s32 arg0) {
    D_800DDD10[0] = 0;
    D_800DDD10[1] = 0;
    D_800DDD0C = 110;
}

void func_1500BE68(void) {
    D_800DDD1C = 0;
    D_8008CEB0 = 0;
    D_800DDC04 = D_800DDC00 = D_800DDC08 = 0;
    D_800DDD20 = 0;
    func_1500BE40(0);
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500BEC0.s")
