#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_impact_burst_desc[]; /* was D_8009FB60 */

u8 *world_record_find(u8);

// The callee (game_eu_1FB080.c) takes only the first three arguments.
void ground_fx_spawn_random(s32 arg0, f32 arg1, f32 arg2, s16 *arg3);


extern s32 * g_world_obj_rider_masks; /* was D_800DC3C4 */
/* was func_150AF6E0 */
void world_pair_hit_player(s32 arg0, u8 arg1) {
    s32 i;
    if (g_obj_tab_stunned[0] == 0) {
        i = (struct131 *)world_record_find(arg0) - g_world_objs;
        if (g_world_obj_rider_masks[i] & 1) {
            obj_send_hit(g_objects, 0x3F, 0x6E00, -1);
            return;
        }
        i = (struct131 *)world_record_find(arg1) - g_world_objs;
        if (g_world_obj_rider_masks[i] & 1) {
            obj_send_hit(g_objects, 0x3F, 0xEE00, -1);
        }
    }
}

/* was func_150AF7C0 */
void ground_fx_spawn_at_span(s32 arg0, s16 *arg1) {
    ground_fx_spawn_random(arg0, (f32)(arg1[4] + arg1[1]), (f32)arg1[1], arg1);
}

s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 memcpy(s32, s8 *, s32);

/* was func_150AF808 */
void smoke_emitter_update_small(u8 *arg0) {
    struct {
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        f32 u90;
        f32 u94;
        f32 u98;
        s32 u9C;
        s32 uA0;
        s16 uA4;
        s16 uA6;
        s32 uA8;
        s32 uAC;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        u8 padF8[0x4];
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s8 u100;
        s8 u101;
    } sp;
    f32 temp_f10;
    f32 temp_f6;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((1352.0f + (random_float() * 1698.0f)) * 0.0001f * g_frame_step_f));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        sp.uB9 = 0x6C;
        sp.uA4 = 0x5103;
        sp.u9C = 0x200005;
        sp.uBA = 0x46;
        sp.uBC = 3;
        sp.uF4 = 0x80DE07;
        sp.uFC = 8;
        sp.uFD = 6;
        sp.uFE = 0x16;
        sp.u8C = 0;
        sp.u8D = 0;
        sp.uA0 = 0;
        sp.uA8 = 0;
        sp.uAC = 0;
        sp.uFF = -1;
        sp.u100 = -1;
        sp.u101 = 0;
        sp.uBE = 0x46;
        sp.uB0 = 0xC7;
        sp.uB1 = 0x78;
        sp.uB2 = 8;
        sp.uB3 = 0xFF;
        sp.uB4 = 0x30;
        sp.uB5 = 0xE;
        sp.uB6 = 0;
        sp.uB8 = 0xFF;
        sp.u98 = 0.97047f;
        sp.uC0 = 1.021029f;
        (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0));
        (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s1 + 4));
        (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s1 + 8));
        sp.uD8 = 0.0f;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        do {
            sp.u8E = (random_int() % 5U) + 4;
            sp.u8F = (random_int() % 5U) + 4;
            sp.u90 = random_float() * 11.0f;
            sp.u94 = random_float() * 11.0f;
            temp_f10 = random_float() * 0.172f;
            sp.uF4 &= ~0xC0;
            sp.uF0 = temp_f10 + 0.098000005f;
            var_s0 = 0;
            if (random_int() & 1) {
                var_s0 = 0x80;
            }
            if (random_int() & 1) {
                var_v0 = 0x40;
            } else {
                var_v0 = 0;
            }
            sp.uF4 |= var_v0 | var_s0;
            sp.uB7 = (random_int() % 101U) + 0x64;
            sp.uA6 = (random_int() % 51U) + 0x50;
            temp_f6 = (random_float() * 71.0f) + 80.0f;
            sp.uC8 = temp_f6;
            sp.uC4 = temp_f6;
            temp_v0 = particle_spawn_ex(&sp.u9C, 0, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u8C, 0x10);
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}
// P230 (implicit_scan): vec_damp_xyz_per_tick takes (f32 *, f32); the matching C below calls it without a prototype and
// passes the f32's bit pattern as an int (lands in a1 either way on N64, wrong type on the port).
void particle_update_wobble_offset(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void vec_damp_xyz_per_tick(f32 *arg0, f32 arg1);
/* was func_150AFBC4 */
s32 particle_wobble_damp_update(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    particle_update_wobble_offset(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    vec_damp_xyz_per_tick((f32 *)(arg0 + 0x58), *(f32 *)(p + 0xC));
    return 1;
}

u8 * fb_fx_spawn(void *arg0, s32 arg1, u8 arg2, s32 arg3);

/* was func_150AFC18 */
void fb_fx_spawn_simple(s16 arg0, u8 arg1, s32 arg2) {
    struct {
        s8 unk0;
        s8 unk1;
        s8 unk2;
        s16 unk4;
        s8 unk6;
    } sp18;

    sp18.unk0 = 1;
    sp18.unk1 = -1;
    sp18.unk2 = 2;
    sp18.unk6 = 0;
    sp18.unk4 = arg0;
    fb_fx_spawn(&sp18, 0, arg1, arg2);
}

void framebuffer_green_to_gray(u16 *start, u16 *end);

/* was func_150AFC70 */
void fb_fx_gray_callback(s32 arg0, s32 arg1) {
    framebuffer_green_to_gray((u16 *)arg1, (u16 *)(arg1 + 0x1ECC0));
}

s32 sprite2d_spawn(f32 *, s32, s32, s32, s32, s32, s32);
u8 impact_puff_tex_kind0(void);

/* was func_150AFCA4 */
void sprite_emitter_update(u8 *arg0) {
    struct {
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s8 u50;
        u8 pad51[0x1];
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        s8 u5A;
        s8 u5B;
        s8 u5C;
        s8 u5D;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s32 u64;
        s32 u68;
        s32 u6C;
        s32 u70;
        s32 u74;
        s32 u78;
        s32 u7C;
        s8 u80;
        s8 u81;
        u8 pad82[0x2];
        s8 u84;
        u8 pad85[0x17];
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        s8 uBC;
        u8 padBD[0x1];
        s16 uBE;
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s8 uC6;
        s8 uC7;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s8 uCC;
        s8 uCD;
        s8 uCE;
        s8 uCF;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        s32 uDC;
        s32 uE0;
        s32 uE4;
        s32 uE8;
        s8 uEC;
        s8 uED;
        u8 padEE[0x2];
        s8 uF0;
    } sp;
    s32 sp38;
    u8 *sp34;
    f32 temp_f10;
    f32 temp_f2;
    s16 temp_t2;
    s16 temp_t5;
    s16 temp_v1;
    s16 temp_v1_2;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_v0_2;

    (*(s16 *)((u8 *)arg0 + 0x28)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x28)) - g_frame_ticks);
    if ((*(s16 *)((u8 *)arg0 + 0x28)) < 0) {
        sp.u9C = (random_float() * 280.0f) + -140.0f;
        sp.uA0 = random_float() * 50.0f;
        sp.uA4 = 2.0f * (random_float() * 3.1415927f);
        temp_f10 = random_float() * 0.268f;
        sp.uAC = 0.0f;
        sp.uB0 = 0.0f;
        sp.uA8 = temp_f10;
        random_float();
        sp.uBC = 0xFF;
        sp.uB4 = 1.0f;
        sp.uB8 = 115.0f;
        temp_t2 = (random_int() % 71U) + 0x14;
        sp.uBE = temp_t2;
        temp_v1 = (*(s16 *)((u8 *)arg0 + 0xE));
        if (temp_v1 < temp_t2) {
            sp.uBE = temp_v1;
        }
        sp.uC0 = 0x21;
        sp.uC2 = 1;
        sp.uC4 = 0xFF;
        sp.uC6 = 0;
        sp.uC7 = 0xFF;
        sp.uC8 = 0xFF;
        sp.uC9 = 0xFF;
        sp.uCA = (random_int() % 71U) + 0x28;
        sp.uCB = 0xFF;
        sp.uCC = 0xFF;
        sp.uCD = 0xFF;
        sp.uCE = 0xFF;
        sp.uCF = 0xFF;
        sp.uD0 = 0;
        sp.uD4 = 0x200004;
        sp.uD8 = 0x1F0601;
        sp.uDC = 0x19;
        sp.uE0 = 0x54;
        sp.uE4 = 0x80;
        sp.uE8 = 0x20;
        sp.uEC = 0;
        sp.uED = 0xA;
        sp.uF0 = 0;
        temp_v0 = sprite2d_spawn(&sp.uAC, 6, 0, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x70, (s8 *) &sp.u9C, 0x10);
        }
        (*(s16 *)((u8 *)arg0 + 0x28)) = (s16) ((random_int() % 41U) + 0x2D);
    }
    temp_v0_2 = arg0 + 0x28;
    (*(s16 *)((u8 *)temp_v0_2 + 2)) = (s16) ((*(s16 *)((u8 *)temp_v0_2 + 2)) - g_frame_ticks);
    if ((*(s16 *)((u8 *)temp_v0_2 + 2)) < 0) {
        sp34 = temp_v0_2;
        sp.u40 = (random_float() * 280.0f) + -140.0f;
        sp.u44 = (random_float() * 200.0f) + -100.0f;
        temp_f2 = (2.0f * random_float()) + 1.0f;
        sp.u48 = temp_f2;
        sp.u4C = temp_f2;
        sp.u50 = impact_puff_tex_kind0();
        temp_t5 = (random_int() % 7U) + 5;
        sp.u52 = temp_t5;
        temp_v1_2 = (*(s16 *)((u8 *)arg0 + 0xE));
        if (temp_v1_2 < temp_t5) {
            sp.u52 = temp_v1_2;
        }
        var_v1 = 0;
        if (random_int() != 0) {
            var_v1 = 2;
        }
        sp38 = var_v1;
        if (random_int() != 0) {
            var_v0 = 4;
        } else {
            var_v0 = 0;
        }
        sp.u54 = var_v0 | 1 | var_v1 | 0x20;
        sp.u56 = 1;
        sp.u58 = 0xFF;
        sp.u5A = 0;
        sp.u5B = 0xFF;
        sp.u5C = 0xFF;
        sp.u5D = 0xFF;
        sp.u5E = (random_int() % 121U) + 0x50;
        sp.u5F = 0xFF;
        sp.u60 = 0xFF;
        sp.u61 = 0xFF;
        sp.u62 = 0xFF;
        sp.u63 = 0xFF;
        sp.u64 = 0;
        sp.u68 = 0x200004;
        sp.u6C = 0x1F0601;
        sp.u70 = 0x19;
        sp.u74 = 0x55;
        sp.u78 = 0x80;
        sp.u7C = 0x20;
        sp.u80 = 0;
        sp.u81 = 7;
        sp.u84 = 0;
        sprite2d_spawn(&sp.u40, 0, 0, 0, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(s16 *)((u8 *)sp34 + 2)) = (s16) ((random_int() % 11U) + 3);
    }
}
/* was func_150B00D4 */
s32 fx_bob_update(u8 *arg0) {
    u8 *v = arg0 + 0x70;
    *(f32 *)(arg0 + 0x78) = *(f32 *)(arg0 + 0x7C) * g_frame_step_f + *(f32 *)(arg0 + 0x78);
    *(f32 *)(v + 8) = wrap_angle_rad(*(f32 *)(arg0 + 0x78));
    *(f32 *)(arg0 + 0x10) = *(f32 *)v + *(f32 *)(v + 4) * sinf(*(f32 *)(v + 8));
    return 1;
}

s32 particle_emitter_node_spawn(s16, s16, s16, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, s16, s16, s16, s16, u16, u8, u8, u8, u8, s16, u16, u16, u8, u8, u8, u8, u8, s32, u8, u8, u8, s32);

/* was func_150B0148 */
void particle_emitter_preset_spawn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    particle_emitter_node_spawn(1, 0, 0, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 1, 0, 0, 0, 0, 0xAA, 0xAA, 0xAA, 0xAA, arg2, arg3, 0, arg0, 0xF0, 0x50, 0x50, 1, 4, 0, 1, 0, 0, 0, arg1, 0, (s32) arg4, arg5);
}

extern struct_eu_node *g_node_list_head; /* was D_800DD2C4 */
/* was func_150B0290 */
void nodes_destroy_for_player(void) {
    struct_eu_node *node;

    node = g_node_list_head;
    g_node_iter_depth++;
    while (node != NULL) {
        g_node_iter_next[g_node_iter_depth] = node->next;
        if (g_cur_obj_index == ((u8 *)node)[0x3F]) {
            node_destroy((struct102 *)node);
        }
        node = g_node_iter_next[g_node_iter_depth];
    }
    g_node_iter_depth--;
}

s32 beam_effect_spawn(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                  s32, f32, f32, f32, f32, f32, f32);
void beam_effect_spawn_attached(s32 arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   s16 argA, s16 argB, u16 argC, u8 argD);

// player_joint_beam_spawn: event-mode helper (g_cur_obj_cmd modes 9 / 10). Uses joint matrix 3 (side 0) or 2 (side 1)
// of the player's (g_cur_obj) matrix block at +0x1D4 (64 bytes per matrix; nothing when it is NULL); transforms the
// local points (0, 0, -20) and (0, 0, -150) to world space, spawns the line effect beam_effect_spawn between them
// (40, 0, 2, 120, 60, 35) and attaches effect beam_effect_spawn_attached to that joint ((0, 0, -39) .. (0, 0, -150), 3, 255, 4).
/* was func_150B0344 */
void player_joint_beam_spawn(s32 side) {
    u8 *mtx = (u8 *)g_cur_obj->unk1D4;
    f32 x0, y0, z0;
    f32 x1, y1, z1;
    f32 (*m)[4];
    s32 joint;

    if (mtx == NULL) {
        return;
    }
    if (side == 0) {
        joint = 3;
    } else {
        joint = 2;
    }
    m = (f32 (*)[4])(mtx + (joint << 6));
    x0 = 0.0f;
    y0 = 0.0f;
    z0 = -20.0f;
    mtxf_transform_point(m, x0, y0, z0, &x0, &y0, &z0);
    x1 = 0.0f;
    y1 = 0.0f;
    z1 = -150.0f;
    mtxf_transform_point(m, x1, y1, z1, &x1, &y1, &z1);
    beam_effect_spawn(0, x0, y0, z0, x1, y1, z1, 40.0f, 0.0f, 2.0f, 120.0f, 0x3C, 0x23, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    beam_effect_spawn_attached((s32)g_cur_obj, g_cur_obj->unique_id, (s16)joint, -1, 0.0f, 0.0f, -39.0f, 0.0f, 0.0f, -150.0f, 3, 0xFF,
                  4, 0);
}

/* was func_150B051C */
void world_pair_hit_player_level(s32 arg0) {
    if (g_level_id == 6) {
        rain_update(0);
        world_pair_hit_player(0xE2, 0xE1);
    } else {
        world_pair_hit_player(0xDF, 0xDE);
    }
}

s32 vec3_normalize_len(f32 *, f32 *, s32 *, s32 *);
void vec3_to_yaw_pitch_deg(f32 *, f32 *, f32 *);
u8 *mdl_particle_spawn_ex(u8 *req, s32 nTrails, s32 arg2, s32 *bounds, s32 extraSize, u8 arg5, s32 owner);
u8 *obj_attached_glow_spawn(void *src, u8 type, s32 size, u8 alpha, s32 arg4);

// beam_trail_spawn: spawns a 3-strand trail (mdl_particle_spawn_ex, request below, 4 extra bytes) from `from` along
// (to - from) when that direction is non-zero (vec3_normalize_len): scale (1, 1, 0.7, 0.7), heading / pitch of the
// direction * 80 (vec3_to_yaw_pitch_deg), colour 1, start `from`, speed (to - from) * 80, life 0x19A0 / 300 / 210; then
// records an effect of type 1 (obj_attached_glow_spawn, size 8, owner = the trail) in the trail's extra word (+0x170).
/* was func_150B0574 */
void beam_trail_spawn(f32 *from, f32 *to, u8 alpha, s32 arg3) {
    struct {
        f32 u00;
        f32 u04;
        f32 u08;
        f32 u0C;
        f32 pitch;
        f32 yaw;
        f32 u18;
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 pos[3];
        f32 vel[3];
        f32 u40[3];
        f32 u4C;
        s32 u50;
        s16 u54;
        s16 u56;
        u8 u58;
        u8 pad59[3];
        s32 u5C;
        u8 u60;
        u8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        u8 u65;
        u8 u66;
        u8 u67;
        u8 u68;
        u8 pad69;
        u8 u6A;
        u8 pad6B;
        s32 u6C;
        u8 u70;
        u8 pad71;
        s16 u72;
        s16 u74;
        u8 pad76[2];
        s32 u78;
    } req;
    f32 dir[3];
    s32 o44;
    s32 o40;
    s32 zero;
    u8 *src;
    u8 *trail;

    zero = 0;
    dir[0] = to[0] - from[0];
    dir[1] = to[1] - from[1];
    dir[2] = to[2] - from[2];
    if (vec3_normalize_len(dir, dir, &o44, &o40) == 0) {
        return;
    }
    req.u00 = 1.0f;
    req.u04 = 1.0f;
    req.u0C = 0.7f;
    req.u08 = 0.7f;
    req.pos[0] = from[0];
    req.pos[1] = from[1];
    req.pos[2] = from[2];
    req.vel[0] = dir[0] * 80.0f;
    req.vel[1] = dir[1] * 80.0f;
    req.vel[2] = dir[2] * 80.0f;
    vec3_to_yaw_pitch_deg(req.vel, &req.yaw, &req.pitch);
    req.u1C = 1.0f;
    req.u20 = 1.0f;
    req.u24 = 1.0f;
    req.u18 = 0.0f;
    req.u40[0] = ((f32 *)g_vec3_zero)[0];
    req.u40[1] = ((f32 *)g_vec3_zero)[1];
    req.u40[2] = ((f32 *)g_vec3_zero)[2];
    req.u50 = 0x19A0;
    req.u54 = 0x12C;
    req.u56 = 0xD2;
    req.u58 = 7;
    req.u5C = 0;
    req.u60 = 0xFF;
    req.u61 = 8;
    req.u62 = 0;
    req.u63 = 0;
    req.u64 = 0;
    req.u65 = 0;
    req.u66 = 0;
    req.u67 = 0;
    req.u68 = 2;
    req.u6A = 0;
    req.u6C = 0;
    req.u70 = 0;
    req.u72 = 1;
    req.u74 = 0xFF;
    req.u78 = 0;
    req.u4C = 0.0f;
    trail = mdl_particle_spawn_ex((u8 *)&req, 3, 0xFF, NULL, 4, alpha, arg3);
    if (trail == NULL) {
        return;
    }
    memcpy((s32)(trail + 0x170), (s8 *)&zero, 4);
    src = trail;
    *(u8 **)(trail + 0x170) = obj_attached_glow_spawn(&src, 1, 8, alpha, arg3);
}

/* was func_150B07A0 */
void beam_trail_free_extra(struct102 **arg0) {
    if (*(s32 *)&arg0[0x170 / 4] != 0) {
        node_destroy(arg0[0x170 / 4]);
    }
}

/* was func_150B07D0 */
void beam_trail_die_retire(u8 *arg0) {
    beam_trail_free_extra(arg0);
    mdl_particle_die_retire(arg0);
}

/* was func_150B07FC */
void beam_trail_die_free(u8 *arg0) {
    beam_trail_free_extra(arg0);
    mdl_particle_die_free(arg0);
}

void emit_particle_burst_req(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 g_impact_burst_params; /* was D_8009FB74 */

/* was func_150B0828 */
void obj_impact_burst_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u2C;
        s32 u30;
        s32 u34;
        u8 pad38[0x8];
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        s16 u58;
        s16 u5A;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s8 u6C;
        u8 pad6D[0x1];
        s16 u6E;
        s32 u70;
        s32 u74;
        s16 u78;
        s16 u7A;
        s32 u7C;
        s32 u80;
        s8 u84;
        s8 u85;
        s8 u86;
        s8 u87;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s16 u8E;
        s16 u90;
        s16 u92;
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x8];
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s16 uB2;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s8 uCC;
        u8 padCD[0x3];
        f32 uD0;
        s32 uD4;
        f32 uD8;
        f32 uDC;
    } sp;

    sp.uD4 = (*(s32 *)((u8 *)arg0 + 0x14));
    sp.uD8 = (*(f32 *)((u8 *)arg0 + 0x18)) + 30.0f;
    sp.uDC = (*(f32 *)((u8 *)arg0 + 0x1C));
    sp.u68 = 0xA;
    sp.u6A = 7;
    sp.u6C = 0x6C;
    sp.u6E = 0x5103;
    sp.u70 = 0x200005;
    sp.u78 = 0x1E;
    sp.u7A = 0xF;
    sp.u87 = 0xFF;
    sp.u84 = 0x7F;
    sp.u86 = 6;
    sp.u74 = 0;
    sp.u7C = 0;
    sp.u80 = 0;
    sp.u85 = 0x4B;
    sp.u88 = 0x80;
    sp.u89 = 0x53;
    sp.u8A = 0;
    sp.u8B = 0x64;
    sp.u8C = 0x64;
    sp.u8D = 0xFF;
    sp.u8E = 0x20;
    sp.u90 = 7;
    sp.u92 = 0x20;
    sp.u94 = 1.025729f;
    sp.u98 = 351.0f;
    sp.u9C = 200.0f;
    (*(s32 *)((u8 *)(&sp.uA0) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 0));
    (*(s32 *)((u8 *)(&sp.uA0) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 4));
    (*(s32 *)((u8 *)(&sp.uA0) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 8));
    sp.uAC = 0;
    sp.uAE = -0x19;
    sp.uB0 = 0xFF;
    sp.uB2 = 0x15;
    sp.uC4 = 0x40E07;
    sp.uC8 = 0x10;
    sp.uC9 = -1;
    sp.uCA = 8;
    sp.uCB = 6;
    sp.uCC = 1;
    sp.uB4 = 5.0f;
    sp.uB8 = 25.0f;
    sp.uBC = 0.008f;
    sp.uC0 = 0.266f;
    sp.uD0 = 0.938608f;
    emit_particle_burst_req(&sp.u68, 0xFF, arg1, arg2);
    sp.u2C = 0x24;
    sp.u30 = 0xA;
    (*(s32 *)((u8 *)(&sp.u34) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 0));
    (*(s32 *)((u8 *)(&sp.u34) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 4));
    (*(s32 *)((u8 *)(&sp.u34) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 8));
    sp.u48 = 11.0f;
    sp.u4C = 8.0f;
    sp.u40 = 0;
    sp.u42 = 0xFF;
    sp.u44 = -0x28;
    sp.u46 = 0x14;
    sp.u58 = 0x22;
    sp.u5A = 0xF;
    sp.u50 = -1.09f;
    sp.u54 = 0.37100002f;
    sp.u5C = 0.30200002f;
    sp.u60 = 0.31800002f;
    sp.u64 = 9.687f;
    emit_textured_burst(&sp.u2C, ((u8 *)&g_impact_burst_desc), &g_impact_burst_params, 5, 65.0f, 0U, (u8) (s32) arg1, arg2);
}
/* was func_150B0AEC */
s32 world_record_anchor_init(u8 arg0, u8 *arg1) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = world_record_find(arg0);
    (*(u8 **)((u8 *)arg1 + 8)) = temp_v0;
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 8));
    (*(f32 *)((u8 *)arg1 + 0)) = -150.0f;
    (*(f32 *)((u8 *)arg1 + 4)) = 4.5f;
    (*(f32 *)((u8 *)arg1 + 0xC)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)arg1 + 0x10)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x12));
    (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x14));
    return 1;
}
