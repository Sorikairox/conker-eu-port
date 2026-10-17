#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510DEF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E6A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E908.s")

Gfx *func_1510EBB4(Gfx *gdl, s32 arg1, s32 arg2) {
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return gdl;
}
