#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* local copies of character_smoke_puff's rodata g_char_smoke_puff_pt / DC / E8 / F4 (its .s carries it) */
static const f32 sPuffPoint[3] = { 10.0f, -102.0f, 75.0f };
static const f32 sSparkEnd[3] = { 10.0f, -151.0f, 105.0f };
static const f32 sSegStart[3] = { -1.0f, -38.0f, 38.0f };
static const f32 sSegEnd[3] = { -26.0f, -23.0f, 51.0f };
s32 mtx_transform_points(s32 **, s32 *, s32, s32);
extern u8 g_char_smoke_bone; /* was D_80088F40 */
void bone_point_spark_spray(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
s32 tracer_spawn(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, struct127 *, s32, s32, s32, s32, s32,
                  s32, s32, s32, f32, s32, s32, s32, s32, s32);
void weapon_count_shot(struct127 *);
void muzzle_light_small_spawn(f32 *, u8, s32);
void bone_streak_fx_start(f32 *, f32 *, s32, struct127 *, f32, u8, s32);

// character_smoke_puff: smoke from a character obj (owner byte room / owner passed on). Takes its facing (obj_get_aim_vectors,
// 0.811) and either, with a bone matrix table (obj+0x1D4, entry g_char_smoke_bone), the transformed local points
// sPuffPoint (puff position), sSegStart / sSegEnd (a segment, stored as start + direction), or else a point 34 in
// front of the object (perpendicular of the flat facing, (0, 0, 1) when it has no flat part) and 49 up. Spawns the
// puff (tracer_spawn: 300, 1/300, 25..35, 400..600, 50, life 100..255, kind 0x35); with the bone table and unless
// obj+0x74 & 0xF == 0xF, also muzzle_light_small_spawn at the puff, bone_streak_fx_start along the segment, and on a coin flip
// bone_point_spark_spray between sPuffPoint and sSparkEnd.
/* was func_150FEDE0 */
void character_smoke_puff(struct127 *obj, u8 room, s32 owner) {
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

    weapon_count_shot(obj);
    obj_get_aim_vectors(obj, (s32) dir, (s32) tmp1, (s32) tmp2, 0.81100005f);
    if (*(s32 *) (o + 0x1D4) != 0) {
        tbl = *(s32 *) (o + 0x1D4) + (g_char_smoke_bone << 6);
        src[0] = sPuffPoint;
        src[1] = sSegStart;
        src[2] = sSegEnd;
        dst[0] = pos;
        dst[1] = seg0;
        dst[2] = seg1;
        mtx_transform_points((s32 **) src, (s32 *) dst, tbl, 3);
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
    r1 = random_float();
    r2 = random_float();
    tracer_spawn(pos, dir, 0, 0, 0, 0, 300.0f, 0.0033333334f, r1 * 10.0f + 25.0f, r2 * 200.0f + 400.0f, 50.0f,
                  (u32) random_int() % 156 + 100, obj, 1, 1, 0, 0, 1, 1, 0, 0x35, 0.0f, 0xFF, -1, 0, room, owner);
    if (*(s32 *) (o + 0x1D4) == 0) {
        return;
    }
    if ((o[0x74] & 0xF) == 0xF) {
        return;
    }
    muzzle_light_small_spawn(pos, room, owner);
    bone_streak_fx_start(seg0, seg1, tbl, obj, 1.0f, room, owner);
    if (random_int() & 1) {
        bone_point_spark_spray((s32) obj, g_char_smoke_bone, (s32) sPuffPoint, (s32) sSparkEnd, (s32) pos, room, owner);
    }
}
#define g_char_smoke_puff_pt sPuffPoint[0] /* character_smoke_point_get's reference */
/* was func_150FF148 */
void character_smoke_point_get(u8 *arg0, s32 arg1, s32 arg2) {
    s32 pad;
    s32 *sp20;
    s32 sp1C;
    s32 v;
    v = *(s32 *)(arg0 + 0x1D4) + (g_char_smoke_bone << 6);
    sp20 = (s32 *) &g_char_smoke_puff_pt;
    sp1C = arg2;
    mtx_transform_points(&sp20, &sp1C, v, 1);
}

/* P262: the C definition's exact types (game_eu_1306B0) */
void *attached_particle_spawn(u8 *, u8, f32 *, f32 *, f32 *, s16, u8, f32, u8 *, u8, s32, s16, u8, s32);

/* was func_150FF1A8 */
void bone_point_spark_spray(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    f32 v[2];
    s32 r[3];

    v[1] = random_float() * 1.001f + 0.60400003f;
    v[0] = random_float() * 5.9f + 14.1f;
    r[0] = random_int();
    r[1] = random_int();
    attached_particle_spawn((u8 *)arg0, arg1, (f32 *)arg2, (f32 *)arg3, v, (r[0] & 3) + 6, 0xFF, random_float() * 270.0f + 359.0f, (u8 *)arg4, 0xFF, 0, -1, arg5, arg6);
}
