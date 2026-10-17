#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C000.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C164.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C2D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C628.s")

s32 func_1518CAB0(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 8;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    temp_v0[0x1B] = var_v1;
    if (temp_v0[0x1B] < 0) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518CAEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518CC0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518CDC0.s")
