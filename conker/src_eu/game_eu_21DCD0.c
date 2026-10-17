#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21DCD0/guMtxF2L2.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21DCD0/func_151F05C0.s")

void func_151F0648(Mtx *arg0) {
    f32 mf[4][4];

    func_151F05C0(mf);
    guMtxF2L2(mf, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21DCD0/guMtxL2F.s")
