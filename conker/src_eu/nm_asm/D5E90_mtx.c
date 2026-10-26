/*
 * NON_MATCHING C for two matrix helpers of the raw asm file asm/D5E90.s (P62):
 *   mtx_rotate_scale_3x3  rotation (three angles in degrees) times scale into the 3x3 part of a float matrix
 *                  (the US name; the EU code is the raw-word block at 0x150A9FEC);
 *   mtx_f_to_l_batch  n float matrices converted in place to the RSP's fixed-point Mtx.
 *
 * Built only with NON_MATCHING=1 (Makefile: NM_ASM_C_FUNCS_D5E90 line for these two, and the linker script line
 * that places D5E90_mtx.c.o); the asm copies are weakened so these definitions win.
 * The file must not contain the word G-L-O-B-A-L_ASM (see the Makefile note on nm_asm files).
 * Float operations are written in the asm's order: each line rounds like one mul.s / add.s.
 */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern f32 D_8009FAA0; /* pi / 180 */

/*
 * m[0..2][0..2] = rotation(x, y, z) scaled per row by (sx, sy, sz); row 3 and column 3 are left alone.
 * With cX = cos(x), sX = sin(x) (fast_cosf is cos, fast_sinf is sin):
 *   row 0 = sx * (cZ cY,                      sZ,      -cZ sY)
 *   row 1 = sy * (-cX sZ cY + sX sY,          cX cZ,    cX sZ sY + sX cY)
 *   row 2 = sz * ( sX sZ cY + cX sY,         -sX cZ,   -sX sZ sY + cX cY)
 * The order of each product and sum is the asm's.
 */
/* was func_150A9B0C */
void mtx_rotate_scale_3x3(f32 m[4][4], f32 x, f32 y, f32 z, f32 sx, f32 sy, f32 sz) {
    f32 cosX, sinX, cosY, sinY, cosZ, sinZ;
    f32 cxsz, sxsz; /* cos(x) * -sin(z), -sin(x) * -sin(z) */
    f32 m00, m02, m10, m11, m12, m20, m21, m22;

    x = x * D_8009FAA0;
    cosX = fast_cosf(x);
    sinX = fast_sinf(x);
    y = y * D_8009FAA0;
    cosY = fast_cosf(y);
    sinY = fast_sinf(y);
    z = z * D_8009FAA0;
    cosZ = fast_cosf(z);
    sinZ = fast_sinf(z);

    m11 = cosX * cosZ;
    m21 = -sinX * cosZ;
    cxsz = cosX * -sinZ;
    sxsz = -sinX * -sinZ;
    m00 = cosZ * cosY;
    m02 = cosZ * -sinY;

    m10 = cxsz * cosY + sinX * sinY;
    m12 = cxsz * -sinY + sinX * cosY;
    m20 = sxsz * cosY + cosX * sinY;
    m22 = sxsz * -sinY + cosX * cosY;

    m[0][0] = m00 * sx;
    m[0][1] = sinZ * sx;
    m[0][2] = m02 * sx;
    m[1][0] = m10 * sy;
    m[1][1] = m11 * sy;
    m[1][2] = m12 * sy;
    m[2][0] = m20 * sz;
    m[2][1] = m21 * sz;
    m[2][2] = m22 * sz;
}

/* cvt.w.s in the default FCSR mode (round to nearest, ties to even), for |f| < 2^31 */
static s32 nmMtxRound(f32 f) {
    if (f >= 8388608.0f || f <= -8388608.0f) {
        return (s32)f; /* already integral */
    }
    if (f >= 0.0f) {
        return (s32)((f + 8388608.0f) - 8388608.0f);
    }
    return -(s32)((-f + 8388608.0f) - 8388608.0f);
}

/*
 * In place: each of the n 64-byte float matrices becomes an Mtx (s16 integer parts at +0x00, u16 fractions at
 * +0x20, element (i, j) at 2 * (4 * i + j)). Only the 3x4 part is read (column 3 of rows 0..2 is taken as 0 and
 * element (3, 3) as 1.0). n is decremented before the test, so n = 0 runs 2^32 times like the asm.
 */
/* was func_150A9E64 */
void mtx_f_to_l_batch(f32 *m, s32 n) {
    s32 fx[4][3];
    s16 *ip;
    u16 *fp;
    s32 i;
    s32 j;

    do {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                fx[i][j] = nmMtxRound(m[i * 4 + j] * 65536.0f);
            }
        }
        ip = (s16 *)m;
        fp = (u16 *)m + 16;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                ip[i * 4 + j] = fx[i][j] >> 16;
                fp[i * 4 + j] = fx[i][j];
            }
            ip[i * 4 + 3] = (i == 3) ? 1 : 0;
            fp[i * 4 + 3] = 0;
        }
        m += 16;
        n--;
    } while (n != 0);
}
