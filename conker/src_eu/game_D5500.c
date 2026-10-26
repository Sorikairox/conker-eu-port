#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// is this handwritten??
extern f32 g_mtxf_deg_to_rad; /* pi / 180; was D_8009FA90 */
/* Rotation matrix from three angles in degrees (g_mtxf_deg_to_rad = pi/180): with cX/sX the cos/sin of each,
 * row 0 = (cy cz, cy sz, -sy), row 1 = (sx sy cz - cx sz, sx sy sz + cx cz, sx cy),
 * row 2 = (cx sy cz + sx sz, cx sy sz - sx cz, cx cy); translation 0, w = 1. */
/* was func_150A8050 */
void mtxf_rotate_xyz_deg(f32 mtx[4][4], f32 arg1, f32 arg2, f32 arg3) {
    f32 cx, sx, cy, sy, cz, sz;
    f32 sxsy, cxsy;

    arg1 *= g_mtxf_deg_to_rad;
    cx = fast_cosf(arg1);
    sx = fast_sinf(arg1);
    arg2 *= g_mtxf_deg_to_rad;
    cy = fast_cosf(arg2);
    sy = fast_sinf(arg2);
    arg3 *= g_mtxf_deg_to_rad;
    cz = fast_cosf(arg3);
    sz = fast_sinf(arg3);
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