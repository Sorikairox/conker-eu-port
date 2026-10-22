#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6070.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6324.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A661C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A66F0.s")

#ifdef NON_MATCHING
void func_150A6834(void) {

}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6834.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800D9F40; /* screen width (also the near-depth bound here) */
s32 func_150A6A48(s32, s32, s32 *, s32, s32, s32, s32, s32);

/* cvt.w.s with the default FCSR mode: round to nearest, ties to even */
#define VIEW6840_RINT(f)                                                                             \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32)(f)                                            \
     : ((f) >= 0.0f) ? (s32)(((f) + 8388608.0f) - 8388608.0f)                                       \
                     : -(s32)((-(f) + 8388608.0f) - 8388608.0f))

/*
 * P38: view test of a sphere / box (hand asm, FR=1 odd FPRs as singles). cam: camera record (D_800BE628 + i * 0x180,
 * side planes at +0x88..+0xB4), m: view matrix (4x4 floats). (x, y, z) is transformed by m into (u, v, w):
 * outside when w - r > -D_800D9F40 (in front of the near bound), w + r < -far, or a side plane test
 * u * p0 + w * p2 < -r (planes +0x88/+0x90, +0x94/+0x9C) or v * p0 + w * p2 < -ry (+0xA4/+0xA8, +0xB0/+0xB4)
 * (NaN counts as outside). Returns 0 when outside, else round(w), or 1 when that is 0.
 */
s32 func_150A6840(s32 cam, s32 *mtx, f32 x, f32 y, f32 z, f32 r, f32 ry, f32 far) {
    f32 *m = (f32 *)mtx;
    u8 *c = (u8 *)cam;
    f32 u, v, w;
    s32 ret;

    w = (m[2] * x + m[6] * y) + (m[10] * z + m[14]);
    if (!(w - r <= -D_800D9F40)) {
        return 0;
    }
    if (w + r < -far) {
        return 0;
    }
    u = (m[0] * x + m[4] * y) + (m[8] * z + m[12]);
    if (!(u * *(f32 *)(c + 0x88) + w * *(f32 *)(c + 0x90) >= -r)) {
        return 0;
    }
    if (!(u * *(f32 *)(c + 0x94) + w * *(f32 *)(c + 0x9C) >= -r)) {
        return 0;
    }
    v = (m[1] * x + m[5] * y) + (m[9] * z + m[13]);
    if (!(v * *(f32 *)(c + 0xA4) + w * *(f32 *)(c + 0xA8) >= -ry)) {
        return 0;
    }
    if (!(v * *(f32 *)(c + 0xB0) + w * *(f32 *)(c + 0xB4) >= -ry)) {
        return 0;
    }
    ret = VIEW6840_RINT(w);
    if (ret == 0) {
        ret = 1;
    }
    return ret;
}

/* func_150A6A48(a0, a1, a2, 0, a0, a1, -10000, a3) (same .s as func_150A6840) */
s32 func_150A69A8(s32 arg0, s32 arg1, s32 *arg2, s32 arg3) {
    return func_150A6A48(arg0, arg1, arg2, 0, arg0, arg1, -10000, arg3);
}

#pragma GLOBAL_ASM("src_eu/nm_asm/func_150A6840_tail.s")
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6840.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A69E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6A48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6C40.s")
