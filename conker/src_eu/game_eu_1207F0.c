#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_drip_bone_pt_a[]; /* was D_800A1D20 */


extern u8 g_held_item_obj_id; /* was D_800CC82C */
extern u8 g_player_health; /* was D_800CC8BA */
extern s32 *g_world_obj_rider_masks; /* was D_800DC3C4 */
s32 world_record_find(u8);
s32 object_hit_effects(void *, s32, s32, s32, s32, s32, s32, s32);
s32 player_hit_reaction(struct127 *, s32);
void texscroll_set_speed(u8 *, s32, s32);

// player_item_drop_check: unless the player's held object (g_obj0_state, byte 0x120) is busy, checks items 0xFA and
// 0xF9 (world_record_find; entry index = (item - g_world_objs) / 160 into the flag words at g_world_obj_rider_masks). The first one
// with bit 0 set: releases the player's current carried object (obj_remove), clears g_player_health and resets the
// player (object_hit_effects, sound 0x627 via actor_sound_play_untracked, obj_set_destroyed, mode 6 via player_hit_reaction). Then the four
// g_level_scroll_handles nodes are offset by +-object 0xE's +0x2E4 value (texscroll_set_speed).
/* was func_150F2FE0 */
void player_item_drop_check(s32 arg0) {
    struct127 *o;
    s32 off;
    s32 i;
    s32 item;

    if (g_obj0_state == NULL || g_obj0_state[0x120] != 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        item = world_record_find(0xFA - i);
        if (g_world_obj_rider_masks[(item - (s32) g_world_objs) / 160] & 1) {
            if (g_held_item_obj_id != 0) {
                obj_remove((struct127 *) ((u8 *) g_objects + (g_held_item_obj_id - 100) * 0x32C), 0);
            }
            g_player_health = 0;
            object_hit_effects(g_objects, 0, 0, 1, 1, 0, 0xFF, 1);
            actor_sound_play_untracked(0x627, g_objects, 0x6D60, 0x1F4, 0x3E8);
            obj_set_destroyed(g_objects);
            player_hit_reaction(g_objects, 6);
            break;
        }
    }
    o = obj_find_by_setup_id(0xE);
    off = (o != NULL) ? *(s32 *) ((u8 *) o + 0x2E4) : 0;
    texscroll_set_speed(((u8 **) g_level_scroll_handles)[0], off, 0);
    texscroll_set_speed(((u8 **) g_level_scroll_handles)[1], 0, -off);
    texscroll_set_speed(((u8 **) g_level_scroll_handles)[2], off, 0);
    texscroll_set_speed(((u8 **) g_level_scroll_handles)[3], -off, 0);
}

/* was func_150F320C */
void drip_emitter_spawn(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        f32 unk8;
        u8 unkC;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = 0;
    tmp.unk8 = 0.0f;
    tmp.unkC = 0;
    temp_v0 = effect_node_create(300, -1, 0x5C, -1, 0, 0x44, 0x10, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

void obj_tint_set_flash(u8 *, s32, s32, s32, s32, s32, s32);
void mtx_transform_points(f32 **, f32 **, void *, s32);
s32 vec3_make_basis(f32 *, s32 *, s32 *);
void *effect3d_spawn_full(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9,
                    u8 argA, s32 argB);
extern u8 g_drip_bone_pt_b[];  /* second bone-space point (after g_drip_bone_pt_a); was D_800A1D20; was D_800A1D2C */
extern f32 g_drip_rate;   /* drops per frame unit; was D_800A1D38 */
extern f32 g_drip_trail_k_1d3c; /* was D_800A1D3C */

// drip_emitter_update: object update of a drip emitter (record at +0x28: owner, +4 owner id, +5 last owner
// state, +8 f32 accumulator, +0xC s8 drops left). Stops when the cutscene flag D_800C35EA is 1; ends the object
// (+0xE = -1) when the owner is gone or its id changed. A new non-zero owner state (+0x222) refills 3 drops; while
// the state is set, obj_tint_set_flash runs on object g_objects[state]. With a model, the accumulator grows by
// g_drip_rate * frame time and every whole unit drops one: the line between the bone points g_drip_bone_pt_a / g_drip_bone_pt_b
// (bone matrix +0x3C0) is probed (vec3_make_basis) and a drop sprite (effect3d_spawn_full, template D_800A4AA0, size
// 60..100, alpha 0x34-byte trail record copied to +0x110) is spawned at the first point.
/* was func_150F3294 */
void drip_emitter_update(u8 *obj) {
    struct {
        u8 *owner;
        u8 id;
        u8 pad5[3];
        f32 t;
        f32 size;
        f32 unk10;
        f32 speed;
        f32 accel;
        s32 hit[3];
        s32 normal[3];
    } trail;
    struct {
        u8 type;
        u8 unk1;
        s16 tex;
        s16 life;
        u8 pad6[2];
        s32 unk8;
        s32 unkC;
        u8 col[4];
        f32 unk14;
        f32 unk18;
        f32 pos[3];
        s32 unk28[3];
        f32 scale[3];
        s32 unk40;
        u8 alpha;
        u8 unk45;
        u8 unk46;
        u8 unk47;
        s32 unk48;
        u8 unk4C;
        u8 pad4D[3];
        s32 unk50;
        s16 unk54;
        s16 unk56;
    } spr;
    f32 *in[2];
    f32 *out[2];
    f32 dir[3];
    u8 *st = obj + 0x28;
    u8 *owner;
    u8 state;
    void *p;

    if (D_800C35EA == 1) {
        return;
    }
    owner = *(u8 **) st;
    if (*(s32 *) owner == 0 || st[4] != owner[0x3B]) {
        *(s16 *) (obj + 0xE) = -1;
        return;
    }
    state = owner[0x222];
    if (state != st[5] && state != 0) {
        st[0xC] = 3;
        *(f32 *) (st + 8) = 0.0f;
    }
    st[5] = owner[0x222];
    state = owner[0x222];
    if (state != 0) {
        obj_tint_set_flash((u8 *) g_objects + state * 0x32C, 0xFF, 0, 0, 0x50, 0, 0xF);
    }
    if (*(u8 **) (owner + 0x1D4) == NULL) {
        return;
    }
    if (*(s8 *) (st + 0xC) <= 0) {
        return;
    }
    *(f32 *) (st + 8) += g_drip_rate * g_frame_step_f;
    if (!(1.0f < *(f32 *) (st + 8))) {
        return;
    }
    do {
        trail.owner = owner;
        trail.id = owner[0x3B];
        trail.t = 0.0f;
        trail.size = random_float() * 6.0f + 13.0f;
        trail.unk10 = g_drip_trail_k_1d3c;
        trail.speed = random_float() * 40.0f + 60.0f;
        trail.accel = trail.speed / (trail.size * trail.size);
        in[0] = (f32 *) g_drip_bone_pt_a;
        in[1] = (f32 *) g_drip_bone_pt_b;
        out[0] = spr.pos;
        out[1] = dir;
        mtx_transform_points(in, out, *(u8 **) (owner + 0x1D4) + 0x3C0, 2);
        dir[0] -= spr.pos[0];
        dir[1] -= spr.pos[1];
        dir[2] -= spr.pos[2];
        if (vec3_make_basis(dir, trail.hit, trail.normal) == 0) {
            return;
        }
        spr.alpha = (u32) trail.speed;
        spr.type = 0x79;
        spr.unk1 = 0xC;
        spr.tex = 0x4405;
        spr.life = 300;
        spr.unk8 = 0;
        spr.unkC = 0;
        spr.col[0] = 0xD5;
        spr.col[1] = 0xDB;
        spr.col[2] = 0xFF;
        spr.col[3] = 0xFF;
        spr.unk18 = 0.0f;
        spr.unk14 = 0.0f;
        spr.unk28[0] = ((s32 *) g_vec3_zero)[0];
        spr.unk28[1] = ((s32 *) g_vec3_zero)[1];
        spr.unk28[2] = ((s32 *) g_vec3_zero)[2];
        spr.scale[0] = 1.0f;
        spr.scale[1] = 1.0f;
        spr.scale[2] = 1.0f;
        spr.unk40 = 0x04EC0000;
        spr.unk45 = 0xFF;
        spr.unk46 = 0;
        spr.unk47 = 6;
        spr.unk48 = 0;
        spr.unk4C = 0xFF;
        spr.unk50 = 0;
        spr.unk54 = 1;
        spr.unk56 = 0xFF;
        p = effect3d_spawn_full(&spr, (s32) &D_800A4AA0, 0x26, 0, 0, 0x25, 0, 0, 0, 0x34, obj[0xC], obj[1]);
        if (p != NULL) {
            memcpy((u8 *) p + 0x110, &trail, 0x34);
        }
        *(f32 *) (st + 8) -= 1.0f;
        (*(s8 *) (st + 0xC))--;
        if (!(1.0f < *(f32 *) (st + 8))) {
            return;
        }
    } while (*(s8 *) (st + 0xC) > 0);
}

/* was func_150F3714 */
void drip_emitter_on_message(s32 arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

/* was func_150F3754 */
void drip_sprite_on_message(s32 arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

/* was func_150F3794 */
s32 drip_sprite_update(u8 *arg0) {
    u8 *sp18;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_t0;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x110));
    temp_v0 = arg0 + 0x110;
    if (((*(s32 *)((u8 *)temp_v1 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_v1 + 0x3B))) || (temp_t0 = (*(s32 *)((u8 *)temp_v1 + 0x1D4)), (temp_t0 == 0))) {
        return 0;
    }
    sp18 = temp_v0;
    mtx_transform_point_or_origin(((u8 *)&g_drip_bone_pt_a), arg0 + 0x34, temp_t0 + 0x3C0);
    temp_f2 = sqrtf((*(f32 *)((u8 *)temp_v0 + 8))) * (*(f32 *)((u8 *)temp_v0 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x30)) = temp_f2;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = temp_f2;
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
    (*(s8 *)((u8 *)arg0 + 0x5C)) = (s8) (u32) ((*(f32 *)((u8 *)temp_v0 + 0x14)) - ((*(f32 *)((u8 *)temp_v0 + 0x18)) * temp_f12 * temp_f12));
    (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) + g_frame_step_f);
    var_v0 = 1;
    if ((*(f32 *)((u8 *)temp_v0 + 0xC)) < (*(f32 *)((u8 *)temp_v0 + 8))) {
        var_v0 = 0;
    }
    return var_v0;
}
s32 sprite_quad_build_axes();

/* P224: draw table g_effect3d_draw_fns entry; the asm returns sprite_quad_build_axes's v0 and the dispatcher uses it. */
/* was func_150F38FC */
u8 *drip_sprite_draw(u8 *arg0, s16 arg1) {
    return (u8 *) sprite_quad_build_axes(arg0, arg0 + 0x12C, arg0 + 0x138, arg1);
}

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F_7 : 7;
    u8 unk4F_0 : 1;
} struct_eu_150F3930;

/* was func_150F3930 */
void map_obj_vis_by_cam_depth(struct_eu_150F3930 *arg0) {
    if (*(f32 *)((u8 *)g_player_views + 0x300) < -2000.0f) {
        arg0->unk4F_0 = 0;
        return;
    }
    arg0->unk4F_0 = 1;
}

extern f32 g_cam_zone_y_limit; /* was D_800A1D40 */

/* was func_150F3978 */
void camera_zone_flag_update(s32 arg0) {
    u8 *e = (u8 *)g_player_views + arg0 * 0x9A0;

    if (*(f32 *)(e + 0x300) < g_cam_zone_y_limit) {
        if (*(f32 *)(e + 0x2FC) > 840.0f) {
            **(s16 **)&g_cam_zone_leaf = **(s16 **)&g_cam_zone_leaf | (1 << arg0); // fakematch: g_cam_zone_leaf is declared s32 but holds a pointer; inline casts, no local
            return;
        }
        **(s16 **)&g_cam_zone_leaf = **(s16 **)&g_cam_zone_leaf & ~(1 << arg0);
    }
}

extern f32 g_swim_anim_speed_slope; /* was D_800A1D50 */
extern f32 g_swim_anim_speed_base; /* was D_800A1D54 */

/* was func_150F3A20 */
f32 player_swim_anim_speed(s32 arg0, f32 arg1) {
    f32 var_f2;

    if (arg1 < -5.0f) {
        var_f2 = (arg1 * g_swim_anim_speed_slope) + g_swim_anim_speed_base;
    } else {
        var_f2 = 0.75f;
    }
    return var_f2;
}

extern u16 D_800BEB30[];
extern u8 *D_800CC6A4; /* controller: +0 buttons (u16), +2 stick x, +3 stick y (s8) */
extern s32 D_800CC6A0;
extern u8 g_contact_grab_obj_id; /* was D_800CC68D */
extern u8 g_wall_coll_soft_edges; /* was D_800CC1F3 */
void obj_stun_update(struct127 *); /* P209: the asm reads only a0 (this caller leaves 0.25f in a1) */
u8 obj_turn_towards(struct127 *arg0, u8 arg1, u16 arg2);
f32 obj_approach_speed(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);
void obj_state_common_update(struct127 *);
void objev_spawn_helper_object(void);

// player_swim_update: player interaction state 0x15 handler (entry 21 of D_800863B4, called as `(obj)` by
// objects_run_state_handlers / cutscene_event_dispatch). Reads the controller (D_800CC6A4, cleared when the g_hud_lens_state / g_hud_lens_zoom gate
// of player g_cur_obj_index holds). Stunned: drops the carried object (unk13C = 100 + index). Entry (unk102 == 0): heading
// from the stick (math_atan2_u16 / pad_stick_speed), may grab object g_contact_grab_obj_id, dives below unk118. Then each frame:
// stick y / buttons 0x8000 / 0x4000 / 0x10 steer pitch (unkB8), turn (unkC4 -> unk76) and speed (obj_approach_speed),
// gravity damping and clamps, the closest grabbable object (ids 0x9C / 0x9D) to g_cur_obj (unk222), carry / drop
// sounds, the 0x2000 spawn (id 0x25, fewer than 5), surfacing near the floor, and the animation (obj_start_anim).
/* was func_150F3A74 */
void player_swim_update(struct127 *self) {
    struct127 *pl;
    s32 i;
    s32 n;
    u16 heading;
    u16 btn;
    u16 anim;
    u8 who;
    f32 floor_h;
    f32 speed;
    f32 stick;
    f32 mag;
    f32 best;
    f32 d;
    f32 rate;
    f32 lim;
    f32 g;
    f32 vy;
    f32 c4;
    f32 anim_speed;

    floor_h = 0.0f;
    self->unkAB = 1;
    self->unk80 = 1;
    self->unk222 = 0;
    D_800CC288 = D_800BEB30[0];
    D_800CC6A4 = *(u8 **) D_800BE728[0];
    who = g_cur_obj_index;
    if (who <= g_last_player_index && (&g_hud_lens_state)[who] != 0 && 0.75f < (&g_hud_lens_zoom)[who] && g_game_mode != 2) {
        /* input blocked */
        D_800CC6A4[2] = 0;
        D_800CC6A4[3] = 0;
        *(u16 *) D_800CC6A4 = 0;
        D_800CC288 = 0;
    }
    self->unkF8 |= 0x40;
    self->unk1CC = self->y_position;
    if (self->unk103 != 0) {
        self->unk103--;
    }
    if (self->stunned != 0) {
        obj_stun_update(self);
        obj_physics_step(self);
        self->unk40 = (f32) ((s16) self->unk7A + 0x4000) * 0.0054931640625f; /* 360 / 65536 */
        if (self->unk13C != 0) {
            /* let go of the carried object */
            pl = &g_objects[self->unk13C - 100];
            pl->unk13D = 0;
            pl->unk232 = 0x21;
            pl->unk218 = NULL;
            pl->stunned = 0;
            pl->unkF8 &= ~0x400;
            pl->xz_velocity = self->xz_velocity;
            self->unk13C = 0;
        }
        return;
    }
    if (self->unk102 == 0) {
        /* entering: face the stick direction */
        self->in_water = 0;
        heading = math_atan2_u16((f32) ((s8 *) D_800CC6A4)[2], (f32) ((s8 *) D_800CC6A4)[3], 0);
        mag = pad_stick_speed((struct49 *) D_800CC6A4);
        if (*(u16 *) D_800CC6A4 & 0x10) {
            mag = 0.0f;
        }
        self->unk78 = self->unk7A;
        if (1.0f < mag) {
            self->unk78 = heading + D_800CC6A0;
        }
        self->unk232 = 7;
        self->unk44 = mag * 0.35f;
        self->unk218 = NULL;
        if ((D_800CC288 & 0xC000) || self->unk28 > 100.0f) {
            self->unk232 = 8;
            self->unk102 = 1;
        }
        obj_state_common_update(self);
        if (g_contact_grab_obj_id != 0) {
            if (self->unk28 > 30.0f) {
                /* grab object g_contact_grab_obj_id - 100 */
                g_cur_obj_cmd = 0xFF010074;
                objev_sound_alt_300_1800();
                obj_attach_to_carrier(&g_objects[g_contact_grab_obj_id - 100], g_cur_obj_index);
                self->unk102 = 1;
                self->unk13C = g_contact_grab_obj_id;
            }
            self->y_velocity = 23.0f;
        }
        if (self->y_position < self->unk118) {
            self->unk102 = 1;
            self->unk86 = 1;
            self->y_velocity = -6.0f;
        }
        return;
    }
    speed = self->xz_velocity;
    if (60.0f < speed) {
        speed = 60.0f;
    }
    stick = ((s8 *) D_800CC6A4)[3] * 1.25f;
    btn = *(u16 *) D_800CC6A4 & 0x10;
    if (btn) {
        stick = 0.0f;
    }
    if (self->unk13C != 0) {
        if (!btn) {
            self->y_position -= 16.0f * g_obj_time_step[0];
        }
    } else {
        /* closest grabbable object (ids 0x9C / 0x9D) resting on the ground */
        best = 1000.0f;
        for (i = 0, pl = g_objects; i != 25; i++, pl++) {
            if (pl->interaction_state != 0 && pl->health != 0 && pl->unk28 == 0.0f && pl->unk232 != 0x21 &&
                (pl->id == 0x9C || pl->id == 0x9D)) {
                d = obj_dist_xz(g_cur_obj, pl);
                if (d < best) {
                    self->unk222 = i;
                    best = d;
                }
            }
        }
    }
    if (stick < -90.0f) {
        stick = -90.0f;
    }
    if (90.0f < stick) {
        stick = 90.0f;
    }
    if (2100.0f < self->y_position) {
        if (-30.0f < self->y_velocity) {
            self->y_velocity -= 1.5f;
        }
        stick = 40.0f;
    }
    c4 = self->unkC4;
    self->unkC4 = c4 + ((f32) ((s8 *) D_800CC6A4)[2] - c4) * (0.2f * g_obj_time_step[0]);
    self->unk7E = 0x19;
    self->unk76 -= (s32) (self->unkC4 * g_obj_time_step[0] * 0.04f * ((100.0f - speed) * 0.015f) * 220.0f);
    obj_turn_towards(self, 8, self->unk76);
    self->target_speed = 0.0f;
    speed = 0.0f;
    if (self->y_position < self->unk118) {
        if (self->unk86 == 0) {
            self->unk86 = 1;
            self->xz_velocity = 0.0f;
            self->y_velocity = -6.0f;
        }
    } else if (self->unk86 != 0) {
        self->unk86 = 0;
        self->y_velocity = 9.0f;
    }
    rate = 1.3f;
    btn = *(u16 *) D_800CC6A4;
    if (!(btn & 0x10)) {
        if (btn & 0x8000) {
            self->target_speed = -22.0f;
            speed = 1.0f;
            rate = 1.8f;
            btn = *(u16 *) D_800CC6A4;
        }
        if (btn & 0x4000) {
            self->target_speed = 30.0f;
            if (self->y_velocity < 0.0f) {
                self->target_speed -= self->y_velocity * 0.6f;
            }
            speed = 1.5f;
            rate = 0.3f;
        }
    }
    obj_approach_speed(self->target_speed, self, speed, rate, 1);
    self->unk40 = (f32) ((s16) self->unk7A + 0x4000) * 0.0054931640625f; /* 360 / 65536 */
    self->gravity = stick * 0.000125f * (200.0f - self->xz_velocity);
    if (self->unk13C == 0) {
        if (26.0f < self->y_velocity) {
            self->y_velocity = 26.0f;
        }
        if (self->y_velocity < -34.0f) {
            self->y_velocity = -34.0f;
        }
    }
    lim = fabsf(stick * 0.5f);
    if (self->unk86 != 0) {
        lim *= 0.4f;
        self->gravity *= 0.6f;
    }
    g = self->gravity;
    vy = self->y_velocity;
    if (g == 0.0f) {
        if (fabsf(vy) < 1.5f) {
            self->y_velocity = 0.0f;
        } else if (0.0f < vy) {
            self->gravity = 1.6f;
        } else {
            self->gravity = -1.6f;
        }
    } else if (lim * 1.2f < vy && g < 0.0f) {
        self->gravity = 0.0f;
    } else if (vy < -lim * 1.5f && 0.0f < g) {
        self->gravity = 0.0f;
    }
    self->in_water = 10;
    if (*(u16 *) D_800CC6A4 & 0x10) {
        self->y_velocity = 0.0f;
        self->gravity = 0.0f;
        self->unkB8 += ((f32) ((s8 *) D_800CC6A4)[3] - self->unkB8) * 0.2f;
    } else {
        self->unkB8 = (self->y_velocity - 0.0f) * -2.0f;
        if (40.0f < self->unkB8) {
            self->unkB8 = 40.0f;
        } else if (self->unkB8 < -55.0f) {
            self->unkB8 = -55.0f;
        }
    }
    speed = self->y_velocity;
    g_wall_coll_soft_edges = 1;
    obj_physics_step(self);
    g_wall_coll_soft_edges = 0;
    if (self->unk13C != 0 && self->unk28 < 50.0f) {
        floor_h = 50.0f;
    }
    if (!(*(u16 *) D_800CC6A4 & 0x10)) {
        if (g_contact_grab_obj_id != 0 && self->unk13C == 0 && g_objects[g_contact_grab_obj_id - 100].unk28 == 0.0f) {
            /* pick up object g_contact_grab_obj_id - 100 from the ground */
            self->y_velocity = 20.0f;
            self->y_position = g_objects[g_contact_grab_obj_id - 100].y_position + 70.0f;
            obj_attach_to_carrier(&g_objects[g_contact_grab_obj_id - 100], g_cur_obj_index);
            self->unk13C = g_contact_grab_obj_id;
            g_cur_obj_cmd = 0xFF010074;
            objev_sound_alt_300_1800();
        }
        if (self->unk13C != 0) {
            if (self->unk25C & 2) {
                /* drop the carried object */
                self->unk25C &= ~2;
                pl = &g_objects[self->unk13C - 100];
                pl->unk13D = 0;
                pl->unk232 = 0x21;
                pl->unk218 = NULL;
                pl->stunned = 0;
                pl->unkF8 &= ~0x400;
                pl->xz_velocity = self->xz_velocity;
                self->unk13C = 0;
                self->y_velocity = 0.0f;
                g_cur_obj_cmd = 0x76;
                objev_sound_alt_300_1800();
            }
        } else if ((D_800CC288 & 0x2000) && self->unk103 == 0 && g_level_id == 0x3C) {
            n = 0;
            for (pl = &g_objects[1]; pl != &g_objects[25]; pl++) {
                if (pl->interaction_state != 0 && pl->id == 0x25) {
                    n++;
                }
            }
            if (n < 5) {
                g_cur_obj_cmd = 6;
                self->unk103 = 4;
                objev_spawn_helper_object();
            }
        }
    }
    if (self->unk28 <= floor_h) {
        /* at the floor */
        self->xz_velocity *= 0.6f;
        if ((*(u16 *) D_800CC6A4 & 0x4000) || self->unk86 != 0 || self->unk13C != 0) {
            if (self->unk13C != 0) {
                if (self->y_velocity < -10.0f) {
                    g_cur_obj_cmd = 0xFF0100A7;
                    objev_sound_300_1800();
                    g_cur_obj_cmd = 0xFF060372;
                    objev_sound_alt_300_1800();
                }
            } else if (self->y_position < 0.0f) {
                g_cur_obj_cmd = 0xFF010072;
                objev_sound_alt_300_1800();
            }
            if (self->unk13C == 0) {
                self->y_velocity = 20.0f;
            } else if (self->unk86 == 0) {
                self->y_velocity = 38.0f;
            }
            stick = -80.0f;
        } else {
            self->unk102 = 0;
            self->y_velocity = speed * -1.0f;
            self->unkB8 = 0.0f;
            self->unk28 = 0.1f;
        }
    }
    if (!(*(u16 *) D_800CC6A4 & 0x10)) {
        self->unkB8 += 20.0f;
    } else {
        self->y_velocity = self->unkB8 * -0.35f;
    }
    if (self->unk86 != 0) {
        self->unk83 = 0;
        if (8.0f < fabsf(stick) || 7.0f < self->target_speed) {
            anim_speed = 1.0f;
        } else {
            anim_speed = 0.5f;
        }
    } else {
        anim_speed = player_swim_anim_speed((s32) self, stick);
    }
    anim = 0xF;
    if (40.0f < self->unkB8 && 20.0f < stick) {
        anim = 0x11;
    }
    if (self->xz_velocity < 20.0f && self->target_speed <= 0.0f && stick == 0.0f) {
        anim = 0x18;
    }
    if (self->xz_velocity < 0.0f) {
        anim = 0x1F;
    }
    if (self->unk13C != 0) {
        anim = 0x17;
        anim_speed += 0.2f;
    }
    obj_start_anim(self, anim, anim_speed, 9.0f, 0.0f, 0.0f, 0);
}

s32 event_dispatch(s32, s32, ...);

/* was func_150F4970 */
void camera_update_state3b_view(struct108 *arg0) {
    s32 temp_t0;

    if (arg0->unk23E == 0x3B) {
        event_dispatch_alt(0, 0x405C, 1);
        if ((arg0->unk2C != 0x100) && (arg0->unk6C8 == 0)) {
            if (camera_push_mode(arg0, 8, 0, 0, 0) != 0) {
                temp_t0 = arg0->unk84 | 0x300000;
                arg0->unk84 = temp_t0;
                arg0->unk84 = temp_t0 & ~4;
                arg0->unk1B4 = 1;
                arg0->unk1E0 = 3;
                camera_apply_zoom_level(arg0);
            }
            arg0->unk134 = 0;
            arg0->unk348 = 125.0f;
            arg0->unk34C = 125.0f;
            arg0->unk374 = 220.0f;
            arg0->unk190 = 30.0f;
        } else {
            arg0->unk190 = 0.0f;
        }
    } else if ((arg0->unk2C == 8) && (arg0->unk6C8 == 0)) {
        camera_pop_mode(arg0, 0);
        event_dispatch_alt(0, 0x405C, 0);
    }
    if ((event_dispatch(1, 0x4054, 6, 0x9000) != 0) && (event_dispatch(1, 0x405E, 6, 0x9000) == 0)) {
        arg0->unk84 |= 0x80000000;
        return;
    }
    arg0->unk84 &= 0x7FFFFFFF;
}