#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void scenery_platform_drift_update(s32, s32, s32, f32);
/* was func_150C7D70 */
void scenery_drift_by_level_flag(s32 arg0) {
    if (!((*(u8 *)((u8 *)g_save_progress_bits + 0xA)) & 8)) {
        if (!(g_world_objs->pad70[3] & 4)) {
            scenery_platform_drift_update(arg0, 1, 0x353, 1000.0f);
            return;
        }
        scenery_platform_drift_update(arg0, 1, 0x43, 400.0f);
    }
}

void scenery_spin_z_update(u8 *);
/* was func_150C7DE0 */
void scenery_spin_z_level_neg(u8 *arg0) {
    u8 *p;
    if (!(arg0[0x73] & 4)) {
        p = (u8 *)g_world_objs;
        p += 0x1E1;  // fakematch: keeps the dead addiu (p += K+1; p--;)
        p--;  // fakematch: pairs with p += K+1
        *(s32 *)(arg0 + 0x3C) = -(*(s32 *)(p + 0x3C) & 0xFFFF0000) & 0xFFFF0000;
        scenery_spin_z_update(arg0);
    }
}

/* was func_150C7E30 */
void scenery_spin_z_level(u8 *arg0) {
    u8 *p;
    p = (u8 *)g_world_objs;
    p += 0x1E1;  // fakematch: keeps the dead addiu (p += K+1; p--;)
    p--;  // fakematch: pairs with p += K+1
    *(s32 *)(arg0 + 0x3C) = *(s32 *)(p + 0x3C) & 0xFFFF0000;
    scenery_spin_z_update(arg0);
}

void scenery_start_pending_anim(u8 *obj);
// obj_shade_from_level: P237. Object callback (same family as scenery_spin_z_level_neg / scenery_spin_z_level): runs scenery_start_pending_anim(obj),
// then, unless the object's +0x73 bit 2 is set, gives its model record (+0x7C, when there is one) the shade byte
// +0x13 = the level block's (g_world_objs) s16 +0x21C / 16.
/* was func_150C7E68 */
void obj_shade_from_level(u8 *obj) {
    u8 *rec;

    scenery_start_pending_anim(obj);
    if (!(obj[0x73] & 4)) {
        rec = *(u8 **) (obj + 0x7C);
        if (rec != NULL) {
            rec[0x13] = *(s16 *) ((u8 *) g_world_objs + 0x21C) >> 4;
        }
    }
}

void music_play_song(s32, s32, s32);
void music_stop_song(s32, s32);
f32 math_cos_u8(s32);
void puff_drift_spawn(s32, s16, s32, s16, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80088B94;

/* was func_150C7EBC */
void zone_ambience_update(s32 arg0) {
    u8 sp4B;
    s32 sp44;                                       /* compiler-managed */
    f32 temp_f18;
    f32 temp_f2;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_3;
    s32 var_a1;
    struct108 *temp_v0;
    u32 temp_s1_2;
    u8 temp_v0_2;

    sp44 = arg0 * 0x9A0;
    temp_v0 = &g_player_views[arg0];
    var_a1 = (s32) temp_v0->unk2FC;
    temp_s0 = (s32) temp_v0->unk2F8 + 0x972;
    temp_s1 = (s32) temp_v0->unk300 - 0x6EF;
    if (((var_a1 - 0x9C4) >= -0xC7) && (((temp_s0 * temp_s0) + (temp_s1 * temp_s1)) < 0x15F900)) {
        if (D_80088B94 == 0) {
            music_play_song(0x5F, 0xF, 6);
            music_stop_song(0x10, 4);
            D_80088B94 = 1;
            var_a1 = (s32) (*(f32 *)((u8 *)((g_player_views + sp44)) + 0x2FC));
        }
    } else if (D_80088B94 != 0) {
        music_play_song(0xF, 0x5F, 4);
        music_play_song(0x10, 0, 3);
        D_80088B94 = 0;
        var_a1 = (s32) (*(f32 *)((u8 *)((g_player_views + sp44)) + 0x2FC));
    }
    if (((var_a1 - 0x62F) < 0) && (((temp_s0 * temp_s0) + (temp_s1 * temp_s1)) < 0xC5C10) && ((u32) (random_int() & 0xFFFF) < 0x2000U)) {
        temp_s1_2 = random_int() % 900U;
        temp_v0_2 = random_int();
        sp4B = temp_v0_2;
        temp_f2 = (f32) temp_s1_2;
        temp_f18 = math_cos_u8(temp_v0_2 & 0xFF) * temp_f2;
        sp44 = temp_f2;
        temp_s1_3 = (s32) ((math_sin_u8(sp4B) * temp_f2) + 1775.0f);
        puff_drift_spawn((s32) ((f32) ((random_int() & 0xFFFF) * 2) * 0.000015258789f) & 0xFF, (s16) (s32) (temp_f18 + -2418.0f), 0x62F, (s16) temp_s1_3, 7, 0x4B0, 0x25, 0xA, 0x1E, 3, 8);
    }
}
u8 *world_record_find(u8 id); /* P119: one argument (world_record_find reads only the id) */

/* was func_150C8190 */
void scenery_dl_set_angle_coord(u8 *arg0) {
    s32 *sp18;
    s32 *temp_a1_2;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    s8 *temp_a1;

    var_v1 = (*(s32 *)((u8 *)arg0 + 0x7C));
    if (var_v1 == 0) {
        temp_a1 = (*(s8 **)((u8 *)arg0 + 0x1C));
        var_v0 = 0;
        if (*temp_a1 != -0xE) {
            do {
                var_v0 += 1;
            } while (*((var_v0 * 8) + temp_a1) != -0xE);
        }
        (*(s32 *)((u8 *)arg0 + 0x7C)) = var_v0;
        var_v1 = var_v0;
    }
    temp_a1_2 = (*(s8 **)((u8 *)arg0 + 0x1C)) + (var_v1 * 8);
    sp18 = temp_a1_2;
    var_v1_2 = -0x29D - (*(s16 *)((u8 *)(world_record_find((*(s32 *)((u8 *)arg0 + 0x3C)) & 0xFF)) + 0x12));
    if ((*(s32 *)((u8 *)arg0 + 0x3C)) & 0x8000) {
        var_v1_2 = 0x344 - var_v1_2;
    }
    if (var_v1_2 < 0) {
        do {
            var_v1_2 += 0x400;
        } while (var_v1_2 < 0);
    }
    if (var_v1_2 >= 0x400) {
        do {
            var_v1_2 -= 0x400;
        } while (var_v1_2 >= 0x400);
    }
    temp_t0 = *temp_a1_2 & ~0xFFF;
    *temp_a1_2 = temp_t0;
    *temp_a1_2 = temp_t0 | var_v1_2;
}
/* was func_150C827C */
void scenery_follow_obj_0c(u8 *arg0) {
    struct127 *temp_v0;

    temp_v0 = obj_find_by_setup_id(0xC);
    (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) (temp_v0->x_position - 30.0f);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) (temp_v0->y_position + 50.0f);
    (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) (temp_v0->z_position + 30.0f);
}
