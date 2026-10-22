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

/* P54: func_150A6840_tail.s no longer needed (func_150A6A48 is C) */
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6840.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A69E0.s")

#ifdef NON_MATCHING
/*
 * P54: func_150A6A48 (hand asm): the world objects (D_800DBEF4, D_800DC320 of them, 0xA0 bytes) whose box
 * (+0x10 / +0x12 / +0x14 centre, +0x50 x/z half size, +0x52 y half size) overlaps (x .. x2, z .. z2) and, unless
 * +0x4F & 0x40, (y .. y2), all bounds strict; skipped: +0x6E != 0, +0x4F & 0x60 == 0x20, index n - 1.
 * Indices with +0x4F & 0x60 == 0 go to the u16 list D_800D3C00 (the count is returned), the others (0x40 / 0x60)
 * to D_800D3C50 (count in *outCount).
 */
extern s32 D_800D3C00;
extern s32 D_800D3C50;

s32 func_150A6A48(s32 x, s32 z, s32 *outCount, s32 n, s32 x2, s32 z2, s32 y, s32 y2) {
    u16 *l0 = (u16 *)&D_800D3C00;
    u16 *l1 = (u16 *)&D_800D3C50;
    u8 *obj, *end;
    s32 n0 = 0, n1 = 0, i = 0;
    s32 k, r, c;

    *outCount = 0;
    if (D_800DC320 == 0) return 0;
    obj = (u8 *)D_800DBEF4;
    end = obj + (s32)((u32)D_800DC320 * 0xA0u);
    do {
        if (obj[0x6E] != 0) goto next;
        k = obj[0x4F] & 0x60;
        if (k == 0x20) goto next;
        r = *(u16 *)(obj + 0x50);
        c = *(s16 *)(obj + 0x10);
        if (!(c - r < x2) || !(x < c + r)) goto next;
        c = *(s16 *)(obj + 0x14);
        if (!(c - r < z2) || !(z < c + r)) goto next;
        if ((obj[0x4F] & 0x40) != 0x40) {
            r = *(u16 *)(obj + 0x52);
            c = *(s16 *)(obj + 0x12);
            if (!(c - r < y2) || !(y < c + r)) goto next;
        }
        if (i == n - 1) goto next;
        if (k != 0) {
            n1++;
            *l1++ = i;
        } else {
            n0++;
            *l0++ = i;
        }
    next:
        obj += 0xA0;
        i++;
    } while (obj != end);
    *outCount = n1;
    return n0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6A48.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_D3880/func_150A6C40.s")
