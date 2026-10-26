#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// is this handwritten??
#ifdef NON_MATCHING
extern f32 D_8009FA90; /* pi / 180 */
/* Rotation matrix from three angles in degrees (D_8009FA90 = pi/180): with cX/sX the cos/sin of each,
 * row 0 = (cy cz, cy sz, -sy), row 1 = (sx sy cz - cx sz, sx sy sz + cx cz, sx cy),
 * row 2 = (cx sy cz + sx sz, cx sy sz - sx cz, cx cy); translation 0, w = 1. */
/* was func_150A8050 */
void mtxf_rotate_xyz_deg(f32 mtx[4][4], f32 arg1, f32 arg2, f32 arg3) {
    f32 cx, sx, cy, sy, cz, sz;
    f32 sxsy, cxsy;

    arg1 *= D_8009FA90;
    cx = func_150AD780(arg1);
    sx = func_150AD78C(arg1);
    arg2 *= D_8009FA90;
    cy = func_150AD780(arg2);
    sy = func_150AD78C(arg2);
    arg3 *= D_8009FA90;
    cz = func_150AD780(arg3);
    sz = func_150AD78C(arg3);
    sxsy = sx * sy;
    cxsy = cx * sy;
    mtx[0][0] = cy * cz;
    mtx[0][1] = cy * sz;
    mtx[0][2] = -sy;
    mtx[0][3] = 0.0f;
    mtx[1][0] = sxsy * cz - cx * sz;
    mtx[1][1] = sxsy * sz + cx * cz;
    mtx[1][2] = sx * cy;
    mtx[1][3] = 0.0f;
    mtx[2][0] = cxsy * cz + sx * sz;
    mtx[2][1] = cxsy * sz - sx * cz;
    mtx[2][2] = cx * cy;
    mtx[2][3] = 0.0f;
    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = 0.0f;
    mtx[3][3] = 1.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5500/mtxf_rotate_xyz_deg.s")
#endif