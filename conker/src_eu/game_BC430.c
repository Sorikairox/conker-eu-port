#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_BC430/func_1508EF80.s")
// NON-MATCHING: only the stack slots of x and the cosf() spill differ
// extern f32 D_8009E050; // degrees to radians
//
// // rotate pos around center in the XZ plane by angle degrees
// void func_1508EF80(f32 *pos, f32 *center, f32 angle, f32 *out) {
//     f32 dx = pos[0] - center[0];
//     f32 dz = pos[2] - center[2];
//     f32 rad = angle * D_8009E050;
//     f32 x;
//     f32 z;
//
//     x = center[0] + (cosf(rad) * dx + sinf(rad) * dz);
//     z = cosf(rad) * dz + -sinf(rad) * dx + center[2];
//     out[0] = x;
//     out[2] = z;
// }
