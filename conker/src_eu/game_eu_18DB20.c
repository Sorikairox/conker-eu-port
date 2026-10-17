#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_15160310.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_151604E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_1516055C.s")

void func_eu_15160600(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_8008B484[arg0[0x14]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_15160648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/func_151607E4.s")
