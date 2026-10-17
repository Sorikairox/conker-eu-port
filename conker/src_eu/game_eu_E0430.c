#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B2C20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3668.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3B8C.s")

s32 func_150B3C6C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 16;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = var_v1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3CA8.s")
