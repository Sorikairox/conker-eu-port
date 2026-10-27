#include <ultra64.h>
#include "functions.h"
#include "variables.h"
s32 weapon_a_muzzle_effects(struct127 *, u8, s32, s32 *, s32 *);
s32 tracer_spawn(s32 *, s32, s32 *, s32 *, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
/* was func_150FDDA0 */
s32 weapon_a_fire(s32 arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused local moves the unnamed f32 spill temps down (frame layout)
    s32 spB0[3];
    s32 spA4[3];
    s32 sp98[3];
    s32 sp8C[3];

    if (arg0 == 0) {
        return 0;
    }
    obj_get_aim_vectors(arg0, (s32) sp98, (s32) spB0, 0, 0.0f);
    weapon_a_muzzle_effects(arg0, arg1, arg2, spA4, sp8C);
    return tracer_spawn(sp8C, 0, sp8C, sp98, 0, 0, 300.0f, 0.0033333334f, (random_float() * 10.0f) + 25.0f, (random_float() * 201.0f) + 601.0f, 50.0f, (random_int() % 56U) + 0xC8, arg0, 1, 1, 0, 0xFF, 1, 1, 0, (g_level_id == 0x2B) ? 0x27 : 0x1A, 0.0f, 0xFF, -1, 0, (s32) arg1, arg2);
}

const u32 rodata_12BB30_FDF38[] = { 0x40E00000, 0xC3080000, 0x42340000, 0x40E00000, 0xC3290000, 0x424C0000, 0x40E00000, 0x42200000, 0x41500000 }; /* was D_800A234C */ /* was D_800A2340 */ // g_weapon_a_muzzle_pts = [0], g_weapon_a_spark_end_pt = [3], D_800A2358 = [6]
void weapon_a_shell_sparks(struct127 *, s32, u8, s32);
s32 mtx_transform_points(u8 **, struct17 **, s32, s32);
void object_effect_between(struct127 *, struct17 *, struct17 *, s32);
void muzzle_light_small_spawn(struct17 *, u8, s32);
void weapon_a_rumble(u8 *);
extern u8 g_weapon_a_bone; /* was D_80088F20 */

/* was func_150FDF38 */
s32 weapon_a_muzzle_effects(struct127 *arg0, u8 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    struct17 pos;
    struct17 pos2;
    u8 *tbl[2];
    struct17 *out[2];

    if (arg0 != NULL) {
        if (arg0->unk1D4 != 0) {
            tbl[0] = g_weapon_a_muzzle_pts;
            tbl[1] = g_weapon_a_muzzle_pts + 0x18;
            out[0] = &pos;
            out[1] = &pos2;
            mtx_transform_points(tbl, out, (s32) arg0->unk1D4 + (g_weapon_a_bone << 6), 2);
        } else {
            pos.unk0 = *(f32 *)((u8 *)arg0 + 0x14);
            pos.unk4 = *(f32 *)((u8 *)arg0 + 0x18) + 56.0f;
            pos.unk8 = *(f32 *)((u8 *)arg0 + 0x1C);
            pos2 = pos;
        }
        object_effect_between(arg0, &pos, &pos2, (g_level_id == 0x2B) ? 0x28 : 0x1E);
        muzzle_light_small_spawn(&pos, arg1, arg2);
        weapon_a_shell_sparks(arg0, (s32) &pos, arg1, arg2);
        weapon_a_rumble((u8 *) arg0);
        if (arg3 != NULL) {
            *(struct17 *)arg3 = pos;
        }
        if (arg4 != NULL) {
            *(struct17 *)arg4 = pos2;
        }
    }
}

s32 attached_particle_spawn(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern s32 g_weapon_a_spark_end_pt; /* was D_800A234C */

/* was func_150FE638 */
void weapon_a_shell_sparks(struct127 *arg0, s32 arg1, u8 arg2, s32 arg3)
{
  f32 sp60[2];
  u8 sp5F;
  if ((arg0->unk1D4 != 0) && ((arg0->unk74 & 0xF) != 0xF))
  {
    sp60[1] = (random_float() * 1.5f) + 2.0f;
    sp60[0] = (random_float() * 10.1f) + 2.06f;
    if (((arg0->unk31C != 0) && (arg0->unk31C->aim_state != 0)) && (arg0->camera != 0))
    {
      sp5F = (~(1 << arg0->camera->unk23D)) & 0xFFFFu;
    }
    else
    {
      sp5F = 0xFF;
    }

    attached_particle_spawn(arg0, g_weapon_a_bone, g_weapon_a_muzzle_pts, &g_weapon_a_spark_end_pt, sp60, (random_int() % 5U) + 6, (((u32) random_int()) % 101U) + 0x9B, (random_float() * 199.0f) + 501.0f, arg1, (s32) sp5F, 0, -1, (s32) arg2, arg3);
  }
}

/* was func_150FE7C8 */
void weapon_a_bone_effect(s32 arg0, s32 arg1, s32 arg2) {
    obj_bone_point_or_pos(arg0, arg2, &g_weapon_a_muzzle_pts, g_weapon_a_bone, 0.0f);
}

/* was func_150FE808 */
void weapon_a_rumble(u8 *arg0) {
    s8 sp18[8];
    if (*(s32 *)(arg0 + 0x318) != 0) {
        sp18[0] = 1;
        *(s16 *)(sp18 + 2) = ((u32)random_int() % 9) + 0xF;
        sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];
        sp18[4] = (random_int() & 3) + 3;
        sp18[6] = -1;
        rumble_request(sp18, 0, 0xFF, 1);
    }
}
