#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15007A70 */
void level_start_game(s16 arg0, s16 arg1, s16 arg2) {

    D_800BE9B4 = 2;
    select_menu_reset();
    D_800BE9F0 = D_800BE9F4 = arg2;

    warp_requests_reset(D_800DD2C0);
    cutscene_clear_pending();
    obj_flagged_select_reset();
    level_lights_init(arg0, arg1);

    mp_set_mode_for_level(D_80087280[D_800D2138], arg2);
    render_set_detail_level();
    level_state_init();
    rail_state_clear();
    level_music_stop_all();
    D_800BE938 = 1;
    D_800D18A8 = 0;
    D_800BE9ED = 0;
}

// requires jump table
#ifdef NON_MATCHING
// Level loader (hand C from the asm, P13). Runs once per level change: picks the music/ambience id for the
// level (tlb_remap_game_segment), resets the per-level systems, allocates the two DL buffers (gfx_alloc_dl_buffers), arms the
// controller-read timer (cont_arm_read_timer), initialises every player (camera_raise_timer), every live object
// (trigger_zones_update_object) and commits the level id (D_800BE9F4 = D_800BE9F0).
extern s32 D_8003E724;
extern u8 D_800BEA39;
extern u8 D_800BEA3A;
extern u8 D_800BEE2C;
extern s32 D_800BEE08;
extern s32 D_800BE804;
extern u8 D_800E0FC9;
extern u8 D_800E1001;
extern s8 D_eu_800E0E30;
void tlb_remap_game_segment(s32 arg0);
void heap_free_tags_1_to_4(void);
void sound_level_init(s32 arg0);
void audio_mixer_reset_modes(void);
void mp3_voice_stop(s32 arg0);
void texture_scroll_clear(void);
void collision_set_step_size(s32 arg0);
void level_load_header(s32 arg0);
void collision_build_quadtrees(void);
void collision_noop(s32 arg0);
void breakable_slots_clear(void);
void level_matrix_arenas_alloc(void);
void attachment_list_reset(void);
void joint_chain_reset_mask_init(void);
void level_reset_globals(void);
void cutscene_reset_state(s32 arg0);
void cutscene_start_pending(void);
void zap_bolt_table_clear(void);
void player_morph_cache_clear(void);
void flare_nodes_level_init(s32 arg0);
void ambient_state_reset(void);
void level_clear_dd410(void);
void records_set_tint_180_60_60(void);
void level_globals_reset(void);
void level_lights_stub(s16 arg0);
void player_stat_modify(s16, s16, s32);
void camera_raise_timer(struct108 *arg0, s32 arg1);
void framebuffer_fill_color(s32 arg0, s32 arg1, s32 arg2);
void level_start_music(void);
s32 level_setup_screen_projection(s32);
void level_setup_sky_backdrop(s32 arg0);
void level_load_models(s32 arg0);
void collision_build_level_tris(s32 arg0);
void world_objects_load(s32 arg0, s32 arg1);
void world_object_cache_selected(void);
void world_objects_level_start(s32 arg0);
void vertex_anchor_alloc_players(void);
void camera_level_init(s32 arg0, s32 arg1);
void effect_lists_clear(s32 arg0);
void effect_run_init_hooks(s32 arg0);
void view_zoom_state_reset(void);
void level_lights_reset(void);
void level_hotspots_setup_all(void);
void anim_mesh_slots_reset(void);
void debris_counts_reset(void);
void level_objects_init(s32 arg0);
void level_hook_level_2b(s32 arg0);
void level_set_lod_shifts(void);
void clear_dfc00_table(void);
void hotspots_start_all(void);
void glyph_count_reset(void);
void gfx_alloc_dl_buffers(void);
void records_table_reset(void);
void level_load_ptr_table_3c(s32 arg0);
void level_clear_d18c0(void);
void start_points_load(s32 arg0);
void level_setup_load(s32 arg0);
void level_table_load(s32 arg0);
void camera_view_state_init(void);
void level_apply_flag_entries(void);
void zones_load(s32 arg0);
void viewports_init(s32 arg0, s32 arg1);
void camera_update_dir_vector_thunk(s32 player); /* P68: forwards the player index to camera_update_dir_vector */
void cont_arm_read_timer(void);
void rumble_stop_all(void);
void gfx_load_ucode(void);
void asset_system_stub_a(void);
void asset_system_stub_b(s32 arg0);
void collision_reset_counter(void);
void level_restart_at_start_point(s32 arg0, s32 arg1);
s32 checkpoint_get_restart_index(s32 arg0);
void lipsync_reset(void);
void rail_nodes_load(s32 arg0);
void event_list_run_phase(s32 arg0);
s32 level_is_game_over_level(void);
void game_over_apply_pending(void);
void trigger_zones_update_object(struct127 *arg0);
void camera_set_screen_ortho(s32 arg0);
void scenery_door_groups_reset(void);
void fog_init_from_level(s32 arg0);
void hud_lens_start_zoom_in(s32 arg0);
void light_fx_clear_all(void);
void lives_popup_spawn(s32 arg0, s32 arg1);
void rumble_records_clear_all(void);
void menu_clear_flag_ebc(void);
s8 mp_human_player_count(void);
void menu_char_slots_clear(void);

/* was func_15007B3C */
void level_load(void) {
    s32 sp30;   /* in/out for checkpoint_get_restart_index: the save slot / profile byte */
    s32 sp2C;
    s32 level;
    s32 snd;
    s32 i;
    s32 n;
    u8 *obj;

    if (D_800BE9B4 == 0) {
        D_800BE9B4 = 1;
    }
    heap_free_tags_1_to_4();
    level_load_header((s32)D_800BE9F4);

    level = (s32)D_800BE9F4;
    switch (level) {
    case 0x1A: case 0x24: case 0x2B: case 0x2D: case 0x30: case 0x33: case 0x34: case 0x3F:
        snd = (level == 0x24) ? 0xF3 : 0x103;
        if (level == 0x33) snd -= 8;
        if (level == 0x3F) snd -= 8;
        if (level == 0x34) snd += 8;
        break;
    case 0x13:
        snd = 0xEB;
        if (!(((u8 *)D_800D2E4C)[0x11] & 4)) {
            snd = ((s8 *)D_800B0DF0)[0x11] + 0xEB;
        }
        break;
    default:
        snd = ((s8 *)D_800B0DF0)[0x11] + 0xEB;
        break;
    }
    tlb_remap_game_segment(snd);

    D_eu_800E0E30 = 0;
    level_set_lod_shifts();
    debris_counts_reset();
    D_800DCE20 = 0;
    D_800E0D50 = 0;
    zap_bolt_table_clear();
    D_8003E724 = 1;
    sp30 = D_800DD2C0;
    sp2C = checkpoint_get_restart_index((s32)&sp30);
    if (D_800E0B94 == 2) {
        sp30 = D_800E1001;
    }
    D_800BE9F8 = D_800BE9F0;
    D_800BE9F0 = (s32)D_800BE9F4;
    level_lights_reset();
    light_fx_clear_all();
    D_800BEA39 = 0;
    D_800BEA3A = 0;
    D_800BEE2C = 0;
    level_reset_globals();
    if (D_800BE9ED != 0) {
        framebuffer_fill_color(0xFF, 0xFF, 0xFF);
        D_800BE9ED = 0;
    } else {
        framebuffer_fill_color(0, 0, 0);
    }
    if (D_800BE616 == 0 && !(((u8 *)D_800D2E4C)[0x18] & 1)) {
        D_800D2456 = 3;
        D_800D2457 = 3;
        player_stat_modify(0, 5, 3);
    }
    collision_set_step_size(D_800BE9F0);
    rumble_stop_all();
    gfx_alloc_dl_buffers();
    records_table_reset();
    zones_load(D_800BE9F0);
    level_globals_reset();
    viewports_init(D_800BEE08, 1);
    clear_dfc00_table();
    view_zoom_state_reset();
    texture_scroll_clear();
    level_clear_dd410();
    ambient_state_reset();
    collision_reset_counter();
    level_clear_d18c0();
    attachment_list_reset();
    level_matrix_arenas_alloc();
    level_apply_flag_entries();
    fog_init_from_level(D_800BE9F0);
    asset_system_stub_a();
    asset_system_stub_b(D_800BE9F0);
    level_load_models(D_800BE9F0);
    world_objects_load(D_800BE9F0, 1);
    world_object_cache_selected();
    scenery_door_groups_reset();
    collision_build_level_tris(D_800BE9F0);
    collision_build_quadtrees();
    collision_noop(D_800BE9F0);
    level_table_load(D_800BE9F0);
    world_objects_level_start(D_800BE9F0);
    cutscene_reset_state(D_800BE9F0);
    level_start_music();
    sound_level_init(D_800BE9F0);
    mp3_voice_stop(D_800BE9F0);
    audio_mixer_reset_modes();
    cont_arm_read_timer();
    effect_lists_clear(1);
    effect_run_init_hooks(1);
    start_points_load(D_800BE9F0);
    level_setup_load(D_800BE9F0);
    camera_level_init(D_800BE9F0, sp30);
    records_set_tint_180_60_60();
    level_setup_screen_projection(D_800BE9F0);
    camera_set_screen_ortho(0);
    for (i = 0; i <= D_80082FA0; i++) {
        camera_raise_timer((struct108 *)((u8 *)D_800DBFF0 + i * 0x9A0), 1);
    }
    level_hook_level_2b(D_800BE9F0);
    level_load_ptr_table_3c(D_800BE9F0);
    level_hotspots_setup_all();
    level_setup_sky_backdrop(D_800BE9F0);
    if (D_800BE9F0 == 0x1D) {
        menu_char_slots_clear();
    }
    level_objects_init(D_800BE9F0);
    flare_nodes_level_init(D_800BE9F0);
    rail_nodes_load(D_800BE9F0);
    player_morph_cache_clear();
    camera_update_dir_vector_thunk(0); /* the asm passes 0 */
    lipsync_reset();
    D_800BE9E4 = 2;
    glyph_count_reset();
    joint_chain_reset_mask_init();
    level_lights_stub(D_800D2340);
    anim_mesh_slots_reset();
    breakable_slots_clear();
    vertex_anchor_alloc_players();
    cutscene_start_pending();
    if (D_800BE616 == 0) {
        player_stat_modify(0, 9, D_800BE804);
    }
    if (level_is_game_over_level() != 0) {
        D_800BE800 = sp30;
    }
    D_800D2E43 = 1;
    event_list_run_phase(4);
    event_list_run_phase(1);
    hotspots_start_all();
    if (sp2C != 0) {
        level_restart_at_start_point(sp30, sp2C - 1);
    }
    menu_clear_flag_ebc();
    if (D_800E0FC9 != 0 || D_800DDE38 == 2) {
        if (D_800C35EA != 1 && D_800DDE38 != 1) {
            n = mp_human_player_count();
            for (i = 0; i < n; i++) {
                hud_lens_start_zoom_in(i);
            }
        }
        D_800E0FC9 = 0;
    }
    camera_view_state_init();
    gfx_load_ucode();
    obj = (u8 *)D_800CC2D0;
    do {
        if (*(s32 *)obj != 0 && obj[0x127] != 0xFF) {
            trigger_zones_update_object((struct127 *)obj);
        }
        obj += 0x32C;
    } while (obj != (u8 *)&D_800D121C);
    if (D_800D18A8 != 0 && D_800BE9F0 != 0x22) {
        D_800D18A8 = 0;
        lives_popup_spawn(0xFF, 1);
    }
    game_over_apply_pending();
    D_800BE9F4 = (u16 *)D_800BE9F0;
    rumble_records_clear_all();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_34F20/level_load.s")
#endif
/* was func_150081E4 */
void level_reset_globals(void) {
    s32 i;

    D_800D3668 = 0;
    D_800CBE00 = 0;
    D_800DDD64 = 0;

    for (i = 0; i < 2; i++)
    {
        D_800DF7C8[i] = 0;
    }

    D_800D245C = 0;
    D_800D2548 = 0;
}


/* was func_15008230 */
void cutscene_clear_pending(void) {
    D_800C35C4 = (u8)0;
    D_800C3C88 = (u8)0;
}

/* was func_15008248 */
void cutscene_reset_state(s32 arg0) {
    s32 i;

    D_800C3638 = 0;
    D_800C3671 = 0;
    D_800C3670 = 0;
    cutscene_slot_reset(0);
    cutscene_slot_reset(1);
    D_800C3663 = 0;

    for (i = 0; i < 3; i++)
    {
        D_800C3CA0[i].unk0 = 0;
        D_800C3CA0[i].unkC = 0;
    }

    D_800C3681 = 0;
    D_800C3682 = 0;
    D_800C3683 = 0;
}

/* was func_150082CC */
void cutscene_start_pending(void) {
    s32 tmp = D_800C35C4 - 1;

    if (D_800C35C4 != 0) {
        if (D_800C35C5 == 0) {
            D_800C35EA = 2;
        }
        D_800C35C4 = 0;
        cutscene_scene_load(D_800BE9F0, tmp, 0, D_800C3C90, D_800C3C94);
    }
}
