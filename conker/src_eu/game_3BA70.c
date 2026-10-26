#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void fx_alloc_d88750(void);
extern s32 g_mist_puff_handles; /* was D_800D9CF0 */
extern s8 g_event_effect_flag; /* was D_800D9D40 */
extern s8 g_level_flag_9d41; /* was D_800D9D41 */
extern s8 g_level_flag_9d48; /* was D_800D9D48 */
extern s8 g_level_flag_9d49; /* was D_800D9D49 */
extern s32 g_level_bytes_9d4a; /* was D_800D9D4A */
extern s8 g_level_flag_9d58; /* was D_800D9D58 */
extern s8 g_level_flag_9d59; /* was D_800D9D59 */
extern s32 g_level_bytes_9d5a; /* was D_800D9D5A */
extern s32 g_level_bytes_9d66_end; /* was D_800D9D66 */
extern s32 g_level_part_fades; /* was D_800D9D70 */
extern s32 g_level_reset_block_end; /* was D_800E0D94 */

/* was func_1500E5C0 */
void level_objects_reset_state(void) {
    s32 *var_v0_2;
    s32 *var_v1;
    u8 *var_v0;

    fx_alloc_d88750();
    obj_holder_refs_init();
    level_init_nop_15012770();
    var_v0 = &g_attach_fx_asset_refs;
    do {
        var_v0 += 4;
        (*(s8 *)((u8 *)var_v0 + -3)) = 0;
        (*(s8 *)((u8 *)var_v0 + -2)) = 0;
        (*(s8 *)((u8 *)var_v0 + -1)) = 0;
        (*(s8 *)((u8 *)var_v0 + -4)) = 0;
    } while ((s32)var_v0 != (s32)&g_level_reset_block_end);
    g_level_flag_9d41 = 0;
    g_event_effect_flag = 0;
    g_level_flag_9d48 = 0;
    g_level_flag_9d58 = 0;
    g_level_flag_9d49 = 0;
    var_v0_2 = &g_level_bytes_9d5a;
    var_v1 = &g_level_bytes_9d4a;
    g_level_flag_9d59 = 0;
    do {
        var_v0_2 = (s32 *)((u8 *)var_v0_2 + (4));
        (*(s8 *)((u8 *)var_v1 + 1)) = 0;
        (*(s8 *)((u8 *)var_v0_2 + -3)) = 0;
        (*(s8 *)((u8 *)var_v1 + 2)) = 0;
        (*(s8 *)((u8 *)var_v0_2 + -2)) = 0;
        (*(s8 *)((u8 *)var_v1 + 3)) = 0;
        (*(s8 *)((u8 *)var_v0_2 + -1)) = 0;
        var_v1 = (s32 *)((u8 *)var_v1 + (4));
        (*(s8 *)((u8 *)var_v1 + -4)) = 0;
        (*(s8 *)((u8 *)var_v0_2 + -4)) = 0;
    } while (var_v0_2 != &g_level_bytes_9d66_end);
    g_cs_overlay_cmd = 0;
    g_cs_overlay_tint = 0;
    (*(s32 *)((u8 *)(&g_mist_puff_handles) + 0)) = 0;
    (*(s32 *)((u8 *)(&g_mist_puff_handles) + 4)) = 0;
    (*(s32 *)((u8 *)(&g_mist_puff_handles) + 8)) = 0;
    (*(s32 *)((u8 *)(&g_mist_puff_handles) + 0xC)) = 0;
    g_shooting_star_obj = NULL;
    bzero(g_sky_segment_on, 5);
    (*(s8 *)((u8 *)(&g_level_part_fades) + 2)) = 0;
    (*(s8 *)((u8 *)(&g_level_part_fades) + 1)) = 0;
    (*(s8 *)((u8 *)(&g_level_part_fades) + 0)) = 0;
    g_water_effect_started = 0;
    (*(struct134 **)((u8 *)g_view_sparkle_spots + 0)) = NULL;
    (*(s32 *)((u8 *)g_view_sparkle_spots + 4)) = 0;
    (*(s32 *)((u8 *)g_view_sparkle_spots + 8)) = 0;
    g_level_scroll_handles = NULL;
    g_storm_thunder_flag = 0;
}
/* was func_1500E70C */
void level_hook_level_2b(s32 arg0) {
    if (arg0 == 0x2B) {
        level_reset_d9aa0_sfx();
    }
}

extern u8 g_fx_lod_shift_players; /* was D_800DCE50 */
extern f32 g_fx_lod_scale_players; /* was D_800DCE54 */
extern s8 g_fx_lod_shift_chars; /* was D_800DCE58 */
extern f32 g_fx_lod_scale_chars; /* was D_800DCE5C */

/* was func_1500E738 */
void level_set_lod_shifts(void) {
    switch (g_last_player_index) {
    case 0:
        g_fx_lod_shift_players = 0;
        g_fx_lod_scale_players = 1.0f;
        break;
    case 1:
        g_fx_lod_shift_players = 1;
        g_fx_lod_scale_players = 0.5f;
        break;
    case 2:
    case 3:
        g_fx_lod_shift_players = 2;
        g_fx_lod_scale_players = 0.25f;
        break;
    }
    switch (g_player_count) {
    case 2:
        g_fx_lod_shift_chars = 1;
        g_fx_lod_scale_chars = 0.5f;
        return;
    case 3:
    case 4:
        g_fx_lod_shift_chars = 2;
        g_fx_lod_scale_chars = 0.25f;
        return;
    case 5:
    case 6:
    case 7:
    case 8:
        g_fx_lod_shift_chars = 3;
        g_fx_lod_scale_chars = 0.125f;
        return;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        g_fx_lod_shift_chars = 4;
        g_fx_lod_scale_chars = 0.0625f;
        return;
    case 1:
    default:
        g_fx_lod_shift_chars = 0;
        g_fx_lod_scale_chars = 1.0f;
        return;
    }
}

/* was func_1500E890 */
void level_obj_init_area_points(void) {
    area_points_reset();
    area_points_alloc(0);
    area_points_alloc(1);
}

void area_drift_emitter_create(void *arg0, u8 arg1);
extern s32 g_level_dl_tinted_extra; /* was D_800B1214 */

/* was func_1500E8C0 */
void level_obj_init_drift_scene(void) {
    struct {
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s16 u78;
        s16 u7A;
        f32 u7C;
        f32 u80;
        s16 u84;
        s16 u86;
        s32 u88;
        s32 u8C;
    } sp;
    s16 var_v0;

    level_dl_add_texture_scroll(*g_level_part_dls, g_level_scroll_tex_a, 0, -1, 0, 0, 0, -6);
    level_dl_add_texture_scroll(g_level_dl_tinted_extra, g_level_scroll_tex_a, 0, -1, 0, 1, 0, -6);
    sp.u68 = 0.21428572f;
    sp.u70 = 5.0f;
    sp.u74 = 6.0f;
    sp.u60 = 8.0f;
    sp.u64 = 7.0f;
    sp.u6C = 0.0f;
    sp.u88 = 3;
    sp.u8C = 2;
    sp.u40 = 0x34;
    sp.u42 = 0x12;
    sp.u44 = -0x28;
    sp.u46 = 0xF;
    sp.u78 = 0x9B;
    sp.u7A = 0x64;
    sp.u84 = 0x29;
    sp.u86 = 0x29;
    sp.u50 = 400.0f;
    sp.u54 = 0.0f;
    sp.u58 = 0.0f;
    sp.u5C = 900.0f - 400.0f;
    sp.u7C = 0.6f;
    sp.u80 = 0.39999998f;
    sp.u48 = 800.0f;
    sp.u4C = -3000.0f;
    area_drift_emitter_create(&sp.u40, 1);
    if (g_level_id == 6) {
        var_v0 = 0x34;
    } else {
        var_v0 = 7;
    }
    sfx_emitter_start(0x61FU, var_v0, 0, 0, 0x2EE0, 0x3E8U, 0x190, (s32) sfx_cb_keep_until_silent, NULL, 0, 0x48, 0);
}
// NON-MATCHING: fair bit to figure out
// void level_obj_init_drift_scene(void) {
//     struct145 tmp;
//     s32 phi_v0;
//
//     level_dl_add_texture_scroll(g_level_part_dls[0], g_level_scroll_tex_a, 0, -1, 0, 0, 0, -6);
//     level_dl_add_texture_scroll(g_level_part_dls[1], g_level_scroll_tex_a, 0, -1, 0, 1, 0, -6);
//     tmp.unk28 = D_80096210; // 0.2142857164144516
//     tmp.unk30 = 5.0f;
//     tmp.unk34 = 6.0f;
//     tmp.unk20 = 8.0f;
//     tmp.unk24 = 7.0f;
//     tmp.unk14 = 0.0f;
//     tmp.unk18 = 0.0f;
//     tmp.unk2C = 0.0f;
//     tmp.unk48 = 3;
//     tmp.unk4C = 2;
//     tmp.unk0 = 0x34;
//     tmp.unk2 = 0x12;
//     tmp.unk4 = -0x28;
//     tmp.unk6 = 0xF;
//     tmp.unk38 = 0x9B;
//     tmp.unk3A = 0x64;
//     tmp.unk44 = 0x29;
//     tmp.unk46 = 0x29;
//     tmp.unk10 = 400.0f;
//     tmp.unk1C = 900.0f - 400.0f;
//     tmp.unk3C = D_80096214; // 0.6000000238418579
//     tmp.unk40 = D_80096218;
//     tmp.unkC = D_8009621C;
//     tmp.unk8 = 800.0f;
//     func_15189900(&tmp, 1);
//     if (g_level_id == 6) {
//         phi_v0 = 52;
//     } else {
//         phi_v0 = 7;
//     }
//     sfx_emitter_start(1567, (s16)phi_v0, 0, 0, 12000, 1000, 400, sfx_cb_keep_until_silent, 0, 0, 72, 0);
// }

/* was func_1500EAA0 */
void level_obj_init_tex_scroll(void) {
    level_dl_add_texture_scroll(g_level_part_dls[0], g_level_scroll_tex_b, 0, -1, 0, 0, 0, -8);
    level_dl_add_texture_scroll(g_level_part_dls[1], g_level_scroll_tex_b, 0, -1, 0, 1, 0, -8);
}
