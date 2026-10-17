#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F2A30/func_150C5220.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F2A30/func_150C539C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F2A30/func_150C572C.s")

s32 func_150C5780(void) {
    if ((D_800C35EA == 1) && ((D_800C3A08 == 0xB) || (D_800C3A08 == 0xC) || (D_800C3A08 == 0xD))) {
        return 1;
    }
    return 0;
}

s32 func_150C5780(void);

s32 func_150C57CC(s32 arg0) {
    if (func_150C5780() != 0) {
        return 0;
    }
    return D_8008B148(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F2A30/func_150C5810.s")
