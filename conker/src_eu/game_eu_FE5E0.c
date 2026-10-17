#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D0DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D13A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D15F4.s")

extern f32 D_800A0C64;

s32 func_150D16C4(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x74)) = (f32) (((func_150ADA68() * 150.0f) + 350.0f) * D_800A0C64);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D1714.s")
