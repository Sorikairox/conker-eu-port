#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P279: readable C for the hand asm (40 insns, sd zero x8 then sh of the diagonal). */
// mtx_scale_fixed: guScale straight into a fixed-point Mtx: m = diag(x, y, z, 1) in s15.16 (integer halves at
// +0x00, the fraction halves at +0x20). Each factor is truncated toward zero (trunc.w.s) after * 65536.
void func_150A80F0(Mtx *m, f32 x, f32 y, f32 z) {
    u16 *h = (u16 *) m;
    s32 i;
    s32 sx, sy, sz;

    for (i = 0; i < 32; i++) {
        h[i] = 0;
    }
    sx = (s32) (x * 65536.0f);
    sy = (s32) (y * 65536.0f);
    sz = (s32) (z * 65536.0f);
    h[0] = (u32) sx >> 16;  /* [0][0] integer */
    h[5] = (u32) sy >> 16;  /* [1][1] */
    h[10] = (u32) sz >> 16; /* [2][2] */
    h[15] = 1;              /* [3][3] = 1.0 */
    h[16] = sx;             /* [0][0] fraction */
    h[21] = sy;
    h[26] = sz;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D5900/func_150A80F0.s")
#endif
