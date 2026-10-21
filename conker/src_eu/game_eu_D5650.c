#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_150A7E40(f32 (*mf)[4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ) {
    *outX = (mf[0][0] * x) + (mf[1][0] * y) + ((mf[2][0] * z) + mf[3][0]);
    *outY = (mf[0][1] * x) + (mf[1][1] * y) + ((mf[2][1] * z) + mf[3][1]);
    *outZ = (mf[0][2] * x) + (mf[1][2] * y) + ((mf[2][2] * z) + mf[3][2]);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D5650/func_150A7E40.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D5650/func_150A7EE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D5650/func_150A7EF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D5650/func_150A7A48.s")
