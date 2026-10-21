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

#ifdef NON_MATCHING
/* 4x4 f32 matrix product c = a * b (row-major, hand-written asm in the original). b is read completely
 * before anything is written, and each row of a before its row of c, so c may alias a or b. */
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]) {
    f32 m[4][4];
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m[i][j] = b[i][j];
        }
    }
    for (i = 0; i < 4; i++) {
        f32 r0 = a[i][0];
        f32 r1 = a[i][1];
        f32 r2 = a[i][2];
        f32 r3 = a[i][3];

        for (j = 0; j < 4; j++) {
            c[i][j] = r0 * m[0][j] + r1 * m[1][j] + r2 * m[2][j] + r3 * m[3][j];
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D5650/func_150A7A48.s")
#endif