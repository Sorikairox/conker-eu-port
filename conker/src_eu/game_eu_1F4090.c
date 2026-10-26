#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P188 */
s32 obj_sub_counter_positive(u8 *);
void weapon_count_shot(u8 *arg0);
s32 model_node_points_to_world(u8 *, u8 *, s32, f32 **, f32 **, s32);
void mtx_transform_points(f32 **, f32 **, void *, s32);
void weapon_find_aim_target(u8 *, u8 *, void *, void *, void *, u8 *, u8 *, u8 **, u8 **, u8 *);
void muzzle_light_small_spawn(u8 *, u8, s32);
void bone_streak_fx_start(u8 *, u8 *, s32, u8 *, f32, u8, s32);
void gun_side_spark_spray(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5);
u8 *tracer_spawn(u8 *, u8 *, u8 *, u8 *, u8, s32, f32, f32, f32, f32, f32, u8, u8 *, u8, u8, u8, u8, u8, u8, s8, s32, f32, u8, s8, s32, u8, s32);
extern u32 g_gun_side_bone_offsets[]; /* [2 side] bone matrix byte offset; was D_800AAEE0 */
extern u8 g_gun_side_muzzle_pts[];  /* [2 side] f32[3] muzzle point; was D_800AAEE8 */
extern u8 g_gun_side_aim_pts[];  /* [2 side] f32[3] aim point (with `aimed`); was D_800AAF00 */
extern u8 g_gun_side_second_pts[];  /* [2 side] f32[3] second point; was D_800AAF18 */
extern u8 g_gun_side_third_pts[];  /* [2 side] f32[3] third point (direction = third - second); was D_800AAF30 */
extern u8 g_gun_side_shot_start_pts[];  /* [2 side] f32[3] shot start point; was D_800AAF48 */
extern f32 g_gun_fire_aim_param;   /* obj_get_aim_vectors parameter; was D_800AAFD8 */
extern f32 g_gun_fire_min_dir;   /* smallest direction component for a side offset; was D_800AAFDC */
extern f32 g_gun_fire_tracer_k;   /* shot parameter (1 / 300); was D_800AAFE0 */
extern u8 g_fx_lod_shift_players; /* was D_800DCE50 */

/*
 * object_gun_fire: P188: fires side `side` (0 / 1) of obj's gun (not while obj_sub_counter_positive says it is busy).
 * With a bone matrix (obj +0x1D4) the muzzle, second, third and shot-start points of the side (g_gun_side_muzzle_pts /
 * g_gun_side_second_pts / g_gun_side_third_pts / g_gun_side_shot_start_pts, plus the aim point g_gun_side_aim_pts when `aimed`) go to world space by the bone
 * (model_node_points_to_world when an attachment `att` is given, which can refuse, else mtx_transform_points); the tracer direction is
 * third - second and, when aimed, the aim direction is aim - muzzle. Without matrices (only when not aimed) the
 * muzzle is the object position +0x14.. + 49 up and 34 to the side (left for side 0) of the direction
 * obj_get_aim_vectors gave, which also becomes the shot start. Then weapon_find_aim_target (impact / target search), a sound
 * when the object has one (+0x318: rumble_request with a random 11..21 pitch value and voice 1 << +0x23D), and with
 * matrices and a model that is not hidden (+0x74 & 0xF != 15): the muzzle puff (muzzle_light_small_spawn), the tracer
 * (bone_streak_fx_start) and the shot (gun_side_spark_spray), each always when aimed, otherwise only by chance (puff / tracer: 1
 * in 2 and single-player-ish modes g_last_player_index < 2; shot: random & the g_fx_lod_shift_players mask is 0), and the projectile
 * (tracer_spawn: speed 300, random life / size, kind 26). The asm returns tracer_spawn's result (0 on the early
 * exits) but no caller reads it and game_eu_51190 declares it void, so it is void here (one wasm signature).
 */
/* was func_151C62D0 */
void object_gun_fire(u8 *obj, u8 side, s32 aimed_, u8 *att, s32 kind, s32 flag, s32 arg6) {
    f32 *src[5];
    f32 *dst[5];
    f32 aim[3];      /* sp328 */
    f32 muzzle[3];   /* sp340 */
    f32 start[3];    /* sp316 */
    f32 second[3];   /* sp268 */
    f32 dir[3];      /* sp256 */
    f32 out280[3];
    f32 out228[3];
    f32 out304[3];
    f32 out292[3];
    u8 *hit244;
    u8 *hit240;
    u8 *bone;
    structEU_151D8E18 snd;
    u8 aimed = aimed_;
    f32 x, z, inv, px, pz, off;
    f32 r1, r2;
    u32 r;
    s32 n, mask;

    if (obj == NULL) {
        return;
    }
    if (side >= 2) {
        return;
    }
    if (obj_sub_counter_positive(obj) != 0) {
        return;
    }
    weapon_count_shot(obj);
    if (!aimed) {
        obj_get_aim_vectors((struct127 *) obj, (s32) aim, (s32) out280, (s32) out228, g_gun_fire_aim_param);
    }
    if (*(u8 **) (obj + 0x1D4) != NULL) {
        bone = *(u8 **) (obj + 0x1D4) + g_gun_side_bone_offsets[side];
        dst[0] = muzzle;
        dst[1] = second;
        dst[2] = dir;
        dst[3] = start;
        dst[4] = aim;
        src[0] = (f32 *) (g_gun_side_muzzle_pts + side * 12);
        src[1] = (f32 *) (g_gun_side_second_pts + side * 12);
        src[2] = (f32 *) (g_gun_side_third_pts + side * 12);
        src[3] = (f32 *) (g_gun_side_shot_start_pts + side * 12);
        src[4] = (f32 *) (g_gun_side_aim_pts + side * 12);
        if (att != NULL) {
            if (model_node_points_to_world(obj, att, 0, src, dst, aimed ? 5 : 4) == 0) {
                return;
            }
        } else {
            mtx_transform_points(src, dst, bone, aimed ? 5 : 4);
        }
        dir[0] -= second[0];
        dir[1] -= second[1];
        dir[2] -= second[2];
        if (aimed) {
            aim[0] -= muzzle[0];
            aim[1] -= muzzle[1];
            aim[2] -= muzzle[2];
        }
    } else {
        if (aimed) {
            return;
        }
        x = aim[0];
        z = aim[2];
        if (g_gun_fire_min_dir < fabsf(x) || g_gun_fire_min_dir < fabsf(z)) {
            inv = 1.0f / sqrtf(x * x + z * z);
            pz = z * inv;
            px = -x * inv;
        } else {
            pz = 1.0f;
            px = 0.0f;
        }
        off = side ? 34.0f : -34.0f;
        muzzle[0] = *(f32 *) (obj + 0x14) + off * px;
        muzzle[1] = *(f32 *) (obj + 0x18) + 49.0f;
        muzzle[2] = *(f32 *) (obj + 0x1C) + off * pz;
        start[0] = muzzle[0];
        start[1] = muzzle[1];
        start[2] = muzzle[2];
    }
    weapon_find_aim_target(obj, (u8 *) muzzle, aim, out280, out228, (u8 *) out304, (u8 *) out292, &hit244, &hit240,
                  (u8 *) start);
    if (*(u8 **) (obj + 0x318) != NULL) {
        snd.unk0 = 1;
        snd.unk2 = (u32) random_int() % 11 + 11;
        snd.unk5 = 1 << (*(u8 **) (obj + 0x318))[0x23D];
        random_int();
        snd.unk4 = 8;
        snd.unk6 = -1;
        rumble_request(&snd, 0, 255, 1);
    }
    if (*(u8 **) (obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 15) {
        if (aimed || (g_last_player_index < 2 && (random_int() & 1))) {
            muzzle_light_small_spawn((u8 *) muzzle, flag, arg6);
        }
        if (aimed || g_last_player_index < 2) {
            if (random_int() & 1) {
                bone_streak_fx_start((u8 *) second, (u8 *) dir, (s32) bone, obj, 1.0f, flag, arg6);
            }
        }
        mask = 1;
        for (n = g_fx_lod_shift_players; n != 0; n--) {
            mask |= 1 << n;
        }
        if (aimed || !(random_int() & mask)) {
            gun_side_spark_spray((s32) obj, side, (s32) muzzle, kind, flag, arg6);
        }
    }
    r1 = random_float();
    r2 = random_float();
    r = random_int();
    tracer_spawn((u8 *) start, (u8 *) aim, hit244, hit240, 1, 0, 300.0f, g_gun_fire_tracer_k, r1 * 10.0f + 25.0f,
                               r2 * 150.0f + 400.0f, 50.0f, r % 156 + 100, obj, !aimed, !aimed, !aimed, 8, !aimed, 1,
                               0, 26, 0.0f, 255, -1, 0, flag, arg6);
}

/* P160: object_bone_point reads three arguments (the matching callers below leave a 4th in a3) */
void object_bone_point(u8 *obj, f32 *out, u8 kind);

// object_bone_point_0: g_obj_point_fx_fns handler 0 (object_point_effect_spawn): bone point 0 of obj into out (arg1 unused)
/* was func_151C6F24 */
void object_bone_point_0(u8 *obj, s32 arg1, f32 *out) {
    object_bone_point(obj, out, 0);
}

// object_bone_point_1: g_obj_point_fx_fns handler 1 (object_point_effect_spawn): bone point 1 of obj into out (arg1 unused)
/* was func_151C6F50 */
void object_bone_point_1(u8 *obj, s32 arg1, f32 *out) {
    object_bone_point(obj, out, 1);
}

/* P160 */
extern u32 g_gun_side_bone_offsets[]; /* was D_800AAEE0 */
extern u8 g_gun_side_muzzle_pts[]; /* was D_800AAEE8 */

// object_bone_point: transforms point `kind` (0 or 1) of the g_gun_side_muzzle_pts offset table (3 floats each) by the bone
// matrix at byte offset g_gun_side_bone_offsets[kind] in the object's matrix block (obj+0x1D4) and writes it to out.
/* was func_151C6F7C */
void object_bone_point(u8 *obj, f32 *out, u8 kind) {
    mtx_transform_point_or_origin(g_gun_side_muzzle_pts + kind * 12, out, *(u8 **)(obj + 0x1D4) + g_gun_side_bone_offsets[kind]);
}

/* P163 */
s32 obj_sub_counter_positive(u8 *);
void weapon_count_shot(u8 *arg0);
void mtx_transform_points(f32 **, f32 **, void *, s32);
void muzzle_light_small_spawn(u8 *, u8, s32);
void bone_streak_fx_start(u8 *, u8 *, s32, u8 *, f32, u8, s32);
void gun_side_spark_spray(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5);
void beam_light_effect_spawn(f32 *, void *, void *, void *, u8, u8 *, f32, f32, f32, u8 *, u8, u8, u8, u8, s32, s8, s32, u8, u8, s32);
extern u32 g_gun_side_bone_offsets[];  /* [2 kind] bone matrix byte offset; was D_800AAEE0 */
extern u8 g_gun_side_muzzle_pts[];   /* [2 kind] f32[3] muzzle point; was D_800AAEE8 */
extern u8 g_gun_side_second_pts[];   /* [2 kind] f32[3] second point; was D_800AAF18 */
extern u8 g_gun_side_third_pts[];   /* [2 kind] f32[3] third point (direction = third - second); was D_800AAF30 */
extern f32 g_muzzle_flash_lerp;    /* flash position: fraction of the way from the muzzle to the linked record's point; was D_800AAFE4 */
extern f32 g_muzzle_beam_k_afe8; /* was D_800AAFE8 */
extern f32 g_muzzle_beam_k_afec; /* was D_800AAFEC */

/* Returns 0: game_981E0 calls it undeclared (int); difftested as the void draft d_6a28.c. */
// object_muzzle_fire: for point kind arg1 (0 / 1) of obj (not while obj_sub_counter_positive says it is busy), moves the
// kind's three g_gun_side_muzzle_pts / g_gun_side_second_pts / g_gun_side_third_pts points to world space by the bone matrix, spawns the muzzle
// puff (muzzle_light_small_spawn), the tracer from the second point along (third - second) (bone_streak_fx_start) and the shot
// (gun_side_spark_spray); when the object's link 0x1B record is active (+0x9C bit 0) with a light at +0x91, spawns its
// light effect (beam_light_effect_spawn) from the muzzle with a copy of the record's 0x64-byte light block whose position
// (+0x2C) is the record's point (+0x40), or for light kinds >= 2 part of the way from the muzzle to it
/* was func_151C6A28 */
s32 object_muzzle_fire(u8 *obj, u8 arg1, u8 arg2, s32 arg3) {
    f32 *src[3];
    f32 *dst[3];
    u8 *bone;
    f32 dir[3];
    f32 second[3];
    f32 muzzle[3];
    struct_eu_link *link;
    u8 *rec;
    u8 *light;
    f32 at[3];
    u8 blk[0x64];
    s32 i;

    if (obj == NULL || arg1 >= 2) {
        return 0;
    }
    if (obj_sub_counter_positive(obj) != 0) {
        return 0;
    }
    weapon_count_shot(obj);
    if (*(u8 **)(obj + 0x1D4) == NULL) {
        return 0;
    }
    src[0] = (f32 *)(g_gun_side_muzzle_pts + arg1 * 12);
    src[1] = (f32 *)(g_gun_side_second_pts + arg1 * 12);
    src[2] = (f32 *)(g_gun_side_third_pts + arg1 * 12);
    dst[0] = muzzle;
    dst[1] = second;
    dst[2] = dir;
    bone = *(u8 **)(obj + 0x1D4) + g_gun_side_bone_offsets[arg1];
    mtx_transform_points(src, dst, bone, 3);
    dir[0] -= second[0];
    dir[1] -= second[1];
    dir[2] -= second[2];
    muzzle_light_small_spawn(muzzle, arg2, arg3);
    bone_streak_fx_start((u8 *)second, (u8 *)dir, (s32)bone, obj, 1.0f, arg2, arg3);
    gun_side_spark_spray((s32)obj, arg1, (s32)muzzle, -1, arg2, arg3);
    if (char_fx_find_slot(*(struct_eu_link **)(obj + 0x2F4), 0x1B, &link) == 0) {
        return 0;
    }
    rec = *(u8 **)((u8 *)link + 0x10);
    if (!(rec[0x9C] & 1)) {
        return 0;
    }
    if (rec[0x91] == 0) {
        return 0;
    }
    light = rec + 0x38;
    if (light[0x59] >= 2) {
        at[0] = (*(f32 *)(light + 8) - muzzle[0]) * g_muzzle_flash_lerp + muzzle[0];
        at[1] = (*(f32 *)(light + 0xC) - muzzle[1]) * g_muzzle_flash_lerp + muzzle[1];
        at[2] = (*(f32 *)(light + 0x10) - muzzle[2]) * g_muzzle_flash_lerp + muzzle[2];
    } else {
        at[0] = *(f32 *)(light + 8);
        at[1] = *(f32 *)(light + 0xC);
        at[2] = *(f32 *)(light + 0x10);
    }
    for (i = 0; i < 0x64; i++) {
        blk[i] = light[i];
    }
    *(f32 *)(blk + 0x2C) = at[0];
    *(f32 *)(blk + 0x30) = at[1];
    *(f32 *)(blk + 0x34) = at[2];
    beam_light_effect_spawn(muzzle, NULL, NULL, NULL, 0, blk, g_muzzle_beam_k_afe8, g_muzzle_beam_k_afec, 500.0f, obj, 0, (light[0x59] < 2) ? 1 : 0, 1,
                  0, 0x1A, -1, 0, 1, arg2, arg3);
    return 0;
}

/* P262: the C definition's exact types (game_eu_1306B0) */
void *attached_particle_spawn(u8 *, u8, f32 *, f32 *, f32 *, s16, u8, f32, u8 *, u8, s32, s16, u8, s32);
extern u32 g_gun_side_bone_offsets[]; /* was D_800AAEE0 */
extern u8 g_gun_side_muzzle_pts[]; /* was D_800AAEE8 */
extern u8 g_gun_side_aim_pts[]; /* was D_800AAF00 */
extern f32 g_gun_spray_vy_range; /* was D_800AAFF0 */
extern f32 g_gun_spray_vy_min; /* was D_800AAFF4 */
extern f32 g_gun_spray_vx_range; /* was D_800AAFF8 */
extern f32 g_gun_spray_vx_min; /* was D_800AAFFC */
extern f32 g_gun_spray_param_min; /* was D_800AB000 */

/* was func_151C7320 */
void gun_side_spark_spray(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5)
{
  f32 v[2];
  f32 t; // fakematch: named rand temp (s162 recipe: named float temps)
  s32 r[2];
  v[1] = (random_float() * g_gun_spray_vy_range) + g_gun_spray_vy_min;
  v[0] = (random_float() * g_gun_spray_vx_range) + g_gun_spray_vx_min;
  r[0] = random_int();
  r[1] = random_int();
  t = random_float();
  attached_particle_spawn((u8 *)arg0, g_gun_side_bone_offsets[arg1] >> 6, (f32 *)(g_gun_side_muzzle_pts + (arg1 * 12)), (f32 *)(g_gun_side_aim_pts + (arg1 * 12)), v, (r[0] & 3) + 6, 0xFF, (t * 270.0f) + g_gun_spray_param_min, (u8 *)arg2, 0xFF, 0, arg3, arg4, arg5);
}

void *memcpy(void *, const void *, s32);
typedef struct { f32 x, y, z; } V3_151C7450;

typedef struct {
    f32 u0[4];
    V3_151C7450 u10;
    f32 u1C[3];
    V3_151C7450 u28;
    V3_151C7450 u34;
    V3_151C7450 u40;
    f32 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
    s8 u58;
    s32 u5C;
    u8 u60;
    u8 u61;
    s8 u62[6];
    s8 u68;
    s8 u69;
    s8 u6A;
    u8 *u6C;
    u8 u70;
    s16 u72;
    s16 u74;
    s32 u78;
} Blk7C_7450;

/* was func_151C7450 */
void obj_attached_model_fx_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    Blk7C_7450 blk;
    u8 tmp[1];
    void *temp_v0;

    tmp[0] = 0;
    blk.u0[0] = 1.0f;
    blk.u0[1] = 1.0f;
    blk.u0[3] = 1.0f;
    blk.u0[2] = 1.0f;
    blk.u10 = *(V3_151C7450 *)g_vec3_zero;
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.u28 = *(V3_151C7450 *)g_vec3_zero;
    blk.u34 = *(V3_151C7450 *)g_vec3_zero;
    blk.u40 = *(V3_151C7450 *)g_vec3_zero;
    blk.u4C = 0.0f;
    blk.u50 = 0x11900;
    blk.u54 = 0x12C;
    blk.u56 = 0xF;
    blk.u58 = 0;
    blk.u5C = 0;
    blk.u60 = 0x64;
    blk.u61 = 0x17;
    blk.u62[0] = 0;
    blk.u62[1] = 0;
    blk.u62[2] = 0;
    blk.u62[3] = 0;
    blk.u62[4] = 0;
    blk.u62[5] = 0;
    blk.u68 = 5;
    blk.u69 = -1;
    blk.u6A = 1;
    blk.u6C = arg0;
    blk.u70 = arg0[0x3B];
    blk.u72 = 1;
    blk.u74 = 0xFF;
    blk.u78 = 0;
    temp_v0 = mdl_particle_spawn_ex(&blk, 3, 0xFF, 0, 1, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x170, tmp, 1);
    }
}

/* P163: obj_sub_counter_positive (game_eu_170760) takes only the object; the matching build passes a second argument the
   callee ignores, which would be a call signature mismatch on wasm. */
s32 obj_sub_counter_positive(u8 *);

/* was func_151C75E8 */
s32 fx_alpha_from_parent_update(u8 *arg0) {
    u8 *p;
    f32 f;

    p = *(u8 **)(arg0 + 0x7C);
    if (*(u16 *)(p + 0x84) != 0xE9) {
        return 0;
    }
    if (obj_sub_counter_positive(p) != 0) {
        *(s32 *)(arg0 + 0x60) |= 0x20000;
    } else {
        *(s32 *)(arg0 + 0x60) &= ~0x20000;
    }
    f = *(f32 *)(p + 0x4C) * 35.0f;
    if (f > 255.0f) {
        f = 255;
    } else if (f < 0.0f) {
        f = 0.0f;
    }
    arg0[0x70] = f;
    if (!arg0 && !arg0 && !arg0) { // fakematch: empty if keeps arg0 live, schedules li v0,1 early (local permuter)
    }
    return 1;
}
