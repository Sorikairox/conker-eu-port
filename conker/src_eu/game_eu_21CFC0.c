#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_151EF7B0(void) {
    D_800E9D00 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21CFC0/func_151EF7B0.s")
#endif