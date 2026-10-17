#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D4CC0/func_151A74B0.s")

s32 func_151A799C(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x170;
    if (*(s16 *)(arg0 + 0x64) < 0x20) {
        if (*(struct102 **)(temp_v0 + 4) != NULL) {
            func_1516972C(*(struct102 **)(temp_v0 + 4));
            *(struct102 **)(temp_v0 + 4) = NULL;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D4CC0/func_151A79EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D4CC0/func_151A7BC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D4CC0/func_151A7D70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D4CC0/func_151A7E2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D4CC0/func_151A7EB8.s")
