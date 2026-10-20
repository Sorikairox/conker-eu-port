#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8140/func_1518A930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8140/func_1518AB64.s")

s32 func_1518AE84(Mtx *arg0, u8 *arg1) {
    f32 *r;
    f32 mf[4][4];

    r = (f32 *)(arg1 + 0x100);
    func_150A8050(mf, r[0], r[1], r[2]);
    mf[3][0] = *(f32 *)(arg1 + 0x48);
    mf[3][1] = *(f32 *)(arg1 + 0x4C);
    mf[3][2] = *(f32 *)(arg1 + 0x50);
    mf[0][0] *= r[3];
    mf[0][1] *= r[3];
    mf[0][2] *= r[3];
    mf[1][0] *= r[3];
    mf[1][1] *= r[3];
    mf[1][2] *= r[3];
    mf[2][0] *= r[3];
    mf[2][1] *= r[3];
    mf[2][2] *= r[3];
    guMtxF2L(mf, arg0);
    return 1;
}
