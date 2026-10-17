#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3FF70/func_15012760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3FF70/func_15012C34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_3FF70/func_15012E88.s")

void func_15012F40(void) {
    s32 i;

    for (i = 0; i < 0x1E3; i++) {
        D_800DFC00[i] = 0;
    }
}
