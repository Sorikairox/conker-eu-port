#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* local copies of func_150FEDE0's rodata D_800A23D0 / DC / E8 / F4 (its .s carries it) */
static const f32 sPuffPoint[3] = { 10.0f, -102.0f, 75.0f };
static const f32 sSparkEnd[3] = { 10.0f, -151.0f, 105.0f };
static const f32 sSegStart[3] = { -1.0f, -38.0f, 38.0f };
static const f32 sSegEnd[3] = { -26.0f, -23.0f, 51.0f };
s32 func_15145EA4(s32 **, s32 *, s32, s32);
extern u8 D_80088F40;
void func_150FF1A8(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
s32 func_151C284C(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, struct127 *, s32, s32, s32, s32, s32,
                  s32, s32, s32, f32, s32, s32, s32, s32, s32);
void func_151D56F8(struct127 *);
void func_151D44C4(f32 *, u8, s32);
void func_151D49B8(f32 *, f32 *, s32, struct127 *, f32, u8, s32);
#endif

#ifdef NON_MATCHING
// character_smoke_puff: smoke from a character obj (owner byte room / owner passed on). Takes its facing (func_15145740,
// 0.811) and either, with a bone matrix table (obj+0x1D4, entry D_80088F40), the transformed local points
// sPuffPoint (puff position), sSegStart / sSegEnd (a segment, stored as start + direction), or else a point 34 in
// front of the object (perpendicular of the flat facing, (0, 0, 1) when it has no flat part) and 49 up. Spawns the
// puff (func_151C284C: 300, 1/300, 25..35, 400..600, 50, life 100..255, kind 0x35); with the bone table and unless
// obj+0x74 & 0xF == 0xF, also func_151D44C4 at the puff, func_151D49B8 along the segment, and on a coin flip
// func_150FF1A8 between sPuffPoint and sSparkEnd.
void func_150FEDE0(struct127 *obj, u8 room, s32 owner) {
    const f32 *src[3];
    f32 *dst[3];
    f32 pos[3];
    f32 dir[3];
    f32 tmp1[3];
    f32 tmp2[3];
    f32 seg0[3];
    f32 seg1[3];
    s32 tbl;
    f32 x;
    f32 z;
    f32 inv;
    f32 sx;
    f32 sz;
    f32 r1;
    f32 r2;
    u8 *o = (u8 *) obj;

    func_151D56F8(obj);
    func_15145740(obj, (s32) dir, (s32) tmp1, (s32) tmp2, 0.81100005f);
    if (*(s32 *) (o + 0x1D4) != 0) {
        tbl = *(s32 *) (o + 0x1D4) + (D_80088F40 << 6);
        src[0] = sPuffPoint;
        src[1] = sSegStart;
        src[2] = sSegEnd;
        dst[0] = pos;
        dst[1] = seg0;
        dst[2] = seg1;
        func_15145EA4((s32 **) src, (s32 *) dst, tbl, 3);
        seg1[0] = seg1[0] - seg0[0];
        seg1[1] = seg1[1] - seg0[1];
        seg1[2] = seg1[2] - seg0[2];
    } else {
        tbl = 0;
        x = dir[0];
        z = dir[2];
        if (0.0001f < fabsf(x) || 0.0001f < fabsf(z)) {
            inv = 1.0f / sqrtf(x * x + z * z);
            sz = z * inv;
            sx = -x * inv;
        } else {
            sz = 1.0f;
            sx = 0.0f;
        }
        pos[0] = *(f32 *) (o + 0x14) + 34.0f * sx;
        pos[1] = *(f32 *) (o + 0x18) + 49.0f;
        pos[2] = *(f32 *) (o + 0x1C) + 34.0f * sz;
    }
    r1 = func_150ADA68();
    r2 = func_150ADA68();
    func_151C284C(pos, dir, 0, 0, 0, 0, 300.0f, 0.0033333334f, r1 * 10.0f + 25.0f, r2 * 200.0f + 400.0f, 50.0f,
                  (u32) func_150ADA20() % 156 + 100, obj, 1, 1, 0, 0, 1, 1, 0, 0x35, 0.0f, 0xFF, -1, 0, room, owner);
    if (*(s32 *) (o + 0x1D4) == 0) {
        return;
    }
    if ((o[0x74] & 0xF) == 0xF) {
        return;
    }
    func_151D44C4(pos, room, owner);
    func_151D49B8(seg0, seg1, tbl, obj, 1.0f, room, owner);
    if (func_150ADA20() & 1) {
        func_150FF1A8((s32) obj, D_80088F40, (s32) sPuffPoint, (s32) sSparkEnd, (s32) pos, room, owner);
    }
}
#define D_800A23D0 sPuffPoint[0] /* func_150FF148's reference */
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12C5F0/func_150FEDE0.s")

extern s32 D_800A23D0;
#endif
#ifndef NON_MATCHING
s32 func_15145EA4(s32 **, s32 *, s32, s32);
extern u8 D_80088F40;
#endif
void func_150FF148(u8 *arg0, s32 arg1, s32 arg2) {
    s32 pad;
    s32 *sp20;
    s32 sp1C;
    s32 v;
    v = *(s32 *)(arg0 + 0x1D4) + (D_80088F40 << 6);
    sp20 = (s32 *) &D_800A23D0;
    sp1C = arg2;
    func_15145EA4(&sp20, &sp1C, v, 1);
}

#ifdef NON_MATCHING /* P262: the C definition's exact types (game_eu_1306B0) */
void *func_151030B8(u8 *, u8, f32 *, f32 *, f32 *, s16, u8, f32, u8 *, u8, s32, s16, u8, s32);
#else
s32 func_151030B8(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
#endif

void func_150FF1A8(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    f32 v[2];
    s32 r[3];

    v[1] = func_150ADA68() * 1.001f + 0.60400003f;
    v[0] = func_150ADA68() * 5.9f + 14.1f;
    r[0] = func_150ADA20();
    r[1] = func_150ADA20();
    func_151030B8((u8 *)arg0, arg1, (f32 *)arg2, (f32 *)arg3, v, (r[0] & 3) + 6, 0xFF, func_150ADA68() * 270.0f + 359.0f, (u8 *)arg4, 0xFF, 0, -1, arg5, arg6);
}
