#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DB3F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DB694.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DB858.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DBA98.s")

s32 func_150DBBB0(u8 *arg0) {
    f32 **pp = (f32 **)(arg0 + 0x120); // fakematch: pointer to the field keeps the reload of 0x120 in the else-if (permuter)
    if (**pp > 255.0f) {
        arg0[0x5C] = 0xFF;
    } else if (**pp < 0.0f) {
        arg0[0x5C] = 0;
    } else {
        arg0[0x5C] = **pp;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_108C00/func_150DBC94.s")
