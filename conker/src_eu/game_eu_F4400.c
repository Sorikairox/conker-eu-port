#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6BF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6C3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6D2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6D70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6DC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6F08.s")

s32 func_150C721C(u8 *arg0) {
    s32 ret = 1;
    if (arg0[0x5C] == 0) {
        ret = 0;
    }
    arg0[0x5C] = 0;
    return ret;
}

void func_150C7240(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    func_151346EC(arg0);
}

void func_150C7268(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    func_1513470C(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C7290.s")
