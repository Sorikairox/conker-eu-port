#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ultra64.h>

#include "structs.h"

extern f32 fabsf(f32);
#pragma intrinsic (fabsf)

/* matching */
void boot_entry_main(void);
void boot_idle_thread_main(s32 arg0);
void tlb_reset_and_flush_icache(void);
void game_thread_stop(void);
s32  init_printf_null_out(s32 arg0, s32 arg1, s32 arg2);
void func_1000349C(s32 arg0);
s32  init_stub_return_zero(void);
void mem_init_region_bounds(void);
void init_stub_noop(void);
void video_init_screen(void);
void heap_age_tagged_blocks(void);
void heap_free_tags_1_to_4(void);
void heap_update_largest_free(void);
void pi_init_dma_queues(void);
s32  rom_dma_read(s32 devAddr, void *dramAddr, u32 size, s32 arg3);
void rom_dma_wait_queued(void);
void sched_start_gfx_task(void);
void sched_try_swap_buffer(void);
void sched_swap_framebuffer(void);
void sched_add_client(OSPfs *pfs, OSMesgQueue *queue);
void sched_send_retrace_msg(void);
void prenmi_thread_start(void);
void prenmi_stub_noop(void);
void music_player_play(u8 arg0);
s32  music_player_get_state(u8 arg0);
void music_player_set_msg_queue(u8 arg0, s32 arg1);
void music_stub_noop3(s32 arg0, s32 arg1, s32 arg2);
void music_player_set_chan_flag17(u8 arg0, s32 arg1, u8 arg2);
void music_chan_mute(u8 arg0, s32 arg1);
void music_chan_unmute(u8 arg0, s32 arg1);
void music_chan_fade_volume(u8 arg0, u8 arg1, u8 arg2, s32 arg3);
void music_chan_set_cc41(u8 arg0, u8 arg1, u8 arg2);
void music_chan_set_pan(u8 arg0, u8 arg1, u8 arg2);
void music_chans_fade_volume(u8 arg0, s32 arg1, u8 arg2, s32 arg3);
void music_chan_set_volume(u8 arg0, u8 arg1, u8 arg2);
void music_chans_set_volume(u8 arg0, s32 arg1, u8 arg2);
void music_chans_set_muted(u8 arg0, s32 arg1, s32 arg2);
void music_chans_set_enabled(u8 idx, s32 mask, s32 enable);
u8   music_chan_get_volume(u8 idx, u8 chan);
void music_chans_set_cc92(u8 arg0, s32 arg1, s32 arg2);
void music_player_get_tempo(u8 arg0);
void music_player_set_voice_param(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4);
void music_player_set_master_gain(u8 arg0, f32 arg1, f32 arg2);
void music_player_set_volume(u8 arg0, s32 arg1);
void music_player_end_track(u8 arg0);
void music_player_stop(u8 arg0);
void audio_thread_stop(void);
s32  audio_dma_new(s32 *arg0);
void snd_cache_entry_unref(struct54 *arg0);
void snd_cache_entry_release(struct54 *arg0);
void snd_cache_entry_ref(struct54 *arg0);
s32  music_song_cb_pos_song4d(u32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4);
struct151 *music_find_song(s32 arg0);
s32  music_song_cb_duck_song16(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32  music_song_cb_level4_meter(s32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4);
s32  music_song_cb_start_song20(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32  music_song_cb_sync_level(s32 arg0, u8 arg1, s32 arg2, s32 arg3);
void music_players_set_fade_target(s32 arg0);
s32  music_step_toward(s32 arg0, s32 arg1, s32 arg2);
void music_song_set_paused(s32 arg0, s32 arg1);
s32  music_song_is_playing(s32 arg0);
void music_song_set_volume(s32 arg0, s32 arg1);
s32  music_song_set_marker(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32  music_song_set_chans_cc92(s32 arg0, s32 arg1, s32 arg2);
void music_set_b070_mode(s32 arg0);
s32  music_get_event_request(s32 *arg0, s32 *arg1);
u16  music_play_menu_song(s32 arg0);
s32  sfx_cb_ambient_random_chirp(struct04 *arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg6, s32 arg7, u16 *arg8);
s32  sfx_cb_fade_out(struct00 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32  sfx_cb_keep_until_silent(struct57 *arg0, struct57 *arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6);
void sound_level_init(s32 arg0);
s32  sound_voice_is_playing(u16 arg0);
s32  sound_voice_is_looping(u16 arg0);
void sound_voice_update_3d(u16 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
void sound_voice_update_pan(u16 arg0, s16 arg1, s16 arg2, s16 arg3);
void actor_sound_play_untracked_delay(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4, s32 arg5) ;
s32  actor_sound_is_playing(struct127 *arg0);
s32  actor_sound2_is_playing(struct127 *arg0);
void actor_sound_stop(struct127 *arg0);
void actor_sound2_stop(struct127 *arg0);
void actor_sounds_stop_loops(struct127 *arg0);
u16 sound_play_2d(s32 arg0, u16 arg1, u8 arg2, s16 arg3, u8 arg4);
void sound_voice_stop(u16 arg0);
void sound_voice_stop_deferred(u16 arg0);
s32  sound_stop_queue_push(s32 arg0, s32 arg1);
s32  sound_voice_get_id(u16 arg0);
void sound_level_hook_nop(s32 arg0);
void sound_set_pause_mute(s32 arg0);
void audio_mixer_request_mode(s32 *arg0);
void audio_mixer_set_override_mode(s32 arg0);
void audio_mixer_set_base_mode(s32 arg0);
void audio_mixer_reset_modes(void);
void mp3_id3_text_enqueue(s32 arg0, u8 *arg1, s32 arg2);
void mp3_voice_init(s32 arg0);
void mp3_voice_stop(s32 arg0);
void mp3_voice_play(s32 arg0, s32 arg1, s32 arg2);
s32 text_queue_read(s32 arg0, s32 arg1);
s32  mp3_voice_play_at_object(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
s32  mp3_voice_is_playing(void);
void _bnkfPatchBank(struct121 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_bnkf_patch_perc_inst(struct11 *arg0, s32 arg1);
void _bnkfPatchInst(struct11 *arg0, s32 arg1);
void n_bnkf_patch_sound(struct9 *arg0, s32 arg1, s32 arg2);
void _bnkfPatchWaveTable(struct12 *arg0, s32 arg1, s32 arg2);
f32  _depth2Cents(u8 arg0);
s32  audio_osc_init(s32 *arg0, f32 *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);
s32  audio_osc_update(struct124 *arg0, f32 *arg1);
void audio_osc_stop(s32 *arg0);
void audio_osc_pool_create(struct13 *arg0, s32 arg1);
void n_csp_set_bank(struct26 *arg0, s32 arg1);
s32  n_sndp_voice_handler(struct04 *arg0);
void n_sndp_free_state(struct31 *arg0);
void n_sndp_post_pitch_update(struct154 *arg0);
struct31 *n_sndp_alloc_state(s32 arg0, s16 arg1);
void n_sndp_release_state(struct31 *arg0);
s32  n_sndp_get_handle_state(struct31 **arg0);
void n_sndp_stop_sound(struct31 *arg0);
void n_sndp_stop_all(void);
void n_sndp_stop_all_looping(void);
void n_sndp_post_event(s32 arg0, s16 arg1, s32 arg2);
void audio_set_output_mode(u8 arg0);
void audio_set_bus_mix_type(s32 arg0, u32 arg1);
s32  func_10017A80(struct26 *arg0);
void n_csp_play(struct26 *arg0);
void n_csp_set_msg_queue(struct26 *arg0, s32 arg1);
void n_csp_set_chan_notify(struct26 *arg0, s32 arg1, u8 arg2);
void n_csp_reset_chan_levels(struct26 *arg0);
void n_csp_mute_chan(struct26 *arg0, s32 arg1);

void n_csp_set_chan_pan(struct26 *arg0, u8 arg1, u8 arg2);
void n_csp_set_fx_mix_offset_scale(struct26 *arg0, f32 arg1, f32 arg2);
void n_csp_set_chan_fx_bus(struct26 *arg0, u8 arg1, u8 arg2);
void n_csp_set_fx_param(struct26 *arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4);

void n_alInit(struct07 *arg0, s32 arg1);
void n_alClose(s32 arg0);
s32  _n_timeToSamplesNoRound(s32 micros);
s32  _n_timeToSamples(s32 micros);
f32  alCents2Ratio(s32 arg0);
void n_csp_cc_volume(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_pan(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_priority(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_bank_select(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_filter_amount(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_filter_key(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_voice_param17(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_fx_enable(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_fx_mix(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_fx_bus(struct26 *arg0, s32 arg1, s32 arg2, u32 arg3);
void n_csp_cc_voice_clip_bank(struct24 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_play_voice_clip(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_fade_rate(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_csp_cc_fade_level(struct26 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32  __n_vsDelta(struct07 *arg0, s32 arg1);
void func_1001B620(struct26 *arg0, s32 arg1);
void n_fx_calc_biquad_lowpass(f32 arg0, f32 arg1, f32 arg2, struct17 *arg3, struct17 *arg4);
void func_1001CD54(struct125 *arg0);
f32  audio_semitones_to_ratio(s32 arg0);
void func_1001D6E8(struct42 *arg0, s32 (*arg1)(s32 arg), struct15 *arg2);
s32  n_syn_get_aux_fx(s16 arg0);
s32  n_syn_get_aux_filter(s16 arg0);
void n_fx_set_param(s32 arg0, s16 arg1, s32 arg2);
void n_fx_filter_set_param(struct139 *arg0, s16 arg1, s32 *arg2);
// void func_1001E170(struct22 *arg0, s32 *w, f32 pitch, s16 vol, u8 pan, u8 fxmix, u8 arg6, f32 arg7, u8 arg8, s32 arg9);
// void n_csp_send_midi(struct26 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4);
s32  n_synth_aux_fx_new(s16 arg0, s32 arg1, s32 arg2);
f32  n_reverb_do_mod_func(f32 arg0[4][4], s32 arg1);
/* chunk0 */
void game_init_message_queues(void);
void level_music_stop_all(void);
void texture_scroll_clear(void);
void func_15001B08(void);
u16* quadtree_alloc_node(void);
void quadtree_build_area(s32 arg0, s16 *arg1, s16 *arg2);
void collision_build_reset(void);
void collision_begin_area(s32 arg0);
void collision_end_area(s32 arg0);
void collision_count_dl_tris(s32 arg0);
void collision_set_step_size(s32 arg0);
s32  xor_f0f0f0f0(s32 arg0);
void level_load_header(s32 arg0);
void level_stub_noop(void);
s32  texture_table_reset(void);
void collision_build_quadtrees(void);
s32  texture_table_find(s32 arg0);
void collision_noop(s32 arg0);
void collision_set_tri_flags_table(s32 arg0);
void world_objects_noop(void);
void breakable_slots_clear(void);
void level_matrix_arenas_alloc(void);
void attachment_list_reset(void);
void joint_chain_reset_mask_init(void);
void model_kind_tables_clear(void);
void obj_flagged_select_reset(void);
void camera_level_hook_dispatch(struct108 *arg0, s32 arg1);
void camera_level_hook01_setup(struct108 *arg0);
void camera_level_hook02_noop(s32 arg0);
void camera_level_hook03_noop(s32 arg0);
void camera_level_hook04_setup(struct108 *arg0);
void camera_level_hook05_noop(s32 arg0);
void camera_level_hook06_noop(s32 arg0);
void camera_level_hook07_send_events(s32 arg0);
void camera_level_hook08_setup(struct108 *arg0);
void camera_level_hook09_setup(struct108 *arg0);
void camera_level_hook10_setup(struct108 *arg0);
void camera_level_hook11_noop(s32 arg0);
void camera_level_hook12_setup(struct108 *arg0);
void camera_level_hook13_setup(struct108 *arg0);
void camera_level_hook15_setup(struct108 *arg0);
void camera_level_hook16_setup(struct108 *arg0);
void camera_level_hook17_setup(struct108 *arg0);
void camera_level_hook18_setup(struct108 *arg0);
void camera_level_hook19_setup(struct108 *arg0);
void camera_level_hook20_setup(struct108 *arg0);
void camera_level_hook21_setup(struct108 *arg0);
void camera_level_hook22_noop(s32 arg0);
void camera_level_hook23_setup(struct108 *arg0);
void camera_level_hook24_update(struct108 *arg0);
void camera_level_hook25_setup(struct108 *arg0);
void camera_level_hook26_setup(struct108 *arg0);
void controller_init_si_queue(void);
void save_game_defaults(void);
void controller_init_hook_noop(void);
void save_request_options_load(void);
void save_request_options_write(void);
void save_request_config_load(void);
void save_request_config_write(void);
void save_request_slot_load(s32 arg0);
void save_request_slot_write(s32 arg0);
void save_request_slot_erase(s32 arg0);
void game_bss_clear(void);
void level_start_game(s16 arg0, s16 arg1, s16 arg2);
void level_reset_globals(void);
void cutscene_clear_pending(void);
void cutscene_reset_state(s32 arg0);
void cutscene_start_pending(void);
void zap_bolt_table_clear(void);
void obj_holder_refs_init(void);
void level_timed_queue_init(void);
void level_timed_queue_create(void);
void level_load_stub(void);
void player_morph_cache_clear(void);
void area_points_reset(void);
void flare_nodes_level_init(s32 arg0);
void hotspot_fx_type01(s32 arg0, s32 arg1);
void hotspot_fx_type02(s32 arg0, s32 arg1);
void hotspot_fx_type07(s32 arg0, s32 arg1);
void hotspot_fx_type13(s32 arg0, s32 arg1);
void hotspot_fx_type14(s32 arg0, s32 arg1);
void hotspot_fx_type15(s32 arg0, s32 arg1);
void hotspot_fx_type16(s32 arg0, s32 arg1);
void hotspot_fx_type17(s32 arg0, s32 arg1);
void hotspot_fx_type18(s32 arg0, s32 arg1);
void hotspot_fx_type19(s32 arg0, s32 arg1);
void hotspot_fx_type20(s32 arg0, s32 arg1);
void hotspot_fx_type21(s32 arg0, s32 arg1);
void hotspot_fx_type22(s32 arg0, s32 arg1);
void hotspot_fx_type23(s32 arg0, s32 arg1);
void hotspot_fx_type28(s32 arg0, s32 arg1);
void hotspot_fx_type29(s32 arg0, s32 arg1);
void hotspot_fx_type76(s32 arg0, s32 arg1);
void hotspot_fx_type30(s32 arg0, s32 arg1);
void hotspot_fx_type33(s32 arg0, s32 arg1);
void hotspot_fx_type34(s32 arg0, s32 arg1);
void hotspot_fx_type35(s32 arg0, s32 arg1);
void hotspot_fx_type36(s32 arg0, s32 arg1);
void hotspot_fx_type37(s32 arg0, s32 arg1);
void hotspot_fx_type38(s32 arg0, s32 arg1);
void hotspot_fx_type39(s32 arg0, s32 arg1);
void hotspot_fx_type40(s32 arg0, s32 arg1);
void hotspot_fx_type41(s32 arg0, s32 arg1);
void hotspot_fx_type43(s32 arg0, s32 arg1);
void hotspot_fx_type44(s32 arg0, s32 arg1);
void hotspot_fx_type45(s32 arg0, s32 arg1);
void hotspot_fx_type46(s32 arg0, s32 arg1);
void hotspot_fx_type47(s32 arg0, s32 arg1);
void hotspot_fx_type48(s32 arg0, s32 arg1);
void hotspot_fx_type49(s32 arg0, s32 arg1);
void hotspot_fx_type50(s32 arg0, s32 arg1);
void hotspot_fx_type55(s32 arg0, s32 arg1);
void hotspot_fx_type58(s32 arg0, s32 arg1);
void hotspot_fx_type59(s32 arg0, s32 arg1);
void hotspot_fx_type60(s32 arg0, s32 arg1);
void hotspot_fx_type61(s32 arg0, s32 arg1);
void hotspot_fx_type62(s32 arg0, s32 arg1);
void hotspot_fx_type63(s32 arg0, s32 arg1);
void hotspot_fx_type64(s32 arg0, s32 arg1);
void hotspot_fx_type77(s32 arg0, s32 arg1);
void hotspot_fx_type65(s32 arg0, s32 arg1);
void hotspot_fx_type66(s32 arg0, s32 arg1);
void hotspot_fx_type67(s32 arg0, s32 arg1);
void hotspot_fx_type68(s32 arg0, s32 arg1);
void hotspot_fx_type78(s32 arg0, s32 arg1);
void hotspot_fx_type79(s32 arg0, s32 arg1);
void hotspot_fx_type86(s32 arg0, s32 arg1);
void hotspot_fx_type87_88(s32 arg0, s32 arg1);
void hotspot_fx_dispatch(s32 arg0, s32 arg1);
void ambient_fx_spawn_type2(s32 arg0);
void ambient_fx_dispatch(s32 arg0);
void ambient_sounds_reset(s32 arg0);
void ambient_timer_reset(s32 arg0);
void ambient_state_reset(void);

void level_setup_noop_eb20(void);
void level_fx_point_spawn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void level_setup_fx_points(void);
void level_setup_light_pipe_spray(void);
void effect_attach_obj_type45(struct127 *arg0, s32 arg1, s32 arg2);
void effect_track_obj_type46(struct16 *arg0);
void level_setup_scroll_fx_points(void);

void level_setup_tex_scroll_pos(void);
void level_setup_noop_102c0(void);
void level_obj_init_scroll_fx59(void);
void level_obj_init_two_vtx_lights(void);
void obj_spawn_effect_80(struct127 *arg0);
void level_obj_set_hit_activate_cb(void);
void level_obj_init_nop_150106a0(void);
void level_obj_set_target_hit_cb(void);
s32  level_obj_spawn_zone_effect(struct39 *arg0);
void level_obj_init_vertex_lights(void);
void level_obj_init_scroll_handles(void);
void level_obj_init_scroll_xy(void);
void level_obj_init_storm_sounds(void);
void level_obj_init_storm(void);
void level_obj_init_area_points_23(void);
void obj_spawn_effect_85(struct127 *arg0, u8 arg1, s32 arg2);
void level_fx_spawn_random_life(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void level_obj_init_lights_sfx77(void);
void level_clear_be500(void);
void level_reset_d9aa0_sfx(void);
void level_sfx_cooldown_reset(void);
void level_obj_init_scroll_e4(void);
void ambient_fx_spawn_type3(s32 arg0);
void ambient_fx_spawn_type5(s32 arg0);
void level_ground_emitter_spawn7(s32 arg0, s32 arg1);
u8   level_get_proj_mode(void);
void level_init_nop_15012770(void);
void level_clear_dd410(void);
s32  record_light_list_add(s32);
s32  record_dispatch_82f70(struct134 *arg0);
void records_set_tint_180_60_60(void);
void level_globals_reset(void);
void level_lights_init(s16 arg0, s16 arg1);
void render_set_detail_level(void);
void level_state_clear(void);
void level_state_init(void);
void frame_hook_nop_1501c860(void);
void frame_hook_nop_1501c870(void);

void dl_validate(void *arg0, u32 arg1);
s32  dlcheck_tri_invalid(u32 *arg0);
s32 dlcheck_dl_invalid(struct148 *arg0);
void text_queue_reset(void);
void text_set_flags(u8 arg0);
void text_set_scale(f32 arg0);
void text_set_box(s32 arg0, s32 arg1);
void text_set_pos(s16 arg0, s16 arg1);
void text_set_color(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
void ring_buffer_init(struct105 *arg0, s32 arg1, s32 arg2);
void mtx_build_rot_scale_trans(Mtx *m, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
void mtx_build_rot_trans(Mtx *m, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void mtxf_scale_set_trans(f32 mtx[4][4], f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6);
void vec_from_fixed_pos(vertex *arg0, struct113 *arg1);
void mtxf_translate_local(f32 arg0[4][4], f32 x, f32 y, f32 z);
void func_15047F00(f32 mtx[4][4], u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void func_15048134(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
f32  math_atan2f(f32 arg0, f32 arg1);
u16  math_acos_s16(s16 arg0);
s16  math_asin_s16(s16 arg0);
f32  math_acosf_lut(f32 arg0);
f32  math_asinf_lut(f32 arg0);
f32  math_angle_lerp_deg(f32 arg0, f32 arg1, f32 arg2);
void math_wrap_deg_360(f32 *arg0);
f32  math_asin_scaled(f32 arg0);
f32  math_asin_u8(f32 arg0);
f32 math_sin_u8(u8 arg0);
f32  math_angle_diff_deg(f32 arg0, f32 arg1);
s32  math_angle_diff_deg_int(s32 arg0, s32 arg1);
void obj_build_inverse_mtx(s32 arg0, s32 arg1);
void vec3_add(struct17 *arg0, struct17 *arg1, struct17 *arg2);
void vec3_sub(struct17 *arg0, struct17 *arg1, struct17 *arg2);
void vec3_diff(struct17 *arg0, struct17 *arg1, struct17 *arg2);
void vec3_scale(struct17 *arg0, f32 arg1, struct17 *arg2);
void vec3_normalize(struct17 *arg0, struct17 *arg1);
void vec3_dir_to(struct17 *arg0, struct17 *arg1, struct17 *arg2);
void quadtree_set_test_box(f32 arg0, f32 arg1, f32 arg2);
s32 math_mtx_box_in_frustum(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
f32  func_1504A5E0(f32 arg0);
s32  obj_coll_link_resolve_stub(s32 arg0, s32 arg1);
s32  walk_anim_cancel_special(void);
s32  walk_anim_land_id(void);
void ctl_decay_button_latches(struct127 *arg0);

void swim_exit_water(struct127 *arg0);
void obj_state_nop(s32 arg0);
void obj_state_remove_when_dead(struct127 *arg0);
void obj_roll_pitch_step(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3);
void obj_state_reset_idle(struct127 *arg0);
struct127 *obj_reset_link_state(s32 arg0, s32 arg1);
void obj_set_dead_fading(struct127 *arg0);
void obj_set_dead_still(struct127 *arg0);
void obj_state_dead_still(struct127 *arg0);
void obj_state_dead_fading(struct127 *arg0);
void player_state_shrink_death(struct127 *arg0);
void obj_leash_to_spawn(struct127 *arg0);
void obj_follow_water_level(struct127 *arg0);
s32  obj_in_spawn_radius(struct127 *arg0, s32 arg1);
void obj_set_gravity_band(struct127 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void obj_physics_step(struct127 *arg0);
void obj_blend_push_velocity(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3);
void obj_apply_level_current(struct127 *arg0);
void obj_attach_to_carrier(struct127 *arg0, s32 arg1);
f32  pad_stick_speed(struct49 *arg0);
u16  math_atan2_u16(f32 arg0, f32 arg1, s32 arg2);
f32  obj_dist_xz(struct127 *arg0, struct127 *arg1);
s16  obj_facing_angle_diff(struct127 *arg0, struct127 *arg1);
void obj_start_knockback(struct127 *arg0, u8 arg1);
f32  math_rotate_offset_deg(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4);

void obj_sfx_play_simple(s32 arg0, void *arg1);
void obj_fade_reset(struct127 *arg0);
void obj_model_reset(struct127 *arg0);
void obj_update_inner_extent_ratios(struct127 *arg0);
void obj_set_inner_extent_width(struct127 *arg0, f32 arg1);
void obj_set_inner_extent_height(struct127 *arg0, f32 arg1);
void obj_update_outer_extent_ratios(struct127 *arg0);
void obj_set_scale(struct127 *arg0, f32 arg1, f32 arg2);
void objev_anim_38(void);
void objev_anim_48(void);
void objev_anim_39(void);
void objev_nop_1506b070(void);
void objev_anim_d1_by_depth(void);
void objev_play_anim(s32 arg0, f32 arg1, f32 arg2);
void objev_anim_next(void);
void objev_anim_next_flagged(void);
void objev_anim_3c(void);
void objev_anim_54(void);
void objev_anim_f_allow_run(void);
void objev_release_if_player_link(void);
void objev_anim_3e(void);
void objev_nop_1506b368(void);
void objev_player_lose_life(void);
void objev_nop_1506b3b0(void);
void objev_pick_turn_to_player_wrap(void);
void objev_clear_21c(void);
void objev_hurt_or_die(void);
void objev_nop_1506b5a4(void);
void objev_nop_1506b5ac(void);
void objev_set_1cb(void);
void objev_set_1cb_b(void);
void objev_stop_anim(void);
void objev_random_idle_or_swim(void);
void objev_allow_run_pick_idle(void);
void objev_allow_run_idle(void);
void objev_anim_b5(void);
void objev_anim_b6(void);
void objev_reset_state_idle(void);
void objev_anim_de(void);
void objev_anim_bf(void);
void objev_anim_c5_allow_run(void);
void objev_anim_af(void);
void objev_clear_244(void);
void objev_sound_or_stop(s32 arg0, s32 arg1);
void objev_sound_alt_or_stop(s32 arg0, s32 arg1);
void objev_sound_hi_word_3(s32 arg0, s32 arg1);
void objev_sound_hi_word(s32 arg0, s32 arg1);
void objev_sound_hi_word_alt(s32 arg0, s32 arg1);
void objev_set_y_velocity(void);
void objev_jump_if_low(void);
void objev_set_gravity(void);
void objev_set_gravity_tenth(void);
void objev_allow_run(void);
void objev_set_target_speed(void);
void objev_set_disable_run(void);
void objev_set_d0_114(void);
void objev_sound_if_above_water(void);
void objev_stop_sound_alt(void);
void objev_stop_sound(void);
void objev_nop_1506d4ec(void);
void objev_anim_slow(void);
void objev_lose_life_cur_player(void);
void objev_clear_6e(void);
void objev_set_103(void);
void objev_nop_1506d950(void);
void objev_set_immune(void);
void objev_screen_effect_stop(void);
void objev_set_1890_update(void);
void objev_set_xz_velocity(void);
void objev_set_239(void);
void objev_link_nearby_object(void);
void objev_set_2e8(void);
void objev_set_2ec(void);
void objev_set_health(void);
void objev_nop_1506dcf8(void);
void objev_clear_flags_f8(void);
void objev_set_matrix_physics(void);
void objev_nop_1506ddb8(void);
void objev_level_screen_effect(void);
void objev_screen_effect_twice(void);
void objev_sound_300_1800(void);
void objev_sound_100_800(void);
void objev_sound_190_1300(void);
void objev_sound_300_3000(void);
void objev_sound_700_4000(void);
void objev_sound_3000_8000(void);
void objev_sound_hi_300_1800(void);
void objev_sound_hi_300_3000(void);
void objev_sound_if_grounded(void);
void objev_sound_if_not_playing(void);
void objev_sound_global_300_1800(void);
void objev_sound_alt_300_1800(void);
void objev_sound_alt_100_800(void);
void objev_sound_alt_190_1300(void);
void objev_sound_alt_300_3000(void);
void objev_sound_alt_700_4000(void);
void objev_sound_alt_3000_8000(void);
void objev_sound_alt_hi_300_3000(void);
void objev_hold_frame_airborne(void);
void objev_anim_set_flag_8000(void);
void objev_set_3a(void);
void objev_set_83_lock(void);
void objev_set_100(void);
void objev_unlock_a9(void);
void objev_set_21c(void);
void objev_set_flags_f4(void);
void objev_clear_flags_f4(void);
void objev_or_flags_f4(void);
void objev_or_flags_25c(void);
void objev_clear_flags_25c(void);
void objev_trail_set(void);
void objev_set_24e(void);
void objev_clear_282(void);
void objfx_bb760_unless_8c(s32 arg0);
void objfx_bcbbc(s32 arg0);
void objfx_ba4c0(s32 arg0);
void objfx_dust_50(s32 arg0);
void objfx_dust_default(s32 arg0);
void objfx_c1260_0(s32 arg0);
void objfx_c1260_1(s32 arg0);
void objfx_spray_0(s32 arg0);
void objfx_spray_1(s32 arg0);
void objfx_aeeb0(s32 arg0);
void objfx_197a7c(s32 arg0);
void objfx_19ef70(s32 arg0);
void objfx_gun_shot(s32 arg0);
void objfx_1a0a10_70(s32 arg0);
void objfx_1a0a10_40(s32 arg0);
void objfx_buddy_marker_clear(s32 arg0);
void objfx_buddy_marker_create(s32 arg0);
void objfx_b3ab0(s32 arg0);
void objfx_emitter_kind6(s32 arg0);
void objfx_emitter_kind5(s32 arg0);
void objfx_1aabc4_0(s32 arg0);
void objfx_1aabc4_1(s32 arg0);
void objfx_1aabc4_0_b(s32 arg0);
void objfx_1aabc4_1_b(s32 arg0);
void objfx_1aabc4_2(s32 arg0);
void objfx_1aabc4_3(s32 arg0);
void objfx_1ab920_0(s32 arg0);
void objfx_1ab920_1(s32 arg0);
void objfx_1ab930(s32 arg0);
void objfx_cbf80_0(s32 arg0);
void objfx_cbf80_1(s32 arg0);
void objfx_cbf80_2(s32 arg0);
void objfx_ca150(s32 arg0);
void objfx_1b01b8_1b09bc(s32 arg0);
void objfx_1aeca0(s32 arg0);
void objfx_1b03b8(s32 arg0);
void objfx_193660(s32 arg0);
void objfx_1937f4(s32 arg0);
void objfx_shot_self(s32 arg0);
void objfx_1c5280(s32 arg0);
void objfx_1c9740(s32 arg0);
void objfx_eee00(s32 arg0);
void objfx_eef40(s32 arg0);
void objfx_f03f8_both(s32 arg0);
void objfx_ebec0_0(s32 arg0);
void objfx_ebec0_1(s32 arg0);
void objfx_fdda0(s32 arg0);
void objfx_fdf38(s32 arg0);
void objfx_fe320(s32 arg0);
void objfx_fe49c(s32 arg0);
void objfx_199834(s32 arg0);
void objfx_hit_at_self_1(s32 arg0);
void objfx_hit_at_self_0(s32 arg0);
void objfx_sparks_shake_2(s32 arg0);
void objfx_sparks_shake_1(s32 arg0);
void objfx_fc438(s32 arg0);
void objfx_ff840_1_0(s32 arg0);
void objfx_ff840_0_0(s32 arg0);
void objfx_ff840_0_1(s32 arg0);
void objfx_1d5714_a(s32 arg0);
void objfx_1d469c_4(s32 arg0);
void objfx_1d469c_2(s32 arg0);
void objfx_1d469c_3(s32 arg0);
void objfx_nop_1507161c(s32 arg0);
void objfx_1d0058(s32 arg0);
void objfx_1d0024(s32 arg0);
void objfx_b5c38(s32 arg0);
void objfx_shake_large(s32 arg0);
void objfx_kind18_activate(s32 arg0);
void objfx_f9bb0(s32 arg0);
void objfx_19072c(s32 arg0);
void objfx_1d5714_b(s32 arg0);
void objfx_fa520_0(s32 arg0);
void objfx_fa520_1(s32 arg0);
void objfx_fa520_2(s32 arg0);
void objfx_1d09a8(s32 arg0);
void objfx_f2230(s32 arg0);
void objev_run_action(void);
void objev_run_action_on_child(void);
void objev_141a7c(void);
void objev_192800(void);
void objev_set_247(void);
void objev_set_248(void);
void objev_anim_at_frame(void);
void objev_anim_59(void);
void objev_anim_24(void);
void objev_7c8e0(void);
void objev_skip_if_cutscene(void);
void objev_clear_10c_grounded(void);
struct127 *obj_find_child(struct127 *arg0);
void objev_set_mask_94(void);
void objev_clear_mask_94(void);
void objev_or_mask_94(void);
void objev_remove_kind(void);
void objev_remove_kind_owned(void);
void objev_set_anim_speed(void);
void objev_remove_self(void);
void objev_kill_self(void);
void objev_anim_2c_lock_run(void);
void objev_set_2e4(void);
void objev_action21_idle(void);
void objev_clear_66_idle(void);
void objev_clear_19b_idle(void);
void objev_maybe_anim_18a(void);
void objev_anim_next_blend6(void);
void objev_loop_sound_start(void);
void objev_loop_sound_stop(void);
void objev_set_10c(void);
void objev_scale_anim_speed(void);
void objev_clear_10c_if_slow(void);
void objev_set_stunned(void);
void func_1507304C(void);
void objev_set_22e(void);
void objev_nop_15073070(void);
void objev_12d748(void);
void objev_set_1ff_200(void);
void objev_set_wait_timer(void);
void objev_wait_timer(void);
void objev_set_44(void);
void objev_idle(void);
void objev_nop_15073c48(void);
void objev_release_kind53_wait(void);
void objev_set_inner_extent_width(void);
void objev_set_inner_extent_height(void);
void objev_unlink_kind(void);
void objev_camera_view_close(void);
void objev_camera_view_mode11(void);
void objev_camera_view_mode12(void);
void objev_set_timer_3c_2000(void);
void objev_nop_15073f54(void);
void objev_set_2cb(void);
void objev_clear_flags_10b(void);
void objev_set_31c_11a(void);
void objev_add_31c_1aa(void);
void objev_set_24f(void);
void objev_set_cc3d7(void);
void objev_set_31c_26(void);
void objev_skip_if_not_carrying(void);
void objev_hold_frame(void);
void objhit_nop_15074bd8(s32 arg0, s32 arg1, s32 arg2);
void objhit_nop_15074bec(s32 arg0, s32 arg1, s32 arg2);
void objhit_burst_state5(s32 arg0, struct127 *arg1, s32 arg2);
void objhit_set_2e8(struct127 *arg0, s32 arg1, s32 arg2);
void objhit_screen_flash_b(s32 arg0, s32 arg1, s32 arg2);
void objhit_grab_player_6(struct127 *arg0, struct127 *arg1, s32 arg2);
void objhit_grab_player_7(struct127 *arg0, struct127 *arg1, s32 arg2);
void objhit_take_state_from_b(struct127 *arg0, struct127 *arg1, s32 arg2);
void objhit_grab_player_and_hit(struct127 *arg0, struct127 *arg1, s32 arg2);
void objhit_bounce(struct127 *arg0, s32 arg1, s32 arg2);
void objhit_set_gravity(struct127 *arg0, s32 arg1, s32 arg2);
void objhit_kill_b(struct127 *arg0, struct127 *arg1, u8 *arg2);

void aiscript_apply_move_flags(void);
void aiscript_if_path_point(void);
void aiscript_mode10(void) ;

void hud_health_add_piece(void);

void hud_clock_set_enabled(s32 arg0);
void hud_clock_load(void);
void event_start_level_events(s32 arg0, s32 arg1);
void event_dispatch_alt(s32 num, s32, s32, ...);
void particle_fall_step(struct42 *arg0);
void sprite_grow_step(struct114 *arg0);
s32  checksum_key_offset(s32 arg0);
void camera_hook_zoom_reset(struct108 *arg0);

void camera_hook_nop_150de310(s32 arg0);
void func_150DE32C(void); // dummy
void level_hook_rain_stop(s32 arg0);
void target_volume_hit_check_offset(void *arg0, void *arg1, s32 arg2);
void camera_hook_event_4023(struct108 *arg0);
void storm_thunder_flag_set(s32 arg0, s32 arg1);
s32  storm_thunder_flag_take(void);
void storm_thunder_sfx_update(s32 arg0);
void camera_set_ranges_500_800(struct108 *arg0);

void camera_hook_nop_15100330(s32 arg0);
void sfx_cooldown_clear(void);
void sfx_cooldown_tick(void);
void fx_free_on_msg_4b(struct102 *arg0, s32 arg1, u8 arg2);
void fx_quad_bolts_on_msg(struct207 *arg0, s32 *arg1, u8 arg2);
void fx_sparks_on_msg(struct207 *arg0, s32 arg1, u8 arg2);
void frame_hook_nop_1511fc20(s32 arg0);
/* P183: debug position hooks, the arguments their only caller (world_mesh_draw) passes: gdl in a0, three f32 in
 * a1..a3 (mfc1), then an f32 / s32 on the stack; both return gdl. Same o32 registers as the 4 x s32 form. */
Gfx *debug_gdl_pos_value_nop(Gfx *gdl, f32 x, f32 y, f32 z, f32 w, s32 player);
Gfx *debug_gdl_pos_nop(Gfx *gdl, f32 x, f32 y, f32 z, s32 player);
void camera_update_all(void);
void camera_apply_zoom_level(struct108 *arg0);
void camera_read_side_input(struct108 *arg0);
void camera_set_second_target(struct108 *arg0, s32 arg1);
void camera_calc_view_dir(struct108 *arg0);
void camera_calc_pitch(struct108 *arg0);
void camera_calc_yaw(struct108 *arg0);
void camera_update_mode_index(struct108 *arg0);
s32  camera_update_locked_mode(struct108 *arg0);
void camera_sync_angles(struct108 *arg0);
void camera_reset_rates(struct108 *arg0);
void camera_raise_timer(struct108 *arg0, s32 arg1);
void camera_update_follow(struct108 *arg0);
void camera_start_transition(struct108 *arg0, s32 arg1, s32 arg2);
void camera_noop(struct108 *arg0);
void camera_init_controller(struct108 *arg0);
void camera_snap_to_object(struct108 *arg0, struct127 *arg1);
void camera_hook_nop_1512d380(s32 arg0);
s32  fx_fade_alpha_by_life(struct102 *arg0);

struct210 *sprite_fx_spawn_at(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF);
struct210 *sprite_fx_spawn_quad(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD);
struct210 *sprite_fx_spawn_cam_at(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF);
struct210 *sprite_fx_spawn_cam(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD);
struct210 *sprite_fx_spawn_cam_ex(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE);
void sprite_fx_retire(struct210 *arg0);
void sprite_fx_free(struct210 *arg0);
void sprite_fx_free_buffers(struct210 *arg0);
void sprite_fx_dispatch_a(struct210 *arg0);
void sprite_fx_dispatch_b(struct210 *arg0);
void effect3d_release_slot(struct210 *arg0);
void effect3d_retire(struct210 *arg0);
void effect3d_free(struct210 *arg0);
void effect3d_free_buffers(struct210 *arg0);
void effect3d_dispatch_a(struct210 *arg0);
void effect3d_dispatch_b(struct210 *arg0);
struct210 *effect3d_spawn(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
/* P128/P131: the NM definition (game_169510.c) returns effect3d_spawn_full's record (the asm leaves it in v0) */
struct210 *effect3d_spawn_default(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);
s32  effect3d_spawn_oriented(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, u8 argD, s32 argE, u8 argF, s32 arg10);
struct210 *effect3d_spawn_oriented_simple(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE);
void effect3d_msg_stub(s32 arg0, s32 arg1, s32 arg2);
void effect3d_on_msg_owner(struct210 *arg0, struct212 *arg1, u8 arg2);
void sprite_quad_stub_a(void);
void sprite_quad_stub_b(void);
/* P224: D_8008A1BC entries return the callee's v0 */
s32 sprite_quad_build_screen_a(s32 arg0, s16 arg1);
s32 sprite_quad_build_screen_b(s32 arg0, s16 arg1);
u8 *sprite_quad_build_axes_entry(struct210 *arg0, s16 arg1);
void fx_lists_broadcast_a(s32 arg0, u8 arg1);
void fx_lists_broadcast_b(s32 arg0, u8 arg1);
void effect_free_buffers_retire(struct210 *arg0);
void effect_free_buffers_delete(struct210 *arg0);
s32  effect_check_false(s32 arg0, s32 arg1);
void interact_fx_detach(struct37 *arg0);
void interact_fx_destroy(void *arg0);
void interact_fx_delete(void *arg0);
void obj_interaction_start_timed(void *arg0, s32 arg1, s32 arg2);
s32  debug_tweak_int_mid(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char *arg4, s32 arg5);
s32  debug_tweak_int(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32  debug_tweak_value(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32  obj_get_yaw_byte(struct127 *arg0);
s32  wrap_byte_angle(s16 arg0);
f32  angle_diff_rad(f32 arg0, f32 arg1);
void vec3_cross(struct17 *arg0, struct17 *arg1, struct17 *arg2);
s32  camera_within_dist(u8 arg0, f32 arg1, struct17 *arg2);
f32  curve_table_lookup(f32 arg0, f32 arg1, f32 arg2);
void obj_set_destroyed(struct127 *arg0);
void obj_broadcast_replace(struct127 *arg0, struct127 *arg1);
void fx_random_flicker_update(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7);
struct260 *effect_node_create(s16 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, struct37 *arg6, u8 arg7, s32 arg8);
struct260 *effect_node_create_nodraw(s16 arg0, s8 arg1, s8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
void effect_node_free_vtx(struct260 *arg0);
void effect_node_retire(struct260 *arg0);
void effect_node_free(struct260 *arg0);
void effect_node_kind_call_a(struct260 *arg0);
void effect_node_kind_call_b(struct260 *arg0);
void effect_node_kind_message(struct260 *arg0, s32 arg1, u8 arg2);
s32  effect_node_draw(s32 arg0, struct260 *arg1, s16 arg2);
void effect_nodes_broadcast(s32 arg0, u8 arg1);
void effect_node_link_message(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);
void level_frame_hook_nop(void);
void node_destroy(struct102 *arg0);
void node_delete(struct102 *arg0);
void node_retire(struct102 *arg0);
void node_unlink_free(struct102 *arg0);
void objfx_nop_1519ef70(struct127 *arg0, s32 arg1, s32 arg2);

void impact_tint_red(struct218 *arg0);
void impact_tint_yellow(struct218 *arg0);
void impact_tint_red_green_a(struct218 *arg0);
void impact_tint_red_green_b(struct218 *arg0);
void impact_tint_red_green_c(struct218 *arg0);
void impact_tint_white(struct218 *arg0);
void impact_tint_green_fixed(struct218 *arg0);
void impact_tint_green(struct218 *arg0);
void impact_tint_brown(struct218 *arg0);
void impact_tint_cyan(struct218 *arg0);
void impact_tint_magenta(struct218 *arg0);
void impact_spawn_debris_up(struct17 *arg0, s32 arg1, u8 *arg2, u8 arg3, s32 arg4);
void func_151F0080(f32 arg0[4][4], s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_151F00E0(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);

void debugger_page_title_draw(void);
s32  debugger_page_title_input(void);
void debugger_main_menu_draw(void);
s32  debugger_main_menu_input(void);
void debugger_page_nop_draw(void);
void debugger_page_nop_input(void);
void debugger_regs_page_draw(void);
s32  debugger_regs_page_input(void);
void debugger_draw_exception(struct118 *arg0);
void debugger_print_string(s32 arg0, u8 *arg1);
void debugger_set_color(u8 arg0, u8 arg1, u8 arg2);
s32  debugger_identity(s32 arg0);
s32  debug_si_device_busy();
s32  debug_si_raw_start_dma(s32 direction, void *dramAddr);
void debug_stub(void);
s32  debug_float_is_denorm_or_nan(f32 arg0);
void debug_stub_4args(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
u8*  debug_memcpy(u8 *arg0, u8 *arg1, u32 arg2);
s32  debug_sprintf_put(u8 *arg0, u8 *arg1, u32 arg2);


/* non-matching */

void boot_game_thread_main(s32 arg0);
void boot_clear_low_block(void);
void tlb_remap_game_segment(s32 arg0);
void init_printf_ldtob(void *arg0, u8 arg1);
// s16  init_printf_ldunscale(s16 *arg0, struct05 *arg1);
//init_printf_genld
// s32  init_printf_xprintf(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3);
//init_printf_put_arg
// s32  func_10002DB0(s32 arg0, s32 arg1);
//pi_dev_mgr_main
void func_100030A0(OSPri priority, OSMesgQueue *mesgQueue, OSMesg *arg2, s32 arg3);
struct00* func_10003220(struct00 *arg0);
void func_10003330(struct00 *arg0);
//func_100034E0
//func_10003658
// void init_stub_noop4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
// void debug_port_write_4040(void);
void mem_clear_expansion_flag(void);
// void heap_init(void);
//framebuffer_fill_color
s32 heap_alloc_tagged(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
//heap_free
void heap_set_block_tag(s32 *arg0, u32 arg1);
//rom_dma_read_chunked
void rom_read_direct(s32 devAddr, void *dramAddr, u32 size);
void sched_thread_main(s32 arg0);
//sched_try_start_gfx_task
void sched_init(OSMesgQueue *arg0);
void prenmi_thread_main(s32 arg0);
//func_10005570
//func_100056A0
//func_100057E0
//func_10005948
//func_10005AB0
void tlb_area_init(s32 arg0);
//tlb_page_bitmap_reset
//func_10005C2C
void func_1000709C(void);
//func_10007C74
//func_10007CC4
//os_dispatch_thread
//func_10007DA0
//func_10007DAC
//func_10008120
//audio_system_init
//music_player_set_voice_param
//music_player_set_master_gain
//music_seq_new_marker
void music_seq_jump_marker(u8 arg0, u8 arg1);
//music_player_start_seq
//audio_mgr_init
void audio_thread_main(s32 arg0);
//audio_do_frame
s32 audio_dma_callback(u32 arg0, s32 arg1, s32 arg2);
//audio_clear_dma
void snd_cache_entry_free(struct54 *arg0);
s32 snd_cache_load_on_demand(void *arg0, s32 arg1);
s32  snd_cache_dma_new(void);
//snd_cache_update_dmas
//snd_cache_flush_unused
//sound_calc_pan_volume
//sound_path_calc_pan_volume
//sound_calc_pan_from_xz
struct151 *music_find_song_or_queued(s32 arg0);
//music_clear_link_refs
//music_song_slot_alloc
//music_queue_song
//music_get_playing_songs
//music_song_cb_mute_layers
//music_song_cb_level4_meter
//music_song_cb_pos_song93
//music_song_cb_level19_ambience
//music_song_cb_level1d_voices
//music_song_cb_level1d_mode
s32 music_song_cb_channel_effect(s32, u8, f32, f32, f32);
//music_song_cb_level31_distance
//music_song_cb_level37_song54
//music_song_cb_level37_song54_b
//music_song_cb_level42_song58
//music_players_set_volume_ramp
//music_player_apply_volume
//music_song_can_start
//music_player_process_messages
//music_player_update_frame
void music_update_all(f32 arg0, f32 arg1, s32 arg2);
//music_play_song
//music_stop_song
//music_release_stopped_slots
void music_song_set_fade(s32 arg0, s32 arg1, s32 arg2);
//music_song_type_is_1_or_3
//music_restart_type13_songs
//music_set_all_paused
s32 music_song_set_chans_level(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 music_song_set_chans_volume(s32 arg0, s32 arg1, s32 arg2);
//music_song_set_marker
//music_post_event_request
//music_clear_event_flag1
//music_song_get_player_flags
//music_system_reset
//sfx_cb_delayed_play_2d
//sfx_cb_delayed_object_sound2
s32  sfx_cb_delayed_object_sound(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6);
s32  sfx_cb_follow_object(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, void *arg5);
//sfx_cb_follow_object_anim
//sound_voices_reset
//sound_voice_is_looping
//sound_id_is_playing
//sound_pick_variant
//sound_listener_volume_pan
void sound_voice_set_param(u16 arg0, s16 arg1, s32 arg2);
void sound_voice_update_3d(u16 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
u16  sfx_emitter_start(u16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s16 arg6, s32 arg7, void *arg8, s32 arg9, s32 argA, s32 argB);
//sfx_emitter_stop_at
//sfx_emitter_stop_by_callback
//sfx_emitter_stop_by_voice
//sfx_emitter_free_index
//sfx_emitter_find_by_voice
s32  sfx_emitter_find_by_callback(s32 arg0, s32 arg1, s32 arg2);
//sfx_emitter_set_volume_pitch
//sfx_emitter_replace_callback
u16 actor_sound_play(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
u16 actor_sound_play2(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
//actor_sound_play2_delayed
void actor_sound_play_untracked(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
//actor_sound_set_volume
u16  sound_voice_play(u16 arg0, s32 arg1, u16 arg2, u8 arg3, s16 arg4, u8 arg5, u8 arg6);
//sound_voice_play_at
u16 sound_play_at(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
//sound_play_for_actor
//sound_stop_queue_process
s32 sound_source_mix(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 *arg6, s32 *arg7, s32 *arg8);
//sfx_emitters_update
//sound_update_frame
//sound_surface_footstep
//audio_mixer_update_frame
//mp3_voice_play
//text_queue_read
// void audio_set_output_mode(u8 arg0);
void n_cseq_set_loc(void *arg0, void *arg1);
void n_cseq_find_markers(void *arg0, s32 arg1, u32 arg2, u32 arg3);
// void n_csp_update_chan_filter(struct26 *arg0, u8 arg1);
// void n_csp_cc_sustain(struct26 *arg0, s32 arg1, s32 arg2, u32 arg3);
// void n_csp_cc_fade_target(struct26 *arg0, struct25 *arg1, s32 arg2, s32 arg3);
//n_seqp_unmap_voice
//n_seqp_cancel_voice_kill
//n_seqp_lookup_voice
//n_seqp_lookup_sound_quick
//func_1001B200
// s32  n_seqp_voice_fx_mix(void *arg0, void *arg1);
// u8   func_1001B450(void *arg0, void *arg1);
Acmd *func_1001E530(s32 arg0, Acmd *arg1, s32 arg2);
//func_1019EA88
//func_1019EAB0
//func_1019EAE0
//func_1019ECAC
//func_1019ED8C
//func_1019ED94
//func_1019ED9C
//func_1019EE0C
//func_1019EEAC
//func_1019F018
//func_1019F154
//func_1019F214
//func_1019F4E4
//func_1019F59C
//func_1019FA14
//func_1019FACC
//func_1019FD38
//func_1019FDC0
//func_1019FE18
//func_1019FF78
//func_101A0094
//func_101A0100
//func_101A017C
//func_101A0188
//func_101A02B8
//func_101A0344
//func_101A040C
//func_101A0430
//func_101A04EC
//func_101A04F4
//func_101A0538
void func_1001C224(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void n_fx_lowpass_update_coefs(struct139 *arg0, f32 arg1);

u16 *quadtree_build_node(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void level_lights_stub(s16 arg0);

s32  render_set_scissor(s32 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32  asset_load_ptr(s32 *, s32, ...);
struct126 *func_1503195C(struct127 *, s32, s32);
void dl_validate_list(void *arg0, u32 arg1, s32 arg2);
s32 ring_buffer_put_record(struct105 *arg0, u8 *arg1, s32 arg2); /* P98: the asm reads a1 / a2 (callback args left in place by mp3_id3_text_enqueue) */
f32  func_15047C00(f32 arg0);
f32  func_15047D60(f32 arg0);
f32  math_asinf_table(f32 arg0);
f32  math_asinf(f32 arg0);
f32  vec3_heading_deg(struct17 *arg0);
void func_15049688(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void obj_update_move_anim(struct127 *arg0, f32 arg1);
void obj_update_floor(struct127 *, f32);
void vec_from_yaw_pitch(u16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
f32  obj_dist_3d(struct127 *arg0, struct127 *arg1);
void obj_land_on_floor(struct127 *arg0, f32 arg1);
void obj_start_anim(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6);
u32  obj_find_reaction_row(s32, struct127*);
void obj_hit_reaction_advance(u8, struct127*); /* P209: the asm ignores a0 (home slot only) and returns nothing */
struct127* obj_find_by_id(s32);
void obj_sfx_play_attached(s32 arg0, struct127 *arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void obj_remove(struct127 *arg0, s32 arg1);
void obj_fade_command(struct127*, u8, u8, u8, u8);
void obj_set_inner_extent_width(struct127 *arg0, f32 arg1);
void obj_set_inner_extent_height(struct127 *arg0, f32 arg1);
s32 camera_object_spawn(f32, f32, f32, f32, u8, s32, f32, f32, s32, s32, s32);
struct127 *obj_find_child_nth(struct127 *, s32);
void aiscript_set_flags_fc(void);
s32  func_15081574(s32, f32, f32, s32, s32, s32);
s32 obj_setup_run(struct127*, s32, f32, s32);
s32  setup_entry_find_by_id(u8);
struct127 *obj_find_by_setup_id(u8);
void player_stat_modify(s16, s16, s32);
s32  player_stat_get(s16 arg0, s32 arg1); // a guess
void rail_event_add(f32, f32, f32, f32);
s32 trigger_test_player(s32, s32);
void mtxf_scale(f32 mtx[4][4], s32 x, s32 y, s32 z);
void mtxf_rotate_xyz_deg(f32 mtx[4][4], f32 arg1, f32 arg2, f32 arg3);
void mtx_rotate_scale_3x3(f32 mtx[4][4], f32, f32, f32, f32, f32, f32);
void func_150AD770(void);
f32  fast_cosf(f32);
f32  fast_sinf(f32);
f32  func_150AD900(f32 *arg0, f32 *arg1);
f32  vec3f_magnitude(f32 *arg0);
s32  random_int(void);
f32  random_float(void);
void beam_effect_spawn_attached_ex(struct127*, u8, s16, s32, f32, f32, f32, f32, f32, f32, s16, s16, u16, f32, f32, u8, f32);
void world_obj_hit_activate(s32 arg0, s32 arg1);
void func_1510B32C(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_1510B958(s32 arg0);
s32  func_1510B9D0(s32 arg0, s16 arg1);
s32  zone_tree_find_leaf(s32 arg0, s32 arg1);
s32  camera_push_mode(struct108 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32  camera_pop_mode(struct108 *arg0, s32 arg1);
void camera_exit_aim_mode(struct108 *arg0);
s32 camera_shake_start(struct108*, s32, s32);
struct210 *sprite_fx_spawn(struct210 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, struct167 *arg7, s32 arg8, u8 arg9, s32 argA);
void *effect3d_spawn_full(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
s32  effect3d_build_axes(struct211 *arg0, s16 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6);
void  sprite_quad_place(struct210 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6);
s32 sprite_quad_place_cam(s32, s32, s32, f32, f32, f32, f32, f32, u8);
f32  angle_byte_cos(u8);
f32  spawn_region_area(struct_eu_15144598 *arg0);
f32  spawn_region_volume(struct_eu_15144598 *arg0);
f32  wrap_angle_rad(f32 arg0);
s32 char_fx_send_event(s32, s16, s32, s32); /* P218: the asm passes the event values (a2 / a3) through unmasked */
s32  func_1515D6D0(s32 arg0, s32 arg1);
void light_set_level_colour(s32, s32, s32, u8);
void node_broadcast_types(void *, s32, s32, u8);
void node_broadcast_type(s32, s32, u8);
s32 node_handle_link_message(s32, u8, s32, s32, s32);
void fx_dust_puff_behind_obj(s32, s32, s32, s32, s32, s32, s32, u8, s32);
void vtx_anim_light_create(u8 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4, f32 arg5, u16 arg6, f32 arg7, s8 arg8, s8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF);
s32  func_1517EFAC(s32 arg0);
void swarm_destroy_by_id(u8);
s32  light_fx_add(s32 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void *level_dl_add_texture_scroll(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void swinging_lamp_spawn(s32 arg0, u8 arg1, u8 arg2, u8 arg3);
void rumble_all_players_at(struct17*, f32, f32, f32, s16, s16, s32, s32);
void bone_beam_spawn(struct127*, f32*, f32*, u8, f32, u8, s32);
s32 impact_debris_spawn(u8 arg0, f32 arg1, u8 arg2, s32 arg3, struct17 *arg4, s16 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA);
s32 impact_smoke_puff_spawn(u8 arg0, f32 arg1, f32 arg2, u8 arg3, s16 arg4, s32 arg5, void *arg6, s32 arg7, s32 arg8);
void impact_dust_particle_spawn(u8 arg0, f32 arg1, s16 arg2, s32 arg3, void *arg4, u8 arg5, s32 arg6);
void func_151EF954(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
s32 mp3_stream_rom_read(s32, void *, s32, s32);
void func_151FA130(void);
void func_1019EA88(void);

/* EU: new decompilation */
void node_set_type(s32 arg0, s32 arg1);
void node_broadcast_range(s32 arg0, s32 arg1, s32 arg2, u8 arg3);
void point_emitter_handle_message(void *arg0, void *arg1, u8 arg2);
void impact_burst(s32 arg0, u8 arg1, s32 arg2);
void flash_blades_spawn(s32 arg0, s32 arg1, s32 arg2, f32 arg3, u8 arg4, s32 arg5);
void flare_node_remove(f32 *arg0, structEU_16DC80 *arg1);
void effect_set_orbit_pos(structEU_16DC80 *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5);
void swing_lamp_handle_event(u8 *arg0, s32 arg1, u8 arg2);
void screen_uv_mesh_handle_message(u8 *arg0, s32 arg1, u8 arg2);
s32 collision_tri_box_test(struct_eu_bytes24 arg0);
void debugger_draw_gprs(struct118 *arg0);
void debugger_draw_fpu_regs(struct118 *arg0);
s32  asset_rec_read_cached(u8 *arg0, s32 arg1, s32 *arg2);
void node_list_insert(struct_eu_node *arg0, s32 arg1);
void node_list_unlink(struct_eu_node *arg0);
s32  trigger_first_touched(); // 3 params (u32, s32, s32 *); the caller in game_16EE20 passes a 4th
s32 dl_count_triangles(Gfx *arg0);
u16  sound_voice_play_at(u16 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4, s32 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA);
void objev_start_anim_cmd(void);
void ground_explosion(struct127 *arg0, struct127 *arg1, f32 *arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);
void *node_alloc(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5);
s32  ray_sphere_intersect(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, s32 arg4, s32 arg5, f32 *arg6, f32 *arg7);
void mtxf_transform_point(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);
void obj_dust_trail_on_link(struct127 *arg0, struct127 *arg1);
s32  line_closest_point(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4);
struct225 *light_create_with_ctrl(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);
s32 rumble_request(structEU_151D8E18 *arg0, s32 arg1, u8 arg2, s32 arg3);
s32  held_obj_byte7d_get(void);
void object_beam_fire(struct127 *arg0, u8 arg1, s32 arg2);
void object_bolt_fire(struct127 *arg0, u8 arg1, s32 arg2);
void character_smoke_puff(struct127 *arg0, u8 arg1, s32 arg2);
s32 point_emitter_spawn(struct_eu_EF410 *arg0, s32 arg1, u8 arg2, s32 arg3);
void *fxrec_spawn(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9, s32 argA);
void mtx_transform_point_or_origin(void *arg0, void *arg1, void *arg2);
void fire_embers_spawn(void *arg0, u8 arg1, s32 arg2);
void impact_blast_spawn_small(void *arg0, void *arg1, u8 arg2, u8 arg3, s32 arg4);
void emit_sparks_in_angle_range(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4);
void obj_start_hit_reaction(struct127 *arg0, s32 arg1, u8 arg2);
void quadtree_link_siblings(struct_eu_qnode *arg0, struct_eu_qnode *arg1);
s32 char_fx_find_slot(struct_eu_link *arg0, s16 arg1, struct_eu_link **arg2);
s32 char_fx_attach(void *arg0, struct127 *arg1, s16 arg2);
void obj_interaction_attach_timed(struct127 *arg0, s32 arg1);
s32 impact_dust_cloud_spawn(void *arg0, f32 *arg1, u8 arg2, f32 arg3, s16 arg4, u8 arg5, f32 arg6, u8 arg7, f32 arg8, f32 arg9, u8 argA, s32 argB, u8 argC, u8 argD, u8 argE, s32 argF);
s32  sfx_cb_delayed_object_sound2(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6);
s32 life_pickup_spawn(f32 *arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6); /* P98: asm reloads a1 with lwc1 */
void kind_effect_spawn(u8 arg0, u8 arg1, void *arg2, s32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8);
void music_release_stopped_slots(void);
s32  asset_dma_into(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void hit_react_puff_burst(struct127 *arg0, struct127 *arg1);
void emit_textured_burst(void *arg0, void *arg1, void *arg2, s32 arg3, f32 arg4, u8 arg5, u8 arg6, s32 arg7);
f32 *camera_get_pos(s32 arg0);
s32 eeprom_async_write_start(OSMesgQueue *mq, u8 address, void *buffer, s32 nbytes); // osEepromLongWrite
s32 game_eeprom_long_read(OSMesgQueue *mq, u8 address, void *buffer, s32 nbytes); // osEepromLongRead
s32 game_eeprom_write(OSMesgQueue *mq, u8 address, u8 *buffer); // osEepromWrite
s32 impact_dust_cloud_wobble(struct_eu_2062D0_d *arg0, s32 arg1);
struct_eu_C8950_blk *event_block_relocate(struct_eu_C8950_blk *arg0);
void spawn_line_emit(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, s32 arg8, f32 arg9, s32 argA, u8 argB);
void quadtree_alloc_node_pool(void);
void attach_fx_asset_release(s32 arg0);
void wake_spray_spawn(u8 *arg0, u8 arg1, s32 arg2);
void path_trail_spawn_effects(s32 arg0, f32 arg1, s32 arg2);
f32  scenery_swing_angle_step(f32 *arg0, f32 arg1);
f32  scenery_pendulum_angle_step(f32 *arg0, f32 arg1);
void sky_flash_uncount(s32 arg0);
void obj_get_aim_vectors(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
void breakable_scatter_pieces(s32 arg0, f32 arg1, f32 arg2, s32 arg3);
void sprite2d_broadcast(void *arg0, u8 arg1);
void obj_bone_point_or_pos(s32 arg0, s32 arg1, void *arg2, u8 arg3, f32 arg4);
void face_set_default_anim(struct127 *arg0, s32 arg1);
struct127 *obj_find_by_spawn();
s32 sprite_draw_if_visible(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void rubble_scatter_spawn_ex(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u16 arg4, s32 arg5, u8 arg6);
s32 attack_spawn_at_point(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, u16 arg5, s32 arg6, s32 arg7);
void surface_impact_effects(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, u8 arg6, u8 arg7);
void idle_recent_push_one(u8 arg0, u8 *arg1);
/* P221: NM only (game_981E0's objfx_fc438 called it undeclared: implicit int, a wasm signature mismatch) */
void gunfire_burst_spawn(struct127 *arg0, struct127 *arg1, u8 arg2, u8 arg3);
/* EU: end new */
#endif
