#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 attached_particle_spawn(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern f32 g_weapon_b_spark_end_pt[]; /* was D_800A23B0 */
s32 tracer_spawn(s32 *, s32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
s32 weapon_b_muzzle_effects(struct127 *, u8, s32, s32 *, s32 *);
/* was func_150FE320 */
s32 weapon_b_fire(s32 arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused local moves the unnamed f32 spill temps down (frame layout)
    s32 spA8[3];
    s32 sp9C[3];
    s32 sp90[3];
    s32 sp84[3];

    if (arg0 == 0) {
        return 0;
    }
    obj_get_aim_vectors(arg0, (s32) sp84, (s32) spA8, 0, 0.0f);
    weapon_b_muzzle_effects(arg0, arg1, arg2, sp9C, sp90);
    return tracer_spawn(sp90, sp84, 0, 0, 0, 0, 300.0f, 0.0033333334f, (random_float() * 10.0f) + 25.0f, (random_float() * 200.0f) + 600.0f, 50.0f, (random_int() % 56U) + 0xC8, arg0, 1, 1, 0, 0xFF, 1, 1, 0, 0x23, 0.0f, 0xFF, -1, 0, (s32) arg1, arg2);
}

const u32 rodata_12C0B0_FE49C[] = { 0x00000000, 0xC1E00000, 0x41C00000, 0x00000000, 0x00000000, 0x41C00000, 0x00000000, 0xC31B0000, 0x41D80000, 0x00000000, 0x41200000, 0x41D80000, 0x00000000, 0xC3520000, 0x41D80000 }; /* was D_800A23B0 */ /* was D_800A2398 */ // g_weapon_b_muzzle_pts = [6], D_800A23A4 = [9], g_weapon_b_spark_end_pt = [12]
void weapon_b_shell_sparks(struct127 *, s32, u8, s32);
s32 mtx_transform_points(u8 **, struct17 **, s32, s32);
void object_effect_between(struct127 *, struct17 *, struct17 *, s32);
void muzzle_light_small_spawn(struct17 *, u8, s32);
void weapon_b_rumble(u8 *);
extern u8 g_weapon_b_bone; /* was D_80088F34 */

/* was func_150FE49C */
s32 weapon_b_muzzle_effects(struct127 *arg0, u8 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    struct17 pos;
    struct17 pos2;
    u8 *tbl[2];
    struct17 *out[2];

    if (arg0 != NULL) {
        if (arg0->unk1D4 != 0) {
            tbl[0] = g_weapon_b_muzzle_pts;
            tbl[1] = g_weapon_b_muzzle_pts + 0xC;
            out[0] = &pos;
            out[1] = &pos2;
            mtx_transform_points(tbl, out, (s32) arg0->unk1D4 + (g_weapon_b_bone << 6), 2);
        } else {
            pos.unk0 = *(f32 *)((u8 *)arg0 + 0x14);
            pos.unk4 = *(f32 *)((u8 *)arg0 + 0x18) + 70.0f;
            pos.unk8 = *(f32 *)((u8 *)arg0 + 0x1C);
            pos2 = pos;
        }
        object_effect_between(arg0, &pos, &pos2, 0x23);
        muzzle_light_small_spawn(&pos, arg1, arg2);
        weapon_b_shell_sparks(arg0, (s32) &pos, arg1, arg2);
        weapon_b_rumble((u8 *) arg0);
        if (arg3 != NULL) {
            *(struct17 *)arg3 = pos;
        }
        if (arg4 != NULL) {
            *(struct17 *)arg4 = pos2;
        }
    }
}

/* was func_150FEB84 */
void weapon_b_shell_sparks(struct127 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    f32 sp60[2];
    u8 sp5F;

    if ((arg0->unk1D4 != NULL) && ((arg0->unk74 & 0xF) != 0xF)) {
        sp60[1] = (random_float() * 2) + 3.7099998f; // 0x406D70A3 (3.71f would round to ...A4)
        sp60[0] = (random_float() * 15.0f) + 35.0f;
        if ((arg0->unk31C != NULL) && (arg0->unk31C->unk197 != 0) && (arg0->camera != NULL)) {
            sp5F = (~(1 << arg0->camera->unk23D)) & 0xFFFFu;
        } else {
            sp5F = 0xFF;
        }
        attached_particle_spawn(arg0, g_weapon_b_bone, g_weapon_b_muzzle_pts, (s32 *)g_weapon_b_spark_end_pt, sp60, (random_int() % 3U) + 4, (random_int() % 56U) + 0xC8, (random_float() * 301.0f) + 500.0f, arg1, (s32) sp5F, 0, -1, (s32) arg2, arg3);
    }
}

/* was func_150FED14 */
void weapon_b_bone_effect(s32 arg0, s32 arg1, s32 arg2) {
    obj_bone_point_or_pos(arg0, arg2, g_weapon_b_muzzle_pts, g_weapon_b_bone, 0.0f);
}

/* was func_150FED54 */
void weapon_b_rumble(u8 *arg0) {
    s8 sp18[8];
    if (*(s32 *)(arg0 + 0x318) != 0) {
        sp18[0] = 1;
        *(s16 *)(sp18 + 2) = ((u32)random_int() % 13) + 0x14;
        sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];
        random_int();
        sp18[4] = 8;
        sp18[6] = -1;
        rumble_request(sp18, 0, 0xFF, 1);
    }
}
