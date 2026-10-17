#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_200480/func_151D2C70.s")

void func_151D2CC8(s16 arg0) {
    u8 *var_v0;

    for (var_v0 = D_800DD510; var_v0 != NULL; var_v0 = *(u8 **)(var_v0 + 8)) {
        if (arg0 == *(s16 *)(var_v0 + 0x10)) {
            *(s8 *)(var_v0 + 0x16) = -2;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_200480/func_151D2D0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_200480/func_151D2DE0.s")
