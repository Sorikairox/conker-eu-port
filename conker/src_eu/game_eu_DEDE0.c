#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_150B15D0 */
void obj_whirlpool_pull_update(struct127 *arg0) {
    s32 pad;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f0_2;
    f32 temp_f2;
    u16 temp_v1;

    arg0->unk174 = arg0->x_position;
    arg0->unk178 = arg0->z_position;
    arg0->immune = 0x64;
    arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
    if (obj_dist_xz(g_objects, arg0) < 1100.0f) {
        temp_f0 = obj_dist_xz(arg0, g_objects);
        temp_f16 = temp_f0;
        temp_f2 = arg0->y_position - g_objects->y_position;
        if (temp_f2 < 0.0f) {
            temp_f2 = 1000.0f;
        } else {
            temp_f2 = 1050.0f - (temp_f2 * 0.7f);
        }
        if ((temp_f0 < temp_f2) && (g_objects->in_water == 1)) {
            
            temp_f0_2 = 1100.0f - temp_f16;
            temp_v1 = math_atan2_u16(arg0->unk174 - g_objects->x_position, g_objects->z_position - arg0->unk178, 0);
            if (temp_f0_2 > 850.0f) {
                temp_f2 = (temp_f0_2 - 820.0f) * 0.09f;
                *g_obj0_y = g_objects->y_position - *g_obj_time_step * (0, temp_f2);
            }
            vec_from_yaw_pitch(temp_v1 - 0x3000, (temp_f0_2 * 0.045f) + 5.0f, 0.0f, &sp50, &sp4C, &sp48);
            g_objects->unk164 = sp50;
            g_objects->unk168 = sp4C;
        }
    }
    obj_start_anim(arg0, 0U, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

extern f32 D_8009FC8C;
extern f32 D_8009FC90;
void cutscene_actor_apply_track(struct127 *, s32, s32);
void obj_walk_update(struct127 *);
s32 obj_check_death(struct127 *);

/* was func_150B17DC */
void obj_path_bank_update(struct127 *arg0) {
    f32 var_f2;
    f32 var_f0;
    f32 temp_f2;
    f32 temp_f12;
    f32 temp_f0;
    s16 sp34;

    arg0->unk80 = 0xA;
    sp34 = arg0->unk76;
    temp_f0 = (f32) (*(s16 *)((u8 *)(D_800D2104[arg0->unk13F]) + 2));
    obj_set_gravity_band(arg0, temp_f0, 1.0f, temp_f0, D_8009FC8C, 12.0f, -16.0f);
    obj_walk_update(arg0);
    var_f2 = 6.0f;
    temp_f12 = arg0->unkC4;
    var_f0 = ((f32) (s16) ((sp34 - arg0->unk76) * 6) * 0.00390625f) - temp_f12;
    if (var_f0 > 6.0f) {
        goto block_3;
    }
    var_f2 = -6.0f;
    if (var_f0 < -6.0f) {
block_3:
        var_f0 = var_f2;
    }
    temp_f2 = arg0->unk148;
    arg0->unk148 = temp_f2 + ((var_f0 - temp_f2) * D_8009FC90);
    arg0->unkC4 = temp_f12 + arg0->unk148;
    arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
    obj_physics_step(arg0);
    if (obj_check_death(arg0) == 0) {
        cutscene_actor_apply_track(arg0, 0, -1);
    }
}

void obj_stun_update(struct127 *);
void obj_lean_into_turn(struct127 *, s16);

// held_object_update: update of an object that may be held, thrown or resting: unk80 = 10; stunned objects only run
// obj_stun_update. Otherwise its resting height is 210 above the floor entry D_800D20FC[unk13F] (+8), the vertical
// bounce speed unkB8 is -vy / 2 (0 in mode 3) unless unk22C bit 3; in mode 14 (unk223) it is pulled towards object
// unk222 (no gravity, vy = (its height + unk224 - y) / (distance obj_dist_xz / speed)); otherwise (mode 1: 210 above
// the player) the height comes from unk224 (10000: the D_800D2104 path point unk21E, else 8 x unk224, + unk180 for
// all but kinds 5 / 0x50 / 0xAD..0xAF) and, unless unk100 bit 6, the collision box (obj_set_gravity_band, 3 x 12 for kind
// 0x44 at its path point height, else 5 x 35). Then the move (obj_walk_update), the facing unk40 from unk7A, the
// animation (obj_physics_step), kinds 5 / 0xAD..0xAF / 0x44 turn from the old heading (obj_lean_into_turn), and the object
// is released (cutscene_actor_apply_track) when obj_check_death says so.
/* was func_150B1964 */
void held_object_update(struct127 *obj) {
    s16 heading;
    f32 height;
    f32 half;
    f32 depth;
    struct127 *target;
    f32 dist;
    s16 level;

    heading = obj->unk76;
    obj->unk80 = 10;
    if (obj->stunned == 0) {
        height = *(s16 *) ((u8 *) D_800D20FC + obj->unk13F * 0x30 + 8) + 210.0f;
        if (!(obj->unk22C & 8)) {
            if (obj->unk223 == 3) {
                obj->unkB8 = 0.0f;
            } else {
                obj->unkB8 = obj->y_velocity * -0.5f;
            }
        }
        if (obj->unk223 == 14) {
            target = &g_objects[obj->unk222];
            dist = obj_dist_xz(target, obj);
            obj->gravity = 0.0f;
            obj->y_velocity = (g_objects[obj->unk222].y_position + (s16) obj->unk224 - obj->y_position) /
                              (dist / obj->xz_velocity);
        } else {
            if (obj->unk223 == 1) {
                height = g_objects[0].y_position + 210.0f;
            }
            level = obj->unk224;
            if (level != 0) {
                if (level == 10000) {
                    height = *(s16 *) ((u8 *) D_800D2104[obj->unk13F] + obj->unk21E * 8 + 0xA);
                } else if (obj->id == 0x50 || obj->id == 5 || obj->id == 0xAD || obj->id == 0xAE ||
                           obj->id == 0xAF) {
                    height = level * 8;
                } else {
                    height = level * 8 + obj->unk180;
                }
            }
            if (!(obj->unk100 & 0x40)) {
                if (obj->id == 0x44) {
                    height = *(s16 *) ((u8 *) D_800D2104[obj->unk13F] + obj->unk21E * 8 + 0xA);
                    half = 3.0f;
                    depth = 12.0f;
                } else {
                    half = 5.0f;
                    depth = 35.0f;
                }
                obj_set_gravity_band(obj, height, half, height, -half, depth, -depth);
            }
        }
        obj_walk_update(obj);
    } else {
        obj_stun_update(obj);
    }
    obj->unk40 = (f32) (s16) (obj->unk7A + 0x4000) * 0.0054931640625f;
    obj_physics_step(obj);
    if (obj->id == 5 || obj->id == 0xAD || obj->id == 0xAE || obj->id == 0xAF || obj->id == 0x44) {
        obj_lean_into_turn(obj, heading);
    }
    if (obj_check_death(obj) == 0) {
        cutscene_actor_apply_track(obj, 0, -1);
    }
}

void obj_walk_update(struct127 *);
void obj_apply_gravity(struct127 *);
u8 *obj_find_by_state(s32, s32 *);

/* was func_150B1CBC */
void obj_carrier_update(struct127 *arg0) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        u8 pad38[0x4];
        s32 u3C;
    } sp;
    f32 var_f12;
    u16 temp_v0;
    u8 temp_t9;
    u8 *temp_s0;

    temp_s0 = obj_find_by_state(0xA, &sp.u3C);
    obj_walk_update(arg0);
    if (arg0->unk1E5 == 2) {
        arg0->x_position = (*(f32 *)((u8 *)temp_s0 + 0x14));
        arg0->z_position = (*(f32 *)((u8 *)temp_s0 + 0x1C));
        arg0->y_velocity = 0.0f;
        arg0->y_position = (*(f32 *)((u8 *)temp_s0 + 0x18)) + ((f32) ((s32) arg0->unk21C / 5) + 160.0f);
        arg0->unk7E = 0;
        arg0->gravity = -0.35f;
    } else {
        temp_t9 = arg0->unk7E;
        var_f12 = (f32) temp_t9;
        if ((s32) temp_t9 < 0) {
            var_f12 += 4294967296.0f;
        }
        (*(f32 *)((u8 *)temp_s0 + 0xB8)) = (f32) (fast_sinf(var_f12 * 0.2f) * 6.0f);
        obj_apply_gravity(arg0);
        (*(f32 *)((u8 *)temp_s0 + 0x18)) = (f32) (arg0->y_position - 170.0f);
        (*(s8 *)((u8 *)temp_s0 + 0x13C)) = (s8) (g_cur_obj_index + 0x64);
        vec_from_yaw_pitch((*(u16 *)((u8 *)temp_s0 + 0x7A)), (*(f32 *)((u8 *)temp_s0 + 0xB8)) * -7.0f, 0.0f, &sp.u34, &sp.u30, &sp.u2C);
        (*(f32 *)((u8 *)temp_s0 + 0x14)) = (f32) (arg0->x_position + sp.u34);
        (*(f32 *)((u8 *)temp_s0 + 0x1C)) = (f32) (arg0->z_position + sp.u30);
        (*(u16 *)((u8 *)temp_s0 + 0x7A)) = (u16) ((*(u16 *)((u8 *)temp_s0 + 0x7A)) + (D_800BE9A0 << 8));
        arg0->unk7E += D_800BE9A0;
        (*(s8 *)((u8 *)temp_s0 + 0xAD)) = 0;
        (*(f32 *)((u8 *)temp_s0 + 0x3C)) = 0.0f;
        (*(f32 *)((u8 *)temp_s0 + 0x16C)) = 0.0f;
        (*(f32 *)((u8 *)temp_s0 + 0x170)) = 0.0f;
    }
    temp_v0 = math_atan2_u16(g_objects->x_position - arg0->x_position, arg0->z_position - g_objects->z_position, 0);
    arg0->unk7A = temp_v0;
    arg0->unk40 = (f32) (s16) (temp_v0 + 0x4000) * 0.005493164f;
}
extern u8 D_800B8AC4[];
extern s32 D_800CC670;
extern s32 D_8008CE80;
void obj_carried_update(struct127 *);
void obj_find_carrier(struct127 *);
f32 math_cos_u8(u8);
void collision_select_area(s32);
s32 collision_level_nearest_height(s32, s32, s32, s32 *);
void *node_spawn_sprite(void *, s32, s32, s8, u8, s32);

// sinking_object_update: per-frame update of an object sinking / floating in water: flags (0x80, 0x4 while moving
// faster than 1), unkB0 25, stunned 10, unk239 3, unkFC 0xA7, unk80 1; a pending reset (unk25C bit 6) puts its old
// position on the player's. In a water region (unk13D) it calls obj_carried_update and sinks (unkB8 eases towards -20 with
// factor 0.2, else towards 0) once unk21C reaches 9, unless the region's D_800B8AC4 entry is set and D_800CC670 bit 2
// is clear. Facing / animation / obj_find_carrier / obj_start_anim / release as usual. In water, 40 in 256 frames spawn
// a ripple record (node_spawn_sprite) at a random point up to 40 x xz_scale around it, drifting with the player's speed.
/* was func_150B1EC0 */
void sinking_object_update(struct127 *obj) {
    struct {
        s32 u00;
        s32 u04;
        s32 u08;
        s16 u0C;
        s16 u0E;
        s16 pos[3];
        s16 u16;
        s16 u18;
        s16 u1A;
        u8 pad1C[3];
        u8 u1F;
        s16 u20;
        s16 u22;
        s16 u24;
        s16 u26;
        s16 u28;
        u8 u2A;
        u8 u2B;
        u8 u2C;
        u8 u2D;
        u8 u2E;
        u8 u2F;
        u8 pad30[4];
        s16 u34;
    } rec;
    f32 target;
    f32 dist;
    f32 s;
    f32 c;
    f32 speed;
    u8 a;
    u8 r;

    obj->unkF8 &= ~4;
    obj->unkB0 = 25;
    obj->unk13C = 0;
    obj->unkF8 |= 0x80;
    if (1.0f < obj->xz_velocity) {
        obj->unkF8 |= 4;
    }
    obj->stunned = 10;
    obj->unk239 = 3;
    obj->unkFC = 0xA7;
    obj->unk80 = 1;
    if (obj->unk25C & 0x40) {
        obj->unk25C &= ~0x40;
        obj->old_x_position = g_objects[0].x_position;
        obj->old_z_position = g_objects[0].z_position;
    }
    target = 0.0f;
    if (obj->unk13D != 0) {
        obj_carried_update(obj);
        if ((D_800B8AC4[obj->unk13D * 0x32C] == 0 || (D_800CC670 & 4)) && obj->unk21C >= 9) {
            target = -20.0f;
        }
    }
    obj->unkB8 = obj->unkB8 + (target - obj->unkB8) * 0.2f;
    obj->unk40 = (f32) (s16) (obj->unk7A + 0x4000) * 0.0054931640625f;
    obj_physics_step(obj);
    obj_find_carrier(obj);
    obj_start_anim(obj, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0);
    cutscene_actor_apply_track(obj, 0, -1);
    if (obj->unk13D == 0 || (u8) random_int() >= 40) {
        return;
    }
    dist = obj->xz_scale * (f32) ((u32) random_int() % 40);
    a = random_int();
    s = math_cos_u8(a);
    c = math_sin_u8(a);
    rec.u00 = D_8008CE80;
    rec.u0C = 0;
    rec.u0E = 0;
    rec.pos[0] = (s32) (obj->x_position + s * dist);
    rec.pos[1] = (s32) obj->y_position;
    rec.pos[2] = (s32) (obj->z_position + c * dist);
    collision_select_area(0);
    rec.u04 = collision_level_nearest_height(rec.pos[0], rec.pos[1], rec.pos[2], NULL);
    speed = g_objects[0].xz_velocity * 64.0f;
    a = g_objects[0].unk76 >> 8;
    rec.u16 = (s32) (math_cos_u8(a) * speed);
    rec.u18 = (s32) (math_sin_u8(a) * -speed);
    rec.u1A = -30;
    rec.u1F = 7;
    rec.u20 = 0;
    rec.u22 = -80;
    r = random_int();
    rec.u24 = (r << 12) / 5100 + 204;
    rec.u26 = (r << 12) / 12750 + 81;
    rec.u28 = 400;
    rec.u2A = 0;
    rec.u2B = r;
    rec.u2C = 0xFF;
    rec.u2D = 0xFF;
    rec.u2E = 0;
    rec.u2F = 0xFF;
    rec.u34 = 0;
    node_spawn_sprite(&rec, 0, 0, -1, 0xFF, 0);
}
