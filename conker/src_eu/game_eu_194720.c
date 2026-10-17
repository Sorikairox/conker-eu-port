#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_194720/func_15166F10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_194720/func_eu_151670C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_194720/func_151672D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_194720/func_151674DC.s")

Gfx *func_15167548(Gfx *arg0, s32 arg1, s32 arg2) {
    gSPMatrix(arg0++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return arg0;
}
