#include <ultra64.h>

#include "functions.h"
#include "variables.h"


s32 level_load_look_points(s32);
void ambient_sounds_load(void);
void ambient_emitters_build(void);
void level_objects_reset_state(void);
void camera_init_player_projections(void);
void level_vertex_colours_backup(void);
void level_clear_be570(void);
void level_set_lights_mode(u8);
void fog_init_from_level(s32);
void rain_init(void);
void shadow_settings_for_level(s32);
void texscroll_reset(void);
void game_os_pi_set_control(u32);
extern s32 g_level_obj_init_fns; /* was D_80083120 */
extern s8 g_arc_bolts_spawned; /* was D_80088F00 */
extern s8 g_level_obj_state_d834; /* was D_800DD834 */
extern s8 g_level_anim_frame; /* was D_800DD835 */
extern s8 g_level_anim_accum; /* was D_800DD836 */
extern s32 g_level_point_hit_cb; /* was D_800E0D64 */
extern s32 D_eu_800BE900;

/* was func_1500E470 */
void level_objects_init(s32 arg0) {
    u8 temp_v0;

    g_node_iter_depth = -1;
    bzero(g_node_iter_next, 0x18);
    g_level_obj_state_d834 = 0xFF;
    g_level_anim_frame = 0;
    g_level_anim_accum = 0;
    g_level_bullet_hit_cb = NULL;
    g_level_point_hit_cb = 0;
    g_world_obj_hit_cb = NULL;
    g_aim_hud_active = 0;
    g_arc_bolts_spawned = 0;
    D_eu_800BE900 = 0;
    g_level_proj_mode = level_get_proj_mode();
    camera_init_player_projections();
    game_os_pi_set_control(0x40);
    fog_init_from_level(arg0);
    level_load_look_points(arg0);
    level_vertex_colours_backup();
    texscroll_reset();
    level_load_stub();
    level_timed_queue_init();
    level_objects_reset_state();
    temp_v0 = g_level_header->unkA;
    if (temp_v0 != 0) {
        (*(s32 (**)())((u8 *)&g_level_obj_init_fns + (temp_v0 * 4)))();
    }
    ambient_sounds_reset(arg0);
    ambient_emitters_build();
    ambient_sounds_load();
    shadow_settings_for_level(arg0);
    rain_init();
    level_clear_be570();
    level_set_lights_mode(((g_save_progress_bits->unk4 & 0x80) == 0) & 0xFF);
}
// NON-MATCHING: damn nops, is this -g ?
// void level_objects_init(s32 arg0) {
//     u8 tmp;
//     D_800DD190 = -1;
//     bzero(&D_800DD198, 24);
//     D_800DD404 = 0xFF;
//     D_800DD405 = 0;
//     D_800DD406 = 0;
//     g_level_bullet_hit_cb = 0;
//     D_800E0934 = 0;
//     g_world_obj_hit_cb = 0;
//     D_8008CD00 = 0;
//     g_beam_free_fns = 0;
//     D_800BE4E0 = 0;
//     // is this handwritten?
//     g_level_proj_mode = level_get_proj_mode();
//     camera_init_player_projections();
//
//     func_151EF640(64);
//     func_151732E0(arg0);
//     level_load_look_points(arg0);
//     func_150127B0();
//
//     func_1519582C();
//     level_load_stub();
//     level_timed_queue_init();
//     level_objects_reset_state();
//
//     if (0) {};
//     if (g_level_header->unkA) {
//         D_80082D90[g_level_header->unkA]();
//     }
//     ambient_sounds_reset(arg0);
//     ambient_emitters_build();
//     ambient_sounds_load();
//     func_151872B0(arg0);
//     func_15178EB0();
//     level_clear_be570();
//
//     if (0) {};
//     tmp = (g_save_progress_bits->unk4 & 128) == 0;
//     level_set_lights_mode(tmp);
// }
