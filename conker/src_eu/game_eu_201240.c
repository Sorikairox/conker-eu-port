#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P203 */
/* P203: the 0x12-byte surface record a ray hit leaves (copied from the caller's hit when it has one) */
typedef struct {
    s16 v[9];
} ImpactSurface;
/* P203: spark burst spec for emit_streaks_from_spec (0x74 bytes; bytes 0x59..0x5B and 0x6B are never set) */
typedef struct {
    s32 count;        /* 0x00 5 >> g_fx_lod_shift_players */
    s32 count2;       /* 0x04 4 >> g_fx_lod_shift_players */
    f32 pos[3];       /* 0x08 */
    f32 speed;        /* 0x14 8.25 */
    f32 spread;       /* 0x18 5.86 */
    f32 f1C, f20;     /* 0x1C, 0x20 0 */
    f32 f24, f28;     /* 0x24 7, 0x28 16 */
    s16 h2C, h2E;     /* 0x2C 0, 0x2E 0xFF */
    s16 h30, h32;     /* 0x30 -61, 0x32 80 */
    s32 w34, w38;     /* 0x34 3, 0x38 1 */
    s16 h3C, h3E, h40; /* 0x3C 12, 0x3E 10, 0x40 1 */
    u8 b42, b43, b44; /* 0x42 4, 0x43 2, 0x44 3 */
    u8 rgba0[4];      /* 0x45 white */
    u8 rgba1[4];      /* 0x49 0 */
    u8 rgba2[4];      /* 0x4D white */
    u8 rgba3[4];      /* 0x51 0 */
    u8 b55, b56, b57, b58; /* 0x55 0xFF, 0 , 1, 0x24 */
    u8 pad59[3];
    s32 w5C, w60;     /* 0x5C 0x200005, 0x60 0x60600 */
    s16 h64, h66, h68; /* 0x64 10, 0x66 25, 0x68 1 */
    u8 b6A, pad6B;    /* 0x6A 0 */
    f32 f6C;          /* 0x6C 1 */
    u8 b70, b71, b72, b73; /* 0x70 0xFF, 0, 0xFF, 0xFF */
} ImpactSparks;
/* P203: particle spec for mdl_particle_spawn (0x76 bytes used; 0x59..0x5B, 0x69, 0x6B, 0x71 never set) */
typedef struct {
    f32 scale[4];     /* 0x00 1, 1, 0.65, 0.65 */
    f32 rot[3];       /* 0x10 / 0x14 from the direction (vec3_to_yaw_pitch_deg), 0x18 0 */
    f32 one[3];       /* 0x1C 1, 1, 1 */
    f32 pos[3];       /* 0x28 */
    f32 vel[3];       /* 0x34 */
    f32 spin[4];      /* 0x40 */
    s32 tex;          /* 0x50 0x39E8 / 0x3980 */
    s16 life;         /* 0x54 */
    s16 kind;         /* 0x56 the spark type of the impact kind */
    u8 b58, pad59[3]; /* 0x58 0 */
    s32 w5C;          /* 0x5C 0 */
    u8 b60, b61;      /* 0x60 0xFF, 0x61 8 / 12 */
    u8 b62[6];        /* 0x62 0 */
    u8 b68, pad69;    /* 0x68 2 */
    u8 b6A, pad6B;    /* 0x6A 0 */
    s32 w6C;          /* 0x6C 0 */
    u8 b70, pad71;    /* 0x70 0 */
    s16 h72, h74;     /* 0x72 12, 0x74 21 */
} ImpactParticle;
/* P203: the trail block copied to the particle +0x170 (0x10 bytes, 0x02..0x03 never set) */
typedef struct {
    s16 life;
    s16 pad;
    f32 f4, f8, fC;
} ImpactTrail;
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, f32 *, ImpactSurface *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
u8 prop_is_flagged(s32 arg0);
void vec3_to_yaw_pitch_deg(f32 *dir, f32 *yaw, f32 *pitch);
s32 vec3_normalize_len(f32 *dir, f32 *out, f32 *a, f32 *b);
s32 emit_streaks_from_spec(ImpactSparks *spec, u8 arg1, s32 arg2);
u8 *mdl_particle_spawn(ImpactParticle *spec, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void *cam_sprite_puff_spawn(f32 size, u8 arg1, ImpactSurface *surf, f32 *pos, s16 life, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
s32 sfx_cb_delayed_play_2d(s32, s32, s32, s32, s32, s32, s32); /* a function (init_EB00.c), passed by address */
void *memcpy(void *, const void *, s32);
extern u8 g_fx_lod_shift_players;  /* spark count shift (0 = full); was D_800DCE50 */
extern f32 g_fx_lod_scale_players; /* spark chance; was D_800DCE54 */

// impact_effect_spawn: P203: effects where a shot or blow hits `pos` coming along `dir`. The surface: the caller's
// hit record (`hit`, 0x12 bytes) at pos, else a ray from pos - dir along dir (collision_ray_cast) gives the hit point,
// surface and material id (-1 when nothing is hit). kind (0..5, others do nothing) picks the particle type (0x34,
// 0x4D, 0x57, 0x58, 0x0C, none). `big` = a random odd number or a surface without material (prop_is_flagged == 0).
// Kind 1 (bullet) plays a ricochet: a random 0x459..0x45B one-shot (sfx_emitter_start, only in one-player mode, then
// the follow-up sound 0x106) when big, else 0xB0, through sound_voice_play_at at the position. With chance g_fx_lod_scale_players a
// spark burst (emit_streaks_from_spec, 5 >> g_fx_lod_shift_players sparks). In one- and two-player modes the particle of the kind: when
// big a fast debris piece thrown back along the surface normal (vec3_normalize_len) with random spin, else a slow puff
// with a trail block (+0x170) along the direction's angles. A material surface that was hit also gets a decal
// (cam_sprite_puff_spawn, size 15..35, life 300). arg4 / arg5 are passed to every spawner (view / owner).
// Returns 0: the asm leaves the last callee's v0, which no caller reads (s32 for game_eu_981C0's prototype).
/* was func_151D3A30 */
s32 bullet_impact_effects(f32 *pos, f32 *dir, ImpactSurface *hit, s32 kind, s32 arg4, s32 arg5) {
    f32 hit_pos[3];
    ImpactSurface surf;
    s32 surf_id;
    f32 ray_t, ray_u;
    ImpactSparks sparks;
    ImpactParticle part;
    ImpactTrail trail;
    f32 normal[3];
    f32 na, nb;
    f32 speed;
    s32 type, big, snd;
    u8 found, material;
    u8 *p;

    kind &= 0xFF;
    if (kind >= 6) {
        return 0;
    }
    switch (kind) {
        case 4:
            type = 0xC;
            break;
        case 2:
            type = 0x57;
            break;
        case 3:
            type = 0x58;
            break;
        case 0:
            type = 0x34;
            break;
        case 1:
            type = 0x4D;
            break;
        default:
            type = 0;
            break;
    }
    if (hit == NULL) {
        if (collision_ray_cast(pos[0] - dir[0], pos[1] - dir[1], pos[2] - dir[2], dir[0], dir[1], dir[2], &ray_u, &surf,
                          &hit_pos[0], &hit_pos[1], &hit_pos[2], &ray_t, &surf_id, 0, 0.0f) != 0) {
            found = TRUE;
        } else {
            found = FALSE;
            surf_id = -1;
        }
    } else {
        surf_id = -1;
        hit_pos[0] = pos[0];
        hit_pos[1] = pos[1];
        hit_pos[2] = pos[2];
        surf = *hit;
        found = TRUE;
    }
    material = prop_is_flagged(surf_id);
    if ((random_int() & 1) || material == 0) {
        big = TRUE;
    } else {
        big = FALSE;
    }
    if (kind == 1) {
        if (big) {
            snd = (u32) random_int() % 3 + 0x459;
            if (g_last_player_index == 0) {
                sfx_emitter_start(snd, (s32) pos[0], (s32) pos[1], (s32) pos[2], 0x4000, 0x4B0, 0x320, (s32) sfx_cb_delayed_play_2d,
                              (void *) 0x28, 0, 0, 0);
                snd = 0x106;
            }
        } else {
            snd = 0xB0;
        }
        sound_voice_play_at(0, snd, 0x6590, (u32) random_int() % 500 - 250, 0, 0, (s32) pos[0], (s32) pos[1],
                      (s32) pos[2], 500, 800);
    }
    if (random_float() < g_fx_lod_scale_players) {
        sparks.count = 5 >> g_fx_lod_shift_players;
        sparks.count2 = 4 >> g_fx_lod_shift_players;
        sparks.pos[0] = pos[0];
        sparks.pos[1] = pos[1];
        sparks.pos[2] = pos[2];
        sparks.speed = 8.25f;
        sparks.spread = 5.85999966f; /* 0x40BB851E (IDO reads 5.86f as 0x40BB851F) */
        sparks.f1C = 0.0f;
        sparks.f20 = 0.0f;
        sparks.f24 = 7.0f;
        sparks.f28 = 16.0f;
        sparks.h2C = 0;
        sparks.h2E = 0xFF;
        sparks.h30 = -0x3D;
        sparks.h32 = 0x50;
        sparks.w34 = 3;
        sparks.w38 = 1;
        sparks.h3C = 0xC;
        sparks.h3E = 0xA;
        sparks.h40 = 1;
        sparks.b42 = 4;
        sparks.b43 = 2;
        sparks.b44 = 3;
        sparks.rgba0[0] = sparks.rgba0[1] = sparks.rgba0[2] = sparks.rgba0[3] = 0xFF;
        sparks.rgba1[0] = sparks.rgba1[1] = sparks.rgba1[2] = sparks.rgba1[3] = 0;
        sparks.rgba2[0] = sparks.rgba2[1] = sparks.rgba2[2] = sparks.rgba2[3] = 0xFF;
        sparks.rgba3[0] = sparks.rgba3[1] = sparks.rgba3[2] = sparks.rgba3[3] = 0;
        sparks.b55 = 0xFF;
        sparks.b56 = 0;
        sparks.b57 = 1;
        sparks.b58 = 0x24;
        sparks.w5C = 0x200005;
        sparks.w60 = 0x60600;
        sparks.h64 = 0xA;
        sparks.h66 = 0x19;
        sparks.h68 = 1;
        sparks.b6A = 0;
        sparks.f6C = 1.0f;
        sparks.b70 = 0xFF;
        sparks.b71 = 0;
        sparks.b72 = 0xFF;
        sparks.b73 = 0xFF;
        emit_streaks_from_spec(&sparks, arg4, arg5);
    }
    if (type != 0 && g_last_player_index < 2) {
        part.pos[0] = pos[0];
        part.pos[1] = pos[1];
        part.pos[2] = pos[2];
        vec3_to_yaw_pitch_deg(dir, &part.rot[1], &part.rot[0]);
        part.b58 = 0;
        part.w5C = 0;
        part.b60 = 0xFF;
        part.b62[0] = part.b62[1] = part.b62[2] = part.b62[3] = part.b62[4] = part.b62[5] = 0;
        part.b68 = 2;
        part.b6A = 0;
        part.w6C = 0;
        part.b70 = 0;
        part.h72 = 0xC;
        part.h74 = 0x15;
        part.scale[0] = 1.0f;
        part.scale[1] = 1.0f;
        part.one[0] = 1.0f;
        part.one[1] = 1.0f;
        part.one[2] = 1.0f;
        part.scale[3] = 0.65f;
        part.scale[2] = 0.65f;
        part.rot[2] = 0.0f;
        part.kind = type;
        if (big) {
            if (vec3_normalize_len(dir, normal, &na, &nb) != 0) {
                speed = random_float() * 12.0f + 3.0f;
                part.life = (u32) random_int() % 11 + 0x1E;
                part.vel[0] = -normal[0] * speed;
                part.vel[1] = -normal[1] * speed;
                part.vel[2] = -normal[2] * speed;
                part.spin[0] = (random_float() * 203280.0f + -101640.0f) * 0.0001f;
                part.spin[1] = (random_float() * 203280.0f + -101640.0f) * 0.0001f;
                part.spin[2] = (random_float() * 203280.0f + -101640.0f) * 0.0001f;
                part.spin[3] = (random_float() * 449.0f + -744.0f) * 0.001f;
                part.tex = 0x39E8;
                part.b61 = 8;
                mdl_particle_spawn(&part, 3, 0xFF, 0, arg4, arg5);
            }
        } else {
            trail.life = (random_int() & 0xF) + 0x14;
            trail.f4 = 0.0f;
            trail.f8 = (random_float() * 10000.0f + 10000.0f) * 0.0001f;
            trail.fC = (random_float() * 21000.0f + 4000.0f) * 0.0001f;
            part.life = 0x12C;
            part.vel[0] = 0.0f;
            part.vel[1] = 0.0f;
            part.vel[2] = 0.0f;
            part.spin[0] = part.rot[0];
            part.spin[1] = part.rot[1];
            part.spin[2] = part.rot[2];
            part.tex = 0x3980;
            part.b61 = 0xC;
            part.spin[3] = 0.0f;
            p = mdl_particle_spawn(&part, 3, 0xFF, 0x10, arg4, arg5);
            if (p != NULL) {
                memcpy(p + 0x170, &trail, sizeof(trail));
            }
        }
    }
    if (found && material != 0) {
        cam_sprite_puff_spawn(random_float() * 20.0f + 15.0f, 0xFF, &surf, hit_pos, 0x12C, 1, 1, 0, arg4, arg5);
    }
    return 0;
}

/* was func_151D4300 */
s32 impact_puff_wobble_update(u8 *arg0) {
    u8 *v;

    v = arg0 + 0x170;
    if (*(s16 *)(arg0 + 0x170) > 0) {
        *(f32 *)(v + 4) = (*(f32 *)(v + 8) * g_frame_step_f) + *(f32 *)(v + 4);
        *(f32 *)(v + 4) = wrap_angle_rad(*(f32 *)(v + 4));
        *(f32 *)(arg0 + 0x24) = *(f32 *)(arg0 + 0x54) + (*(f32 *)(v + 0xC) * sinf(*(f32 *)(v + 4)));
        *(s16 *)(v + 0) = *(s16 *)(v + 0) - g_frame_ticks;
    } else {
        *(vertex *)(arg0 + 0x20) = *(vertex *)(arg0 + 0x50);
    }
    return 1;
}

/* was func_151D43B4 */
void obj_bone_point_or_pos(s32 arg0, s32 arg1, void *arg2, u8 arg3, f32 arg4) {
    u8 *temp_v0;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x1D4));
    if (temp_v0 != 0) {
        mtx_transform_point_or_origin(arg2, (u8 *) arg1, (u8 *)((s32)temp_v0 + (arg3 << 6)));
        return;
    }
    (*(f32 *)((u8 *)arg1 + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + arg4);
    (*(f32 *)((u8 *)arg1 + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C));
}

/* P159 */
// object_sound_between: plays sound `sound` (attack_spawn_at_point) at the midpoint of a and b for object obj (its index
// in g_objects); the facing is obj's u16 at +0x76, minus the s16 at +0x12 of its parent (+0x31C) when it has one.
/* was func_151D441C */
void object_effect_between(struct127 *obj, f32 *a, f32 *b, s32 sound) {
    u8 *parent;
    u16 facing;

    parent = *(u8 **)((u8 *)obj + 0x31C);
    if (parent != NULL) {
        facing = *(u16 *)((u8 *)obj + 0x76) - *(s16 *)(parent + 0x12);
    } else {
        facing = *(u16 *)((u8 *)obj + 0x76);
    }
    attack_spawn_at_point((a[0] + b[0]) * 0.5f, (a[1] + b[1]) * 0.5f, (a[2] + b[2]) * 0.5f, sound, obj - g_objects,
                  facing, 0, 0);
}

/* was func_151D44C4 */
void muzzle_light_small_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (random_int() % 3U) + 4;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    light_create_with_ctrl(sp48, sp3C, (random_int() % 13U) + 0x14, 0xFF, 0xE8, 0xAB, 0xFFU, 0U, 0, arg1, arg2);
}

/* was func_151D45A4 */
void explosion_light_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    s8 sp48[8];
    s32 sp3C[3];

    sp48[0] = 3;
    sp48[1] = -1;
    *(s16 *)(sp48 + 2) = (random_int() % 11U) + 0x14;
    sp48[4] = 0;
    sp3C[0] = *(f32 *)(arg0 + 0);
    sp3C[1] = *(f32 *)(arg0 + 4);
    sp3C[2] = *(f32 *)(arg0 + 8);
    light_create_with_ctrl(sp48, sp3C, (random_int() % 24U) + 0x22, 0xFF, 0xA1, 0xA2, 0xFFU, 0U, 0, arg1, arg2);
}

/* P155 */
s32 attack_spawn_at_point(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, u16 arg5, s32 arg6, s32 arg7);
// object_sounds_at: plays the sounds `sound1` and `sound2` (attack_spawn_at_point) at pos for object obj (its index in
// g_objects) with `flags` and a source point: with dir, pos - 90 * dir and dir's binary angle - 0x4000 (odd) as
// facing; without, pos raised by half the height of `model` (obj_collision_cylinder, when given) and facing 0. arg4 is
// unused. Returns 0 (the asm leaves v0 unset; the caller ignores it).
/* was func_151D4684 */
s32 object_effects_at(f32 *pos, f32 *dir, struct127 *obj, struct127 *model, s32 arg4, s32 sound1, s32 sound2, s32 flags) {
    f32 at[3];
    s16 height;
    f32 a;
    u32 angle;
    s32 facing;
    s32 index;

    if (dir != NULL) {
        a = math_atan2f(dir[0], dir[2]) * 10430.378f;
        /* IDO's f32 -> u32 conversion: below 0 gives 0xFFFFFFFF (undefined in C, wasm traps) */
        angle = (a <= -1.0f) ? 0xFFFFFFFF : (u32)a;
        facing = ((angle - 0x4000) | 1) & 0xFFFF;
        at[0] = pos[0] + dir[0] * -90.0f;
        at[1] = pos[1] + dir[1] * -90.0f;
        at[2] = pos[2] + dir[2] * -90.0f;
    } else {
        ((s32 *)at)[0] = ((s32 *)pos)[0];
        ((s32 *)at)[1] = ((s32 *)pos)[1];
        ((s32 *)at)[2] = ((s32 *)pos)[2];
        if (model != NULL) {
            obj_collision_cylinder(model, &height, NULL, NULL);
            at[1] += height >> 1;
        }
        facing = 0;
    }
    index = obj - g_objects;
    attack_spawn_at_point(pos[0], pos[1], pos[2], sound1, index, facing, flags, (s32)at);
    attack_spawn_at_point(pos[0], pos[1], pos[2], sound2, index, facing, flags, (s32)at);
    return 0;
}

/* P155 */
// object_sound_at: plays sound `sound` (attack_spawn_at_point) at pos for object obj (its index in g_objects), with the
// direction of dir (x / z, binary angle - 0x4000, odd) or 0 without dir. arg3 is unused.
/* was func_151D4898 */
void object_effect_at(f32 *pos, f32 *dir, struct127 *obj, s32 arg3, s32 sound) {
    f32 a;
    u32 angle;
    s32 facing;

    facing = 0;
    if (dir != NULL) {
        a = math_atan2f(dir[0], dir[2]) * 10430.378f;
        /* IDO's f32 -> u32 conversion: below 0 gives 0xFFFFFFFF (undefined in C, wasm traps) */
        angle = (a <= -1.0f) ? 0xFFFFFFFF : (u32)a;
        facing = ((angle - 0x4000) | 1) & 0xFFFF;
    }
    attack_spawn_at_point(pos[0], pos[1], pos[2], sound, obj - g_objects, facing, 0, 0);
}

typedef struct { f32 x, y, z; } V3;

/* was func_151D49B8 */
void bone_streak_fx_start(u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3, f32 arg4, u8 arg5, s32 arg6) {
    struct {
        s32 u38[6];
        u8 pad50[0x4];
        f32 u54[5];
        s32 u68[2];
        f32 u70;
        f32 u74;
        f32 u78;
        s32 u7C;
        u8 pad80[0x8];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        s32 uA4;
        s16 uA8;
        s16 uAA;
        s8 uAC;
        u8 padAD[0x3];
        s32 uB0;
        u8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s8 uBA;
        s8 uBB;
        s8 uBC;
        u8 padBD[0x1];
        s8 uBE;
        u8 padBF[0x1];
        u8 *uC0;
        u8 uC4;
        u8 padC5[0x1];
        s16 uC6;
        s16 uC8;
        u8 padCA[0x2];
        s32 uCC;
    } sp;

    mtx_decompose(arg2, &sp.u38[3], &sp.u38[4], &sp.u38[5], &sp.u54[4], &sp.u68[0], &sp.u68[1], &sp.u38[0], &sp.u38[1], &sp.u38[2]);
    sp.u54[4] += 180.0f;
    {
        f32 temp_f0;

        temp_f0 = random_float();
        sp.u54[0] = 1.0f;
        sp.u54[1] = 1.0f;
        sp.u70 = 1.0f;
        sp.u74 = 1.0f;
        sp.u78 = 1.0f;
        sp.u54[3] = 0.042000003f * arg4;
        sp.u54[2] = sp.u54[3];
        *(V3 *)&sp.u7C = *(V3 *)arg0;
        arg4 = ((temp_f0 * 105.0f) + 199.0f) * 0.001f;
        sp.u88 = (*(f32 *)((u8 *)arg1 + 0)) * arg4;
        sp.u8C = (*(f32 *)((u8 *)arg1 + 4)) * arg4;
        sp.u90 = (*(f32 *)((u8 *)arg1 + 8)) * arg4;
        sp.u94 = ((random_float() * 6378.0f) + -3189.0f) * 0.001f;
        sp.u98 = 0.0f;
        sp.u9C = ((random_float() * 6378.0f) + -3189.0f) * 0.001f;
        sp.uA0 = ((random_float() * 320.0f) + -707.0f) * 0.001f;
        sp.uA4 = 0x29E8;
        sp.uA8 = (random_int() & 7) + 0x1C;
        sp.uAA = 0x25;
        sp.uAC = 0;
        sp.uB0 = 0;
        sp.uB4 = 0xFF;
        sp.uB5 = 8;
        sp.uB6 = 0;
        sp.uB7 = 0;
        sp.uB8 = 0;
        sp.uB9 = 0;
        sp.uBA = 0;
        sp.uBB = 0;
        sp.uBC = 2;
        sp.uBE = 1;
        sp.uC0 = arg3;
        sp.uC4 = (*(u8 *)((u8 *)arg3 + 0x3B));
        sp.uC6 = 6;
        sp.uC8 = 0x2A;
        mdl_particle_spawn((u8 *)&sp.u54, 3, 0xFF, 0, (s32) arg5, arg6);
    }
}

/* was func_151D4668 */
void obj_point_fx_broadcast_kill(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    effect_nodes_broadcast(&tmp, 0x3C);
}

/* P160 */
void *memcpy(void *, const void *, s32);
extern void (*g_obj_point_fx_fns[])(u8 *obj, s32 sound, f32 *point); /* was D_80090010 */

typedef struct {
    u8 *obj;     /* 0x00 */
    u8 objId;    /* 0x04: obj[0x3B] */
    s16 sound;   /* 0x06: -1, 0x82 for kind 6 */
    u8 kind;     /* 0x08 */
    f32 unkC;    /* 0x0C */
    u8 flags;    /* 0x10: bit 0 = point valid */
    f32 point[3]; /* 0x14 */
} ObjEffectRec_151D469C; /* 0x20 bytes, copied to the record at +0x28 */

// object_point_effect_spawn: fills a 0x20-byte record (object, kind, the kind's point on the object from the
// g_obj_point_fx_fns handler when the object has bone matrices and obj[0x74] low nibble != 0xF) and spawns event 0x41 /
// kind 0x35 through effect_node_create with it. Returns 0 (callers in game_981E0 declare it implicitly as int).
/* was func_151D469C */
s32 object_point_effect_spawn(u8 *obj, u8 kind, s16 arg2, u8 arg3, s32 arg4) {
    ObjEffectRec_151D469C rec;
    u8 *p;

    rec.obj = obj;
    rec.objId = obj[0x3B];
    rec.sound = -1;
    rec.flags = 0;
    rec.kind = kind;
    rec.unkC = 0.0f;
    if (kind == 6) {
        rec.sound = 0x82;
    }
    if (*(u8 **)(obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 0xF) {
        g_obj_point_fx_fns[kind](obj, rec.sound, rec.point);
        rec.flags |= 1;
    }
    p = (u8 *)effect_node_create(arg2, -1, 0x41, -1, 1, 0x35, (struct37 *)0x20, arg3, arg4);
    if (p != NULL) {
        memcpy(p + 0x28, &rec, 0x20);
    }
    return 0;
}

/* P222: readable C for object_trail_smoke_update (game_eu_201240, 297 words). */
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
f32 vec3_length(struct17 *arg0);

typedef struct {
    s32 w00;        /* 0x00 0x200005 */
    s32 w04;        /* 0x04 0 */
    s16 h08;        /* 0x08 0x5103 */
    s16 life;       /* 0x0A rand % 11 + 0x46 */
    s32 w0C, w10;   /* 0x0C 0 */
    u8 rgba0[4];    /* 0x14 DD D3 CD FF */
    u8 rgba1[4];    /* 0x18 57 55 5A, alpha rand % 61 + 0x3C */
    u8 b1C, b1D;    /* 0x1C FF 6C */
    s16 h1E, h20, h22; /* 0x1E 0x46, 3, 0x46 */
    f32 f24;        /* 0x24 1.02555 */
    f32 size[2];    /* 0x28 rand * 40 + 40 (both) */
    f32 pos[3];     /* 0x30 */
    f32 f3C[3];     /* 0x3C 0 */
    f32 vel[3];     /* 0x48 */
    f32 f54;        /* 0x54 rand * 0.18 + 0.13 */
    s32 flags;      /* 0x58 0x90DE07, bits 0x80 / 0x40 random */
    u8 pad5C[4];
    u8 b60, b61, b62, b63, b64, b65; /* 0x60 8 6 0x20 0xFF 0xFF 0 */
} SmokeSpec_151D4D44;

typedef struct {
    u8 b0, b1, b2, b3;  /* rand, rand, rand % 5 + 4, rand % 5 + 4 */
    f32 f4, f8;         /* rand * 6 */
    f32 fC;             /* 0.915686 */
} SmokeData_151D4D44;   /* copied to the particle's +0xA8 */

// object_trail_smoke_update: update handler (table D_8008A980) of the event record that object_point_effect_spawn spawns (kind
// 0x35, its 0x20-byte object record at +0x28: object, id, sound, point kind, accumulator +0x34, flags +0x38, point
// +0x3C). Ends the event (+0xE = -1) when the object is gone or reused (id +0x2C != obj[0x3B]). Re-reads the point from
// the object's g_obj_point_fx_fns handler (bone matrices present and obj[0x74] low nibble != 0xF). When the old point was
// valid and the point moved at most 5 units, the accumulator grows by (0.2 + rand * 0.209) per second and each whole
// unit emits one smoke particle (particle_spawn_ex, layer ev[0xC] / ev[1]) at a random spot on the move segment, with
// random size / alpha / life and its 16-byte data at +0xA8.
/* was func_151D4D44 */
void object_trail_smoke_update(u8 *ev) {
    ObjEffectRec_151D469C *rec = (ObjEffectRec_151D469C *) (ev + 0x28);
    u8 *obj;
    struct17 old;
    struct17 d;
    SmokeSpec_151D4D44 spec;
    SmokeData_151D4D44 data;
    u8 *p;
    f32 t;
    s32 b80, b40;
    u8 valid;

    old = *(struct17 *) rec->point;
    obj = rec->obj;
    valid = rec->flags & 1;
    if (*(s32 *) obj == 0 || rec->objId != obj[0x3B]) {
        *(s16 *) (ev + 0xE) = -1;
        return;
    }
    if (*(u8 **) (obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 0xF) {
        g_obj_point_fx_fns[rec->kind](obj, rec->sound, rec->point);
        rec->flags |= 1;
    }
    if (!valid) {
        return;
    }
    d.unk0 = rec->point[0] - old.unk0;
    d.unk4 = rec->point[1] - old.unk4;
    d.unk8 = rec->point[2] - old.unk8;
    if (vec3_length(&d) > 5.0f) {
        return;
    }
    rec->unkC += (0.2f + random_float() * 0.209f) * g_frame_step_f;
    if (!(rec->unkC > 1.0f)) {
        return;
    }
    data.fC = 0.915686f;
    spec.w00 = 0x200005;
    spec.w04 = 0;
    spec.h08 = 0x5103;
    spec.w0C = 0;
    spec.w10 = 0;
    spec.rgba0[0] = 0xDD;
    spec.rgba0[1] = 0xD3;
    spec.rgba0[2] = 0xCD;
    spec.rgba0[3] = 0xFF;
    spec.rgba1[0] = 0x57;
    spec.rgba1[1] = 0x55;
    spec.rgba1[2] = 0x5A;
    spec.b1C = 0xFF;
    spec.b1D = 0x6C;
    spec.h1E = 0x46;
    spec.h20 = 3;
    spec.h22 = 0x46;
    spec.f24 = 1.02555f;
    spec.f3C[0] = spec.f3C[1] = spec.f3C[2] = 0.0f;
    spec.flags = 0x90DE07;
    spec.b60 = 8;
    spec.b61 = 6;
    spec.b62 = 0x20;
    spec.b63 = 0xFF;
    spec.b64 = 0xFF;
    spec.b65 = 0;
    do {
        t = random_float();
        spec.pos[0] = d.unk0 * t + old.unk0;
        spec.pos[1] = d.unk4 * t + old.unk4;
        spec.pos[2] = d.unk8 * t + old.unk8;
        spec.vel[0] = d.unk0 * D_800BEDC8 * 0.298f;
        spec.vel[1] = d.unk4 * D_800BEDC8 * 0.298f;
        spec.vel[2] = d.unk8 * D_800BEDC8 * 0.298f;
        data.b0 = random_int();
        data.b1 = random_int();
        data.b2 = (u32) random_int() % 5 + 4;
        data.b3 = (u32) random_int() % 5 + 4;
        data.f4 = random_float() * 6.0f;
        data.f8 = random_float() * 6.0f;
        spec.f54 = random_float() * 0.18f + 0.13000001f;
        b80 = (random_int() & 1) ? 0x80 : 0;
        b40 = (random_int() & 1) ? 0x40 : 0;
        spec.flags = (spec.flags & ~0xC0) | b40 | b80;
        spec.rgba1[3] = (u32) random_int() % 61 + 0x3C;
        spec.life = (u32) random_int() % 11 + 0x46;
        spec.size[0] = spec.size[1] = random_float() * 40.0f + 40.0f;
        p = (u8 *) particle_spawn_ex((s32) &spec, 1, 0, 0x10, ev[0xC], ev[1]);
        if (p != NULL) {
            memcpy(p + 0xA8, &data, 0x10);
        }
        rec->unkC -= 1.0f;
    } while (rec->unkC > 1.0f);
}

/* was func_151D51E8 */
void obj_point_fx_on_message(struct102 *arg0, u8 *arg1, u8 arg2)
{
  u8 *p = (u8 *)arg0 + 0x28;
  if (arg2 == 0x3C) {
    if (*(s32 *)p == *(s32 *)arg1 || p[4] == arg1[4]) {
      node_destroy(arg0);
    }
  } else if (arg2 == 4) {
    if (*(s32 *)p == *(s32 *)arg1 || p[4] == arg1[4]) {
      u8 *q = p + 0x10; // a declaration in the arm = basic-block boundary (unfilled b delay slot, s69)
      *q &= ~1;
    }
  } else {
    effect_node_link_message((s32)arg1, arg2, (s32)p, (s32)(p + 4), (s32)arg0);
  }
}

// P231 (P230 implicit_scan): vec_damp_xyz_per_tick takes (f32 *, f32); the matching C below calls it without a prototype and
// passes the f32's bit pattern as an int (lands in a1 either way on N64, wrong type on the port). Same fix as
// particle_wobble_damp_update (game_eu_DCEF0, P230).
void particle_update_wobble_offset(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void vec_damp_xyz_per_tick(f32 *arg0, f32 arg1);
/* was func_151D52B4 */
s32 trail_smoke_particle_update(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    particle_update_wobble_offset(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    vec_damp_xyz_per_tick((f32 *)(arg0 + 0x58), *(f32 *)(p + 0xC));
    return 1;
}

/* P160: object_point_effect_spawn takes the object as a pointer */
// object_bone_point_effects: spawns the point effects of bone points 0 and 1 of obj (object_point_effect_spawn kinds 0, 1)
/* was func_151D5308 */
void object_bone_point_effects(s32 arg0) {
    object_point_effect_spawn((u8 *)arg0, 0, 0x50, 0xFF, 1);
    object_point_effect_spawn((u8 *)arg0, 1, 0x50, 0xFF, 1);
}

/* P179 */
void hit_spark_sound_play(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 arg4);
void object_impact_effects(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4, s32 arg5);
void obj_set_dying_flags(struct127 *arg0);
void object_hit_effect(struct127 *arg0, s32 arg1, s32 arg2);
s32 obj_send_hit(struct127 *, s32, u16, s32);

// object_take_hit: P179: a hit on `obj` by `attacker` (or NULL) at `pos` / `pos2`, direction `dir`, hit record `rec`
/* (or NULL). Body kinds that react with a spark (the list below) get hit_spark_sound_play (attacker, pos, dir, 9, rec +4
 * or 0). A kind-0xA / type-3 hit record (rec +0x58 / +0x59) wears down the shield count obj +0x1CA: at 3 or more it
 * loses one, else it is cleared, obj_set_dying_flags / object_hit_effect (obj, 0xFF, 1) run and the message flags become
 * 0x100020 (else `flags` | 0x60000). Then object_impact_effects (obj, pos, pos2, dir, arg7, arg8); and only if the count
 * was non-zero on entry, the message obj_send_hit(obj, flags | 0x80000, (dir angle - 0x4000) | 1, attacker index
 * or -1). The angle is math_atan2f(dir x, dir z) x 65536 / 2pi converted as IDO's float -> unsigned (negative ->
 * 0xFFFF). */
/* was func_151D535C */
void object_take_hit(u8 *obj, u8 *attacker, u8 *pos, f32 *pos2, u8 *rec, s32 flags, f32 *dir, u8 arg7, s32 arg8) {
    u8 count;
    s32 untouched;
    s32 w;
    u16 angle;

    switch (obj[4]) {
        case 0x09: case 0x0F: case 0x10: case 0x12: case 0x17: case 0x1B: case 0x1E: case 0x28: case 0x29:
        case 0x2A: case 0x2B: case 0x2C: case 0x2E: case 0x38: case 0x41: case 0x42: case 0x4B: case 0x46:
        case 0x47: case 0x49: case 0x4A: case 0x4C: case 0x4D: case 0x4E: case 0x4F: case 0x52: case 0x5D:
        case 0x60: case 0x61: case 0x66: case 0x67: case 0x70: case 0x73: case 0x77: case 0x7B: case 0x89:
        case 0x8C: case 0x8E: case 0x8F: case 0x91: case 0x9E: case 0xA6: case 0xAB: case 0xAC: case 0xB2:
        case 0xB4: case 0x5B:
            hit_spark_sound_play(attacker, pos, (u8 *) dir, 9, (rec != NULL) ? *(f32 *)(rec + 4) : 0.0f);
            break;
    }
    count = obj[0x1CA];
    untouched = (count == 0) ? 1 : 0;
    flags |= 0x60000;
    if (rec != NULL && rec[0x59] == 3 && rec[0x58] == 0xA) {
        if (count >= 3) {
            obj[0x1CA] = count - 1;
        } else {
            obj[0x1CA] = 0;
            obj_set_dying_flags((struct127 *) obj);
            object_hit_effect((struct127 *) obj, 0xFF, 1);
            flags = 0x100020;
        }
    }
    object_impact_effects(obj, (f32 *) pos, pos2, dir, arg7, arg8);
    if (untouched != 0) {
        return;
    }
    w = (s32) (math_atan2f(dir[0], dir[2]) * 10430.378f);
    angle = (w < 0) ? 0xFFFF : w;
    obj_send_hit((struct127 *) obj, flags | 0x80000, (u16) ((angle - 0x4000) | 1),
                  (attacker != NULL) ? (struct127 *) attacker - g_objects : -1);
}

/* was func_151D56F8 */
void weapon_count_shot(u8 *arg0) {
    if (*(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x24) > 0) {
        *(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x24) -= 1;
    }
    *(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x1AA) += 1;
}

/* was func_151D5724 */
void weapon_find_aim_target(u8 *arg0, u8 *arg1, struct17 *arg2, struct17 *arg3, struct17 *arg4, u8 *arg5, u8 *arg6, u8 **arg7, u8 **arg8, u8 *arg9) {
    u8 *sp54;
    struct17 sp48;
    struct17 sp3C;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f12;
    f32 var_f14;
    f32 var_f16;
    f32 var_f18;
    u8 *temp_v0;
    u8 *temp_v0_2;

    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        temp_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
        if ((temp_v0 != NULL) && (((*(u8 *)((u8 *)temp_v0 + 0x198)) == 2) || ((*(u8 *)((u8 *)temp_v0 + 0x84)) != 0))) {
            sp54 = temp_v0 + 0x13C;
            vec3_cross(arg2, arg3, &sp48);
            vec3_cross(&sp48, arg4, &sp3C);
            if (arg9 != NULL) {
                var_f14 = (*(f32 *)((u8 *)arg9 + 0)) - (*(f32 *)((u8 *)sp54 + 0));
                var_f16 = (*(f32 *)((u8 *)arg9 + 4)) - (*(f32 *)((u8 *)sp54 + 4));
                var_f18 = (*(f32 *)((u8 *)arg9 + 8)) - (*(f32 *)((u8 *)sp54 + 8));
            } else {
                var_f14 = (*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)sp54 + 0));
                var_f16 = (*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)sp54 + 4));
                var_f18 = (*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)sp54 + 8));
            }
            temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x31C));
            temp_f0 = (*(f32 *)((u8 *)temp_v0_2 + 0x130));
            sp20 = sp3C.unk4;
            temp_f12 = (((*(f32 *)&(sp3C)) * var_f14) + (sp20 * var_f16) + (sp3C.unk8 * var_f18)) / (((*(f32 *)&(sp3C)) * temp_f0) + (sp3C.unk4 * (*(f32 *)((u8 *)temp_v0_2 + 0x134))) + (sp3C.unk8 * (*(f32 *)((u8 *)temp_v0_2 + 0x138))));
            (*(f32 *)((u8 *)arg5 + 0)) = (f32) ((*(f32 *)((u8 *)sp54 + 0)) + (temp_f12 * temp_f0));
            (*(f32 *)((u8 *)arg5 + 4)) = (f32) ((*(f32 *)((u8 *)sp54 + 4)) + (temp_f12 * (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x134))));
            (*(f32 *)((u8 *)arg5 + 8)) = (f32) ((*(f32 *)((u8 *)sp54 + 8)) + (temp_f12 * (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x138))));
            (*(f32 *)((u8 *)arg6 + 0)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x130));
            (*(f32 *)((u8 *)arg6 + 4)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x134));
            (*(f32 *)((u8 *)arg6 + 8)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x138));
            *arg7 = arg5;
            *arg8 = arg6;
            return;
        }
    }
    *arg7 = NULL;
    *arg8 = NULL;
}
s32 cam_wobble_start_preset(s32, s32, s32 *, s32, s32);

/* was func_151D58E4 */
void cam_shake_all_players(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6) {
    struct {
        s32 u3C;
        u8 pad40[0x8];
        f32 u48;
        f32 u4C;
        f32 u50;
    } sp;
    s32 var_s0;

    var_s0 = 0;
    (*(s32 *)((u8 *)(&sp.u3C) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u48 = arg1;
    sp.u4C = arg2;
    sp.u50 = arg3;
    if ((g_last_player_index + 1) > 0) {
        do {
            cam_wobble_start_preset(arg4 & 0xFF, var_s0 & 0xFF, &sp.u3C, arg5 & 0xFF, arg6);
            var_s0 += 1;
        } while (g_last_player_index >= var_s0);
    }
}
typedef struct {
    struct17 pos;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
} Blk_151D5404;
/* was func_151D5404 */
void rumble_all_players_at(struct17 *arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7) {
    s32 i;
    Blk_151D5404 sp38;
    structEU_151D8E18 sp30;
    s32 p;

    sp38.pos = *arg0;
    sp38.unkC = arg1;
    sp38.unk10 = arg2;
    sp38.unk14 = arg3;
    sp30.unk0 = 1;
    sp30.unk2 = (random_int() % (u32) (arg5 + 1)) + arg4;
    sp30.unk4 = 0;
    sp30.unk6 = 0;
    for (i = 0; i < g_last_player_index + 1; i++) {
        sp30.unk5 = 1 << i;
        sp38.unk18 = i;
        p = rumble_request(&sp30, 0x1C, 0xFF, 0);
        if (p != 0) {
            memcpy((u8 *)p + 0x18, &sp38, 0x1C);
        }
    }
}

/* P155 */
void emit_random_sprites(u8 *, u8, s32);
// smoke_cloud_spawn: spawns a smoke cloud at pos (f32[3]) through emit_random_sprites with a fixed emitter block (0x5C
// bytes: 9 puffs over 3 frames, colours 323 / 214 / 203 / 263, sizes 677..895, drift (0.602, -1.732, 1.512) at 45).
// Returns 0 (the asm leaves emit_random_sprites's v0; callers ignore it).
/* was func_151D5AC4 */
s32 smoke_cloud_spawn(u8 *pos, u8 arg1, s32 arg2) {
    struct {
        s16 u1C;
        s16 u1E;
        s16 u20;
        s16 u22;
        s32 u24;
        s32 u28;
        s32 pos[3];
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s32 u50;
        s32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s16 u70;
        s16 u72;
        s8 u74;
    } sp;

    sp.u1C = 0;
    sp.u1E = 0xFF;
    sp.u20 = -0x40;
    sp.u22 = 0x4A;
    sp.u24 = 9;
    sp.u28 = 3;
    sp.pos[0] = ((s32 *)pos)[0];
    sp.pos[1] = ((s32 *)pos)[1];
    sp.pos[2] = ((s32 *)pos)[2];
    sp.u38 = 323.0f;
    sp.u3C = 214.0f;
    sp.u40 = 203.0f;
    sp.u44 = 263.0f;
    sp.u48 = 677.0f;
    sp.u4C = 895.0f;
    sp.u50 = 7;
    sp.u54 = 3;
    sp.u58 = 45.0f;
    sp.u5C = 0.60200006f;
    sp.u60 = -1.7320001f;
    sp.u64 = 1.5120001f;
    sp.u68 = 0xF;
    sp.u6A = 0xF;
    sp.u6C = 0x64;
    sp.u6E = 0x64;
    sp.u70 = 0xC;
    sp.u72 = 0x14;
    sp.u74 = 0;
    emit_random_sprites((u8 *)&sp, arg1, arg2);
    return 0;
}

s32 spark_shower_spawn(u8 *, f32, f32, f32, f32, u8, s32); /* P95: f32 parameter */
s32 smoke_cloud_spawn(u8 *, u8, s32);

/* was func_151D5BF8 */
void explosion_smoke_flash_spawn(u8 *arg0, u8 arg1, s32 arg2) {

    smoke_cloud_spawn(arg0, arg1, arg2);
    explosion_light_spawn(arg0, arg1, arg2);
    spark_shower_spawn(arg0, (random_float() * 4.0f) + 12.0f, 1.6409999f, (random_int() % 56U) + 0xC8, 0.0f, arg1, arg2); /* P95: float literal (asm passes the bits 0x3FD20C49) */
}

/* P155 */
void mtx_transform_points(f32 **, f32 **, void *, s32);
void bone_streak_fx_start(u8 *, u8 *, s32, u8 *, f32, u8, s32);
// bone_beam_spawn: unless obj has no bone matrices (+0x1D4) or is hidden (+0x74 low nibble 0xF), transforms the
// points a and b by bone `bone` (mtx_transform_points, two points) and starts the effect bone_streak_fx_start at a's world
// position along b - a (with the bone matrix, obj, scale, alpha and flags).
/* was func_151D5714 */
void bone_beam_spawn(struct127 *obj, f32 *a, f32 *b, u8 bone, f32 scale, u8 alpha, s32 flags) {
    f32 *outs[2];
    f32 *ins[2];
    u8 *mtx;
    f32 dir[3];
    f32 at[3];

    if (obj->unk1D4 == NULL || (((u8 *)obj)[0x74] & 0xF) == 0xF) {
        return;
    }
    outs[0] = at;
    outs[1] = dir;
    mtx = (u8 *)obj->unk1D4 + bone * 64;
    ins[0] = a;
    ins[1] = b;
    mtx_transform_points(ins, outs, mtx, 2);
    dir[0] -= at[0];
    dir[1] -= at[1];
    dir[2] -= at[2];
    bone_streak_fx_start((u8 *)at, (u8 *)dir, (s32)mtx, (u8 *)obj, scale, alpha, flags);
}

extern f32 *g_mouth_points[]; /* P216: per-mouth point (2 entries); was D_8009002C */
extern u8 *g_mouth_bones[];  /* P216: per-mouth bone index (2 entries); was D_80090034 */
s32 ray_cast_world(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
void obj_notify_hit_target(struct127 *);
s32 object_mouth_point(struct127 *obj, f32 *out, f32 *dir, s32 arg3, s32 arg4, f32 *point, u8 bone);
// mouth_aim_ray: P216: for mouth `which` (0 / 1, table g_mouth_points point + g_mouth_bones bone): the mouth point and
// aim direction (object_mouth_point), the impact / target search (weapon_find_aim_target, two result pointers, NULL = use the
// mouth point / the direction), then the control block (obj +0x31C) gets flag +0x109 = 1 and the far point
// +0xB8 = hitA + hitB * 9999. The segment from the mouth to that point is normalised (vec3_normalize_len) and, when it has
// a length, cast as a ray (ray_cast_world, result at control +0xB0, range 1.01 * length). Ends with obj_notify_hit_target.
// Callers (obj_run_pending_actions, asm) ignore v0.
/* was func_151D5DA8 */
void mouth_aim_ray(struct127 *obj, u8 which) {
    f32 mouth[3];
    f32 dir[3];
    f32 sp94[3];
    f32 sp88[3];
    f32 sp7C[3];
    f32 sp70[3];
    f32 *hitA;
    f32 *hitB;
    f32 seg[3];
    f32 len;
    u8 *ctl;

    object_mouth_point(obj, mouth, dir, (s32)sp94, (s32)sp88, g_mouth_points[which], *g_mouth_bones[which]);
    weapon_find_aim_target((u8 *)obj, (u8 *)mouth, (struct17 *)dir, (struct17 *)sp94, (struct17 *)sp88, (u8 *)sp7C,
                  (u8 *)sp70, (u8 **)&hitA, (u8 **)&hitB, NULL);
    ((u8 *)obj->unk31C)[0x109] = 1;
    if (hitA == NULL) {
        hitA = mouth;
    }
    if (hitB == NULL) {
        hitB = dir;
    }
    *(f32 *)((u8 *)obj->unk31C + 0xB8) = hitA[0] + hitB[0] * 9999.0f;
    *(f32 *)((u8 *)obj->unk31C + 0xBC) = hitA[1] + hitB[1] * 9999.0f;
    *(f32 *)((u8 *)obj->unk31C + 0xC0) = hitA[2] + hitB[2] * 9999.0f;
    ctl = (u8 *)obj->unk31C;
    if (ctl[0x109] != 0) {
        seg[0] = *(f32 *)(ctl + 0xB8) - mouth[0];
        seg[1] = *(f32 *)((u8 *)obj->unk31C + 0xBC) - mouth[1];
        seg[2] = *(f32 *)((u8 *)obj->unk31C + 0xC0) - mouth[2];
        if (vec3_normalize_len(seg, seg, &len, NULL) != 0) {
            ray_cast_world(obj, mouth[0], mouth[1], mouth[2], seg[0], seg[1], seg[2], (u8 *)obj->unk31C + 0xB0,
                          len * 1.01f, 0, 0, 0, -1, 0, 0);
        }
    }
    obj_notify_hit_target(obj);
}

/* P155 */
void mtx_transform_points(f32 **, f32 **, void *, s32);
// object_mouth_point: P155: obj_get_aim_vectors (obj, dir, arg3, arg4, 0.811), then out = `point` transformed by obj's
// bone `bone` (mtx_transform_points) or, without bone matrices, obj's position + 49 up + 34 to the side of dir (x / z
// normalised, (0, 1) when both are below 0.0001). Returns 0 (the asm leaves v0 unset; the caller ignores it).
/* was func_151D5FC8 */
s32 object_mouth_point(struct127 *obj, f32 *out, f32 *dir, s32 arg3, s32 arg4, f32 *point, u8 bone) {
    f32 *ins[1];
    f32 *outs[1];
    f32 n;
    f32 sx, sz;

    obj_get_aim_vectors(obj, (s32)dir, arg3, arg4, 0.81100005f);
    if (obj->unk1D4 != NULL) {
        outs[0] = out;
        ins[0] = point;
        mtx_transform_points(ins, outs, (u8 *)obj->unk1D4 + bone * 64, 1);
        return 0;
    }
    if (fabsf(dir[0]) > 0.0001f || fabsf(dir[2]) > 0.0001f) {
        n = 1.0f / sqrtf(dir[0] * dir[0] + dir[2] * dir[2]);
        sz = dir[2] * n;
        sx = -dir[0] * n;
    } else {
        sz = 1.0f;
        sx = 0.0f;
    }
    out[0] = obj->x_position + 34.0f * sx;
    out[1] = obj->y_position + 49.0f;
    out[2] = obj->z_position + 34.0f * sz;
    return 0;
}

/* P159 */
extern s32 (*D_80087030[])(u8 *, s32, s32);
// objects_hit_by_segment: tests the segment start / dir (ray_sphere_intersect) against every live object of g_objects
// (not self, kind byte +4 not 0xFF unless level 0x23, state +5 not 3, flag 0x40 at +0xF8, passing filter
// D_80087030[filter](obj, self, filterArg) unless filter is -1) as a sphere at its position raised by +0xD6 with
// diameter 2 * max(+0xD2, +0xD4). Returns a mask with bit i cleared for each hit object i (all other bits set).
/* was func_151D611C */
s32 objects_hit_by_segment(u8 *start, s32 *dir, u8 *self, s8 filter, s32 filterArg) {
    f32 center[3];
    f32 out0[3];
    f32 out1[3];
    f32 dist0;
    f32 dist1;
    f32 radius;
    s32 mask;
    u8 i;
    u8 *obj;

    mask = -1;
    for (i = 0; i < 25; i++) {
        obj = (u8 *)&g_objects[i];
        if (*(s32 *)(obj + 0) == 0) {
            continue;
        }
        if (obj[5] == 3) {
            continue;
        }
        if (g_level_id != 0x23 && obj[4] == 0xFF) {
            continue;
        }
        if (obj == self) {
            continue;
        }
        if ((*(s32 *)(obj + 0xF8) & 0x40) == 0) {
            continue;
        }
        if (filter != -1 && D_80087030[filter](obj, (s32)self, filterArg) == 0) {
            continue;
        }
        if (*(s16 *)(obj + 0xD2) < *(s16 *)(obj + 0xD4)) {
            radius = *(s16 *)(obj + 0xD4);
        } else {
            radius = *(s16 *)(obj + 0xD2);
        }
        center[0] = *(f32 *)(obj + 0x14);
        center[1] = *(f32 *)(obj + 0x18) + (f32)*(s16 *)(obj + 0xD6);
        center[2] = *(f32 *)(obj + 0x1C);
        if (ray_sphere_intersect((struct17 *)start, (struct17 *)dir, (struct17 *)center, radius + radius, (s32)out0,
                          (s32)out1, &dist0, &dist1)) {
            mask &= ~(1 << i);
        }
    }
    return mask;
}

s32 allocate_memory(s32, s32, s32, s32);

/* was func_151D6310 */
void vtx_slot_buffer_get(s32 *arg0, s16 arg1, s32 arg2, s32 *arg3, u8 *arg4) {
    u8 dummy;

    if (arg4 == NULL) {
        arg4 = &dummy;
    }
    *arg4 = 0;
    if (arg0[arg1] == 0) {
        arg0[arg1] = allocate_memory(arg2 * 2, 1, 2, 1);
        if (arg0[arg1] == 0) {
            *arg3 = 0;
            return;
        }
        *arg4 = 1;
    }
    *arg3 = arg0[arg1] + (g_dl_buf_index ? 0 : arg2);
}

/* was func_151D5E30 */
void vtx_slot_buffers_free(s32 **arg0)
{
  s32 *new_var;
  u8 i;
  for (i = 0; i < 4; i++)
  {
    s32 *t = arg0[i];
    if (1)
    {
    }
    if (t)
    {
      new_var = arg0[i]; // fakematch: re-load of the element after the test
      heap_set_block_tag(new_var, 3);
 } }
}
