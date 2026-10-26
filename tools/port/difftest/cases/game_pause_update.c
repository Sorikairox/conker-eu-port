#ifdef NON_MATCHING
typedef struct MenuPad {
    u16 button;
    s8 stickX;
    s8 stickY;
    u8 errno_;
    u8 pad5;
} MenuPad;
extern MenuPad g_cont_pads[4];   /* controller state, 6 bytes each; was D_800BED38 */
extern u16 g_cont_pressed;          /* new button presses per controller (u16 each); was D_800BED50 */
extern u8 g_menu_cursor;           /* pause menu cursor (read signed); was D_800901CC */
extern s8 g_settings_time_limit; /* was D_800E1013 */
extern s32 g_mp_time_left;          /* time limit (frames); was D_80090118 */
extern s32 *g_menu_fade_callback;         /* callback run when the menu fade ends; was D_800E0EB8 */
extern s8 g_pause_drop_queue; /* was D_8009013C */
extern u8 g_pause_simple; /* was D_80090158 */
extern s8 g_pause_input_delay;           /* pause input delay; was D_80090298 */
extern s8 g_pause_unpause_timer;           /* unpause countdown; was D_8009029C */
extern s8 g_pause_last_stick_x;           /* last stick x; was D_800902A0 */
extern s8 g_pause_last_stick_y;           /* last stick y; was D_800E0EB5 */
extern s8 g_pause_quit_yes;           /* quit confirmation: 1 = yes; was D_80090138 */
extern u8 g_menu_prompt_alpha_lo; /* was D_8009016D */
extern u8 g_rumble_stop_request; /* was D_800BEEE3 */
extern u8 g_pause_pad;           /* controller that paused; was D_800E0EC8 */
extern s8 g_play_time_frames;           /* frame counter for the seconds of play time; was D_800E0EC9 */
extern s32 g_event_cur_id; /* was D_800D3268 */
extern OSIoMesg g_pause_pi_io_mesg; /* was D_80038C40 */
extern u8 g_str_pause_time_fmt[];         /* "%d:%02d"; was D_800ABBB8 */
extern u8 g_str_pause_simple_item[];         /* "#": text id (the next argument), likewise the following; was D_800ABBC0 */
extern u8 g_str_pause_title[]; /* was D_800ABBC4 */
extern u8 g_str_pause_continue[]; /* was D_800ABBC8 */
extern u8 g_str_pause_restart_ask[]; /* was D_800ABBCC */
extern u8 g_str_pause_quit_ask[]; /* was D_800ABBD0 */
extern u8 g_str_pause_restart[]; /* was D_800ABBD4 */
extern u8 g_str_pause_quit[]; /* was D_800ABBD8 */
extern u8 g_str_pause_yes[]; /* was D_800ABBDC */
extern u8 g_str_pause_no[]; /* was D_800ABBE0 */
s32 screen_fade_all_active();
void text_printf(s32, ...);   /* varargs, as its definition (game_70200) */
void text_printf_at(s32, s32, u8, s32, ...);
void text_set_color(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
void menu_game_start(void);
void os_writeback_dcache(void *, s32); /* osWritebackDCache (hand-written cache loop) */

// game_pause_update: P127: menu handler of mode 0 (story game, g_game_mode_fns[0]): counts the play time (g_save_play_time
// seconds), shows the time limit (multiplayer, settings byte 3 >= 3), and runs the pause menu: START (0x1000) on a
// controller that is not disabled (g_player_view_hidden_mask) opens it (g_pause_open) unless blocked (screen_fade_all_active, scene states);
// the stick moves the cursor g_menu_cursor over the 2 (story) / 3 (multiplayer) items with sfx 0x62D; past the last item
// is the quit confirmation (g_pause_quit_yes no / yes). A on "yes" quits to the menu (g_menu_fade_callback = pause_quit_to_menu, in
// multiplayer menu_game_start to restart when the cursor was on "restart"); A on "no" goes back after Rare's cartridge
// check (2 words at ROM 0xF80; a mismatch DMAs 0x100 bytes to a random 0x803xxxxx address); START / B closes it.
void game_pause_update(void) {
    u8 dmaBuf[0x20];
    u8 *p;
    s32 sfx;
    u8 simple;
    s32 blocked;
    s32 nPads;
    s32 i;
    s32 yOff;
    s32 count;
    s32 y;
    s32 secs;
    s32 sel;
    u8 pad;
    s8 stickX;
    s8 stickY;

    g_screen_fade_alpha = 0;
    sfx = 0;
    blocked = 0;
    simple = g_pause_simple;
    if (g_level_id == 0x22) {
        simple = 1;
    }
    if (g_cutscene_slot_state != 1 || g_level_id != 0x18 || g_cutscene_scene != 1) {
        if (screen_fade_all_active() != 0) {
            blocked = 1;
        }
    }
    if (g_cutscene_slot_state == 1 && g_cutscene_no_pause != 0) {
        blocked = 1;
    }
    if (g_pause_input_delay > 0) {
        g_pause_input_delay--;
    }

    /* START opens the pause menu */
    if (g_game_paused == 0 && g_pause_open == 0 && !blocked && g_pause_input_delay == 0) {
        nPads = g_last_player_index;
        for (i = 0; i <= nPads && g_pause_open == 0; i++) {
            if (((&g_cont_pressed)[i] & 0x1000) && !(g_player_view_hidden_mask & (1 << i))) {
                g_pause_open = 1;
                g_rumble_stop_request = 1;
                g_pause_pad = i;
                g_menu_cursor = 0;
                g_pause_last_stick_x = g_cont_pads[i].stickY;
                g_pause_input_delay = 10;
            }
        }
    }

    /* play time */
    if (g_game_paused == 0 && g_event_cur_id != 0xC7) {
        g_play_time_frames += g_frame_ticks;
        if (g_play_time_frames >= 50) {
            g_play_time_frames -= 50;
            g_save_play_time++;
        }
    }

    /* time limit */
    if (g_mp_mode_active != 0 && g_pause_open == 0 && g_settings_time_limit >= 3) {
        y = 198;
        if (g_last_player_index > 0) {
            y = 100;
        }
        if (g_mp_time_left > 0) {
            g_mp_time_left -= g_frame_ticks_raw;
        } else {
            g_mp_time_left = 0;
        }
        secs = g_mp_time_left / 50;
        text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
        text_printf_at(0x87, y, 0x80, (s32) g_str_pause_time_fmt, secs / 60, secs % 60);
    }

    if (g_pause_unpause_timer > 0) {
        g_pause_unpause_timer--;
        if (g_pause_unpause_timer < 2) {
            g_pause_open = 0;
        }
        return;
    }
    if (g_game_paused == 0) {
        return;
    }

    /* pause menu */
    if (g_mp_mode_active != 0) {
        yOff = -0x24;
        count = 3;
    } else {
        yOff = 5;
        count = 2;
    }
    pad = g_pause_pad;
    g_menu_pressed = (&g_cont_pressed)[pad];
    if (g_pause_input_delay != 0) {
        g_menu_pressed = 0;
    }
    stickX = g_cont_pads[pad].stickX;
    stickY = g_cont_pads[pad].stickY;
    if ((s8) g_menu_cursor < count) {
        if ((g_pause_last_stick_x < 31 && stickX >= 31) || (g_pause_last_stick_x >= -30 && stickX < -30)) {
            if ((s8) g_menu_cursor == 2) {
                g_menu_cursor = 0;
            } else {
                g_menu_cursor = 1 - (s8) g_menu_cursor;
            }
            sfx = 0x62D;
        }
        if ((s8) g_menu_cursor != 0 && count == 3
            && ((g_pause_last_stick_y >= -30 && stickY < -30) || (g_pause_last_stick_y < 31 && stickY >= 31))) {
            sfx = 0x62D;
            if ((s8) g_menu_cursor == 2) {
                g_menu_cursor = 1;
            } else {
                g_menu_cursor = 2;
            }
        }
    } else if ((g_pause_last_stick_x >= -30 && stickX < -30) || (g_pause_last_stick_x < 31 && stickX >= 31)) {
        g_pause_quit_yes = 1 - g_pause_quit_yes;
        sfx = 0x62D;
    }
    g_pause_last_stick_x = stickX;
    g_pause_last_stick_y = stickY;
    text_set_color(0xFF, 0xFF, 0xFF, g_menu_prompt_alpha_lo);
    y = yOff + 0x73;
    if (simple) {
        g_menu_cursor = 0;
        text_printf_at(0x94, y, 1, (s32) g_str_pause_simple_item, 0xD);
    } else {
        text_printf_at(0x94, y, 1, (s32) g_str_pause_title, 0x1A);
        if ((s8) g_menu_cursor < count) {
            text_printf_at(0xD5, y, 1, (s32) g_str_pause_continue, ((s8) g_menu_cursor == 0) + 0xC);
        }
        text_set_pos(0x94, yOff + 0x55);
        if (count == (s8) g_menu_cursor) {
            text_printf((s32) g_str_pause_restart_ask, 0x32);
        } else if (count < (s8) g_menu_cursor) {
            text_printf((s32) g_str_pause_quit_ask, 0x33);
        }
    }
    text_set_pos(0x53, y);

    if ((s8) g_menu_cursor < count) {
        if (!simple) {
            sel = 1;
            if (count == 3) {
                text_set_pos(0x53, yOff + 0x63);
                text_printf((s32) g_str_pause_restart, ((s8) g_menu_cursor == 1) + 0x21);
                sel = 2;
                text_set_pos(0x53, yOff + 0x82);
            }
            text_printf((s32) g_str_pause_quit, (sel == (s8) g_menu_cursor) + 0xE);
        }
        if (g_menu_pressed & 0x1000) {
            g_pause_unpause_timer = 5;
            g_pause_input_delay = 10;
        } else if ((s8) g_menu_cursor == 0 || (g_menu_pressed & 0x4000)) {
            if (g_menu_pressed & 0xC000) {
                g_pause_unpause_timer = 5;
                g_pause_input_delay = 10;
            }
        } else if (g_menu_pressed & 0x8000) {
            /* A on the last item: to the quit confirmation */
            g_pause_quit_yes = 0;
            g_menu_cursor = (s8) g_menu_cursor + count - 1;
            if (count == 2) {
                g_menu_cursor = (s8) g_menu_cursor + 1;
            }
            sfx = 0x500;
        }
    } else {
        text_printf_at(0x6C, y, 1, (s32) g_str_pause_yes, g_pause_quit_yes + 0x1F);
        text_printf_at(0xBC, y, 1, (s32) g_str_pause_no, 0x1E - g_pause_quit_yes);
        if (g_menu_pressed & 0x8000) {
            if (g_pause_quit_yes != 0) {
                g_game_mode = 7;
                g_menu_fade_callback = (s32 *) pause_quit_to_menu;
                g_menu_fade_speed = 8;
                if (g_mp_mode_active != 0) {
                    g_menu_state[0x3F] = 4; /* MenuState mainPage */
                    if (count == (s8) g_menu_cursor) {
                        g_pause_drop_queue = 1;
                        g_menu_fade_callback = (s32 *) menu_game_start;
                    }
                } else if (g_save_cur_slot >= 0) {
                    save_request_slot_write(g_save_cur_slot);
                }
                g_menu_cursor = 0;
                g_player_start_state[0] = 0;
            } else {
                p = dmaBuf;
                if ((u32) p & 0xF) {
                    do {
                        p += 4;
                    } while ((u32) p & 0xF);
                }
                i = pause_bit_invert(-0xF81);
                os_writeback_dcache(p, 0x10);
                osPiStartDma(&g_pause_pi_io_mesg, 0, 0, i, p, 0x10, &gMessageQueue[0]);
                osRecvMesg(&gMessageQueue[0], NULL, 1);
                osInvalDCache(p, 0x10);
                ((u32 *) p)[0] -= 0x3E0EF0F0;
                ((u32 *) p)[1] -= 0x3E0EF0F0;
                if (((u32 *) p)[0] != 0x3050A14A || ((u32 *) p)[1] != 0xBCFCF506) {
                    i = random_int();
                    osPiStartDma(&g_pause_pi_io_mesg, 0, 0, i & 0xFFFF, (void *) ((random_int() & 0xFFFFE) + 0x80300000), 0x100,
                                 &gMessageQueue[0]);
                    osRecvMesg(&gMessageQueue[0], NULL, 1);
                }
                g_menu_cursor = (s8) g_menu_cursor - 2;
            }
            sfx = 0x500;
        } else if (g_menu_pressed & 0x4000) {
            g_menu_cursor = (s8) g_menu_cursor - 2;
        }
    }
    if (sfx != 0) {
        sound_play_2d(sfx, 0x5DC0, 0x40, 0, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/game_pause_update.s")
#endif
