#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* Hand asm in the original: fixed-point rotation matrix from three angles in degrees (rx, ry, rz; 0.017453292 = pi/180):
 * row 0 = (cy cz, cy sz, -sy), row 1 = (sx sy cz - cx sz, sx sy sz + cx cz, sx cy),
 * row 2 = (cx sy cz + sx sz, cx sy sz - sx cz, cx cy), no translation. The asm keeps the angles in f20-f30 (saved). */
void func_150A82D0(Mtx *m, f32 rx, f32 ry, f32 rz) {
    s16 *h = (s16 *)m;
    f32 v[12];
    f32 cx, sx, cy, sy, cz, sz, t;
    s32 i, k;

    rx *= 0.017453292f;
    cx = cosf(rx);
    sx = sinf(rx);
    ry *= 0.017453292f;
    cy = cosf(ry);
    sy = sinf(ry);
    rz *= 0.017453292f;
    cz = cosf(rz);
    sz = sinf(rz);
    v[0] = cy * cz;
    v[1] = cy * sz;
    v[2] = -sy;
    v[3] = 0.0f;
    t = sx * sy;
    v[4] = t * cz - cx * sz;
    v[5] = t * sz + cx * cz;
    v[6] = sx * cy;
    v[7] = 0.0f;
    t = cx * sy;
    v[8] = t * cz + sx * sz;
    v[9] = t * sz - sx * cz;
    v[10] = cx * cy;
    v[11] = 0.0f;
    for (i = 0; i < 12; i++) {
        k = (s32)(v[i] * 65536.0f);
        h[i] = k >> 16;
        h[i + 16] = k;
    }
    h[12] = 0;
    h[13] = 0;
    h[14] = 0;
    h[15] = 1;
    h[28] = 0;
    h[29] = 0;
    h[30] = 0;
    h[31] = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D5AE0/func_150A82D0.s")
#endif