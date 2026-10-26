#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void mtx_transform_points(f32 **, f32 **, void *, s32);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, s32, f32 *, f32 *, f32 *, s32, s32, s32, f32);
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);
u8 *tracer_spawn(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, u8 argB, u8 *argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, s8 arg13, s32 arg14, f32 arg15, u8 arg16, s8 arg17, s32 arg18, u8 arg19, s32 arg1A);
struct225 *light_create_with_ctrl(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);
s32 attached_particle_spawn(u8 *, u8, f32 *, f32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
extern f32 D_800A18D0[3];    /* (-40, 0, 57): aim ray start, model space */
extern f32 D_800A18DC[3];    /* (-40, 0, 160): aim ray end */
extern f32 D_800A18E8[2][3]; /* muzzle points of the two barrels (+-17, 0, 570) */
extern f32 D_800A1900[2][3]; /* barrel tips (+-17, 0, 700) */
extern u8 D_800A1918[2];     /* barrel bones (2, 4) */
extern f32 D_800A191C;       /* 1 / 130 */
extern f32 D_800A1920, D_800A1924, D_800A1928; /* 2586, 1758, 0.001 */
extern f32 D_800A192C, D_800A1930; /* 1357, 0.1 */
extern f32 D_800A1934;       /* 1077 */

// gun_barrel_fire: shot from barrel `side` (0 / 1) of the gun object `obj` (model +0x1D4). Casts the aim ray (the
// model's D_800A18D0 -> D_800A18DC, transformed by the model matrix at +0x80) through func_150ACEA0; on a hit the
// tracer is aimed at the hit point moved by a random offset (vec2_from_angle_byte, up to 80 units), else along the aim
// direction. Spawns the tracer (tracer_spawn, its record is returned), a muzzle flash sprite at the muzzle point
// (light_create_with_ctrl: random frame 3..5, size 0x5A..0x66) and the barrel smoke (attached_particle_spawn from the bone
// D_800A1918[side]). room / owner are passed on to all three. Returns NULL without a model or for side >= 2.
/* was func_150EBEC0 */
u8 *gun_barrel_fire(u8 *obj, u8 side, u8 room, s32 owner) {
    f32 *src[2];
    f32 *dst[2];
    f32 *msrc;
    f32 *mdst;
    f32 start[3];
    f32 dir[3];
    f32 muzzle[3];
    f32 aim[3];
    f32 *tracerDir;
    f32 hitX, hitY, hitZ;
    f32 offX, offZ;
    f32 r1, r2;
    s32 ri;
    s32 r6, r34;
    f32 smoke[2];
    s32 flashPos[3];
    struct {
        u8 kind;  /* 3 */
        u8 alpha; /* 0xFF */
        s16 frame;
        u8 flags;
    } flash;
    u8 *tracer;

    if (obj == NULL) {
        return NULL;
    }
    if (side >= 2) {
        return NULL;
    }
    if (*(u8 **) (obj + 0x1D4) == NULL) {
        return NULL;
    }
    src[0] = D_800A18D0;
    src[1] = D_800A18DC;
    dst[0] = start;
    dst[1] = dir;
    mtx_transform_points(src, dst, *(u8 **) (obj + 0x1D4) + 0x80, 2);
    dir[0] -= start[0];
    dir[1] -= start[1];
    dir[2] -= start[2];
    msrc = D_800A18E8[side];
    mdst = muzzle;
    mtx_transform_points(&msrc, &mdst, *(u8 **) (obj + 0x1D4) + D_800A1918[side] * 0x40, 1);
    if (func_150ACEA0(start[0], start[1], start[2], dir[0], dir[1], dir[2], 0, 0, &hitX, &hitY, &hitZ, 0, 0, 0, 0.0f)) {
        ri = random_int();
        vec2_from_angle_byte(ri & 0xFF, random_float() * 80.0f, &offX, &offZ);
        hitX += offX;
        hitZ += offZ;
        aim[0] = hitX - muzzle[0];
        aim[1] = hitY - muzzle[1];
        aim[2] = hitZ - muzzle[2];
        tracerDir = aim;
    } else {
        tracerDir = dir;
    }
    r1 = random_float();
    r2 = random_float();
    random_int();
    tracer = tracer_spawn((u8 *) muzzle, (u8 *) tracerDir, NULL, NULL, 0, 0, 130.0f, D_800A191C, r1 * 18.0f + 29.0f,
                           r2 * 400.0f + 262.0f, 100.0f, 0xFF, obj, 1, 1, 0, 0, 0, 1, 3, 0x1A, 0.0f, 0xFF, -1, 0, room,
                           owner);
    flash.kind = 3;
    flash.alpha = 0xFF;
    flash.frame = (u32) random_int() % 3 + 3;
    flash.flags = 0;
    flashPos[0] = muzzle[0];
    flashPos[1] = muzzle[1];
    flashPos[2] = muzzle[2];
    light_create_with_ctrl((Header *) &flash, (Header2 *) flashPos, (u32) random_int() % 13 + 0x5A, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                  0, room, owner);
    smoke[1] = (random_float() * D_800A1920 + D_800A1924) * D_800A1928;
    smoke[0] = (random_float() * D_800A192C + 968.0f) * D_800A1930;
    r6 = random_int();
    r34 = random_int();
    attached_particle_spawn(obj, D_800A1918[side], D_800A18E8[side], D_800A1900[side], smoke, (u32) r6 % 6 + 6, (u32) r34 % 0x34 + 0xC1,
                  random_float() * D_800A1934 + 4000.0f, muzzle, 0xFF, 0, -1, room, owner);
    return tracer;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_119C50/gun_barrel_fire.s")
#endif

/* was func_150EC954 */
s32 gun_tracer_can_hit(u8 *arg0, u8 *arg1) {
    s32 temp_v0;
    if (arg0 == arg1) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0)) == 0) {
        return 0;
    }
    temp_v0 = (*(u8 *)((u8 *)arg0 + 4));
    if (temp_v0 == 0xFF) {
        return 0;
    }
    if ((temp_v0 == 0) || (temp_v0 == 1) || (temp_v0 == 2) || (temp_v0 == 3) || (temp_v0 == 4) || (temp_v0 == 0x28) || (temp_v0 == 0x77)) {
        return 1;
    }
    return 0;
}

/* was func_150EC9DC */
void fx_set_tint_white(s32 arg0) {
    surface_impact_effects(arg0, 1.0f, 1.0f, 1.0f, 0.0f, 0xFF, 0xFF, 0xFF);
}
