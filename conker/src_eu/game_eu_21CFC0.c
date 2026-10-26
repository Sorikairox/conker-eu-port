#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* was func_151EF7B0 */
void game_clear_e9d00_flag(void) {
    D_800E9D00 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21CFC0/game_clear_e9d00_flag.s")
#endif