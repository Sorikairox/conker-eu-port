#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void func_1505327C(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);

#pragma GLOBAL_ASM("asm/nonmatchings/game_77AD0/func_1504A620.s")
// NON-MATCHING: work-in-progress...
// f32 func_1504A620(f32 arg0) {
//     f32 temp_f14;
//     f32 temp_f2;
//     f32 phi_f2;
//     f32 phi_f0;
//     s32 phi_v0;
//     f32 tmp0;
//
//     if (arg0 < 0.0f) {
//         return 0.0f;
//     }
//     if (arg0 == 0.0f) {
//         return 0.0f;
//     }
//
//     phi_f2 = 0.0f;
//
//     while (arg0 >= 2.0f ) {
//         arg0 = arg0 * 0.5f;
//         phi_f2 += D_800990B0;
//     }
//
//     tmp0 = D_800990B4;
//     while (arg0 < 1.0f) {
//         arg0 = arg0 * 2.0f;
//         phi_f2 -= tmp0;
//     }
//
//     temp_f14 = (phi_f2 - 1.0f) / (phi_f2 + 1.0f);
//     phi_f0 = 2.0f * temp_f14;
//     phi_v0 = 1;
//
//     do {
//         temp_f2 = phi_f2 + (phi_f0 / (f32) phi_v0);
//         phi_f2 = temp_f2;
//         phi_f0 = phi_f0 * (temp_f14 * temp_f14);
//         phi_v0 = phi_v0 + 2;
//     }
//     while (temp_f2 != phi_f2);
//
//     return temp_f2;
// }
