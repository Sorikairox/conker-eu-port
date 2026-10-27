#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 g_cont_read_done; /* was D_8002AE18 */
extern u64 g_os_clock_rate; /* was D_8002C060 */
extern OSMesgQueue g_sched_event_queue; /* was D_8003B578 */
extern OSTimer g_cont_read_timer; /* was D_800BEB00 */
/* was func_1501BB20 */
void cont_arm_read_timer(void) {
    if (g_cont_read_done != 0) {
        osSetTimer(&g_cont_read_timer, (25ULL * g_os_clock_rate) / 1000000ULL, 0, &g_sched_event_queue, (void *)6);
        g_cont_read_done = 0;
    }
}

extern u8 g_cont_read_done; /* was D_8002AE18 */
extern OSMesg g_si_recv_mesg; /* was D_800BEDB0 */
extern u8 g_cont_connected_mask; /* was D_800BEB60 */
extern u8 g_game_mode_prev; /* was D_800E0FC5 */
extern u16 g_cont_prev_buttons[4]; /* was D_800BEB20 */
extern u16 g_cont_prev_buttons_b[4]; /* was D_800BEB28 */
extern u16 g_pad_pressed[4]; /* was D_800BEB30 */
extern u16 g_cont_last_buttons[4]; /* was D_800BEB38 */
extern OSContPad g_cont_pads[4]; /* was D_800BED38 */
extern u16 g_cont_pressed[4]; /* was D_800BED50 */
void demo_input_play_next(void);
void save_process_request(void);

/* Stick dead zone: |v| < 8 -> 0, otherwise move v 7 towards 0. */
#define DEADZONE(v) ((((v) < 0) ? -(v) : (v)) >= 8 ? (v) - (((v) < 0) ? -1 : 1) * 7 : 0)

/* Per-frame controller read: fetch the 4 pads, map them to players, compute the edge masks
 * and apply the stick dead zone. Returns the player input block. */
/* was func_1501BBB8 */
struct14 *cont_read_frame(void) {
    OSContPad pads[4];
    OSContPad *player = (OSContPad *)g_pad_states;
    s32 i;
    s32 nplayers;
    s32 replay;
    u8 idx;

    for (i = 0; i < 4; i++) {
        g_cont_last_buttons[i] = player[i].button;
    }
    osRecvMesg(&g_si_mesg_queue, &g_si_recv_mesg, OS_MESG_BLOCK);
    osContGetReadData(pads);
    save_process_request();
    g_cont_read_done = 1;
    g_cont_connected_mask = 0;
    for (i = 0; i < 4; i++) {
        if (pads[i].errno != 0) {
            pads[i].button = 0;
            pads[i].stick_x = 0;
            pads[i].stick_y = 0;
        } else {
            g_cont_connected_mask |= 1 << i;
        }
    }

    nplayers = 4;
    if (g_level_id != 0x1D) {
        nplayers = g_human_player_count;
    }
    for (i = 0; i < 4; i++) {
        idx = g_player_pad_map[i];
        if (idx < 4 && i < nplayers) {
            player[i].stick_x = pads[idx].stick_x;
            player[i].stick_y = pads[idx].stick_y;
            player[i].button = pads[idx].button | g_cont_forced_buttons[idx];
            g_cont_forced_buttons[idx] = 0;
        } else {
            player[i].button = 0;
            player[i].stick_x = 0;
            player[i].stick_y = 0;
        }
    }

    for (i = 0; i < 4; i++) {
        g_cont_pressed[i] = ~g_cont_prev_buttons_b[i] & player[i].button;
        g_cont_pads[i].button = player[i].button;
        g_cont_prev_buttons_b[i] = player[i].button;
        g_cont_pads[i].stick_x = DEADZONE(player[i].stick_x);
        g_cont_pads[i].stick_y = DEADZONE(player[i].stick_y);
    }

    if (g_game_mode == 2 || g_game_mode_prev == 2) {
        replay = 1;
        demo_input_play_next();
    } else {
        replay = 0;
    }

    for (i = 0; i < 4; i++) {
        g_pad_pressed[i] = ~g_cont_prev_buttons[i] & player[i].button;
        g_cont_prev_buttons[i] = player[i].button;
        if (replay == 0) {
            player[i].stick_x = DEADZONE(player[i].stick_x);
            player[i].stick_y = DEADZONE(player[i].stick_y);
        }
    }
    return &g_cont_pad_ptrs;
}
#undef DEADZONE
extern f32 g_rumble_k_6d10; /* was D_80096D10 */
void rumble_start(u8, f32, f32);
/* was func_1501BFF0 */
void rumble_start_strength(u8 player /* was arg0 */, u8 strength /* was arg1 */)
{
  f32 step; /* was t */
  f32 on_time; /* was a; frames on per period */
  f32 off_time; /* was b */
  if (strength >= 9) {
    strength = 8;
  }
  if (strength == 8) {
    on_time = 20.0f;
    off_time = 0.0f;
  } else if (strength == 0) {
    on_time = 0.0f;
    off_time = 99.0f;
  } else {
    step = ((f32)(u32)strength - 1) * g_rumble_k_6d10 * 5.0f;
    on_time = step + 2.0f;
    off_time = 7.0f - step;
  }
  rumble_start(player, on_time, off_time);
}

extern u8 g_rumble_pak_present[]; /* was D_800BED64 */
extern f32 g_rumble_phase[]; /* was D_800BED70 */
extern f32 g_rumble_on_time[]; /* was D_800BED80 */
extern f32 g_rumble_off_time[]; /* was D_800BED90 */
extern f32 g_rumble_period[]; /* was D_800BEDA0 */
/* was func_1501C0D0 */
void rumble_start(u8 player /* was arg0 */, f32 on_time /* was arg1 */, f32 off_time /* was arg2 */) {
    s32 idx;
    idx = g_player_pad_map[player];
    if (idx < 4 && g_rumble_pak_present[idx] != 0) {
        g_rumble_active[idx] = 1;
        g_rumble_phase[idx] = 0.0f;
        g_rumble_on_time[idx] = on_time;
        g_rumble_off_time[idx] = off_time;
        g_rumble_period[idx] = on_time + off_time;
    }
}

/* was func_1501C15C */
void rumble_stop(u8 player /* was arg0 */) {
    s32 pad = g_player_pad_map[player]; /* was temp_v0 */

    if (pad < 4) {
        g_rumble_active[pad] = 0;
    }
}

extern s32 g_rumble_pfs; /* was D_800BEB80 */
extern s32 g_rumble_prev_active; /* was D_800BED60 */
extern s32 g_rumble_motor_on; /* was D_800BED68 */
extern u8 g_unpause_settle_frames; /* was D_800BEEE2 */
extern u8 g_rumble_stop_request; /* was D_800BEEE3 */
extern u8 g_rumble_clear_request; /* was D_eu_800E0E30 */

/* was func_1501C1B0 */
void rumble_update(void) {
    f32 *phase; /* was temp_v0_2 */
    f32 period; /* was temp_f2 */
    s32 ch; /* was var_s1 */
    u8 *motor_on; /* was temp_s2 */
    u8 *active; /* was temp_s4 */
    u8 *prev_active; /* was temp_s7 */
    u8 *pak_present; /* was var_s3 */
    u8 state; /* was temp_v0 */
    u8 want_on; /* was var_s0 */
    u8 *pfs; /* was temp_s0 */
    u8 *pfs_stop; /* was temp_s0_2 */
    u8 *pfs_idle; /* was temp_s0_3 */

#ifdef PORT
    {   /* P335: the page option "Rumble" (PORT_OPT_RUMBLE) decides whether pc_pif.c answers as a Rumble Pak. The game
         * only probes at a level / area start (g_rumble_probe_request from level_start_game), so a toggle used to wait
         * for the next load. Now a change of the option requests the same probe this frame: on -> os_motor_init finds
         * the pak (g_rumble_pak_present 1, pattern state reset, motor stopped); off -> it finds none (present 0, the
         * channel is skipped and rumble_request / rumble_start ignore it). */
        static s32 rumble_option_seen = -1; /* -1 until the first frame */
        s32 rumble_option_on = port_option(PORT_OPT_RUMBLE) != 0;

        if (rumble_option_seen >= 0 && rumble_option_on != rumble_option_seen) {
            g_rumble_probe_request = 1;
        }
        rumble_option_seen = rumble_option_on;
    }
#endif
    pak_present = g_rumble_pak_present;
    ch = 0;
    do {
        if (g_rumble_probe_request != 0) {
            pfs = ((u8 *)&g_rumble_pfs + (ch * 0x68));
            if (os_motor_init(&g_si_mesg_queue, pfs, ch) == 0) {
                if (*pak_present == 0) {
                    *pak_present = 1;
                    g_rumble_active[ch] = 0;
                    ((u8 *)&g_rumble_prev_active)[ch] = 0;
                    ((u8 *)&g_rumble_motor_on)[ch] = 0;
                    g_rumble_phase[ch] = 0.0f;
                    g_rumble_on_time[ch] = 1.0f;
                    g_rumble_off_time[ch] = 1.0f;
                    g_rumble_period[ch] = 2.0f;
                    os_motor_stop(pfs);
                }
            } else {
                *pak_present = 0;
            }
        }
        active = &g_rumble_active[ch];
        if (*pak_present != 0) {
            prev_active = ((u8 *)&g_rumble_prev_active + ch);
            if ((g_rumble_stop_request != 0) || (g_rumble_clear_request != 0)) {
                pfs_stop = ((u8 *)&g_rumble_pfs + (ch * 0x68));
                os_motor_init(&g_si_mesg_queue, pfs_stop, ch);
                os_motor_stop(pfs_stop);
                ((u8 *)&g_rumble_motor_on)[ch] = 0;
                *active = 0;
            }
            if ((g_pause_open == 0) && (g_game_paused == 0) && (g_unpause_settle_frames == 0) && (g_rumble_stop_request == 0) && (g_rumble_clear_request == 0)) {
                state = *active;
                switch (state) {                  /* irregular */
                case 0:
                    if (*prev_active == 1) {
                        pfs_idle = ((u8 *)&g_rumble_pfs + (ch * 0x68));
                        os_motor_init(&g_si_mesg_queue, pfs_idle, ch);
                        os_motor_stop(pfs_idle);
                        ((u8 *)&g_rumble_motor_on)[ch] = 0;
                    }
                    break;
                case 1:
                    phase = &g_rumble_phase[ch];
                    *phase += g_frame_step_f;
                    period = g_rumble_period[ch];
                    motor_on = ((u8 *)&g_rumble_motor_on + ch);
                    want_on = 1;
                    if (period < *phase) {
                        do {
                            *phase -= period;
                        } while (period < *phase);
                    }
                    if (g_rumble_on_time[ch] <= *phase) {
                        want_on = 0;
                    }
                    if (want_on != 0) {
                        if (*motor_on == 0) {
                            os_motor_start(((u8 *)&g_rumble_pfs + (ch * 0x68)));
                        }
                    } else if (*motor_on == 1) {
    s32 pad;
                        os_motor_stop(((u8 *)&g_rumble_pfs + (ch * 0x68)));
                    }
                    *motor_on = want_on;
                    break;
                }
            }
            *prev_active = *active;
        }
        ch += 1;
        pak_present += 1;
    } while (ch != 4);
    g_rumble_probe_request = 0;
    g_rumble_stop_request = 0;
    g_rumble_clear_request = 0;
}
/* was func_1501C51C */
void rumble_stop_all(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        rumble_stop(i);
    }
}

void heap_free(s32);
void save_slot_load(s8);
void save_slot_write(s8);
void save_slot_erase(s8);
void save_config_reset(void);
void save_config_load(void);
void save_config_write(void);
void save_options_load(void);
void save_options_write(void);
s32 eeprom_async_write_step(s32);
s32 game_eeprom_probe(OSMesgQueue *);
extern u8 g_save_eeprom_state; /* was D_800843F4 */
extern s32 g_save_field_widths; /* was D_800BE810 */

/* was func_1501C55C */
void save_process_request(void) {
    s8 mode;
    u8 state;

    eeprom_async_write_step(0);
    mode = (s8)g_save_request_kind;
    if (mode == 0) {
        return;
    }
    state = g_save_eeprom_state;
    if (state != 2) {
        g_save_eeprom_state = game_eeprom_probe(&g_si_mesg_queue);
        state = g_save_eeprom_state;
        mode = (s8)g_save_request_kind;
    }
    if (state != 2) {
        if (mode == 1) {
            save_game_defaults();
        } else if (mode == 4) {
            save_config_reset();
        }
        g_save_request_kind = 0;
        return;
    }
    switch (mode) {
        case 1: save_slot_load((s8)g_save_request_slot); break;
        case 2: save_slot_write((s8)g_save_request_slot); break;
        case 3: save_slot_erase((s8)g_save_request_slot); break;
        case 4: save_config_load(); break;
        case 5: save_config_write(); break;
        case 6: save_options_load(); break;
        case 7: save_options_write(); break;
    }
    g_save_request_kind = 0;
    if (g_save_field_widths != 0) {
        heap_free(g_save_field_widths - 8);
        g_save_field_widths = 0;
    }
}