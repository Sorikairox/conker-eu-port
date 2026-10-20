#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B8DB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B97C4.s")

s32 func_151B98C0(Mtx *arg0, u8 *arg1) {
    f32 mf[4][4];
    u8 *p;

    p = arg1;
    func_150A8050(mf, 0.0f, 0.0f, *(f32 *)(p + 0x170));
    mf[3][0] = *(f32 *)(p + 0x38);
    mf[3][1] = *(f32 *)(p + 0x3C);
    mf[3][2] = *(f32 *)(p + 0x40);
    mf[0][0] *= *(f32 *)(p + 0x18);
    mf[0][1] *= *(f32 *)(p + 0x18);
    mf[0][2] *= *(f32 *)(p + 0x18);
    mf[1][0] *= *(f32 *)(p + 0x1C);
    mf[1][1] *= *(f32 *)(p + 0x1C);
    mf[1][2] *= *(f32 *)(p + 0x1C);
    mf[2][0] *= *(f32 *)(p + 0x18);
    mf[2][1] *= *(f32 *)(p + 0x18);
    mf[2][2] *= *(f32 *)(p + 0x18);
    guMtxF2L(mf, arg0);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B99B8.s")

void func_151B9C10(f32 *arg0) {
    arg0[0x188 / 4] = 5.0f;
    arg0[0x18C / 4] = D_800AA94C;
    arg0[0x190 / 4] = D_800AA950;
}
