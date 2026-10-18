#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F9CA0/func_150CBF80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F9CA0/func_150CCB48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F9CA0/func_150CCBC8.s")

s32 func_150CCDE4(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F9CA0/func_150CCF8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F9CA0/func_150CD1C4.s")
