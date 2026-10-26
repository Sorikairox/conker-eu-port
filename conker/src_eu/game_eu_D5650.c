#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150A7E40 */
void mtxf_transform_point(f32 (*mf)[4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ) {
    *outX = (mf[0][0] * x) + (mf[1][0] * y) + ((mf[2][0] * z) + mf[3][0]);
    *outY = (mf[0][1] * x) + (mf[1][1] * y) + ((mf[2][1] * z) + mf[3][1]);
    *outZ = (mf[0][2] * x) + (mf[1][2] * y) + ((mf[2][2] * z) + mf[3][2]);
}
/* matrix_transform_point_w: hand-asm trampoline in the original (calls mtxf_transform_point with $ra set to the extra
 * entry mtxf_transform_point_w_tail, which returns to the real caller). Transforms (x, y, z, 1) by the 4x4 matrix mf like
 * mtxf_transform_point and also writes the fourth (w) component: same summation order as the asm. */
/* was func_150A7EE0 */
void mtxf_transform_point_w(f32 (*mf)[4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ, f32 *outW) {
    mtxf_transform_point(mf, x, y, z, outX, outY, outZ);
    *outW = (mf[0][3] * x) + (mf[1][3] * y) + ((mf[2][3] * z) + mf[3][3]);
}

// matrix_transform_point_w_tail: not a function of its own. In the original it is the second half of the
// mtxf_transform_point_w trampoline (mtxf_transform_point returns into it with f0 / f2 / f4 = x / y / z still live; it computes
// w = m[0][3] * x + m[1][3] * y + m[2][3] * z + m[3][3] into the 8th argument and returns through $t9). The
// NON_MATCHING mtxf_transform_point_w computes w itself, so nothing reaches this entry; no other code references it.

/* 4x4 f32 matrix product c = a * b (row-major, hand-written asm in the original). b is read completely
 * before anything is written, and each row of a before its row of c, so c may alias a or b. */
/* was func_150A7A48 */
void mtxf_mul(f32 a[4][4], f32 b[4][4], f32 c[4][4]) {
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