#ifndef VARIABLES_H
#define VARIABLES_H

#include "structs.h"
#include "sched.h"

/* defined */

// 0x0002C200
extern f32 D_8002C200;
extern f32 D_8002C204;
extern f64 D_8002C208;

// 0x0002C210
extern f32 D_8002C210;
extern f32 D_8002C214;
extern f64 D_8002C218;

// 0x0002C220
extern f32 D_8002C220;
extern f32 D_8002C224;
extern f32 D_8002C228;
extern f32 D_8002C22C;
// 0x0002C230
extern f32 D_8002C230;
extern f32 D_8002C234;
extern f32 D_8002C238;

extern struct120 D_8002C240[];

extern f32 D_8002C3F8;
extern f32 D_8002C3FC;

// 0x0002C750
extern f32 g_audio_k_usec_per_sec; /* was D_8002C750 */

// 0x0002C770
extern f32 PI;
extern f32 g_audio_fx_sqrt2; /* was D_8002C774 */
extern f32 g_audio_semitone_up; /* was D_8002C778 */
extern f32 g_audio_semitone_down; /* was D_8002C77C */
// 0x0002C780
extern f32 g_audio_lp_coef_scale_0; /* was D_8002C780 */
extern f32 g_audio_lp_coef_scale_1; /* was D_8002C784 */

// 0x0002C810
extern f32 D_8002C814;
// 0x0002C820
extern f32 D_8002C820;
// 0x0002C830
extern f32 D_8002C830;
extern f32 D_8002C834;
extern f32 D_8002C838;
// 0x0002C840
extern f64 D_8002C840; // double
extern f32 D_8002C848;

extern f32 D_8002C920;

extern u32 D_80042450[512]; // chunk0 offsets

extern char D_8002C6B0[];
extern char D_8002C6DC[];

/* undefined */

extern OSThread *__osRunningThread;

/* FUNCTIONS */
// FIXME: we should be able to reference these directly
extern s32  D_10013598;


/* 80000000 */

extern s32  D_80000000;
extern s32  D_80000004;
extern s32  D_80000008;
extern s32  D_8000000C;

extern struct14 *D_80000080;
extern struct14 *D_80000100;
extern struct14 *D_80000180;

extern s32  g_os_tv_type; /* was D_80000300 */
extern s32  g_os_rom_base; /* was D_80000308 */
extern s32  g_os_reset_type; /* was D_8000030C */
extern u32  g_os_cic_id; /* was D_80000310 */
extern s32  g_os_app_nmi_buffer[16]; /* was D_8000031C */ // 64 bytes

/* 80020000 */

extern u8   D_8002AAE0;
extern u8   D_8002AAE4;
extern s32  g_framebuffers[2]; // pointer to framebuffer /* was D_8002AAE8 */
extern u8   D_8002AB40;
extern OSViMode D_8002AB90;
extern OSViMode D_8002ABE0;
extern s32  g_heap_largest_free; /* was D_8002AC30 */
extern OSScTask *g_sched_gfx_task; /* was D_8002AC50 */
extern OSScTask *g_sched_audio_task; /* was D_8002AC54 */
extern OSScTask *g_sched_last_gfx_task; /* was D_8002AC58 */
extern u8   g_eeprom_writes_disabled; /* was D_8002AC5C */
extern u8   g_loop_exit_flag_ac60; /* was D_8002AC60 */
extern u16  g_loop_exit_value_ac64; /* was D_8002AC64 */
extern s8   g_sched_audio_timer_armed; /* was D_8002AC6C */
extern u8   g_audio_thread_started; /* was D_8002AE40 */
extern u32  D_8002AE44;
extern s32  D_8002AE48;
extern s32  D_8002AE4C;
extern s32  g_printf_zeros; /* was D_8002AE54 */

extern s32  g_music_open_level; /* was D_8002B070 */
extern struct138 g_music_song_table[]; /* was D_8002B074 */
extern s32  g_music_song_table_type[][4]; /* was D_8002B078 */ // probably not correct...
extern s32  g_music_slot_default_types; /* was D_8002B9D4 */
extern s32  g_music_slot_default_masks; /* was D_8002B9F4 */

extern struct31 *g_sndp_active_head; /* was D_8002BA20 */
extern struct31 *g_sndp_active_tail; /* was D_8002BA24 */
extern struct31 *g_sndp_free_list; /* was D_8002BA28 */
extern s32  g_sndp_player; /* was D_8002BA2C */
extern s16  g_sndp_active_count; /* was D_8002BA30 */

extern struct07  *D_8002BA40;
extern struct07  *g_audio_synth; /* was D_8002BA44 */

extern s16  D_8002BC10[];
extern s16  D_8002BD0E[];
extern s64  D_8002BD10;
extern s32  D_8002BD14;
extern s32  D_8002BD18;
extern s32  D_8002BD20; // init ok?
extern s32  g_audio_mixer_default_vol; /* was D_8002BD60 */
extern u8   D_8002BF70[];

/* DATA section from g_os_litob_ldigs to g_boot_idle_stack_alias */


/* BSS STARTS at g_boot_idle_stack_alias */

extern s32  g_boot_idle_stack_alias; /* was D_8002D4B0 */ // BSS
extern s32 *g_boot_thread_stack_4000_alias; /* was D_8002D8B0 */

/* 80030000 */
extern OSThread g_game_thread; /* was D_80031AE0 */
extern OSThread g_boot_idle_thread; /* was D_800318B0 */ // thread 1

extern s32  D_80032B30;
extern s32  D_80033330;

extern s32  D_800354F8;
extern s32 *D_800354FC; // contains chunk0 offsets
extern s16  g_debug_printf_len; /* was D_80035500 */
extern OSThread *D_80035910;

extern s32 D_800364C4;
extern OSMesgQueue D_80036B40;
extern OSMesg      D_80036B58;
extern struct00 *D_80036B60;
extern s32  D_80036B70;
extern s32  D_80036B78;
extern s32  D_80036B80;
extern s32  D_80036B88;
extern s32  D_80036B8C;
extern s32  D_80036B90;
extern s32  D_80036B98;

extern u32  D_80038070;
extern u16  D_80038074;
extern u8   g_mem_expansion_pak; /* was D_80038080 */
extern u32  g_mem_rdp_fifo_start; /* was D_80038090 */
extern u32  g_mem_rdp_fifo_end; /* was D_80038094 */
extern u32  g_mem_heap_end; /* was D_80038098 */
extern u32  g_mem_scratch_area; /* was D_8003809C */
extern f32  g_text_scale_x_alias; /* was D_800380A0 */
extern f32  g_text_scale_y_alias; /* was D_800380A4 */
extern struct54 *g_heap_largest_block; /* was D_800380B0 */
extern struct54 *g_heap_head; /* was D_800380B4 */
extern struct54 *g_heap_free_head; /* was D_800380B8 */
extern s32 *D_800380BC;

extern s32  D_800380C0;
extern s32  D_800380C4;
extern s32  D_800380C8;
extern s32  D_800380CC;
extern s32  D_800380D0;
extern OSMesg      g_pi_mgr_msgs; /* was D_800380E0 */
extern OSMesgQueue g_pi_mgr_queue; /* was D_800388B0 */

extern OSMesg      gMessage0;
extern OSMesgQueue gMessageQueue0;

extern OSMesg      gMessages[3];
extern OSMesgQueue gMessageQueue[3];

extern s32 D_80038904;
extern OSIoMesg g_pi_io_msgs[]; /* was D_80038950 */

extern u8  g_pi_io_msg_index; /* was D_8003A570 */
extern u8  g_pi_io_pending; /* was D_8003A571 */
extern u8  D_8003A572;
extern u8  D_8003A573;
extern u8  D_8003A574;
extern u8  D_8003A575;
extern u8  g_sched_gfx_resumed; /* was D_8003A580 */
extern u8  g_sched_audio_running; /* was D_8003A581 */
extern u8  g_sched_gfx_state; /* was D_8003A582 */
extern u8  g_sched_gfx_running; /* was D_8003A583 */
extern u8  g_sched_dp_done; /* was D_8003A584 */
extern u8  D_8003A588;
extern u8  D_8003A5C8;

extern OSMesgQueue g_sched_gfx_queue_alias; /* was D_8003B1E8 */
extern OSMesgQueue g_sched_audio_queue_alias; /* was D_8003B200 */
extern OSMesgQueue g_sched_event_queue_alias; /* was D_8003B218 */

extern OSMesgQueue *g_sched_client_queue; /* was D_8003B230 */
extern OSPfs       *g_sched_clients; /* was D_8003B234 */
extern u8 g_sched_retrace_count; /* was D_8003B238 */
extern u8 g_sched_frame_retraces; /* was D_8003B239 */
extern u8 g_sched_retrace_hold; /* was D_8003B23A */
extern OSMesg      g_sched_retrace_msg; /* was D_8003B240 */

// extern s32 *D_8003B264;
extern OSThread    g_sched_thread; /* was D_8003B6A0 */
extern OSMesg      g_sched_gfx_msgs; /* was D_8003B660 */
extern OSMesg      g_sched_audio_msgs; /* was D_8003B670 */
extern OSMesg      D_8003B680;

extern OSMesgQueue g_prenmi_queue; /* was D_8003B9D0 */
extern OSMesg      g_prenmi_msgs; /* was D_8003B9E8 */
extern OSThread    g_prenmi_thread; /* was D_8003B9F0 */

extern u64  D_8003BC20;
extern u32  D_8003BC24;

extern s32  D_8003BC30;
extern s32  D_8003BD30;
extern s32  D_8003BE30;
extern u8   D_8003BE50[];
extern s32  g_tlb_page_bitmap; /* was D_8003BE70 */
extern s32  g_tlb_area_phys; /* was D_8003BE74 */
extern s16  D_8003BE78;
extern s8   D_8003BE7C;
extern s32  D_8003BE94;

extern s32  D_8003C858;
extern s32  g_dbg_crash_marker; /* was D_8003C8E0 */
extern struct26 *g_music_players[]; /* was D_8003C900 */
extern struct14 *D_8003CD40;
extern struct247  g_music_seq_markers[]; /* was D_8003CD48 */
extern s16  D_8003C910[];

extern s32  D_8003E368;
extern s32  D_8003E370;
extern s32  D_8003E388;
extern struct50 *D_8003E390[];
extern OSThread  g_audio_thread; /* was D_8003E3A0 */
extern s32  D_8003E640;

extern OSMesgQueue *D_8003E608;
extern OSMesg      *D_8003E620;
extern OSMesgQueue *D_8003E5D0;
extern OSMesg      *D_8003E5E8;

extern s32  D_8003CA3C[];
extern u8   D_8003CA48[];
extern ALCSeq g_music_seqs[]; /* was D_8003CA58 */
extern s32  D_8003C90C;

/* 80040000 */


extern s32  D_80040000;
extern struct147 g_snd_cache; /* was D_800406A0 */
extern struct54 *D_800406A4;
extern struct54 *D_800406B0;
extern u8   g_audio_dma_buffers; /* was D_800406B8 */
extern u32  g_snd_cache_dma_bufs; /* was D_80040AC8 */ // 1200 byte struct?
extern struct147 g_audio_dma_state; /* was D_80040F78 */
extern u8   D_80040F84;
extern s32  D_80040F88;
extern s32  D_80040F8C;
extern s32  D_80040F90;
extern struct146 D_80040F98[];
extern u8   D_80041F00;
extern s32  g_music_event_flags; /* was D_80041F04 */
extern s32  g_music_event_value; /* was D_80041F08 */
extern s32  g_music_event_param; /* was D_80041F0C */
extern struct49 *g_sound_stop_queue[]; /* was D_80041F10 */
extern u32  g_sound_stop_queue_count; /* was D_80041F50 */
extern s32  g_sound_bus_volume; /* was D_80041F54 */
extern u16  g_sound_bus_volume_lo; /* was D_80041F56 */
extern f32  g_sound_bus_volume_rate; /* was D_80041F58 */
extern s32  *g_sound_variant_played; /* was D_80041F5C */
extern u8   g_sound_pause_mute_state; /* was D_80041F60 */
extern u8   g_sound_pause_mute_request; /* was D_80041F61 */
extern struct00 D_80041F68[];
extern s8   g_sound_fx_mix_boost; /* was D_80041FD8 */
extern u8   g_sound_default_fx_mode; /* was D_80041FD9 */
extern s32  g_sound_bus_volume_target; /* was D_80041FDC */
extern struct15 g_sfx_emitters[]; /* was D_80041FE0 */
// extern struct15 **D_80041FEC[]; // struct size 0x30 ?
extern s32 D_80041FEC[][12];

extern OSMesgQueue *D_80041298;
extern OSMesg      *D_800412B0;
extern OSMesgQueue *D_800416F0;
extern OSMesg      *D_80041708;

extern struct151* g_music_player_songs[]; /* was D_800417B0 */
extern u32 D_800417BC;
extern u8 g_music_player_marker_bits[]; /* was D_800418AC */
extern s32 D_800418B0[];

extern u8 D_800419A0;
extern struct137 g_music_song_slots[12]; /* was D_800419A8 */ // 1200 bytes
extern OSMesgQueue g_music_player_queues[3]; /* was D_80041E58 */
extern struct117 g_game_mesg_bufs[3]; /* was D_80041EA0 */

extern s32  g_sfx_emitter_count_alias; /* was D_80042760 */
extern s32  g_audio_mixer_req_mode; /* was D_80042770 */
extern s32  g_audio_mixer_override_mode; /* was D_80042774 */
extern s32  g_audio_mixer_base_mode; /* was D_80042778 */
extern s32  g_audio_mixer_fade_mode; /* was D_8004277C */
extern f32  D_80042780;
extern f32  D_80042784;
extern f32  D_80042788;
extern f32  D_80042790;
extern f32  D_80042794;
extern f32  D_80042798;
extern struct105 g_mp3_text_queue; /* was D_800427A0 */
extern s32  g_mp3_text_queue_buf; /* was D_800427B0 */
extern s16  g_mp3_voice_last_id; /* was D_800427F4 */
extern struct120 g_sound_voices[]; /* was D_800425E0 */
extern struct124 *g_audio_osc_free_list; /* was D_80042800 */
extern s32  g_audio_osc_pool; /* was D_80042804 */
extern u16  D_800428B8[];
extern u8   g_audio_surround; /* was D_800428C0 */
extern u8   g_audio_mono; /* was D_800428C1 */
extern u8   g_audio_headphones; /* was D_800428C2 */
extern u8   g_audio_bus_one_side[]; /* was D_800428C4 */
extern u8   g_audio_bus_invert[]; /* was D_800428C6 */
extern u8   g_audio_bus_mix_type[]; /* was D_800428C8 */
extern s32  D_800428E0;
extern s32 *D_800428F8;

// BSS ENDS AT g_frame_counter_block_alias

extern s32  *g_frame_counter_block_alias; /* was D_80043B40 */ // 4064
extern s32  g_audio_heap_arena; /* was D_80044B20 */ // 253952 bytes, bunch of structs?

// this space is filled by g_audio_heap_arena
// 0x80044B20 + 253952 = 0x80082B20

/* 80080000 */
extern s32  D_80082B20;
extern void (*g_camera_level_hook_fns[])(struct108 *); /* was D_80082B40 */
extern u8   g_save_request_kind; /* was D_80082BB4 */
extern u8   D_80082BC0;
extern u8   D_80082BE0[4];
extern u8   D_80082BE4[5];
extern void (*g_hotspot_fx_fns[])(s32 arg0); /* was D_80082BFC */
extern void (*g_ambient_fx_fns[])(void); /* was D_80082D60 */
extern void (*D_80082D90[])(void);
extern void (*g_record_start_handlers[])(void); /* was D_80082EA0 */
extern void (*g_record_dispatch_82ecc_tbl[])(void); /* was D_80082ECC */
extern void (*g_record_dispatch_82f40_tbl[])(void); /* was D_80082F40 */
extern void (*g_record_dispatch_82f70_tbl[])(void); /* was D_80082F70 */
extern s32  g_last_player_index; /* was D_80082FA0 */
extern s32  g_cur_view_player; /* was D_80082FA4 */
extern u8   D_80084064;
extern s32  g_vertex_anchor_template; /* was D_80084300 */
extern s16  D_80084480;
extern void (*D_800844B0[])(s32 arg0);
extern s32  g_dl_check_last_timg; /* was D_800848B0 */

extern f32 D_80085FD0;
extern f32 D_80085FD4;
extern f32 D_80085FD8;
extern f32 D_80085FDC;
extern f32 D_80085FE0;
extern f32 D_80085FE4;
extern f32 D_80085FE8;

extern f32 D_80085EB0;
extern f32 D_80085EB4;
extern f32 D_80085EB8;
extern f32 D_80085EBC;
extern u16 g_acos_table_coarse[]; /* was D_80085EC0 */
extern u16 g_acos_table_fine[]; /* was D_80085F3C */
extern u16 g_acos_table_finest[]; /* was D_80085FBC */

extern s32 g_obj_table_reset_word; /* was D_80086000 */
extern void (*D_80086004[])(s32);
extern void (*D_8008600C[])(s32);
extern void (*D_80086014[])(s32);
extern s16 g_carry_anim_ids[]; /* was D_800860C0 */
extern f32 g_carry_anim_speeds[]; /* was D_800860CC */
extern u16 g_carry_reaction_rows[]; /* was D_800860E4 */
extern void (*g_objev_action_fns[])(s32); /* was D_80086150 */
extern void (*g_aiscript_cmd_fns[])(void); /* was D_80086730 */
extern s8  g_player_start_lives; /* was D_80087260 */
extern s8  g_player_start_stat9; /* was D_80087264 */
extern s8  g_player_start_health; /* was D_8008726C */
extern s8  g_player_start_state[]; /* was D_80087270 */
extern u8  g_mp_level_mode_ids[]; /* was D_80087280 */
extern u32 g_link_group_count; /* was D_80087380 */

extern u64 D_800885B0;
extern struct127 *g_holder_target_obj; /* was D_80088720 */
extern struct127 *g_holder_obj; /* was D_80088730 */
extern s32 g_foot_splash_queue; /* was D_80088750 */
extern vertex g_holder_target_pos; /* was D_80088724 */
extern u8  D_80088980;
extern u8  g_storm_thunder_flag; /* was D_80088B40 */
extern void (*g_beam_free_fns[2])(void); /* was D_80088B60 */
extern u8  g_bone_beam_style_b; /* was D_80088B90 */
extern u8  g_weapon_c_bone; /* was D_80088BB0 */
extern s32 g_camera_frame_count; /* was D_800894B0 */
extern s32 D_80089520;
extern s32 D_80089524[]; // struct arrays?
extern s32 D_80089534[];
extern s16 D_80089550;
extern void (*g_object_state_fns_a[10])(void); /* was D_80089AAC */
extern void (*g_object_state_fns_b[10])(void); /* was D_80089AD4 */
extern void (*g_object_mode_fns_a[])(void); /* was D_80089C44 */
extern void (*g_object_mode_fns_b[])(void); /* was D_80089C54 */
extern void (*g_sprite_fx_fns_a[])(void); /* was D_80089EE8 */
extern void (*g_sprite_fx_fns_b[])(void); /* was D_80089EF0 */
extern void (*g_effect3d_fns_a[])(void); /* was D_80089EF8 */
extern void (*g_effect3d_fns_b[])(void); /* was D_80089F2C */
extern void (*g_sprite_fx_msg_fns[])(s32, s32, u8); /* was D_80089F60 */
extern s32 D_8008A074[2];
extern struct32 g_interaction_handlers[]; /* was D_8008A0B4 */
extern s32  g_interaction_hook_fns[]; /* was D_8008A084 */
extern void (*g_effect_node_update_fns_b[])(struct260*); /* was D_8008A4E8 */
extern void (*g_effect_node_update_fns_a[])(struct260*); /* was D_8008A4C0 */
extern void (*g_effect_node_call_a_fns[])(struct260*); /* was D_8008A688 */
extern void (*g_effect_node_call_b_fns[])(struct260*); /* was D_8008A7B0 */
extern void (*g_effect_node_msg_fns[74])(struct260*, s32, u8); /* was D_8008A8D8 */
extern s32 (*g_effect_node_draw_fns[])(s32, struct260*, s16); /* was D_8008A670 */
/* P234: EU D_8008B490; every handler takes the struct225 (the asm keeps a0 = the object at the jalr) and the
   dispatcher light_ctrl_update tests the result (0 = destroy) */
extern s32  (*g_light_effect_update_fns[])(struct225 *); /* was D_8008B0F0 */
extern u8   (*D_8008B1F8[])(struct225*);
extern void (*g_light_destroy_fns[])(struct225*); /* was D_8008B208 */
extern void (*g_light_delete_fns[])(struct225*); /* was D_8008B2B0 */
extern s32 (*D_8008B36C[])(void);
extern s32 (*g_move_watch_fns[])(s32); /* was D_8008B370 */
extern void (*D_8008B374[])(s32);

extern struct115 g_node_type_update_fns[]; /* was D_8008B4A8 */
extern struct115 g_node_type_destroy_fns[]; /* was D_8008B4D0 */
extern struct115 g_node_type_delete_fns[]; /* was D_8008B4D4 */


extern u8   g_ambient_flame_queue_count; /* was D_8008CEB0 */
extern u8   D_8008CD00;
extern s32  g_flare_level_points[]; /* was D_8008CFFC */

extern s8   g_player_count; /* was D_8008FD8C */
extern s8   g_human_player_count_us; /* was D_8008FD90 */
extern s32  D_8008FD94;
extern s8   g_save_cur_slot; /* was D_8008FDA8 */
extern u16  D_8008FDBC;

/* 8009 */
extern s32 g_tex_scroll_id_02b8; /* was D_800902B8 */
extern s32 g_tex_scroll_id_02e4; /* was D_800902E4 */
extern s32 g_level_scroll_tex_a; /* was D_800902E8 */
extern s32 g_tex_scroll_id_02ec; /* was D_800902EC */
extern s32 g_tex_scroll_id_0310; /* was D_80090310 */
extern s32 g_tex_scroll_id_0314; /* was D_80090314 */
extern s32 g_tex_scroll_id_0318; /* was D_80090318 */
extern s32 g_tex_scroll_id_031c; /* was D_8009031C */
extern s32 g_level_scroll_tex_b; /* was D_80090320 */

extern s32 jtbl_80091A30[];

extern s32 g_text_icon_b9[]; /* was D_80091AF0 */
extern s32 g_level_collision_buf_sizes[]; /* was D_80091C04 */
extern s32 D_80091D20[];

// chunk0 data starts at rom 0x80082B20
// this chunk0 data
// D_800959E0 is 0x80082B20 + 0x00012ec0

extern f32 D_80095B10;
extern f32 D_80095B14;
extern f32 D_80095B18;
extern f32 D_80095B1C;
extern f32 D_80095B20;
extern f32 D_80095B24;
extern u8  g_hotspot_light_levels[]; /* was D_80095B27 */
extern f32 D_80095B28;
extern f32 D_80095B2C;
extern f32 D_80095B30;
extern f32 D_80095B40;
extern f32 D_80095B44;
// hotspot_fx_type24_27 suggests they are u8, but they look like floats!
extern u8 g_area_drift_speed_k[]; // 0.002188183832913637 /* was D_80095B48 */
extern u8 g_area_drift_param_48[]; // 20.100000381469727 /* was D_80095B4C */
extern u8 g_area_drift_param_64[]; // 0.4000000059604645 /* was D_80095B50 */

extern f32 D_80095B54;
extern u8  g_hotspot_swing_lamp_presets[4]; /* was D_80095B70 */
extern u8  g_hotspot_flash_presets[2]; /* was D_80095B74 */
extern f32 D_80095BB8;
extern f32 D_80095BBC;
extern f32 D_80095BC0;
extern f32 D_80095BC4;
extern f32 D_80095BC8;
extern f32 D_80095BCC;
extern f32 D_80095BD0;
extern f32 D_80095BD4;
extern f32 D_80095BD8;

extern f32 D_8009616C;
extern f32 D_80096170;
extern f32 D_80096174;
extern f32 D_80096178;
extern f32 D_8009617C;
extern f32 D_80096180;
extern f32 D_80096184;

extern f32 D_800961A8;
extern f32 D_800961AC;
extern f32 D_800961B0;
extern f32 D_800961B4;
extern f32 D_800961B8;
extern f32 D_800961BC;
extern f32 D_800961C0;

extern s32 D_80096210;
extern f32 D_80096214;
extern f32 D_80096218;
extern f32 D_8009621C;
extern f32 g_scroll_fx_pt0_x; /* was D_80096220 */
extern f32 g_scroll_fx_pt0_y; /* was D_80096224 */
extern f32 g_scroll_fx_pt0_z; /* was D_80096228 */
extern f32 g_scroll_fx_pt1_x; /* was D_8009622C */
extern f32 g_scroll_fx_pt1_y; /* was D_80096230 */
extern f32 g_scroll_fx_pt1_z; /* was D_80096234 */
extern f32 g_scroll_fx_pt2_y; /* was D_80096238 */
extern f32 g_scroll_fx_pt3_x; /* was D_8009623C */
extern f32 g_scroll_fx_pt3_y; /* was D_80096240 */
extern f32 g_scroll_fx_pt3_z; /* was D_80096244 */

extern f32 *D_800963A0;
extern struct180 *g_level_rope_def; // 6 x s32? /* was D_80096430 */

extern f32 g_ground_emitter7_param_8; /* was D_80096530 */
extern f32 g_ground_emitter7_param_c; /* was D_80096534 */

extern f32 g_ambient_fx4_param_1c; /* was D_80096540 */

extern f32 D_80096560;
extern f32 D_80096570;
extern u32 D_8009667C;
extern f32 D_800968B0;
extern f32 g_level_init_heading_f; /* was D_800968C0 */
extern s32 D_800968E0;
extern f32 g_debris_linked_zone_pos; /* was D_80096900 */
extern f32 D_80096904;

extern f32 D_80098D90[];
extern f32 D_80098DB0; // 0.008726646192371845
extern f32 D_80098DB4; // 0.008726646192371845

extern f32 D_800990B0; // 0.6931471824645996f
extern f32 D_800990B4; // 0.6931471824645996f
extern s8  D_80099140[];
extern u16 g_explosion_sfx_ids[6]; /* was D_8009919C */
extern f32 D_800991A8;
extern f32 D_800991AC;
extern f32 D_800991B0;
extern f32 D_800991D4; // 0.10000000149011612f
extern f32 D_80099408;
extern f32 g_asinf_near1_q; /* was D_8009940C */
extern f32 D_80099410;
extern f32 D_80099414;
extern f32 D_80099418;
extern f32 D_8009941C; // 0.949999988079071

extern f32 D_80099440; // 0.10000000149011612f
extern f32 D_80099444;
extern f32 D_80099448;
extern f32 D_8009944C;
extern f32 D_80099468;
extern f32 D_8009946C;
extern f32 g_walk_slide_push_k; /* was D_80099470 */
extern f32 D_80099474;
extern f32 D_80099478;
extern f32 D_8009947C;
extern f32 D_80099480;
extern f32 D_80099484;
extern f32 D_800994A4;
extern f32 D_800994A8;
extern f32 D_800994AC;
extern f32 D_800994B0;
extern f32 D_800994B4;
extern f32 D_800994B8;
extern f32 D_800994BC;
extern f32 D_800994D4; // 0.6000000238418579f
extern f32 D_800994D8; // 10430.3779296875f
extern f32 D_8009950C;
extern f32 D_80099510;
extern f32 D_80099514;
extern f32 D_80099520;
extern s16 D_80099A3C[];
extern s16 D_80099A3E;
extern u8  D_80099A43;
extern s16 D_80099AB4[];
extern s16 D_80099ABC[];

extern f32 g_screen_flash_b_effect; /* was D_80099C1C */
extern f32 D_80099C34;
extern f32 D_80099C38;
extern f32 D_80099C3C;
extern f32 D_80099C40;
extern f32 D_80099C44;

extern f32 D_80099D44;
extern f32 D_80099D4C;
extern f32 D_80099DA0;
extern f32 D_80099DA4;
extern f32 D_80099DA8;

extern f32 D_80099E98;
extern f32 D_80099E9C;

extern f32 D_80099F30;
extern f32 D_80099F4C;

extern f32 D_8009A020[];
extern f32 D_8009A0E8;
extern f32 D_8009A0EC;
extern f32 D_8009A0F0;
extern f32 D_8009A0F4;
extern f32 D_8009A0F8;
extern f32 D_8009A0FC;
extern f32 D_8009A100;
// code_75400.c
extern f32 g_aiscript_speed_boost; /* was D_8009A13C */ // 1.399999976158142
extern f32 D_8009A140;
extern f32 D_8009A144;
extern f32 g_aiscript_find_max_dist; /* was D_8009A148 */
extern f32 D_8009A1E4;

extern f32 D_8009A220[];
extern f32 D_8009A420[];
extern f32 D_8009A620[];
extern struct253 g_hit_desc_table[]; /* was D_8009A6D8 */
extern struct252 g_hit_sender_default; /* was D_8009A9F8 */

extern s16 D_8009DCB4[];
extern s32 D_8009DCC0;
extern s32 D_8009DCC4;
extern s32 D_8009DCD4;
extern s32 D_8009DCD8;
extern s32 g_face_anim_default_body; /* was D_8009DCE0 */

extern s32 D_8009DCCC;

extern f32 D_8009F6C0; // 0.01745329238474369f

/* 800A0000 */
extern f32 D_800A028C;
extern f32 D_800A0288;
extern f32 D_800A0290;
extern f32 g_skel_line_pts_a; /* was D_800A0310 */
extern f32 D_800A0314;
extern f32 D_800A1B80;
extern f32 D_800A1B8C;
extern f32 D_800A1B98;
extern f32 D_800A1B9C;
extern f32 D_800A1BA0;
extern f32 g_bone_beam_b_start; /* was D_800A1FB0 */
extern f32 g_bone_beam_b_end; /* was D_800A1FBC */
extern f32 g_bone_beam_a_start; /* was D_800A2148 */
extern f32 g_bone_beam_a_end; /* was D_800A2154 */
// extern struct201 D_800A2CD0[];
extern u8  D_800A2CD0[][3];

extern u8 g_str_blood_power[]; // "power" /* was D_800A3FB4 */
extern u8 g_str_blood_c_path[]; // "../Effects/Blood/blood.c" /* was D_800A3FBC */
extern s32 g_effect3d_default_params; /* was D_800A4AA0 */ //?
extern f32 g_fx_broadcast_types_a; /* was D_800A5168 */
extern f32 g_fx_broadcast_types_b; /* was D_800A5178 */
extern f32 D_800A45B4;
extern f32 D_800A5644;
extern f32 D_800A56A8;
extern f32 D_800A56AC;
extern f32 D_800A56B4;
extern f32 D_800A56B8;
extern f32 D_800A56BC; // 57.2957763671875
extern f32 D_800A56C0;
extern f32 D_800A56C4;
extern f32 D_800A56C8;
extern s32 g_effect_bcast_types; /* was D_800A5770 */

// in game_18D770.c
extern u8  g_str_light_scale[5];  // "scale" /* was D_800A6690 */
extern u8  g_str_light_c_path[24]; // "../Effects/Light/light.c" /* was D_800A6698 */
extern f32 D_800A66B4[3];  // { 0.0f, -415.0f, 0.0f }
extern f32 g_light_lightning_peaks[9];  // { 70.0f, 38.0f, 70.0f, 55.0f, 50.0f, 80.0f, 140.0f, 70.0f, 34.0f }; /* was D_800A66C0 */
extern s32 D_800A66E4[10]; // { 1099, 1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108 }
extern s32 g_light_joint_pulse_joints; /* was D_800A6A0C */
extern f32 D_800A6AD4;     // 0.005000000353902578f
extern f32 D_800A6AD8;     // 6.2831854820251465f
extern f32 D_800A6ADC;     // 0.10209999978542328f
extern f32 D_800A6AE0;     // 0.24889999628067017f
extern f32 D_800A6AE4;     // 0.07999999821186066f
extern f32 D_800A6AE8;     // 6.2831854820251465f
extern f32 D_800A6AEC;     // 0.07660000026226044f
extern f32 D_800A6AF0;
extern f32 D_800A6AF4;
extern f32 D_800A6AF8;
extern f32 D_800A6AFC;
extern s32 D_800A670C[][3]; // { {128.0f, 59.5f, 59.5f}, {187.0f, 59.5f, 59.5f}, {128.0f, 17.5f, 0.0f} }
extern s32 D_800A6730[][3];
extern f32 D_800A6754[];
extern f32 g_light_flicker_low_levels[24]; /* was D_800A6760 */
extern f32 g_light_flicker_mid_levels[24]; /* was D_800A67C0 */
extern f32 g_light_flicker_high_levels[24]; /* was D_800A6820 */
extern f32 g_fx_source_emitter_presets[]; /* was D_800A6880 */
extern f32 D_800A6894[];
extern f32 D_800A68A8[];
extern f32 D_800A68BC[];
extern f32 D_800A68D0[];
extern f32 D_800A68E4[];
extern f32 g_light_storm_flash_decay[3]; /* was D_800A68F8 */
extern f32 g_light_storm_pause_min[3]; /* was D_800A6904 */
extern f32 g_light_storm_pause_range[3]; /* was D_800A6910 */
extern s32 g_light_storm_burst_min[3]; /* was D_800A691C */
extern s32 g_light_storm_burst_range[3]; /* was D_800A6928 */
extern f32 g_light_storm_gap_min[3]; /* was D_800A6934 */
extern f32 g_light_storm_gap_range[3]; /* was D_800A6940 */
extern f32 g_light_storm_level_min[3]; /* was D_800A694C */
extern f32 g_light_storm_level_range[3]; /* was D_800A6958 */
extern f32 g_light_pulse_base_levels[14]; /* was D_800A6964 */
extern f32 g_light_pulse_amplitudes[14]; /* was D_800A699C */
extern f32 g_light_pulse_speeds[14]; /* was D_800A69D4 */

extern f32 D_800A6B00; // 6.2831854820251465f
extern f32 D_800A6B04; // 3.1415927410125732f
extern f32 D_800A6B08;
extern f32 D_800A6B0C;
extern f32 D_800A6B10;

extern u16 g_attach_fx_asset_ids[]; /* was D_800AB140 */
extern s32 D_800AB168[1];
// game_2062D0.c
extern u8  g_impact_puff_tex_kind0[3]; // 88, 64, 62 /* was D_800AB340 */
extern u8  g_impact_puff_tex_kind5[5]; // 46, 48, 45, 51, 52 /* was D_800AB344 */
extern u8  g_impact_puff_tex_kind11[4]; // 96, 97, 98, 99 /* was D_800AB34C */
extern s32 g_impact_debris_tex_kind0[7]; // 0, 1, 2, 58, 59, 60, 61 /* was D_800AB350 */
extern s32 g_impact_debris_tex_kind1[3]; // 15, 16, 17 /* was D_800AB36C */
extern s32 g_impact_debris_tex_kind3[2]; // 28, 29 /* was D_800AB384 */
extern s32 g_impact_debris_tex_kind2[3]; // 143, 144, 145 /* was D_800AB378 */
extern s32 g_impact_debris_tex_kind4[2]; // 8, 9 /* was D_800AB38C */
extern s32 g_impact_debris_tex_kind5[5]; // 49, 50, 51, 13, 14 /* was D_800AB394 */
extern s32 g_impact_debris_tex_kind6[3]; // 150, 151, 152 /* was D_800AB3A8 */
extern s32 g_impact_debris_tex_kind7[2]; // 27, 28 /* was D_800AB3B4 */
extern s32 g_impact_debris_tex_kind8[3]; // 160, 161, 162 /* was D_800AB3BC */
extern s32 g_impact_debris_tex_kind9[1]; // 179 /* was D_800AB3C8 */
extern s32 g_impact_debris_tex_kind10[3]; // 185, 186, 187 /* was D_800AB3CC */
extern s32 g_impact_debris_tex_kind11[4]; // 96, 97, 98, 99 /* was D_800AB3D8 */
extern f32 g_obj_ribbon_k_b3e8; /* was D_800AB3E8 */ // 0.0f;
extern f32 D_800AB3EC; //-1.0f

extern f32 D_800AB464;
extern f32 D_800AB468;
extern f32 g_impact_puff_size_factor; // 0.0003000000142492354f /* was D_800AB46C */
extern f32 g_destroy_burst_debris_scales; /* was D_800AB4C0 */
extern f32 D_800AB4C4;
extern f32 D_800AB4C8;
extern f32 D_800AB4CC;
extern f32 D_800AB4E4;
extern f32 D_800AB4E8;
extern f32 D_800AB4EC;
extern f32 g_destroy_burst_tex_params_a; /* was D_800AB4F0 */
extern f32 g_destroy_burst_tex_params_b; /* was D_800AB4F4 */

extern f32 D_800A5480;
extern f32 g_curve_table[]; /* was D_800A548C */

// end of data D_800B0DBC

/* 800B0000 */

extern s32  g_collision_buf_cursor; /* was D_800B0DC0 */
extern s32  g_collision_buf_start; /* was D_800B0DC4 */
extern s32  g_collision_buf_end; /* was D_800B0DC8 */
extern s32  g_quadtree_node_count; /* was D_800B0DCC */
extern s32  g_quadtree_leaf_count; /* was D_800B0DD0 */
extern s32  g_quadtree_min_half_size; /* was D_800B0DD4 */
extern u16  g_quadtree_leaf_max_tris; /* was D_800B0DD8 */
extern s32  D_800B0DDC;
extern u8  *g_quadtree_pool_cursor; /* was D_800B0DE0 */
extern s32  g_collision_total_tris; /* was D_800B0DE4 */
extern struct104 *g_level_header; /* was D_800B0DF0 */
// extern struct00 *g_level_part_dls;
extern s32 g_level_part_dls[]; /* was D_800B0E00 */
extern s32  D_800B0E04;

extern s32  D_800B0E30[];
extern u8   D_800B0E34[];

extern s32 g_texture_table_ids[7762]; /* was D_800B0E58 */

extern s32 D_800B87A0[];

extern u8  g_texture_table_flags[]; /* was D_800BC448 */

extern s32 g_ambient_slot_ids; /* was D_800BE4A0 */ // struct/array of size 0x3c
extern struct14 *g_level_scroll_handles; /* was D_800BE4F0 */
extern s32 D_800BE4E0;
extern u8  g_sky_segment_on[5]; /* was D_800BE500 */ // might be a struct?
extern s32 g_fb_ghost_image; /* was D_800BE570 */
extern u8  g_fb_ghost_alpha; /* was D_800BE574 */
extern u8  g_fb_ghost_pass; /* was D_800BE575 */
extern s32 g_pvs_stream; /* was D_800BE5D0 */
extern u8  g_game_loop_flag_5e0; /* was D_800BE5E0 */
extern u8  g_frame_delta; /* was D_800BE9A0 */
extern f32 g_frame_step_f; /* was D_800BE9A4 */
extern f32 D_800BE9A8;
extern s32 g_level_id; /* was D_800BE9F0 */


extern s32  D_800BE2B0[]; // type?
extern OSMesg  g_si_mesg_buf; /* was D_800BE2D0 */
extern u8   D_800BE358[8];
extern s8   D_800BE3D8;
extern s8   D_800BE3D9;
extern s8   D_800BE3DA;
extern s8   D_800BE3DB;
extern s16  D_800BE3DC;
extern u8   D_800BE3DE;
extern u8   g_save_resume_level; /* was D_800BE3DF */
extern u8   D_800BE3E0;
extern s32  g_save_play_time; /* was D_800BE3E8 */
extern u8   g_save_request_slot; /* was D_800BE3EC */
extern struct162 *D_800BE3F8;

extern u8   D_800BE614;
extern u8   D_800BE615;
extern u8   g_mp_mode_active; /* was D_800BE616 */
extern u8   D_800BE617;
extern s8   D_800BE618;
extern s32  g_framebuffer_width; /* was D_800BE620 */
extern s32  g_framebuffer_height; /* was D_800BE624 */
extern s32  g_player_cams; /* was D_800BE628 */ //[]; // contains structs size 0x180
extern s32  D_800BE62C;
extern u8   D_800BE635;
extern s32  D_800BE638;
extern s32  D_800BE63C[];
extern s32  D_800BE650;
extern s32  D_800BE654[];
extern f32  D_800BE6B8;
extern struct156 D_800BE760[];
extern OSMesgQueue g_si_mesg_queue; /* was D_800BE900 */
extern u8   g_rumble_probe_request; /* was D_800BE938 */
extern s32  g_gfx_dl_ptr; /* was D_800BE9D0 */
extern s32  g_gfx_dl_frame_starts[]; /* was D_800BE9D8 */

extern u8   D_800BE93C[];

extern struct_eu_save g_save_config; /* was D_800BE710 */
extern u16  g_cont_forced_buttons[]; /* was D_800BE720 */
extern s32  g_cont_frame[]; /* was D_800BE728 */
extern u8   g_vtx_colour_group_backup[]; /* was D_800BE940 */
extern u8   g_vtx_colour_room_base[]; /* was D_800BE944 */
extern u8   g_vtx_colour_stored[]; /* was D_800BE948 */
extern f32  g_level_env_colours_rgb[]; /* was D_800BE950 */
extern f32  D_800BE960[];
extern f32  g_level_env_colour_cmds[]; /* was D_800BE970 */
extern f32  D_800BE980[];

extern OSMesg      D_800BE990;
extern u8   g_level_first_frame; /* was D_800BE9B4 */
extern u8   g_dl_buf_index; /* was D_800BE9C0 */
extern s32  g_zbuffer_alias; /* was D_800BE9C4 */
extern s32  g_si_event_mesg; // OSMesg /* was D_800BE9E0 */
extern s32  g_frame_ticks; /* was D_800BE9E4 */
extern s32  D_800BE9E8;
extern u8   D_800BE9EC;
extern u8   g_level_load_white_fill; /* was D_800BE9ED */
extern u16  *g_level_load_id; // was u16 /* was D_800BE9F4 */
extern s32  g_level_loaded_id; /* was D_800BE9F8 */

extern struct14 g_cont_pad_ptrs; /* was D_800BE730 */
extern u16 g_pad_states[]; /* was D_800BE748 */
extern s32 g_cont_pad1; /* was D_800BE74E */
extern s32 g_cont_pad2; /* was D_800BE754 */
extern s32 g_cont_pad3; /* was D_800BE75A */

extern s32 g_frame_phase_accum[]; // struct04 /* was D_800BEA00 */
extern s32 D_800BEA04[]; // struct04
extern s32 g_frame_ticks_raw; /* was D_800BEA08 */
extern OSMesgQueue g_frame_dt_history_2; /* was D_800BEA10 */
extern OSMesg      D_800BEA28;
extern struct195  *g_view_widths_3; /* was D_800BEA68 */
extern u16 D_800BEAA8;
extern u8  D_800BEAAA;
extern u8  D_800BEAAB;
extern u8  g_game_paused; /* was D_800BEAC0 */
extern u8  g_pause_open; /* was D_800BEAC1 */

/* 800C0000 */

extern u16 D_800C18B8[];
extern u8  g_cutscene_pending; /* was D_800C35C4 */
extern u8  g_cutscene_pending_was_idle; /* was D_800C35C5 */
extern u8  g_cutscene_slot_state; /* was D_800C35EA */
extern struct168 *D_800C3600;
extern u8  g_cutscene_in_progress; /* was D_800C3638 */
extern s32 D_800C3654;
extern u8  g_cutscene_focus_set; /* was D_800C3663 */
extern u8  g_cutscene_treat_as_seen; /* was D_800C3670 */
extern u8  g_cutscene_restart_transition; /* was D_800C3671 */
extern u8  g_cutscene_hide_background; /* was D_800C3681 */
extern u8  g_cutscene_flat_background; /* was D_800C3682 */
extern u8  g_cutscene_no_pause; /* was D_800C3683 */
extern struct233 *g_cutscene_track_recs; /* was D_800C3958 */
extern u8  g_cutscene_skip_state; /* was D_800C3C88 */
extern u8  g_cutscene_load_callback; /* was D_800C3C90 */
extern s32 g_cutscene_load_callback_arg; /* was D_800C3C94 */
extern struct163 g_subtitle_slots[3]; /* was D_800C3CA0 */
extern u8  g_cur_obj_index; /* was D_800C3E78 */
extern u16 g_matrix_arena_count; /* was D_800C3E7C */
extern s32 g_matrix_arena_a; /* was D_800C3E80 */
extern s32 g_matrix_arena_b; /* was D_800C3E84 */
extern s32 g_attachment_list; /* was D_800C3EE0 */
extern struct222* g_vertex_anchor_blocks; /* was D_800C3FC0 */
extern s32 D_800C3FC4;
extern s64 g_save_level_bits[]; /* was D_800C3A60 */
extern u8  g_tail_reset_mask; /* was D_800C4000 */

extern s16 g_model_anim_counts[187]; /* was D_800C5A90 */ // 374 bytes, 187 shorts
extern s32 g_model_vtx_ranges[187]; /* was D_800C5C08 */
extern s32 g_model_coll_tris[187]; /* was D_800C6070 */
extern s32 g_model_vtx_ptr_tables[187]; /* was D_800C6360 */

extern struct160 D_800C6650[];
extern s32 D_800C6654;
extern struct106 g_breakable_slots[]; /* was D_800C6660 */
extern u8  g_obj_flagged_pending; /* was D_800C67F0 */
extern u8  g_obj_flagged_select_idx; /* was D_800C67F1 */
extern s32 g_dl_check_segments[]; /* was D_800C6860 */
extern u8  g_dl_check_drawn_flag; /* was D_800C68A0 */
extern u8  g_dl_check_depth; /* was D_800C68A1 */

extern s32 g_timedfx_list; /* was D_800CBE00 */
extern u8  g_text_color_r; /* was D_800CBD60 */
extern u8  g_text_color_g; /* was D_800CBD61 */
extern u8  g_text_color_b; /* was D_800CBD62 */
extern u8  g_text_color_a; /* was D_800CBD63 */
extern s32 g_text_queue_head; /* was D_800CBD64 */
extern s16 g_text_pos_x; /* was D_800CBD70 */
extern s16 g_text_pos_y; /* was D_800CBD72 */
extern u8  g_text_flags; /* was D_800CBD74 */
extern u32 g_text_anchor_obj; /* was D_800CBD78 */
extern s16 g_text_anchor_yoff; /* was D_800CBD7C */

extern f32 g_text_scale; /* was D_800CBD80 */

extern f32 D_800CC210;
extern f32 g_wall_ledge_h_neg; /* was D_800CC214 */
extern f32 g_wall_ledge_h_pos; /* was D_800CC218 */
extern f32 g_wall_ledge_grab_x; /* was D_800CC21C */
extern f32 D_800CC220;
extern f32 D_800CC224;
extern f32 D_800CC228;
extern f32 D_800CC22C;
extern f32 g_gfx_dram_stack; /* was D_800CC230 */
extern f32 D_800CC234;
extern f32 D_800CC238;
extern f32 D_800CC23C;

extern s32 D_800CC250;

extern s16 g_obj_time_step_pct; /* was D_800CC264 */
extern s32 g_obj_contact_mask; /* was D_800CC268 */
extern u8  g_records_game_mode; /* was D_800CC26E */
extern u8  D_800CC27C;
extern s32 D_800CC280;
extern s32 D_800CC284; //pointer to 6 u8s
extern s32 g_cur_buttons_pressed; /* was D_800CC288 */
extern s32 g_obj_anim_shared; /* was D_800CC298 */ // 0x18 length
extern u8  g_records_flag_2a2; /* was D_800CC2A2 */

extern f32 g_hit_point_x; /* was D_800CC2C0 */
extern f32 g_hit_point_y; /* was D_800CC2C4 */
extern f32 g_hit_point_z; /* was D_800CC2C8 */

extern u8  g_obj_pending_actions; /* was D_800CC2B0 */
extern u8  D_800CC2B8;
extern s32 D_800CC2BA;
extern s32 D_800CC2BC;
extern struct127 g_objects[26]; // objects /* was D_800CC2D0 */
extern u8  g_objects_id[]; /* was D_800CC2D4 */
extern f32 g_objects_y[]; /* was D_800CC2E8 */
extern f32 g_objects_xz_velocity[]; /* was D_800CC30C */
extern u8  g_objects_parent_slot; /* was D_800CC335 */
extern u16 D_800CC34A[];
extern u8  g_objects_in_water; /* was D_800CC37D */
extern u8  g_objects_stunned[]; /* was D_800CC3D4 */
extern s8  g_objects_107; /* was D_800CC3D7 */
extern u8  g_objects_immune[] ; /* was D_800CC3F5 */ // ??

extern struct127  g_objects_2d0[]; /* was D_800CC5A0 */
extern u8  g_objects_counter_251[]; /* was D_800CC521 */ // ??

extern struct127 *D_800CE370;

/* 800D0000 */

extern s32 g_obj_scratch_rec; /* was D_800D121C */
extern f32 g_obj_scratch_x; /* was D_800D1230 */
extern f32 g_obj_scratch_y; /* was D_800D1234 */
extern f32 g_obj_scratch_z; /* was D_800D1238 */
extern s16 g_obj_scratch_yaw; /* was D_800D1292 */
extern s16 D_800D1296;
extern s8  g_obj_scratch_d0; /* was D_800D12EC */
extern f32 g_obj_scratch_114; /* was D_800D1330 */
extern u8  g_obj_scratch_owner; /* was D_800D1340 */
extern s8  g_obj_scratch_13d; /* was D_800D1359 */
extern f32 g_obj_scratch_xz_scale; /* was D_800D1368 */
extern f32 g_obj_scratch_y_scale; /* was D_800D136C */

extern s32 g_obj_scratch_links; /* was D_800D1510 */
extern f32 g_obj_time_step[]; /* was D_800D1550 */
extern s32 g_cur_obj_cmd; // array? /* was D_800D1580 */
extern s16 g_cur_obj_cmd_sound; /* was D_800D1582 */
extern u8  g_cur_obj_cmd_setup_id; /* was D_800D1583 */
extern s32 g_model_anim_banks[187]; /* was D_800D1588 */ // 748 bytes
extern s32 D_800D1548;
extern struct127 *g_cur_obj; /* was D_800D154C */

extern f32 g_anim_event_fparam; /* was D_800D1874 */
extern f32 g_anim_event_result; /* was D_800D1878 */
extern s32 g_anim_event_continue; /* was D_800D1880 */
extern u8  g_aiscript_arg0; /* was D_800D1890 */
extern u8  g_aiscript_arg1; /* was D_800D1891 */
extern u8  g_aiscript_arg2; /* was D_800D1892 */
extern u8  g_aiscript_arg3; /* was D_800D1893 */
extern f32 g_aiscript_values[]; /* was D_800D1898 */
extern u16 g_player_view_hidden_mask; /* was D_800D18A0 */
extern u16 g_player_mask_18a2; /* was D_800D18A2 */
extern s32 g_player_state_18a4; /* was D_800D18A4 */
extern u8  g_mp_respawning; /* was D_800D18A8 */
extern u8  g_idle_request_flags; /* was D_800D18C0 */
extern u8  g_lipsync_obj_idx; /* was D_800D18D0 */

extern u8  g_hint_action; /* was D_800D1940 */
extern u8  g_hint_box_open; /* was D_800D1941 */
extern s32 g_hint_text_asset; /* was D_800D1944 */
extern s32 g_hint_intro_asset; /* was D_800D1948 */
extern s32 g_hint_text_buf; /* was D_800D194C */
extern s32 g_hint_text_box; /* was D_800D1950 */
extern s32 g_hint_box_params[12]; /* was D_800D1958 */ // 48 bytes long, struct?
extern f32 g_hint_box_x; /* was D_800D1988 */
extern f32 g_hint_box_y; /* was D_800D198C */
extern f32 g_hint_box_scale; /* was D_800D1990 */
extern u8  g_hint_voice_pos; /* was D_800D1994 */
extern u8  g_hint_voice_count; /* was D_800D1995 */
extern s32 g_hint_voice_queue; /* was D_800D1998 */

extern s32 g_model_bases; /* was D_800D19A0 */
extern struct124 *g_type_descs[187]; /* was D_800D1C90 */ // 748 bytes, 187 pointers? 17 structs?
extern s32 g_model_slot_users[187]; /* was D_800D1F80 */ // 187 bytes long
extern s32 g_model_slot_timers[187]; /* was D_800D2040 */ // 187 bytes long
extern struct258 *g_setup_entries; /* was D_800D20FC */

extern s32 *g_path_points; /* was D_800D2104 */
extern u8  D_800D2108[];
extern s16 D_800D2110[];
extern s32 g_start_point_mask; /* was D_800D2120 */
extern s32 g_start_point_team_mask; /* was D_800D2124 */
extern s32 g_start_point_count; /* was D_800D2128 */
extern struct187 *g_start_points; /* was D_800D212C */
extern u16 g_transition_air_time; /* was D_800D2132 */
extern s32 g_session_game_mode; /* was D_800D2138 */

extern s16 g_player_active_mask; /* was D_800D2340 */
extern u8  g_game_state_u8_23a9; /* was D_800D23A9 */
extern s32 g_link_groups; /* was D_800D23C0 */
extern s32 D_800D23D0;

extern f32 g_hud_health_piece_scales[]; /* was D_800D2410 */
extern f32 D_800D2428[3];
extern f32 D_800D2438[3];
extern s32 D_800D2444;
extern s32 g_hud_clock_dl; /* was D_800D2448 */
extern s32 g_hud_clock_mtx; /* was D_800D244C */
extern u8  D_800D2454;
extern u8  g_hud_health_max_pieces; /* was D_800D2456 */
extern u8  g_hud_health_shown_pieces; /* was D_800D2457 */
extern u8  g_hud_clock_enabled; /* was D_800D2458 */
extern struct256 *g_hud_health_drop_list; /* was D_800D245C */
extern u8  D_800D2460[][16];
extern u8  D_800D246D;
extern u8  D_800D247D;
extern s32 g_level_reset_2548; /* was D_800D2548 */
extern s32 D_800D2588;
extern u8  g_hud_health_piece_mtx; /* was D_800D2590 */
extern s32 D_800D24C0;
extern s32 D_800D24C8;

extern struct17 g_hud_health_rot_vel; /* was D_800D2890 */

extern u8  D_800D2C68;
extern s32 D_800D2C28;
extern s32 D_800D2C2C;

extern s32 g_level_state_blk_2e50; /* was D_800D2E50 */
extern u8  g_hints_seen[]; /* was D_800D2E60 */
extern u8  g_hints_seen_b8; /* was D_800D2E68 */
extern s32 g_event_states; /* was D_800D2E70 */ // struct/array of size 0xF0
extern u8  g_level_state_u8_2e41; /* was D_800D2E41 */
extern u8  g_level_state_u8_2e42; /* was D_800D2E42 */
extern u8  g_game_over_pending; /* was D_800D2E43 */
extern u8  g_game_over_disabled; /* was D_800D2E44 */
extern u8  g_save_default_flag_2e45; /* was D_800D2E45 */
extern struct102 *g_save_progress_bits; /* was D_800D2E4C */

extern u8  g_level_event_count; /* was D_800D2F3C */
extern u16 *g_level_event_ids; /* was D_800D2F40 */
extern struct250 g_event_list; /* was D_800D2F48 */ // bzero'd 0xC
extern f32 g_camera_event_heading; /* was D_800D2DB0 */
extern s32 g_camera_timed_active; /* was D_800D2DB4 */

extern s32 g_level_zone_count; /* was D_800D3094 */
extern struct178 g_sprite_rect_left[73]; /* was D_800D3098 */
extern struct00 *D_800D3300;
extern s32 D_800D35DC;
extern s32 g_level_tri_vis_flags; /* was D_800D3668 */
extern s32 D_800D366C;
extern f32 D_800D3670;
extern s16 g_camera_dir_y_bound; /* was D_800D3674 */
extern s32 g_event_vm_abort; /* was D_800D3858 */

extern s32 g_level_timed_queue; /* was D_800D98E0 */
extern u8  g_record_flag_d987c; /* was D_800D987C */
extern u8  D_800D9890;

extern u8  D_800D9930[];
extern u8  D_800D9920;
extern u8  D_800D9921;
extern u8  D_800D9928;
extern u8  D_800D9929;
extern u8  D_800D9938;
extern u8  D_800D9939;
extern u8  D_800D992A[];
extern u8  D_800D993A[];

extern s32 g_zap_bolts[8]; /* was D_800D99D0 */
extern struct134 *g_spawn_region_pair; /* was D_800D9A20 */
extern struct134 *g_spawn_region_record_1; /* was D_800D9A24 */
extern s32 g_cam_zone_leaf; /* was D_800D9A40 */
extern s32 D_800D9A50;
extern struct134 *g_view_sparkle_spots[]; // length 3? /* was D_800D9AA0 */
extern u16 g_sfx_cooldowns[4]; /* was D_800D9AB0 */
extern struct17 D_800D9AC0[];
extern u8 D_800D9AF0;
extern struct200 D_800D9AF8[];

extern u8  D_800D9B18;
extern f32 D_800D9B1C;
extern f32 D_800D9B20;
extern u8  D_800D9B68[4][3];
extern u8  D_800D9B78[4][3];
extern u8  D_800D9B84[];
extern u8  D_800D9B88[];
extern u8  D_800D9B8B;
extern u8  D_800D9B8C;
extern u8  D_800D9BD0[][2][8];
extern s32 g_cam_point_ahead[]; /* was D_800D9E10 */
extern u8  D_800D9E20;

// extern u16 g_aim_vec_scratch[][3];
// extern u8 D_800D9E88[][3];
// extern u8 D_800D9E98[][3];
// extern u8 D_800D9EA8[][3];
// extern u8 D_800D9EB4[][3];
// extern u8 D_800D9EB8[][3];
//
// extern u8 D_800A2D04[][3];
// extern u8 D_800A2CE8[][3];
// extern u8 D_800A2CEC[][3];

extern s32 g_ambient_cue_timer[]; /* was D_800D9D10 */
extern u8  g_tex_scroll_count; /* was D_800D9E64 */
extern s32 g_texture_last_id_a; /* was D_800D9F58 */
extern s32 g_texture_last_id_b; /* was D_800D9F5C */
extern u8  g_texture_level_mode; /* was D_800D9F60 */

extern s32 D_800DBDD8[];
extern s32 D_800DBDE8[];
extern s32 D_800DBDF8[];

extern u16* g_quadtree_roots[]; /* was D_800DBE08 */
extern s32 g_coll_area_tri_counts[]; /* was D_800DBE18 */
extern s32 g_collision_area_tris_1[]; /* was D_800DBE1C */
extern s32 g_collision_area_tris_2; /* was D_800DBE20 */
extern s32 g_collision_area_tris_3; /* was D_800DBE24 */
extern s16 g_pvs_row_bytes; /* was D_800DBE28 */
extern s16 g_quadtree0_node_count; /* was D_800DBE2A */
extern s16 g_quadtree0_leaf_count; /* was D_800DBE2C */
extern u16 D_800DBE30;
extern u16 D_800DBE32;
extern u16 D_800DBE34;
extern u16 D_800DBE36;
extern s32 g_collision_area_tri_count; /* was D_800DBE38 */
extern s32 D_800DBE3C;
extern s32 g_coll_tri_count; /* was D_800DBE4C */
extern s32 D_800DBE50;
extern s32 g_coll_tri_flags; /* was D_800DBE5C */
extern u8  g_coll_quadtrees_built; /* was D_800DBE62 */
extern u8  g_collision_full_bounds; /* was D_800DBE63 */
extern f32 g_collision_floor_step; /* was D_800DBE64 */
extern s32 D_800DBEF0;
extern struct131 *g_world_objs; /* was D_800DBEF4 */ // ???
extern s32 D_800DBEF8[];
extern s8  D_800DBEFC[];
extern u8  g_world_obj_level_count; /* was D_800DBF00 */
extern u8  g_world_obj_selected; /* was D_800DBF88 */
extern s32 g_world_obj_selected_1c; /* was D_800DBF8C */
extern s32 g_world_obj_selected_28; /* was D_800DBF90 */
extern struct108 *g_player_views; /* was D_800DBFF0 */
extern u8  g_camera_timers[]; /* was D_800DBFF4 */
extern u8  D_800DBFF5;
extern u8  D_800DBFF6;
extern u8  D_800DBFF7;

extern s32  D_800DC010;
extern s32 D_800DC020;
extern struct10 *g_coll_probe_z; /* was D_800DC2A0 */ // TODO: find correct struct
extern s32 g_sky_asset; /* was D_800DC2B0 */
extern f32 *D_800DCC10[][4];
extern s32 g_mdl_particle_list_head; /* was D_800DC460 */
extern s32 g_mdl_particle_list_tail; /* was D_800DC464 */
extern u16 g_mdl_particle_model_users[]; /* was D_800DC468 */
extern s32 g_mdl_particle_live_count; /* was D_800DC63C */
extern u8  g_level_light_dirs; /* was D_800DCD30 */
extern u8  g_level_light_dirs_0y; /* was D_800DCD31 */
extern u8  g_level_light_dirs_0z; /* was D_800DCD32 */
extern u8  g_level_light_dirs_1x; /* was D_800DCD33 */
extern u8  g_level_light_dirs_1y; /* was D_800DCD34 */
extern u8  g_level_light_dirs_1z; /* was D_800DCD35 */
extern u8  g_level_light_dirs_2x; /* was D_800DCD36 */
extern u8  g_level_light_dirs_2y; /* was D_800DCD37 */
extern u8  g_level_light_dirs_2z; /* was D_800DCD38 */
extern u8  g_level_light_dirs_3x; /* was D_800DCD39 */
extern u8  g_level_light_dirs_3y; /* was D_800DCD3A */
extern u8  g_level_light_dirs_3z; /* was D_800DCD3B */
extern u8  g_level_tint_strength_b; /* was D_800DCD3C */
extern u8  g_level_tint_strength_a; /* was D_800DCD3D */
extern s32 g_light_cmd_data; /* was D_800DCD40 */
extern s32 g_light_list_head; /* was D_800DCD78 */
extern s32 g_light_vertex_lighting; /* was D_800DCD7C */
extern s32 g_light_colour_zones; /* was D_800DCD80 */
extern s32 g_light_tint_zones; /* was D_800DCD84 */
extern f32 g_light_list_weight; /* was D_800DCD90 */
extern f32 g_level_colour_ease_r; /* was D_800DCD94 */
extern f32 g_level_colour_ease_g; /* was D_800DCD98 */
extern f32 g_level_colour_ease_b; /* was D_800DCD9C */
extern f32 g_level_colour_cycle; /* was D_800DCDA0 */

extern struct100 *g_level_light_colour; /* was D_800DCD20 */
// extern struct100 *g_level_light_dir;
// extern struct100 *g_level_tint_colour;

extern s8 g_level_light_dir[3]; /* was D_800DCD24 */
extern u8 g_level_tint_colour[3]; /* was D_800DCD28 */

extern s32  g_light_record_list; /* was D_800DCDC4 */ // probably wrong type
extern u8   g_level_lights_mode; /* was D_800DCDD0 */
extern s8   D_800DD190;
extern u8   D_800DD198[]; // 24 bytes
extern f32  g_rope_light_g[]; /* was D_800DD1D8 */
extern f32  g_rope_tint_b[]; /* was D_800DD1E8 */

extern u8   g_warp_entry_ids; /* was D_800DD2C0 */
extern u8   g_sun_flash_alpha; /* was D_800DD2D0 */
extern u8   g_particle_cooldown; /* was D_800DD2A0 */
extern u8   g_particle_cooldown_p1; /* was D_800DD2A1 */
extern u8   g_particle_cooldown_p2; /* was D_800DD2A2 */
extern u8   g_particle_cooldown_p3; /* was D_800DD2A3 */

extern u8   D_800DD404;
extern u8   D_800DD405;
extern u8   D_800DD406;
extern s32  g_vtx_anim_lights[2]; /* was D_800DD410 */
extern u8   g_vtx_anim_light_count; /* was D_800DD418 */
extern u16  g_rain_state_timer; /* was D_800DD444 */
extern s32  g_player_morph_caches[2]; /* was D_800DD460 */
extern s32  g_ambient_slots; /* was D_800DD478 */ // struct/array of size 0x618 (1560)

extern s32  g_ambient_voices; /* was D_800DDA90 */ // struct/array of size 0xf0
extern s32  g_ambient_alt_phase_slots; /* was D_800DDC00 */
extern s32  g_ambient_slow_random_slots; /* was D_800DDC08 */
extern s32  g_ambient_pingpong_slots; /* was D_800DDC04 */
extern s32  g_ambient_quad_bufs[]; /* was D_800DDD10 */
extern s32  g_ambient_quad_max; /* was D_800DDD0C */
extern u8   g_ambient_flame_phase; /* was D_800DDD1C */
extern s32  g_ambient_emitter_count; /* was D_800DDD20 */
extern u8   g_flare_state_byte; /* was D_800DDD61 */
extern s32  g_flare_nodes; /* was D_800DDD64 */

extern u8   g_screen_fade_dir; /* was D_800DDDAC */
extern u8   g_screen_fade_dir_p1; /* was D_800DDDAD */
extern u8   g_screen_fade_dir_p2; /* was D_800DDDAE */
extern u8   g_screen_fade_dir_p3; /* was D_800DDDAF */
extern s32  g_screen_fade_timer; /* was D_800DDDB0 */
extern s32  g_screen_fade_timer_p1; /* was D_800DDDB4 */
extern s32  g_screen_fade_timer_p2; /* was D_800DDDB8 */
extern s32  g_screen_fade_timer_p3; /* was D_800DDDBC */
extern f32  g_hud_lens_zoom; /* was D_800DDDC8 */
extern f32  g_hud_lens_zoom_p1; /* was D_800DDDCC */
extern f32  g_hud_lens_zoom_p2; /* was D_800DDDD0 */
extern f32  g_hud_lens_zoom_p3; /* was D_800DDDD4 */
extern f32  g_hud_lens_zoom_rate; /* was D_800DDDD8 */
extern f32  g_hud_lens_zoom_rate_p1; /* was D_800DDDDC */
extern f32  g_hud_lens_zoom_rate_p2; /* was D_800DDDE0 */
extern f32  g_hud_lens_zoom_rate_p3; /* was D_800DDDE4 */
extern u16  g_screen_pulse_timer; /* was D_800DDE08 */
extern s32  g_letterbox_track; /* was D_800DDE18 */
extern u8   g_hud_lens_mode; /* was D_800DDE1C */
extern u8   g_hud_lens_mode_p1; /* was D_800DDE1D */
extern u8   g_hud_lens_mode_p2; /* was D_800DDE1E */
extern u8   g_hud_lens_mode_p3; /* was D_800DDE1F */
extern u8   g_hud_lens_scripted; /* was D_800DDE20 */
extern u8   g_hud_lens_scripted_p1; /* was D_800DDE21 */
extern u8   g_hud_lens_scripted_p2; /* was D_800DDE22 */
extern u8   g_hud_lens_scripted_p3; /* was D_800DDE23 */
extern s32  g_screen_fade_duration_p1; /* was D_800DDE2C */
extern s32  g_screen_fade_duration; /* was D_800DDE28 */
extern s32  g_screen_fade_duration_p2; /* was D_800DDE30 */
extern s32  g_screen_fade_duration_p3; /* was D_800DDE34 */
extern u8   g_level_entry_zoom_mode; /* was D_800DDE38 */
extern u8   g_hud_lens_state; /* was D_800DDE3C */
extern u8   g_hud_lens_state_p1; /* was D_800DDE3D */
extern u8   g_hud_lens_state_p2; /* was D_800DDE3E */
extern u8   g_hud_lens_state_p3; /* was D_800DDE3F */
extern u8   g_hud_scope_scripted; /* was D_800DDE40 */
extern u8   g_area_points_count; /* was D_800DDE50 */
extern s32  g_anim_mesh_slots[55]; /* was D_800DDE80 */ // 220 bytes?

extern s32  g_afterimage_lists[]; /* was D_800DF7C8 */
extern u8   g_weather_slot_busy[]; /* was D_800DDF5C */
extern u8   g_weather_slot_timers[]; /* was D_800DDF60 */
extern s8   g_anim_mesh_state[]; /* was D_800DDF68 */
extern s32  g_anim_mesh_dls[]; /* was D_800DDF78 */

/* 800E0000 */
extern u8   g_game_mode; /* was D_800E0B94 */
extern s32  D_800E0C20;
extern s32  g_mp3_stream_state; /* was D_800E0E04 */
extern struct134 *g_emitter_owner_records[]; /* was D_800E0900 */ // probably not struct134
extern void *g_level_bullet_hit_cb; /* was D_800E0930 */
extern s32  D_800E0934;
extern void *g_world_obj_hit_cb; /* was D_800E0940 */
extern u8   g_attach_fx_asset_refs; /* was D_800E0950 */
extern s32  D_800E0964;
extern s16  g_attach_fx_point_counts[]; /* was D_800E0968 */
extern s32  g_attach_fx_assets[]; /* was D_800E0990 */
extern u8   g_level_proj_mode; /* was D_800E0A10 */
extern struct186 g_mp3_stream; /* was D_800E0D80 */ // libaudio struct?

// end of zero'd out section

extern s32  g_cheat_flags; /* was D_800E9D00 */
extern s32  *D_800E9D10; // probably not struct54

/* debugger variables */

extern s32  D_16001B8C; // a struct
extern s8   g_dbg_stick_y; // control stick Y-axis ? /* was D_160036F3 */
extern s32  g_dbg_exc_cause_names[]; /* was D_16003848 */
extern u8   g_dbg_fb_index; /* was D_16003888 */
extern u16  g_dbg_draw_color; /* was D_1600388C */
extern s32  g_dbg_first_text_row; /* was D_160038A0 */
extern u8   g_dbg_is_lockup; /* was D_160038A4 */
extern s32  g_dbg_fb_width; /* was D_160038A8 */
extern s32  g_dbg_buttons_pressed; /* was D_16003890 */
extern s32  g_dbg_fault_not_retryable; /* was D_16003AF0 */
extern u8   g_dbg_page; /* was D_16003AF4 */
extern s8   g_dbg_menu_cursor; /* was D_16003B1C */
extern s32  g_dbg_menu_item_strs[]; // array containing 0x20 structs? /* was D_16003B20 */
extern s8   g_dbg_regs_subpage; /* was D_16003B28 */
extern s32  g_dbg_stack_scroll; /* was D_16003B4C */
extern struct118 *g_dbg_fault_thread; // array or struct? /* was D_1600389C */

extern u8   g_dbg_str_title[]; // data /* was D_160046AC */
extern u8   g_dbg_str_main_menu[]; /* was D_160046D0 */
extern u8   g_dbg_str_menu_continue[]; /* was D_160046DC */
extern u8   g_dbg_str_menu_no_retry[]; /* was D_160046E8 */
extern u8   g_dbg_str_retry_code[]; /* was D_160046F4 */
extern u8   g_dbg_str_version[]; /* was D_16004700 */
extern u8   g_dbg_str_built[]; /* was D_16004708 */
extern u8   g_dbg_str_build_date[]; /* was D_16004710 */
extern u8   g_dbg_str_build_time[]; /* was D_1600471C */
extern u8   g_dbg_str_pc[]; /* was D_16004728 */
extern u8   g_dbg_str_cause[]; /* was D_1600472C */
extern u8   g_dbg_str_sr[]; /* was D_16004734 */
extern u8   g_dbg_str_badvaddr[]; /* was D_16004738 */
extern u8   g_dbg_str_thread[]; /* was D_16004740 */
extern u8   g_dbg_str_lockup_now[]; /* was D_16004748 */
extern u8   g_dbg_str_stack_title[]; /* was D_160047B0 */
extern u8   g_dbg_str_stack_addr_sep[]; /* was D_160047BC */
extern u8   g_dbg_str_stack_val_sep[]; /* was D_160047C0 */
extern u8   g_dbg_str_float_bad[]; /* was D_160047D0 */
extern u8   g_dbg_str_float_fmt[]; /* was D_160047D4 */
extern u8   g_dbg_str_float_arg_a[]; /* was D_160047DC */
extern u8   g_dbg_str_float_arg_b[]; /* was D_160047E0 */

/* EU: new decompilation (splat names, EU addresses) */

extern void (*g_node_end_handlers[])(void); /* was D_8008CDC0 */
extern u8   g_sprite_keep_prim_colour; /* was D_800D31CB */
extern f32  D_800A5A04;
extern f32  D_800A5A08;
extern f32  D_800A4C08;
extern struct_eu_node *g_node_lists[][104]; /* was D_800DD280 */
extern f32  g_cos_u8_table[]; /* was D_8009A5E0 */
extern f32  D_800A5A84;
extern f32  D_800A5AA4;
extern f32  D_800A5AA8;
extern struct_eu_bytes4 D_800AB548;
extern s16 *g_setup_respawn_timers; /* was D_800D2530 */
extern s8   g_node_iter_depth; /* was D_800DD5C0 */
extern struct_eu_node *g_node_iter_next[]; /* was D_800DD5C8 */
extern void (*g_node_global_hooks[3])(void); /* was D_8008CF04 */
extern void (*g_effect_retire_fns[])(structEU_16DC80 *); /* was D_8008A33C */
extern void (*g_effect_delete_fns[])(structEU_16DC80 *); /* was D_8008A384 */
extern structEU_8008A414 D_8008A414;
extern s32  g_particle_emitter_count; /* was D_800DCE20 */
extern void (*D_8008CF10[])(void);
extern u16  g_model_joint_counts[]; /* was D_800C52F0 */
extern s32  g_world_obj_count; /* was D_800DC320 */
extern s32 *g_world_obj_blocks; /* was D_800DC328 */
extern u8  *g_world_obj_block_timers; /* was D_800DC32C */
extern f32  g_quadtree_box_x; /* was D_800CC640 */
extern f32  g_quadtree_box_y; /* was D_800CC644 */
extern f32  g_quadtree_box_z; /* was D_800CC648 */
extern f32  g_quadtree_box_half_x; /* was D_800CC64C */
extern f32  g_quadtree_box_half_y; /* was D_800CC650 */
extern f32  g_quadtree_box_half_z; /* was D_800CC654 */
extern f32  g_quadtree_box_ratio_yx; /* was D_800CC658 */
extern f32  g_quadtree_box_ratio_zx; /* was D_800CC65C */
extern f32  g_quadtree_box_min_x; /* was D_80099430 */
extern s32  g_gfx_othermode_hi_cached; /* was D_800DD648 */
extern s32  g_gfx_othermode_lo_cached; /* was D_800DD64C */
extern u8   g_fx_random_colours[]; /* was D_8008A500 */
extern u8   g_dbg_str_fpcsr[]; /* was D_160047A4 */
extern u8   g_dbg_str_fpr_prefix[]; /* was D_160047AC */
extern s32  g_dbg_fpcsr_flag_names[]; /* was D_16003B30 */
extern u8   g_objects_event_id[]; /* was D_800CC82F */
extern u8   D_AB2240[]; // asset offsets table (EU address of US D_00AB1950)
extern struct_eu_words6 g_trigger_query_words6; /* was D_800A55E0 */
extern s32  g_gfx_geom_set_cached; /* was D_800DD62C */
extern s32  g_gfx_geom_clear_cached; /* was D_800DD630 */
extern f32  D_800A5A74;
extern u8   g_mtx_fixed_point; /* was D_800C42B0 */
extern f32  D_8009A10C;
extern f32  g_aiscript_hundredth; /* was D_8009A504 */
extern struct54 g_heap_start; /* was D_800EA140 */ // start of the heap managed by init_3C40
extern f32  D_8009A260;
extern u8  *g_path_point_counts; /* was D_800D2528 */
extern u8  *g_level_zones; /* was D_800D34B8 */
extern void (*g_effect_init_hooks_a[])(void); /* was D_80082F60 */
extern void (*g_effect_init_hooks_b[])(void); /* was D_80082F64 */
extern s32  g_tex_cache_last_addr; /* was D_800DD5E0 */
extern s16  g_gfx_env_r_cached; /* was D_800DD5F8 */
extern s16  g_gfx_env_g_cached; /* was D_800DD5FA */
extern s16  g_gfx_env_b_cached; /* was D_800DD5FC */
extern s16  g_gfx_env_a_cached; /* was D_800DD5FE */
extern s32 (*g_light_track_ptr_fns[])(void);           // EU address of US D_8008B36C /* was D_8008B70C */
extern void (*g_light_track_message_fns[])(struct225 *, s32, u8); /* was D_8008B370 */ // EU address of US g_move_watch_fns /* was D_8008B710 */
extern f32  D_800A5A78;
extern f32  D_800A5A7C;
extern f32  g_impact_ring_height_base; /* was D_800AB890 */
extern void (*g_light_obj_message_fns_a[])(struct225 *, void *, u8); /* was D_8008B714 */
extern void (*g_light_obj_message_fns_b[])(struct225 *, void *, u8); /* was D_8008B71C */
extern f32  g_fx_point_emitter_uc; /* was D_800A0650 */
extern f32  g_fx_point_emitter_u10; /* was D_800A0654 */
extern s32  g_random_joint_ids; /* was D_80099F78 */
extern u8   g_vs_player_fx_point[]; /* was D_80099F7C */
extern u8   g_vec3_zero[]; /* was D_800A5860 */
extern s16  g_gfx_prim_r_cached; /* was D_800DD5F0 */
extern s16  g_gfx_prim_g_cached; /* was D_800DD5F2 */
extern s16  g_gfx_prim_b_cached; /* was D_800DD5F4 */
extern s16  g_gfx_prim_a_cached; /* was D_800DD5F6 */
extern s16  g_gfx_prim_m_cached; /* was D_800DD634 */
extern s16  g_gfx_prim_l_cached; /* was D_800DD636 */
extern u8   g_hit_reaction_anims[][10]; /* was D_80099DFC */
extern f32  D_800A5850;
extern f32  D_800A5854;
extern u8   D_800DC425;
extern u8   D_800DC426[];
extern s32  g_collision_cur_area; /* was D_800DC280 */
extern s32  g_coll_area_tri_tables[]; /* was D_800DC208 */
extern s32  g_coll_area_xz_bounds[]; /* was D_800DC218 */
extern s32  g_coll_area_y_bounds[]; /* was D_800DC228 */
extern f32  D_8009A4A8;
extern f32  D_8009A4AC;
extern f32  D_8009A4B0;
extern f32  D_8009A4B4;
extern f32  D_8009A4B8;
extern f32  D_8009A4BC;
extern void (*g_bone_emitter_stop_fns_a[])(void *); /* was D_80089F10 */
extern void (*g_bone_emitter_stop_fns_b[])(void *); /* was D_80089F28 */
extern f32  D_8009A498;
extern u8   g_hit_kind_info[][16]; /* was D_800A43B8 */
extern f32  D_800A4990;
extern s32 (*g_mesh_effect_tick_fns[])(struct_eu_168A90 *); /* was D_80089FB8 */
extern f32  D_800A3900;
extern f32  D_80099460; // ln(2)?
extern f32  D_80099464;
extern u8   g_sprite_anim_table[][12]; /* was D_80090F14 */
extern s8   g_surface_lean_params[]; /* was D_800994F0 */
extern f32  D_80099588;
extern f32  g_rec_kind_effect_param; /* was D_80096A2C */
extern f32  g_frame_step_inv; /* was D_800BEDC8 */
extern u8   g_obj_half_rate_parity; /* was D_800CC6D8 */
extern s16  g_obj_half_rate_saved_ticks; /* was D_800CC6DA */
extern s32  g_mtx_xform_dbg_step; /* was D_800DCE30 */
extern void *g_mtx_xform_dbg_mtx; /* was D_800DCE34 */
extern f32  g_mtx_xform_dbg_x; /* was D_800DCE38 */
extern f32  g_mtx_xform_dbg_y; /* was D_800DCE3C */
extern f32  g_mtx_xform_dbg_z; /* was D_800DCE40 */
extern f32  D_8009A110;
extern f32  g_effect60_const_20; /* was D_80096A64 */
extern f32  D_800A49FC;
extern f32  D_800A4A00;
extern f32  g_anim_cmd_default_speed; /* was D_8009A108 */
extern u8   g_cutscene_scene; /* was D_800C3A08 */
extern f32  g_rec_scripted_param_scale; /* was D_80096A00 */
extern u8   g_save_restart_entry; /* was D_800BE800 */
extern void (*g_attach_ctrl_release_fns[])(struct_eu_1FFF60 *); /* was D_8008FFFC */
/* P241 (port-b P239): the NM dispatchers use the s32 results */
extern s32 (*g_attach_child_end_fns[])(struct_eu_1FFF60_child *, void *); /* was D_8008FFE8 */
extern struct_eu_80090F10 g_sprite_textures[]; /* was D_80090F10 */
extern f32  D_8009A4C8;
extern f32  D_8009A4CC;
extern f32  D_8009A4D0;
extern u8   g_idle_anims[]; /* was D_80099E74 */
extern u8   g_idle_anims_alt[]; /* was D_80099E7C */
extern f32  D_80099FF8;
extern struct17 g_light_rotated_offset; /* was D_800A6A94 */
extern f32  D_800A4D30;
extern f32  D_800A4D34;
extern f32  D_800A4D38;
extern f32  D_800A4D3C;
extern u8   g_impact_small_tex_ids[]; /* was D_800A4640 */
extern u8   g_impact_small_tex_scales[]; /* was D_800A4644 */
extern f32  D_800A06E0;
extern f32  D_800A06E4;
extern f32  g_spark_emit_speed_scale; /* was D_800A4A04 */
extern f32  g_spark_dust_size_scale; /* was D_800A4A08 */
extern f32  g_spark_dust_size_bias; /* was D_800A4A0C */
extern struct17 D_eu_800A6AEC[];
extern struct17 D_eu_800A6B10[];
extern f32  g_light_colour_pulse_speeds[]; /* was D_800A6B34 */
extern u8   g_save_config_data0; /* was D_800BE712 */
extern u8   g_save_config_data1; /* was D_800BE713 */
extern u8   g_save_config_data_rest[]; /* was D_800BE714 */
extern u8   g_save_slot_buf[]; /* was D_800BE778 */
extern s8   g_save_slot_kinds[]; /* was D_800BE7F8 */
extern struct54 *g_snd_cache_used_head; /* was D_80040A44 */ /* was D_800406A0 */ // g_snd_cache.unk4 (list head) in EU
extern struct54 *g_snd_cache_free_list; /* was D_80040A50 */ /* was D_800406A0 */ // g_snd_cache.unk10 (free list) in EU
extern s16  g_sprite_last_combine; /* was D_800DD5EE */
extern u8   g_combine_mode_table[][16]; /* was D_800A4F88 */
extern Gfx *g_gfx_dl_buffers[]; /* was D_800BEDE8 */
extern Gfx  g_dl_frame_init[]; /* was D_8002CC90 */
extern s32  g_zbuffer; /* was D_800BEDE4 */
extern f32  D_80096CB0;
extern f32  D_80096CB4;
extern f32  D_800A0638;
extern f32  D_800A063C;
extern f32  g_impact_cloud_size_range; /* was D_800AB844 */
extern f32  g_impact_cloud_size_min; /* was D_800AB848 */
extern s32 (*g_attach_child_update_fns[])(struct_eu_1FFF60_child *, void *); /* was D_8008FFE0 */
extern struct_eu_spawnlist g_owner_spawn_lists[]; /* was D_80088A80 */
extern u32  D_15001B08[];
extern f32  g_fx_debris_spray_scale; /* was D_800A0658 */
extern f32  g_fx_debris_dust_size_mul; /* was D_800A065C */
extern f32  g_fx_debris_dust_size_add; /* was D_800A0660 */
extern SaveSlotSummary g_save_slot_summaries[3]; /* was D_800BE818 */
extern s16  g_save_best_slot_score; /* was D_800BE7FC */
extern u8   g_save_final_scene_unlock; /* was D_800BE7FE */
extern u8   g_save_slot_refresh; /* was D_80082F50 */
extern s8   D_800BE7F9;
extern s8   D_800BE7FA;
extern s8   D_800BE7FB;
extern u8   g_game_flags_dirty; /* was D_800D3289 */
extern u8   g_glyph_count; /* was D_800CC16C */
extern s32  g_coll_counter_1bc; /* was D_800CC1BC */
extern s8  *g_race_state; /* was D_800D27D0 */
extern f32  D_800A8E84;
extern f32  D_800A8E8C;
extern s32  g_scenery_door_group_count; /* was D_800DC3F0 */
extern f32  D_800A35C4;
extern u8   g_cutscene_obj_list_count[]; /* was D_800C3930 */
extern u8   g_cutscene_rec_list_count[]; /* was D_800C396A */
extern u8   g_sky_flash_count; /* was D_800D9D20 */
extern s16  g_ambient_flare_point[3]; /* was D_800DD8A0 */
extern u8   g_reflect_queue_count; /* was D_800C4320 */
extern struct_eu_800877D0 g_event_table[]; /* was D_800877D0 */
extern s8   g_mp_free_for_all; /* was D_80090168 */
extern u8   g_menu_flag_ebc; /* was D_800E0EBC */
extern s32  g_text_bank1_extra; /* was D_80090178 */
extern s8   g_text_bank_loaded; /* was D_800E1003 */
extern s32  g_text_bank_data; /* was D_800E1004 */
extern f32  g_bone_debris_k_85c8; /* was D_800A85C8 */
extern u8   g_camera_view_offsets[]; /* was D_800DD210 */
extern s16  g_menu_pressed; /* was D_800E0FCA */
extern struct_eu_80087640 *g_race_records; /* was D_80087640 */
extern u8   g_look_limits[][0x18]; /* was D_80098418 */
extern f32  D_800A1380;
extern u16  g_anim_segment_clock; /* was D_800D9D30 */
extern s32  g_buddy_marker; /* was D_800E0D50 */
extern s32  g_lipsync_mode; /* was D_800D1D48 */
extern s32  g_lipsync_shape_idx; /* was D_800D1D4C */
extern s32  g_lipsync_unk_1d50; /* was D_800D1D50 */
extern s8   g_texture_cache_ages[]; /* was D_800BC860 */
extern u8   g_cs_overlay_cmd; /* was D_800D9CB0 */
extern f32  D_800A24EC;
extern u8   D_800A0000[];
extern s32  g_level_vtx_scroll_tex_key; /* was D_80091B68 */
extern Gfx  g_sprite_setup_dl[]; /* was D_80087770 */
extern s32  g_gfx_cur_tex_addr; /* was D_800D30C0 */
extern u8  *g_objects_state; /* was D_800CCA0C */
extern u8   g_camera_timed_records[]; /* was D_800D31E0 */
extern u8   g_player_pad_map[]; /* was D_800843F0 */
extern u8   g_rumble_active[]; /* was D_800BED5C */
extern s32  g_obj_mtx_next; /* was D_800C42A8 */
extern s32  g_obj_mtx_arena_start; /* was D_800C42AC */
extern s16  g_obj_mtx_count; /* was D_800C429A */
extern OSMesgQueue g_os_si_access_queue; /* was D_80042E38 */
extern f32  g_lamp_kick_k_18c; /* was D_800AA94C */
extern f32  g_lamp_kick_k_190; /* was D_800AA950 */
extern u8   g_identity_mtx[]; /* was D_80089810 */
extern u8   g_rumble_bcast_types[]; /* was D_800AB6E0 */
extern s8   g_human_player_count; /* was D_80090130 */
extern u8  *g_menu_state; /* was D_80090174 */
extern s16  g_hud_fade_alpha; /* was D_8009016C */
extern void (*g_screen_tint_fx_draw_fns[])(s32, void *, s16); /* was D_8008FCA0 */
extern void (*g_screen_tint_fx_msg_fns[])(s32, void *, u8); /* was D_8008FCA4 */
extern s32  D_800A9150;
extern s32  D_80088FF8[2];
extern u8   g_weapon_b_muzzle_pts[]; /* was D_800A2398 */
extern u8   g_weapon_b_bone; /* was D_80088F34 */
extern u8   g_anim_model_fx_node_types[]; /* was D_800A6440 */
extern s32  g_select_menu_scroll_dir; /* was D_80084818 */
extern f32  g_select_menu_scroll; /* was D_800C6C70 */
extern s32  g_select_menu_reset_timer; /* was D_8008481C */
extern u8   g_select_menu_blink_timer; /* was D_80084820 */
extern u8   g_select_menu_blink_on; /* was D_80084824 */
extern Gfx  g_sprite_setup_dl_alt[]; /* was D_800877A8 */
extern struct_eu_words3 g_event_timers_count[]; /* was D_800D3434 */
extern f32  g_shadow_far_depth; /* was D_800D3AA8 */
extern f32  g_shadow_near_depth; /* was D_800D3AAC */
extern struct_eu_800DFB30 g_light_fx[]; /* was D_800DFB30 */
extern s32  g_light_fx_count; /* was D_800DFBE4 */
extern s32  g_save_route_table; /* was D_800D33D0 */
extern s8   g_menu_scene_start_state; /* was D_80090120 */
extern u8   g_obj_effect_pos[]; /* was D_800D1980 */
extern u8   D_eu_800D1990[];
extern u8   g_weapon_a_muzzle_pts[]; /* was D_800A2340 */
extern u8   g_weapon_a_bone; /* was D_80088F20 */
extern s8   g_aim_hud_active; /* was D_8008D0A0 */
extern u8   g_char_fx_effect_5d00[]; /* was D_800A5D00 */
extern u8   g_char_fx_effect_5d68[]; /* was D_800A5D68 */
extern s32  D_80088FF0[2];
extern s32  g_game_mode_timer; /* was D_800E0EC0 */
extern struct127 *g_text_strings; /* was D_800E1008 */
extern u8   g_fxrec_bcast_types[]; /* was D_800A5B40 */
extern u8   g_screen_pulse_speed; /* was D_800DE1B8 */
extern u8   g_screen_pulse_phase; /* was D_800DE1B9 */
extern u8   g_screen_pulse_colour; /* was D_800DE1BA */
extern u8   g_screen_pulse_alpha; /* was D_800DE1BB */
extern u8   g_screen_pulse_wave; /* was D_800DE1BC */
extern f32  g_angle_offset_k_0c08; /* was D_800A0C08 */
/* P241 (port-b P239): the NM dispatchers use the s32 results */
extern s32 (*D_8008DA20[])(u8 *);
extern u8  *g_shooting_star_obj; /* was D_80088C10 */
extern f32  g_shooting_star_rate_scale; /* was D_800A0B74 */
extern s32  (*g_cutscene_gated_fn)(s32); /* was D_8008B148 */
extern u8   g_cutscene_actor_count[]; /* was D_800C3A5A */
extern u16 *g_cutscene_event_counts[]; /* was D_800C39F8 */
extern s16  g_cutscene_focus2_pos[3]; /* was D_800C39B8 */
extern f32  g_cutscene_focus2_yaw; /* was D_800C39C0 */
extern void (*g_obj_interaction_state_fns[])(void); /* was D_800863B4 */
extern void (*g_level_player_state_fns[])(s32); /* was D_80089A10 */
extern s32  g_cs_overlay_tint; /* was D_800D9CB4 */
extern s32  g_cs_overlay_fx[10]; /* was D_800D9CB8 */
extern s32  g_texture_cache_dirty_lo; /* was D_800DA378 */
extern s32  g_texture_cache_dirty_hi; /* was D_800DA37C */
extern u8   g_texture_cache_refs[]; /* was D_800DA388 */
extern u8   g_char_fx_light_ofs_j2[]; /* was D_800A5C80 */
extern struct_eu_800D2778 *g_rail_nodes; /* was D_800D2778 */
extern s16  g_rail_node_count; /* was D_80087630 */
extern f32  D_8009DDD0;
extern f32  g_rail_band_splits[]; /* was D_800D2788 */
extern u8   g_rail_bands[]; /* was D_800D2770 */
extern s16  g_puff_last_alpha; /* was D_800DD880 */
extern void (*g_bolt_path_retire_fns[])(void *); /* was D_8008FCEC */
extern void (*g_bolt_path_free_fns[])(void *); /* was D_8008FCF8 */
extern s32  g_cs_overlay_fx_end[]; /* was D_800D9CE0 */
extern s8   g_save_options_loaded; /* was D_800901D0 */
extern s8   g_menu_fade_speed; /* was D_80090114 */
extern s8   g_screen_fade_alpha; /* was D_800E0FC6 */
extern s8   g_menu_blink_alpha; /* was D_800E0FC7 */
extern s8   g_menu_blink_dir; /* was D_800E0FC8 */
extern s8   g_menu_input_lock_frames; /* was D_800901C8 */
extern s8   g_mp_player_team[]; /* was D_800E1030 */
extern s8   g_settings_cpu_views; /* was D_800E101B */
extern u8   g_level_colour_priority; /* was D_800DD157 */
extern void (*g_sprite2d_msg_fns[])(void *, s32, u8); /* was D_8008B0A4 */
extern void (*g_obj_kind9_fns[])(void *, void *); /* was D_8008B430 */
extern void (*g_cord_msg_fns[])(void *, s32, u8); /* was D_8008FF08 */
extern u8   g_char_fx_effect_5cb0[]; /* was D_800A5CB0 */
extern u8   g_char_fx_effect_5cc4[]; /* was D_800A5CC4 */
extern u8   g_char_fx_effect_5cd8[]; /* was D_800A5CD8 */
extern u8   g_char_fx_effect_5cec[]; /* was D_800A5CEC */
extern f32  g_fx_spin_gravity; /* was D_800A01FC */
extern void (*g_aim_hud_sprite_msg_fns[])(void *, u8 **, u8); /* was D_8008FFB0 */
extern void (*g_beam_message_fns[])(u8 *, s32, u8); /* was D_80088B68 */
extern void (*g_bolt_arc_event_fns[])(u8 *, s32, u8); /* was D_80088FC8 */
extern void (*g_fb_fx_msg_fns[])(u8 *, s32, u8); /* was D_8008B484 */
extern void (*g_glow_msg_fns[])(u8 *, s32, u8); /* was D_8008FF38 */
extern void (*g_mdl_particle_hook_fns_d50[])(u8 *); /* was D_80089D50 */
extern void (*g_mdl_particle_hook_fns_d74[])(u8 *); /* was D_80089D74 */
extern struct_eu_s32x2 g_mdl_particle_bcast_types; /* was D_800A3C40 */
extern struct_eu_s32x1 D_800A6A50;
extern u8   D_eu_800BE9A0[];
extern f32  g_trail_aim_scale_mp; /* was D_800A0F10 */
extern f32  g_trail_aim_scale_sp; /* was D_800A0F14 */
extern u8  *g_node_list_swarms; /* was D_800DD368 */
extern f32  g_bone_emitter_timer_scale; /* was D_800AAC40 */
extern f32  g_bone_emitter_timer_base; /* was D_800AAC44 */
extern void (*g_fxrec_free_fns[20])(void); /* was D_8008A690 */
extern void (*g_fxrec_kind_fns_b[20])(void); /* was D_8008A6E0 */
extern void (*g_fxrec_msg_fns[])(void *, s32, u8); /* was D_8008A730 */
extern void (*g_particle_hook_fns_bb4[])(void *); /* was D_80089BB4 */
extern void (*g_particle_hook_fns_be4[])(void *); /* was D_80089BE4 */
extern u8   g_screen_tint_rgb[][3]; /* was D_800DE1C0 */
extern u8   g_screen_tint_alpha[]; /* was D_800DE1CC */
extern s16  g_screen_tint_timer[]; /* was D_800DE240 */
extern f32  g_hud_lens_centre[][2]; /* was D_800DE218 */
extern u8   g_objects_shadow_kind; /* was D_800CC826 */
extern u8  *g_scroll_banner_nodes; /* was D_800DD510 */
extern u8   g_water_effect_started; /* was D_80088D20 */
extern struct_eu_size0C g_reflect_queue[]; /* was D_800C4328 */
extern u8   g_rain_level; /* was D_800DD864 */
extern u8   g_rain_state; /* was D_800DD876 */
extern u8   g_rain_gust_timer; /* was D_800DD862 */
extern u8   g_rain_gust_strength; /* was D_800DD863 */
extern s16  g_rain_drop_count; /* was D_800DD866 */
extern s32  g_rain_drops; /* was D_800DD870 */
extern f32  g_trail_point_gravity; /* was D_800AB6CC */
extern f32  g_trail_point_gravity_half; /* was D_800AB6D0 */
extern s32  g_att_pingpong_tex_ids[]; /* was D_8009066C */
extern s32  g_att_blink_tex_ids[]; /* was D_800906AC */
extern s8   g_settings_defaults[]; /* was D_800901F4 */
extern s8   g_settings[]; /* was D_800E1010 */
extern u8   g_shared_dl_refcounts[]; /* was D_800DFC00 */
extern u8   D_800DFC01;
extern u8   D_800DFC02;
extern u8   D_800DFC03[];
extern void (*g_cord_release_fns[])(void *); /* was D_8008FF10 */
extern u8   g_camera_shake_states[][0x68]; /* was D_800DC6F0 */
extern void (*g_bolt_path_msg_fns[])(void); /* was D_8008FD04 */
extern f32  g_cutscene_focus_yaw; /* was D_800C39B4 */
extern s16  g_cutscene_focus_pos[3]; /* was D_800C39AC */
extern u8   g_cutscene_focus_set; /* was D_800C3663 */
extern f32  D_800A35B0;
extern u8   g_player_screen_proj[]; /* was D_800DD040 */
extern u8   g_tint_prim_rgb[]; /* was D_800D9F88 */
extern u8   g_tint_env_rgb[]; /* was D_800D9F98 */
/* EU: end new */

/* other */

extern u32  D_00AB1950; // offsets table

extern s32  D_100290D0; // start of data (?)
extern s32  D_100291A0;
extern s32 *g_icache_flush_base; /* was D_1002AAD0 */
extern s32  D_151F3C4C;

/* what is this */
extern u16  D_BC000C02;
extern s32  D_1FC007FC;

#endif
