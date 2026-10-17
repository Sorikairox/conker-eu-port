#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15177F90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_151787D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15178CC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15178D1C.s")

u8 *func_15179108(u8 arg0) {
    u8 *var_v1 = D_800DD368;

    while (var_v1 != NULL) {
        if (arg0 == var_v1[0x34]) {
            return var_v1;
        }
        var_v1 = *(u8 **)(var_v1 + 8);
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15179154.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_151791A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15178C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15179314.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A5D10/func_15178E14.s")
