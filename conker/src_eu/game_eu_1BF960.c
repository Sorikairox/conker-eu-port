#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void hitinfo_from_obj_floor(s32 *, struct127 *);
void *memcpy(void *, const void *, u32);
/* dust effect data (0x68 bytes) copied to the effect object at +0x28 */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 objId;     /* obj +0x3B */
    /* 0x08 */ f32 offset[3];
    /* 0x14 */ s32 kind;     /* arg2 << 6 */
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s32 ground[9]; /* floor query of obj (hitinfo_from_obj_floor) */
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ s16 u50;
    /* 0x52 */ s16 u52;
    /* 0x54 */ u8 u54;
    /* 0x55 */ u8 u55;
    /* 0x58 */ f32 u58;
    /* 0x5C */ f32 u5C;
    /* 0x60 */ f32 u60;
    /* 0x64 */ u8 u64;
} ObjDustData;
// obj_dust_effect_spawn: starts an effect object (effect_node_create, type 0x1D, 0x68 bytes of data) that follows obj
// at `offset` (an f32[3]) with the given parameters and a snapshot of obj's floor query; life `life` (-1: 300 and
// not timed). Returns the effect object or NULL (also for a NULL obj). Only caller obj_dust_effect.
/* was func_15192150 */
struct260 *obj_dust_effect_spawn(u8 *obj, f32 *offset, u8 kind, f32 a3, f32 arg4, s16 life, f32 arg6, f32 arg7, s16 arg8, s16 arg9, u8 arg10, u8 arg11, f32 arg12, f32 arg13, f32 arg14, u8 arg15, u8 arg16, s32 arg17) {
    ObjDustData d;
    struct260 *fx;

    if (obj == NULL) {
        return NULL;
    }
    d.obj = obj;
    d.objId = obj[0x3B];
    d.offset[0] = offset[0];
    d.offset[1] = offset[1];
    d.offset[2] = offset[2];
    d.kind = kind << 6;
    d.u1C = a3;
    d.u18 = 0.0f;
    d.u20 = arg4;
    hitinfo_from_obj_floor(d.ground, (struct127 *) obj);
    d.u48 = arg6;
    d.u4C = arg7;
    d.u50 = arg8;
    d.u52 = arg9;
    d.u54 = arg10;
    d.u55 = arg11;
    d.u58 = arg12;
    d.u5C = arg13;
    d.u60 = arg14;
    d.u64 = arg15;
    /* argument 6 is the data size here (the header types it struct37 *) */
    fx = effect_node_create((life == -1) ? 300 : life, -1, 0x1D, -1, life != -1, 0x1D, (struct37 *) 0x68, arg16, arg17);
    if (fx != NULL) {
        memcpy((u8 *) fx + 0x28, &d, sizeof(d));
    }
    return fx;
}

typedef struct { f32 x, y, z; } V3_25AC;      /* P232: moved up for obj_dust_effect_update (used by dust_drop_particle_spawn) */
typedef struct { s16 h[9]; } H12_25AC;
extern f32 g_dust_out_of_level_height;          /* height used when the point is outside the level (pos_in_world_bounds == 0); was D_800A84C8 */
extern f32 g_dust_floor_search_depth;          /* floor search depth / default height; was D_800A84CC */
extern f32 g_dust_no_ground_height;          /* height used without a ground chance (+0x60 <= 0); was D_800A84D0 */
s32 pos_in_world_bounds(f32 *);
s32 collision_floor_probe_alt(f32 *, s32, f32, s32 *);
f32 random_float(void);
s32 random_int(void);
u8 *dust_drop_particle_spawn(V3_25AC *arg0, V3_25AC *arg1, f32 arg2, s16 arg3, u8 arg4, u8 arg5, f32 arg6, s32 arg7, f32 arg8,
                  H12_25AC *arg9, u8 argA, u8 argB, s32 argC);

// obj_dust_effect_update: P232. Update callback of effect type 0x1D (obj_dust_effect_spawn fills ObjDustData at +0x28). Ends
// the effect (+0xE = -1) when its object is gone or was replaced (+0x3B). The accumulator +0x18 grows by
// (u1C + rand * u20) * frame step; for every whole unit, when the object has a model (+0x1D4), one dust particle
// is spawned (dust_drop_particle_spawn) at the object's `offset` point (mtx_transform_point_or_origin): size u48 + rand * u4C, life
// u50 + rand % (u52 + 1), frames u54 + rand % (u55 + 1), scale u58 + rand * u5C, landing on the ground with
// chance u60 (height from the floor query collision_floor_probe_alt into ground[], g_dust_floor_search_depth if none, g_dust_out_of_level_height outside the
// level, g_dust_no_ground_height when u60 <= 0). Without a model the units are dropped.
/* was func_151922C4 */
void obj_dust_effect_update(u8 *fx) {
    ObjDustData *d = (ObjDustData *) (fx + 0x28);
    u8 *obj = d->obj;
    V3_25AC pos;
    V3_25AC vel;
    f32 height;
    f32 depth;
    f32 size;
    s32 onGround;
    s32 r1;
    s32 r2;
    s32 life;
    s32 frames;
    f32 scale;

    if (*(s32 *) obj == 0 || d->objId != obj[0x3B]) {
        *(s16 *) (fx + 0xE) = -1;
        return;
    }
    d->u18 += (d->u1C + random_float() * d->u20) * g_frame_step_f;
    if (!(d->u18 > 1.0f)) {
        return;
    }
    if (*(u8 **) (obj + 0x1D4) == NULL) {
        while (d->u18 > 1.0f) {
            d->u18 -= 1.0f;
        }
        return;
    }
    mtx_transform_point_or_origin(d->offset, &pos, *(u8 **) (obj + 0x1D4) + d->kind);
    if (0.0f < d->u60) {
        if (pos_in_world_bounds(&pos.x) == 0) {
            height = g_dust_out_of_level_height;
        } else {
            depth = g_dust_floor_search_depth;
            if (collision_floor_probe_alt(&pos.x, 0, depth, d->ground) != 0) {
                height = *(f32 *) &d->ground[0];
            } else {
                height = depth;
            }
        }
    } else {
        height = g_dust_no_ground_height;
    }
    do {
        onGround = (random_float() < d->u60) ? 1 : 0;
        vel.x = 0.0f;
        vel.y = 0.0f;
        vel.z = 0.0f;
        size = random_float();
        r1 = random_int();
        r2 = random_int();
        life = (u32) r1 % (u32) (d->u52 + 1) + d->u50;
        frames = (u32) r2 % (u32) (d->u55 + 1) + d->u54;
        scale = random_float() * d->u5C + d->u58;
        dust_drop_particle_spawn(&pos, &vel, size * d->u4C + d->u48, life, frames, 0xFF, scale, onGround, height,
                      (H12_25AC *) &d->ground[1], d->u64, fx[0xC], fx[1]);
        d->u18 -= 1.0f;
    } while (d->u18 > 1.0f);
}

u8 *particle_spawn_basic(void *, s32, s32, u8, s32);
extern u8 (*g_impact_dust_tex_fns[])(void); /* was D_80090070 */
extern f32 g_dust_drop_k_84d4; /* was D_800A84D4 */
extern f32 g_dust_drop_k_84d8; /* was D_800A84D8 */
typedef struct {
    s32 u0;
    s32 u4;
    s16 u8;
    s16 uA;
    s32 uC;
    s32 u10;
    u8 u14[4];
    u8 u18;
    u8 u19;
    u8 u1A;
    u8 u1B;
    u8 u1C;
    u8 u1D;
    s16 u1E;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    f32 u2C;
    V3_25AC u30;
    f32 u3C;
    f32 u40;
    f32 u44;
    V3_25AC u48;
    f32 u54;
    s32 u58;
    s32 u5C;
    u8 u60;
    u8 u61;
    u8 u62;
    s8 u63;
    s8 u64;
    u8 u65;
} Blk_25AC;
typedef struct {
    f32 u0;
    u8 u4;
    u8 u5;
    u8 u6;
    u8 u7;
    f32 u8;
    f32 uC;
    f32 u10;
    H12_25AC u14;
    u8 u26;
} Tmp_25AC;

/* was func_151925AC */
u8 *dust_drop_particle_spawn(V3_25AC *arg0, V3_25AC *arg1, f32 arg2, s16 arg3, u8 arg4, u8 arg5, f32 arg6, s32 arg7, f32 arg8, H12_25AC *arg9, u8 argA, u8 argB, s32 argC) {
    u8 *ret;
    s32 pad[2]; // fakematch: hole above the block
    Blk_25AC blk;
    Tmp_25AC tmp;
    s32 pad2; // fakematch: spill slot below tmp
    s32 a;

    blk.u8 = 0x4401;
    blk.u0 = 0x200005;
    blk.u4 = 0;
    blk.uC = 0;
    blk.u10 = 0;
    blk.u14[0] = 0;
    blk.u14[1] = 0;
    blk.u14[2] = 0;
    blk.u14[3] = 0xFF;
    blk.u18 = 0;
    blk.u19 = 0;
    blk.u1A = 0;
    blk.u1B = arg4;
    blk.u1C = arg5;
    blk.u30 = *arg0;
    blk.u3C = 0.0f;
    blk.u40 = 0.0f;
    blk.u44 = 0.0f;
    blk.u48 = *arg1;
    blk.u54 = arg2;
    blk.u22 = 1;
    blk.u24 = 1.0f;
    if (random_int() & 1) {
        a = 0x40;
    } else {
        a = 0;
    }
    blk.u58 = ((random_int() & 1) ? 0x80 : 0) | 0xC207 | a | 0x10000;
    blk.uA = arg3 + 0x12;
    blk.u1E = 0x12;
    blk.u20 = 0xE;
    blk.u60 = 6;
    blk.u61 = 8;
    blk.u62 = 0xF;
    blk.u63 = -1;
    blk.u64 = -1;
    blk.u65 = 3;
    tmp.u4 = (s16)random_int(); // fakematch: s16 cast of the rand result (permuter)
    tmp.u5 = random_int();
    blk.u1D = g_impact_dust_tex_fns[argA]();
    blk.u2C = arg6;
    blk.u28 = arg6;
    tmp.u0 = arg6;
    tmp.u6 = (random_int() % 6U) + 5;
    tmp.u7 = (random_int() % 6U) + 5;
    tmp.u8 = ((random_float() * 0.25f) + g_dust_drop_k_84d4) * tmp.u0;
    tmp.uC = ((random_float() * 0.25f) + g_dust_drop_k_84d8) * tmp.u0;
    tmp.u10 = arg8;
    tmp.u14 = *arg9;
    tmp.u26 = argA;
    ret = particle_spawn_basic(&blk, 1, 0x28, argB, argC);
    if (ret != NULL) {
        memcpy(ret + 0xA8, &tmp, 0x28);
    }
    return ret;
}

s32 particle_calc_wobble(u8 *, u8 *, f32, u8 *, u8 *, u8 *); /* P95: f32 (float bits were passed as an int) */

/* was func_15192878 */
s32 dust_drop_wobble(u8 *arg0, s32 arg1) {
    particle_calc_wobble(arg0 + 0xAC, arg0 + 0xAE, (*(f32 *)((u8 *)arg0 + 0xA8)), arg0 + 0xB0, arg0 + 0x38, arg0 + 0x3C); /* P95: f32 (float bits were passed as an int) */
    return 1;
}

extern f32 g_water_splash_k_84dc; /* was D_800A84DC */
extern f32 g_water_splash_k_84e0; /* was D_800A84E0 */
extern f32 g_water_splash_k_84e4; /* was D_800A84E4 */
extern f32 g_water_splash_k_84e8; /* was D_800A84E8 */
extern f32 g_water_splash_k_84ec; /* was D_800A84EC */
extern f32 g_water_splash_k_84f0; /* was D_800A84F0 */
extern f32 g_water_splash_k_84f4; /* was D_800A84F4 */
extern f32 g_water_splash_k_84f8; /* was D_800A84F8 */
void vec3_from_angles_rad(f32, f32, f32, struct17 *);
u8 *impact_spark_spawn(u8 *, u8 *, f32, s16, u8, f32, s32, u8, f32, f32, u8, u8, s32, s16, s16, s32, u8, s32);

// water_drop_splash_update: update handler 14 of the particle tick particle_sprite_update for drops spawned by dust_drop_particle_spawn.
// The extra block at +0xA8 (scale f32, ..., water level f32 at +0x10, splash ring H12 at +0x14, type at +0x26) stays
// unused while the drop is above the water. On the first tick its y (+0x44) is below the water level it spawns a
// splash ring (impact_debris_spawn) at (x, level + 2, z) and one spray droplet (impact_spark_spawn) with a random direction,
// and returns 0 (the drop dies); otherwise returns 1 (keep alive).
/* was func_151928C8 */
s32 water_drop_splash_update(u8 *arg0, s32 arg1) {
    u8 *ext = arg0 + 0xA8;
    struct17 pos;
    struct17 vel;
    f32 r0;
    f32 r1;
    f32 r2;
    f32 r3;
    u32 sprite;
    u32 tint;
    u8 alive = 1;

    if (*(f32 *)(arg0 + 0x44) < *(f32 *)(ext + 0x10)) {
        alive = 0;
        pos.unk0 = *(f32 *)(arg0 + 0x40);
        pos.unk4 = *(f32 *)(ext + 0x10) + 2.0f;
        pos.unk8 = *(f32 *)(arg0 + 0x48);
        impact_debris_spawn(ext[0x26], *(f32 *)ext * g_water_splash_k_84dc, arg0[0x2B], (s32)(ext + 0x14), &pos, 0x64, 0, 1, 0,
                      arg0[0xC], arg0[0x1]);
        r0 = random_float();
        r1 = random_float();
        r2 = random_float();
        vec3_from_angles_rad(r0 * g_water_splash_k_84e4, (r1 * 1000.0f + g_water_splash_k_84e8) * g_water_splash_k_84e0, (r2 * g_water_splash_k_84ec + g_water_splash_k_84f0) * g_water_splash_k_84e0,
                      &vel);
        r3 = random_float();
        sprite = random_int();
        tint = random_int();
        impact_spark_spawn((u8 *)&pos, (u8 *)&vel, r3 * g_water_splash_k_84f4 + g_water_splash_k_84f4, (s16)(sprite % 21 + 0x23), arg0[0x2B],
                      *(f32 *)ext * g_water_splash_k_84f8, tint % 7 + 5, 0, 1.0f, 1.0f, 1, ext[0x26], 0, 0x10, 0xF, 0, arg0[0xC],
                      arg0[0x1]);
    }
    return alive;
}

s32 water_drop_splash_update(u8 *, s32);

/* was func_15192AEC */
s32 dust_drop_wobble_splash(u8 *arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = dust_drop_wobble(arg0, arg1);
    var_v1 = temp_v0 & 0xFF;
    if (temp_v0 != 0) {
        var_v1 = water_drop_splash_update(arg0, arg1) & 0xFF;
    }
    return var_v1;
}

struct260 *obj_dust_effect_spawn(u8 *obj, f32 *offset, u8 kind, f32 a3, f32 arg4, s16 life, f32 arg6, f32 arg7, s16 arg8, s16 arg9, u8 arg10, u8 arg11, f32 arg12, f32 arg13, f32 arg14, u8 arg15, u8 arg16, s32 arg17);
/* per-dust-type parameters for obj_dust_effect_spawn (rodata), indexed by obj_dust_effect's type */
extern f32 g_dust_fx_offsets[4][3]; /* was D_800A8410 */
extern u8 g_dust_fx_kinds[4]; /* was D_800A8440 */
extern f32 g_dust_fx_rate_base[4]; /* was D_800A8444 */
extern f32 g_dust_fx_rate_rand[4]; /* was D_800A8454 */
extern f32 g_dust_fx_size_base[4]; /* was D_800A8464 */
extern f32 g_dust_fx_size_rand[4]; /* was D_800A8474 */
extern s16 g_dust_fx_life_base[4]; /* was D_800A8484 */
extern s16 g_dust_fx_life_rand[4]; /* was D_800A848C */
extern f32 g_dust_fx_scale_base[4]; /* was D_800A8494 */
extern f32 g_dust_fx_scale_rand[4]; /* was D_800A84A4 */
extern f32 g_dust_fx_ground_chance[4]; /* was D_800A84B4 */
extern u8 g_dust_fx_param_64[4]; /* was D_800A84C4 */
// obj_dust_effect: the dust / splash effect for obj's kind (obj +4): kinds 0..4 -> type 0, 0x10 -> 1, 0x58 -> 2,
// 0x79 -> 3, others none; spawns it through obj_dust_effect_spawn with that type's parameters (g_dust_fx_offsets ..). life -1 =
// untimed. Returns the effect object (NULL for none / NULL obj). Callers scene_event_run_b (game_eu_51190, twice),
// objfx_dust_50 (game_981E0).
/* was func_151925C4 */
struct260 *obj_dust_effect(u8 *obj, s16 life, u8 arg2, s32 arg3) {
    s32 type;

    if (obj == NULL) {
        return NULL;
    }
    switch (obj[4]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            type = 0;
            break;
        case 0x10:
            type = 1;
            break;
        case 0x58:
            type = 2;
            break;
        case 0x79:
            type = 3;
            break;
        default:
            type = -1;
            break;
    }
    if (type == -1) {
        return NULL;
    }
    return obj_dust_effect_spawn(obj, g_dust_fx_offsets[type], g_dust_fx_kinds[type], g_dust_fx_rate_base[type], g_dust_fx_rate_rand[type], life,
                         g_dust_fx_size_base[type], g_dust_fx_size_rand[type], g_dust_fx_life_base[type], g_dust_fx_life_rand[type], 100, 155,
                         g_dust_fx_scale_base[type], g_dust_fx_scale_rand[type], g_dust_fx_ground_chance[type], g_dust_fx_param_64[type], arg2, arg3);
}

/* was func_15192CEC */
void obj_dust_effect_on_message(s32 arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
