#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void guMtxIdentF(f32 (*mf)[4]) {
    mf[0][1] = 0.0f;
    mf[0][0] = 1.0f;
    mf[0][2] = 0.0f;
    mf[0][3] = 0.0f;
    mf[1][0] = 0.0f;
    mf[1][1] = 1.0f;
    mf[1][2] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][0] = 0.0f;
    mf[2][1] = 0.0f;
    mf[2][2] = 1.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/gu/guMtxIdentF/guMtxIdentF.s")
#endif
// NON-MATCHING: assume handwritten like OOT
// void guMtxIdentF(f32 mf[4][4]) {
//     if (0) {};
//     ((s32)mf[0][1]) = (s32)0;
//     mf[0][0] = 1;
//     dummy_label:;
//     ((s32)mf[0][2]) = 0;
//     ((s32)mf[0][3]) = 0;
//     ((s32)mf[1][0]) = 0;
//     mf[1][1] = 1;
//     ((s32)mf[1][2]) = 0;
//     ((s32)mf[1][3]) = 0;
//     ((s32)mf[2][0]) = 0;
//     ((s32)mf[2][1]) = 0;
//     mf[2][2] = 1;
//     ((s32)mf[2][3]) = 0;
//     ((s32)mf[3][0]) = 0;
//     ((s32)mf[3][1]) = 0;
//     ((s32)mf[3][2]) = 0;
//     mf[3][3] = 1;
// }
