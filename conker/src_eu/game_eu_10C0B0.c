#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150DE8A0 */
void zone_stub(s32 arg0) {
}

extern u8 g_trigger_zone_ids[8]; /* was D_80088CF0 */
extern u8 g_trigger_zone_objs[8]; /* was D_80088CF8 */
s32 trigger_contains_point(u8 *, s32, s32, s32);
u8 *world_record_find(u8);
void trigger_set_disabled(s32, s32);

// trigger_zones_check: hit callback (g_level_point_hit_cb, set in game_3DC30) for the point (x, y, z): for each of
// the 8 zones g_trigger_zone_ids (g_level_zones records of 0x34 bytes) that contains it (trigger_contains_point), the matching
// g_trigger_zone_objs object id gets state 3 in its +0x73 low bits (world_record_find), or the zone itself is triggered
// (trigger_set_disabled(zone, 1)) when the id is 0. Returns 0 (the asm leaves the last helper's v0; the caller
// ignores it).
/* was func_150DE8AC */
s32 trigger_zones_check(s32 x, s32 y, s32 z) {
    u8 *obj;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (trigger_contains_point(g_level_zones + g_trigger_zone_ids[i] * 0x34, x, y, z) != 0) {
            if (g_trigger_zone_objs[i] != 0) {
                obj = world_record_find(g_trigger_zone_objs[i]);
                obj[0x73] = (obj[0x73] & ~3) | 3;
            } else {
                trigger_set_disabled(g_trigger_zone_ids[i], 1);
            }
        }
    }
    return 0;
}

s32 texture_cache_lookup(s32, s32 *, s32, s32);
void segment_override_add(s32, s32, s32, s32, s32);
extern s32 g_zone_debris_tex_sets; /* was D_800905B4 */

/* was func_150DE9D8 */
void zone_debris_fall_update(u8 *arg0) {
    struct {
        s32 u54;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    s32 *var_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s2;

    if (((*(u8 *)((u8 *)arg0 + 0x73)) & 3) == 3) {
        temp_f12 = (f32) g_frame_ticks;
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0)) + ((*(f32 *)((u8 *)arg0 + 0x60)) * temp_f12));
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0));
        if (temp_f0 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0 + 360.0f);
        } else if (temp_f0 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0 - 360.0f);
        }
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 4)) + ((*(f32 *)((u8 *)arg0 + 0x64)) * temp_f12));
        temp_f0_2 = (*(f32 *)((u8 *)arg0 + 4));
        if (temp_f0_2 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_2 + 360.0f);
        } else if (temp_f0_2 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_2 - 360.0f);
        }
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) ((*(f32 *)((u8 *)arg0 + 8)) + ((*(f32 *)((u8 *)arg0 + 0x68)) * temp_f12));
        temp_f0_3 = (*(f32 *)((u8 *)arg0 + 8));
        if (temp_f0_3 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0_3 + 360.0f);
        } else if (temp_f0_3 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0_3 - 360.0f);
        }
        (*(s16 *)((u8 *)arg0 + 0x5C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x5C)) - ((*(s32 *)((u8 *)arg0 + 0x3C)) * g_frame_ticks));
        (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x10)) + ((*(s16 *)((u8 *)arg0 + 0x5A)) * g_frame_ticks));
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) + ((*(s16 *)((u8 *)arg0 + 0x5C)) * g_frame_ticks));
        (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x14)) + ((*(s16 *)((u8 *)arg0 + 0x5E)) * g_frame_ticks));
        temp_v0 = (*(u8 *)((u8 *)arg0 + 0x8A)) - g_frame_ticks;
        if (temp_v0 > 0) {
            (*(u8 *)((u8 *)arg0 + 0x8A)) = (u8) temp_v0;
        } else {
            (*(s8 *)((u8 *)arg0 + 0x6E)) = 1;
        }
    }
    if (((*(u16 *)((u8 *)arg0 + 0x54)) & 0xFFFF7FFF) == 0xC) {
        var_s2 = 4;
        var_s1 = (s32 *) ((u8 *) &g_zone_debris_tex_sets + (*(s32 *)((u8 *)arg0 + 0x7C)) * 8);
        var_s0 = 5;
        do {
            temp_v0_2 = texture_cache_lookup(*var_s1, &sp.u54, 3, 0);
            segment_override_add(arg0, temp_v0_2, (sp.u54 + temp_v0_2) - 0x200, var_s2, var_s0);
            var_s0 += 2;
            var_s1++;
            var_s2 += 2;
        } while (var_s0 != 9);
    }
}
/* was func_150DEC58 */
void obj_sine_wobble_update(u8 *arg0) {
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((math_sin_u8(((s32) (*(s32 *)((u8 *)arg0 + 0x7C)) >> 3) & 0xFF) * 10.2f) + 1130.0f);
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) (math_sin_u8(((s32) (*(s32 *)((u8 *)arg0 + 0x80)) >> 3) & 0xFF) * 1.1f);
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) (math_sin_u8(((s32) (*(s32 *)((u8 *)arg0 + 0x84)) >> 3) & 0xFF) * 1.1f);
    (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x7C)) + (g_frame_ticks * 0xC));
    (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x80)) + (g_frame_ticks * 0x10));
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) + (g_frame_ticks * 0x18));
}
void spawn_region_random_point_3d(u8 *, f32 *);
s32 vec3_normalize_len(f32 *, f32 *, f32 *, f32 *);
s32 memcpy(u8 *, void *, s32);

// beam_link_fire: timer handler of a link effect p (timer s16 at p+0x28, two objects at p+0x2C / p+0x30). When the
// timer runs out (minus g_frame_ticks) it fires a bolt (effect3d_spawn_full template, kind 0xBE or 0xBF at random, size 706,
// at the first object's position) towards the second object at speed 25..55 (x0.18 for kind 0xBF); the bolt's +0x110
// gets {velocity, travel time = distance / speed, the flat side vector (-z, 0, x) and flat direction (x, 0, z) of the
// normalised horizontal offset}. The timer restarts at 200..400.
/* was func_150DED40 */
void beam_link_fire(u8 *p) {
    struct {
        u8 kind;            /* 0x00 */
        u8 u1;              /* 0x01 */
        s16 u2;             /* 0x02 */
        s16 u4;             /* 0x04 */
        u8 pad6[2];
        s32 u8;             /* 0x08 */
        s32 uC;             /* 0x0C */
        u8 colour[4];       /* 0x10 */
        f32 size[2];        /* 0x14 */
        f32 pos[3];         /* 0x1C */
        f32 u28[3];         /* 0x28 */
        f32 scale[3];       /* 0x34 */
        s32 mode;           /* 0x40 */
        u8 u44[4];          /* 0x44 */
        s32 u48;            /* 0x48 */
        u8 u4C;             /* 0x4C */
        u8 pad4D[3];
        s32 u50;            /* 0x50 */
        s16 u54;            /* 0x54 */
        s16 u56;            /* 0x56 */
    } t;
    struct {
        f32 vel[3];         /* 0x00 */
        f32 time;           /* 0x0C */
        f32 side[3];        /* 0x10 */
        f32 flat[3];        /* 0x1C */
    } rec;
    s32 kinds[2];
    f32 to[3];
    f32 d[3];
    f32 len;
    f32 unused;
    f32 speed;
    f32 spd;
    s16 *timer;
    u8 *e;

    *(s16 *) (p + 0x28) -= g_frame_ticks;
    if (*(s16 *) (p + 0x28) >= 0) {
        return;
    }
    kinds[0] = 0xBE;
    kinds[1] = 0xBF;
    t.kind = kinds[random_int() & 1];
    timer = (s16 *) (p + 0x28);
    spawn_region_random_point_3d(*(u8 **) (p + 0x2C), t.pos);
    spawn_region_random_point_3d(*(u8 **) (p + 0x30), to);
    d[0] = to[0] - t.pos[0];
    d[1] = to[1] - t.pos[1];
    d[2] = to[2] - t.pos[2];
    vec3_normalize_len(d, rec.vel, &len, &unused);
    speed = random_float() * 30.0f + 25.0f;
    spd = speed;
    if (t.kind == 0xBF) {
        spd = speed * 0.18f;
    }
    rec.vel[0] *= spd;
    rec.vel[1] *= spd;
    rec.vel[2] *= spd;
    rec.time = len / spd;
    rec.flat[0] = d[0];
    rec.flat[1] = 0.0f;
    rec.flat[2] = d[2];
    vec3_normalize_len(rec.flat, rec.flat, NULL, NULL);
    rec.side[0] = -rec.flat[2];
    rec.side[1] = 0.0f;
    rec.side[2] = rec.flat[0];
    t.u28[0] = ((f32 *) g_vec3_zero)[0];
    t.u28[1] = ((f32 *) g_vec3_zero)[1];
    t.u28[2] = ((f32 *) g_vec3_zero)[2];
    t.u1 = 0;
    t.u2 = 0x3B03;
    t.u4 = 300;
    t.u8 = 0;
    t.uC = 0;
    t.colour[0] = 0xFF;
    t.colour[1] = 0xFF;
    t.colour[2] = 0xFF;
    t.colour[3] = 0xFF;
    random_float(); /* result unused */
    t.size[1] = 706.0f;
    t.size[0] = 706.0f;
    t.u28[0] = ((f32 *) g_vec3_zero)[0];
    t.u28[1] = ((f32 *) g_vec3_zero)[1];
    t.u28[2] = ((f32 *) g_vec3_zero)[2];
    t.mode = 0x65C0000;
    t.u44[0] = 0xFF;
    t.u44[1] = 0xFF;
    t.u44[2] = 0;
    t.u44[3] = 7;
    t.u48 = 0;
    t.u4C = 0xFF;
    t.u50 = 0;
    t.u54 = 1;
    t.u56 = 0xFF;
    t.scale[0] = 1.0f;
    t.scale[1] = 1.0f;
    t.scale[2] = 1.0f;
    e = effect3d_spawn_full(&t, (s32) &g_effect3d_default_params, 0x28, 0, 0, 0x26, 0, 3, 0xFF, 0x28, p[0xC], p[1]);
    if (e != NULL) {
        memcpy(e + 0x110, &rec, 0x28);
    }
    *timer = (u32) random_int() % 201 + 200;
}

/* was func_150DF04C */
s32 bolt_move_step(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg0 + 0x110)) * g_frame_step_f);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg0 + 0x114)) * g_frame_step_f);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg0 + 0x118)) * g_frame_step_f);
    (*(f32 *)((u8 *)arg0 + 0x11C)) -= g_frame_step_f;
    if ((*(f32 *)((u8 *)arg0 + 0x11C)) < 0.0f) {
        return 0;
    }
    return 1;
}

s32 sprite_quad_build_axes(s32, s32, s32, s16);
/* was func_150DF0D8 */
s32 bolt_build_quad(s32 arg0, s16 arg1) {
    if (g_player_views[g_last_player_index].unk388 < 5.0f) {
        return 0;
    }
    return sprite_quad_build_axes(arg0, arg0 + 0x120, arg0 + 0x12C, arg1);
}

void light_group_send_msg22(u8 arg0, s32 arg1);

/* was func_150DF160 */
void light_groups_send_msg22_all(s32 arg0) {
    u8 i;

    for (i = 0; i < 4; i++) {
        light_group_send_msg22(i, 1);
    }
}

extern u8 g_light_group_ctrl_ids[]; /* was D_800A10DB */
extern u8 g_light_group_fx_ids[]; /* was D_800A10FB */
/* was func_150DF1A8 */
void light_group_send_msg22(u8 arg0, s32 arg1) {
    s32 i = arg0 * 4;
    light_ctrl_broadcast(g_light_group_ctrl_ids[i], 0x22, 0);
    effect_broadcast_message(g_light_group_fx_ids[i], 0x22);
}
