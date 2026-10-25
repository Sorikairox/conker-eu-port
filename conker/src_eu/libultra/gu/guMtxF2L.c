#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P279: readable C for libultra's hand-asm guMtxF2L (guMtxF2L.s: 16 unrolled cvt.w.s, round to nearest even in the
 * default FCSR mode, not the truncating C cast of mtxutil.c). */
/* mtx_rint: cvt.w.s in the default mode (ties to even) for |f| < 2^31, as VTX_WAVE_RINT in game_eu_D4C90.c */
#define MTX_RINT(f)                                                                                        \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32) (f)                                                 \
     : ((f) >= 0.0f) ? (s32) (((f) + 8388608.0f) - 8388608.0f)                                            \
                     : -(s32) ((-(f) + 8388608.0f) - 8388608.0f))

// guMtxF2L: float 4x4 matrix to the RSP fixed-point Mtx: element k (row-major) * 65536 rounded to s15.16; its
// integer half goes to halfword k, its fraction half to halfword 16 + k.
void guMtxF2L(float mf[4][4], Mtx *m) {
    u16 *h = (u16 *) m;
    s32 k;

    for (k = 0; k < 16; k++) {
        f32 f = mf[k >> 2][k & 3] * 65536.0f;
        s32 v = MTX_RINT(f);

        h[16 + k] = v;
        h[k] = (u32) v >> 16;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/gu/guMtxF2L/guMtxF2L.s")
#endif
