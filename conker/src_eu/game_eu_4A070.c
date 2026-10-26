#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void lipsync_poll_text_queue(void);
u8 *world_record_find(u8);
extern u8 g_cutscene_obj_lists[][0x19]; /* was D_800C3938 */
void cutscene_actor_apply_track(struct127 *, s32, s32);
extern s32 D_eu_800C3A60;
extern s32 g_cutscene_frame; /* was D_800C39D0 */
extern s32 g_cutscene_length_60hz; /* was D_800C3A68 */
extern u16 *g_cutscene_actor_key_counts[]; /* was D_800C39E8 */
extern u16 *g_cutscene_cam_key_counts[]; /* was D_800C39F0 */
extern s32 g_cutscene_cam_tracks[][30]; /* was D_800C3B98 */
extern s32 g_cutscene_event_tracks[][30]; /* was D_800C3AA8 */
s32 cutscene_obj_takes_part(s32 *);
struct127 *obj_find_by_setup_id(u8);
// hoisted forward declaration(s) for cutscene_actors_reset_anim
s32 face_anim_reset_default(struct127 *);


/* End of frame (P13, hand C): closes the display list (rolled back to the per-buffer reserve g_gfx_dl_frame_starts when it
 * overflowed, cut at 0x190 commands before the end otherwise), fills the gfx OSScTask g_gfx_tasks[idx] (0x60
 * bytes), sends it to the scheduler's gfx queue and, when arg1 != 0, flips the DL buffer index g_dl_buf_index.
 * Names are the asm's (several are US names remapped by undefined_syms.eu.txt). */
extern s32 *g_gfx_cur_task;           /* the task being filled; was D_800BEEF4 */
extern u8 g_gfx_tasks[];           /* OSScTask[2], 0x60 each; was D_800BEEF8 */
extern u8 g_rspboot_text[];           /* rspboot; was D_10029400 */
extern u8 g_rspboot_text_end[]; /* was D_100294D0 */
extern u8 g_gfx_alt_ucode_active; /* was D_800BEFC0 */
extern u8 g_gfx_vi_mode_pending; /* was D_800BEA37 */
extern u8 g_gfx_yield_buffer[];           /* yield buffer; was D_8003A948 */
extern OSMesgQueue g_game_main_queue;    /* main-loop queue; was D_800BEE30 */
extern u8 g_gfx_done_msgs[];           /* done messages, 0x20 each; was D_800BEE88 */
extern OSMesgQueue g_sched_gfx_queue;    /* scheduler gfx queue; was D_8003B548 */
extern s16 g_gfx_tasks_pending; /* was D_800BEEC8 */
extern s32 g_gfx_ucode2_text;            /* ucode text / data pairs; was D_800BEFD0 */
extern s32 g_gfx_ucode_text; /* was D_800C1480 */
extern u8 *g_gfx_ucode_data; /* was D_800BEFBC */
extern u8 *g_gfx_ucode2_data; /* was D_800BEEF0 */
void render_dl_buffers_init(void);
void gfx_load_ucode(void);

/* was func_eu_1501C860 */
void gfx_task_submit(s32 arg0, s32 arg1) {
    s32 *task;
    s32 cap;
    s32 n;
    s32 base;
    s32 *g;

    task = (s32 *)(g_gfx_tasks + g_dl_buf_index * 0x60);
    g_gfx_cur_task = task;
    task[0] = 0;
    cap = ((s32)g_gfx_dl_buffers[1] - (s32)g_gfx_dl_buffers[0]) >> 3;
    base = (s32)g_gfx_dl_buffers[g_dl_buf_index];
    n = (g_gfx_dl_ptr - base) >> 3;
    if (n < 0 || cap < n) {
        render_dl_buffers_init();
        g_gfx_dl_ptr = g_gfx_dl_frame_starts[g_dl_buf_index];
        g = (s32 *)g_gfx_dl_ptr; g_gfx_dl_ptr += 8; g[1] = 0; g[0] = 0xE9000000;
        g = (s32 *)g_gfx_dl_ptr; g_gfx_dl_ptr += 8; g[1] = 0; g[0] = 0xDF000000;
        base = (s32)g_gfx_dl_buffers[g_dl_buf_index];
        n = (g_gfx_dl_ptr - base) >> 3;
    }
    if (n < 0 || cap - 0x190 < n) {
        g_gfx_dl_ptr = base + (cap - 0x190) * 8;
        g = (s32 *)g_gfx_dl_ptr; g_gfx_dl_ptr += 8; g[1] = 0; g[0] = 0xE9000000;
        g = (s32 *)g_gfx_dl_ptr; g_gfx_dl_ptr += 8; g[1] = 0; g[0] = 0xDF000000;
        base = (s32)g_gfx_dl_buffers[g_dl_buf_index];
    }
    g_gfx_cur_task[0x48 / 4] = base;
    g_gfx_cur_task[0x4C / 4] = ((g_gfx_dl_ptr - (s32)g_gfx_dl_buffers[g_dl_buf_index]) >> 3) << 3;
    gfx_load_ucode();
    g_gfx_cur_task[0x18 / 4] = 1;                                  /* M_GFXTASK */
    g_gfx_cur_task[0x1C / 4] = 4;                                  /* OS_TASK_LOADABLE */
    g_gfx_cur_task[0x20 / 4] = (s32)g_rspboot_text;
    g_gfx_cur_task[0x24 / 4] = g_rspboot_text_end - g_rspboot_text;
    if (g_gfx_alt_ucode_active != 0) {
        g_gfx_cur_task[0x28 / 4] = (s32)&g_gfx_ucode_text;
        g_gfx_cur_task[0x30 / 4] = (s32)g_gfx_ucode_data;
    } else {
        g_gfx_cur_task[0x28 / 4] = (s32)&g_gfx_ucode2_text;
        g_gfx_cur_task[0x30 / 4] = (s32)g_gfx_ucode2_data;
    }
    g_gfx_cur_task[0x34 / 4] = 0x800;
    g_gfx_cur_task[0x38 / 4] = (s32)&g_gfx_dram_stack;
    g_gfx_cur_task[0x3C / 4] = 0x400;
    g_gfx_cur_task[0x40 / 4] = g_mem_rdp_fifo_start;
    g_gfx_cur_task[0x44 / 4] = g_mem_rdp_fifo_end;
    g_gfx_cur_task[0x50 / 4] = (s32)g_gfx_yield_buffer;
    g_gfx_cur_task[0x54 / 4] = 0xC00;
    g_gfx_cur_task[0x0C / 4] = 0x23;
    if (arg1 != 0) {
        g_gfx_cur_task[0x0C / 4] |= 0x40;
    }
    if (g_gfx_vi_mode_pending != 0) {
        g_gfx_cur_task[0x0C / 4] |= (g_last_player_index + 1) << 16;
        g_gfx_vi_mode_pending = 0;
    }
    g_gfx_cur_task[0x58 / 4] = (s32)&g_game_main_queue;
    g_gfx_cur_task[0x5C / 4] = (s32)(g_gfx_done_msgs + g_dl_buf_index * 0x20);
    g_gfx_cur_task[0x10 / 4] = g_framebuffers[g_dl_buf_index];
    osWritebackDCacheAll();
    osSendMesg(&g_sched_gfx_queue, (OSMesg)g_gfx_cur_task, OS_MESG_BLOCK);
    if (arg1 != 0) {
        g_dl_buf_index ^= 1;
    }
    g_gfx_tasks_pending++;
}
extern s32 D_2D810;
extern s8 g_gfx_loaded_ucode_idx; /* was D_80084400 */
extern s8 g_gfx_loaded_ucode2_ofs; /* was D_80084404 */
extern s32 g_gfx_ucode_rom_table; /* was D_80084408 */
extern u8 *g_gfx_ucode2_data; /* was D_800BEEF0 */
extern s32 g_gfx_ucode_variant; /* was D_800BEFB8 */
extern u8 *g_gfx_ucode_data; /* was D_800BEFBC */
extern s32 g_gfx_ucode2_text; /* was D_800BEFD0 */
extern s32 g_gfx_ucode_text; /* was D_800C1480 */

/* was func_1501CC1C */
void gfx_load_ucode(void) {
    s32 sp2C;
    s32 sp28;
    u8 *sp20;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_t1;
    u8 var_t0;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_t1 = 4;
    var_t0 = g_level_header->pad2A[1];
    if ((s32) var_t0 >= 2) {
        var_t0 -= 2;
        var_t1 = 0;
    }
    if (g_gfx_ucode_variant == 1) {
        var_t0 += 2;
    }
    temp_v0 = ((s32 *)((u8 *)&g_gfx_ucode_rom_table + (var_t0 * 0x10)));
    if ((var_t0 != g_gfx_loaded_ucode_idx) || (var_t1 != g_gfx_loaded_ucode2_ofs)) {
        temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0));
        sp20 = temp_v0;
        sp2C = (s32) var_t0;
        sp28 = var_t1;
        rom_dma_read((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1))), &g_gfx_ucode_text, (*(s32 *)((u8 *)temp_v0 + 4)) - temp_v1, 1);
        temp_v1_2 = (*(s32 *)((u8 *)temp_v0 + 8));
        temp_a1 = ((s32 *)((u8 *)&g_gfx_ucode_text + ((*(s32 *)((u8 *)temp_v0 + 4)) - (*(s32 *)((u8 *)temp_v0 + 0)))));
        g_gfx_ucode_data = temp_a1;
        rom_dma_read((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_2))), temp_a1, (*(s32 *)((u8 *)temp_v0 + 0xC)) - temp_v1_2, 1);
        g_gfx_loaded_ucode_idx = (s8) var_t0;
        temp_v0_2 = ((s32 *)((u8 *)&g_gfx_ucode_rom_table + ((var_t0 + var_t1) * 0x10)));
        g_gfx_loaded_ucode2_ofs = (s8) var_t1;
        temp_v1_3 = (*(s32 *)((u8 *)temp_v0_2 + 0));
        sp20 = temp_v0_2;
        rom_dma_read((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_3))), &g_gfx_ucode2_text, (*(s32 *)((u8 *)temp_v0_2 + 4)) - temp_v1_3, 1);
        temp_a1_2 = ((s32 *)((u8 *)&g_gfx_ucode2_text + ((*(s32 *)((u8 *)temp_v0_2 + 4)) - (*(s32 *)((u8 *)temp_v0_2 + 0)))));
        g_gfx_ucode2_data = temp_a1_2;
        temp_v1_4 = (*(s32 *)((u8 *)temp_v0_2 + 8));
        rom_dma_read((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_4))), temp_a1_2, (*(s32 *)((u8 *)temp_v0_2 + 0xC)) - temp_v1_4, 1);
    }
}
extern void *g_cutscene_actor_blocks[][30];   /* 16-byte block per actor; was D_800C3D80 */

/* Clears (0xFF) the 16-byte block of every actor of sequence slot `slot`. */
/* was func_1501CDA0 */
void cutscene_clear_actor_blocks(s32 slot) {
    s32 i;
    s32 j;

    for (i = 0; i < g_cutscene_actor_count[slot]; i++) {
        for (j = 0; j < 16; j++) {
            ((u8 *)g_cutscene_actor_blocks[slot][i])[j] = 0xFF;
        }
    }
}

/* Length of cutscene slot `slot` (P84 browser blocker: cutscene_check_finished waits for it): the end frame of the first
 * camera track when it has one (record +0x12 != -9999 and the slot's first camera word >= 4), else the latest end
 * (+0x0A) of the camera tracks of the active actors, else the last key (frame at -2 of key k, g_cutscene_cam_key_counts count)
 * of their actor tracks. g_cutscene_length_60hz = the length in 60 Hz frames, D_eu_800C3A60[slot] = it in 50 Hz frames
 * (EU: * 50 / 60). */
/* was func_1501CE34 */
void cutscene_compute_length(s32 slot) {
    s32 *len = &(&D_eu_800C3A60)[slot];
    u16 *cams;
    u8 n;
    s32 i;
    s32 found;
    s32 end;
    s32 v;
    u16 k;

    *len = 0;
    g_cutscene_length_60hz = 0;
    n = g_cutscene_actor_count[slot];
    if (n == 0) {
        return;
    }
    cams = g_cutscene_event_counts[slot];
    if (cams[0] >= 4) {
        v = *(s16 *)((u8 *)g_cutscene_event_tracks[slot][0] + 0x12);
        if (v != -9999) {
            g_cutscene_length_60hz = v;
            *len = v * 50 / 60;
            return;
        }
    }
    found = FALSE;
    for (i = 0; i < n; i++) {
        if (g_cutscene_actor_key_counts[slot][i] != 0 && cams[i] != 0) {
            v = *(s16 *)((u8 *)g_cutscene_event_tracks[slot][i] + 0xA);
            if (*len < v) {
                *len = v;
                found = TRUE;
            }
        }
    }
    if (found) {
        end = *len;
        g_cutscene_length_60hz = end;
        *len = end * 50 / 60;
        return;
    }
    end = *len;
    for (i = 0; i < n; i++) {
        if (g_cutscene_actor_key_counts[slot][i] != 0) {
            k = g_cutscene_cam_key_counts[slot][i];
            if (k != 0) {
                v = *(s16 *)((u8 *)g_cutscene_cam_tracks[slot][i] + k * 8 - 2);
                if (end < v) {
                    *len = v;
                    end = v;
                }
            }
        }
    }
    g_cutscene_length_60hz = end;
    *len = end * 50 / 60;
}

/* was func_1501D064 */
s32 cutscene_sum_actor_counts(s32 arg0) {
    s32 sum = 0;
    s32 i;

    for (i = 0; i < g_cutscene_actor_count[arg0]; i++) {
        sum += g_cutscene_event_counts[arg0][i];
    }
    return sum;
}

/* P87: declarations for cutscene_slot_reset / cutscene_scan_start_events / cutscene_end */
extern s32 g_cutscene_frame; /* was D_800C39D0 */
extern s32 g_cutscene_prev_frame[]; /* was D_800C39D8 */
extern u8 g_cutscene_events_ran[]; /* was D_800C39E0 */
extern u16 g_cutscene_start_frame; /* was D_800C40AE */
extern void *g_scene_event_queue; /* was D_800C4170 */
extern u8 g_cutscene_camera_actor; /* was D_800C3A18 */
extern f32 g_cutscene_scene_rot; /* was D_800C39C4 */
extern f32 g_camera_fov_extra; /* was D_800C3A6C */
extern f32 g_camera_viewport_w; /* was D_800C3A70 */
extern f32 g_camera_viewport_h; /* was D_800C3A74 */
extern f32 g_cutscene_end_cam_value; /* was D_800C3A94 */
extern f32 g_cutscene_end_cam_blend_arg; /* was D_800C3A98 */
extern u8 g_cutscene_run_all_objs; /* was D_800C3A78 */
extern u8 g_cutscene_show_all_objs; /* was D_800C3A7A */
extern u8 g_cutscene_show_all; /* was D_800C3A7C */
extern u8 g_cutscene_keep_listed_objs; /* was D_800C3A7E */
extern u8 g_cutscene_ev13_value; /* was D_800C3A80 */
extern u8 g_cutscene_anim_events_on; /* was D_800C3A82 */
extern u8 g_cutscene_obj_vis_mode; /* was D_800C3A84 */
extern u8 g_cutscene_hide_world; /* was D_800C3A86 */
extern u8 g_cutscene_finish_state; /* was D_800C40AC */
extern u8 g_cutscene_event_no_fade; /* was D_800C40AD */
extern u8 g_cutscene_next_scene;            /* queued follow-up scene + 1; was D_800C39E2 */
extern u8 g_cutscene_return_level;            /* its level; was D_800C39E3 */
extern u8 D_eu_800C3E78;
extern u8 g_cutscene_last_fade_in; /* was D_800C40AA */
extern u8 g_cutscene_fade_out_at_end; /* was D_800C40AB */
extern s32 g_cutscene_end_cam_blend_time; /* was D_800C3A9C */
extern u8 g_cutscene_skip_end_cam_event; /* was D_800C3AA0 */
extern u8 g_cutscene_skipped; /* was D_800C3A92 */
extern u8 g_cutscene_tail_lift_pct; /* was D_800C40BD */
extern s16 g_cutscene_cash_offset; /* was D_800C40BE */
extern s8 g_cutscene_menu_skip_req; /* was D_80090124 */
extern u8 g_cutscene_chain_skip; /* was D_800C40B9 */
extern u8 g_cutscene_script_no_fade; /* was D_800C39C9 */
extern u8 g_cutscene_no_skip; /* was D_800C40BC */
extern u8 g_cutscene_keep_player; /* was D_800C39CA */
extern u8 g_scene_fade_colours[][3];       /* RGB rows; was D_800844A0 */
void subtitle_slots_clear(void);
s32 scene_event_find_next(u32, s32, s32, u8 **, s32, s32, s32, s32, s32, s32, s32);
void screen_fade_start(s32, s32, s32, s32, s8, s32);
void node_broadcast_all(s32, u8);
void subtitle_slots_close_all(void);
void cutscene_teardown_player(s32);
void cutscene_end_camera_objs(s32);
void cutscene_free_tables(s32);
void camera_projection_set_fov(s32, f32, f32, f32);
void cutscene_actors_reset_anim(s32);
void cutscene_scene_load(s32, s32, s32, s32, s32);
/* Resets cutscene slot `slot` and the shared cutscene state (cutscene_scene_load, before a scene is loaded): no
 * script position / script wait (g_cutscene_prev_frame = -100), slot not loaded, no actors, camera actor g_cutscene_camera_actor =
 * 0xFF (cutscene_apply_cameras picks it again), cleared look / fade state, g_cutscene_end_cam_value / g_cutscene_end_cam_blend_arg = 999, then
 * subtitle_slots_clear. */
/* was func_1501D044 */
void cutscene_slot_reset(s32 slot) {
    g_cutscene_prev_frame[slot] = -100;
    (&g_cutscene_frame)[slot] = 0;
    g_cutscene_events_ran[slot] = 0;
    g_cutscene_start_frame = 0;
    g_cutscene_actor_count[slot] = 0;
    (&g_cutscene_slot_state)[slot] = 0;
    g_scene_event_queue = NULL;
    g_cutscene_camera_actor = 0xFF;
    g_camera_fov_extra = 0.0f;
    g_camera_viewport_w = 0.0f;
    g_camera_viewport_h = 0.0f;
    (&g_cutscene_run_all_objs)[slot] = 0;
    (&g_cutscene_show_all_objs)[slot] = 0;
    (&g_cutscene_show_all)[slot] = 1;
    (&g_cutscene_keep_listed_objs)[slot] = 0;
    (&g_cutscene_ev13_value)[slot] = 0;
    (&g_cutscene_anim_events_on)[slot] = 0;
    (&g_cutscene_obj_vis_mode)[slot] = 0;
    g_cutscene_in_progress = 0;
    g_cutscene_hide_world = 0;
    g_cutscene_finish_state = 0;
    g_cutscene_event_no_fade = 0;
    g_cutscene_next_scene = 0;
    D_eu_800C3E78 = 0;
    g_cutscene_scene_rot = 0.0f;
    g_cutscene_last_fade_in = 0xFF;
    g_cutscene_fade_out_at_end = 0;
    g_cutscene_end_cam_value = 999.0f;
    g_cutscene_end_cam_blend_arg = 999.0f;
    g_cutscene_end_cam_blend_time = 0;
    g_cutscene_skip_end_cam_event = 0;
    g_cutscene_skipped = 0;
    g_cutscene_tail_lift_pct = 100;
    g_cutscene_cash_offset = -1;
    subtitle_slots_clear();
    g_cutscene_menu_skip_req = 0;
    g_cutscene_treat_as_seen = 0;
}

s32 asset_load_with_subfiles(s32 *, s32, s32 *, s32, s32, s32, s32);
extern s32 g_cutscene_scene_assets; /* was D_800C3A88 */

/* was func_1501D240 */
s32 cutscene_load_scene_asset(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp34;
    s32 sp30;
    s32 temp_v0;

    temp_v0 = asset_load_with_subfiles(&sp30, 0, &sp34, 3, 6, arg0, arg1);
    if (temp_v0 != 0) {
        (&g_cutscene_scene_assets)[arg2] = temp_v0;
    } else {
        (&g_cutscene_scene_assets)[arg2] = 0;
    }
    return temp_v0;
}

/* was func_1501D2C4 */
void cutscene_mark_seen(s32 arg0, s32 arg1) {
    if (g_cutscene_treat_as_seen == 0) {
        g_save_level_bits[arg0] |= 1ULL << arg1;
    }
}

/* cutscene_was_seen: has scene arg1 of level arg0 been seen (bit in the saved g_save_level_bits[level]), or is g_cutscene_treat_as_seen set?
 * Only the cutscene-skip test cutscene_can_skip asks this. */
/* was func_1501D330 */
s32 cutscene_was_seen(s32 arg0, s32 arg1) {
    u64 bit;
#ifdef PORT
    /* DELIBERATE PORT CHANGE (P320, user request): the browser / native port treats every cutscene as already seen,
     * so any cutscene can be skipped on the first viewing (the original only allows it after it was watched once).
     * Nothing is written: the seen bits (cutscene_mark_seen, saved to the EEPROM) are still recorded as on the N64.
     * Since P324 only with the page option "Skippable cutscenes (hold L)" on (PORT_OPT_CUTSCENE_SKIP, default on);
     * off = the N64 rule below. Not in the default eu or the plain NON_MATCHING build (no PORT define there). */
    if (port_option(PORT_OPT_CUTSCENE_SKIP)) {
        return 1;
    }
#endif
    if (g_cutscene_treat_as_seen != 0) {
        return 1;
    }
    if ((g_save_level_bits[arg0] & (1ULL << arg1)) != 0) {
        return 1;
    }
    return 0;
}

/* Load scene `scene` (asset group 3, type 6, found by cutscene_load_scene_asset) of level `level` into sequence slot `slot`.
 * Skipped while the slot is already loaded (g_cutscene_slot_state[slot] == 1) or a level change is pending (g_cutscene_pending).
 * For another level than the current one (g_level_id) the level change is requested instead (game_request_transition;
 * g_cutscene_pending = scene + 1, g_cutscene_pending_was_idle = "the slot was empty").
 * The asset is a header {u16 nActors, nCameras, nSounds, nWords} followed by 8-byte records {s32 value, u32 bits}
 * (record 0 is the header pointer itself): nActors actor records, one record for g_cutscene_actor_entries[slot], nActors
 * more (not read here), nCameras, nSounds, then nWords plain words. The per-slot tables (u16 arrays of
 * bits >> 3, the 30-entry value tables, actor state blocks) are allocated and filled, the optional setup
 * callback g_cutscene_setup_fns[callback] runs, and the sequence is started (cutscene_clear_actor_blocks ... cutscene_scan_start_events). */
typedef void (*SceneSetupFunc)(s32 level, s32 scene, s32 slot, s32 arg);
typedef struct {
    s32 value;
    u32 bits;
} SceneRecord;
typedef struct {
    u8 pad0[4];
    void *keys;        /* +0x04: (count of the actor's u16 entry) words */
    u8 pad8[0x30];
    void *state;       /* +0x38: 0x194 bytes */
    u8 pad3C[4];
} SceneActor;          /* 0x40 bytes, g_cutscene_actors[slot][actor] */

void *allocate_memory(s32, s32, s32, s32);
void game_request_transition(s32, s32, s32, s32, s32);
void cutscene_slot_reset(s32);
void cutscene_clear_actor_blocks(s32);
void cutscene_compute_length(s32);
void cutscene_place_scene(s32);
void cutscene_path_compute_length(s32, s32);
void scene_stub_noop(void);
void cutscene_obj_list_clear(s32);
void cutscene_record_list_clear(s32);
void cutscene_end(s32, s32);
void scene_event_track_pass(s32, s32);
void cutscene_camera_track_pass(s32);
void cutscene_spawn_actors(s32);
void cutscene_claim_records(s32);
void cutscene_actor_pass(s32);
void cutscene_apply_cameras(s32);
void cutscene_scan_start_events(s32);
extern u8 g_cutscene_level; /* was D_800C39C8 */
extern u8 g_cutscene_scene_id; /* was D_800C40B8 */
extern u16 *g_cutscene_actor_key_counts[];        /* actors: bits >> 3; was D_800C39E8 */
extern u16 *g_cutscene_cam_key_counts[];        /* cameras; was D_800C39F0 */
extern s32 *g_cutscene_words[];        /* plain words; was D_800C3A00 */
extern SceneActor *g_cutscene_actors[]; /* was D_800C3E70 */
extern void *g_cutscene_actor_blocks[][30];   /* 16-byte block per actor; was D_800C3D80 */
extern s32 D_eu_800C3C88[][30];  /* actor record values */
extern s32 g_cutscene_cam_tracks[][30];     /* camera record values; was D_800C3B98 */
extern s32 g_cutscene_event_tracks[][30];     /* sound record values; was D_800C3AA8 */
extern SceneSetupFunc g_cutscene_setup_fns[]; /* was D_8008448C */
extern u16 g_scene_event_queue_size; /* was D_800C40BA */
extern void *g_scene_event_queue; /* was D_800C4170 */
extern s32 g_cutscene_frame; /* was D_800C39D0 */
extern u8 *g_cutscene_actor_entries[];        /* the record after the actors; was D_800C3A10 */

/* was func_1501D348 */
void cutscene_scene_load(s32 level, s32 scene, s32 slot, s32 callback, s32 callbackArg) {
    u8 *loaded;
    u8 state;
    SceneRecord *rec;
    u16 *hdr;
    s32 size;
    s32 n;
    s32 i;
    s32 k;

    loaded = &g_cutscene_slot_state + slot;
    state = *loaded;
    if (state == 1 || g_cutscene_pending != 0) {
        return;
    }
    g_cutscene_load_callback = callback;
    g_cutscene_load_callback_arg = callbackArg;
    if (level != g_level_id) {
        g_cutscene_pending = scene + 1;
        game_request_transition(1, level, 0, 0, 0);
        if (*loaded != 0) {
            g_cutscene_pending_was_idle = 0;
        } else {
            g_cutscene_pending_was_idle = 1;
        }
        return;
    }

    (&g_cutscene_scene)[slot] = scene;
    if (state != 2) {
        g_cutscene_level = g_level_id;
        g_cutscene_scene_id = scene;
    }
    cutscene_slot_reset(slot);
    if (cutscene_load_scene_asset(level, scene, slot) == 0) {
        return;
    }
    rec = ((SceneRecord **)&g_cutscene_scene_assets)[slot];
    hdr = (u16 *)rec[0].value;

    /* the per-slot tables */
    g_cutscene_actor_key_counts[slot] = allocate_memory(hdr[0] * 2, 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        g_cutscene_actor_key_counts[slot][i] = rec[1 + i].bits >> 3;
    }
    size = ((hdr[1] < hdr[0]) ? hdr[0] : hdr[1]) * 2;
    g_cutscene_cam_key_counts[slot] = allocate_memory(size, 1, 0, 0);
    bzero(g_cutscene_cam_key_counts[slot], size);
    size = ((hdr[2] < hdr[0]) ? hdr[0] : hdr[2]) * 2;
    g_cutscene_event_counts[slot] = allocate_memory(size, 1, 0, 0);
    bzero(g_cutscene_event_counts[slot], size);
    g_cutscene_words[slot] = allocate_memory(hdr[3] * 4, 1, 0, 0);
    g_cutscene_actors[slot] = allocate_memory(hdr[0] * sizeof(SceneActor), 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        if (g_cutscene_actor_key_counts[slot][i] != 0) {
            g_cutscene_actors[slot][i].keys = allocate_memory(g_cutscene_actor_key_counts[slot][i] * 4, 1, 0, 0);
            g_cutscene_actors[slot][i].state = allocate_memory(0x194, 1, 0, 0);
        }
    }
    (&g_cutscene_track_recs)[slot] = allocate_memory(hdr[0] * 0x44, 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        g_cutscene_actor_blocks[slot][i] = allocate_memory(0x10, 1, 0, 0);
    }
    for (i = 0; i < hdr[0]; i++) {
        g_cutscene_event_counts[slot][i] = 0;
        g_cutscene_cam_key_counts[slot][i] = 0;
        g_cutscene_actor_key_counts[slot][i] = 0;
    }
    g_cutscene_actor_count[slot] = hdr[0];

    /* the records */
    k = 1;
    for (i = 0; i < hdr[0]; i++, k++) {
        g_cutscene_actor_key_counts[slot][i] = rec[k].bits >> 3;
        D_eu_800C3C88[slot][i] = rec[k].value;
    }
    g_cutscene_actor_entries[slot] = (u8 *)rec[k].value;
    k += hdr[0];
    for (i = 0; i < hdr[1]; i++, k++) {
        g_cutscene_cam_key_counts[slot][i] = rec[k].bits >> 3;
        g_cutscene_cam_tracks[slot][i] = rec[k].value;
    }
    for (i = 0; i < hdr[2]; i++, k++) {
        g_cutscene_event_counts[slot][i] = rec[k].bits >> 3;
        g_cutscene_event_tracks[slot][i] = rec[k].value;
    }
    for (i = 0; i < hdr[3]; i++) {
        g_cutscene_words[slot][i] = rec[k + i].value;
    }

    if (callback != 0) {
        g_cutscene_setup_fns[callback](level, scene, slot, callbackArg);
    }
    n = cutscene_sum_actor_counts(slot);
    g_scene_event_queue_size = n;
    g_scene_event_queue = allocate_memory((u16)n * 12, 1, 0, 0);
    (&g_cutscene_frame)[slot] = 0;

    /* start the sequence */
    cutscene_clear_actor_blocks(slot);
    cutscene_compute_length(slot);
    cutscene_place_scene(slot);
    for (i = 0; i < g_cutscene_actor_count[slot]; i++) {
        cutscene_path_compute_length(i, slot);
    }
    scene_stub_noop();
    *loaded = 1;
    g_cutscene_in_progress = 1;
    cutscene_obj_list_clear(slot);
    cutscene_record_list_clear(slot);
    if (g_cutscene_actor_count[slot] == 0) {
        cutscene_end(0, slot);
    }
    scene_event_track_pass(1, slot);
    cutscene_camera_track_pass(slot);
    cutscene_spawn_actors(slot);
    cutscene_claim_records(slot);
    cutscene_actor_pass(slot);
    cutscene_apply_cameras(slot);
    g_camera_timers[0] = 4;
    cutscene_scan_start_events(slot);
}

/* Start of cutscene slot `slot`: scans the sound / event track (g_cutscene_event_tracks[slot][i] + 0x18) of every actor with
 * scene_event_find_next (type 5) for the event codes 0x1E, 0x0E, 0x68, 0x44 (flags g_cutscene_chain_skip, g_cutscene_no_skip, g_cutscene_keep_player,
 * g_cutscene_script_no_fade), 0x77 (start position g_cutscene_start_frame = its frame) and 1 (the earliest one sets the screen colour
 * screen_fade_start from the RGB row g_scene_fade_colours[key[5]], key +6 == 1: with fade). The script position
 * g_cutscene_frame[slot] starts at g_cutscene_start_frame. */
/* was func_1501DB18 */
void cutscene_scan_start_events(s32 slot) {
    u8 *found;
    u8 *rec;
    u8 *rgb;
    s32 best;
    s32 v;
    s32 i;

    g_cutscene_chain_skip = 0;
    g_cutscene_script_no_fade = 0;
    g_cutscene_no_skip = 0;
    g_cutscene_keep_player = 0;
    g_cutscene_start_frame = 0;
    best = -1;
    for (i = 0; i < g_cutscene_actor_count[slot]; i++) {
        rec = (u8 *)g_cutscene_event_tracks[slot][i];
        if (rec == NULL) {
            continue;
        }
        found = NULL;
        scene_event_find_next((u32)(rec + 0x18), 5, i, &found, 1, 0x1E, 0, 0, 0, 0, slot);
        if (found != NULL) {
            g_cutscene_chain_skip = 1;
        }
        found = NULL;
        scene_event_find_next((u32)(rec + 0x18), 5, i, &found, 1, 0xE, 0, 0, 0, 0, slot);
        if (found != NULL) {
            g_cutscene_no_skip = 1;
        }
        found = NULL;
        scene_event_find_next((u32)(rec + 0x18), 5, i, &found, 1, 0x68, 0, 0, 0, 0, slot);
        if (found != NULL) {
            g_cutscene_keep_player = 1;
        }
        found = NULL;
        scene_event_find_next((u32)(rec + 0x18), 5, i, &found, 1, 0x44, 0, 0, 0, 0, slot);
        if (found != NULL) {
            g_cutscene_script_no_fade = 1;
        }
        found = NULL;
        v = scene_event_find_next((u32)(rec + 0x18), 5, i, &found, 1, 0x77, 0, 0, 0, 0, slot);
        if (found != NULL) {
            g_cutscene_start_frame = v;
        }
        found = NULL;
        v = scene_event_find_next((u32)(rec + 0x18), 5, i, &found, 1, 1, 1, 0, 0, 0, slot);
        if (found != NULL && (best == -1 || v < best)) {
            best = v;
            rgb = g_scene_fade_colours[(s8)found[5]];
            if (*(s16 *)(found + 6) == 1) {
                screen_fade_start(rgb[0], rgb[1], rgb[2], 0, 1, 0);
            } else {
                screen_fade_start(rgb[0], rgb[1], rgb[2], 0, 0, 0);
            }
        }
    }
    (&g_cutscene_frame)[slot] = g_cutscene_start_frame;
}

/* Starts cutscene slot `slot`: script position g_cutscene_frame[slot] = start D_eu_800C3A60[slot] + g_frame_ticks_raw, runs the
 * camera / actor tracks once (cutscene_camera_track_pass, cutscene_apply_cameras, with scene_event_track_pass around them), then gives every
 * live object that takes part (cutscene_obj_takes_part, current object index in g_cur_obj_index) its first actor frame
 * (cutscene_actor_apply_track(obj, slot, -1)) and ends with cutscene_end(1, slot). */
/* was func_1501DE84 */
void cutscene_start(s32 slot) {
    struct127 *obj;
    s32 i;

    (&g_cutscene_frame)[slot] = (&D_eu_800C3A60)[slot] + g_frame_ticks_raw;
    scene_event_track_pass(1, 0);
    cutscene_camera_track_pass(0);
    scene_event_track_pass(0, 0);
    cutscene_apply_cameras(0);
    for (i = 0, obj = g_objects; i < 25; i++, obj++) {
        if (*(s32 *)obj != 0) {
            g_cur_obj_index = i;
            if (cutscene_obj_takes_part((s32 *)obj) != 0) {
                cutscene_actor_apply_track(obj, slot, -1);
            }
        }
    }
    cutscene_end(1, slot);
}

s32 mp3_voice_is_playing(void);
void mp3_stream_stop(void);
struct127 *obj_find_child_nth(struct127 *, s32);
void obj_remove(struct127 *, s32);
void cutscene_start(s32 slot);
void screen_fade_start(s32, s32, s32, s32, s8, s32);
void music_restart_type13_songs(void);

/* End of cutscene slot `slot` (called by cutscene_update_skip with the slot left in a0): mp3_stream_stop when
 * mp3_voice_is_playing, remove object 0's attachment 0 (obj_find_child_nth / obj_remove), run cutscene_start(slot) once and
 * again while g_cutscene_chain_skip was set before the call and no level change is pending (g_cutscene_pending); screen colour
 * screen_fade_start(0, 0, 0, 0x19, 0, 0) unless g_cutscene_script_no_fade, g_cutscene_last_fade_in == 1 or g_cutscene_event_no_fade; clear +0xA4 of every live
 * object (g_objects, 25), g_cutscene_focus_set = 0, music_restart_type13_songs, g_camera_timers[0] = 4, g_cutscene_skipped = 1. */
/* was func_1501DF70 */
void cutscene_end_skip(s32 slot) {
    struct127 *p;
    u8 flag;
    s32 i;

    if (mp3_voice_is_playing() != 0) {
        mp3_stream_stop();
    }
    p = obj_find_child_nth(g_objects, 0);
    if (p != NULL) {
        obj_remove(p, 0);
    }
    do {
        flag = g_cutscene_chain_skip;
        cutscene_start(slot);
    } while (flag != 0 && g_cutscene_pending == 0);
    if (g_cutscene_script_no_fade == 0 && (s8)g_cutscene_last_fade_in != 1 && g_cutscene_event_no_fade == 0) {
        screen_fade_start(0, 0, 0, 0x19, 0, 0);
    }
    for (i = 0; i < 25; i++) {
        if (g_objects[i].interaction_state != 0) {
            *((u8 *)&g_objects[i] + 0xA4) = 0;
        }
    }
    g_cutscene_focus_set = 0;
    music_restart_type13_songs();
    g_camera_timers[0] = 4;
    g_cutscene_skipped = 1;
}
/* P96: cutscene_can_skip */
extern u16 g_pad_pressed;  /* buttons held; was D_800BEB30 */
extern u8 g_chapter_replay; /* was D_800D3260 */
extern u8 g_cutscene_scene; /* was D_800C3A08 */
extern s32 g_level_id; /* was D_800BE9F0 */
/* May cutscene slot `slot` be skipped (called by cutscene_update_skip for a playing slot)? Level 0x1D: once after a
 * pending request (g_cutscene_menu_skip_req, cleared here), else only when slot 0's scene is 5 (then as below). Level 0x21:
 * button 0x1000 held (g_pad_pressed) with g_os_reset_type == 1 and slot 0 past frame 250. Other levels: button 0x20,
 * no g_cutscene_no_skip, and either g_chapter_replay or a skippable scene (cutscene_was_seen with the slot's scene number) that is
 * forced (g_cutscene_chain_skip) or still has more than 25 frames to run (g_cutscene_frame + 25 < D_eu_800C3A60). The second
 * argument is not read. */
/* DELIBERATE PORT CHANGE (P321, user request): L skips a cutscene only after it is held for 3 s straight.
 * The L test moves to the end: once the scene may be skipped, port_skip_hold (port/ultra/pc_os.c) times how
 * long L is held (g_pad_pressed only flags the press) and the page draws a ring around an L badge from port_skip_progress.
 * P324: all the port changes in this function (P320 + P321) apply only while the page option "Skippable cutscenes
 * (hold L)" is on (PORT_SKIP_RULES = port_option(PORT_OPT_CUTSCENE_SKIP)). Off, every test is the N64 one: Start
 * skips the boot intro only after a reset, L skips at once, and the "no skip" marker g_cutscene_no_skip is obeyed.
 * Without PORT, PORT_SKIP_RULES is 0 and SKIP_YES is 1, so the NON_MATCHING code is the original. */
#ifdef PORT
s32 port_skip_hold(void);
#define PORT_SKIP_RULES port_option(PORT_OPT_CUTSCENE_SKIP)
#define SKIP_YES (PORT_SKIP_RULES ? port_skip_hold() : 1)
#else
#define PORT_SKIP_RULES 0
#define SKIP_YES 1
#endif
/* was func_1501E0C8 */
s32 cutscene_can_skip(s32 slot, u8 *unused) {
    s32 level = g_level_id;

    if (level == 0x1D) {
        if (g_cutscene_menu_skip_req != 0) {
            g_cutscene_menu_skip_req = 0;
            return 1;
        }
        if (g_cutscene_scene != 5) {
            return 0;
        }
    }
    if (level == 0x21) {
        /* DELIBERATE PORT CHANGE (P320): with the option on, the boot intro (level 0x21) can be skipped with Start
         * from the first power-on; the N64 allows it only after a reset (osResetType g_os_reset_type == 1, seen once). */
        if ((g_pad_pressed & 0x1000) && (g_os_reset_type == 1 || PORT_SKIP_RULES) && g_cutscene_frame >= 0xFB) {
            return 1;
        }
        return 0;
    }
    if (!PORT_SKIP_RULES) {
        if (!(g_pad_pressed & 0x20)) {
            return 0;
        }
        /* g_cutscene_no_skip: the scene script carries the "no skip" event 0xE (cutscene_scan_start_events), or an event
         * set it (event_action_scene case 6).
         * DELIBERATE PORT CHANGE (P320): with the option on, the port ignores it so every cutscene can be skipped
         * with L, the opening (level 0x18 scene 1) included; that one carries the marker, so it can never be skipped
         * on the N64. (The L test itself then happens in SKIP_YES, held for 3 s.) */
        if (g_cutscene_no_skip != 0) {
            return 0;
        }
    }
    if (g_chapter_replay != 0) {
        return SKIP_YES;
    }
    if (cutscene_was_seen(level, (&g_cutscene_scene)[slot]) == 0) {
        return 0;
    }
    if (g_cutscene_chain_skip != 0) {
        return SKIP_YES;
    }
    if ((&g_cutscene_frame)[slot] + 25 < (&D_eu_800C3A60)[slot]) {
        return SKIP_YES;
    }
    return 0;
}
#undef SKIP_YES
#undef PORT_SKIP_RULES
void music_restart_type13_songs(void);
void cutscene_end_skip(s32);
s32 cutscene_can_skip(s32, u8 *);
s32 mp3_stream_get_state(void);
extern s8 g_cutscene_menu_skip_req; /* was D_80090124 */
extern s32 g_cutscene_frame; /* was D_800C39D0 */
extern u8 g_cutscene_volume; /* was D_800C40A9 */
extern s32 D_eu_800C3A60;

/* was func_1501E220 */
void cutscene_update_skip(s32 arg0) {
    if (g_cutscene_skip_state == 0) {
        if (((&g_cutscene_slot_state)[arg0] == 1) && (cutscene_can_skip(arg0, &g_cutscene_skip_state) != 0)) {
            g_cutscene_menu_skip_req = 0;
            if (((*(&D_eu_800C3A60 + arg0) - *(&g_cutscene_frame + arg0)) >= 0x4C)) {
                g_cutscene_skip_state = 1;
                g_cutscene_volume = 0x19;
                screen_fade_start(0, 0, 0, 0x19, 1, 0);
                music_restart_type13_songs();
                if ((mp3_stream_get_state() == 1) || (mp3_stream_get_state() == 2)) {
                    mp3_stream_set_volume(0, 0x2B02);
                }
            }
        }
    } else if (g_cutscene_skip_state == 1) {
        if (g_frame_ticks_raw < (s32) g_cutscene_volume) {
            g_cutscene_volume -= g_frame_ticks_raw;
            return;
        }
        g_cutscene_volume = 0;
        g_cutscene_skip_state = 2;
        /* P82: the asm leaves arg0 (the slot) in a0; cutscene_end_skip reads it (arity scan row, dropped argument) */
        cutscene_end_skip(arg0);
        g_cutscene_skip_state = 0;
    }
}

void cutscene_advance_position(s32);
void cutscene_end(s32, s32);
void cutscene_camera_track_pass(s32);
void cutscene_apply_cameras(s32);
void scene_event_track_pass(s32, s32);
extern u8 g_cutscene_finish_state; /* was D_800C40AC */

/* was func_1501E364 */
void cutscene_check_finished(s32 arg0) {
    s32 var_s1;
    u8 *temp_s0;

    var_s1 = arg0;
loop_1:
    temp_s0 = &(&g_cutscene_slot_state)[var_s1];
    if ((*temp_s0 == 1) && ((&g_cutscene_frame)[var_s1] >= (&D_eu_800C3A60)[var_s1])) {
        if (g_cutscene_finish_state == 0) {
            cutscene_end(0, var_s1);
            if (*temp_s0 == 1) {
                var_s1 = 0;
                cutscene_advance_position(0);
                scene_event_track_pass(1, 0);
                cutscene_camera_track_pass(0);
                scene_event_track_pass(0, 0);
                cutscene_apply_cameras(0);
                goto loop_1;
            }
        } else {
            g_cutscene_finish_state = 2;
        }
    }
}
extern s32 g_cutscene_prev_frame[]; /* was D_800C39D8 */
extern u8 g_cutscene_events_ran[]; /* was D_800C39E0 */
extern u16 g_cutscene_start_frame; /* was D_800C40AE */
extern u8 D_eu_800C3E78;

/* Per-player counter step (P15, hand C from the asm): remembers the previous value g_cutscene_prev_frame[i] of
 * g_cutscene_frame[i], and for an active player (g_cutscene_slot_state[i] == 1) advances it by g_frame_ticks_raw (player 0
 * only when g_game_paused == 0), clamped to D_eu_800C3A60[i]. */
/* was func_1501E46C */
void cutscene_advance_position(s32 i) {
    s32 *cur = &(&g_cutscene_frame)[i];
    s32 lim;

    if (D_eu_800C3E78 != 0) {
        D_eu_800C3E78--;
    }
    g_cutscene_prev_frame[i] = *cur;
    if ((&g_cutscene_slot_state)[i] != 1) {
        return;
    }
    cutscene_update_skip(i);
    if (i != 0 || g_game_paused == 0) {
        *cur += g_frame_ticks_raw;
    }
    if (g_cutscene_events_ran[i] == 0 && g_cutscene_start_frame == g_cutscene_prev_frame[i] && g_cutscene_start_frame != *cur) {
        g_cutscene_prev_frame[i] = -1;
    }
    if (mp3_stream_get_state() == 1) {
        lipsync_poll_text_queue();
    }
    lim = (&D_eu_800C3A60)[i];
    if (*cur >= lim) {
        *cur = lim;
    }
}
/* P92: declarations for cutscene_free_tables */
void heap_free(s32);   /* free */

/* Frees the tables of cutscene slot `slot` (scene teardown, cutscene_end), when a scene asset is loaded
 * (g_cutscene_scene_assets[slot], first word = its header {u16 nActors, ...}): every actor's path length table and sample
 * table (SceneActor +4 / +0x38, actors with path keys only), the actor array g_cutscene_actors, the camera records
 * g_cutscene_track_recs, the per-actor blocks g_cutscene_actor_blocks, the u16 tables g_cutscene_actor_key_counts / g_cutscene_cam_key_counts / g_cutscene_event_counts, the words
 * g_cutscene_words, the shared g_scene_event_queue and the asset itself; all pointers become NULL. */
/* was func_1501E5AC */
void cutscene_free_tables(s32 slot) {
    u16 *hdr;
    s32 i;

    if ((&g_cutscene_scene_assets)[slot] == 0) {
        return;
    }
    hdr = *(u16 **)(&g_cutscene_scene_assets)[slot];
    for (i = 0; i < hdr[0]; i++) {
        if (g_cutscene_actor_key_counts[slot][i] != 0) {
            heap_free((s32)g_cutscene_actors[slot][i].keys);
            heap_free((s32)g_cutscene_actors[slot][i].state);
        }
    }
    heap_free((s32)g_cutscene_actors[slot]);
    g_cutscene_actors[slot] = NULL;
    heap_free((s32)(&g_cutscene_track_recs)[slot]);
    (&g_cutscene_track_recs)[slot] = NULL;
    for (i = 0; i < hdr[0]; i++) {
        heap_free((s32)g_cutscene_actor_blocks[slot][i]);
        g_cutscene_actor_blocks[slot][i] = NULL;
    }
    heap_free((s32)g_cutscene_actor_key_counts[slot]);
    heap_free((s32)g_cutscene_cam_key_counts[slot]);
    heap_free((s32)g_cutscene_event_counts[slot]);
    heap_free((s32)g_cutscene_words[slot]);
    g_cutscene_actor_key_counts[slot] = NULL;
    g_cutscene_cam_key_counts[slot] = NULL;
    g_cutscene_event_counts[slot] = NULL;
    g_cutscene_words[slot] = NULL;
    heap_free((s32)g_scene_event_queue);
    g_scene_event_queue = NULL;
    heap_free((&g_cutscene_scene_assets)[slot]);
    (&g_cutscene_scene_assets)[slot] = 0;
}
extern u8 *g_cutscene_actor_entries[]; /* was D_800C3A10 */

/* was func_1501E7A8 */
void cutscene_actors_reset_anim(s32 arg0)
{
  s32 var_s0;
  s32 n;
  struct127 *e;
  u8 *cnt;
  u8 **tbl;
  u8 *p;
  cnt = &g_cutscene_actor_count[arg0];
  n = *cnt;
  if (n > 0)
  {
    tbl = &g_cutscene_actor_entries[arg0];
    var_s0 = 0;
    do
    {
      p = (*tbl) + var_s0;
      if ((*((u16 *) p)) == 2)
      {
        e = obj_find_by_setup_id(p[2]);
        if (e == 0)
        {
          s32 blk_t; // fakematch: block-local decl (shape D)
          n = *cnt;
        }
        else
        {
          if ((*((u8 *) (((u8 *) e) + 0x6C))) >= 0xA)
          {
            *((u8 *) (((u8 *) e) + 0x6C)) = 0;
            *((s8 *) (((u8 *) e) + 0x6A)) = 0;
          }
          if ((*((u8 *) (((u8 *) e) + 0x6D))) >= 0xA)
          {
            *((u8 *) (((u8 *) e) + 0x6D)) = 0;
            *((s8 *) (((u8 *) e) + 0x6B)) = 0;
          }
          face_anim_reset_default(e);
          n = *cnt;
        }
      }
      if (0) // fakematch: permuter empty if
      {
      }
    }
    while ((var_s0 += 8) < (n * 8));
  }
  tbl++; // fakematch: permuter tbl++/tbl--
  tbl--;
}

/* End of cutscene slot `slot` (skipped != 0: cut short, event 0xF, else 0x10 to node_broadcast_all with the scene
 * number): position back to the start g_cutscene_start_frame, scene marked as seen (cutscene_mark_seen), slot unloaded,
 * per-scene teardown (cutscene_actors_reset_anim, subtitle_slots_close_all, cutscene_teardown_player, cutscene_end_camera_objs, cutscene_free_tables), view reset
 * (camera_projection_set_fov with the game camera's +0x19C / +0x1A0). A queued follow-up scene (g_cutscene_next_scene = scene + 1,
 * level g_cutscene_return_level, 0x25 = load it into level 0x25 temporarily) is loaded at once (cutscene_scene_load, slot state
 * 2); otherwise the screen fade / pause flags are cleared. */
/* was func_1501E888 */
void cutscene_end(s32 skipped, s32 slot) {
    u8 *loaded;
    struct108 *gameCam;
    u8 scene;
    s32 level;
    s32 savedLevel;

    loaded = &g_cutscene_slot_state + slot;
    gameCam = g_player_views;
    if (*loaded == 0) {
        return;
    }
    scene = (&g_cutscene_scene)[slot];
    node_broadcast_all((s32)&scene, skipped ? 0xF : 0x10);
    g_cutscene_prev_frame[slot] = -100;
    (&g_cutscene_frame)[slot] = g_cutscene_start_frame;
    cutscene_mark_seen(g_level_id, (&g_cutscene_scene)[slot]);
    *loaded = 0;
    g_cutscene_in_progress = 0;
    cutscene_actors_reset_anim(slot);
    subtitle_slots_close_all();
    g_cutscene_hide_world = 0;
    g_cutscene_no_pause = 0;
    cutscene_teardown_player(slot);
    cutscene_end_camera_objs(slot);
    cutscene_free_tables(slot);
    g_camera_fov_extra = 0.0f;
    g_camera_viewport_w = 0.0f;
    g_camera_viewport_h = 0.0f;
    camera_projection_set_fov(0, *(f32 *)((u8 *)gameCam + 0x19C), *(f32 *)((u8 *)gameCam + 0x1A0), 1.0f);
    if (g_cutscene_next_scene != 0) {
        *loaded = 2;
        level = g_cutscene_return_level;
        if (level == 0x25) {
            savedLevel = g_level_id;
            g_level_id = 0x25;
        }
        g_cutscene_restart_transition = 0;
        cutscene_scene_load(level, g_cutscene_next_scene - 1, slot, g_cutscene_load_callback, g_cutscene_load_callback_arg);
        if (g_cutscene_return_level == 0x25) {
            g_level_id = savedLevel;
        }
    } else {
        if (g_cutscene_fade_out_at_end != 0) {
            screen_fade_start(0, 0, 0, 0x19, 0, 0);
        }
        g_cutscene_menu_skip_req = 0;
        g_cutscene_treat_as_seen = 0;
        g_cutscene_restart_transition = 0;
    }
}

/* P92: declarations for cutscene_end_camera_objs */
void camera_queue_event(struct108 *, s32, void *);
void cutscene_restore_records(s32);
void cutscene_release_listed_objs(s32);
extern s32 g_camera_event_params;   /* camera event block; was D_800C3A20 */
extern s32 g_obj_scratch_rec;   /* end of the object table g_objects; was D_800D121C; was D_800CC2D0 */
extern f32 g_cutscene_k_6d74;   /* unset g_cutscene_end_cam_value; was D_80096D74; was D_800C3A94 */
extern f32 g_cutscene_k_6d78;   /* unset g_cutscene_end_cam_blend_arg; was D_80096D78; was D_800C3A98 */

/* Scene end, camera and objects of cutscene slot `slot` (called by cutscene_end). The camera event block
 * g_camera_event_params = {1, slot, .., eye = game camera +0x2F8..0x300, 0, +0x388, +0x37C} is sent to the game camera
 * (camera_queue_event event 7) unless g_cutscene_restart_transition; then event 8 with g_cutscene_end_cam_value at +0xC unless it is unset
 * (g_cutscene_k_6d74), and event 10 with g_cutscene_end_cam_blend_arg / g_cutscene_end_cam_blend_time unless that is unset (g_cutscene_k_6d78). Without a queued
 * follow-up scene (g_cutscene_next_scene) and g_cutscene_restart_transition: event 6 (with the slot number as its data), skipped once when
 * g_cutscene_skip_end_cam_event is set (it is cleared). Then cutscene_release_listed_objs (unless g_cutscene_keep_listed_objs[slot]) and cutscene_restore_records; every
 * object of the scene (cutscene_obj_takes_part) gets byte +0xA4 and the floats +0xB8 / +0xC4 cleared. Without a follow-up
 * scene: D_eu_800C3E78 = 2, g_cutscene_focus_set = 0, the start angle / position g_cutscene_focus_yaw / g_cutscene_focus_pos come back from
 * g_cutscene_focus2_yaw / g_cutscene_focus2_pos. */
/* was func_1501EA84 */
void cutscene_end_camera_objs(s32 slot) {
    struct108 *cam;
    s32 *ev;
    u8 *obj;

    ev = &g_camera_event_params;
    cam = g_player_views;
    ev[0] = 1;
    ev[1] = slot;
    ((f32 *)ev)[5] = *(f32 *)((u8 *)cam + 0x2F8);
    ((f32 *)ev)[6] = *(f32 *)((u8 *)cam + 0x2FC);
    ((f32 *)ev)[7] = *(f32 *)((u8 *)cam + 0x300);
    ((f32 *)ev)[8] = 0.0f;
    ((f32 *)ev)[9] = *(f32 *)((u8 *)cam + 0x388);
    ((f32 *)ev)[10] = *(f32 *)((u8 *)cam + 0x37C);
    if (g_cutscene_restart_transition == 0) {
        camera_queue_event(cam, 7, ev);
        if (g_cutscene_end_cam_value != g_cutscene_k_6d74) {
            ((f32 *)ev)[3] = g_cutscene_end_cam_value;
            camera_queue_event(cam, 8, ev);
        }
        if (g_cutscene_end_cam_blend_arg != g_cutscene_k_6d78) {
            ((f32 *)ev)[3] = g_cutscene_end_cam_blend_arg;
            ev[4] = g_cutscene_end_cam_blend_time;
            camera_queue_event(cam, 10, ev);
        }
    }
    if (g_cutscene_next_scene == 0 && g_cutscene_restart_transition == 0) {
        if (g_cutscene_skip_end_cam_event == 0) {
            camera_queue_event(cam, 6, (void *)slot);
        } else {
            g_cutscene_skip_end_cam_event = 0;
        }
    }
    if ((&g_cutscene_keep_listed_objs)[slot] == 0) {
        cutscene_release_listed_objs(slot);
    }
    cutscene_restore_records(slot);
    for (obj = (u8 *)g_objects; obj != (u8 *)&g_obj_scratch_rec; obj += 0x32C) {
        if (*(s32 *)obj != 0 && cutscene_obj_takes_part((s32 *)obj) != 0) {
            obj[0xA4] = 0;
            *(f32 *)(obj + 0xB8) = 0.0f;
            *(f32 *)(obj + 0xC4) = 0.0f;
        }
    }
    if (g_cutscene_next_scene == 0) {
        D_eu_800C3E78 = 2;
        g_cutscene_focus_set = 0;
        g_cutscene_focus_yaw = g_cutscene_focus2_yaw;
        g_cutscene_focus_pos[0] = g_cutscene_focus2_pos[0];
        g_cutscene_focus_pos[1] = g_cutscene_focus2_pos[1];
        g_cutscene_focus_pos[2] = g_cutscene_focus2_pos[2];
    }
}
/* P87: camera / actor track key (8 bytes, g_cutscene_cam_tracks[slot][actor] arrays) */
typedef struct {
    f32 value;
    u8 mode;     /* interpolation into the next key: 0 = spline (catmull_rom_eval), else linear */
    u8 channel;  /* 0 .. 14 */
    s16 frame;   /* 60 Hz frames */
} TrackKey;
#define TRACK_NONE (-9999)
#define TRACK_NONE_F (-9999.0f)   /* D_80096D7C / D_80096DA0: no value */
extern f32 g_cutscene_scene_rot; /* was D_800C39C4 */
f32 catmull_rom_eval(s32 *, s32, f32);
void cutscene_actor_heading_at(s32, f32, f32 *, s32);
void cutscene_actor_place_at(s32, f32, f32 *, f32 *, f32 *, s32);
s32 cutscene_path_point_at(s32, f32, f32 *, s32, s32 *);
void cutscene_path_ctrl_points(u8 *, s32, s32, s32);
extern f32 g_cutscene_k_6d84; /* 0.01; was D_80096D84 */
extern f32 g_cutscene_k_6d80; /* 0.01; was D_80096D80 */
void cutscene_path_prepare_segment(s32, s32, s32);
extern f32 g_cutscene_k_6d9c; /* 0.01; was D_80096D9C */
extern f32 g_cutscene_k_6d88; /* 0.01; was D_80096D88 */
extern f32 g_cutscene_k_6d8c; /* radians to degrees; was D_80096D8C */
/* Camera track pass of cutscene slot `slot` (P72 / P84: the scene loader reads what this writes). Every actor i
 * has a 0x44-byte camera record cam = g_cutscene_track_recs[slot] + i * 17 floats (position 0..2 from its s16 actor record,
 * then per-type defaults, entry type = u16 at g_cutscene_actor_entries[slot] + i * 8). Its keys g_cutscene_cam_tracks[slot][i] (count
 * g_cutscene_cam_key_counts[slot][i]) are 8-byte TrackKey records on 15 channels; each channel is evaluated at the current
 * frame (script position * 60 / 50, or g_cutscene_length_60hz once the slot has ended): before the first key -> no value,
 * at / after the last key -> last value, else spline (mode 0, catmull_rom_eval over the 4 surrounding keys) or
 * linear between the two keys around the frame. Channel 10 (roll) goes to cutscene_actor_heading_at when the actor has a
 * look step (g_cutscene_actor_blocks byte 0 != 0xFF), else channel 7 sets cam[4]; the other channels overwrite cam[3..16]
 * where they have a value; cutscene_actor_place_at then places cam[0..2]. g_cutscene_in_progress = 0 while running, 1 after. */
/* was func_1501ECA4 */
void cutscene_camera_track_pass(s32 slot) {
    TrackKey *keys;
    TrackKey *key;
    f32 *cam;
    u8 *n;
    s32 frame;
    s32 i;
    s32 ch;
    s32 k;
    s32 seen;
    s32 at;
    s32 want;
    s32 flags;
    s32 ia;
    s32 ib;
    f32 t;
    s16 *pos;
    s32 nextFrame[15];
    s32 prevFrame[15];
    s32 nextIdx[15];
    s32 mode[15];
    s32 count[15];
    f32 first[15];
    f32 last[15];
    f32 out[15];
    f32 pts[4];

    if ((&g_cutscene_slot_state)[slot] != 1) {
        return;
    }
    if ((&g_cutscene_frame)[slot] < (&D_eu_800C3A60)[slot]) {
        frame = (&g_cutscene_frame)[slot] * 60 / 50;
    } else {
        frame = g_cutscene_length_60hz;
    }
    g_cutscene_in_progress = 0;
    n = &g_cutscene_actor_count[slot];
    ib = 0;
    for (i = 0; i < *n; i++) {
        cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
        if (g_cutscene_actor_key_counts[slot][i] != 0) {
            pos = (s16 *)D_eu_800C3C88[slot][i];
            cam[0] = pos[0];
            cam[1] = pos[1];
            cam[2] = pos[2];
        } else {
            cam[0] = 0.0f;
            cam[1] = 0.0f;
            cam[2] = 0.0f;
        }
        if (*(u16 *)(g_cutscene_actor_entries[slot] + i * 8) == 4) {
            cam[3] = 64.0f;
            cam[4] = 0.0f;
            cam[5] = 20.0f;
            cam[6] = 255.0f;
            cam[7] = 62.5f;
            cam[8] = 50.0f;
            cam[9] = 0.0f;
            cam[10] = 0.0f;
            cam[11] = 0.0f;
            cam[13] = 0.0f;
        } else {
            cam[3] = 0.0f;
            cam[4] = g_cutscene_scene_rot;
            cam[5] = 0.0f;
            cam[6] = TRACK_NONE_F;
            cam[7] = TRACK_NONE_F;
            cam[8] = TRACK_NONE_F;
            cam[9] = 0.0f;
            cam[10] = 0.0f;
            cam[11] = 0.0f;
            cam[15] = TRACK_NONE_F;
            cam[16] = TRACK_NONE_F;
            cam[12] = TRACK_NONE_F;
        }
        cam[14] = 0.0f;
        switch (*(u16 *)(g_cutscene_actor_entries[slot] + i * 8)) {
            case 1:
                cam[13] = TRACK_NONE_F;
                break;
            case 2:
                cam[13] = 255.0f;
                break;
            case 5:
                cam[6] = 32.0f;
                cam[7] = 32.0f;
                cam[13] = 1.0f;
                break;
            case 3:
                cam[6] = TRACK_NONE_F;
                cam[7] = TRACK_NONE_F;
                cam[8] = TRACK_NONE_F;
                cam[13] = 255.0f;
                break;
        }

        keys = (TrackKey *)g_cutscene_cam_tracks[slot][i];
        if (keys == NULL) {
            continue;
        }
        for (ch = 0; ch < 15; ch++) {
            nextFrame[ch] = TRACK_NONE;
            prevFrame[ch] = TRACK_NONE;
            nextIdx[ch] = TRACK_NONE;
            mode[ch] = 1;
            count[ch] = 0;
            first[ch] = TRACK_NONE_F;
            last[ch] = TRACK_NONE_F;
        }
        /* per channel: the last key before the frame (its mode and frame), the first key at / after it */
        for (k = 0; k < g_cutscene_cam_key_counts[slot][i]; k++) {
            key = &keys[k];
            ch = key->channel;
            if (nextIdx[ch] == TRACK_NONE) {
                if (key->frame < frame) {
                    mode[ch] = key->mode;
                    prevFrame[ch] = key->frame;
                } else {
                    nextIdx[ch] = count[ch];
                    nextFrame[ch] = key->frame;
                }
            }
            last[ch] = key->value;
            if (first[ch] == TRACK_NONE_F) {
                first[ch] = key->value;
            }
            count[ch]++;
        }
        for (ch = 0; ch < 15; ch++) {
            out[ch] = TRACK_NONE_F;
            if (prevFrame[ch] == TRACK_NONE) {
                if (nextFrame[ch] != TRACK_NONE) {
                    out[ch] = first[ch];
                }
            } else if (nextFrame[ch] == TRACK_NONE) {
                out[ch] = last[ch];
            } else {
                t = (f32)(frame - prevFrame[ch]) / (f32)(nextFrame[ch] - prevFrame[ch]);
                if (mode[ch] == 0) {
                    /* spline over keys nextIdx-2 .. nextIdx+1 of the channel, ends repeated */
                    if (nextIdx[ch] - 2 >= 0) {
                        flags = 7;
                        seen = nextIdx[ch] - 2;
                        want = 3;
                        at = 0;
                    } else {
                        flags = 6;
                        seen = nextIdx[ch] - 1;
                        want = 2;
                        at = 1;
                    }
                    if (nextIdx[ch] + 1 < count[ch]) {
                        flags |= 8;
                        want++;
                    }
                    /* ia counts the channel's keys; from index `seen` on they are collected */
                    ia = 0;
                    for (k = 0; k < g_cutscene_cam_key_counts[slot][i] && want != 0; k++) {
                        if (keys[k].channel == ch) {
                            if (ia == seen) {
                                pts[at++] = keys[k].value;
                                want--;
                            } else {
                                ia++;
                            }
                        }
                    }
                    if (!(flags & 1)) {
                        pts[0] = pts[1];
                    }
                    if (!(flags & 8)) {
                        pts[3] = pts[2];
                    }
                    out[ch] = catmull_rom_eval((s32 *)pts, 0, t);
                } else {
                    /* linear between the channel's keys nextIdx-1 (ia) and nextIdx (ib) */
                    seen = 0;
                    ia = -1;
                    for (k = 0; k < g_cutscene_cam_key_counts[slot][i]; k++) {
                        if (keys[k].channel == ch) {
                            if (ia != -1) {
                                ib = k;
                                break;
                            }
                            if (seen + 1 == nextIdx[ch]) {
                                ia = k;
                            } else {
                                seen++;
                            }
                        }
                    }
                    out[ch] = (keys[ib].value - keys[ia].value) * t + keys[ia].value;
                }
            }
        }
        if (out[10] == TRACK_NONE_F) {
            out[10] = 0.0f;
        }
        if (*(u8 *)g_cutscene_actor_blocks[slot][i] != 0xFF) {
            cutscene_actor_heading_at(i, out[10], &cam[4], slot);
        } else if (out[7] != TRACK_NONE_F) {
            cam[4] = out[7];
        }
        if (out[8] != TRACK_NONE_F) {
            cam[3] = out[8];
        }
        if (out[6] != TRACK_NONE_F) {
            cam[5] = out[6];
        }
        if (out[5] != TRACK_NONE_F) {
            cam[6] = out[5];
        }
        if (out[4] != TRACK_NONE_F) {
            cam[7] = out[4];
        }
        if (out[3] != TRACK_NONE_F) {
            cam[8] = out[3];
        }
        if (out[1] != TRACK_NONE_F) {
            cam[9] = out[1];
        }
        if (out[2] != TRACK_NONE_F) {
            cam[10] = out[2];
        }
        if (out[0] != TRACK_NONE_F) {
            cam[11] = out[0];
        }
        if (out[14] != TRACK_NONE_F) {
            cam[12] = out[14];
        }
        if (out[9] != TRACK_NONE_F) {
            cam[13] = out[9];
        }
        if (out[11] != TRACK_NONE_F) {
            cam[14] = out[11];
        }
        if (out[13] != TRACK_NONE_F) {
            cam[15] = out[13];
        }
        if (out[12] != TRACK_NONE_F) {
            cam[16] = out[12];
        }
        cutscene_actor_place_at(i, out[10], &cam[0], &cam[1], &cam[2], slot);
    }
    g_cutscene_in_progress = 1;
}

/* Path point lookup for actor `actor` of cutscene slot `slot` at distance `dist` along its path: binary search of
 * the segment start lengths (SceneActor +4, g_cutscene_actor_key_counts key count entries) gives `seg` (*segOut); a segment change
 * (SceneActor +0x3C) prepares the segment's cubic (cutscene_path_prepare_segment: coefficients D / C / B / A at +0x08 / +0x14 /
 * +0x20 / +0x2C, xyz each). Curved segment (key shape +6 == 0): binary search of the 101 sample lengths
 * (SceneActor +0x38) gives the sample k; out[0..2] / out[3..5] = the cubic at u = k * 0.01 and (k + 1) * 0.01;
 * returns k. Straight segment: out[0..2] = out[3..5] = the point between the middle control points (cutscene_path_ctrl_points)
 * at the distance's fraction of the segment; the asm then returns an uninitialised stack word (callers only read
 * the result of a curved segment): 0 here. A slot without keys leaves `seg` uninitialised in the asm (0 here). */
/* was func_1501F7D4 */
s32 cutscene_path_point_at(s32 actor, f32 dist, f32 *out, s32 slot, s32 *segOut) {
    SceneActor *a;
    f32 pts[12];
    f32 *tab;
    f32 *c;
    f32 *o;
    f32 frac;
    f32 u;
    s32 lo;
    s32 hi;
    s32 mid;
    s32 seg;
    s32 k;
    s32 j;
    u16 shape;

    a = &g_cutscene_actors[slot][actor];
    seg = 0;
    lo = 0;
    hi = g_cutscene_actor_key_counts[slot][actor] - 1;
    if (hi >= 0) {
        tab = a->keys;
        do {
            mid = (lo + hi) / 2;
            if (dist < tab[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
            if (tab[mid] <= dist && dist <= tab[mid + 1]) {
                break;
            }
        } while (lo <= hi);
        seg = mid;
    }
    *segOut = seg;
    if (seg != a->pad3C[0]) {
        cutscene_path_prepare_segment(actor, seg, slot);
    }
    shape = *(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6);
    cutscene_path_ctrl_points((u8 *)pts, D_eu_800C3C88[slot][actor], seg, g_cutscene_actor_key_counts[slot][actor]);
    if (shape == 0) {
        tab = a->state;
        lo = 0;
        hi = 100;
        do {
            k = (lo + hi) / 2;
            if (dist < tab[k]) {
                hi = k - 1;
            } else {
                lo = k + 1;
            }
            if (tab[k] <= dist && dist <= tab[k + 1]) {
                break;
            }
        } while (lo <= hi);
        c = (f32 *)a->pad8;
        for (j = 0; j < 2; j++) {
            u = (f32)(k + j) * g_cutscene_k_6d80;
            o = out + j * 3;
            o[0] = c[0] + ((c[9] * u + c[6]) * u + c[3]) * u;
            o[1] = c[1] + ((c[10] * u + c[7]) * u + c[4]) * u;
            o[2] = c[2] + ((c[11] * u + c[8]) * u + c[5]) * u;
        }
        return k;
    }
    tab = a->keys;
    if (tab[seg + 1] - tab[seg] == 0.0f) {
        frac = 0.0f;
    } else {
        frac = (dist - tab[seg]) / (tab[seg + 1] - tab[seg]);
    }
    for (j = 0; j < 2; j++) {
        o = out + j * 3;
        o[0] = pts[3] + (pts[6] - pts[3]) * frac;
        o[1] = pts[4] + (pts[7] - pts[4]) * frac;
        o[2] = pts[5] + (pts[8] - pts[5]) * frac;
    }
    return 0;
}
/* Place actor `actor` of cutscene slot `slot` at `t` percent (clamped to 0..100) of its path length (SceneActor
 * +0, needs >= 2 path keys). cutscene_path_point_at finds the segment `seg` holding that distance, two points (ends[0..2],
 * ends[3..5]) and the sample `k` of the actor's length table (SceneActor +0x38). On a curved segment (key shape
 * +6 == 0, cutscene_path_compute_length) the position is interpolated between the two points by the distance's fraction between
 * the lengths of samples k and k + 1; on a straight one it is the first point. */
/* was func_1501FD34 */
void cutscene_actor_place_at(s32 actor, f32 t, f32 *x, f32 *y, f32 *z, s32 slot) {
    SceneActor *a;
    f32 ends[6];
    f32 dist;
    f32 frac;
    f32 *len;
    s32 seg;
    s32 k;

    if (g_cutscene_actor_key_counts[slot][actor] < 2) {
        return;
    }
    if (100.0f < t) {
        t = 100.0f;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }
    a = &g_cutscene_actors[slot][actor];
    dist = *(f32 *)a->pad0 * t * g_cutscene_k_6d84;
    k = cutscene_path_point_at(actor, dist, ends, slot, &seg);
    if (*(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6) == 0) {
        len = (f32 *)a->state + k;
        if (len[1] - len[0] == 0.0f) {
            frac = 0.0f;
        } else {
            frac = (dist - len[0]) / (len[1] - len[0]);
        }
        *x = (ends[3] - ends[0]) * frac + ends[0];
        *y = (ends[4] - ends[1]) * frac + ends[1];
        *z = (ends[5] - ends[2]) * frac + ends[2];
    } else {
        *x = ends[0];
        *y = ends[1];
        *z = ends[2];
    }
}
/* Heading of actor `actor` of cutscene slot `slot` at `t` percent (clamped to 0..100) of its path length (needs
 * >= 2 path keys), in degrees (math_atan2f(dx, dz) * g_cutscene_k_6d8c). cutscene_path_point_at finds the segment for that
 * distance: on a curved segment (key shape +6 == 0, cutscene_path_compute_length) the direction runs between the two curve
 * points it returns (first - second), on a straight one between the segment's middle control points
 * (cutscene_path_ctrl_points, third - second). */
/* was func_1501FF10 */
void cutscene_actor_heading_at(s32 actor, f32 t, f32 *out, s32 slot) {
    f32 pts[12];
    f32 ends[6];
    f32 dx;
    f32 dz;
    s32 seg;

    if (g_cutscene_actor_key_counts[slot][actor] < 2) {
        return;
    }
    if (100.0f < t) {
        t = 100.0f;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }
    cutscene_path_point_at(actor, *(f32 *)g_cutscene_actors[slot][actor].pad0 * t * g_cutscene_k_6d88, ends, slot, &seg);
    if (*(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6) == 0) {
        dx = ends[0] - ends[3];
        dz = ends[2] - ends[5];
    } else {
        cutscene_path_ctrl_points((u8 *)pts, D_eu_800C3C88[slot][actor], seg, g_cutscene_actor_key_counts[slot][actor]);
        dx = pts[6] - pts[3];
        dz = pts[8] - pts[5];
    }
    *out = math_atan2f(dx, dz) * g_cutscene_k_6d8c;
}
/* was func_15020090 */
void cutscene_path_ctrl_points(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 *var_t0;
    s16 var_t6;
    s16 var_t6_2;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_t9;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_t0;
    u8 *var_a1_2;
    u8 *var_a1_3;
    u8 *var_t0_2;

    temp_v1 = arg2 - 1;
    var_v0 = 6;
    if (temp_v1 >= 0) {
        var_v0 = 7;
        var_a0 = temp_v1;
        var_a1 = 3;
        var_a3 = 0;
    } else {
        var_a0 = arg2;
        var_a1 = 2;
        var_a3 = 1;
    }
    if ((arg2 + 2) < arg3) {
        var_v0 |= 8;
        var_a1 += 1;
    }
    temp_a2 = var_a0 + var_a1;
    var_v1 = var_a0;
    if (var_a0 < temp_a2) {
        temp_t9 = (temp_a2 - var_a0) & 3;
        temp_t1 = temp_t9 + var_a0;
        if (temp_t9 != 0) {
            var_a1_2 = arg0 + (var_a3 * 0xC);
            var_t0 = arg1 + (var_a0 * 8);
            var_v1 += 1;
            var_t6 = *var_t0;
            if (temp_t1 != var_v1) {
                do {
                    var_v1 += 1;
                    var_a3 += 1;
                    var_a1_2 += 0xC;
                    var_t0 = (s16 *)((u8 *)var_t0 + (8));
                    (*(f32 *)((u8 *)var_a1_2 + -0xC)) = (f32) var_t6;
                    (*(f32 *)((u8 *)var_a1_2 + -8)) = (f32) (*(s16 *)((u8 *)var_t0 + -6));
                    (*(f32 *)((u8 *)var_a1_2 + -4)) = (f32) (*(s16 *)((u8 *)var_t0 + -4));
                    var_t6 = (*(s16 *)((u8 *)var_t0 + 0));
                } while (temp_t1 != var_v1);
            }
            var_a3 += 1;
            temp_a1 = var_a1_2 + 0xC;
            temp_t0 = ((s16 *)((u8 *)var_t0 + 8));
            (*(f32 *)((u8 *)temp_a1 + -0xC)) = (f32) var_t6;
            (*(f32 *)((u8 *)temp_a1 + -8)) = (f32) (*(s16 *)((u8 *)temp_t0 + -6));
            (*(f32 *)((u8 *)temp_a1 + -4)) = (f32) (*(s16 *)((u8 *)temp_t0 + -4));
            if (var_v1 != temp_a2) {
                goto block_10;
            }
        } else {
block_10:
            var_a1_3 = arg0 + (var_a3 * 0xC);
            temp_a0 = (temp_a2 * 8) + arg1;
            var_t0_2 = arg1 + (var_v1 * 8) + 0x20;
            var_t6_2 = (*(s16 *)((u8 *)var_t0_2 + -0x20));
            if ((s32)var_t0_2 != (s32)temp_a0) {
                do {
                    var_t0_2 += 0x20;
                    var_a1_3 += 0x30;
                    (*(f32 *)((u8 *)var_a1_3 + -0x30)) = (f32) var_t6_2;
                    (*(f32 *)((u8 *)var_a1_3 + -0x2C)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x3E));
                    (*(f32 *)((u8 *)var_a1_3 + -0x28)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x3C));
                    (*(f32 *)((u8 *)var_a1_3 + -0x24)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x38));
                    (*(f32 *)((u8 *)var_a1_3 + -0x20)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x36));
                    (*(f32 *)((u8 *)var_a1_3 + -0x1C)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x34));
                    (*(f32 *)((u8 *)var_a1_3 + -0x18)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x30));
                    (*(f32 *)((u8 *)var_a1_3 + -0x14)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x2E));
                    (*(f32 *)((u8 *)var_a1_3 + -0x10)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x2C));
                    (*(f32 *)((u8 *)var_a1_3 + -0xC)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x28));
                    (*(f32 *)((u8 *)var_a1_3 + -8)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x26));
                    (*(f32 *)((u8 *)var_a1_3 + -4)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x24));
                    var_t6_2 = (*(s16 *)((u8 *)var_t0_2 + -0x20));
                } while ((s32)var_t0_2 != (s32)temp_a0);
            }
            temp_a1_2 = var_a1_3 + 0x30;
            (*(f32 *)((u8 *)temp_a1_2 + -0x30)) = (f32) var_t6_2;
            (*(f32 *)((u8 *)temp_a1_2 + -0x2C)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x1E));
            (*(f32 *)((u8 *)temp_a1_2 + -0x28)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x1C));
            (*(f32 *)((u8 *)temp_a1_2 + -0x24)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x18));
            (*(f32 *)((u8 *)temp_a1_2 + -0x20)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x16));
            (*(f32 *)((u8 *)temp_a1_2 + -0x1C)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x14));
            (*(f32 *)((u8 *)temp_a1_2 + -0x18)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x10));
            (*(f32 *)((u8 *)temp_a1_2 + -0x14)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0xE));
            (*(f32 *)((u8 *)temp_a1_2 + -0x10)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0xC));
            (*(f32 *)((u8 *)temp_a1_2 + -0xC)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -8));
            (*(f32 *)((u8 *)temp_a1_2 + -8)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -6));
            (*(f32 *)((u8 *)temp_a1_2 + -4)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -4));
        }
    }
    if (!(var_v0 & 1)) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0xC));
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x10));
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    }
    if (!(var_v0 & 8)) {
        (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) (*(f32 *)((u8 *)arg0 + 0x18));
        (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C));
        (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (*(f32 *)((u8 *)arg0 + 0x20));
    }
}
/* Path length of actor `actor` of cutscene slot `slot` (needs >= 2 path keys, g_cutscene_actor_key_counts count; keys are the
 * 8-byte records D_eu_800C3C88[slot][actor], +6 = segment shape). For every segment the 4 control points come
 * from cutscene_path_ctrl_points; keys[seg] (g_cutscene_actors actor +4) = the length up to the segment's start. A curved segment
 * (shape 0) is measured as a Catmull-Rom curve sampled every 0.01 (chords between successive samples, the
 * previous sample in the other half of `prev`, which carries over between segments), a straight one as the
 * distance between its two middle points. +0 = the total length, keys[count - 1] = it too; +0x3C = 0xFF. */
/* was func_15020430 */
void cutscene_path_compute_length(s32 actor, s32 slot) {
    SceneActor *act;
    s32 seg;
    s32 c;
    u16 shape;
    u8 cur;
    f32 total;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    f32 pts[4][3];
    f32 A[3];
    f32 B[3];
    f32 C[3];
    f32 D[3];
    f32 prev[2][3];

    if (g_cutscene_actor_key_counts[slot][actor] < 2) {
        return;
    }
    g_cutscene_actors[slot][actor].pad3C[0] = 0xFF;
    total = 0.0f;
    cur = 0;
    for (seg = 0; seg < g_cutscene_actor_key_counts[slot][actor] - 1; seg++) {
        shape = *(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6);
        /* P87: the asm leaves the key count in a3; cutscene_path_ctrl_points reads it (dropped argument) */
        cutscene_path_ctrl_points((u8 *)pts, D_eu_800C3C88[slot][actor], seg, g_cutscene_actor_key_counts[slot][actor]);
        ((f32 *)g_cutscene_actors[slot][actor].keys)[seg] = total;
        if (shape == 0) {
            for (c = 0; c < 3; c++) {
                A[c] = 0.5f * pts[3][c] + ((-0.5f * pts[0][c] + 1.5f * pts[1][c]) + -1.5f * pts[2][c]);
                B[c] = -0.5f * pts[3][c] + ((pts[0][c] + -2.5f * pts[1][c]) + (pts[2][c] + pts[2][c]));
                C[c] = 0.5f * pts[2][c] + -0.5f * pts[0][c];
                D[c] = pts[1][c];
            }
            for (c = 0; c < 3; c++) {
                prev[cur == 0][c] = D[c];
            }
            for (t = 0.01f; t <= 1.0f; t += 0.01f) {
                x = D[0] + ((A[0] * t + B[0]) * t + C[0]) * t;
                prev[cur][0] = x;
                y = D[1] + ((A[1] * t + B[1]) * t + C[1]) * t;
                prev[cur][1] = y;
                z = D[2] + ((A[2] * t + B[2]) * t + C[2]) * t;
                prev[cur][2] = z;
                dx = x - prev[cur == 0][0];
                dy = y - prev[cur == 0][1];
                dz = prev[cur][2] - prev[cur == 0][2];
                d = dx * dx + (dy * dy + dz * dz);
                if (d != 0.0f) {
                    total += sqrtf(d);
                }
                cur ^= 1;
            }
        } else {
            dz = pts[2][2] - pts[1][2];
            dx = pts[2][0] - pts[1][0];
            dy = pts[2][1] - pts[1][1];
            total += sqrtf(dz * dz + (dx * dx + dy * dy));
        }
    }
    ((f32 *)g_cutscene_actors[slot][actor].keys)[seg] = total;
    *(f32 *)g_cutscene_actors[slot][actor].pad0 = total;
    g_cutscene_actors[slot][actor].pad3C[0] = 0xFF;
}

/* Prepares segment `seg` of the path of actor `actor` of cutscene slot `slot` (needs seg < key count - 1).
 * The segment's control points P0..P3 (cutscene_path_ctrl_points, xyz each) give the Catmull-Rom cubic
 * D + (C + (B + A u) u) u with D = P1, C = (P2 - P0) / 2, B = P0 - 2.5 P1 + 2 P2 - P3 / 2,
 * A = (P3 - P0) / 2 + 1.5 (P1 - P2), stored per axis at SceneActor +0x08 / +0x14 / +0x20 / +0x2C.
 * The 101-entry length table (SceneActor +0x38) gets the path length at each sample: on a curved segment (key
 * shape +6 == 0) the segment start length (keys[seg]) plus the chord lengths between the samples at u = 0, 0.01,
 * ...; on a straight one i / 101 of the segment length (keys[seg + 1] - keys[seg]), from 0. SceneActor +0x3C
 * remembers the prepared segment. */
/* was func_15020920 */
void cutscene_path_prepare_segment(s32 actor, s32 seg, s32 slot) {
    SceneActor *a;
    f32 pts[12];
    f32 cA[3];
    f32 cB[3];
    f32 cC[3];
    f32 cD[3];
    f32 prev[2][3];
    f32 *c;
    f32 *cur;
    f32 *old;
    f32 len;
    f32 step;
    f32 u;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d2;
    s32 cnt;
    s32 i;
    u16 shape;
    u8 flip;

    cnt = g_cutscene_actor_key_counts[slot][actor];
    if (seg >= cnt - 1) {
        return;
    }
    a = &g_cutscene_actors[slot][actor];
    len = ((f32 *)a->keys)[seg];
    shape = *(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6);
    flip = 0;
    cutscene_path_ctrl_points((u8 *)pts, D_eu_800C3C88[slot][actor], seg, cnt);
    if (shape == 0) {
        c = (f32 *)a->pad8;
        for (i = 0; i < 3; i++) {
            cA[i] = pts[9 + i] * 0.5f + ((-0.5f * pts[i] + 1.5f * pts[3 + i]) + -1.5f * pts[6 + i]);
            cB[i] = pts[9 + i] * -0.5f + ((pts[i] + -2.5f * pts[3 + i]) + (pts[6 + i] + pts[6 + i]));
            cC[i] = pts[6 + i] * 0.5f + -0.5f * pts[i];
            cD[i] = pts[3 + i];
            c[i] = cD[i];
            c[3 + i] = cC[i];
            c[6 + i] = cB[i];
            c[9 + i] = cA[i];
        }
        ((f32 *)a->state)[0] = len;
        for (i = 0; i < 3; i++) {
            prev[1][i] = cD[i];
        }
        step = g_cutscene_k_6d9c;
        i = 1;
        for (u = step; u <= 1.0f; u += step) {
            cur = prev[flip];
            old = prev[flip == 0];
            cur[0] = cD[0] + ((cA[0] * u + cB[0]) * u + cC[0]) * u;
            cur[1] = cD[1] + ((cA[1] * u + cB[1]) * u + cC[1]) * u;
            cur[2] = cD[2] + ((cA[2] * u + cB[2]) * u + cC[2]) * u;
            dx = cur[0] - old[0];
            dy = cur[1] - old[1];
            dz = cur[2] - old[2];
            d2 = dx * dx + (dy * dy + dz * dz);
            if (d2 != 0.0f) {
                len += sqrtf(d2);
            }
            ((f32 *)a->state)[i] = len;
            flip ^= 1;
            i++;
        }
    } else {
        len = ((f32 *)a->keys)[seg + 1] - len;
        for (i = 0; i < 101; i++) {
            ((f32 *)a->state)[i] = (f32)i * len / 101.0f;
        }
    }
    a->pad3C[0] = seg;
}
s32 cutscene_find_camera_actor(s32, s32);
void camera_queue_event(struct108 *, s32, void *);
void camera_process_events(struct108 *);
void ambient_extra_flame_queue_cam(s16, s16, s16, s32, s32, s32);
extern u8 g_cutscene_camera_actor; /* was D_800C3A18 */
extern s32 g_camera_event_params;   /* camera event block (camera_queue_event event 7); was D_800C3A20 */
extern f32 g_camera_event_target_x;   /* g_camera_event_params + 0x20: look target; was D_800C3A40; was D_800C3A20 */
extern f32 g_camera_event_target_y; /* was D_800C3A44 */
extern f32 g_camera_event_target_z; /* was D_800C3A48 */
/* Applies the camera records of cutscene slot `slot` (written by cutscene_camera_track_pass) to the game. g_cutscene_camera_actor = the
 * actor whose record drives the game camera (cutscene_find_camera_actor at the current script position, cached until reset
 * to 0xFF). Two passes over the active actors (g_cutscene_cam_key_counts / g_cutscene_actor_key_counts counts != 0): pass 0 every entry type
 * but 1, pass 1 type 1 (the camera; so the camera sees the objects already placed). Entry = 8 bytes at
 * g_cutscene_actor_entries[slot] + i * 8: u16 type, u8 a, s8 b, s16 c.
 *   type 1 (camera, only actor g_cutscene_camera_actor): clamps cam[13] / cam[15] / cam[16] to -20 .. 40, fills the camera
 *     event block g_camera_event_params (eye cam[0..2]; target by a: 1 = actor b's position raised by c (+ cam[14]),
 *     2 = object obj_find_by_setup_id(b), 3 = entity world_record_find(b) raised by c, 0 = angle mode) and sends it to the
 *     game camera g_player_views (camera_queue_event event 7; event 5 + camera_process_events first unless flag 0x40000).
 *   type 3: entity world_record_find(a) gets position / angles / scale (* 0.01) / alpha from the record.
 *   type 2: object obj_find_by_setup_id(a) takes its actor frame (cutscene_actor_apply_track(obj, slot, i)).
 *   type 5: when cam[13] >= 1, ambient_extra_flame_queue_cam at the record position with cam[6] / cam[7].
 * g_cutscene_in_progress = 0 while running, 1 after. */
/* was func_15020F6C */
void cutscene_apply_cameras(s32 slot) {
    f32 *cams;
    f32 *cam;
    f32 *other;
    u8 *ent;
    u8 *ev;
    u8 *e;
    struct108 *gameCam;
    s32 pass;
    s32 i;
    s32 a;
    f32 f;
    f32 v15;
    f32 v16;

    if ((&g_cutscene_slot_state)[slot] != 1) {
        return;
    }
    g_cutscene_in_progress = 0;
    if (g_cutscene_camera_actor == 0xFF) {
        g_cutscene_camera_actor = cutscene_find_camera_actor(slot, (&g_cutscene_frame)[slot]);
    }
    ev = (u8 *)&g_camera_event_params;
    for (pass = 0; pass != 2; pass++) {
        for (i = 0; i < g_cutscene_actor_count[slot]; i++) {
            if (g_cutscene_cam_key_counts[slot][i] == 0 || g_cutscene_actor_key_counts[slot][i] == 0) {
                continue;
            }
            ent = g_cutscene_actor_entries[slot] + i * 8;
            if (pass == 0) {
                if (*(u16 *)ent == 1) {
                    continue;
                }
            } else if (*(u16 *)ent != 1) {
                continue;
            }
            switch (*(u16 *)ent) {
                case 1:
                    gameCam = g_player_views;
                    if (i != g_cutscene_camera_actor) {
                        break;
                    }
                    if (!(*(s32 *)((u8 *)gameCam + 0x2C) & 0x40000)) {
                        if (g_cutscene_restart_transition == 0) {
                            camera_queue_event(gameCam, 5, (void *)slot);
                        }
                        camera_process_events(gameCam);
                    }
                    cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
                    f = cam[13];
                    if (f == TRACK_NONE_F) {
                        *(f32 *)(ev + 8) = 0.0f;
                    } else {
                        cam[13] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
                        *(f32 *)(ev + 8) = cam[13];
                    }
                    f = cam[15];
                    if (f == TRACK_NONE_F) {
                        v15 = 0.0f;
                    } else {
                        cam[15] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
                        v15 = cam[15];
                    }
                    f = cam[16];
                    if (f == TRACK_NONE_F) {
                        v16 = 0.0f;
                    } else {
                        cam[16] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
                        v16 = cam[16];
                    }
                    ent = g_cutscene_actor_entries[slot] + i * 8;
                    *(s32 *)(ev + 4) = slot;
                    *(f32 *)(ev + 0x14) = cam[0];
                    *(f32 *)(ev + 0x18) = cam[1];
                    *(f32 *)(ev + 0x1C) = cam[2];
                    switch (ent[2]) {
                        case 1:
                            /* look at actor ent[3], raised by the entry's s16 */
                            *(s32 *)ev = 0;
                            cams = (f32 *)(&g_cutscene_track_recs)[slot];
                            other = cams + (s8)ent[3] * 17;
                            *(f32 *)(ev + 0x20) = other[0];
                            *(f32 *)(ev + 0x24) = cam[14] + (other[1] + (f32)*(s16 *)(ent + 4));
                            *(f32 *)(ev + 0x28) = other[2];
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 2:
                            /* look at object ent[3] */
                            e = (u8 *)obj_find_by_setup_id(ent[3]);
                            if (e == NULL) {
                                continue;
                            }
                            *(s32 *)ev = 0;
                            g_camera_event_target_x = *(f32 *)(e + 0x14);
                            ent = g_cutscene_actor_entries[slot] + i * 8;
                            cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
                            g_camera_event_target_y = cam[14] + (*(f32 *)(e + 0x18) + (f32)*(s16 *)(ent + 4));
                            g_camera_event_target_z = *(f32 *)(e + 0x1C);
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 3:
                            /* look at entity ent[3] (s16 position) */
                            e = world_record_find(ent[3]);
                            if (e == NULL) {
                                continue;
                            }
                            *(s32 *)ev = 0;
                            g_camera_event_target_x = *(s16 *)(e + 0x10);
                            ent = g_cutscene_actor_entries[slot] + i * 8;
                            cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
                            g_camera_event_target_y = cam[14] + (f32)(*(s16 *)(e + 0x12) + *(s16 *)(ent + 4));
                            g_camera_event_target_z = *(s16 *)(e + 0x14);
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 0:
                            /* angle mode */
                            *(s32 *)ev = 1;
                            *(f32 *)(ev + 0x20) = -cam[5];
                            *(f32 *)(ev + 0x24) = cam[3];
                            *(f32 *)(ev + 0x28) = cam[4];
                            *(f32 *)(ev + 0x2C) = v15;
                            *(f32 *)(ev + 0x30) = v16;
                            *(f32 *)(ev + 0x18) = cam[1] + cam[14];
                            break;
                    }
                    if (g_cutscene_restart_transition == 0) {
                        camera_queue_event(gameCam, 7, ev);
                    }
                    break;
                case 3:
                    e = world_record_find(ent[2]);
                    if (e == NULL) {
                        continue;
                    }
                    e[0x4E] = 0;
                    e[0x6F] &= 0x7F;
                    cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
                    *(s16 *)(e + 0x10) = (s32)cam[0];
                    *(s16 *)(e + 0x12) = (s32)(cam[14] + cam[1]);
                    *(s16 *)(e + 0x14) = (s32)cam[2];
                    *(f32 *)(e + 0x0) = cam[3];
                    *(f32 *)(e + 0x4) = cam[4];
                    *(f32 *)(e + 0x8) = cam[5];
                    if (cam[6] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x2C) = cam[6] * 0.01f;
                    }
                    if (cam[7] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x30) = cam[7] * 0.01f;
                    }
                    if (cam[8] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x34) = cam[8] * 0.01f;
                    }
                    a = cam[13];
                    e[0x8A] = (a >= 0x100) ? 0xFF : (a >= 0) ? a : 0;
                    break;
                case 2:
                    cutscene_actor_apply_track(obj_find_by_setup_id(ent[2]), slot, i);
                    break;
                case 5:
                    cam = (f32 *)(&g_cutscene_track_recs)[slot] + i * 17;
                    if (1.0f <= cam[13]) {
                        ambient_extra_flame_queue_cam((s32)cam[0], (s32)cam[1], (s32)cam[2], 0, (s32)cam[6], (s32)cam[7]);
                    }
                    break;
            }
        }
    }
    g_cutscene_in_progress = 1;
}

/*
 * P53: place an actor on its spawn / cutscene marker of player slot arg1 (arg2 = one marker, -1 = all) and refresh
 * its floor (collision_find_floor: floor triangle, height, water level). Hand-written (m2c gave no draft: the f32 -> u32
 * angle conversion minus 0x4000 and the 0x44-byte marker records).
 */
void collision_find_floor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
extern u16 *g_cutscene_actor_key_counts[]; /* was D_800C39E8 */
extern u8 *g_cutscene_actor_entries[]; /* was D_800C3A10 */
extern u8 g_obj_updating_slot; /* was D_800D39FC */
extern f32 g_cutscene_k_6db0; /* "unset" scale marker; was D_80096DB0 */
extern f32 g_cutscene_k_6db4; /* no water level; was D_80096DB4 */
extern f32 g_cutscene_k_6db8; /* scale factor; was D_80096DB8 */
extern f32 g_cutscene_k_6dbc; /* degrees to the 16-bit angle; was D_80096DBC */
#define A834_F(o) (*(f32 *)((u8 *)obj + (o)))
#define A834_M(o) (*(f32 *)(mk + (o)))

/* was func_15021834 */
void cutscene_actor_apply_track(struct127 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 end;
    s32 scaled;
    u8 *e;
    u8 *mk;
    struct127 *obj;
    f32 ox, oz, d, a;
    f32 floorY;
    u32 ang;

    if ((&g_cutscene_slot_state)[arg1] != 1) {
        return;
    }
    g_cutscene_in_progress = 0;
    if (arg2 != -1) {
        i = arg2;
        end = arg2 + 1;
    } else {
        i = 0;
        end = g_cutscene_actor_count[arg1];
    }
    for (; i < end; i++) {
        if (g_cutscene_actor_key_counts[arg1][i] == 0) continue;
        e = g_cutscene_actor_entries[arg1] + i * 8;
        if (*(u16 *)e != 2) continue;
        obj = obj_find_by_setup_id(e[2]);
        if (obj == NULL || obj != arg0) continue;
        mk = (u8 *)(&g_cutscene_track_recs)[arg1] + i * 0x44;
        ox = A834_F(0x14);
        oz = A834_F(0x1C);
        A834_F(0x14) = A834_M(0x0);
        A834_F(0x18) = A834_M(0x38) + A834_M(0x4);
        A834_F(0x1CC) = A834_F(0x18);
        A834_F(0x1C) = A834_M(0x8);
        if (g_cutscene_skip_state == 0) {
            d = A834_F(0x1C) - oz;
            a = A834_F(0x14) - ox;
            A834_F(0x3C) = d * d + a * a;
            if (A834_F(0x3C) != 0.0f) {
                A834_F(0x3C) = sqrtf(A834_F(0x3C)) * 2.0f;
            }
        } else {
            A834_F(0x3C) = 0.0f;
        }
        if (*(f32 **)((u8 *)obj + 0x31C) != NULL) {
            **(f32 **)((u8 *)obj + 0x31C) = A834_F(0x3C) * 2.0f;
        }
        A834_F(0x54) = 0.0f;
        *(s16 *)((u8 *)obj + 0xCC) = 0;
        g_obj_updating_slot = (arg0 - g_objects) + 1;
        collision_find_floor((s32)obj + 0x188, (s32)obj + 0x18C, (s32)&floorY, (s32)obj + 0x118, (s32)obj + 0x184,
                      (s32)obj + 0x1A2, A834_F(0x14), A834_F(0x18), A834_F(0x1C), A834_F(0x18), 0, (s32)obj,
                      g_cutscene_k_6db4, *(f32 *)((u8 *)arg0 + 0x18));
        g_obj_updating_slot = 0;
        A834_F(0x180) = floorY;
        *((u8 *)obj + 0xD0) = 0;
        A834_F(0x28) = A834_F(0x18) - A834_F(0x180);
        if (*(s32 *)obj == 1) {
            if (g_cutscene_k_6db4 != A834_F(0x118) && A834_F(0x18) < A834_F(0x118)) {
                *((u8 *)obj + 0xAD) = 1;
            } else {
                *((u8 *)obj + 0xAD) = 0;
                *(s16 *)((u8 *)obj + 0xB2) = 0;
            }
        }
        scaled = 0;
        if (g_cutscene_k_6db0 != A834_M(0x18)) {
            scaled = 1;
            A834_F(0x14C) = A834_M(0x18) * g_cutscene_k_6db8;
            A834_F(0x154) = A834_M(0x18) * g_cutscene_k_6db8;
        }
        if (g_cutscene_k_6db0 != A834_M(0x1C)) {
            scaled = 1;
            A834_F(0x150) = A834_M(0x1C) * g_cutscene_k_6db8;
            A834_F(0x158) = A834_M(0x1C) * g_cutscene_k_6db8;
        }
        if (scaled) {
            obj_set_scale(obj, A834_F(0x14C), A834_F(0x150));
        }
        A834_F(0xB8) = A834_M(0xC);
        a = A834_M(0x10) + 180.0f;
        while (a >= 360.0f) a -= 360.0f;
        while (a < 0.0f) a += 360.0f;
        ang = (u32)(a * g_cutscene_k_6dbc) - 0x4000;
        *(u16 *)((u8 *)obj + 0x78) = ang;
        *(u16 *)((u8 *)obj + 0x7A) = ang;
        *(u16 *)((u8 *)obj + 0x76) = ang;
        A834_F(0x40) = a;
        A834_F(0xC4) = A834_M(0x14);
        if (A834_M(0x34) < 0.0f) {
            A834_M(0x34) = 0.0f;
        } else {
            A834_M(0x34) = (A834_M(0x34) > 255.0f) ? 255.0f : A834_M(0x34);
        }
        obj_fade_command(obj, 1, (u32)A834_M(0x34) & 0xFF, 0, 0);
        A834_F(0x2C) = A834_F(0x14);
        A834_F(0x30) = A834_F(0x18);
        A834_F(0x34) = A834_F(0x1C);
    }
    g_cutscene_in_progress = 1;
}

extern f32 g_cutscene_k_6dc0; /* was D_80096DC0 */
/* Look target of the actor of player `player` in sequence slot `slot` (g_cutscene_slot_state[slot] == 1: a cutscene runs):
 * the first live actor (g_cutscene_actor_key_counts id != 0) whose record (g_cutscene_actor_entries, kind 2) names the player's room.
 * Its look step (g_cutscene_actor_blocks +2) gives a point next to entity r[5] (g_cutscene_track_recs 0x44-byte records) raised by r[6]:
 * written to pos, returns 0. Without one, look step +1: entity 0 = fixed angles (record i +0x24 / +0x28 / +0x2C
 * to outB / outA / outC, returns 1), else the camera point (g_player_views +0x2F8) raised by r[6]. No step: pos =
 * g_cutscene_k_6dc0 x3. */
/* was func_15021E60 */
s32 cutscene_player_look_target(f32 *outA, f32 *outB, f32 *outC, f32 *pos, s32 player, s32 slot) {
    u16 *ids;
    u8 *e;
    u8 *step;
    u8 *r;
    f32 *q;
    s32 n;
    s32 i;

    if ((&g_cutscene_slot_state)[slot] != 1) {
        return 0;
    }
    n = g_cutscene_actor_count[slot];
    ids = g_cutscene_actor_key_counts[slot];
    for (i = 0; i < n; i++, ids++) {
        if (*ids == 0) {
            continue;
        }
        e = g_cutscene_actor_entries[slot] + i * 8;
        if (*(u16 *)e != 2) {
            continue;
        }
        if (*((u8 *)g_objects + player * 0x32C + 0x3B) != e[2]) {
            continue;
        }
        step = (u8 *)g_cutscene_actor_blocks[slot][i];
        if (step[2] != 0xFF) {
            r = (u8 *)g_cutscene_event_tracks[slot][i] + step[2] * 8;
            q = (f32 *)(((u8 **)&g_cutscene_track_recs)[slot] + (s8)r[5] * 0x44);
            pos[0] = q[0];
            pos[1] = q[1] + (f32)*(s16 *)(r + 6);
            pos[2] = q[2];
            return 0;
        }
        if (step[1] != 0xFF) {
            r = (u8 *)g_cutscene_event_tracks[slot][i] + step[1] * 8;
            if ((s8)r[5] == 0) {
                q = (f32 *)(((u8 **)&g_cutscene_track_recs)[slot] + i * 0x44);
                *outA = q[10];
                *outB = q[9];
                *outC = q[11];
                return 1;
            }
            pos[0] = *(f32 *)((u8 *)g_player_views + 0x2F8);
            pos[1] = *(f32 *)((u8 *)g_player_views + 0x2FC) + (f32)*(s16 *)(r + 6);
            pos[2] = *(f32 *)((u8 *)g_player_views + 0x300);
            return 0;
        }
        pos[0] = g_cutscene_k_6dc0;
        pos[1] = g_cutscene_k_6dc0;
        pos[2] = g_cutscene_k_6dc0;
        return 0;
    }
    return 0;
}

extern f32 g_cutscene_k_6dc4; /* was D_80096DC4 */
/* Look limits of the actor of player `player` in sequence slot `slot` (same search as cutscene_player_look_target): both
 * pairs are cleared, then entity record i +0x3C (into b[0], b[1]) and +0x40 (into a[0], a[1]) unless they hold the
 * "unset" value g_cutscene_k_6dc4. Returns 1 when the actor was found. */
/* was func_150220CC */
s32 cutscene_player_look_limits(f32 *a, f32 *b, s32 player, s32 slot) {
    u16 *ids;
    u8 *e;
    f32 *q;
    s32 n;
    s32 i;

    if ((&g_cutscene_slot_state)[slot] != 1) {
        return 0;
    }
    n = g_cutscene_actor_count[slot];
    ids = g_cutscene_actor_key_counts[slot];
    for (i = 0; i < n; i++, ids++) {
        if (*ids == 0) {
            continue;
        }
        e = g_cutscene_actor_entries[slot] + i * 8;
        if (*(u16 *)e != 2) {
            continue;
        }
        if (*((u8 *)g_objects + player * 0x32C + 0x3B) != e[2]) {
            continue;
        }
        a[1] = 0.0f;
        b[1] = 0.0f;
        a[0] = 0.0f;
        b[0] = 0.0f;
        q = (f32 *)(((u8 **)&g_cutscene_track_recs)[slot] + i * 0x44);
        if (q[15] != g_cutscene_k_6dc4) {
            b[0] = q[15];
            b[1] = b[0];
        }
        if (q[16] != g_cutscene_k_6dc4) {
            a[0] = q[16];
            a[1] = a[0];
        }
        return 1;
    }
    return 0;
}

/* was func_15022238 */
void cutscene_set_focus_point(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    g_cutscene_focus_yaw = arg3;
    g_cutscene_focus_pos[0] = arg0;
    g_cutscene_focus_pos[1] = arg1;
    g_cutscene_focus_pos[2] = arg2;
    g_cutscene_focus_set = 1;
}

/* was func_15022290 */
void cutscene_set_focus_point2(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    g_cutscene_focus2_yaw = arg3;
    g_cutscene_focus2_pos[0] = arg0;
    g_cutscene_focus2_pos[1] = arg1;
    g_cutscene_focus2_pos[2] = arg2;
}

/* was func_150222DC */
void cutscene_obj_list_clear(s32 arg0) {
    g_cutscene_obj_list_count[arg0] = 0;
}

/* was func_150222F0 */
void cutscene_record_list_clear(s32 arg0) {
    g_cutscene_rec_list_count[arg0] = 0;
}

/* P36: add id to the list `list` (g_cutscene_obj_lists[list], 25 bytes, count g_cutscene_obj_list_count[list]) unless present. Returns the
 * 1-based position when found, else the old count (the new entry's index). */
/* was func_15022304 */
s32 cutscene_obj_list_add(s32 id, s32 list) {
    u8 *cnt = (u8 *) &g_cutscene_obj_list_count + list;
    u8 *a = (u8 *) &g_cutscene_obj_lists + list * 25;
    s32 n = *cnt;
    s32 i = 0;

    if (n > 0) {
        do {
            i++;
            if (id == a[i - 1]) {
                return i;
            }
        } while (i < n);
    }
    a[n] = id;
    *cnt = n + 1;
    return i;
}
extern u16 *g_cutscene_actor_key_counts[]; /* was D_800C39E8 */
extern u8 *g_cutscene_actor_entries[]; /* was D_800C3A10 */
/* was func_15022388 */
void cutscene_actor_reset_obj(s32 arg0, s32 arg1) {
    struct127 *obj;
    u8 *e;
    if (g_cutscene_actor_key_counts[arg1][arg0] != 0) {
        e = g_cutscene_actor_entries[arg1] + arg0 * 8;
        if (*(u16 *)e == 2) {
            obj = obj_find_by_setup_id(e[2]);
            if (obj != NULL) {
                *((u8 *)obj + 0x6C) = 0;
                *((u8 *)obj + 0x6D) = 0;
                *((u8 *)obj + 0x6A) = 0;
                *((u8 *)obj + 0x6B) = 0;
                *(s16 *)((u8 *)obj + 0x282) = 0;
                *(s16 *)((u8 *)obj + 0x27A) = 0;
                *(s16 *)((u8 *)obj + 0x27C) = 0;
                *(s16 *)((u8 *)obj + 0x27E) = 0;
                *(s16 *)((u8 *)obj + 0x280) = 0;
                face_anim_start(obj, 0, 3, 0xFFFF, 0xA);
                *((u8 *)obj + 0x71) = 0;
            }
        }
    }
}

s32 cutscene_obj_list_add(s32, s32);
s32 setup_entry_spawn(u8 *, s32, s32, s32, s32);
extern u8 g_setup_entry_count; /* was D_800D2520 */

/* was func_15022440 */
s32 cutscene_actor_spawn_obj(s32 arg0, s32 arg1) {
    struct127 *sp3C;
    s32 sp38;
    s32 sp34;
    u8 **sp2C;
    s32 var_v0;
    u8 **temp_a2;
    u8 temp_v0;
    u8 *temp_v1;

    var_v0 = arg1;
    temp_a2 = &g_cutscene_actor_entries[var_v0];
    if (g_cutscene_actor_key_counts[var_v0][arg0] != 0) {
        temp_v1 = *temp_a2 + (arg0 * 8);
        if ((*(u16 *)((u8 *)temp_v1 + 0)) == 2) {
            temp_v0 = (*(u8 *)((u8 *)temp_v1 + 2));
            sp2C = temp_a2;
            sp34 = (s32) temp_v0;
            var_v0 = setup_entry_find_by_id(temp_v0);
            if (var_v0 != -1) {
                sp38 = var_v0;
                sp2C = temp_a2;
                var_v0 = obj_find_by_spawn(var_v0);
                if (var_v0 != 0) {
                    if ((*(u8 *)((u8 *)var_v0 + 5)) == 3) {
                        if (temp_a2 != g_cutscene_actor_entries) {
                            (*(u8 *)((u8 *)var_v0 + 5)) = 4U;
                        } else {
                            (*(u8 *)((u8 *)var_v0 + 5)) = 0U;
                        }
                    }
                    if (sp34 == 1) {
                        (*(s32 *)((u8 *)var_v0 + 0xF4)) = (s32) ((*(s32 *)((u8 *)var_v0 + 0xF4)) & ~0x2A);
                        return var_v0;
                    }
                    /* Duplicate return node #13. Try simplifying control flow for better match */
                    return var_v0;
                }
                if (sp38 < (s32) g_setup_entry_count) {
                    setup_entry_spawn((u8 *) g_setup_entries + sp38 * 0x30, sp38, 0, arg1, 0);
                    var_v0 = obj_find_by_spawn(sp38);
                    if (var_v0 != 0) {
                        sp3C = (struct127 *) var_v0;
                        obj_start_anim((struct127 *) var_v0, 0U, 0.0f, 0.0f, 0.0f, 0.0f, 1);
                        var_v0 = cutscene_obj_list_add(((u8 *) sp3C - (u8 *) g_objects) / 812, arg1);
                    }
                }
                /* Duplicate return node #13. Try simplifying control flow for better match */
                return var_v0;
            }
        }
    }
    return var_v0;
}
/* Actor pass of cutscene slot `slot`: for each of its g_cutscene_actor_count[slot] actors that has a camera and actor track
 * (g_cutscene_cam_key_counts / g_cutscene_actor_key_counts words != 0) and a record of kind 2 (g_cutscene_actor_entries[slot] + 8 i), finds the object
 * (obj_find_by_setup_id(record[2])) and gives it its actor frame (cutscene_actor_apply_track(obj, slot, i)). */
/* was func_150225D0 */
void cutscene_actor_pass(s32 slot) {
    struct127 *obj;
    u8 *rec;
    s32 i;

    for (i = 0; i < g_cutscene_actor_count[slot]; i++) {
        if (g_cutscene_cam_key_counts[slot][i] == 0 || g_cutscene_actor_key_counts[slot][i] == 0) {
            continue;
        }
        rec = g_cutscene_actor_entries[slot] + i * 8;
        if (*(u16 *)rec == 2) {
            obj = obj_find_by_setup_id(rec[2]);
            if (obj != NULL) {
                cutscene_actor_apply_track(obj, slot, i);
            }
        }
    }
}

extern u8 g_cutscene_rec_lists[]; /* was D_800C3970 */

/* Adds `id` to sequence slot `slot`'s id list (g_cutscene_rec_lists, 30 bytes per slot, count g_cutscene_rec_list_count[slot]) unless it
 * is already there. Returns i + 1 for an id found at index i, else the old count (the loop counter, as the
 * original). The list is not bounded. */
/* was func_150226E8 */
s32 cutscene_record_list_add(u8 id, s32 slot) {
    u8 *list = &g_cutscene_rec_lists[slot * 30];
    s32 count = g_cutscene_rec_list_count[slot];
    s32 i = 0;

    while (i < count) {
        i++;
        if (list[i - 1] == id) {
            return i;
        }
    }
    list[count] = id;
    g_cutscene_rec_list_count[slot] = count + 1;
    return i;
}

s32 cutscene_record_list_add(u8, s32);

/* was func_15022764 */
s32 cutscene_actor_claim_record(s32 arg0, s32 arg1) {
    u8 *sp1C;
    s32 var_v0;
    u8 *temp_v1;

    var_v0 = arg1 * 4;
    if (g_cutscene_actor_key_counts[arg1][arg0] != 0) {
        temp_v1 = g_cutscene_actor_entries[arg1] + (arg0 * 8);
        if ((*(u16 *)((u8 *)temp_v1 + 0)) == 3) {
            var_v0 = world_record_find((*(u8 *)((u8 *)temp_v1 + 2)));
            if ((var_v0 != 0) && ((*(u8 *)((u8 *)var_v0 + 0x6E)) == 1)) {
                sp1C = (u8 *) var_v0;
                var_v0 = cutscene_record_list_add((*(u8 *)((u8 *)var_v0 + 0x72)), arg1);
                (*(s8 *)((u8 *)sp1C + 0x6E)) = 0;
            }
        }
    }
    return var_v0;
}
s32 cutscene_actor_claim_record(s32, s32);

/* was func_150227FC */
void cutscene_claim_records(s32 arg0) {
    s32 var_s0;
    u8 *temp_s1;

    temp_s1 = &g_cutscene_actor_count[arg0];
    var_s0 = 0;
    if ((s32) *temp_s1 > 0) {
        do {
            cutscene_actor_claim_record(var_s0, arg0);
            var_s0 += 1;
        } while (var_s0 < (s32) *temp_s1);
    }
}

u8 *world_record_find(u8);
extern u8 g_cutscene_rec_lists[]; /* was D_800C3970 */
/* was func_15022864 */
void cutscene_restore_records(s32 arg0)
{
  s32 i;
  u8 *cnt;
  u8 *p;
  cnt = &g_cutscene_rec_list_count[arg0];
 do { i = 0; if ((*cnt) > 0) { p = g_cutscene_rec_lists + (arg0 * 0x1E); do { world_record_find(*p)[0x6E] = 1; i += 1; p += 1; } while (i < (*cnt)); } } while (0);
}

void cutscene_actor_reset_obj(s32, s32);
s32 cutscene_actor_spawn_obj(s32, s32);

/* was func_150228F0 */
void cutscene_spawn_actors(s32 arg0) {
    s32 var_s0;
    u8 *temp_s2;

    if ((&g_cutscene_slot_state)[arg0] == 1) {
        g_cutscene_in_progress = 0;
        temp_s2 = &g_cutscene_actor_count[arg0];
        var_s0 = 0;
        if ((s32) *temp_s2 > 0) {
            do {
                cutscene_actor_spawn_obj(var_s0, arg0);
                cutscene_actor_reset_obj(var_s0, arg0);
                var_s0 += 1;
            } while (var_s0 < (s32) *temp_s2);
        }
        g_cutscene_in_progress = 1;
    }
}

extern u8 g_cutscene_obj_lists[][0x19]; /* was D_800C3938 */

/* was func_1502298C */
void cutscene_release_listed_objs(s32 arg0)
{
  s32 i;
  u8 *new_var; // fakematch: permuter temp
  s32 n;
  u8 *cnt = &g_cutscene_obj_list_count[arg0];
  u8 *p;
  struct127 *e;
 i = 0; n = *cnt; if (n > 0) { p = g_cutscene_obj_lists[arg0]; do {
      e = &g_objects[*p];
      if (e->interaction_state)
      {
        new_var = &(*cnt);
        obj_remove(e, 0);
        n = *new_var;
      }
      i++;
      p++;
    }
    while (i < n);
  }
}

/* was func_15022A40 */
void cutscene_event_dispatch(s32 *arg0) {
    s32 v = arg0[0];

    if ((v == 27) || (v == 4)) {
        if (g_obj_interaction_state_fns[v] != NULL) {
            ((void (*)(s32 *)) g_obj_interaction_state_fns[v])(arg0);   /* P76: a0 still holds arg0 */
        }
    }
}

extern u8 g_obj_unique_id_by_slot1;   /* g_objects[0] + 0x12F: actor id of an object (0x32C-byte objects); was D_800CC2D0; was D_800CC3FF */
/* Does object `obj` take part in the loaded cutscene? Slot 1 for object kind 4 (byte +5), else slot 0; its id
 * is the actor id of its owner g_objects[obj[0x65]] (byte at +0x12F) when it has one, else its own byte +0x3B.
 * Returns 2 (owned) / 1 when an active actor of that slot has entry type 2 (object) with that id (entry byte
 * +2), else 0 (also for no object, a free slot obj[0] == 0, or no scene loaded in slot 0). */
/* was func_15022A8C */
s32 cutscene_obj_takes_part(s32 *obj) {
    u8 *ent;
    u8 owner;
    u8 id;
    s32 slot;
    s32 n;
    s32 i;

    if (obj == NULL || obj[0] == 0 || g_cutscene_actor_key_counts[0] == NULL) {
        return 0;
    }
    slot = (((u8 *)obj)[5] == 4) ? 1 : 0;
    owner = ((u8 *)obj)[0x65];
    if (owner != 0) {
        id = (&g_obj_unique_id_by_slot1)[owner * 0x32C];
    } else {
        id = ((u8 *)obj)[0x3B];
    }
    n = g_cutscene_actor_count[slot];
    for (i = 0; i < n; i++) {
        if (g_cutscene_actor_key_counts[slot][i] == 0) {
            continue;
        }
        ent = g_cutscene_actor_entries[slot] + i * 8;
        if (*(u16 *)ent == 2 && ent[2] == id) {
            return (owner != 0) ? 2 : 1;
        }
    }
    return 0;
}

/* was func_15022BB0 */
s32 cutscene_room_has_actor(s32 arg0, s32 arg1) {
    s32 var_v0;
    u16 *var_a2;
    u8 temp_v1;

    temp_v1 = g_cutscene_actor_count[arg1];
    var_v0 = 0;
    if ((s32) temp_v1 > 0) {
        var_a2 = g_cutscene_actor_key_counts[arg1];
loop_2:
        if ((*var_a2 != 0) && ((*(u8 *)((u8 *)((g_cutscene_actor_entries[arg1] + (var_v0 * 8))) + 2)) == g_world_objs[arg0].pad70[2])) {
            return 1;
        }
        var_v0 += 1;
        var_a2 = (u16 *)((u8 *)var_a2 + (2));
        if (var_v0 >= (s32) temp_v1) {
            /* Duplicate return node #6. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_2;
    }
    return 0;
}
void cutscene_set_focus_point(s16, s16, s16, f32);
f32 sinf(f32);
f32 cosf(f32);
/* Places the scene of cutscene slot `slot` in the level: the first actor whose entry (g_cutscene_actor_entries[slot] + i * 8)
 * is an anchor moves every actor's path keys (s16 x, y, z at D_eu_800C3C88[slot][j] + k * 8):
 *   type 6: by the offset from the anchor's first key to object obj_find_by_setup_id(b) (a == 0) or entity
 *     world_record_find(b) (a == 1); other a: nothing.
 *   type 7: rotated about the anchor's first key by g_cutscene_focus_yaw - its channel-7 key angle (stored in
 *     g_cutscene_scene_rot) and moved onto g_cutscene_focus_pos; the channel-7 keys of the other camera tracks turn by the same
 *     angle unless their sound record +0x20 is 7.
 * cutscene_set_focus_point gets the anchor (unless g_cutscene_focus_set). */
/* was func_15022C4C */
void cutscene_place_scene(s32 slot) {
    TrackKey *keys;
    u8 *ent;
    u8 *o;
    s16 *p;
    s16 *q;
    s32 i;
    s32 j;
    s32 k;
    s32 cnt;
    s32 keep;
    f32 ang;
    f32 rot;
    f32 r;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 px;
    f32 py;
    f32 pz;
    f32 c;
    f32 s;
    f32 ox;
    f32 oz;
    f32 nx;
    f32 nz;

    for (i = 0; i < g_cutscene_actor_count[slot]; i++) {
        if (g_cutscene_actor_key_counts[slot][i] == 0) {
            continue;
        }
        ent = g_cutscene_actor_entries[slot] + i * 8;
        if (*(u16 *)ent == 6) {
            if (g_cutscene_focus_set == 0) {
                p = (s16 *)D_eu_800C3C88[slot][i];
                cutscene_set_focus_point(p[0], p[1], p[2], 0.0f);
                ent = g_cutscene_actor_entries[slot] + i * 8;
            }
            if (ent[2] == 0) {
                o = (u8 *)obj_find_by_setup_id(ent[3]);
                if (o == NULL) {
                    return;
                }
                tx = *(f32 *)(o + 0x14);
                ty = *(f32 *)(o + 0x18);
                tz = *(f32 *)(o + 0x1C);
            } else if (ent[2] == 1) {
                o = world_record_find(ent[3]);
                if (o == NULL) {
                    return;
                }
                tx = *(s16 *)(o + 0x10);
                ty = *(s16 *)(o + 0x12);
                tz = *(s16 *)(o + 0x14);
            } else {
                return;
            }
            p = (s16 *)D_eu_800C3C88[slot][i];
            dx = tx - (f32)p[0];
            dy = ty - (f32)p[1];
            dz = tz - (f32)p[2];
            for (j = 0; j < g_cutscene_actor_count[slot]; j++) {
                for (k = 0; k < g_cutscene_actor_key_counts[slot][j]; k++) {
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[0] = (s32)((f32)q[0] + dx);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[1] = (s32)((f32)q[1] + dy);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[2] = (s32)((f32)q[2] + dz);
                }
            }
            return;
        }
        if (*(u16 *)ent == 7) {
            cnt = g_cutscene_cam_key_counts[slot][i];
            ang = 0.0f;
            keys = (TrackKey *)g_cutscene_cam_tracks[slot][i];
            for (k = 0; k < cnt; k++) {
                if (keys[k].channel == 7) {
                    ang = keys[k].value;
                    break;
                }
            }
            if (g_cutscene_focus_set == 0) {
                p = (s16 *)D_eu_800C3C88[slot][i];
                cutscene_set_focus_point(p[0], p[1], p[2], ang);
            }
            rot = g_cutscene_focus_yaw - ang;
            g_cutscene_scene_rot = rot;
            p = (s16 *)D_eu_800C3C88[slot][i];
            r = rot * 0.017453292f;
            px = p[0];
            py = p[1];
            pz = p[2];
            c = cosf(r);
            s = sinf(r);
            dy = (f32)g_cutscene_focus_pos[1] - py;
            for (j = 0; j < g_cutscene_actor_count[slot]; j++) {
                keep = FALSE;
                for (k = 0; k < g_cutscene_actor_key_counts[slot][j]; k++) {
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    ox = (f32)q[0] - px;
                    oz = (f32)q[2] - pz;
                    nx = ox * c + oz * s;
                    nz = -ox * s + oz * c;
                    q[0] = (s32)((f32)g_cutscene_focus_pos[0] + nx);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[1] = (s32)((f32)q[1] + dy);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[2] = (s32)((f32)g_cutscene_focus_pos[2] + nz);
                }
                if (g_cutscene_event_counts[slot][j] != 0 && *(s8 *)((u8 *)g_cutscene_event_tracks[slot][j] + 0x20) == 7) {
                    keep = TRUE;
                }
                if (!keep) {
                    for (k = 0; k < g_cutscene_cam_key_counts[slot][j]; k++) {
                        keys = (TrackKey *)g_cutscene_cam_tracks[slot][j];
                        if (keys[k].channel == 7) {
                            keys[k].value += rot;
                        }
                    }
                }
            }
            return;
        }
    }
}

/* Camera actor of cutscene slot `slot`: of the slot's sound / event records g_cutscene_event_tracks[slot][i] (i < the actor
 * count g_cutscene_actor_count[slot]) asks scene_event_find_next (type 3) for the nearest event; the record it reports with the
 * smallest distance gives the actor (s16 at +2). Without one the first actor with entry type 1 (u16 at
 * g_cutscene_actor_entries[slot] + i * 8), else 0. `pos` (the script position) is not read. */
/* was func_1502330C */
s32 cutscene_find_camera_actor(s32 slot, s32 pos) {
    u8 *found;
    s32 best;
    s32 dist;
    s32 actor;
    s32 i;

    best = 99999;
    actor = -1;
    for (i = 0; i < g_cutscene_actor_count[slot]; i++) {
        if (g_cutscene_event_tracks[slot][i] != 0) {
            found = NULL;
            dist = scene_event_find_next(g_cutscene_event_tracks[slot][i] + 0x18, 3, i, &found, 0, 0, 0, 0, 0, 0, slot);
            if (found != NULL && dist < best) {
                best = dist;
                actor = *(s16 *)(found + 2);
            }
        }
    }
    if (actor == -1) {
        actor = 0;
        for (i = 0; i < g_cutscene_actor_count[slot]; i++) {
            if (*(u16 *)(g_cutscene_actor_entries[slot] + i * 8) == 1) {
                actor = i;
                break;
            }
        }
    }
    return actor;
}
/* was func_15023464 */
void subtitle_slots_clear(void) {
    bzero(g_subtitle_slots, 0xA8);
}

/* was func_1502348C */
void subtitle_slots_close_all(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((s16)g_subtitle_slots[i].unk0 != 0) {
            text_box_close_now(*(s32 *)((u8 *)&g_subtitle_slots[i] + 0x34));
            *(s32 *)((u8 *)&g_subtitle_slots[i] + 0x34) = 0;
            g_subtitle_slots[i].unk0 = 0;
        }
    }
}

/* was func_150234E8 */
void subtitle_slot_close(s16 *arg0, s32 arg1) {
    if (arg1 != 0) {
        text_box_close_now(*(s32 *)((u8 *)arg0 + 0x34));
        *(s32 *)((u8 *)arg0 + 0x34) = 0;
    } else if (*(u8 *)((u8 *)arg0 + 0xC) != 0) {
        text_box_request_finish(*(s32 *)((u8 *)arg0 + 0x34));
    } else {
        *(s32 *)((u8 *)arg0 + 0x34) = 0;
    }
    *(s16 *)((u8 *)arg0) = 0;
}

extern s32 g_subtitle_slots_end; /* was D_800C4168 */

/* was func_1502354C */
s16 *subtitle_slot_get(s32 arg0, s32 arg1) {
    s16 *sp20;                                      /* compiler-managed */
    struct163 *sp1C;
    s16 *sp18;                                      /* compiler-managed */
    s16 temp_v0;
    s32 var_a3;
    struct163 *var_a2;
    struct163 *var_t0;
    struct163 *var_t1;

    var_a3 = arg0 + 1;
    var_t1 = NULL;
    var_t0 = NULL;
    var_a2 = g_subtitle_slots;
loop_1:
    temp_v0 = (s16) var_a2->unk0;
    if (var_a3 == temp_v0) {
        if ((arg1 != 0) && (var_a2->unkC != 0)) {
            sp18 = (s16 *) var_a2;
            arg0 = var_a3;
            sp1C = g_subtitle_slots;
            sp20 = NULL;
            subtitle_slot_close((s16 *) g_subtitle_slots, 1);
            var_a3 = arg0;
            var_t0 = sp1C;
            var_t1 = NULL;
        } else {
            var_t1 = var_a2;
        }
    } else if (temp_v0 == 0) {
        var_t0 = var_a2;
        if ((arg1 != 0) && (var_a2->unkC != 0)) {
            sp18 = var_a2;
            arg0 = var_a3;
            sp1C = var_t0;
            sp20 = NULL;
            subtitle_slot_close((s16 *) var_a2, 1);
            var_a3 = arg0;
            var_t1 = NULL;
        }
    } else {
        var_a2 = (struct163 *)((u8 *)var_a2 + (0x38));
        if ((s32)var_a2 != (s32)&g_subtitle_slots_end) {
            goto loop_1;
        }
    }
    if ((s32)var_a2 == (s32)&g_subtitle_slots_end) {
        sp1C = g_subtitle_slots;
        arg0 = var_a3;
        sp20 = var_t1;
        subtitle_slot_close((s16 *) g_subtitle_slots, 1);
        var_a3 = arg0;
        var_t0 = sp1C;
    }
    if (var_t1 != NULL) {
        return (s16 *) var_t1;
    }
    if (var_t0 != NULL) {
        var_t0->unk0 = (u16) var_a3;
    }
    return (s16 *) var_t0;
}
/* P92: declarations for cutscene_teardown_player */
void hud_bubbles_reset(void);
void player_idle_animation(void);
extern f32 g_cutscene_k_6dcc;   /* no water level (-10000); was D_80096DCC */
/* Scene teardown, player (cutscene_end): clears flag 0x200 of object 0 (+0x25C) and, unless g_cutscene_keep_player, resets
 * the player object obj_find_by_setup_id(1) (g_cur_obj_index = its index): speeds / timers cleared; in water (water level
 * +0x118 set, g_cutscene_k_6dcc = none, and above the feet +0x18): swimming (+0xAD = 1, hud_bubbles_reset when the water
 * is deeper than 50 above the floor +0x1A6 or the model flag +0x31C->+0x20 bit 0 is set), else standing on the
 * floor +0x180 (+0x20 = -4, +0x24 = 5). Then the height above the floor (+0x28), cleared input / state bytes,
 * g_cur_obj = the player and the idle animation (player_idle_animation). `slot` is not read. */
/* was func_15023684 */
void cutscene_teardown_player(s32 slot) {
    u8 *p;
    f32 water;

    *(u32 *)((u8 *)g_objects + 0x25C) &= ~0x200;
    if (g_cutscene_keep_player != 0) {
        return;
    }
    p = (u8 *)obj_find_by_setup_id(1);
    if (p == NULL) {
        return;
    }
    g_cur_obj_index = (p - (u8 *)g_objects) / 0x32C;
    *(f32 *)(p + 0x3C) = 0.0f;
    if (*(f32 **)(p + 0x31C) != NULL) {
        **(f32 **)(p + 0x31C) = 0.0f;
    }
    *(f32 *)(p + 0x54) = 0.0f;
    *(s16 *)(p + 0xCC) = 0;
    p[0xD0] = 0;
    water = *(f32 *)(p + 0x118);
    if (g_cutscene_k_6dcc != water && *(f32 *)(p + 0x18) < water) {
        p[0xAD] = 1;
        *(f32 *)(p + 0x20) = 0.0f;
        *(f32 *)(p + 0x24) = 0.0f;
        if (water - 50.0f < (f32)*(s16 *)(p + 0x1A6) || (*(u8 **)(p + 0x31C))[0x20] & 1) {
            *(s16 *)(p + 0xB2) = 0;
            hud_bubbles_reset();
        }
    } else {
        p[0xAD] = 0;
        *(s16 *)(p + 0xB2) = 0;
        *(f32 *)(p + 0x20) = -4.0f;
        *(f32 *)(p + 0x18) = *(f32 *)(p + 0x180);
        *(f32 *)(p + 0x1CC) = *(f32 *)(p + 0x180);
        *(f32 *)(p + 0x24) = 5.0f;
    }
    p[0x81] = 0;
    p[0x83] = 0;
    p[0x89] = 0;
    p[0x8A] = 0;
    p[0x104] = 0;
    *(f32 *)(p + 0x28) = *(f32 *)(p + 0x18) - *(f32 *)(p + 0x180);
    g_cur_obj = (struct127 *)p;
    player_idle_animation();
    (*(u8 **)(p + 0x31C))[0x23] = 0;
    p[0x276] = 0;
    *(s16 *)(p + 0x282) = 0;
    *(s16 *)(p + 0x278) = 0;
    p[0x284] = p[0x285] = p[0x286] = p[0x287] = 0;
    (*(u8 **)(p + 0x31C))[0x31] = 0;
}
void cutscene_actor_apply_track(struct127 *, s32, s32);
extern s32 D_eu_800C3A60;
extern s32 g_cutscene_frame; /* was D_800C39D0 */
s32 cutscene_obj_takes_part(s32 *);
void objects_run_state_handlers(void);
void objects_animate_textures(void);
void face_anim_timer_step(s32 *);
void player_idle_state_update(s32 *);
extern u8 g_cutscene_run_all_objs; /* was D_800C3A78 */

/* was func_1502378C */
void cutscene_update_objects(void) {
    struct127 *var_s0;
    u8 var_s1;

    var_s0 = g_objects;
    var_s1 = 0;
    if (g_cutscene_run_all_objs != 0) {
        objects_run_state_handlers();
        return;
    }
    do {
        if (var_s0->interaction_state != 0) {
            g_cur_obj_index = var_s1;
            cutscene_event_dispatch(&var_s0->interaction_state);
            face_anim_timer_step(&var_s0->interaction_state);
            if (cutscene_obj_takes_part(&var_s0->interaction_state) != 0) {
                cutscene_actor_apply_track(&var_s0->interaction_state, 0, -1);
                obj_model_reset(var_s0);
                player_idle_state_update(&var_s0->interaction_state);
                var_s0->unk2FF = 1;
            }
        }
        var_s1 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    } while (var_s1 != 0x19);
    objects_animate_textures();
}