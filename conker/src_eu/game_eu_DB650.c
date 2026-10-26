#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P64: approximate 2D distance between (x0, z0) and (x1, z1) (hand-written asm in the original):
 * |dx| + |dz| - min(|dx|, |dz|) / 2, an octagonal estimate of sqrt(dx^2 + dz^2). */
/* was func_150ADE40 */
s32 approx_dist2_int(s32 x0, s32 z0, s32 x1, s32 z1) {
    s32 dx = x1 - x0;
    s32 dz = z1 - z0;

    if (dx < 0) {
        dx = -dx;
    }
    if (dz < 0) {
        dz = -dz;
    }
    if (dz < dx) {
        return dx + dz - (dz >> 1);
    }
    return dx + dz - (dx >> 1);
}
