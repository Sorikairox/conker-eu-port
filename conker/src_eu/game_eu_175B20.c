#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15148310.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15148428.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_151485AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15148E34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15149064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15149114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15149350.s")

s32 func_15149468(u8 **arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp = arg0[0x98 / 4];
    temp[0x20] = 4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_1514948C.s")

s32 func_15149638(u8 *arg0) {
    u8 *temp_v0;
    s32 temp_v1;

    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C) * 8;
    if (temp_v1 >= 256) {
        temp_v1 = 255;
    }
    temp_v0[0x1B] = temp_v1;
    if ((u8)temp_v1 < 0) {
        return 0;
    }
    return 1;
}

void func_15149674(s32 arg0) {
    func_15147E64(arg0);
}
