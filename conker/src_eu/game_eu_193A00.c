#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P125 */
f32 fast_cosf(f32);
f32 fast_sinf(f32);

/* mesh_swing_update: swings n / 2 vertex pairs of a Vtx buffer by an angle (degrees, *angle): for k < n / 2 the
 * vertex rows[k] gets x = -cos * amp, y = sin * amp and the vertex rows[k + n / 2] x = cos * amp, y = sin * amp.
 * Then the angle moves by *speed per frame step (D_800BE9E4); at max or min it is clamped and the speed reversed.
 * fast_sinf / fast_cosf are sin / cos of radians. */
/* was func_151661F0 */
void mesh_swing_update(f32 *angle, s16 *vtx, f32 amp, f32 *speed, f32 max, f32 min, u8 *rows, u8 n) {
    f32 rad;
    f32 sp;
    f32 s;
    f32 c;
    s32 half;
    s32 k;

    rad = *angle * 0.017453292f;
    sp = *speed;
    s = fast_sinf(rad) * amp;
    c = fast_cosf(rad);
    half = (n >> 1) & 0xFF;
    for (k = 0; k < half; k++) {
        vtx[rows[k] * 8 + 0] = -(s16) (s32) (c * amp);
        vtx[rows[k] * 8 + 1] = (s32) s;
        vtx[rows[k + half] * 8 + 0] = (s32) (c * amp);
        vtx[rows[k + half] * 8 + 1] = (s32) s;
    }
    *angle += sp * (f32) D_800BE9E4;
    if (max <= *angle) {
        *speed = -sp;
        *angle = max;
    } else if (*angle <= min) {
        *speed = -sp;
        *angle = min;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_193A00/mesh_swing_update.s")
#endif
