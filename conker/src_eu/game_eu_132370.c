#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_15104B60(s32 arg0, s32 arg1, f32 arg2) { /* P95: f32 (float bits were passed as an int) */
#else
void func_15104B60(s32 arg0, s32 arg1, s32 arg2) {
#endif
}

s32 func_15104B74(s32 arg0, s32 arg1) {
    return 1;
}

void func_15104B88(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}

s32 func_15104BA0(s32 arg0, s32 arg1) {
    return 1;
}

#ifdef NON_MATCHING
void func_1510F800(s32 arg0);
s32 func_150A3F50(s32, s32);
/* floor triangles found by func_150A3F50 (16-byte records) */
typedef struct {
    s32 h;      /* height, 1/256 units */
    u8 **vtx;   /* three vertex bases */
    s32 off;    /* byte offset of the s16 x, y, z in each vertex */
    s32 pad;
} FloorHit4BB4;
extern FloorHit4BB4 D_800D3720[];
extern f32 D_800A2740; /* 10000.0 */

// floor_height_below: floor height at (x, z) closest to `y`. func_150A3F50 lists the floor triangles under the
// point in D_800D3720; those whose third vertex lies on the positive side of the edge from vertex 0 to 1 (x / z
// plane) are kept, and of these the one whose height (h / 256) is nearest to y is written to *out. Returns 0
// when nothing is found, else 1.
s32 func_15104BB4(f32 x, f32 z, f32 y, f32 *out) {
    s32 list[26];
    f32 vz[3];
    f32 vx[3];
    s32 n, cnt, i, k;
    s32 best;
    f32 bestd, d;
    f32 ex, ez, c, side;
    s16 *v;

    func_1510F800(0);
    n = func_150A3F50((s32) x, (s32) z);
    if (n == 0) {
        return 0;
    }
    cnt = 0;
    for (i = 0; i < n; i++) {
        for (k = 0; k < 3; k++) {
            v = (s16 *) (D_800D3720[i].vtx[k] + D_800D3720[i].off);
            vx[k] = v[0];
            vz[k] = v[2];
        }
        ex = vx[0] - vx[1];
        ez = vz[1] - vz[0];
        c = -(vz[0] * ex + ez * vx[0]);
        side = (vz[2] * ex + ez * vx[2]) + c;
        if (0.0f < side) {
            list[cnt++] = i;
        }
    }
    if (cnt == 0) {
        return 0;
    }
    best = -1;
    bestd = D_800A2740;
    for (i = 0; i < cnt; i++) {
        d = D_800D3720[list[i]].h * 0.00390625f - y;
        if (d < 0.0f) {
            d = -d;
        }
        if (d < bestd || best == -1) {
            bestd = d;
            best = list[i];
        }
    }
    *out = D_800D3720[best].h * 0.00390625f;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_132370/func_15104BB4.s")
#endif
