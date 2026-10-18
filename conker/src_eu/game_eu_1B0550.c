#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B0550/func_15182D40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B0550/func_151831CC.s")

extern u8 D_800DE284[];
extern f32 D_8008D3F8[][6];

f32 func_151834C8(s32 arg0, s32 arg1) {
    f32 x;

    x = D_8008D3F8[D_800DE284[arg1]][0] * (f32)(arg0 * 40);
    if (x < 0.0f) {
        x = 0.0f;
    } else if (x > 39.0f) {
        x = 39.0f;
    }
    return x;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B0550/func_1518354C.s")
