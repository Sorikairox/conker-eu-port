#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void obj_notify_hit_target(struct127 *);


/* was func_15063740 */
s16 obj_yaw_to_linked_obj(u8 *arg0) {
    struct127 *temp_v0;

    temp_v0 = &g_objects[(*(u8 *)((u8 *)arg0 + 0x222))];
    return math_atan2_u16(temp_v0->x_position - (*(f32 *)((u8 *)arg0 + 0x14)), (*(f32 *)((u8 *)arg0 + 0x1C)) - temp_v0->z_position, 0);
}

/*
 * obj_knockdown_start: for object record rec (g_objects, 0x32C bytes): its state block (+0x31C) gets +0x78 = 9,
 * animations 0x1D then 0x1E at speed 1 (obj_setup_run), rec +0x8A = 20, +0x89 = +0x83 = 0, the block's +0x24 timer
 * = 60 and +0x11A = 2, then obj_start_anim(rec, 0x7F, 1.0, 0, 0, 0, 0). As obj_hit_react_start, the asm finds the block
 * through the record index (rec - base) / 0x32C.
 */
/* was func_150637B4 */
void obj_knockdown_start(struct127 *rec) {
    s32 idx = ((u8 *)rec - (u8 *)g_objects) / 0x32C;
    u8 *state;

    state = *(u8 **)((u8 *)g_objects + idx * 0x32C + 0x31C);
    state[0x78] = 9;
    obj_setup_run(rec, 0x1D, 1.0f, 0);
    obj_setup_run(rec, 0x1E, 1.0f, 0);
    ((u8 *)rec)[0x8A] = 20;
    ((u8 *)rec)[0x89] = 0;
    ((u8 *)rec)[0x83] = 0;
    state = *(u8 **)((u8 *)g_objects + idx * 0x32C + 0x31C);
    *(s16 *)(state + 0x24) = 60;
    state = *(u8 **)((u8 *)g_objects + idx * 0x32C + 0x31C);
    state[0x11A] = 2;
    obj_start_anim(rec, 0x7F, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

s32 obj_setup_undo(struct127 *, s32);
/* was func_15063894 */
void obj_knockdown_clear(struct127 *arg0) {
    struct127 *temp_v0;
    temp_v0 = &g_objects[arg0 - g_objects];
    temp_v0->unk31C->unk78 = 0;
    temp_v0->unk31C->unk11A = 0;
    obj_setup_undo(arg0, 0x1D);
    obj_setup_undo(arg0, 0x1E);
    *((u8 *)arg0 + 0x8A) = 0;
    *((u8 *)arg0 + 0x89) = 0;
    *((u8 *)arg0 + 0x83) = 0;
}

/*
 * obj_hit_react_start: P190. For object record rec (g_objects, 0x32C bytes): its state block (+0x31C) gets
 * +0x78 = 0x3B and +0x11A = 2, animation 0x89 at speed 1 (obj_setup_run), rec +0x8A = 20, +0x89 = +0x83 = 0, and
 * obj_start_anim(rec, 0x221, 1.0, 0, 0, 0, 0). The asm finds the block through the record index (rec - base) / 0x32C.
 */
/* was func_15063920 */
void obj_hit_react_start(struct127 *rec) {
    s32 idx = ((u8 *)rec - (u8 *)g_objects) / 0x32C;
    u8 *state;

    state = *(u8 **)((u8 *)g_objects + idx * 0x32C + 0x31C);
    state[0x78] = 0x3B;
    state = *(u8 **)((u8 *)g_objects + idx * 0x32C + 0x31C);
    state[0x11A] = 2;
    obj_setup_run(rec, 0x89, 1.0f, 0);
    ((u8 *)rec)[0x8A] = 20;
    ((u8 *)rec)[0x89] = 0;
    ((u8 *)rec)[0x83] = 0;
    obj_start_anim(rec, 0x221, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

s32 ray_cast_world(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
/* was func_150639D8 */
void obj_ray_cast_from_ctl(u8 *arg0, f32 arg1) {
    u8 *temp_v0;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
    ray_cast_world(arg0, (*(f32 *)((u8 *)temp_v0 + 0x13C)), (*(f32 *)((u8 *)temp_v0 + 0x140)), (*(f32 *)((u8 *)temp_v0 + 0x144)), (*(f32 *)((u8 *)temp_v0 + 0x130)), (*(f32 *)((u8 *)temp_v0 + 0x134)), (*(f32 *)((u8 *)temp_v0 + 0x138)), temp_v0 + 0xB0, arg1, 0, 0, 0, -1, 0, 0);
    obj_notify_hit_target((struct127 *)arg0);
}

/* was func_15063A54 */
void obj_notify_hit_target(struct127 *arg0) {
    u8 *v = *(u8 **)(*(u8 **)((u8 *)arg0 + 0x31C) + 0xB0);
    u8 *w;

    if (v != NULL) {
        w = *(u8 **)(v + 0x31C);
        if (w != NULL) {
            (*(u8 **)(v + 0x31C))[0x195] = 0x1E;
            (*(u8 **)(v + 0x31C))[0x196] = arg0 - g_objects;
        }
    }
}

/* P222: readable C for obj_run_pending_actions (game_eu_90F50, 179 words; jump table jtbl_80099A98 = EU 0x80099A98). */
void obj_spawn_hit_shot(u8 *arg0, s32 arg1);
void mouth_aim_ray(struct127 *obj, u8 which);
s32 shot_hit_apply(u8 *obj, u8 *hit, s32 kind);
s32 actor_sound2_is_playing(struct127 *arg0);
void actor_sound_play2_delayed(u16, struct127 *, s32, s32, s32, s32);
void camera_track_start(s32, s32);
void weapon_c_muzzle_frame_get(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void gun_shot_sparks(f32 *pos, f32 *dir, u8 flag, s32 arg3);

// object_pending_actions_run: once per frame (game_45B80) for every live object with a controller (+0x31C) whose
// pending-action byte ctl +0x1B4 is set: makes it the current object (g_cur_obj_index = slot, g_cur_obj = obj) and runs
// bit 0: obj_ray_cast_from_ctl(obj, 0), bit 2 / bit 3: mouth_aim_ray(obj, 0 / 1), bit 1: the action of the controller's item
// kind ctl +0x78 (bit 7 ignored): 0x14 / 0x3F / 0x18 / 0x41 hit reactions (obj_spawn_hit_shot 2 / 0x12 / 6, counter
// ctl +0x1AA, pad rumble), 0x24 the hit record ctl +0xB0 as kind 7 (with a pain voice 0x53B..0x53D unless the
// record says 2 or ctl +0xAF is clear), 0x3B kind 0x10 plus the muzzle sparks (weapon_c_muzzle_frame_get / gun_shot_sparks),
// 0x23 kind 8 (rumble off). Then clears ctl +0x1B4. D_800CC2B0 is cleared first.
/* was func_15063AA0 */
void obj_run_pending_actions(void) {
    struct127 *obj;
    u8 *ctl;
    u8 kind;
    f32 pos[3];
    f32 dir[3];
    f32 v50[3];
    f32 v44[3];
    s32 i;

    D_800CC2B0 = 0;
    for (i = 0, obj = g_objects; i < 25; i++, obj++) {
        if (obj->interaction_state == 0 || (ctl = *(u8 **) ((u8 *) obj + 0x31C)) == NULL || ctl[0x1B4] == 0) {
            continue;
        }
        g_cur_obj_index = i;
        g_cur_obj = obj;
        if (ctl[0x1B4] & 1) {
            obj_ray_cast_from_ctl((u8 *) obj, 0.0f);
        }
        if ((*(u8 **) ((u8 *) obj + 0x31C))[0x1B4] & 4) {
            mouth_aim_ray(obj, 0);
        }
        if ((*(u8 **) ((u8 *) obj + 0x31C))[0x1B4] & 8) {
            mouth_aim_ray(obj, 1);
        }
        ctl = *(u8 **) ((u8 *) obj + 0x31C);
        if (ctl[0x1B4] & 2) {
            kind = ctl[0x78] & ~0x80;
            switch (kind) {
            case 0x18:
            case 0x41:
                obj_spawn_hit_shot((u8 *) obj, 6);
                (*(s16 *) ((*(u8 **) ((u8 *) obj + 0x31C)) + 0x1AA))++;
                if (*(s32 *) ((u8 *) obj + 0x318) != 0) {
                    camera_track_start(*(s32 *) ((u8 *) obj + 0x318), 1);
                }
                break;
            case 0x14:
            case 0x3F:
                obj_spawn_hit_shot((u8 *) obj, kind == 0x14 ? 2 : 0x12);
                (*(s16 *) ((*(u8 **) ((u8 *) obj + 0x31C)) + 0x1AA))++;
                if (*(s32 *) ((u8 *) obj + 0x318) != 0) {
                    camera_track_start(*(s32 *) ((u8 *) obj + 0x318), 1);
                }
                break;
            case 0x24:
                if (shot_hit_apply((u8 *) obj, ctl + 0xB0, 7) != 2) {
                    ctl = *(u8 **) ((u8 *) obj + 0x31C);
                    if (ctl[0xAF] != 0) {
                        ctl[0xAF] = 0;
                        if (actor_sound2_is_playing(obj) == 0) {
                            actor_sound_play2_delayed((u32) random_int() % 3 + 0x53B, obj, 0x7D00, 0x320, 0xBB8, 0x19);
                        }
                    }
                }
                if (*(s32 *) ((u8 *) obj + 0x318) != 0) {
                    camera_track_start(*(s32 *) ((u8 *) obj + 0x318), 1);
                }
                break;
            case 0x3B:
                shot_hit_apply((u8 *) obj, ctl + 0xB0, 0x10);
                weapon_c_muzzle_frame_get((s32) obj, (s32) pos, (s32) dir, (s32) v50, (s32) v44);
                gun_shot_sparks(pos, dir, 0xFF, 1);
                break;
            case 0x23:
                shot_hit_apply((u8 *) obj, ctl + 0xB0, 8);
                if (*(s32 *) ((u8 *) obj + 0x318) != 0) {
                    camera_track_start(*(s32 *) ((u8 *) obj + 0x318), 0);
                }
                break;
            }
        }
        (*(u8 **) ((u8 *) obj + 0x31C))[0x1B4] = 0;
    }
}

extern s16 D_800CC6D2;

/* was func_15063D6C */
s16 player_aim_yaw_delta(u8 *arg0) {
    D_800CC6D2 = ((*(u16 *)((u8 *)arg0 + 0x7A)) - (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x12))) - obj_yaw_to_linked_obj(arg0);
    if (D_800CC6D2 >= 0x3E81) {
        D_800CC6D2 = 0x3E80;
    }
    if (D_800CC6D2 < -0x3E80) {
        D_800CC6D2 = -0x3E80;
    }
    return D_800CC6D2;
}

extern u8 *D_800CC6A4;
extern f32 D_800CC6D4;

/* was func_15063DE8 */
s32 player_aim_turn_update(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_v0;
    u16 temp_t0;
    u16 temp_t3;

    var_v0 = 0;
    if (arg1 & arg2) {
        D_800CC6D2 = (*(s8 *)((u8 *)D_800CC6A4 + 2)) * 0xC8;
        if ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x84)) != 0) {
            D_800CC6D2 = player_aim_yaw_delta(arg0);
        }
        D_800CC6D4 = 12.0f;
        D_800CC6D2 = (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x12)) + ((s32) (D_800CC6D2 * D_800CC264) / 2000);
        if (D_800CC6D2 < -0x2328) {
            temp_t0 = ((*(u16 *)((u8 *)arg0 + 0x7A)) - D_800CC6D2) - 0x2328;
            (*(u16 *)((u8 *)arg0 + 0x7A)) = temp_t0;
            (*(u16 *)((u8 *)arg0 + 0x76)) = temp_t0;
            D_800CC6D2 = -0x2328;
        }
        if (D_800CC6D2 >= 0x2329) {
            temp_t3 = ((*(u16 *)((u8 *)arg0 + 0x7A)) - D_800CC6D2) + 0x2328;
            (*(u16 *)((u8 *)arg0 + 0x7A)) = temp_t3;
            (*(u16 *)((u8 *)arg0 + 0x76)) = temp_t3;
            D_800CC6D2 = 0x2328;
        }
        var_v0 = 1;
        (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x12)) = D_800CC6D2;
    }
    return var_v0;
}
u8 * attachment_find_by_slot(u8 *arg0, s32 arg1, s32 arg2);
void obj_effect_run_handler(struct127 *, s32, void *);

/* was func_15063F14 */
void obj_detonate_attachment(struct127 *arg0, s32 arg1) {
    s32 kind;
    struct {
        struct127 *obj;
        struct17 pos;
        s32 idx;
    } blk;

    if (arg0->id == 0x75 || arg0->id == 0xB1) {
        kind = 100;
    } else {
        kind = 44;
    }
    if (attachment_find_by_slot(arg0, kind, 0) == 0 && arg1 == 0) {
        return;
    }
    if (arg0->unk1D4 != NULL) {
        mtx_transform_point_or_origin(NULL, &blk.pos, (u8 *)arg0->unk1D4 + 0x100);
    } else {
        blk.pos.unk0 = arg0->x_position;
        blk.pos.unk4 = arg0->y_position;
        blk.pos.unk8 = arg0->z_position;
    }
    blk.idx = (arg0 - g_objects) + 1;
    blk.obj = arg0;
    obj_effect_run_handler(arg0, 0xB, &blk);
    if (obj_setup_undo(arg0, kind)) {} // fakematch: consuming the result frees v0 for the tail
    if (*(*(u8 **)((u8 *)arg0 + 0x31C) + 0x19A) != 0) {
        *(*(u8 **)((u8 *)arg0 + 0x31C) + 0x19A) -= 1;
    }
    *(*(u8 **)((u8 *)arg0 + 0x31C) + 0x11A) = 0;
}

// object_find_held: returns the first live object (word +0 != 0) of kind `kind` (+0x4) whose holder byte +0x65 is
// owner's slot + 1, or NULL. Scans all 25 objects of g_objects (the asm peels slot 0).
/* was func_1506401C */
struct127 *obj_find_held(struct127 *owner, s32 kind) {
    struct127 *o;
    s32 i;

    for (i = 0, o = g_objects; i < 25; i++, o++) {
        if (*(s32 *) o != 0 && kind == *((u8 *) o + 4) && (owner - g_objects) + 1 == *((u8 *) o + 0x65)) {
            return o;
        }
    }
    return NULL;
}

/* was func_15064240 */
s32 player_try_begin_action(struct127 *arg0, s32 arg1, s32 arg2, s8 arg3, s32 arg4) {
    s32 temp_t6;
    struct126 *temp_v0;
    u8 temp_a1;

    temp_t6 = arg1 & 0xFFFF;
    if ((arg4 & 0x4000) && (arg0->unk28 == 0.0f) && (arg0->y_velocity <= 0.0f)) {
        temp_v0 = arg0->unk31C;
        if (((u8) temp_v0->unk95 == 0) && (temp_t6 != arg0->unk84.uh) && ((temp_a1 = temp_v0->unk11A, (temp_a1 == 0)) || (temp_a1 == 2)) && (temp_v0->unk27 == 0)) {
            if ((arg3 != 0) && (arg0->disable_jump != 0)) {
                return 0x3E7;
            }
            if (arg2 & 0xFFFF & 1) {
                arg0->disable_jump = 0x14;
            }
            if (arg3 != 0) {
                if (arg0->unk31C->unk11A == 2) {
                    return 0x3E7;
                }
                arg0->unk31C->unk11A = 1;
                /* Duplicate return node #18. Try simplifying control flow for better match */
                arg0->unk31C->unk78 = (u8) arg3;
                arg0->disable_run = 0xFF;
                arg0->unk83 = 0xFF;
                return temp_t6;
            }
            arg0->unk31C->unk11A = 3;
            arg0->unk31C->unk78 = (u8) arg3;
            arg0->disable_run = 0xFF;
            arg0->unk83 = 0xFF;
            return temp_t6;
        }
    }
    return 0x3E7;
}
extern f32 D_80099B50;
extern f32 D_80099B54;
extern f32 D_80099B5C;
/* was func_1506435C */
void obj_spawn_hit_shot(u8 *arg0, s32 arg1) {
    struct {
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
    } sp;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp44;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    f32 var_f2_2;
    u8 *temp_v0;

    var_f0 = 300.0f;
    var_f2 = 0.0f;
    var_f14 = 0.0f;
    switch (arg1) {                                 /* irregular */
    case 2:
        var_f14 = 27.0f;
        break;
    case 3:
    case 6:
        var_f2 = -11.0f;
        var_f0 = 500.0f;
        break;
    }
    sp5C = var_f14;
    sp60 = var_f2;
    temp_f12 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x16C)) * D_80099B50;
    sp.u78 = var_f0;
    sp58 = temp_f12;
    sp64 = sinf(temp_f12) * var_f14;
    sp68 = cosf(temp_f12) * var_f14;
    sp.u6C = sp64 + (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x13C));
    sp.u70 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x140)) + var_f2;
    sp.u74 = sp68 + (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x144));
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x31C));
    if ((*(u8 *)((u8 *)temp_v0 + 0x109)) == 0) {
        var_f2_2 = -(*(f32 *)((u8 *)temp_v0 + 0x170));
        var_f12 = (*(f32 *)((u8 *)temp_v0 + 0x16C)) + 90.0f;
    } else {
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0xB8)) - sp.u6C;
        temp_f16 = (*(f32 *)((u8 *)temp_v0 + 0xC0)) - sp.u74;
        sp4C = temp_f2;
        sp44 = temp_f16;
        temp_f2_2 = math_atan2f((*(f32 *)((u8 *)temp_v0 + 0xBC)) - sp.u70, sqrtf((temp_f2 * temp_f2) + (temp_f16 * temp_f16))) * D_80099B54;
        sp54 = temp_f2_2;
        var_f2_2 = temp_f2_2;
        var_f12 = math_atan2f(sp4C, sp44) * D_80099B54;
    }
    sp50 = var_f12;
    vec_from_yaw_pitch((s32) (var_f2_2 * D_80099B5C) & 0xFFFF, sp.u78, 0.0f, &sp.u84, &sp.u80, &sp.u7C);
    temp_f0 = -sp.u80;
    sp.u80 = temp_f0;
    camera_object_spawn(sp50, sp.u84, temp_f0, 0.0f, 0x64U, arg1, 0.0f, 0.5f, (s32) &sp.u6C, 1, 1);
}
s32 obj_find_visible_target(u8 *, u16 *, s32, s32, s32);

/* was func_15064594 */
u16 obj_pick_attack_anim(u8 *arg0, u16 arg1, u16 arg2, u16 arg3) {
    u16 r;
    s32 pad; // fakematch: frame slot between r and s
    u16 s;

    s = 0;
    r = arg1;
    if (random_int() & 1) {
        r = arg2;
    }
    if (arg1 == *(u16 *)(arg0 + 0x84) || arg2 == *(u16 *)(arg0 + 0x84)) {
        if (arg0[0x107] < 0x28) {
            return 999;
        }
        r = arg3;
    }
    if (arg3 == *(u16 *)(arg0 + 0x84)) {
        r = 999;
    }
    if (obj_find_visible_target(arg0, &s, 0, 0xFE, 0x40) != 0xFF) {
        *(u16 *)(arg0 + 0x76) = s;
    }
    arg0[0x83] = 0xFF;
    return r;
}

extern s32 D_800CC6AC;               /* pad buttons pressed this frame */
void objev_set_music_mode(void);
void move_xz_towards(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
void obj_sfx_play(s32 arg0, struct127 *arg1);

#define P_U8(o) (((u8 *)player)[o])
#define P_F32(o) (*(f32 *)((u8 *)player + (o)))
#define CTX(pl) (*(u8 **)((u8 *)(pl) + 0x31C)) /* the player's context / action state */

// player_context_action: B / context button of the player. First runs a pending context action (ctx+0x7B, set by
// the level: sit down, pick up / put down, open, push, ...), then, when B was pressed with nothing pending and the
// player is on the ground, starts the B animation (attack / slap, or a level variant). arg3 != 0 only updates the
// state (no animation); noPad != 0 swallows the B press (buttons and D_800CC6AC lose 0x4000).
/* was func_15064668 */
void player_context_action(struct127 *player, s32 buttons, f32 height, s32 arg3, s32 noPad) {
    u8 *ctx;
    struct127 *o;
    s32 anim = 0;
    f32 speed = 1.0f;
    f32 blend = 4.0f;
    f32 dx, dz, dist;
    f32 x, y, z;
    u8 mode;
    s32 w;
    u8 *m;

    if (noPad) {
        buttons &= ~0x4000;
        D_800CC6AC &= ~0x4000;
    }
    ctx = CTX(player);
    if (ctx[0x7B] != 0) {
        switch (ctx[0x7B]) {
        case 1: /* sit down at the stored spot */
            w = *(s32 *)((u8 *)player + 0x2E4);
            P_U8(0x83) = 0xFF;
            P_U8(0x89) = 0xFF;
            *(s16 *)((u8 *)player + 0x84) = 0;
            ctx[0x30] = 0xD;
            *(f32 *)(CTX(player) + 0x28) = (s16)(w >> 16);
            *(f32 *)(CTX(player) + 0x2C) = (s16)w;
            anim = 0x96;
            *(s16 *)((u8 *)player + 0x76) = *(s32 *)((u8 *)player + 0x2E8);
            break;
        case 2:
            speed = 0.8f; /* D_80099B90 */
            anim = 0xDD;
            P_U8(0x89) = 0xFF;
            P_U8(0x83) = 0xFF;
            break;
        case 3:
            g_cur_obj_cmd = 1;
            objev_set_music_mode();
            if (P_U8(0xAD) != 0 || (s32)P_F32(0x28) != 0) {
                obj_setup_run(player, 0x17, 1.0f, 0);
                CTX(player)[0x11A] = 2;
            } else {
                P_U8(0x89) = 0xFF;
                P_U8(0x8A) = 0xFF;
                P_U8(0x83) = 0xFF;
                speed = 3.0f;
                anim = 0x151;
                CTX(player)[0x11A] = 1;
            }
            break;
        case 4:
            g_cur_obj_cmd = 0;
            objev_set_music_mode();
            if (P_U8(0xAD) != 0 || (s32)P_F32(0x28) != 0) {
                obj_setup_undo(player, 0x17);
                CTX(player)[0x11A] = 0;
            } else {
                P_U8(0x89) = 0xFF;
                P_U8(0x8A) = 0xFF;
                P_U8(0x83) = 0xFF;
                speed = 3.0f;
                anim = 0x14E;
                CTX(player)[0x11A] = 3;
            }
            break;
        case 5: /* ride object 0x6C */
            o = obj_find_by_id(0x6C);
            P_U8(0x81) = 1;
            w = *(s32 *)((u8 *)o + 0x2E4);
            if (w == 0) {
                P_F32(0x1CC) = P_F32(0x18);
                w = 100;
                anim = 0x38;
                *(s32 *)((u8 *)o + 0x2E4) = 100;
            }
            if (w >= 100) {
                m = *(u8 **)((u8 *)o + 0x1D4);
                if (m != NULL) {
                    P_F32(0x18) = *(s16 *)(m + 0x15A) + 20;
                }
            }
            if ((buttons & 0x8000) && *(s32 *)((u8 *)o + 0x2E4) == 100) {
                *(s32 *)((u8 *)o + 0x2E4) = 0x7A;
                *(s32 *)((u8 *)o + 0x2E8) = 0x7A;
                anim = 0x16;
                obj_sfx_play(0x38E, player);
            }
            break;
        case 6:
        case 8:
            if ((buttons & 0x4000) && height <= 0.0f) {
                speed = 2.0f;
                P_U8(0x83) = 0xFF;
                P_U8(0x89) = 0xFF;
                anim = 0x33;
            }
            break;
        case 9:
            anim = 0x22D;
            P_U8(0x89) = 0xFF;
            P_U8(0x83) = 0xFF;
            break;
        case 10:
        case 12:
            if (P_F32(0x28) <= 1.0f) {
                anim = (ctx[0x7B] == 10) ? 0x19A : 0x2E7;
                P_U8(0x83) = 0xFF;
            }
            P_U8(0x89) = 200;
            P_U8(0x8A) = 200;
            break;
        case 11: /* camera pull towards the point (-1884, 100) */
            dx = P_F32(0x14) - -1884.0f; /* D_80099B94 */
            dz = P_F32(0x1C) - 100.0f;
            dist = sqrtf(dx * dx + dz * dz);
            if (dist < 1000.0f) {
                vec_from_yaw_pitch(math_atan2_u16(-dx, dz, 0), 20.0f, 0.0f, &x, &y, &z);
                move_xz_towards(x, y, (1200.0f - dist) * 0.001f /* D_80099B98 */, (f32 *)((u8 *)player + 0x16C),
                              (f32 *)((u8 *)player + 0x170));
            }
            break;
        }
        CTX(player)[0x7B] = 0;
    }

    ctx = CTX(player);
    if (ctx[0x198] == 0 && anim == 0 && (buttons & 0x4000)) {
        mode = ctx[0x4E];
        if ((mode & 0xF) != 1 && height <= 0.0f && P_U8(0x89) != 0xFF) {
            if (P_U8(0x13C) >= 100) {
                if (!(*(s32 *)((u8 *)player + 0x25C) & 0x20)) {
                    anim = 0xD6;
                    speed = 1.15f; /* D_80099B9C */
                    if (D_800BE616) {
                        anim = 0x118;
                        speed = 1.0f;
                    }
                    if (g_level_id == 0x30) {
                        anim = 0x28D;
                    }
                    P_U8(0x83) = 0xFF;
                    P_U8(0x89) = 0xFF;
                }
            } else if (((ctx[0x75] == 0 && ctx[0x7C] == 0) || mode == 2) && g_level_id != 0x2D &&
                       g_level_id != 0x2B && g_level_id != 0x30 && g_level_id != 0x34) {
                anim = 0x33;
                if (*(s16 *)(ctx + 8) != 0) {
                    P_U8(0x83) = 0xFF;
                    P_U8(0x89) = 0xFF;
                    speed = 1.6f; /* D_80099BA0 */
                } else {
                    P_U8(0x83) = 0xFF;
                    if (D_800BE616 == 0) {
                        anim = 0x1DC;
                    } else if (g_cheat_flags & 0x400) {
                        anim = 0x355;
                    } else if (g_cheat_flags & 0x800) {
                        anim = 0x1DC;
                    } else {
                        anim = 0x354;
                    }
                    ctx = CTX(player);
                    speed = 1.35f; /* D_80099BA4 */
                    if (ctx[0x84] == 0 && ctx[0x4E] == 0) {
                        P_U8(0x89) = 0xFF;
                        P_F32(0x20) = -4.0f;
                        *(u16 *)((u8 *)player + 0x76) = *(u16 *)(ctx + 0x4C);
                        speed = 1.0f;
                        anim = 0x46;
                    }
                    P_U8(0x80) = 1;
                    blend = 0.0f;
                }
            }
        }
    }
    if (anim != 0 && anim != 999 && arg3 == 0) {
        obj_start_anim(player, anim, speed, blend, 0.0f, 0.0f, 0);
    }
}
#undef P_U8
#undef P_F32
#undef CTX

/* was func_15064D5C */
void obj_slot_sync_anim_frame(s32 arg0, s32 arg1) {
    f32 temp_f0;
    struct197 *temp_v0;
    struct197 *temp_v1;

    temp_v0 = g_objects[arg1].unk2D0;
    temp_v1 = g_objects[arg0].unk2D0;
    if ((temp_v0 != NULL) && (temp_v1 != NULL)) {
        temp_f0 = temp_v0->unk18;
        temp_v0->unk8 = temp_v1->unk8;
        if (temp_f0 <= temp_v0->unk8) {
            temp_v0->unk8 = temp_f0 - 1.0f;
        }
    }
}

/* was func_15064DD0 */
void obj_play_carried_anim(struct127 *arg0) {
    s32 *temp_a1;
    s32 var_v0;
    s32 var_v1;
    struct126 *temp_v0_4;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u8 temp_v0;

    temp_a1 = &(*(s32 *)((u8 *)(&g_objects[arg0->unk65]) + -0x32C));
    temp_v0 = (*(u8 *)((u8 *)temp_a1 + 4));
    var_v1 = 0xF;
    if (temp_v0 == 0xC) {
        temp_v0_2 = (*(u16 *)((u8 *)temp_a1 + 0x84));
        var_v1 = 0x5A;
        if (temp_v0_2 == 0xC) {
            var_v1 = 0x5B;
        } else if (temp_v0_2 == 0xD) {
            var_v1 = 0x5C;
        }
    } else if (temp_v0 == 0x53) {
        temp_v0_3 = (*(u16 *)((u8 *)temp_a1 + 0x84));
        var_v1 = 0x8C;
        if (temp_v0_3 == 0xB) {
            var_v1 = 0xA2;
        } else if (temp_v0_3 == 0xD) {
            var_v1 = 0xA3;
        }
    } else if (temp_v0 == 0x21) {
        var_v1 = 0x169;
    } else if (temp_v0 == 0x8A) {
        temp_v0_4 = arg0->unk31C;
        if ((temp_v0_4 != NULL) && ((*(u8 *)((u8 *)temp_v0_4 + 0x1B2)) != 0)) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        if ((*(u8 *)((u8 *)temp_a1 + 0x232)) == 4) {
            if (var_v0 != 0) {
                var_v1 = 0x350;
            } else {
                var_v1 = 0x1A4;
            }
        } else {
            var_v1 = 0x1A1;
            if (var_v0 != 0) {
                var_v1 = 0x34F;
            }
        }
    }
    obj_start_anim(arg0, var_v1 & 0xFFFF, 1.0f, 6.0f, 0.0f, 0.0f, 0);
    obj_slot_sync_anim_frame(arg0->unk65 - 1, (s32) g_cur_obj_index);
}
extern u8 D_800B89C4[];              /* per-player record (stride 0x32C): character kind byte */

#define P_U8(o) (((u8 *)player)[o])
#define P_F32(o) (*(f32 *)((u8 *)player + (o)))

// player_move_animation: picks the walk / run / carry animation of the player for this frame from the movement
// speed (vel = stick speed, ground speed at +0x44, +0x3C), the player's state (ctx = +0x31C: carried / held object
// kind at +0x78, swim, ladder, ...) and the multiplayer character kind, and starts it (obj_start_anim) with a playback
// speed that follows the movement. moveAnim (when no object is held) overrides the choice; stickMag is the raw
// stick magnitude, pushSpeed the push speed (+0x32 bit 2). Returns the animation id, 0 for none, 999 for "keep".
/* was func_15064F50 */
s32 player_move_animation(struct127 *player, f32 vel, f32 stickMag, s32 moveAnim, f32 pushSpeed) {
    u8 *ctx = *(u8 **)((u8 *)player + 0x31C);
    s32 anim = 0;
    f32 speed = 1.0f;
    f32 blend = 4.0f;
    f32 v;

    if (*(s16 *)(ctx + 0x46) > 0) {
        anim = 0x4C;
        speed = vel / 24.0f;
    } else if (ctx[0x4E] == 2) {
        anim = (*(s8 *)(ctx + 0x50) > 0) ? 0x54 : 5;
        blend = 2.0f;
    } else if (P_U8(0x13C) >= 100) {
        /* multiplayer characters */
        v = P_F32(0x3C);
        if (v < 1.0f) {
            anim = walk_anim_cancel_special();
        } else {
            switch (D_800B89C4[((u8 *)g_cur_obj)[0x13C] * 0x32C]) {
            case 0x8C:
                P_U8(0xAA) = 0x5A;
                anim = 0x1A6;
                speed = vel / 6.0f + 0.4f;
                if (14.0f < v) {
                    anim = 0x1A7;
                    speed = vel / 26.0f + 0.5f;
                }
                break;
            case 0x57:
                P_U8(0xAA) = 0x5A;
                anim = 0x116;
                speed = vel / 6.0f + 0.4f;
                if (14.0f < v) {
                    anim = 0x117;
                    speed = vel / 26.0f + 0.5f;
                }
                break;
            case 0xA8:
            case 0xA9:
                if (14.0f < v) {
                    anim = 0x1B1;
                    speed = vel / 22.0f + 0.4f;
                } else {
                    anim = 0x1B0;
                    speed = vel * 0.0625f + 0.6f;
                }
                break;
            case 0x13:
                anim = 0x14C;
                speed = vel / 6.0f;
                break;
            case 0x89:
                anim = 0x1FB;
                speed = vel / 6.0f;
                break;
            default:
                if (14.0f < v) {
                    anim = 0x2E4;
                    speed = vel * 0.0625f + 0.5f;
                } else {
                    anim = 0xD7;
                    speed = vel / 6.0f + 0.4f;
                }
                break;
            }
        }
    } else if (moveAnim != 0 && ctx[0x78] == 0) {
        anim = moveAnim;
        speed = vel / 15.0f + 0.6f;
    } else if (v = P_F32(0x44), 2.6f < v && (*(u16 *)(ctx + 0x32) & 1)) {
        blend = 5.0f;
        P_U8(0xAA) = 0x28;
        speed = v / 15.0f + 0.5f;
        anim = walk_anim_land_id();
    } else {
        /* walking while holding an object of kind ctx[0x78]: walk animation below 20, run animation from 20 */
        switch (ctx[0x78]) {
        case 0x16:
            if (1.0f <= v) {
                anim = ctx[0x1B2] ? 0x2C6 : 0xE8;
                P_U8(0xAA) = 0x1E;
                speed = vel * 0.0625f + 0.6f;
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x09:
            if (1.0f <= v) {
                if (!D_800BE616) {
                    P_U8(0xAA) = 0x37;
                }
                anim = 0x7E;
                if (!D_800BE616) {
                    speed = vel * 0.0625f + 0.6f;
                } else if (20.0f <= P_F32(0x44)) {
                    anim = 0x22C;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x38:
            if (1.0f <= v) {
                anim = 0x1E1;
                if (20.0f <= v) {
                    anim = 0x1E2;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x39:
            if (*(u16 *)((u8 *)player + 0x84) == 0x1EB) {
                anim = 999;
            } else if (1.0f <= v) {
                anim = 0x1EC;
                if (20.0f <= v) {
                    anim = 0x1ED;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x37:
            if (*(u16 *)((u8 *)player + 0x84) == 0x1F4) {
                anim = 999;
            } else if (1.0f <= v) {
                anim = 0x1F5;
                if (20.0f <= v) {
                    anim = 0x1F6;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x3B:
            if (*(u16 *)((u8 *)player + 0x84) == 0x222 || *(u16 *)((u8 *)player + 0x84) == 0x236) {
                anim = 999;
            } else if (1.0f <= v || *(s8 *)(ctx + 0x23) > 0) {
                P_U8(0xAA) = 0x37;
                anim = 0x223;
                if (20.0f <= v) {
                    anim = 0x224;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x12:
        case 0x18:
        case 0x41:
        case 0x24:
        case 0x22:
        case 0x26:
        case 0x23:
        case 0x15:
        case 0x25:
            if (1.0f <= v) {
                s32 walk, run;
                switch (ctx[0x78]) {
                case 0x24: walk = 0x158; run = 0x159; break;
                case 0x22: walk = 0x15B; run = 0x15C; break;
                case 0x26: walk = 0x178; run = 0x179; break;
                case 0x23: walk = 0x161; run = 0x162; break;
                case 0x15: walk = 0xED; run = 0xED; break;
                case 0x25: walk = 0xD7; run = 0xD7; break;
                default: walk = 0xEC; run = 0xF8; break;
                }
                P_U8(0xAA) = 0x50;
                anim = walk;
                speed = vel * 0.0625f + 0.6f;
                if (20.0f <= v) {
                    anim = run;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x21:
            if (1.0f <= v) {
                P_U8(0xAA) = 0x6E;
                anim = 0x123;
                speed = vel * 0.0625f + 0.6f;
                if (15.0f <= v) {
                    anim = 0x124;
                    speed = vel / 27.0f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x3A:
            if (1.0f <= v) {
                P_U8(0xAA) = 0x50;
                anim = 0x1FB;
                speed = vel * 0.0625f + 0.6f;
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x2D:
        case 0x2E:
            if (1.0f <= v) {
                anim = 0x1B0;
                speed = vel * 0.0625f + 0.6f;
                if (20.0f <= v) {
                    anim = 0x1B1;
                    speed = vel / 22.0f + 0.4f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        case 0x19:
        case 0x40:
            v = P_F32(0x3C);
            if (1.0f <= v) {
                blend = 8.0f;
                anim = 0x112;
                speed = vel * 0.125f + 0.3f;
                if (18.0f <= v) {
                    anim = 0x111;
                    speed = vel / 20.0f + 0.3f;
                }
            } else {
                anim = walk_anim_cancel_special();
            }
            break;
        default:
            if (ctx[0x1A] != 0 && 1.0f < stickMag) {
                /* swimming */
                speed = vel / 6.5f + 0.3f;
                P_U8(0xAA) = 0x28;
                anim = 0x6D;
                blend = 8.0f;
            } else if (*(s16 *)(ctx + 8) > 0) {
                if (stickMag < 1.0f) {
                    anim = walk_anim_cancel_special();
                } else {
                    speed = vel / 6.0f + 0.3f;
                    anim = *(u16 *)(ctx + 0xE);
                    blend = 16.0f;
                }
            } else if (ctx[0x17] != 0) {
                blend = 5.0f;
                if (*(u16 *)D_800CC6A4 & 0x2000) {
                    if (*(u16 *)((u8 *)player + 0x84) != 0x283) {
                        P_F32(0x3C) *= 0.2f;
                        g_cur_obj_cmd = 0xFF010604;
                        objev_sound_300_1800();
                    }
                    P_U8(0x89) = 3;
                    P_U8(0x8A) = 3;
                    anim = 0x283;
                } else {
                    if (*(u16 *)((u8 *)player + 0x84) == 0x283) {
                        g_cur_obj_cmd = 0xFF010604;
                        objev_sound_300_1800();
                        v = P_F32(0x44);
                    }
                    if (1.0f <= v && P_U8(0x89) == 0) {
                        P_U8(0xAA) = 0x2D;
                        anim = 0x4E;
                        speed = P_F32(0x3C) / 9.0f;
                    } else {
                        anim = walk_anim_cancel_special();
                    }
                }
            } else if ((*(u16 *)(ctx + 0x32) & 2) && 1.0f <= v) {
                /* pushing */
                ctx[0x3C] = 0x1C;
                P_U8(0xAA) = 0xF;
                blend = 8.0f;
                speed = pushSpeed / 5.0f + 0.3f;
                anim = 100;
                if ((u32)random_int() % 1000 >= 988) {
                    anim = (random_int() & 1) + 0x65;
                    speed = 0.65f;
                    P_U8(0x89) = 0xFF;
                    P_U8(0x83) = 0xFF;
                }
            }
            break;
        }
    }
    if (anim != 0 && anim != 999) {
        obj_start_anim(player, anim, speed, blend, 0.0f, 0.0f, 0);
    }
    return anim;
}
#undef P_U8
#undef P_F32

/* P216 / P219: readable C for player_item_action (game_eu_90F50, 4838 words, 0x42-case switch on `kind` via jtbl_80099C40).
 * P216 wrote the prologue, the tail and most cases; P219 fixed cases 3 / 9 / 0x15 / 0x37 / 0x38 / 0x39 / 0x3C (missing
 * calls) and wrote 0x24 0x3B 0x12 0x23 0x17 0x1A 0x2A 0x1B 0x26 0x3A 0x3E. Case numbers come from the jump table
 * (`port_work/p216/jtbl.txt`, read from conker/conker.eu.bin); the rodata floats D_80099Dxx are written as literals
 * (exact values checked against the ROM). Cases 0xD 0x1C..0x20 0x29 0x2B 0x2C 0x2F..0x33 0x3D go straight to the tail. */
s32 player_try_begin_action(struct127 *obj, s32 anim, s32 arg2, s8 kind, s32 held);   /* returns the anim (999 = none) */
s32 obj_setup_undo(struct127 *, s32);
s32 obj_setup_run(struct127 *, s32, f32, s32);
void obj_start_anim(struct127 *, u16, f32, f32, f32, f32, s32);
void obj_sfx_play(s32, struct127 *);
void obj_spawn_effect50_with_sound(struct127 *);
u8 *item_effect_spawn(u8 kind, s32 arg1); /* P222: as port's C (arg1 unused) */
s32 aiscript_find_by_kind(s32, s32);
void obj_point_fx_broadcast_kill(struct127 *);
void object_bone_point_effects(struct127 *);
extern u16 D_80099A60[][4];  /* per weapon row (kind 2 / 0x13 / 0xA / other): {start, idle, fire, stop} anims */
extern u8 D_eu_800C3E78;
extern s16 D_800CC264;
extern u8 D_800CC2B0;
extern u8 D_800BE9A0;
extern s32 g_level_id;       /* level; was D_800BE9F0 */
extern u8 D_800BE616;
extern u8 *g_obj0_state; /* was D_800CCA0C */
extern u8 D_800D2E68;
extern u8 *D_800D34B8;
extern s32 g_cur_obj_cmd; /* was D_800D1580 */

extern s32 D_800CC6A0;
extern s32 D_800CC6B0;
extern u16 D_800BEB30[];
void hint_box_open(s32);
void hint_box_close(void);
s32 hint_box_is_closed(void);
s32 mp3_stream_get_state(void);
extern s32 D_800864A0[2];
extern u16 D_80099A90[];
void face_anim_reset_default(struct127 *);
void face_anim_start(struct127 *, u8, u8, u16, s32);
void gunfire_burst_spawn(struct127 *arg0, struct127 *arg1, u8 arg2, u8 arg3); /* P222: as port's functions.h */
s32 sfx_cb_delayed_play_2d();
void objev_spawn_helper_object(void);
struct127 *obj_find_held(struct127 *, s32);
void char_fx_glow_spawn(s32);
extern s32 g_frame_ticks; /* was D_800BE9E4 */
extern u8 g_level_first_frame; /* was D_800BE9B4 */
extern u16 D_80099A80[];
extern u16 D_80099A88[];
struct127 *obj_find_by_setup_id(u8);
s32 object_point_effect_spawn(struct127 *, s32, s32, s32, s32);
u16 sfx_emitter_start(u16, s16, s16, s16, s32, u16, s16, s32, void *, s32, s32, s32);
s32 sound_pick_variant(s32, s32);
void sfx_emitter_stop_by_callback(s32, s32, s32);
void actor_sound_play2_delayed(u16, struct127 *, s32, s32, s32, s32);
void camera_track_start(s32, s32);
s32 random_int(void);
s32 callback_return_zero(s32, s32, s32, s32);
s32 sfx_cb_follow_object_anim(s32, s32, s32, s32, s32, s32, s32);

#define B(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define SH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define CTL ((u8 *)obj->unk31C)
#define POSARGS(o) (s16)(*(f32 *)((u8 *)(o) + 0x14)), (s16)(*(f32 *)((u8 *)(o) + 0x18)), (s16)(*(f32 *)((u8 *)(o) + 0x1C))


// player_item_action: per-frame action of the held item / pad mode `kind` (1..0x42) for the player obj.
// held = pressed-button word (0x4000 use, 0x2000 fire, 0x8000 ...), height = ground height (f32; +50 when obj +0x20 > 0).
// Picks an animation (returned; 999 = keep, 1000 = item finished) and plays it through obj_start_anim unless noAnim.
/* was func_15065E18 */
s32 player_item_action(struct127 *obj, s32 buttons, s32 held, f32 height, s32 recurse, s32 kind, s32 stunned,
                  s32 timeout, s32 noAnim) {
    u8 done = 0;          /* sp13F: return 1000 */
    s32 setFlag58 = 0;    /* sp140 */
    s32 sound = 0;        /* sp138 */
    s32 clearItem = 1;    /* sp144 */
    f32 speed = 1.0f;     /* sp150 */
    f32 blend = 4.0f;     /* sp14C */
    f32 f148 = 0.0f;      /* sp148 */
    s32 anim = 0;         /* s3 */
    s32 row;
    u16 *r;

    if (B(CTL, 0x11A) == 3 || B(obj, 0x104) != 0 || recurse != 0) {
        held &= ~0x4000;
        D_800CC6AC &= ~0x4000;
        if (recurse != 0) {
            if (B(obj, 0x104) == 0) {
                W(obj, 0x1C4) = 0;
            }
            held &= ~0x2000;
            D_800CC6AC &= ~0x2000;
        }
    }
    if (0.0f < F(obj, 0x20)) {
        height += 50.0f;
    }
    switch (kind) {
    case 2: case 0xA: case 0x13: case 0x34: /* 15065F40: weapons, rows D_80099A60 */
        done = 1;
        row = (kind == 2) ? 0 : (kind == 0x13) ? 1 : (kind == 0xA) ? 2 : 3;
        if (stunned != 0) {
            if (kind == 0xA) {
                obj_setup_undo(obj, 0x28);
                obj_setup_undo(obj, 0x29);
                B(CTL, 0x11A) = 0;
            } else if (kind == 0x34) {
                obj_setup_undo(obj, 0x3D);
                B(CTL, 0x11A) = 0;
            }
        }
        if (kind == B(CTL, 0x78)) {
            F(obj, 0x3C) = 0.0f;
        }
        if (B(obj, 0xAD) != 0 && (kind == B(CTL, 0x78) || B(CTL, 0x11A) != 0)) {
            B(CTL, 0x78) = 0;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
            if (kind == 0xA) {
                obj_setup_undo(obj, 0x28);
                obj_setup_undo(obj, 0x29);
                B(CTL, 0x11A) = 0;
            }
        } else if ((height <= 0.0f && (held & 0x4000)) || recurse != 0) {
            if (B(CTL, 0x78) != 0 || recurse != 0) {
                if (H(CTL, 0x72) == 0 || recurse != 0) {
                    B(obj, 0x89) = 0xFF;
                    B(obj, 0x8A) = 0xFF;
                    B(obj, 0x83) = 0xFF;
                    anim = D_80099A60[row][3];
                    B(CTL, 0x11A) = 3;
                    H(CTL, 0x72) = 0x5A;
                    setFlag58 = 1;
                }
            } else if (H(CTL, 0x72) == 0 && SH(W(obj, 0x318), 0x73C) != 1 && SH(W(obj, 0x318), 0x73C) != 3) {
                B(CTL, 0x1B) = 0;
                B(CTL, 0x11A) = 1;
                anim = D_80099A60[row][0];
                B(obj, 0x83) = 0xFF;
                B(obj, 0x89) = 0xFF;
                H(CTL, 0x72) = 0x5A;
            }
            held &= ~0x4000;
        }
        r = D_80099A60[row];
        if (B(CTL, 0x78) != 0 && (held & 0x2000) && anim == 0 && H(obj, 0x84) == r[1]) {
            anim = r[2];
            B(CTL, 0x1B)++;
        }
        if ((H(obj, 0x84) == r[1] || H(obj, 0x84) == r[0] || H(obj, 0x84) == r[2] || anim != 0) && anim != r[3]) {
            B(CTL, 0x78) = kind;
            *(u16 *)D_800CC6A4 &= ~0x2000;
            setFlag58 = 1;
        } else {
            B(CTL, 0x78) = 0;
        }
        if (D_eu_800C3E78 == 0) {
            break;
        }
        if (B(CTL, 0x11A) == 1 || B(CTL, 0x11A) == 2) {
            anim = r[1];
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x78) = kind;
            B(CTL, 0x11A) = 2;
            if (kind == 2 || kind == 0x13) {
                obj_setup_run(obj, 8, 1.0f, 0);
            } else if (kind == 0xA) {
                obj_setup_run(obj, 0x28, 1.0f, 0);
                obj_setup_run(obj, 0x29, 1.0f, 0);
            }
        } else {
            B(CTL, 0x11A) = 0;
            B(CTL, 0x78) = 0;
            if (kind == 2 || kind == 0x13) {
                obj_setup_undo(obj, 8);
            } else if (kind == 0xA) {
                obj_setup_undo(obj, 0x28);
                obj_setup_undo(obj, 0x29);
            } else if (kind == 0x34) {
                obj_setup_undo(obj, 0x3D);
            }
        }
        break;

    case 0x14: case 0x3F: { /* 15066378 */
        s32 animOn, animOff, sub, animSwim, animA, animB;
        if (kind == 0x14) {
            animOn = 0x102; animOff = 0x103; sub = 0x28; animSwim = 0x12B; animA = 0xF7; animB = 0xC3;
        } else {
            animOn = 0x2CA; animOff = 0x2CB; sub = 0x2F; animSwim = 0x2CE; animA = 0x2CC; animB = 0x2CD;
        }
        anim = 999;
        if (timeout != 0 && B(CTL, 0x78) != 0) {
            obj_setup_run(obj, sub, 1.0f, 0);
        }
        if ((held & 0x4000) && height <= 0.0f) {
            if (B(CTL, 0x78) != 0) {
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                B(obj, 0x8A) = 0xFF;
                B(CTL, 0x11A) = 3;
                speed = 2.0f;
                anim = animOff;
                B(CTL, 0x78) = 0;
            } else {
                B(obj, 0x89) = 0x10;
                B(obj, 0x83) = 0x10;
                B(obj, 0x8A) = 0x10;
                speed = 2.0f;
                B(CTL, 0x11A) = 1;
                anim = animOn;
                B(CTL, 0x78) = kind;
            }
        }
        if (anim != 999) {
            speed = 2.0f;
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            obj_setup_undo(obj, sub);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (kind != B(CTL, 0x78)) {
            break;
        }
        B(obj, 0xAA) = 0x4B;
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (B(CTL, 0x197) != 0) {
            B(obj, 0x8A) = 10;
            B(obj, 0x89) = 0;
            if ((held & 0x2000) && H(CTL, 0x72) == 0) {
                B(obj, 0x83) = 0xF;
                B(CTL, 0x1B4) |= 3;
                D_800CC2B0 = 1;
                f148 = 6.0f;
                anim = animSwim;
                H(CTL, 0x72) = 0x28;
            }
            break;
        }
        if ((held & 0x2000) && height <= 0.0f && B(obj, 0x89) == 0 && H(CTL, 0x72) == 0) {
            H(CTL, 0x72) = 0x28;
            anim = (2.0f < F(obj, 0x3C)) ? animB : animA;
            B(obj, 0x89) = 0xF;
            B(obj, 0x83) = 0xF;
            B(obj, 0x8A) = 0xF;
        }
        break;
    }

    case 3: /* 1506660C */
        done = 1;
        if (recurse != 0 || stunned != 0) {
            if (g_level_id != 0xA) {
                B(CTL, 0x78) = 0;
                B(CTL, 0xD) = 0;
                B(obj, 0x83) = 0;
            }
            if (stunned != 0) {
                clearItem = 0;
            }
            break;
        }
        if (B(CTL, 0x16) != 0) {
            break;
        }
        if (SH(CTL, 0x8) != 0) {
            SH(CTL, 0x8) -= D_800BE9A0;
            if (SH(CTL, 0x8) < 100) {
                SH(CTL, 0xE) = 0xAD;
                B(CTL, 0x16) = 0xC8;
                face_set_default_anim(obj, 0x2A);
                speed = 1.3f /* D_80099D48 */;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                B(CTL, 0x78) = 0;
                anim = 0x2D;
            }
        }
        if (B(CTL, 0x16) != 0) {
            break;
        }
        if (height <= 0.0f && (held & 0x4000)) {
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            if (B(CTL, 0x78) != 0) {
                speed = 1.3f /* D_80099D4C */;
                anim = 0x2D;
                B(CTL, 0x78) = 0;
            } else {
                B(CTL, 0x78) = 3;
                B(CTL, 0xD) = 0;
                anim = 0x2E;
                speed = 1.6f /* D_80099D50 */;
            }
            break;
        }
        if (B(CTL, 0x78) != 3 || B(obj, 0x89) == 0xFF) {
            break;
        }
        B(CTL, 0x78) = 3;
        anim = 0x2C;
        if (D_800BE616 != 0) {
            B(obj, 0x8A) = 10;
        }
        D_800CC6D2 = ((s8 *)D_800CC6A4)[2] * 150;
        if (B(CTL, 0x84) != 0) {
            SH(CTL, 0x12) = 0;
        } else if (D_800CC6D2 < -8000 && SH(CTL, 0x12) < -7000) {
            H(obj, 0x7A) = H(obj, 0x76) = H(obj, 0x76) + D_800CC264 * 7;
            anim = 0xE0;
            speed = 3.0f;
        } else if (D_800CC6D2 > 8000 && SH(CTL, 0x12) > 7000) {
            H(obj, 0x7A) = H(obj, 0x76) = H(obj, 0x76) - D_800CC264 * 7;
            anim = 0xE0;
            speed = 3.0f;
        }
        D_800CC6D4 = 10.0f;
        blend = 8.0f;
        B(obj, 0x89) = 0x10;
        B(obj, 0x83) = 0x10;
        if (B(CTL, 0xD) == 0) {
            B(CTL, 0xD) = 1;
            obj_spawn_effect50_with_sound(obj);
        }
        break;

    case 1: case 0x35: /* 150668EC */
        if (!(held & 0x4000) || (!(height <= 0.0f) && kind != 0x35) || g_obj0_state[0x4E] == 1 ||
            B(obj, 0x13C) >= 100 || B(obj, 0xA9) != 0) {
            break;
        }
        B(obj, 0x81) = 1;
        B(obj, 0xA9) = 2;
        B(obj, 0x89) = 0x78;
        F(obj, 0x24) = 6.0f;
        F(obj, 0x1CC) = -100000.0f /* D_80099D54 */;
        F(obj, 0x3C) = F(obj, 0x3C) * 0.5f;
        anim = 0x4A;
        speed = 1.8f /* D_80099D58 */;
        F(obj, 0x20) = 80.0f;
        B(CTL, 0x31) = 0;
        break;

    case 4: /* 150669B4 */
        B(CTL, 0x78) = (held & 0x4000) ? kind : 0;
        return 0;

    case 0x42: /* 150669D8 */
        if (!(D_800D2E68 & 4)) {
            if (held & 0x4000) {
                B(CTL, 0x78) = kind;
                return 0;
            }
            B(CTL, 0x78) = 0;
        }
        return 0;

    case 5: /* 15066A10 */
        if (!(held & 0x4000) || !(height <= 0.0f)) {
            break;
        }
        if (H(obj, 0x84) == 0x2F) {
            anim = 999;
            break;
        }
        B(CTL, 0x30) = 0x12;
        anim = 0x2F;
        if (g_level_id == 0x31) {
            F(CTL, 0x28) = SH(D_800D34B8, 0x270);
            F(CTL, 0x2C) = SH(D_800D34B8, 0x274);
            item_effect_spawn(5, 0);
        } else {
            F(CTL, 0x28) = SH(D_800D34B8, 0x68);
            F(CTL, 0x2C) = SH(D_800D34B8, 0x6C);
            item_effect_spawn(0, 0);
        }
        H(obj, 0x76) = 0xC000;
        speed = 1.05f /* D_80099D5C */;
        blend = 6.0f;
        B(obj, 0x89) = 0xFF;
        B(obj, 0x83) = 0xFF;
        sound = 0x143;
        break;

    case 6: /* 15066B3C */
    case 7: /* 15066C24: same with anim 0x45, mode 7 */
        if (B(CTL, 0x78) == 0) {
            if ((held & 0x4000) && height <= 0.0f && H(CTL, 0x72) == 0) {
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                anim = (kind == 6) ? 0x44 : 0x45;
                B(CTL, 0x78) = (kind == 6) ? 6 : 7;
            }
        } else if (H(obj, 0x84) == ((kind == 6) ? 0x44 : 0x45)) {
            anim = 999;
        } else {
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
            B(CTL, 0x78) = 0;
        }
        break;

    case 0x36: /* 15066BC0 */
        if ((held & 0x4000) && height <= 0.0f) {
            u8 *t = (u8 *)attachment_find_by_slot(obj, 0x3C, 0);
            if (t != NULL && W(t, 0x38) < 250) {
                anim = 0x240;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x8A) = 0xFF;
                B(obj, 0x83) = 0xFF;
            }
        }
        break;

    case 8: { /* 15066CA8: the other player obj +0x65 */
        u8 *other = (u8 *)g_objects + (B(obj, 0x65) - 1) * 0x32C;
        B(obj, 0x8A) = 0x14;
        if (!(held & 0xC000)) {
            break;
        }
        if (H(other, 0x84) == 0 || H(other, 0x22E) != 0 || H(other, 0x84) == 0xC || H(other, 0x84) == 0xD) {
            s32 code = 0x10;
            g_cur_obj = (struct127 *)other;
            if (held & 0x4000) {
                code = 0xE;
            } else {
                H(other, 0x84) = 0;
            }
            W(other, 0x218) = aiscript_find_by_kind(1, code);
            H(other, 0x21C) = 0;
            g_cur_obj = obj;
            H(other, 0x22E) = 0;
        }
        anim = 999;
        break;
    }

    case 0x27: /* 15066D6C */
        if (kind != B(CTL, 0x78)) {
            B(CTL, 0x78) = 0x27;
            B(obj, 0x1C9) = 6;
            B(CTL, 0x17) = 1;
        }
        break;

    case 9: { /* 15066D9C: steerable item (anim 0x7B), matrix-physics mode spins ctl +0x7E */
        u8 fire = 0; /* sp10C */
        if (D_eu_800C3E78 != 0) {
            if (B(CTL, 0x11A) == 1 || B(CTL, 0x11A) == 2) {
                obj_knockdown_start(obj);
            } else {
                obj_knockdown_clear(obj);
            }
        }
        if (kind != B(CTL, 0x78)) {
            speed = 1.4f; /* D_80099D74 */
            anim = player_try_begin_action(obj, 0x7B, 1, kind, held);
            if (anim != 999) {
                SH(CTL, 0x24) = 0x3C;
            }
            break;
        }
        {
            s16 d;
            d = -((s8 *)D_800CC6A4)[2] * 100 - SH(CTL, 0x80);
            if (d > 600) d = 600;
            if (d < -600) d = -600;
            SH(CTL, 0x80) += d;
            d = ((s8 *)D_800CC6A4)[3] * 32 - SH(CTL, 0x82) + 0x240;
            if (d > 300) d = 300;
            if (d < -300) d = -300;
            SH(CTL, 0x82) += d;
        }
        if ((recurse != 0 && (B(obj, 0x65) != 0 || B(obj, 0x104) != 0 || F(obj, 0x28) != 0.0f)) || B(obj, 0xAD) != 0) {
            obj_knockdown_clear(obj);
            break;
        }
        if (recurse != 0) {
            speed = 1.4f; /* D_80099D60 */
            anim = player_try_begin_action(obj, 0x7D, 1, 0, held | 0x4000);
            if (anim == 999) {
                obj_knockdown_clear(obj);
            }
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        if (B(CTL, 0x7D) != 0) {
            if ((buttons & 0x2000) && F(obj, 0x48) < 0.6f /* D_80099D64 */) {
                u16 old = H(CTL, 0x7E);
                H(CTL, 0x7E) = old + D_800CC264 * 4 / 3;
                if ((old ^ H(CTL, 0x7E)) & 0x100) {
                    g_cur_obj_cmd = 0x13;
                    if (H(CTL, 0x7E) & 0x200) {
                        g_cur_obj_cmd = 0x14;
                    }
                    objev_run_action();
                    g_cur_obj_cmd = 0xFF0306E0;
                    objev_sound_300_1800();
                    actor_sound_play_untracked((random_int() & 1) + 0x2F5, obj, 0x7D00, 0x1F4, 1000);
                    if ((random_int() & 7) == 0) {
                        actor_sound_play_untracked_delay(0x5CD, obj, 0x5DC0, 0x1F4, 1000, 0x32);
                    }
                }
            } else {
                u16 v = H(CTL, 0x7E);
                H(CTL, 0x7E) = (v & 0xFF00) | ((v * 2 + 1) & 0xFF);
            }
            break;
        }
        player_aim_turn_update((u8 *)obj, buttons, 0x2010);
        if (H(obj, 0x84) == 0x11A || H(obj, 0x84) == 0x7B) {
            break;
        }
        if (!(buttons & 0x2000) && (H(CTL, 0x88) & 0x2000)) {
            fire = 1;
        }
        if (SH(CTL, 0x24) == 0 || (held & 0x8000)) {
            anim = 0x11A;
            if (!(held & 0x8000)) {
                fire = 1;
            }
            SH(CTL, 0x24) = 0x3C;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
        } else if ((buttons & 0x2000) && B(obj, 0x89) == 0) {
            anim = 0x7C;
            if (F(obj, 0x3C) != 0.0f) {
                anim = 0x20D;
                if (20.0f <= F(obj, 0x44)) {
                    anim = 0x238;
                    speed = F(obj, 0x3C) / 22.0f + 0.4f; /* D_80099D68 */
                }
                if (!(buttons & 0x10)) {
                    SH(CTL, 0x12) = 0;
                    B(CTL, 0x3C) = 3;
                } else {
                    B(CTL, 0x3C) = 0;
                }
                if (D_800BE616 == 0) {
                    B(obj, 0xAA) = 0x37;
                }
            }
            B(obj, 0x83) = 8;
            if (H(obj, 0x84) != 0x7C && H(obj, 0x84) != 0x20D && H(obj, 0x84) != 0x238) {
                /* fire sounds (inlined in the asm): sound 0x2CF at the obj, then for obj kinds 0x3B / 0x80 one time in
                 * four a voice line; D_80099A80 is passed through to sfx_emitter_start */
                obj_point_fx_broadcast_kill(obj);
                sfx_emitter_start(0x2CF, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)sfx_cb_follow_object_anim, obj, (s32)D_80099A80, 0, 0);
                if ((B(obj, 4) == 0x3B || B(obj, 4) == 0x80) && (random_int() & 3) == 0) {
                    u16 v = (B(obj, 4) == 0x3B) ? sound_pick_variant(0x543, 4) : sound_pick_variant(0x57C, 6);
                    sfx_emitter_start(v, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)sfx_cb_follow_object_anim, obj, (s32)D_80099A80, 0, 0);
                }
            }
        } else if (W(obj, 0x2EC) != 0 && g_level_id == 0x36) {
            if ((held & 0x4000) && W(obj, 0x2EC) == 1 && F(obj, 0x28) == 0.0f) {
                blend = 16.0f;
                speed = 0.7f; /* D_80099D6C */
                anim = 0x20F;
                H(obj, 0x76) = 0;
                if (0.0f < F(obj, 0x14)) {
                    H(obj, 0x76) = 0x8000;
                    anim = 0x20E;
                }
                F(obj, 0x3C) = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                B(obj, 0x81) = 1;
            }
        } else {
            speed = 1.4f; /* D_80099D70 */
            anim = player_try_begin_action(obj, 0x7D, 1, 0, held);
        }
        if (fire) {
            object_bone_point_effects(obj);
        }
        break;
    }

    case 0x38: { /* 1506749C: anims 0x1DD..0x254, charge ctl +0x1A2 / +0x1A4 */
        u8 fire = 0; /* sp107 */
        s32 a0;
        if (kind != B(CTL, 0x78)) {
            speed = 1.4f; /* D_80099D80 */
            anim = player_try_begin_action(obj, 0x1DD, 1, kind, held);
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            obj_setup_undo(obj, 0x7B);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        player_aim_turn_update((u8 *)obj, buttons, 0x2010);
        a0 = H(obj, 0x84);
        if (a0 == 0x1DD) {
            break;
        }
        if (!(buttons & 0x2000) && (H(CTL, 0x88) & 0x2000)) {
            fire = 1;
        }
        if (buttons & 0x2000) {
            anim = 0x1E0;
            if (F(obj, 0x3C) != 0.0f) {
                anim = 0x253;
                if (20.0f <= F(obj, 0x44)) {
                    anim = 0x254;
                    speed = F(obj, 0x3C) / 22.0f + 0.4f; /* D_80099D78 */
                }
                if (!(buttons & 0x10)) {
                    B(CTL, 0x3C) = 3;
                    SH(CTL, 0x12) = 0;
                }
            }
            blend = 0.0f;
            B(obj, 0x83) = 8;
            if (a0 != 0x1E0 && a0 != 0x253 && a0 != 0x254) {
                /* fire sounds (inlined in the asm): sound 0x2CF at the obj, then for obj kinds 0x3B / 0x80 one time in
                 * four a voice line; D_80099A88 is passed through to sfx_emitter_start */
                obj_point_fx_broadcast_kill(obj);
                sfx_emitter_start(0x2CF, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)sfx_cb_follow_object_anim, obj, (s32)D_80099A88, 0, 0);
                if ((B(obj, 4) == 0x3B || B(obj, 4) == 0x80) && (random_int() & 3) == 0) {
                    u16 v = (B(obj, 4) == 0x3B) ? sound_pick_variant(0x543, 4) : sound_pick_variant(0x57C, 6);
                    sfx_emitter_start(v, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)sfx_cb_follow_object_anim, obj, (s32)D_80099A88, 0, 0);
                }
            }
            H(CTL, 0x1A4) += g_frame_ticks * 10;
            if (H(CTL, 0x1A2) >= 0xB0) {
                H(CTL, 0x1A2) = 0xAF;
            }
            H(CTL, 0x1A2) += H(CTL, 0x1A4) * g_frame_ticks;
            if (H(CTL, 0x1A2) > 0x1E00) {
                H(CTL, 0x1A2) = 0x1E00;
            }
        } else {
            speed = 1.4f; /* D_80099D7C */
            anim = player_try_begin_action(obj, 0x1DE, 1, 0, held);
            H(CTL, 0x1A2) = 0;
            H(CTL, 0x1A4) = 0;
        }
        if (fire) {
            object_point_effect_spawn(obj, 5, 0x78, 0xFF, 1);
        }
        break;
    }

    case 0x39: /* 15067854: anims 0x1EE / 0x21E / 0x1EB, shot sound */
        if (kind != B(CTL, 0x78)) {
            speed = 1.4f; /* D_80099D88 */
            anim = player_try_begin_action(obj, 0x1EE, 1, kind, held);
            if (anim != 999) {
                SH(CTL, 0x24) = 0x1E;
            }
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            obj_setup_undo(obj, 0x82);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        player_aim_turn_update((u8 *)obj, buttons, 0x2010);
        if (H(obj, 0x84) == 0x1EE) {
            break;
        }
        if (H(obj, 0x84) == 0x21E) {
            B(obj, 0x89) = 0xFF;
        }
        if (SH(CTL, 0x24) == 0 || ((held & 0x8000) && H(obj, 0x84) != 0x21E)) {
            if (F(obj, 0x28) == 0.0f) {
                SH(CTL, 0x24) = 0x1E;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                anim = 0x21E;
            }
            break;
        }
        if ((held & 0x2000) && H(obj, 0x84) != 0x1EE && H(obj, 0x84) != 0x21E) {
            anim = 999;
            if (F(obj, 0x3C) == 0.0f) {
                anim = 0x1EB;
            } else {
                g_cur_obj_cmd = 0x53;
                objev_run_action();
            }
            sfx_emitter_stop_by_callback((s32)callback_return_zero, (s32)obj, B(obj, 0x3B));
            sfx_emitter_start((random_int() & 1) + 0x2F3, (s16)F(obj, 0x14), (s16)F(obj, 0x18), (s16)F(obj, 0x1C), 0x7D00,
                          0x5DC, 0x1F4, (s32)callback_return_zero, obj, B(obj, 0x3B), 0, 0);
            if (W(obj, 0x318) != 0) {
                actor_sound_play2_delayed((u32)random_int() % 3 + 0x2EB, obj, 0x7D00, 0x64, 0x78, 0x19);
            }
        } else {
            speed = 1.4f; /* D_80099D84 */
            anim = player_try_begin_action(obj, 0x1EF, 1, 0, held);
        }
        break;

    case 0x37: /* 15067AE4: anims 0x1F7 / 0x1F4 / 0x235 / 0x1F8 */
        if (kind != B(CTL, 0x78)) {
            speed = 1.4f; /* D_80099D90 */
            anim = player_try_begin_action(obj, 0x1F7, 1, kind, held);
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            obj_setup_undo(obj, 0x85);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        player_aim_turn_update((u8 *)obj, buttons, 0x2010);
        if ((held & 0x2000) && H(obj, 0x84) != 0x1F7 && H(CTL, 0x19E) == 0) {
            anim = (random_int() & 3) ? 0x1F4 : 0x235;
            blend = 0.0f;
            H(CTL, 0x19E) = 100;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
        } else if (held & 0x4000) {
            speed = 1.4f; /* D_80099D8C */
            anim = player_try_begin_action(obj, 0x1F8, 1, 0, held);
        }
        break;

    case 0xB: /* 15067C14: anim 0x68 */
        if (H(obj, 0x84) == 0x68) {
            if (F(W(obj, 0x2D0), 8) < 68.0f && B(obj, 0x222) != 0) {
                D_800CC6D2 = H(obj, 0x7A) - obj_yaw_to_linked_obj((u8 *)obj) - 0x2000;
            }
            D_800CC6D4 = 4.0f;
            anim = 999;
            break;
        }
        if ((held & 0x4000) && height <= 0.0f) {
            speed = 1.2f; /* D_80099D94 */
            anim = 0x68;
            blend = 6.0f;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
        }
        break;

    case 0xC: case 0x16: /* 15067CD4: anims 0x76 / 0x78 / 0x77 / 0x207 / 0x2C7 */
        anim = 999;
        if (recurse != 0 && kind == 0x16) {
            if (kind == B(CTL, 0x78)) {
                s32 end = 1;
                if ((s32)F(obj, 0x28) == 0) {
                    anim = player_try_begin_action(obj, 0x78, 1, 0, held | 0x4000);
                    if (anim != 999) {
                        end = 0;
                    }
                }
                if (end) {
                    obj_setup_undo(obj, 0x24);
                    B(CTL, 0x11A) = 0;
                    B(obj, 0x83) = 0;
                    B(obj, 0x89) = 0;
                }
            }
        } else if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, 0x76, 1, kind, held);
        } else {
            B(obj, 0x8A) = 10;
            if (recurse != 0 && (B(obj, 0x65) != 0 || (s32)F(obj, 0x28) != 0)) {
                obj_setup_undo(obj, 0x24);
                B(CTL, 0x11A) = 0;
            } else if (stunned != 0) {
                if (kind == 0x16 || (kind == 0xC && F(obj, 0x28) == 0.0f && B(obj, 0x1CA) != 0)) {
                    clearItem = 0;
                } else {
                    obj_setup_undo(obj, 0x24);
                    B(CTL, 0x11A) = 0;
                }
            } else if ((held & 0x4000) || recurse != 0) {
                anim = player_try_begin_action(obj, 0x78, 1, 0, held | 0x4000);
                if (anim == 999 && recurse != 0) {
                    obj_setup_undo(obj, 0x24);
                    B(CTL, 0x11A) = 0;
                    B(obj, 0x83) = 0;
                }
            } else if ((held & 0x2000) && H(obj, 0x84) != 0x76 && H(CTL, 0x19E) == 0) {
                if (B(CTL, 0x1B2) != 0) {
                    anim = 0x2C7;
                } else if (kind == 0xC || g_level_id == 0x2B) {
                    anim = 0x207;
                } else {
                    anim = D_800BE616 ? 0x77 : 0x207;
                }
                blend = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                if (B(CTL, 0x197) != 0 && W(obj, 0x318) != 0) {
                    camera_track_start(W(obj, 0x318), 0);
                }
                H(CTL, 0x19E) = 100;
            } else if (B(CTL, 0x197) != 0 && W(obj, 0x318) != 0 && B(obj, 4) == 0x80 && actor_sound2_is_playing(obj) == 0 &&
                       (random_int() & 0x7F) == 0) {
                obj_sfx_play(sound_pick_variant(0x568, 4), obj);
            }
        }
        if (kind == 0xC && (kind == B(CTL, 0x78) || B(CTL, 0x11A) != 0)) {
            F(obj, 0x3C) = 0.0f;
            if ((s32)F(obj, 0x28) != 0) {
                obj_setup_undo(obj, 0x24);
                B(CTL, 0x11A) = 0;
                B(CTL, 0x78) = 0;
            }
        }
        break;

    case 0x19: case 0x40: /* 15068034 */
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, (kind == 0x19) ? 0x10E : 0x2C2, 1, kind, held);
            break;
        }
        if (B(CTL, 0x11A) != 2) {
            break;
        }
        if (held & 0x2000) {
            anim = obj_pick_attack_anim((u8 *)obj, 0x113, 0x113, 0x119);
            B(obj, 0x89) = 0xFF;
        } else {
            anim = player_try_begin_action(obj, (kind == 0x19) ? 0x110 : 0x2C3, 1, 0, held);
        }
        break;

    case 0xE: /* 150680F4 */
        B(obj, 0x8A) = 0x14;
        anim = 999;
        break;

    case 0xF: /* 15068104: anims 0xB4 / 0xB6 */
        anim = 999;
        if (kind == B(CTL, 0x78) && (stunned != 0 || B(obj, 0x65) != 0 || recurse != 0)) {
            obj_setup_undo(obj, 0x3A);
            B(CTL, 0x11A) = 0;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
        } else if ((held & 0x4000) && height <= 0.0f) {
            anim = (kind == B(CTL, 0x78)) ? 0xB6 : 0xB4;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x78) = kind;
        }
        if (kind == B(CTL, 0x78)) {
            B(obj, 0x8A) = 10;
            F(obj, 0x3C) = 0.0f;
        }
        break;

    case 0x10: /* 150681BC: anims 0xBE / 0xC1 / 0xC0, stick x -> D_800CC6D2 */
        speed = 1.4f; /* D_80099D98 */
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, 0xBE, 1, kind, held);
            break;
        }
        D_800CC6D2 = ((s8 *)D_800CC6A4)[2] * 200;
        B(obj, 0x8A) = 10;
        if ((buttons & 0x2000) && H(obj, 0x84) != 0xBE) {
            anim = 0xC1;
            speed = 1.0f;
        } else {
            anim = player_try_begin_action(obj, 0xC0, 1, 0, held);
        }
        break;

    case 0x15: /* 15068274: anims 0x168 / 0xE7 / 0x22B / 0xE4 */
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, 0x168, 1, kind, held);
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            obj_setup_undo(obj, 0x4B);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        player_aim_turn_update((u8 *)obj, buttons, 0x2010);
        if ((buttons & 0x2000) && H(obj, 0x84) != 0x168) {
            anim = 0xE7;
            if (F(obj, 0x3C) != 0.0f) {
                B(obj, 0xAA) = 0x50;
                B(CTL, 0x3C) = 3;
                SH(CTL, 0x12) = 0;
                speed = F(obj, 0x3C) * 0.0625f + 0.6f; /* D_80099D9C */
                anim = 0x22B;
                if (20.0f <= F(obj, 0x44)) {
                    speed = F(obj, 0x3C) / 22.0f + 0.4f; /* D_eu_80099DA0 */
                }
            }
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 8;
            if (H(obj, 0x84) != 0xE7 && H(obj, 0x84) != 0x22B) {
                s32 list[2];
                list[0] = 0xE7;
                list[1] = 0x22B;
                SH(CTL, 0x1AA)++;
                obj_effect_run_handler(obj, 9, list);
            }
        } else {
            anim = player_try_begin_action(obj, 0xE4, 1, 0, held);
        }
        break;

    case 0x18: case 0x41: { /* 15068420 */
        s32 a = (kind == 0x18) ? 0xFB : 0x2C8;
        s32 b = (kind == 0x18) ? 0xFC : 0x2C9;
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, a, 1, kind, held);
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (B(CTL, 0x197) != 0 && B(CTL, 0x11A) == 2) {
            B(obj, 0x8A) = 10;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 10;
            if ((*(u16 *)D_800CC6A4 & 0x2000) || (H(CTL, 0x88) & 0x2000)) {
                B(CTL, 0x1B4) |= 1;
                D_800CC2B0 = 1;
            }
            if (a == H(obj, 0x84)) {
                break;
            }
            if (!(*(u16 *)D_800CC6A4 & 0x2000) && (H(CTL, 0x88) & 0x2000) && H(CTL, 0x19E) == 0) {
                B(CTL, 0x1B4) |= 2;
                D_800CC2B0 = 1;
                blend = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                anim = 0x10C;
                H(CTL, 0x19E) = 0x32;
                break;
            }
            if (H(obj, 0x84) != 0x10C) {
                anim = 0x10A;
            }
            break;
        }
        B(obj, 0x8A) = 0x14;
        if ((held & 0x2000) && H(obj, 0x84) != a && H(CTL, 0x19E) == 0) {
            anim = b;
            blend = 0.0f;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            H(CTL, 0x19E) = 0x32;
        } else {
            anim = player_try_begin_action(obj, 0xC6, 1, 0, held);
        }
        break;
    }

    case 0x11: /* 150685F4 */
        if (held & 0x4000) {
            W((u8 *)obj_find_by_setup_id(7), 0x2E4) = 1;
        }
        break;

    case 0x25: case 0x2D: case 0x2E: /* 15068618 */
        B(CTL, 0x78) = kind;
        B(obj, 0x8A) = 0x14;
        break;

    case 0x28: /* 1506862C */
        if (recurse != 0) {
            B(CTL, 0x78) = 0;
        } else if (height <= 0.0f && (held & 0x4000) && kind != B(CTL, 0x78)) {
            B(CTL, 0x78) = kind;
        }
        break;

    case 0x3C: { /* 1506867C: special pad (obj_ctrl_action_update: ctl +0x17 set), spin ctl +0x18 */
        u16 diff = D_800CC6A0 - H(obj, 0x7A);
        anim = 999;
        B(obj, 0x239) = 0x2F;
        if (B(obj, 0x13C) != 0) {
            s16 old = SH(CTL, 0x18);
            f32 mag;
            B(obj, 0x83) = 0xFF;
            B(obj, 0x89) = 0xFF;
            SH(CTL, 0x18) = (SH(CTL, 0x18) < 0) ? SH(CTL, 0x18) + 20 : SH(CTL, 0x18) - 20;
            if ((old ^ SH(CTL, 0x18)) & 0x8000) {
                SH(CTL, 0x18) = 0;
            }
            if (10.0f < F(obj, 0x44)) {
                s16 d = H(CTL, 0x4C) - H(CTL, 0x7E);
                if (d < 0x2000 && d >= -0x1FFF && (d > 0x100 || d < -0x100)) {
                    SH(CTL, 0x18) = (d & 0x8000) ? SH(CTL, 0x18) - 0x28 : SH(CTL, 0x18) + 0x28;
                    if (SH(CTL, 0x18) > 0x1000) SH(CTL, 0x18) = 0x1000;
                    if (SH(CTL, 0x18) < -0x1000) SH(CTL, 0x18) = -0x1000;
                }
            }
            {
                u16 yaw = H(obj, 0x7A) + SH(CTL, 0x18) * D_800CC264 / 100;
                H(obj, 0x7A) = yaw;
                H(obj, 0x76) = yaw;
            }
            if (SH(CTL, 0x18) > 0x200 || SH(CTL, 0x18) < -0x200) {
                u16 now = D_800CC6A0 - H(obj, 0x7A);
                s16 s = SH(CTL, 0x18);
                if (((diff < 0x1000 || diff > 0xF000) && now >= 0x1000 && now < 0x7000 && s < 0) ||
                    (diff > 0x7000 && now <= 0x7000 && s > 0)) {
                    g_cur_obj_cmd = 0xFF0105B6;
                    objev_sound_300_1800();
                }
            }
            H(CTL, 0x7E) = H(CTL, 0x4C);
            mag = fabsf((f32)SH(CTL, 0x18));
            anim = 0x288;
            if (200.0f < mag) anim = 0x286;
            if (2000.0f < mag) anim = 0x27E;
            blend = 16.0f;
            if (g_level_first_frame != 0) {
                blend = 0.0f;
            }
            if (held & 0x4000) {
                u8 *o = (u8 *)obj_find_by_setup_id(6);
                F(o, 0x3C) = 80.0f;
                F(o, 0x3C) = (2000.0f < mag) ? (mag + 1000.0f) / 36.0f : (mag + 2000.0f) / 80.0f;
                B(o, 0x104) = 0;
                B(o, 0x13D) = 0;
                W(o, 0x218) = 0;
                B(o, 0x232) = 2;
                B(obj, 0x13C) = 0;
                B(obj, 0x83) = 0;
                B(obj, 0x89) = 10;
            }
        } else if ((held & 0x4000) && height <= 0.0f && B(obj, 0x8A) == 0 && H(obj, 0x84) != 0x27D) {
            s32 a0 = H(obj, 0x84);
            if (B(obj, 0x89) == 0 || a0 < 0x27A || a0 >= 0x27E) {
                anim = 0x27A;
            } else if (B(obj, 0x103) != 0 || B(obj, 0x107) != 0) {
                anim = a0 + 1;
            }
            if (anim != 999) {
                B(obj, 0x107) = 0;
                B(obj, 0x83) = 0xFF;
                B(obj, 0x89) = 0xFF;
            }
        }
        break;
    }

    case 0x21: /* 15068A34: anims 0x120 / 0x129.. / 0x121 */
        if (recurse != 0 && B(obj, 0x65) != 0) {
            obj_setup_undo(obj, 0x58);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (!(height <= 0.0f)) {
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, 0x120, 1, kind, held);
            speed = 1.4f; /* D_80099DAC */
            break;
        }
        if (B(CTL, 0x11A) != 2) {
            break;
        }
        if (held & 0x2000) {
            anim = obj_pick_attack_anim((u8 *)obj, 0x129, 0x12A, 0x128);
            speed = 1.3f; /* D_eu_80099DA4 */
            B(obj, 0x89) = 0xFF;
        } else {
            anim = player_try_begin_action(obj, 0x121, 1, 0, held);
            speed = 1.4f; /* D_eu_80099DA8 */
        }
        break;

    case 0x22: /* 15068B40: anims 0x15D / 0x15F / 0x15E */
        speed = 1.4f; /* D_80099DB0 */
        if (recurse != 0 && B(obj, 0x65) != 0) {
            obj_setup_undo(obj, 0x56);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (kind == B(CTL, 0x78) && height <= 0.0f) {
            if (B(CTL, 0x11A) != 2) {
                break;
            }
            if (held & 0x2000) {
                anim = obj_pick_attack_anim((u8 *)obj, 0x15F, 0x15F, 0x15F);
                speed = 1.3f; /* D_80099DB4 */
                B(obj, 0x89) = 0xFF;
            } else {
                anim = player_try_begin_action(obj, 0x15E, 1, 0, held);
            }
            break;
        }
        anim = player_try_begin_action(obj, 0x15D, 1, kind, held);
        break;

    case 0x24: /* 15068C3C: anims 0x152 / 0x155 / 0x154 / 0x156 / 0x157 */
        if (recurse != 0) {
            if (kind == B(CTL, 0x78)) {
                s32 end = 1;
                if ((s32)F(obj, 0x28) == 0 && B(CTL, 0x11A) == 2) {
                    anim = player_try_begin_action(obj, 0x155, 1, 0, held | 0x4000);
                    if (anim != 999) {
                        end = 0;
                    }
                }
                if (end) {
                    obj_setup_undo(obj, 0x63);
                    B(CTL, 0x11A) = 0;
                    B(obj, 0x83) = 0;
                    B(obj, 0x89) = 0;
                }
            }
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, 0x152, 1, kind, held);
            break;
        }
        /* (the asm re-tests recurse here: always 0 on this path) */
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (B(CTL, 0x197) != 0 && B(CTL, 0x11A) == 2) {
            B(obj, 0x8A) = 10;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 10;
            if (H(CTL, 0x19E) == 0 && ((*(u16 *)D_800CC6A4 & 0x2000) || (H(CTL, 0x88) & 0x2000))) {
                B(CTL, 0x1B4) |= 1;
                D_800CC2B0 = 1;
            }
            if (H(obj, 0x84) == 0x152) {
                break;
            }
            if (!(*(u16 *)D_800CC6A4 & 0x2000) && (H(CTL, 0x88) & 0x2000) && H(obj, 0x84) == 0x157 &&
                H(CTL, 0x19E) == 0) {
                B(CTL, 0x1B4) |= 2;
                D_800CC2B0 = 1;
                blend = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                H(CTL, 0x19E) = 100;
                anim = 0x156;
                if (W(obj, 0x318) != 0) {
                    s32 m = W(obj, 0x184) & 0x1F;
                    if (m == 5 || m == 3 || m == 6 || m == 9) {
                        actor_sound_play2_delayed((u32)random_int() % 3 + 0x2EB, obj, 0x7D00, 0x64, 0x78, 0x5A);
                    }
                }
                break;
            }
            if (H(obj, 0x84) != 0x156) {
                anim = 0x157;
            }
            break;
        }
        B(obj, 0x8A) = 0x14;
        if ((held & 0x2000) && H(obj, 0x84) != 0x152 && H(CTL, 0x19E) == 0) {
            blend = 0.0f;
            anim = 0x154;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            H(CTL, 0x19E) = 100;
        } else {
            anim = player_try_begin_action(obj, 0x155, 1, 0, held);
        }
        break;

    case 0x3B: /* 15068FA8: anims 0x225 / 0x226 / 0x222 / 0x236 / 0x227 / 0x237 / 0x221 / 0x223 / 0x31B, item 0x89 */
        if (D_eu_800C3E78 != 0) {
            if (kind == B(CTL, 0x78)) {
                obj_setup_run(obj, 0x89, 1.0f, 0);
                B(CTL, 0x11A) = 2;
            } else {
                obj_setup_undo(obj, 0x89);
                B(CTL, 0x11A) = 0;
            }
        }
        if ((kind == B(CTL, 0x78) || B(CTL, 0x11A) != 0) && B(obj, 0xAD) != 0) {
            B(CTL, 0x78) = 0;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
            obj_setup_undo(obj, 0x89);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, 0x225, 1, kind, held);
            break;
        }
        if (recurse != 0 && (B(obj, 0x65) != 0 || B(obj, 0x104) != 0 || B(obj, 0x13C) != 0)) {
            obj_setup_undo(obj, 0x89);
            B(CTL, 0x11A) = 0;
            B(CTL, 0x78) = 0;
            break;
        }
        if (recurse != 0) {
            anim = player_try_begin_action(obj, 0x226, 1, 0, held | 0x4000);
            if (anim == 999) {
                obj_setup_undo(obj, 0x89);
                B(CTL, 0x11A) = 0;
                B(CTL, 0x78) = 0;
                B(obj, 0x83) = 0;
            }
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 0x14;
        player_aim_turn_update((u8 *)obj, buttons, 0x2010);
        if (H(CTL, 0x19E) == 0 && ((D_800CC6B0 & 0x2000) || (H(CTL, 0x88) & 0x2000))) {
            if (B(CTL, 0x198) == 2) {
                B(CTL, 0x1B4) |= 4;
            } else {
                B(CTL, 0x1B4) |= 1;
            }
            D_800CC2B0 = 1;
        }
        /* (the asm re-tests recurse here: always 0 on this path) */
        if ((((D_800CC6B0 & 0x10) && !(D_800CC6B0 & 0x2000) && (H(CTL, 0x88) & 0x2000)) ||
             (!(D_800CC6B0 & 0x10) && (D_800CC6AC & 0x2000))) &&
            H(obj, 0x84) != 0x225 && H(obj, 0x84) != 0x222 && H(obj, 0x84) != 0x236 && H(obj, 0x84) != 0x227 &&
            H(obj, 0x84) != 0x237 && H(CTL, 0x19E) == 0) {
            if (*(u16 *)D_800CC6A4 & 0x10) {
                anim = (random_int() & 3) ? 0x227 : 0x237;
                B(CTL, 0x1B4) |= 2;
                D_800CC2B0 = 1;
            } else {
                anim = (random_int() & 3) ? 0x222 : 0x236;
            }
            blend = 0.0f;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            H(CTL, 0x19E) = 0x32;
            break;
        }
        if ((D_800CC6B0 & 0x10) && (D_800CC6B0 & 0x2000) && H(obj, 0x84) != 0x225) {
            B(obj, 0x89) = 0;
            B(obj, 0x8A) = 8;
            B(obj, 0x83) = 8;
            if (H(obj, 0x84) == 0x222 || H(obj, 0x84) == 0x236 || H(obj, 0x84) == 0x227 || H(obj, 0x84) == 0x237) {
                break;
            }
            if (1.0f <= F(obj, 0x44) || ((s8 *)CTL)[0x23] > 0) {
                anim = 0x223;
                if (20.0f <= F(obj, 0x44)) {
                    anim = 0x31B;
                    speed = F(obj, 0x3C) / 22.0f + 0.4f; /* D_80099DB8 */
                }
            } else {
                anim = 0x221;
            }
            break;
        }
        anim = player_try_begin_action(obj, 0x226, 1, 0, held);
        break;

    case 0x12: /* 15069408: anims 0xC4 / 0xC6 / 0xC7 / 0x10A */
        if ((kind == B(CTL, 0x78) || B(CTL, 0x11A) != 0) && B(obj, 0xAD) != 0) {
            B(CTL, 0x78) = 0;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
            B(CTL, 0x11A) = 0;
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, 0xC4, 1, kind, held);
            if (anim != 999) {
                F(obj, 0x3C) = 0.0f;
            }
            break;
        }
        F(obj, 0x3C) = 0.0f;
        if (recurse != 0 && B(obj, 0x65) != 0) {
            B(CTL, 0x11A) = 0;
            break;
        }
        B(obj, 0x8A) = 0x14;
        if ((*(u16 *)D_800CC6A4 & 0x2000) || (H(CTL, 0x88) & 0x2000)) {
            if (B(CTL, 0x198) == 2) {
                B(CTL, 0x1B4) |= 8;
            } else {
                B(CTL, 0x1B4) |= 1;
            }
            D_800CC2B0 = 1;
        }
        if (recurse != 0) {
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            anim = 0xC6;
            if ((s32)F(obj, 0x28) != 0) {
                B(CTL, 0x11A) = 0;
            }
            break;
        }
        if (!(*(u16 *)D_800CC6A4 & 0x2000) && (H(CTL, 0x88) & 0x2000) && H(obj, 0x84) != 0xC4 && H(CTL, 0x19E) == 0) {
            blend = 0.0f;
            anim = 0xC7;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            H(CTL, 0x19E) = 0x32;
            break;
        }
        if ((*(u16 *)D_800CC6A4 & 0x2000) && H(obj, 0x84) != 0xC4) {
            B(obj, 0x89) = 0;
            B(obj, 0x8A) = 8;
            B(obj, 0x83) = 8;
            if (H(obj, 0x84) != 0xC7) {
                anim = 0x10A;
            }
            break;
        }
        anim = player_try_begin_action(obj, 0xC6, 1, 0, held);
        break;

    case 0x23: /* 15069620: anims 0x163 / 0x164 / 0x165 / 0x166 / 0x167 / 0x26E, shot count ctl +0x199 */
        if (kind != B(CTL, 0x78)) {
            anim = player_try_begin_action(obj, 0x163, 1, kind, held);
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            obj_setup_undo(obj, 0x16);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (B(CTL, 0x197) != 0 && B(CTL, 0x11A) == 2) {
            B(obj, 0x8A) = 10;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 10;
            if (H(CTL, 0x19E) == 0 && ((*(u16 *)D_800CC6A4 & 0x2000) || (H(CTL, 0x88) & 0x2000))) {
                B(CTL, 0x1B4) |= 1;
                D_800CC2B0 = 1;
            }
            if (H(obj, 0x84) == 0x163) {
                break;
            }
            if (B(CTL, 0x199) >= 6 || ((held & 0x8000) && H(obj, 0x84) != 0x26E)) {
                if (F(obj, 0x28) == 0.0f) {
                    B(obj, 0x89) = 0xFF;
                    B(obj, 0x83) = 0xFF;
                    H(CTL, 0x19E) = 0x96;
                    anim = 0x26E;
                    B(CTL, 0x199) = 0;
                }
                break;
            }
            if (!(*(u16 *)D_800CC6A4 & 0x2000) && (H(CTL, 0x88) & 0x2000) && H(obj, 0x84) == 0x165 &&
                H(CTL, 0x19E) == 0) {
                B(CTL, 0x1B4) |= 2;
                D_800CC2B0 = 1;
                blend = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                B(CTL, 0x199)++;
                anim = 0x167;
                H(CTL, 0x19E) = 0x19;
                break;
            }
            if (H(obj, 0x84) != 0x167) {
                anim = 0x165;
            }
            break;
        }
        B(obj, 0x8A) = 0x14;
        if (H(obj, 0x84) != 0x163 &&
            (B(CTL, 0x199) >= 6 || ((held & 0x8000) && H(obj, 0x84) != 0x26E))) {
            if (F(obj, 0x28) == 0.0f) {
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                H(CTL, 0x19E) = 0x96;
                anim = 0x26E;
                B(CTL, 0x199) = 0;
            }
            break;
        }
        if ((held & 0x2000) && H(obj, 0x84) != 0x163 && H(obj, 0x84) != 0x166 && H(CTL, 0x19E) == 0) {
            blend = 0.0f;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x199)++;
            anim = 0x166;
            H(CTL, 0x19E) = 0x19;
            break;
        }
        anim = player_try_begin_action(obj, 0x164, 1, 0, held);
        if (anim == 0x163) {
            B(CTL, 0x199) = 0;
        }
        break;

    case 0x17: { /* 15069924: anim 0x8E, turn to the level point D_800D34B8[ctl +0x7A] (0x34 bytes) */
        s32 ok = 1;
        anim = 999;
        if (!(held & 0x4000) || !(height <= 0.0f)) {
            break;
        }
        if (B(CTL, 0x7A) != 0) {
            f32 d = math_angle_diff_deg(F(D_800D34B8 + B(CTL, 0x7A) * 0x34, 0x10), F(obj, 0x40));
            if (W(D_800D34B8 + B(CTL, 0x7A) * 0x34, 0x18) != 0 && (d < -90.0f || 90.0f < d)) {
                ok = 0;
            }
        }
        if (!ok) {
            break;
        }
        B(obj, 0x89) = 0xFF;
        B(obj, 0x83) = 0xFF;
        B(CTL, 0x78) = 0x17;
        anim = 0x8E;
        {
            /* IDO f32 -> u32: values <= -1 give 0xFFFFFFFF (kept explicit: the plain cast traps on wasm) */
            f32 a = F(D_800D34B8 + B(CTL, 0x7A) * 0x34, 0x10) * 182.04445f; /* D_80099DBC */
            u32 u = (a <= -1.0f) ? 0xFFFFFFFF : (u32)a;
            H(obj, 0x76) = u - 0x4000;
        }
        break;
    }

    case 0x1A: /* 15069ADC: anims 0x12C / 0x12E / 0x358 / 0x142 */
        done = 1;
        anim = 999;
        if (kind != B(CTL, 0x78)) {
            if (!(held & 0x4000) || !(height <= 0.0f)) {
                break;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x8A) = 0xFF;
            B(obj, 0x83) = 0xFF;
            F(obj, 0x3C) = 0.0f;
            anim = 0x12C;
            B(CTL, 0x78) = kind;
            hint_box_open(0);
            break;
        }
        if (stunned != 0) {
            hint_box_close();
            B(CTL, 0x78) = 0;
            break;
        }
        if (hint_box_is_closed() != 0) {
            if (D_800D1940 == 0x42) {
                B(CTL, 0x78) = 0;
                anim = 0x358;
                D_800D2E60[D_800D1940 >> 3] |= 1 << (D_800D1940 & 7);
            } else {
                anim = 0x12E;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            break;
        }
        if (H(obj, 0x84) == 0x12C || !(D_800BEB30[g_cur_obj_index] & 0x8000)) {
            break;
        }
        if ((D_800D1958[0] & 0x20) && mp3_stream_get_state() != 0) {
            break;
        }
        anim = 0x142;
        break;

    case 0x2A: /* 15069C3C: anim 0x26F, random shout through face_anim_start */
        done = 1;
        anim = 999;
        if (kind != B(CTL, 0x78)) {
            if (!(height <= 0.0f) || B(obj, 0x110) != 0 || B(obj, 0x8A) != 0) {
                break;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x8A) = 0xFF;
            B(obj, 0x83) = 0xFF;
            F(obj, 0x3C) = 0.0f;
            B(CTL, 0x78) = kind;
            anim = 0x26F;
            B(obj, 0x276) = 6;
            H(obj, 0x282) = 100;
            H(obj, 0x278) = 0;
            B(obj, 0x284) = 0;
            hint_box_open(1);
            break;
        }
        if (stunned != 0) {
            hint_box_close();
            B(CTL, 0x78) = 0;
            break;
        }
        if (hint_box_is_closed() != 0) {
            B(CTL, 0x78) = 0;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0;
            face_anim_reset_default(obj);
            break;
        }
        {
            s32 shouts[2]; /* sp+0xB0: copy of D_800864A0 */
            shouts[0] = D_800864A0[0];
            shouts[1] = D_800864A0[1];
            H(obj, 0x282) = 100;
            if (((s8 *)obj)[0x284] == 0) {
                H(obj, 0x278) += g_frame_ticks;
                if ((u32)random_int() % 100 + 150 < H(obj, 0x278)) {
                    s32 r = random_int();
                    face_anim_start(obj, shouts[r & 1], 1, (u32)random_int() % 150 + 0x15E, 0);
                    H(obj, 0x278) = 0;
                    B(obj, 0x284) = 1;
                }
            } else if (B(obj, 0x70) == B(obj, 0x6F)) {
                B(obj, 0x284) = 0;
            }
        }
        B(obj, 0x89) = 10;
        B(obj, 0x8A) = 10;
        B(obj, 0x83) = 10;
        break;

    case 0x1B: { /* 15069E18: carry the other player (obj +0x65) */
        u8 *other = (u8 *)g_objects + (B(obj, 0x65) - 1) * 0x32C; /* spAC */
        s32 grab = 0;  /* sp94 */
        s32 hold;      /* spA4 */
        s32 mode;      /* a1 */
        s32 grabAnim;  /* s3 */
        s32 carryAnim; /* s1 */
        s32 mode2;     /* a2 */
        B(CTL, 0x78) = 0x1B;
        B(obj, 0x8A) = 0x14;
        if (D_800BE616 == 0 || B(obj, 0x65) != 0) {
            clearItem = 0;
        }
        anim = 999;
        if (H(CTL, 0x19E) != 0) {
            break;
        }
        if (B(other, 4) == 0x23) {
            hold = 0x10; mode = 0xD; grabAnim = 0x15; carryAnim = 0xA; mode2 = 0xC;
        } else {
            hold = 0xB; mode = 4; grabAnim = 0xC; carryAnim = 1; mode2 = 0;
        }
        if (*(u16 *)D_800CC6A4 & 0x2000) {
            if (mode != B(other, 0x232)) {
                actor_sound2_stop((struct127 *)other);
                actor_sound_stop((struct127 *)other);
            }
            B(other, 0x232) = mode;
            W(other, 0x218) = 0;
            B(CTL, 0x199) = 1;
            if (carryAnim != H(other, 0x84) || (D_eu_800C3E78 != 0 && mode2 != 0)) {
                gunfire_burst_spawn((struct127 *)other, obj, 0, carryAnim);
                actor_sound2_stop((struct127 *)other);
                if (B(obj, 4) == 0x80 && (random_int() & 3) == 0) {
                    u16 v = sound_pick_variant(0x57C, 6); /* voice id: the asm masks it to u16 */
                    sfx_emitter_start(v, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)sfx_cb_follow_object_anim, obj,
                                  (s32)D_80099A90, 0, 0);
                }
            }
            if (g_frame_ticks < SH(CTL, 0x24)) {
                SH(CTL, 0x24) -= g_frame_ticks;
            } else {
                grab = grabAnim;
                actor_sound_stop((struct127 *)other);
            }
        } else if (D_eu_800C3E78 != 0 && mode2 != B(other, 0x232) && mode2 != 0) {
            B(other, 0x232) = mode2;
            W(other, 0x218) = 0;
        } else if (B(CTL, 0x199) == 1) {
            B(CTL, 0x199) = 0;
            if (sfx_emitter_find_by_callback((s32)sfx_cb_delayed_play_2d, -1, -1) == -1) {
                sfx_emitter_start((u32)random_int() % 3 + 0x618, POSARGS(obj), 0x7D00, 0x1F4, 0xC8, (s32)sfx_cb_delayed_play_2d,
                              (void *)0x19, 0, 0x300, 0);
            }
        }
        if (held & 0x4000) {
            grab = hold;
            actor_sound2_stop((struct127 *)other);
            actor_sound_stop((struct127 *)other);
        }
        if (grab != 0) {
            SH(CTL, 0x24) = 0x1F4;
            H(CTL, 0x19E) = 0x7D;
            sfx_emitter_start((u32)random_int() % 3 + 0x618, POSARGS(obj), 0x7D00, 0x1F4, 0xC8, (s32)sfx_cb_delayed_play_2d,
                          (void *)0x19, 0, 0x300, 0);
            B(other, 0x232) = grab;
            W(other, 0x218) = 0;
        }
        break;
    }

    case 0x26: { /* 1506A27C: anims 0x175/0x176 (start) 0x16B/0x16C (end), item 0x2C / 0x64, state ctl +0x19B */
        s32 animStart, animEnd, sub, snd;
        if (B(obj, 4) == 0x75 || B(obj, 4) == 0xB1) {
            animStart = 0x176; animEnd = 0x16B; sub = 0x64; snd = 0x11;
        } else {
            animStart = 0x175; animEnd = 0x16C; sub = 0x2C; snd = 0x12;
        }
        if (stunned != 0) {
            if (kind != B(CTL, 0x78) && B(CTL, 0x19B) != 4) {
                break;
            }
            if (attachment_find_by_slot(obj, sub, 0) != 0 || B(CTL, 0x19B) == 4) {
                obj_setup_undo(obj, sub);
                g_cur_obj_cmd = (snd & 0xFFFF) | 0x10000;
                objev_spawn_helper_object();
                if (B(CTL, 0x19A) != 0) {
                    B(CTL, 0x19A)--;
                }
            }
            B(CTL, 0x19B) = 0;
            B(CTL, 0x11A) = 0;
            break;
        }
        player_aim_turn_update((u8 *)obj, buttons, 0x10);
        if (B(CTL, 0x19B) == 1) {
            if (kind == B(CTL, 0x78)) {
                break;
            }
            B(CTL, 0x78) = kind;
            B(CTL, 0x11A) = 1;
            B(obj, 0x89) = 0x1E;
            B(obj, 0x8A) = 0x1E;
            B(obj, 0x83) = 0x1E;
            B(CTL, 0x19B) = 2;
            H(CTL, 0x19C) = 0xC8;
            anim = animStart;
            SH(CTL, 0x1AA)++;
        } else if (B(CTL, 0x19B) == 2) {
            if (!(D_800CC6B0 & 4) && !(H(obj, 0x2F8) & 0x10)) {
                B(CTL, 0x19B) = 3;
            }
            if (g_frame_ticks < H(CTL, 0x19C)) {
                H(CTL, 0x19C) -= g_frame_ticks;
                break;
            }
            B(CTL, 0x19B) = 0;
            B(CTL, 0x78) = 0;
            B(obj, 0x125) = 0;
            obj_detonate_attachment(obj, 1);
        } else if (B(CTL, 0x19B) == 3) {
            if (!(height <= 0.0f) || H(obj, 0x84) == animStart) {
                break;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x19B) = 4;
            B(CTL, 0x78) = 0;
            B(CTL, 0x11A) = 3;
            anim = animEnd;
            if (B(CTL, 0x19A) != 0) {
                B(CTL, 0x19A)--;
            }
        }
        break;
    }

    case 0x3A: { /* 1506A4E4: throwable item 0x89 (0xBA in level 0x3F), anims 0x1F9 / 0x1FC, state ctl +0x19B */
        s32 item = (g_level_id == 0x3F) ? 0xBA : 0x89; /* sp7C */
        u8 *o;                                          /* sp80 */
        if (stunned != 0) {
            if (kind != B(CTL, 0x78)) {
                break;
            }
            o = (u8 *)obj_find_held(obj, item);
            if (o != NULL) {
                B(o, 0x65) = 0;
                F(o, 0x24) = 4.0f;
                F(o, 0x20) = 0.0f;
                F(o, 0x3C) = 0.0f;
            }
            B(CTL, 0x19B) = 0;
            B(CTL, 0x78) = 0;
            B(CTL, 0x11A) = 0;
            break;
        }
        player_aim_turn_update((u8 *)obj, buttons, 0x10);
        if (B(CTL, 0x19B) == 5) {
            if (kind == B(CTL, 0x78)) {
                break;
            }
            o = (u8 *)obj_setup_run(obj, (item == 0x89) ? 0x86 : 0x9F, 1.0f, 0);
            if (o == NULL) {
                B(CTL, 0x19B) = 0;
                break;
            }
            B(CTL, 0x78) = kind;
            B(CTL, 0x11A) = 1;
            anim = 0x1F9;
            B(obj, 0x89) = 0x1E;
            B(obj, 0x8A) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x19B) = 6;
            B(o, 0x125) = 0xFF;
            obj_set_scale((struct127 *)o, 1.0f, 1.0f);
            W(o, 0x2E4) = 200;
            W(o, 0x2E8) = 200;
            B(o, 0x124) = g_cur_obj_index + 1;
            W(o, 0xF8) = 0x401807;
            obj_start_anim((struct127 *)o, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            char_fx_glow_spawn((s32)o);
        } else if (B(CTL, 0x19B) == 6) {
            if (!(D_800CC6B0 & 4)) {
                B(CTL, 0x19B) = 7;
            }
        } else if (B(CTL, 0x19B) == 7) {
            if (!(height <= 0.0f) || H(obj, 0x84) == 0x1F9) {
                break;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x19B) = 0;
            B(CTL, 0x78) = 0;
            B(CTL, 0x11A) = 0;
            anim = 0x1FC;
            if (B(CTL, 0x19A) != 0) {
                B(CTL, 0x19A)--;
            }
            SH(CTL, 0x1AA)++;
            o = (u8 *)obj_find_held(obj, item);
            if (o != NULL) {
                f32 x, y, z; /* sp74, sp70, sp6C */
                f32 fwd = (f32)(200 - W(o, 0x2E4)) * 210.0f / 200.0f + 40.0f;
                s16 ang = 0x1555;
                B(o, 0x65) = 0;
                if (B(CTL, 0x198) != 0) {
                    ang = (30.0f - F(CTL, 0x170)) * 182.04445f; /* D_80099DC0 */
                }
                vec_from_yaw_pitch(ang, fwd, 0.0f, &x, &y, &z);
                F(o, 0x20) = -y;
                F(o, 0x24) = 4.0f;
                F(o, 0x3C) = x;
                {
                    u16 yaw = H(obj, 0x7A) - SH(CTL, 0x12);
                    H(o, 0x7A) = yaw;
                    H(o, 0x76) = yaw;
                }
            }
        }
        break;
    }

    case 0x3E: /* 1506A840: timer ctl +0x12C -> obj +0xAA */
        if (B(obj, 0x128) != 0) {
            break;
        }
        if (B(obj, 0x83) == 0) {
            B(obj, 0x83) = 1;
        }
        if (H(CTL, 0x12C) < g_frame_ticks) {
            B(obj, 0xAA) = 0x4B;
            H(CTL, 0x12C) = 0;
        } else {
            H(CTL, 0x12C) -= g_frame_ticks;
            B(obj, 0xAA) = 0x96;
        }
        break;

    default:
        break;
    }
    /* common tail (1506A89C) */
    if (recurse != 0 || stunned != 0) {
        H(CTL, 0x72) = 0;
        if (stunned != 0) {
            done = 1;
            anim = 0;
            if (clearItem != 0) {
                B(CTL, 0x78) = 0;
            }
        } else {
            B(CTL, 0x75) = 0;
            B(CTL, 0x78) = 0;
            if (B(CTL, 0x11A) != 3) {
                B(CTL, 0x11A) = 0;
            }
        }
    }
    if (anim != 0 && anim != 999 && noAnim == 0) {
        obj_start_anim(obj, anim, speed, blend, f148, 0.0f, 0);
    }
    if (setFlag58 != 0) {
        B(CTL, 0x58) = 1;
    }
    if (sound != 0) {
        obj_sfx_play(sound, obj);
    }
    return done ? 1000 : anim;
}
#undef B
#undef H
#undef SH
#undef W
#undef F
#undef CTL
#undef POSARGS
