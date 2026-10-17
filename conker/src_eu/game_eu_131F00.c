#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131F00/func_151046F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131F00/func_15104764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_131F00/func_15104A0C.s")

s32 func_151044F4(void) {
    u8 *temp_v1 = D_800CCA0C;
    s32 ret = 0;

    if (temp_v1 != NULL) {
        return temp_v1[0x7D];
    }
    return ret;
}
