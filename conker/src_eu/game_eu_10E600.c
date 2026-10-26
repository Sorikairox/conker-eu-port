#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    f32 height;     // ground height under the probe
    s16 tri[9];     // hit triangle (passed on to fx_scorch_decal_spawn)
    s32 unk18;
    u8 flags;       // bit 0: ground found
    u8 unk1D;
    u8 pad1E[2];
    s32 unk20;
} HitInfo_150E0DF0;
void hitinfo_from_obj_floor(HitInfo_150E0DF0 *out, u8 *obj);
s32 collision_floor_probe(u8 *pos, u16 arg1, f32 min_y, u8 *out);
void fx_scorch_decal_spawn(f32 arg0, u8 arg1, s32 arg2, u8 *arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, s32 argB);
void cam_shake_all_players(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);
s32 smoke_cloud_spawn(u8 *pos, u8 arg1, s32 arg2);
void explosion_light_spawn(u8 *arg0, u8 arg1, s32 arg2);
void fx_debris_emitter_spawn(f32 *arg0, s16 arg1, u8 arg2, s32 arg3);
s32 spark_shower_spawn(f32 *pos, f32 time, f32 size, f32 bright, f32 flat, u8 arg5, s32 arg6);
s32 object_hit_effects(u8 *obj, u8 smoke, u8 splats, u8 debris, u8 finish, u8 fewer, u8 arg6, s32 arg7);
s32 object_effects_at(f32 *pos, f32 *dir, struct127 *obj, struct127 *model, s32 arg4, s32 sound1, s32 sound2, s32 flags);
/* object_explode: big explosion at an object (obj NULL: nothing). Two explosion sounds (0x2BB / 0x2BA, not when
 * g_cutscene_slot_state == 1); probes the ground below (from 100 above to 200 below the blast point, 20 above the object) and,
 * when found, leaves a scorch decal there (fx_scorch_decal_spawn); shock wave / flash / smoke / sparks effects
 * (rumble_all_players_at, cam_shake_all_players, smoke_cloud_spawn, explosion_light_spawn), debris at the ground point (or the blast point),
 * a light (spark_shower_spawn), the object's hit effects (object_hit_effects) and the blast damage (object_effects_at, sounds
 * 0x16 / 0x15). `owner` / `arg2` are passed through to the effects. */
/* was func_150E0DF0 */
void object_explode(u8 *obj, u8 owner, s32 arg2) {
    HitInfo_150E0DF0 hit;
    f32 probe[3];
    f32 ground[3];
    f32 pos[3];
    u8 landed;
    f32 r;
    u32 a, b;

    if (obj == NULL) {
        return;
    }
    if (g_cutscene_slot_state != 1) {
        actor_sound_play_untracked(0x2BB, (struct127 *) obj, 0x7FFF, 1000, 2000);
        actor_sound_play_untracked(0x2BA, (struct127 *) obj, 0x7FFF, 1000, 2000);
    }
    pos[0] = *(f32 *) (obj + 0x14);
    pos[1] = *(f32 *) (obj + 0x18) + 20.0f;
    pos[2] = *(f32 *) (obj + 0x1C);
    landed = FALSE;
    probe[0] = pos[0];
    probe[1] = pos[1] + 100.0f;
    probe[2] = pos[2];
    hitinfo_from_obj_floor(&hit, obj);
    if (collision_floor_probe((u8 *) probe, 0, pos[1] - 200.0f, (u8 *) &hit) != 0 && (hit.flags & 1)) {
        ground[0] = probe[0];
        ground[1] = hit.height;
        ground[2] = probe[2];
        landed = TRUE;
        r = random_float();
        a = random_int();
        b = random_int();
        fx_scorch_decal_spawn(r * 125.0f + 204.0f, a % 101U + 155, (s32) hit.tri, (u8 *) ground, b % 302U + 500, 0, 1, 0, 0, 0,
                      owner, 0);
    }
    rumble_all_players_at((struct17 *) pos, 506.0f, 1013.0f, 0.0009871668880805373f, 15, 20, owner, arg2);
    cam_shake_all_players((u8 *) pos, 506.0f, 1013.0f, 0.0009871668880805373f, 5, owner, arg2);
    smoke_cloud_spawn((u8 *) pos, owner, arg2);
    explosion_light_spawn((u8 *) pos, owner, arg2);
    fx_debris_emitter_spawn(landed ? ground : pos, (s16) ((u32) random_int() % 62U + 120), owner, arg2);
    r = random_float();
    a = random_int();
    spark_shower_spawn(pos, r * 4.0f + 12.0f, 1.6409999132156372f, (f32) (a % 56U + 200), 0.0f, owner, arg2);
    object_hit_effects(obj, 1, 1, 1, 1, 0, owner, arg2);
    object_effects_at(pos, NULL, (struct127 *) obj, (struct127 *) obj, 0, 0x16, 0x15, 0);
}

void cutscene_actor_apply_track(struct127 *, s32, s32);
s32 obj_check_death(struct127 *);
void obj_walk_update(struct127 *);
void obj_stun_update(struct127 *); /* P209: the asm reads only a0 and returns nothing */
s32 obj_turn_towards(struct127 *, s32, u16);
extern u16 g_obj0_yaw; /* was D_800CC766 */

/* was func_150E1160 */
void enemy_update_alert_move(struct127 *arg0) {
    u8 temp_t0;
    u8 temp_v0;
    u8 var_v0;

    arg0->unkB0 = 0xF;
    arg0->unk80 = 0xA;
    if (arg0->unk87 != 0) {
        var_v0 = arg0->unk83;
        if ((s32) var_v0 < 0x64) {
            temp_t0 = var_v0 + g_frame_delta;
            arg0->unk83 = temp_t0;
            var_v0 = temp_t0 & 0xFF;
        }
        if ((s32) var_v0 >= 5) {
            temp_v0 = arg0->unk251;
            if (temp_v0 != 3) {
                arg0->unk218 = NULL;
                arg0->unk232 = 4;
                arg0->unk78 = g_obj0_yaw;
                if (temp_v0 == 2) {
                    arg0->unk232 = 2;
                }
            }
        }
    } else {
        if ((s32) arg0->unk83 >= 0x3D) {
            g_cur_obj_cmd = -0xFDFECD;
            g_cur_obj = g_objects;
            objev_sound_alt_300_1800();
            g_cur_obj = arg0;
        }
        arg0->unk83 = 0;
    }
    if (arg0->unk232 == 4) {
        if (arg0->unk83 == 0) {
            arg0->unk78 = arg0->unk76;
        }
        obj_turn_towards(arg0, 3, arg0->unk78);
    }
    arg0->unk87 = 0;
    if (arg0->stunned == 0) {
        obj_walk_update(arg0);  // P50: one argument (the asm leaves 0x3D4C0000 in a1, unused)
    } else {
        obj_stun_update(arg0);
    }
    arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
    obj_physics_step(arg0);
    arg0->unkBC = arg0->x_position - arg0->old_x_position;
    arg0->unk148 = arg0->z_position - arg0->old_z_position;
    if (obj_check_death(arg0) == 0) {
        cutscene_actor_apply_track(arg0, 0, -1);
    }
}