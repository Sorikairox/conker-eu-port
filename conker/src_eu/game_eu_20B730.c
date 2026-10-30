#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void player_order_reset(void);

extern u8 g_chapter_replay; /* was D_800D3260 */

extern s8 g_menu_setup_step; /* was D_80090144 */

void game_request_transition(s32, s32, s32, s32, s32);


/* was func_151DDF20 */
void settings_reset_defaults(void) {
    s32 i;
    for (i = 0; i < 0x1C; i++) {
        g_settings[i] = g_settings_defaults[i];
    }
}

extern s8 g_settings_min[];        /* settings minimum (0x1C bytes); was D_80090210 */
extern s8 g_settings_max[];        /* settings maximum; was D_8009022C */

/*
 * P85: clamp the 0x1C settings bytes g_settings (signed): a value outside [g_settings_min[i], g_settings_max[i]] is reset to
 * its default g_settings_defaults[i] (as settings_reset_defaults resets all of them). After a failed save checksum the settings are 0xFF
 * (-1) and this puts e.g. the language g_settings_language back in range. Callers pass arguments it ignores.
 */
/* was func_151DDF6C */
void settings_clamp_to_range(void) {
    s32 i;

    for (i = 0; i < 0x1C; i++) {
        if (g_settings[i] < g_settings_min[i] || g_settings_max[i] < g_settings[i]) {
            g_settings[i] = g_settings_defaults[i];
        }
    }
}

/* was func_151DE074 */
s32 pause_bit_invert(s32 arg0) {
    return ~arg0;
}

s32 music_system_reset();
s32 sound_voices_reset();

/* was func_151DE080 */
void pause_quit_to_menu(void) {
    g_chapter_replay = 0;
    game_request_transition(6, 0x1D, 0, 0, 1);
    g_game_mode = 3;
    g_menu_setup_step = 0;
    g_pause_open = 0;
    player_order_reset();
    sound_voices_reset();
    music_system_reset();
    g_player_count = 1;
    g_human_player_count = 1;
}

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
/* was func_151DE100 */
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
    s32 litItem;   /* the item drawn selected (P363: -1 while the port's OPTIONS row is selected) */
#ifdef PORT
    /* DELIBERATE PORT CHANGE (P363, native menus; docs/design/NATIVE_MENUS.md): a CUSTOMISATION SETTINGS row (P369; was "OPTIONS") in this pause menu that
     * opens the page's game-style menu (port/web/gmenu.js). Shown only while port_gmenu_row_shown() (P369: always while the
     * game is local: never online, in a recording / replay or under ?netdet, where this
     * menu's state is hashed) and not in the one-item pause (g_pause_simple / level 0x22); otherwise every line below
     * runs exactly as on the N64. The row sits under the item row (story: centred under PAUSED, between QUIT and CONT..;
     * multiplayer: under CONTINUE), drawn with font 0 like the game's other texts (text_printf_at, drop shadow) in
     * the item pictures' greens: bright when selected, dark otherwise. Stick down reaches it (story: from either item;
     * multiplayer: from CONTINUE, whose up / down did nothing), stick up leaves it; while it is selected
     * g_menu_cursor keeps the item it came from but no item is lit. A on it plays the choose sound (0x500) and asks the
     * page to open its menu (port_gmenu_request_open); the game's pause stays as it is meanwhile (the page gives the game
     * an idle pad 1), so closing that menu comes back here with OPTIONS still selected. B / START resume the game as from
     * any item. port_pause_on_options = OPTIONS is selected (a port variable, outside game memory). */
    static s32 port_pause_on_options;
    s32 optionsRow;   /* the OPTIONS row is shown this frame */
    void port_pause_customisation_row_draw(s32 selected, s32 count, s32 yOff);   /* after this function; was port_pause_options_row_draw */
#endif

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
#ifdef PORT
                port_pause_on_options = 0;
#endif
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
#ifdef PORT
    optionsRow = !simple && port_gmenu_row_shown();
    if (!optionsRow) {
        port_pause_on_options = 0;
    }
    if ((s8) g_menu_cursor < count && optionsRow
        && (port_pause_on_options ? (g_pause_last_stick_y < 31 && stickY >= 31)
                                  : ((count == 2 || (s8) g_menu_cursor == 0) && g_pause_last_stick_y >= -30 && stickY < -30))) {
        port_pause_on_options = !port_pause_on_options;   /* stick down to OPTIONS, stick up back to the item */
        sfx = 0x62D;
    } else if ((s8) g_menu_cursor < count && port_pause_on_options) {
        /* on OPTIONS the other stick moves do nothing */
    } else
#endif
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
    litItem = (s8) g_menu_cursor;
#ifdef PORT
    if (port_pause_on_options) {
        litItem = -1;
    }
#endif
    y = yOff + 0x73;
    if (simple) {
        g_menu_cursor = 0;
        text_printf_at(0x94, y, 1, (s32) g_str_pause_simple_item, 0xD);
    } else {
        text_printf_at(0x94, y, 1, (s32) g_str_pause_title, 0x1A);
        if ((s8) g_menu_cursor < count) {
            text_printf_at(0xD5, y, 1, (s32) g_str_pause_continue, (litItem == 0) + 0xC);
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
                text_printf((s32) g_str_pause_restart, (litItem == 1) + 0x21);
                sel = 2;
                text_set_pos(0x53, yOff + 0x82);
            }
            text_printf((s32) g_str_pause_quit, (sel == litItem) + 0xE);
#ifdef PORT
            if (optionsRow) {
                port_pause_customisation_row_draw(port_pause_on_options, count, yOff);
            }
#endif
        }
#ifdef PORT
        if (port_pause_on_options && !(g_menu_pressed & 0x1000)) {
            if (g_menu_pressed & 0x8000) {
                port_gmenu_request_open();   /* A on OPTIONS: the page opens its menu over this pause */
                sfx = 0x500;
            } else if (g_menu_pressed & 0x4000) {
                g_pause_unpause_timer = 5;   /* B resumes, as from the items */
                g_pause_input_delay = 10;
            }
        } else
#endif
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

void screen_fade_update(void);
#ifdef PORT
/* P363 / P364: the port's row in the game's own menus (pause menu: game_pause_update; title menu: title_slot_page,
 * menu_mode_select_page), P369: labelled CUSTOMISATION SETTINGS (was "OPTIONS"; the page's menu is called the
 * customisation settings since the game-style menus are always on), or CUSTOMISATION where the full label would not fit
 * the 320-unit picture with a 16-unit margin at centreX (the multiplayer pause menu and the MULTI page, centred near
 * 233). Font 0 text through the game's text queue, in the item pictures' greens (bright when selected, dark otherwise),
 * drop shadow, scale 1.2, centred at centreX, top at y, with the page's alpha.
 * centreX / y are where the row should appear, in the units the item pictures are placed in (the 320 x 240 picture):
 * a text node lands about 1.1 x further right and 1.125 x further down than a picture node with the same numbers
 * (measured on the screenshots: P363's row, placed at the pictures' numbers, sat about 12 units right of PAUSED), so
 * the numbers are divided by that here. Flag 0x40 keeps text_queue_draw from also multiplying the position by
 * g_hud_scale_x / _y (pictures never get that), 0x80 adds the drop shadow; the queue's own centring (flag 1) is not
 * used (it subtracts half the scaled width from the scaled x). Widths at scale 1.2 in these units (the page's
 * GameFont.measure x 1.1, as "OPTIONS" measured 57 at scale 1): CUSTOMISATION SETTINGS 210, CUSTOMISATION 128.
 * Font 0 has every letter of both (checked with the page's glyph map). Leaves the text colour white with that alpha
 * and the scale as it was. */
void port_menu_customisation_row_draw(s32 selected, s32 centreX, s32 y, s32 alpha) { /* was port_menu_options_row_draw */
    void port_menu_text_row_draw(const char *label, s32 width, f32 scale, s32 selected, s32 centreX, s32 y, s32 alpha);

    if (centreX - 210 / 2 >= 16 && centreX + 210 / 2 <= 320 - 16) {
        port_menu_text_row_draw("CUSTOMISATION SETTINGS", 210, 1.2f, selected, centreX, y, alpha);
    } else {
        port_menu_text_row_draw("CUSTOMISATION", 128, 1.2f, selected, centreX, y, alpha);
    }
}
/* P367: the same for any label: width = its width in units at that scale (centred at centreX). */
void port_menu_text_row_draw(const char *label, s32 width, f32 scale, s32 selected, s32 centreX, s32 y, s32 alpha) {
    f32 oldScale = g_text_scale;

    if (selected) {
        text_set_color(0x8C, 0xFF, 0x10, alpha);   /* like the lit item pictures */
    } else {
        text_set_color(0x2A, 0x6A, 0x1A, alpha);   /* like the dark ones */
    }
    text_set_scale(scale);
    text_printf_at((centreX - width / 2) * 10 / 11, y * 8 / 9, 0xC0, (s32) label); /* 0x40: position not scaled, 0x80: drop shadow */
    text_set_scale(oldScale);
    text_set_color(0xFF, 0xFF, 0xFF, alpha);
}
/* P363: the pause menu's row (see game_pause_update); P369: CUSTOMISATION SETTINGS in story, CUSTOMISATION in multiplayer. */
void port_pause_customisation_row_draw(s32 selected, s32 count, s32 yOff) { /* was port_pause_options_row_draw */
    /* multiplayer: centred at 233, under the CONTINUE picture (drawn from x 0xD5, its centre near 233); story: centred
     * at 162, under PAUSED, between QUIT and CONT..; under the item row (yOff + 0x73; the pictures reach about
     * yOff + 0x96) */
    port_menu_customisation_row_draw(selected, count == 3 ? 233 : 162, yOff + 0x9C, g_menu_prompt_alpha_lo);
}
static s32 port_intro_skipped; /* P324 "Skip intro": done once per boot (the attract loop also returns to level 0x21) */
static s32 port_warp_started;  /* P327 ?warp: done once per boot */
void port_warp_game_start(s32 level, s32 scene);
#endif
/* intro_mode_update: game mode 11 (set by menu_init at power-on), the boot screen on level 0x25: the age / legal /
 * logo pages run on the timer g_game_mode_timer (A skips ahead), then at 0x2C7 mode 1 and level 0x21, the logo-screen
 * intro whose script finally enters the title menu (menu_reset_and_enter). */
/* was func_151DEBB4 */
void intro_mode_update(void) {
    screen_fade_update();
    *(s32 *)((u8 *)g_objects + 0x25C) |= 0x200;
    g_objects[0].y_position = 1000.0f;
    if (g_os_tv_type != 0) {
        g_game_mode_timer = 0;
    }
    if (g_game_mode_timer >= 0x119 && (g_menu_pressed & 0x8000)) {
        if (g_game_mode_timer < 0x190) {
            g_game_mode_timer = 0x190;
        }
        if (g_game_mode_timer >= 0x1F5 && g_game_mode_timer < 0x258) {
            g_game_mode_timer = 0x258;
        }
    }
#ifdef PORT
    /* DELIBERATE PORT CHANGE (P324, user request): page option "Skip intro" (PORT_OPT_SKIP_INTRO, default off).
     * Step 1 of 2: the boot screen ends early (its timer jumps to the end), so the logo-screen level 0x21 starts
     * next; step 2 is in menu_fade_load_options. It waits until the boot screen has run 25 frames: a level request
     * on its very first frame, while the power-on load of level 0x25 is still settling, stops the game (P324 test).
     * Off = the N64 path. */
    if (port_option(PORT_OPT_SKIP_INTRO) && !port_intro_skipped && g_game_mode_timer >= 25) {
        g_game_mode_timer = 0x2C7;
    }
#endif
#ifdef PORT
    /* TEST AID (P327, not a game feature): ?warp=<level hex>[&warpscene=N] starts gameplay on that level straight
     * from the boot screen, skipping the legal / logo pages, the logo-screen intro, the title menu and the opening
     * (port_warp_game_start). Same 25-frame wait as "Skip intro" (a level request on the first boot frame stops the
     * game). Without ?warp, port_warp_level() is 0 and this does nothing. */
    if (!port_warp_started && g_game_mode_timer >= 25 && port_warp_level() > 0) {
        port_warp_started = 1;
        port_warp_game_start(port_warp_level(), port_warp_scene());
        return;
    }
#endif
    if (g_game_mode_timer >= 0x2C7) {
        g_menu_input_lock_frames = 2;
        g_game_mode = 1;
        g_chapter_replay = 0;
        game_request_transition(6, 0x21, 0, 0, 1);
        *(u8 *)&g_screen_fade_alpha = 0xFF;
    }
}

void menu_enter_title(void);

/* was func_151DECB4 */
void menu_reset_and_enter(void) {
    g_game_mode_timer = 0;
    g_menu_blink_alpha = 0;
    g_menu_blink_dir = 0;
    g_menu_flag_ebc = 0;
    g_menu_input_lock_frames = 2;
    menu_enter_title();
}

/* menu_fade_load_options: game mode 1 (the logo-screen intro on level 0x21), once per frame: fade speed 4, no fade
 * overlay, and the save's options block is requested until it has loaded (g_save_options_loaded). The intro's scene script
 * leaves for the title menu itself (scene opcode 0x67 -> menu_reset_and_enter). */
/* was func_151DECFC */
void menu_fade_load_options(void) {
    g_menu_fade_speed = 4;
    g_screen_fade_alpha = 0;
    if (g_save_options_loaded == 0) {
        save_request_options_load();
    }
#ifdef PORT
    /* DELIBERATE PORT CHANGE (P324): "Skip intro" step 2. Once level 0x21 is running, enter the title menu with the
     * call its intro script ends with, so the intro never plays. It waits until mode 1 has run 32 frames (g_game_mode_timer
     * restarts at 0 on the mode change; level 0x21 is up about 7 frames in): a menu request on the level's first
     * frame stops the game, like the level request on the boot screen's first frame (P324 tests). Saves are unaffected: the options load above
     * is requested as before, and the menu (menu_mode_update) requests the slot, config and options loads itself on
     * its first frames. Only once per boot, so the attract loop (back to level 0x21) behaves as on the N64. */
    if (port_option(PORT_OPT_SKIP_INTRO) && !port_intro_skipped && g_level_id == 0x21 && g_game_mode_timer >= 32) {
        port_intro_skipped = 1;
        menu_reset_and_enter();
    }
#endif
}


/* was func_151DED3C */
void menu_enter_title(void) {
    g_chapter_replay = 0;
    game_request_transition(6, 0x1D, 0, 0, 1);
    g_game_mode = 3;
    g_menu_scene_start_state = 1;
    g_menu_input_lock_frames = 2;
    g_menu_setup_step = 0;
    (*(s8 *)((u8 *)g_menu_state + 0x3E)) = 0;
    (*(s8 *)((u8 *)g_menu_state + 0x2B)) = 5;
    (*(s8 *)((u8 *)g_menu_state + 0x2C)) = (s8) (*(s8 *)((u8 *)g_menu_state + 0x2B));
}

/* was func_151DEDC8 */
void game_mode_stub(void) {
}

/* P117: the menu state record g_menu_state (points at g_menu_state_rec, set by menu_init). */
typedef struct MenuState {
    f32 x0;
    f32 x4;
    f32 fade;           /* 0x08: page fade-in, >= 0.5 shows the page, 1.0 = done */
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    u16 input;          /* 0x20: controller 1's menu input bits of this frame */
    u16 padInput[4];    /* 0x22: menu input bits per controller (1 up, 2 down, 4 left, 8 right, 0x10 accept, 0x20 back, 0x40 / 0x80 C buttons) */
    s8 x2A;
    s8 x2B;
    s8 titlePage;       /* 0x2C: page of the title menu (menu 0) */
    s8 x2D;
    s8 stickX[4];       /* 0x2E: last stick x per controller (0 = released, re-arms the edge) */
    s8 stickY[4];       /* 0x32 */
    s8 repeatX[4];      /* 0x36: auto-repeat counters */
    s8 repeatY[4];      /* 0x3A */
    s8 menu;            /* 0x3E: 0 = title menu, 1 = main menu */
    s8 mainPage;        /* 0x3F: page of the main menu (menu 1) */
    s8 prevMainPage;    /* 0x40 */
    s8 x41;
    s8 x42;
    s8 x43;             /* 0x43: P120: set when the main menu camera slid back to the title (carousel) */
    s8 x44;
} MenuState;

/* P127: MenuPad is defined before game_pause_update */
extern MenuPad g_cont_pads[4];   /* controller state, 6 bytes each; was D_800BED38 */
extern s8 g_menu_queue_drop_count;           /* queue entries to drop; was D_80090110 */
extern s8 g_menu_player_queue;           /* first of a 16-byte queue; was D_800901E4 */
extern u16 g_cont_pressed;          /* new button presses per controller (u16 each); was D_800BED50 */
extern s8 g_cutscene_menu_skip_req; /* was D_80090124 */
extern s8 g_menu_stick_x_held;           /* bit i: controller i's stick x holds (no auto-repeat); was D_8009017C */
extern s8 g_settings_arrow_row; /* was D_80090184 */
extern f32 g_menu_slide_phase; /* was D_80090188 */
extern s32 g_menu_attract_unk_1c4; /* was D_800901C4 */
extern u8 g_settings_sel; /* was D_800901D4 */
extern f32 g_settings_scroll; /* was D_800901D8 */
extern f32 g_settings_scroll_speed; /* was D_800901DC */
extern s8 g_menu_joined_count; /* was D_800901E0 */
extern s8 g_title_info_screen; /* was D_800902A4 */
extern s8 g_title_screen_adjust; /* was D_800902A8 */
extern s16 g_menu_prompt_timer; /* was D_800902AC */
extern u8 g_menu_alpha; /* was D_800E0EC4 */
extern u8 g_menu_page_alpha; /* was D_800E0EC5 */
extern u8 g_menu_pending_page; /* was D_800E0EC6 */
extern u8 g_menu_cursor; /* was D_800901CC */
void menu_sprites_load(void);
void save_slots_reset(void);
void menu_show_stop_objects(void);
void menu_char_slots_clear(void);
void save_request_slot_load(s32 arg0);
void save_request_config_load(void);
void save_request_options_load(void);
void screen_fade_update(void);
void cutscene_scene_load(s32, s32, s32, s32, s32);
void text_set_color(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
void text_printf_at(s32, s32, u8, s32, ...);  /* varargs, as its definition (game_70200) */
void music_post_event_request(u32, s32);
void title_press_start_page(void);
void title_chapter_select_page(void);
void title_slot_page(void);
void menu_mode_select_page(void);
void main_settings_page(void);
void menu_player_join_page(void);
void main_players_page(void);
void menu_team_select_page(void);
void menu_run_level_start(void);

#define MENU_STICK_ON 0x32      /* stick threshold (+-50) */

// menu_mode_update: game mode 3 (title / main menu on level 0x1D), once per frame.
// Frames 0..4 after entering the mode set things up (frame 0: menu sprites, save slots, settings), then the
// pending scene start (g_menu_scene_start_state), the input queue shift, the controller -> menu input bits with stick auto-repeat,
// the attract-mode check (demo: any button stops it), the "press start"-like blinking prompt fade g_menu_prompt_timer,
// the menu music and finally the page handler of the title menu (rec->titlePage) or of the main menu
// (rec->mainPage) once the page has faded in halfway; below that the menu input state is reset.
/* was func_151DEDD0 */
void menu_mode_update(void) {
    MenuState *rec;
    s32 frame;
    s32 i;
    s32 n;
    s32 x;
    s32 a;
    f32 f;
    s32 t;

    frame = (u8) g_menu_setup_step;
    if (frame < 5) {
        if (frame == 0) {
            menu_sprites_load();
            save_slots_reset();
            menu_show_stop_objects();
            menu_char_slots_clear();
            frame = (u8) g_menu_setup_step;
        }
        if (frame < 4) {
            save_request_slot_load(frame);
        } else {
            save_request_config_load();
        }
        g_menu_setup_step = (u8) g_menu_setup_step + 1;
    } else if (g_save_options_loaded == 0) {
        save_request_options_load();
    }

    if ((u8) g_menu_scene_start_state != 0) {
        *(s32 *) ((u8 *) g_player_views + 0x2C) = 0x80000;
        cutscene_scene_load(g_level_id, 1, 0, 0, 0);
        g_menu_scene_start_state = 0;
        return;
    }

    /* drop the first n entries of the two 16-byte queues (copies entry i + n to i for i in n .. 15 - n, as the asm) */
    n = g_menu_queue_drop_count;
    frame = (u8) g_menu_setup_step;
    if (n != 0) {
        for (i = n; i < 0x10 - n; i++) {
            (&g_menu_player_queue)[i] = (&g_menu_player_queue)[i + n];
            g_mp_player_team[i] = g_mp_player_team[i + n];
        }
        g_menu_queue_drop_count = 0;
    }
    if (frame >= 5) {
        screen_fade_update();
    }

    for (i = 0; i < 4; i++) {
        rec = (MenuState *) g_menu_state;
        rec->padInput[i] = 0;
        if ((u8) g_screen_fade_alpha == 0) {
            /* edges: the stick crosses +-50 since the last frame; buttons A / Start accept, B back */
            if (rec->stickY[i] >= -(MENU_STICK_ON - 1) && g_cont_pads[i].stickY < -(MENU_STICK_ON - 1)) {
                rec->padInput[i] |= 2;
            }
            if (rec->stickY[i] < MENU_STICK_ON && g_cont_pads[i].stickY >= MENU_STICK_ON) {
                rec->padInput[i] |= 1;
            }
            if (rec->stickX[i] >= -(MENU_STICK_ON - 1) && g_cont_pads[i].stickX < -(MENU_STICK_ON - 1)) {
                rec->padInput[i] |= 4;
            }
            if (rec->stickX[i] < MENU_STICK_ON && g_cont_pads[i].stickX >= MENU_STICK_ON) {
                rec->padInput[i] |= 8;
            }
            if ((&g_cont_pressed)[i] & 0x1000) {
                rec->padInput[i] |= 0x10;
            }
            if ((&g_cont_pressed)[i] & 0x8000) {
                rec->padInput[i] |= 0x10;
            }
            if ((&g_cont_pressed)[i] & 0x4000) {
                rec->padInput[i] |= 0x20;
            }
            if ((&g_cont_pressed)[i] & 2) {
                rec->padInput[i] |= 0x40;
            }
            if ((&g_cont_pressed)[i] & 1) {
                rec->padInput[i] |= 0x80;
            }
            rec->stickY[i] = g_cont_pads[i].stickY;
            rec->stickX[i] = g_cont_pads[i].stickX;
        } else {
            rec->stickX[i] = 0;
            rec->stickY[i] = 0;
        }
        /* auto-repeat: a held stick forgets its last value after 0x33 ticks (then every 0x0B) */
        x = rec->stickX[i];
        if (x >= -(MENU_STICK_ON - 1) && x < MENU_STICK_ON) {
            rec->repeatX[i] = 0;
            g_menu_stick_x_held &= ~(1 << i);
        } else if (!(g_menu_stick_x_held & (1 << i))) {
            rec->repeatX[i] += g_frame_ticks;
            if (rec->repeatX[i] >= 0x33) {
                rec->repeatX[i] = 0x28;
                rec->stickX[i] = 0;
            }
        }
        x = rec->stickY[i];
        if (x >= -(MENU_STICK_ON - 1) && x < MENU_STICK_ON) {
            rec->repeatY[i] = 0;
        } else {
            rec->repeatY[i] += g_frame_ticks;
            if (rec->repeatY[i] >= 0x33) {
                rec->repeatY[i] = 0x28;
                rec->stickY[i] = 0;
            }
        }
    }
    rec = (MenuState *) g_menu_state;
    rec->input = rec->padInput[0];

    if (g_cutscene_slot_state == 1) {
        /* attract mode: a button press ends the demo */
        g_menu_attract_unk_1c4 = 0;
        if (g_game_mode_timer < 0x546 && g_cont_pressed != 0) {
            g_cutscene_menu_skip_req = 1;
        }
        return;
    }

    if (g_menu_prompt_timer > 0) {
        t = (s16) (g_menu_prompt_timer - g_frame_ticks);
        g_menu_prompt_timer = t;
        if (t >= 0x33) {
            if (t >= 0x97) {
                a = 0xFF - (t - 0x96) * 8;
                if (a < 0) {
                    a = 0;
                }
            } else {
                a = (t - 0x32) * 8;
                if (a >= 0x100) {
                    a = 0xFF;
                }
                if (a == 0xFF && t >= 0x65) {
                    g_menu_prompt_timer = 0x78;
                }
                if (((MenuState *) g_menu_state)->input & 0x10) {
                    g_menu_prompt_timer = 0x64;
                }
            }
            text_set_color(0xFF, 0x32, 0x32, (a - (a >> 2)) & 0xFF);
            text_printf_at(0x94, 0xC0, 0x81, *(s32 *) ((u8 *) g_text_strings + 0x23C));
        }
    }

    *(s32 *) ((u8 *) g_player_views + 0x2C) = 0x80000;
    music_post_event_request(4, ((MenuState *) g_menu_state)->menu);
    rec = (MenuState *) g_menu_state;
    if (rec == NULL || (u8) g_menu_setup_step < 5) {
        return;
    }
    rec->prevMainPage = rec->mainPage;
    rec = (MenuState *) g_menu_state;
    a = (rec->fade - 0.5f) * 512.0f;
    if (a < 0) {
        a = 0;
    } else if (a >= 0x100) {
        a = 0xFF;
    }
    g_menu_alpha = a;
    f = rec->fade;
    if (f >= 0.5f) {
        if (f < 1.0f) {
            rec->input &= ~0x10;
            rec = (MenuState *) g_menu_state;
        }
        if (rec->menu == 0) {
            if (rec->titlePage != 1) {
                g_title_info_screen = 0;
                g_title_screen_adjust = 0;
            }
            switch (rec->titlePage) {
                case 1:
                    title_press_start_page();
                    break;
                case 2:
                    title_chapter_select_page();
                    break;
                case 3:
                case 4:
                case 5:
                    title_slot_page();
                    break;
            }
        } else if (rec->menu == 1) {
            g_save_cur_slot = -1;
            switch ((u8) rec->mainPage) {
                case 0:
                    menu_mode_select_page();
                    break;
                case 2:
                    main_settings_page();
                    break;
                case 3:
                    menu_run_level_start();
                    break;
                case 4:
                    menu_player_join_page();
                    break;
                case 1:
                    menu_team_select_page();
                    break;
                case 5:
                    main_players_page();
                    break;
            }
        }
    } else {
        /* page not shown yet: reset the menu input state */
        g_menu_pending_page = -1;
        g_menu_page_alpha = 0xFF;
        rec->mainPage = 0;
        ((MenuState *) g_menu_state)->x41 = 0;
        g_menu_joined_count = 1;
        g_menu_player_queue = 0;
        g_menu_cursor = 0;
        for (i = 1; i < 0x10; i++) {
            (&g_menu_player_queue)[i] = -1;
        }
        for (i = 0; i < 0x10; i++) {
            g_mp_player_team[i] = 0;
        }
        g_settings_sel = 0;
        g_settings_scroll = 0.0f;
        g_settings_scroll_speed = 0.0f;
        g_menu_slide_phase = 0.0f;
        g_settings_arrow_row = 0;
    }
}

extern u8 g_str_title_info[]; /* "#": text id; was D_800ABBE4 */
extern u8 g_str_title_adjust_head[]; /* was D_800ABBE8 */
extern u8 g_str_title_adjust_mid[]; /* was D_800ABBEC */
extern u8 g_str_title_adjust_left[]; /* was D_800ABBF0 */
extern u8 g_str_title_adjust_right[]; /* was D_800ABBF4 */
extern u8 g_str_title_adjust_up[]; /* was D_800ABBF8 */
extern u8 g_str_title_adjust_down[]; /* was D_800ABBFC */
extern u8 g_menu_song; /* was D_800E0EC7 */
extern s8 g_aiscript_cheat_value; /* was D_800BEE0C */
extern s8 g_settings_screen_x; /* was D_800E1027 */
extern s8 g_settings_screen_y; /* was D_800E1028 */
extern s8 g_settings_screen_scale_x; /* was D_800E102A */
extern s8 g_settings_screen_scale_y; /* was D_800E102B */
extern s8 g_settings_sound_mode; /* was D_800E1019 */
struct216 *aiscript_find_by_kind(s32, u8);
void settings_list_draw(s32, s32, s32, s32, s32);
void settings_apply_sound_mode(void);
void music_stop_song(u8, s32);
s32 mp3_stream_get_state();

// title_press_start_page: title menu page 1 (Conker on the title screen, object 9). g_menu_pending_page != -1 runs a fade-out
// of the page alpha g_menu_page_alpha (32 per tick); at 0 it toggles either the "info" screen g_title_info_screen (playing Conker's
// animation 0xE / 0xF and a random voice 0xC8..0xC9 / 0xBE..0xC0) or, for 2, the screen-position screen g_title_screen_adjust;
// otherwise the alpha fades in. The plain page draws the title (settings_list_draw) and handles accept (menu item 0x15 ->
// info, 0x19 -> screen position), left/right on item 9 (language: next voice bank), back (save_request_options_write). The info
// screen shows text 0x10 and reads the controller pak flags g_cheat_flags into g_aiscript_cheat_value; the screen-position screen
// moves the picture offset g_settings[0x17 / 0x18] with the stick and its scale [0x1A / 0x1B] with the C buttons.
/* was func_151DF6A4 */
void title_press_start_page(void) {
    struct127 *obj;
    s32 v;
    s32 alpha;
    s32 voice;
    s8 x;
    s8 y;
    s8 sx;
    s8 sy;
    u16 in;
#ifdef PORT
    /* DELIBERATE PORT CHANGE (P367, native menus; docs/design/NATIVE_MENUS.md): a fourth row CUSTOMISATION (P369; was "SETTINGS") on this page
     * (the game's own OPTIONS page: sound / language, cheats, screen position, drawn by settings_list_draw as a column)
     * that opens the page's game-style menu (port/web/gmenu.js), like the OPTIONS rows of the pause menu (P363) and of
     * the save slot / MULTI pages (P364). Shown only while port_gmenu_row_shown() (always while the game is local (P369: no page option any more): never online, in a recording / replay or under ?netdet, where this menu's state is
     * hashed); otherwise every line below runs exactly as on the N64. It sits one row under the last item (the column's
     * spacing, 0x22), with the game's own cursor (the two joystick pictures, text id 0x1A) sliding to it like
     * settings_list_draw's (port_title_customisation_row_draw, after this function); settings_list_draw draws no cursor
     * meanwhile (its arg2 = 0), so the list's slide state (g_settings_arrow_row / g_menu_slide_phase) stands still.
     * The 28-item list itself is unchanged: the row is not a g_settings item, the selection g_settings_sel stays on the
     * screen-position item (0x19) and the list sees no direction / accept input while the row is selected.
     * Moves, as a ring with the game's own wrap: down from the last item (0x19) or up from the first (9) reaches the
     * row; up goes back to 0x19, down on to 9 (through the list's own wrap); g_settings_arrow_row = 3 on leaving makes
     * the game's cursor slide from the row. Sound 0x4FF on every move (the list's own), 0x500 when A / START chooses it:
     * that asks the page to open its menu (port_gmenu_request_title) and is taken out of this frame's input, so the
     * screen-position page does not open. B leaves the page as from any item. The selection is forgotten whenever the
     * page is not fully shown (fading to the info / screen-position screens or out of the page). State =
     * function-local statics (port variables, outside game memory). */
    static s32 port_title_on_settings;      /* SETTINGS is selected */
    static s32 port_title_settings_from;    /* the cursor slides from this row (0..2) to the row (3) */
    static f32 port_title_settings_slide;   /* 0..1 */
    s32 settingsRow;   /* the SETTINGS row is shown this frame */
    extern s16 g_settings_value_fade;
    void port_title_customisation_row_draw(s32 selected, s32 fromRow, f32 slide, s32 alpha); /* was port_title_settings_row_draw */
#endif

    obj = obj_find_by_setup_id(9);
    if (g_menu_pending_page != (u8) -1) {
        v = g_menu_page_alpha - (g_frame_ticks << 5);
        if (v <= 0) {
            v = 0;
            if ((s8) g_menu_pending_page != 2) {
                g_title_info_screen = !g_title_info_screen;
                if (!g_title_info_screen) {
                    voice = 0xE;
                    mp3_voice_play((random_int() & 1) + 0xC8, 0x7D00, 0x40);
                } else {
                    voice = 0xF;
                    mp3_voice_play((u32) random_int() % 3 + 0xBE, 0x7D00, 0x40);
                }
                if (obj != NULL) {
                    obj->unk232 = voice;
                    g_cur_obj = obj;
                    g_cur_obj_index = (s32) ((u8 *) obj - (u8 *) g_objects) / (s32) sizeof(struct127);
                    obj->unk218 = aiscript_find_by_kind(0, obj->unk232);
                    obj->unk21C = 0;
                    obj->unk201 = 0x14;
                }
            } else {
                g_title_screen_adjust = !g_title_screen_adjust;
            }
            g_menu_pending_page = -1;
        }
        ((MenuState *) g_menu_state)->input &= ~0x30;
    } else {
        v = g_menu_page_alpha + (g_frame_ticks << 5);
        if (v >= 0x100) {
            v = 0xFF;
        }
    }
    g_menu_page_alpha = v;
    alpha = (g_menu_alpha * v) >> 8;
    if (alpha >= 0xFE) {
        alpha = 0xFF;
    }

    if (!g_title_info_screen && !g_title_screen_adjust) {
#ifdef PORT
        settingsRow = port_gmenu_row_shown();
        if (!settingsRow || alpha != 0xFF) {
            port_title_on_settings = 0;
        }
        in = ((MenuState *) g_menu_state)->input;
        if (settingsRow && alpha == 0xFF && g_menu_slide_phase == 0.0f && g_settings_value_fade == 0xFF) {
            if (!port_title_on_settings) {
                if (((in & 2) && g_settings_sel == 0x19) || ((in & 1) && g_settings_sel == 9)) {
                    port_title_on_settings = 1;   /* down from the last item / up from the first: to SETTINGS */
                    port_title_settings_from = g_settings_arrow_row;
                    port_title_settings_slide = 0.0f;
                    g_settings_sel = 0x19;
                    ((MenuState *) g_menu_state)->input &= ~3;
                    sound_play_2d(0x4FF, 0x4650, 0x40, 0, 0);
                }
            } else if (port_title_settings_slide >= 1.0f) {
                if (in & 3) {
                    port_title_on_settings = 0;   /* up: back to 0x19; down: the list wraps on to 9 (its own sound) */
                    g_settings_arrow_row = 3;
                    if (in & 1) {
                        ((MenuState *) g_menu_state)->input &= ~1;
                        sound_play_2d(0x4FF, 0x4650, 0x40, 0, 0);
                    }
                } else if (in & 0x10) {
                    port_gmenu_request_title();   /* A / START on SETTINGS: the page opens its menu over the title */
                    sound_play_2d(0x500, 0x4650, 0x40, 0, 0);
                }
            }
        }
        if (port_title_on_settings) {
            ((MenuState *) g_menu_state)->input &= ~0x1F;   /* the list and the accept below see nothing; B still leaves */
        }
        settings_list_draw(0x02200200, 0, !port_title_on_settings, alpha & 0xFF, 1);
        if (settingsRow) {
            port_title_customisation_row_draw(port_title_on_settings, port_title_settings_from, port_title_settings_slide, alpha & 0xFF);
            if (port_title_on_settings && port_title_settings_slide < 1.0f) {
                port_title_settings_slide += 0.1f * (f32) g_frame_ticks;
            }
        }
#else
        settings_list_draw(0x02200200, 0, 1, alpha & 0xFF, 1);
#endif
        if (g_settings_sel == 9 && (((MenuState *) g_menu_state)->input & 0xC)) {
            settings_apply_sound_mode();
            music_stop_song(g_menu_song, 0);
            g_menu_song = music_play_menu_song(g_settings_sound_mode);
        }
        in = ((MenuState *) g_menu_state)->input;
        if ((in & 0x10) && g_menu_slide_phase == 0.0f) {
            if (g_settings_sel == 0x15) {
                g_menu_pending_page = 1;
                ((MenuState *) g_menu_state)->input &= ~0x30;
                in = ((MenuState *) g_menu_state)->input;
            } else if (g_settings_sel == 0x19) {
                g_menu_pending_page = 2;
                ((MenuState *) g_menu_state)->input &= ~0x30;
                in = ((MenuState *) g_menu_state)->input;
            }
        }
        if (in & 0x20) {
            save_request_options_write();
        }
    }

    if (obj != NULL) {
        if (mp3_stream_get_state() == 1) {
            if (obj->unk1FF == 0) {
                obj->unk1FF = 1;
            }
        } else {
            obj->unk1FF = 0;
        }
    }

    if (g_title_info_screen) {
        if (((MenuState *) g_menu_state)->input & 0x20) {
            g_menu_pending_page = 1;
        }
        ((MenuState *) g_menu_state)->input &= ~0x20;
        if (g_title_info_screen) {
            text_set_color(0xFF, 0, 0, alpha & 0xFF);
            text_printf_at(0x94, 0x14, 0x81, (s32) g_str_title_info, 0x10);
        }
        g_aiscript_cheat_value = 0;
        if (g_cheat_flags & 0x400000) {
            g_aiscript_cheat_value = 1;
        }
        if (g_cheat_flags & 0x800000) {
            g_aiscript_cheat_value = 2;
        }
    } else if (g_title_screen_adjust) {
        x = g_settings[0x17];
        y = g_settings[0x18];
        sx = g_settings[0x1A];
        sy = g_settings[0x1B];
        text_set_color(0xFF, 0, 0, alpha & 0xFF);
        text_printf_at(0x94, 0x28, 0x81, (s32) g_str_title_adjust_head, 0x3E);
        text_printf_at(0x94, 0x64, 0x81, (s32) g_str_title_adjust_mid, 0x1A);
        text_printf_at(0x7B, 0x64, 0x81, (s32) g_str_title_adjust_left, 0x3B);
        text_printf_at(0xAD, 0x64, 0x81, (s32) g_str_title_adjust_right, 0x3C);
        text_printf_at(0x94, 0x4B, 0x81, (s32) g_str_title_adjust_up, 0x5D);
        text_printf_at(0x94, 0x7D, 0x81, (s32) g_str_title_adjust_down, 0x5E);
        in = ((MenuState *) g_menu_state)->input;
        if ((in & 4) && x > 0) {
            x--;
        }
        if ((in & 8) && x < 0x20) {
            x++;
        }
        if ((in & 1) && y > 0) {
            y--;
        }
        if ((in & 2) && y < 0x10) {
            y++;
        }
        if ((g_cont_pressed & 2) && sx > 0) {
            sx--;
        }
        if ((g_cont_pressed & 1) && sx < 0x10) {
            sx++;
        }
        if ((g_cont_pressed & 8) && sy > 0) {
            sy--;
        }
        if ((g_cont_pressed & 4) && sy < 0x10) {
            sy++;
        }
        g_settings_screen_scale_x = sx;
        g_settings_screen_scale_y = sy;
        g_settings_screen_x = x;
        g_settings_screen_y = y;
        if (((MenuState *) g_menu_state)->input & 0x20) {
            g_menu_pending_page = 2;
        }
        ((MenuState *) g_menu_state)->input &= ~0x20;
    }
}

#ifdef PORT
/* P367: title_press_start_page's SETTINGS row (see there): the label in font 0 through the text queue (the shared
 * port_menu_text_row_draw: the port rows' greens, drop shadow; scale 1, about the width of the CHEATS picture so it
 * fits between the two cursor pictures), one column step (0x22) under the screen-position item, and while selected
 * the game's cursor: the two joystick pictures (text id 0x1A) left and right of the row, sliding from row fromRow with
 * settings_list_draw's own motion (x 50 + 20 sin(slide pi) from the centre 0x94, y linear) over slide 0..1. */
void port_title_customisation_row_draw(s32 selected, s32 fromRow, f32 slide, s32 alpha) { /* was port_title_settings_row_draw */
    extern u8 g_str_settings_arrow_r[];
    extern u8 g_str_settings_arrow_l[];
    void port_menu_text_row_draw(const char *label, s32 width, f32 scale, s32 selected, s32 centreX, s32 y, s32 alpha);
    f32 sinf(f32);
    s32 arrowX;
    s32 arrowY;

    /* centred like the item pictures (drawn at 0x94 with the centring flag, they land centred near 162), vertically in
     * the middle of the row's cursor pictures (about 33 units high from the row's top, 0x46 + 3 * 0x22 = 0xAC) */
    port_menu_text_row_draw("CUSTOMISATION", 107, 1.0f, selected, 162, 0xAC + 11, alpha);
    if (selected) {
        if (slide > 1.0f) {
            slide = 1.0f;
        }
        /* P369: CUSTOMISATION (107 units) is wider than the game's items (about 65): the cursor pictures move out by
         * half the difference as they slide in, so they frame the row like the game's items */
        arrowX = (s32) (50.0f + 20.0f * sinf(slide * 3.1415f) + 21.0f * slide);
        arrowY = (s32) ((f32) (fromRow * 0x22 + 0x46) + slide * (f32) ((3 - fromRow) * 0x22));
        text_set_color(0xFF, 0xFF, 0xFF, alpha);
        text_printf_at(arrowX + 0x94, arrowY, 1, (s32) g_str_settings_arrow_r, 0x1A);
        text_printf_at(0x94 - arrowX, arrowY, 1, (s32) g_str_settings_arrow_l, 0x1A);
    }
}
#endif

extern s8 g_chapter_scene_counts[];         /* scenes per chapter (9 chapters); was D_800ABC00 */
extern u8 g_str_chapter_title[];         /* "#": text id (chapter title); was D_800ABC0C */
extern u8 D_eu_800902B8[];      /* per-chapter text colour, 3 bytes (r, g, b) */
extern s8 g_chapter_sel;           /* chapter (0..8); was D_800902B0 */
extern u8 g_chapter_route_sel;           /* chosen route (scene) id, 0xFF = none; was D_800902B4 */
extern s8 g_chapter_list_scroll;           /* list scroll offset (animates by 2 towards 0); was D_800902D4 */
extern s8 g_chapter_prev_sel;           /* previous list selection; was D_800902D8 */
extern s8 g_chapter_step_dir;           /* chapter step direction (-1 / 1); was D_800902DC */
extern u8 g_chapter_blink_phase;           /* blink phase of the selected entry; was D_800902E0 */
extern s8 g_chapter_scene_sel;           /* list selection; was D_80090150 */
extern u8 **g_text_scene_names;          /* text table (scene names); P137: u8 ** as the loader below (P134 declared s32 *; NM build failed on the redeclaration); was D_800E0FB8 */
extern s32 g_cheat_flags;          /* cheat / unlock flags; was D_800E9D00 */
extern u8 g_save_final_scene_unlock; /* was D_800BE7FE */
extern u8 g_game_mode; /* was D_800E0B94 */
extern s8 g_menu_fade_speed; /* was D_80090114 */
extern s32 *g_menu_fade_callback; /* was D_800E0EB8 */
s32 save_route_table_load(s32, s32 *);
void save_route_table_free(void);
s32 save_route_check(s8, u8, s32 *, s32 *);
void chapter_scene_start(void);

// title_chapter_select_page: title page 2, the chapter / scene select. Left-right (g_menu_pending_page = 1 / 2) steps the
// chapter g_chapter_sel (0..8, wrapping) to the next one with an unlocked scene: the scene mask comes from the save route
// table (save_route_table_load / save_route_check per scene, save_route_table_free), cheat flags g_cheat_flags unlock a chapter's first scene
// (0x8000 every scene), chapter 0's first scene is always open and chapter 8's fourth scene opens with g_save_final_scene_unlock.
// If no other chapter has one the step is cancelled, else the page fades out (g_menu_pending_page = 3 / 4, alpha g_menu_page_alpha
// - 32 per tick), moves and fades back in. Up-down scrolls the unlocked scenes (g_chapter_scene_sel, scroll animation
// g_chapter_list_scroll); the list (11 px rows, a wrapped copy above and below, faded at the edges, the selection blinking) is
// drawn in the chapter's colour under the chapter title. Accept on a scene (g_chapter_route_sel) starts it: mode 7 (fade)
// with the callback chapter_scene_start, g_menu_fade_speed = 3. Sound 0x4FF on a move, 0x500 on accept.
/* was func_151DFD0C */
void title_chapter_select_page(void) {
    u8 rows[32];    /* the asm keeps 0x54 bytes; at most 31 scenes */
    s32 alpha;
    s32 sfx;
    s8 cursor;
    s8 orig;
    s32 again;
    s32 first;      /* text index of the chapter's first scene */
    s32 mask;       /* unlocked scenes */
    s32 count;      /* number of unlocked scenes */
    s32 i;
    s32 k;
    s32 bit;
    s32 found;
    s32 tmp;
    s32 a;
    s32 textAlpha;
    s8 dir;
    s8 scroll;
    s32 rgb;
    s32 lineAlpha;
    s32 y;
    s32 listEnd;
    s8 pass;
    u8 *col;
    u16 in;

    alpha = g_menu_alpha;
    sfx = 0;
    cursor = g_chapter_sel;
    dir = g_menu_pending_page;
    do {
        orig = cursor;
        again = 0;
        if (dir == 1) {
            g_chapter_sel = cursor - 1;
            if (g_chapter_sel < 0) {
                g_chapter_sel = 8;
            }
            g_chapter_step_dir = -1;
        } else if (dir == 2) {
            g_chapter_sel = cursor + 1;
            if (g_chapter_sel >= 9) {
                g_chapter_sel = 0;
            }
            g_chapter_step_dir = 1;
        }
        cursor = g_chapter_sel;
        do {
            first = 1;
            for (i = 0; i < cursor; i++) {
                first += g_chapter_scene_counts[i];
            }
            mask = 0;
            count = 0;
            if (g_cheat_flags & 0x8000) {
                mask = -1;
            }
            if (cursor == 8 && (g_cheat_flags & 2)) {
                mask |= 1;
            }
            if (cursor == 7 && (g_cheat_flags & 4)) {
                mask |= 1;
            }
            if (cursor == 6 && (g_cheat_flags & 0x1000)) {
                mask |= 1;
            }
            if (cursor == 5 && (g_cheat_flags & 0x4000)) {
                mask |= 1;
            }
            if (cursor == 4 && (g_cheat_flags & 0x1000000)) {
                mask |= 1;
            }
            if (cursor == 3 && (g_cheat_flags & 0x2000000)) {
                mask |= 1;
            }
            if (cursor == 2 && (g_cheat_flags & 0x4000000)) {
                mask |= 1;
            }
            found = save_route_table_load(cursor, &i);
            if (g_chapter_sel == 0) {
                mask |= 1;
            }
            if (found != 0) {
                for (i = 0; i < g_chapter_scene_counts[g_chapter_sel] - 1; i++) {
                    if (save_route_check(g_chapter_sel, i, &tmp, NULL)) {
                        mask |= 1 << i;
                    }
                    if (mask & (1 << i)) {
                        count++;
                    }
                }
                save_route_table_free();
                if (g_chapter_sel == 8 && g_save_final_scene_unlock != 0 && !(mask & 8)) {
                    mask |= 8;
                    count++;
                }
            } else {
                /* no route table: only the scene the count names */
                mask |= 1 << i;
                count = 1;
            }
            if (count == 0) {
                /* nothing unlocked in this chapter: try the next one in the same direction */
                g_chapter_sel += g_chapter_step_dir;
                if (g_chapter_sel >= 9) {
                    g_chapter_sel = 0;
                }
                if (g_chapter_sel < 0) {
                    g_chapter_sel = 8;
                }
            }
            cursor = g_chapter_sel;
        } while (count == 0);
        dir = g_menu_pending_page;
        if (dir == 1 || dir == 2) {
            if (orig == g_chapter_sel) {
                g_menu_pending_page = -1;                /* no other chapter: cancel */
            } else {
                g_menu_pending_page = dir + 2;           /* fade out, then move (3 = left, 4 = right) */
                g_chapter_sel = orig;
            }
            again = 1;
            dir = g_menu_pending_page;
        }
        cursor = g_chapter_sel;
    } while (again);

    if (dir > 0) {
        a = g_menu_page_alpha - g_frame_ticks * 32;
        if (a <= 0) {
            a = 0;
            g_menu_pending_page = -1;
            if (dir == 3) {
                g_chapter_sel = cursor - 1;
                if (g_chapter_sel < 0) {
                    g_chapter_sel = 8;
                }
                g_chapter_step_dir = -1;
            } else {
                g_chapter_sel = cursor + 1;
                if (g_chapter_sel >= 9) {
                    g_chapter_sel = 0;
                }
                g_chapter_step_dir = 1;
            }
        }
    } else {
        a = g_menu_page_alpha + g_frame_ticks * 32;
        if (a >= 0x100) {
            a = 0xFF;
        }
    }
    g_menu_page_alpha = a;
    textAlpha = (a * alpha) >> 8;
    if (textAlpha >= 0xFE) {
        textAlpha = 0xFF;
    }

    scroll = g_chapter_list_scroll;
    if (scroll > 0) {
        scroll -= 2;
    } else if (scroll < 0) {
        scroll += 2;
    }
    g_chapter_list_scroll = scroll;
    if (scroll == 0 && g_menu_page_alpha == 0xFF) {
        if (g_cont_pads[0].stickY < -0x31) {
            g_chapter_prev_sel = g_chapter_scene_sel;
            g_chapter_scene_sel++;
            g_chapter_list_scroll = -10;
            sfx = 0x4FF;
        } else if (g_cont_pads[0].stickY >= 0x32) {
            g_chapter_prev_sel = g_chapter_scene_sel;
            g_chapter_scene_sel--;
            g_chapter_list_scroll = 10;
            sfx = 0x4FF;
        }
    }
    if (g_chapter_scene_sel < 0) {
        g_chapter_scene_sel = 0;
        g_chapter_list_scroll = 0;
        sfx = 0;
    }
    if (g_chapter_scene_sel >= count) {
        g_chapter_scene_sel = count - 1;
        g_chapter_list_scroll = 0;
        sfx = 0;
    }
    text_set_color(0xFF, 0xFF, 0xFF, textAlpha & 0xFF);
    text_printf_at(0x94, 0x4D, 0x81, (s32) g_str_chapter_title, g_chapter_sel + 0x42);

    /* the unlocked scenes' numbers, in order */
    bit = 0;
    for (k = 0; k < count; k++) {
        while (!(mask & (1 << bit))) {
            bit++;
        }
        rows[k] = bit;
        bit++;
    }

    col = &D_eu_800902B8[g_chapter_sel * 3];
    text_set_color(0xFF, 0, 0, textAlpha & 0xFF);
    pass = -1;
    if (count < 6) {
        listEnd = count * 11;
        y = 0x2F;
    } else {
        y = -(g_chapter_scene_sel * 11) - g_chapter_list_scroll + 0x45;
        listEnd = 0x37;
        if (y >= 0x30) {
            y = 0x2F;
        }
    }
    k = count - 3;
    for (i = -3; i < count + 3; i++) {
        rgb = g_chapter_list_scroll * 12;
        if (rgb < 0) {
            rgb = -rgb;
        }
        if (k == g_chapter_scene_sel) {
            rgb = 0xFF - rgb;
            if (rgb == 0xFF) {
                /* selected and settled: blink 0xC0 .. 0xFF */
                tmp = (g_chapter_blink_phase * 2) & 0x7F;
                if (tmp >= 0x40) {
                    tmp = 0x7F - tmp;
                }
                rgb = tmp + 0xC0;
                g_chapter_blink_phase += g_frame_ticks;
            } else {
                g_chapter_blink_phase = 0x1F;
            }
        } else if (g_chapter_prev_sel == k) {
            rgb += 0x80;
        } else {
            rgb = 0x80;
        }
        if (k == g_chapter_scene_sel) {
            g_chapter_route_sel = rows[k];
        }
        /* fade the rows in at the top (y 70..80) and out at the bottom (listEnd + 70 .. 80) */
        if (y < 0x50) {
            lineAlpha = y * 25 - 1750;
        } else if (listEnd + 0x46 < y && y < listEnd + 0x50) {
            lineAlpha = (listEnd - y + 10) * 25 + 1750;
        } else {
            lineAlpha = 0xFF;
        }
        if (lineAlpha < 0) {
            lineAlpha = 0;
        }
        if (lineAlpha >= 0xFA) {
            lineAlpha = 0xFF;
        }
        if (textAlpha < lineAlpha) {
            lineAlpha = textAlpha;
        }
        text_set_color((col[0] * rgb) >> 8, (col[1] * rgb) >> 8, (col[2] * rgb) >> 8, lineAlpha & 0xFF);
        if (y >= 0x46 && y < listEnd + 0x50 && pass == 0) {
            text_printf_at(0x94, y + 0xF, 0x81, (s32) g_text_scene_names[rows[k] + first]);
        }
        y += 11;
        k++;
        if (k >= count) {
            pass++;
            k = 0;
        }
    }

    if (g_menu_page_alpha == 0xFF) {
        in = ((MenuState *) g_menu_state)->input;
        if (in & 4) {
            g_menu_pending_page = 1;
            sfx = 0x4FF;
        } else if (in & 8) {
            g_menu_pending_page = 2;
            sfx = 0x4FF;
        }
        if ((((MenuState *) g_menu_state)->input & 0x10) && g_chapter_route_sel != 0xFF) {
            g_game_mode = 7;
            g_menu_fade_callback = (s32 *) chapter_scene_start;
            g_menu_fade_speed = 3;
            sfx = 0x500;
        }
    }
    if (sfx != 0) {
        sound_play_2d(sfx, 0x4650, 0x40, 0, 0);
    }
}

extern u8 g_str_slot_score_fmt[]; /* "%d"; was D_800ABC10 */
extern u8 g_str_slot_time_fmt[]; /* "%d:%02d:%02d"; was D_800ABC14 */
extern u8 g_str_slot_title[]; /* "#": text id; was D_800ABC24 */
extern u8 g_str_slot_continue[]; /* was D_800ABC28 */
extern u8 g_str_slot_erase_ask[]; /* was D_800ABC2C */
extern u8 g_str_slot_start[]; /* was D_800ABC30 */
extern u8 g_str_slot_erase[]; /* was D_800ABC34 */
extern u8 g_str_slot_yes[]; /* was D_800ABC38 */
extern u8 g_str_slot_no[]; /* was D_800ABC3C */
extern s32 g_save_stat9; /* was D_800BE804 */
extern s32 *g_menu_fade_callback; /* was D_800E0EB8 */
void slot_game_start(void);
void text_printf(s32, ...);

// title_slot_page: title menu pages 3..5 = save slot 0..2 (rec->titlePage - 3). Draws the slot in its colour (slot 2
// red, 1 green, 0 blue) with its score ("%d"; 0x7D00 is shown as 1000000 at 0.75 scale) and play time (h:mm:ss), then
// the options: a used slot offers continue / erase (g_menu_cursor 0 / 1, left-right toggles), erase asks no / yes
// (g_menu_cursor 2 / 3); an empty slot (+8 == -1) only offers "start" (text 0x31). Accept on 0 starts the game: mode 7
// (fade) with the callback slot_game_start, g_save_cur_slot = slot, save_request_slot_load(slot +0xE); accept on "yes" erases the slot
// (save_request_slot_erase, level_state_clear, slot marked empty, g_menu_setup_step = 0 re-runs the menu setup). Plays sound 0x62D on a
// move, 0x500 on accept.
/* was func_151E06D0 */
void title_slot_page(void) {
    MenuState *rec;
    SaveSlotSummary *save;
    u8 alpha;
    s32 slot;
    s32 sfx;
    s32 sel;
    u32 v;
    s32 y;
    u16 in;
#ifdef PORT
    /* DELIBERATE PORT CHANGE (P364, native menus; docs/design/NATIVE_MENUS.md): a CUSTOMISATION SETTINGS row (P369; was "OPTIONS") on this save slot page
     * that opens the page's game-style menu (port/web/gmenu.js), like the pause menu's row (P363, game_pause_update).
     * Shown only while port_gmenu_row_shown() (always while the game is local (P369: no page option any more): never
     * online, in a recording / replay or under ?netdet, where this menu's state is hashed) and not during the erase
     * question (g_menu_cursor 2 / 3); otherwise every line below runs exactly as on the N64. It sits under the slot's
     * items (empty slot: under NEW GAME; used slot: under CONTINUE / ERASE), centred, in the item pictures' greens.
     * Stick down reaches it, stick up goes back to the item it came from (g_menu_cursor keeps it, but no item is lit
     * meanwhile); left / right do nothing there. A or START on it plays the choose sound (0x500), asks the page to open
     * its menu (port_gmenu_request_title) and is taken out of this frame's menu input, so it neither starts the game
     * nor reaches the menu camera. The title keeps running underneath (the page gives the game an idle pad 1), so
     * closing that menu comes back here with OPTIONS still selected. B zooms out as from any item. The selection is
     * forgotten whenever the page is not fully shown (g_menu_alpha < 0xFF: zooming in or out), so every visit starts on
     * the game's own item. port_slot_on_options = OPTIONS is selected (a port variable, outside game memory). */
    static s32 port_slot_on_options;
    s32 optionsRow;   /* the OPTIONS row is shown this frame */
    void port_menu_customisation_row_draw(s32 selected, s32 centreX, s32 y, s32 alpha); /* was port_menu_options_row_draw */
#endif

    alpha = g_menu_alpha;
    rec = (MenuState *) g_menu_state;
    sfx = 0;
    slot = rec->titlePage - 3;
    sel = (s8) g_menu_cursor;
#ifdef PORT
    optionsRow = sel < 2 && port_gmenu_row_shown();
    if (!optionsRow || alpha != 0xFF) {
        port_slot_on_options = 0;
    }
    if (optionsRow && alpha == 0xFF && (rec->input & (port_slot_on_options ? 1 : 2))) {
        port_slot_on_options = !port_slot_on_options;   /* stick down to OPTIONS, stick up back to the item */
        sfx = 0x62D;
    } else if (port_slot_on_options) {
        /* on OPTIONS left / right do nothing */
    } else
#endif
    if (sel < 2) {
        if (rec->input & 0xC) {
            g_menu_cursor = 1 - sel;
            sfx = 0x62D;
        }
    } else if (rec->input & 0xC) {
        g_menu_cursor = 5 - sel;
        sfx = 0x62D;
    }
    text_set_pos(0x94, 0x46);
    save = &g_save_slot_summaries[slot];
    if (save->stamp == -1) {
        g_menu_cursor = 0;
    }
    if (slot == 2) {
        text_set_color(0xFF, 0x37, 0x37, alpha);
    } else if (slot == 1) {
        text_set_color(0x78, 0xFF, 0x16, alpha);
    } else {
        text_set_color(0x20, 0x55, 0xFF, alpha);
    }
    if (save->stamp != -1) {
        v = save->score;
        y = 0;
        if (v == 0x7D00) {
            v = 1000000;
            text_set_scale(0.75f);
            y = 2;
        }
        text_printf_at(0x70, y + 0x33, 0, (s32) g_str_slot_score_fmt, v);
        text_set_scale(1.0f);
        v = save->playTime;
        text_printf_at(0xA4, 0x33, 0, (s32) g_str_slot_time_fmt, v / 60 / 60, v / 60 % 60, v % 60);
    }
    text_set_color(0xFF, 0xFF, 0xFF, alpha);
    if (save->stamp >= 0) {
        text_printf_at(0x94, 0xAF, 1, (s32) g_str_slot_title, 0x1A);
        text_set_pos(0x58, 0xAF);
        sel = (s8) g_menu_cursor;
        if (sel < 2) {
#ifdef PORT
            text_printf((s32) g_str_slot_continue, (sel == 0 && !port_slot_on_options) + 0x16, 1);   /* unlit on OPTIONS */
#else
            text_printf((s32) g_str_slot_continue, (sel == 0) + 0x16, 1);
#endif
        } else {
            text_printf_at(0x94, 0x91, 1, (s32) g_str_slot_erase_ask, 0x19);
        }
    } else {
#ifdef PORT
        if (port_slot_on_options) {
            text_set_color(0xFF, 0xFF, 0xFF, alpha >> 1);   /* NEW GAME has no dark picture: half faded while OPTIONS is selected */
        }
#endif
        text_printf_at(0x94, 0x6E, 1, (s32) g_str_slot_start, 0x31);
    }
#ifdef PORT
    if (optionsRow) {
        /* centred on the page (NEW GAME's picture and the joystick between PLAY / ERASE are centred at 162), under NEW
         * GAME (its picture reaches about y 137) / under PLAY / ERASE (they reach about 210) */
        port_menu_customisation_row_draw(port_slot_on_options, 162, save->stamp >= 0 ? 0xD4 : 0x8E, alpha);
    }
    if (port_slot_on_options && (rec->input & 0x10)) {
        port_gmenu_request_title();   /* A / START on OPTIONS: the page opens its menu over the title */
        sfx = 0x500;
        ((MenuState *) g_menu_state)->input &= ~0x10;
    }
#endif
    text_set_pos(0xD0, 0xAF);
    sel = (s8) g_menu_cursor;
    if (sel < 2) {
        if (save->stamp >= 0) {
#ifdef PORT
            text_printf((s32) g_str_slot_erase, (sel != 0 && !port_slot_on_options) + 0x18, 1);   /* unlit on OPTIONS */
#else
            text_printf((s32) g_str_slot_erase, (sel != 0) + 0x18, 1);
#endif
            sel = (s8) g_menu_cursor;
        }
        if (sel == 0) {
            if (((MenuState *) g_menu_state)->input & 0x10) {
                g_game_mode = 7;
                g_menu_fade_callback = (s32 *) slot_game_start;
                g_menu_fade_speed = 3;
                g_save_cur_slot = slot;
                g_save_best_slot_score = -1;
                g_save_slot_refresh = 0;
                save_request_slot_load(save->eepArea);
                sfx = 0x500;
            }
        } else if (((MenuState *) g_menu_state)->input & 0x10) {
            g_menu_cursor = 2;
            sfx = 0x500;
        }
    } else {
        text_printf_at(0x6C, 0xAF, 1, (s32) g_str_slot_yes, (sel == 3) + 0x1F);
        text_printf_at(0xBC, 0xAF, 1, (s32) g_str_slot_no, ((s8) g_menu_cursor == 2) + 0x1D);
        rec = (MenuState *) g_menu_state;
        in = rec->input;
        if (in & 0x10) {
            if ((s8) g_menu_cursor == 3) {
                g_menu_cursor = 0;
                save_request_slot_erase(slot);
                g_save_resume_level = 0x29;
                g_save_restart_entry = 0;
                g_save_stat9 = 0;
                level_state_clear();
                save->resumeLevel = 0x18;
                save->score = 0;
                save->stamp = -1;
                rec = (MenuState *) g_menu_state;
                g_menu_setup_step = 0;
            } else {
                g_menu_cursor = 1;
            }
            sfx = 0x500;
        } else if (in & 0x20) {
            g_menu_cursor = 1;
        }
        rec->input &= ~0x20;
    }
    if (sfx != 0) {
        sound_play_2d(sfx, 0x4650, 0x40, 0, 0);
    }
}

void settings_load_from_save(void);
extern s8 g_menu_team_size_shift; /* was D_80090164 */
extern s8 g_settings_changed; /* was D_80090180 */
extern s8 g_menu_extra_slots; /* was D_80090140 */
extern u8 g_menu_chars_changeable; /* was D_800E0FBC */
extern s8 g_menu_modes[][10]; /* was D_800ABA70 */
extern s8 g_menu_group_mode_counts[];         /* main menu: items per page group (titlePage 1..); was D_80090248 */
extern s8 g_menu_mode_fixed_chars[];         /* s8 per 4 bytes: setting for the negative mode codes; was D_80090270 */
extern s8 g_menu_player_chars[]; /* was D_800E0FC0 */
extern u8 g_str_modes_title[];         /* "#": text id; was D_800ABC40 */
extern u8 g_str_modes_choice[]; /* was D_800ABC44 */
extern u8 g_str_modes_row[]; /* was D_800ABC48 */
// menu_mode_select_page: main menu page 0, the mode list of the page group rec->titlePage (g_menu_group_mode_counts[group - 1]
// rows of g_menu_modes starting after the earlier groups). The page alpha g_menu_page_alpha fades in (8 per frame step) or,
// with a pending page change g_menu_pending_page, out; at 0 the page switches (mainPage = g_menu_pending_page, page 2 resets
// g_settings_changed / g_menu_stick_x_held / g_settings_sel, settings_load_from_save) and returns. Left / right toggles the yes / no cursor
// g_menu_cursor; up / down moves the row x41 (wrapping, sound 0x62D; a 5-row group slides with g_menu_slide_phase instead of
// drawing the rows). x42 = global row. Accept: on "yes" saves x41 in g_settings[0], g_menu_player_chars from the row's mode
// code (g_menu_mode_fixed_chars for codes < 0), g_menu_joined_count = 1, page change 4; on "no" page change 2.
/* was func_151E0BBC */
void menu_mode_select_page(void) {
    MenuState *rec;
    s32 alpha;
    s32 textAlpha;
    s32 v;
    s32 n;
    s32 row;
    s32 first;
    s32 i;
    s16 x;
    s16 id;
    s8 *tab;
    f32 step;
    s8 code;
    s32 setupLit;   /* SET-UP is drawn lit when selected (P364: 0 while the port's OPTIONS row is selected) */
#ifdef PORT
    /* DELIBERATE PORT CHANGE (P364, native menus; docs/design/NATIVE_MENUS.md): a CUSTOMISATION row (P369; was "OPTIONS") on this MULTI mode
     * page, under SET-UP (shown on the page whichever item is selected), that opens the page's game-style menu (port/web/gmenu.js), like the pause menu's row (P363) and
     * the save slot pages' (title_slot_page). Shown only while port_gmenu_row_shown() (always while the game is local (P369: no page option any more): never online, in a recording / replay or under ?netdet, where this menu's state is
     * hashed; the page also switches it off as soon as an online session is being set up); otherwise every line below
     * runs exactly as on the N64. Stick down from SET-UP (g_menu_cursor 1, where up / down did nothing) reaches it,
     * stick up goes back to SET-UP; left / right do nothing there. A or START on it plays the choose sound (0x500), asks
     * the page to open its menu (port_gmenu_request_title) and is taken out of this frame's menu input, so it does not
     * open SET-UP. The menu keeps running underneath (idle pad 1), so closing that menu comes back here with OPTIONS
     * still selected. B zooms out as from any item. The selection is forgotten whenever the page is not fully shown
     * (textAlpha < 0xFF: fading in or out). port_modes_on_options = OPTIONS is selected (a port variable, outside game
     * memory). */
    static s32 port_modes_on_options;
    s32 optionsRow;   /* the OPTIONS row is shown this frame */
    void port_menu_customisation_row_draw(s32 selected, s32 centreX, s32 y, s32 alpha); /* was port_menu_options_row_draw */
#endif

    rec = (MenuState *) g_menu_state;
    if (rec->titlePage == 0) {
        return;
    }
    alpha = g_menu_alpha;
    if ((s8) g_menu_pending_page != -1) {
        rec->input &= ~0x20;
        v = g_menu_page_alpha - (g_frame_ticks << 5);
        if (v <= 0) {
            g_menu_page_alpha = 0;
            ((MenuState *) g_menu_state)->mainPage = g_menu_pending_page;
            if ((s8) g_menu_pending_page == 2) {
                g_settings_changed = 0;
                g_menu_stick_x_held = 1;
                g_settings_sel = 0;
            }
            settings_load_from_save();
            g_menu_pending_page = -1;
            return;
        }
        g_menu_page_alpha = v;
        if ((s8) g_menu_pending_page != 2) {
            alpha = v & 0xFF;
        }
        textAlpha = v & 0xFF;
        rec = (MenuState *) g_menu_state;
    } else {
        v = g_menu_page_alpha + (g_frame_ticks << 5);
        if (v >= 0x100) {
            v = 0xFF;
        }
        g_menu_page_alpha = v;
        textAlpha = (s32) (g_menu_alpha * v) >> 8;
        if (textAlpha >= 0xFE) {
            textAlpha = 0xFF;
        }
    }
    g_menu_extra_slots = 0;
    g_menu_team_size_shift = 0;
    g_menu_chars_changeable = 0;
    n = g_menu_group_mode_counts[rec->titlePage - 1];
#ifdef PORT
    optionsRow = port_gmenu_row_shown();
    if (!optionsRow || textAlpha != 0xFF || (s8) g_menu_cursor != 1) {
        port_modes_on_options = 0;
    }
    if (optionsRow && textAlpha == 0xFF && (s8) g_menu_cursor == 1 && (rec->input & (port_modes_on_options ? 1 : 2))) {
        port_modes_on_options = !port_modes_on_options;   /* stick down from SET-UP to OPTIONS, stick up back */
        sound_play_2d(0x62D, 0x4650, 0x40, 0, 0);
    } else if (port_modes_on_options) {
        /* on OPTIONS left / right do nothing */
    } else
#endif
    if (rec->input & 0xC) {
        g_menu_cursor = 1 - (s8) g_menu_cursor;
        sound_play_2d(0x62D, 0x4650, 0x40, 0, 0);
    }
    setupLit = 1;
#ifdef PORT
    if (port_modes_on_options) {
        setupLit = 0;
    }
#endif
    text_set_color(0xFF, 0xFF, 0xFF, alpha);
    text_printf_at(0x94, 0x7E, 1, (s32) g_str_modes_title, 0x1A);
    text_set_color(0xFF, 0xFF, 0xFF, textAlpha);
    text_printf_at(0xD5, 0x7E, 1, (s32) g_str_modes_choice, ((s8) g_menu_cursor == 1 && setupLit) + 0x1B);
#ifdef PORT
    if (optionsRow) {
        /* under SET-UP (drawn from x 0xD5, its centre near 234; the picture reaches about y 155) */
        port_menu_customisation_row_draw(port_modes_on_options, 234, 0xA0, textAlpha);
    }
    if (port_modes_on_options && textAlpha == 0xFF && (((MenuState *) g_menu_state)->input & 0x10)) {
        port_gmenu_request_title();   /* A / START on OPTIONS: the page opens its menu over the title */
        sound_play_2d(0x500, 0x4650, 0x40, 0, 0);
        ((MenuState *) g_menu_state)->input &= ~0x10;
    }
#endif
    if (textAlpha == 0xFF && (s8) g_menu_cursor == 0 && (n != 5 || g_menu_slide_phase == 0.0f)) {
        rec = (MenuState *) g_menu_state;
        if (rec->input & 1) {
            g_menu_slide_phase = 1.0f;
            rec->x41--;
            sound_play_2d(0x62D, 0x4650, 0x40, 0, 0);
        } else if (rec->input & 2) {
            g_menu_slide_phase = -1.0f;
            rec->x41++;
            sound_play_2d(0x62D, 0x4650, 0x40, 0, 0);
        }
    }
    rec = (MenuState *) g_menu_state;
    if (rec->x41 < 0) {
        rec->x41 += n;
    }
    rec = (MenuState *) g_menu_state;
    if (rec->x41 >= n) {
        rec->x41 -= n;
    }
    rec = (MenuState *) g_menu_state;
    row = rec->x41;
    first = 0;
    for (i = 0; i < rec->titlePage - 1; i++) {
        first += g_menu_group_mode_counts[i];
    }
    rec->x42 = row + first;
    if (n != 5) {
        x = 0x8C - ((n * 0x1C) >> 1);
        tab = g_menu_modes[first];
        for (i = 0; i < n; i++) {
            text_set_pos(0x53, x);
            id = *(s16 *) tab;
            if (i == row && (s8) g_menu_cursor == 0) {
                id++;
            }
            text_printf((s32) g_str_modes_row, id);
            tab += 10;
            x += 0x1C;
        }
    } else {
        step = g_frame_ticks * 0.05f;
        if (g_menu_slide_phase < 0.0f) {
            g_menu_slide_phase += step;
            if (g_menu_slide_phase > 0.0f) {
                g_menu_slide_phase = 0.0f;
            }
        } else if (g_menu_slide_phase > 0.0f) {
            g_menu_slide_phase -= step;
            if (g_menu_slide_phase < 0.0f) {
                g_menu_slide_phase = 0.0f;
            }
        }
        if ((s8) g_menu_cursor == 0 && g_menu_slide_phase != 0.0f) {
            ((MenuState *) g_menu_state)->input &= ~0x10;
        }
    }
    if (textAlpha != 0xFF) {
        return;
    }
    rec = (MenuState *) g_menu_state;
    if (!(rec->input & 0x10)) {
        return;
    }
    rec->input &= ~0x20;
    if ((s8) g_menu_cursor == 0) {
        g_menu_pending_page = 4;
        rec = (MenuState *) g_menu_state;
        g_settings[0] = rec->x41;
        code = g_menu_modes[rec->x42][5];
        if (code < 0) {
            g_menu_player_chars[0] = g_menu_mode_fixed_chars[(-1 - code) * 4];
        } else {
            g_menu_player_chars[0] = 0;
        }
        g_menu_joined_count = 1;
    } else {
        g_menu_pending_page = 2;
        ((MenuState *) g_menu_state)->input &= ~0x20;
    }
}

void text_set_flags(u8);
void settings_save(void);
void settings_list_draw(s32, s32, s32, s32, s32);
extern s8 g_settings_changed; /* was D_80090180 */
extern s32 g_menu_modes_settings_set;            /* s8 table, per save slot (rows of 10): settings set (declared s32 in the TU); was D_800ABA74 */
extern s32 g_settings_set_item_masks[];        /* settings set -> item mask for settings_list_draw; was D_800ABB38 */
extern u8 g_str_settings_title[];         /* "#"; was D_800ABC4C */

// main_settings_page: main menu page 2, the settings list of the current slot (rec->x42): title text 0x1A, the ring
// list settings_list_draw with its own alpha g_menu_page_alpha (fades in by 32 per tick; back (0x20) starts the fade-out,
// g_menu_pending_page = 0). At the end of the fade-out it leaves the page (mainPage 0) and saves the settings (settings_save)
// when they changed (g_settings_changed).
/* was func_151E1174 */
void main_settings_page(void) {
    MenuState *rec;
    s32 mask;
    s32 alpha;

    text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
    text_printf_at(0x94, 0x7E, 1, (s32) g_str_settings_title, 0x1A);
    text_set_flags(0x81);
    rec = (MenuState *) g_menu_state;
    mask = g_settings_set_item_masks[((s8 *) &g_menu_modes_settings_set)[rec->x42 * 10]];
    if ((s8) g_menu_pending_page == 0) {
        rec->input &= ~0x20;
        alpha = g_menu_page_alpha - (g_frame_ticks << 5);
        if (alpha <= 0) {
            ((MenuState *) g_menu_state)->mainPage = 0;
            if (g_settings_changed != 0) {
                settings_save();
            }
            g_settings_changed = 0;
            g_menu_pending_page = -1;
            return;
        }
        g_menu_page_alpha = alpha;
    } else {
        alpha = g_menu_page_alpha + (g_frame_ticks << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        g_menu_page_alpha = alpha;
    }
    if (alpha != 0xFF) {
        ((MenuState *) g_menu_state)->input = 0;
    }
    settings_list_draw(mask, 1, 0, alpha & 0xFF, 0);
    rec = (MenuState *) g_menu_state;
    if (rec->input & 0x20) {
        g_menu_pending_page = 0;
    }
    rec->input &= ~0x20;
}
void obj_remove(struct127 *arg0, s32 arg1);
void menu_spawn_character(s32 slot, s32 character);
void text_printf_at(s32, s32, u8, s32, ...);
extern u8 g_menu_page_alpha;           /* page alpha; was D_800E0EC5 */
extern u8 g_menu_pending_page;           /* pending page (read signed, -1 = none); was D_800E0EC6 */
extern s32 g_menu_char_objs;          /* struct127 *[4]: character object per controller; was D_800E0FD0 */
extern s8 g_menu_modes[][10];     /* menu modes (rows of 10, by MenuState x42); was D_800ABA70 */
extern s32 g_cheat_flags;          /* cheat / unlock flags; was D_800E9D00 */
extern s8 g_menu_mode_fixed_chars[];         /* s8 per 4 bytes: setting for the negative mode codes; was D_80090270 */
extern s32 g_menu_mode_char_masks[];        /* character mask per negative mode code; was D_80090250 */
extern u8 g_menu_chars_changeable;           /* characters can be changed this frame; was D_800E0FBC */
extern u8 g_str_join_title[];         /* page label; was D_800ABC50 */
extern s8 g_menu_player_chars[];         /* character per joined player; was D_800E0FC0 */
extern s8 g_menu_player_queue;           /* first of the 16-byte player queue (controller numbers, sorted, -1 = free); was D_800901E4 */
extern s8 g_menu_joined_count;           /* joined players; was D_800901E0 */
extern u16 g_cont_pressed;          /* new button presses per controller (u16 each); was D_800BED50 */
extern s8 g_mp_player_team[];         /* player -> slot; was D_800E1030 */
extern s8 g_menu_fade_speed; /* was D_80090114 */
extern u8 g_menu_cursor; /* was D_800901CC */
extern s8 g_settings_defaults[];         /* end of the player queue; was D_800901F4 */

// menu_player_join_page: the multiplayer character page. Fades in (alpha g_menu_page_alpha += 32 per tick) or, with a
// pending page in g_menu_pending_page, fades out, then switches the main page and frees the four character objects.
// Controllers 1..3 (only 1 on title page 7) join / leave with START: the queue g_menu_player_queue (sorted controller numbers,
// count g_menu_joined_count) and the players' characters g_menu_player_chars (the mode's fixed character g_menu_mode_fixed_chars[code][controller],
// else the controller number). In a mode with a character mask (negative code at +5 of the mode row; cheat flags add
// characters) controller 0's character is spawned and right / left cycle each player's character over the 22
// characters allowed by the mask, respawning the object (menu_spawn_character) when it changed or a joined slot had one.
// Accept goes to page 5 (mask modes) or 1, back to page 0.
/* was func_151E1308 */
void menu_player_join_page(void) {
    MenuState *rec;
    s8 *queue = &g_menu_player_queue;
    s32 alpha;
    s32 mask = -1;
    s8 *fixed = NULL;
    s8 respawn = 0;
    s8 maxPlayers;
    s32 nextPage;
    s32 code;
    s32 i;
    s32 j;
    s32 count;
    s32 found;
    s32 pad;
    s32 old;
    s32 ch;
    s32 dir;
    struct127 **obj;

    if ((s8) g_menu_pending_page != -1) {
        ((MenuState *) g_menu_state)->input &= ~0x20;
        alpha = g_menu_page_alpha - (g_frame_ticks << 5);
        if (alpha <= 0) {
            g_menu_page_alpha = 0;
            ((MenuState *) g_menu_state)->mainPage = g_menu_pending_page;
            g_menu_pending_page = -1;
            for (obj = (struct127 **) &g_menu_char_objs; obj != (struct127 **) &g_menu_char_objs + 4; obj++) {
                if (*obj != NULL) {
                    obj_remove(*obj, 1);
                    *obj = NULL;
                }
            }
            return;
        }
        g_menu_page_alpha = alpha;
    } else {
        alpha = g_menu_page_alpha + (g_frame_ticks << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        g_menu_page_alpha = alpha;
    }
    text_set_color(0xFF, 0xFF, 0xFF, alpha & 0xFF);
    rec = (MenuState *) g_menu_state;
    code = g_menu_modes[rec->x42][5];
    if (code < 0) {
        nextPage = 5;
        fixed = &g_menu_mode_fixed_chars[(-1 - code) * 4];
        mask = g_menu_mode_char_masks[-1 - code];
        if (g_cheat_flags & 0x20) {
            mask |= 0x8000;
        }
        if (g_cheat_flags & 0x10) {
            mask |= 0x10000;
        }
        if (g_cheat_flags & 0x40) {
            mask |= 0x30;
        }
        if (g_cheat_flags & 0x80) {
            mask |= 0x43C0;
        }
        if (g_cheat_flags & 0x100) {
            mask |= 0xE0800;
        }
        if (g_cheat_flags & 0x10000) {
            mask |= 0xA;
        }
        if (g_cheat_flags & 0x20000) {
            mask |= 0x300000;
        }
    } else {
        nextPage = 1;
    }
    if (rec->titlePage == 7) {
        maxPlayers = 2;
    } else {
        maxPlayers = 4;
    }
    g_menu_chars_changeable = 0;
    if (nextPage == 5 && g_menu_modes[rec->x42][8] != 8) {
        if (*(struct127 **) &g_menu_char_objs == NULL) {
            menu_spawn_character(0, g_menu_player_chars[0]);
        }
        text_printf_at(0x94, 0x9B, 1, (s32) g_str_join_title, 0x1A);
        g_menu_chars_changeable = 1;
        rec = (MenuState *) g_menu_state;
    }

    /* START on controllers 1.. joins or leaves */
    for (pad = 1; pad < 4; pad++) {
        if (pad < maxPlayers && alpha == 0xFF && ((&g_cont_pressed)[pad] & 0x1000)) {
            count = g_menu_joined_count;
            found = 0;
            for (i = 0; i < count; i++) {
                if (pad == queue[i]) {
                    g_menu_joined_count = count - 1;
                    count = g_menu_joined_count;
                    found = 1;
                    for (j = i; j < count; j++) {
                        queue[j] = queue[j + 1];
                        g_menu_player_chars[j] = g_menu_player_chars[j + 1];
                    }
                }
            }
            if (!found) {
                obj = (struct127 **) &g_menu_char_objs + pad;
                for (i = 0; i < count && queue[i] < pad; i++) {
                }
                for (j = count; j > i; j--) {
                    queue[j] = queue[j - 1];
                    g_menu_player_chars[j] = g_menu_player_chars[j - 1];
                }
                queue[i] = pad;
                if (fixed != NULL) {
                    g_menu_player_chars[i] = fixed[pad];
                } else {
                    g_menu_player_chars[i] = pad;
                }
                g_menu_joined_count = count + 1;
                if (*obj != NULL) {
                    respawn = 1;
                }
            }
        }
    }

    /* character choice per joined player */
    count = g_menu_joined_count;
    for (i = 0; i < count; i++) {
        g_mp_player_team[i] = i;
        if (g_menu_chars_changeable == 0) {
            continue;
        }
        pad = queue[i];
        old = ch = g_menu_player_chars[i];
        dir = 1;
        if (rec->padInput[pad] & 8) {
            g_menu_player_chars[i] = ch + 1;
            ch = g_menu_player_chars[i];
            if (ch >= 0x16) {
                g_menu_player_chars[i] = 0;
                ch = g_menu_player_chars[i];
            }
        }
        if (rec->padInput[pad] & 4) {
            g_menu_player_chars[i] = ch - 1;
            ch = g_menu_player_chars[i];
            dir = -1;
            if (ch < 0) {
                g_menu_player_chars[i] = 0x15;
                ch = g_menu_player_chars[i];
            }
        }
        while (!((1 << ch) & mask)) {
            g_menu_player_chars[i] = ch + dir;
            ch = g_menu_player_chars[i];
            if (ch < 0) {
                g_menu_player_chars[i] = 0x15;
                ch = g_menu_player_chars[i];
            }
            if (ch >= 0x16) {
                g_menu_player_chars[i] = 0;
                ch = g_menu_player_chars[i];
            }
        }
        if (old != ch || respawn != 0) {
            menu_spawn_character(pad, ch);
            count = g_menu_joined_count;
            rec = (MenuState *) g_menu_state;
        }
    }
    for (i = count; i < 0x10; i++) {
        queue[i] = -1;
    }

    if (alpha == 0xFF) {
        if (rec->input & 0x10) {
            g_menu_fade_speed = 8;
            sound_play_2d(0x500, 0x7D00, 0x40, 0, 0);
            g_menu_pending_page = nextPage;
            rec = (MenuState *) g_menu_state;
        }
        if (rec->input & 0x20) {
            g_menu_pending_page = 0;
            g_menu_cursor = 0;
        }
    }
    rec->input &= ~0x20;
}

void text_printf(s32, ...);
void menu_game_start(void);
void mp_start_intro_scene(void);
extern s8 g_menu_extra_slots;           /* first queue slot shown / number of extra slots; was D_80090140 */
extern s8 g_menu_mode_slot_rows;           /* (s8 table, indexed backwards by the slot's mode); was D_8009028F */
extern s8 g_menu_modes_code;           /* s8 table, per save slot (rows of 10): byte 1; was D_800ABA75 */
extern u8 g_menu_modes_intro[][10]; /* was D_800ABA76 */
extern s8 g_menu_max_slots;           /* rows of 4 bytes: max players per player count; was D_800ABB30 */
extern s32 *g_menu_fade_callback;         /* callback run when the menu fade-out ends; was D_800E0EB8 */
extern u8 g_str_players_title[];         /* "#"; was D_800ABC54 */
extern u8 g_str_players_slot[];         /* "#"; was D_800ABC58 */
extern u8 g_str_players_open[];         /* "#"; was D_800ABC5C */

// main_players_page: main menu page 5, the player / controller queue (g_menu_player_queue[16], g_menu_joined_count controllers joined).
// Fades the page alpha g_menu_page_alpha in (32 per tick) or, while g_menu_pending_page != -1, out and then switches to mainPage =
// g_menu_pending_page. Each joined controller's up / right (9) adds and down / left (6) removes a slot (g_menu_extra_slots, with a
// click sound), limited by the slot table g_menu_max_slots; slots after the controllers are -2 ("open") and the rest of the
// queue -1. Accept at full alpha starts the game (mode 7 fade, g_menu_fade_speed = 8, callback menu_game_start or
// mp_start_intro_scene); back fades out to page 4. Draws the title text 0x1A and one entry per slot (controller n + 1 or
// text 5).
/* was func_151E19AC */
void main_players_page(void) {
    MenuState *rec;
    s32 alpha;
    s32 joined;
    s32 slots;
    s32 i;
    s16 x;

    if ((s8) g_menu_pending_page != -1) {
        rec = (MenuState *) g_menu_state;
        rec->input &= ~0x20;
        alpha = g_menu_page_alpha - (g_frame_ticks << 5);
        if (alpha <= 0) {
            g_menu_page_alpha = 0;
            ((MenuState *) g_menu_state)->mainPage = g_menu_pending_page;
            g_menu_pending_page = -1;
            return;
        }
        g_menu_page_alpha = alpha;
    } else {
        alpha = g_menu_page_alpha + (g_frame_ticks << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        g_menu_page_alpha = alpha;
    }
    text_set_color(0xFF, 0xFF, 0xFF, alpha & 0xFF);

    joined = g_menu_joined_count;
    rec = (MenuState *) g_menu_state;
    slots = ((s8 *) &g_menu_max_slots)[(&g_menu_mode_slot_rows)[-(&g_menu_modes_code)[rec->x42 * 10]] * 4 + joined - 1];
    for (i = 0; i < joined; i++) {
        if ((&g_menu_player_queue)[i] >= 0) {
            if (((MenuState *) g_menu_state)->padInput[(&g_menu_player_queue)[i]] & 9) {
                g_menu_extra_slots++;
                if (slots >= joined + g_menu_extra_slots) {
                    sound_play_2d(0x4FF, 0x4650, 0x40, 0, 0);
                }
            }
            if (((MenuState *) g_menu_state)->padInput[(&g_menu_player_queue)[i]] & 6) {
                g_menu_extra_slots--;
                if (g_menu_extra_slots >= 0) {
                    sound_play_2d(0x4FF, 0x4650, 0x40, 0, 0);
                }
            }
            joined = g_menu_joined_count;
            if (g_menu_extra_slots < 0) {
                g_menu_extra_slots = 0;
            }
        }
    }
    if (slots < joined + g_menu_extra_slots) {
        g_menu_extra_slots = slots - joined;
    }
    slots = joined + g_menu_extra_slots;
    if (slots < 2) {
        slots = 2;
    }
    g_menu_extra_slots = slots - joined;
    for (i = joined; i < slots; i++) {
        (&g_menu_player_queue)[i] = -2;
        g_mp_player_team[i] = 0;
    }
    for (i = slots; i < 0x10; i++) {
        (&g_menu_player_queue)[i] = -1;
    }

    if (alpha == 0xFF && (((MenuState *) g_menu_state)->input & 0x10)) {
        g_game_mode = 7;
        g_menu_fade_speed = 8;
        sound_play_2d(0x500, 0x7D00, 0x40, 0, 0);
        if ((s8) g_menu_modes_intro[((MenuState *) g_menu_state)->x42][0] == -1) {
            g_menu_fade_callback = (s32 *) menu_game_start;
        } else {
            g_menu_fade_callback = (s32 *) mp_start_intro_scene;
        }
    }
    text_printf_at(0x94, 0x55, 1, (s32) g_str_players_title, 0x1A);
    x = 0xA1 - g_menu_joined_count * 13 - g_menu_extra_slots * 10;
    for (i = 0; i < slots; i++) {
        text_set_pos(x, 0x82);
        if ((&g_menu_player_queue)[i] >= 0) {
            text_printf((s32) g_str_players_slot, (&g_menu_player_queue)[i] + 1);
            x += 0x1A;
        } else {
            text_printf((s32) g_str_players_open, 5);
            x += 0x14;
        }
    }
    if (alpha == 0xFF && (((MenuState *) g_menu_state)->input & 0x20)) {
        g_menu_pending_page = 4;
    }
    ((MenuState *) g_menu_state)->input &= ~0x20;
}
extern s8 D_eu_800902E4[4];     /* initial column offsets of the 4 team columns */
extern s8 g_mp_team_layouts[][12]; /* was D_800ABAF4 */ /* team layout per menu entry: count, min / max / per-team size (< 3 players),
                                 * same for 3+ players, team 1 size, team colours [4] */
extern u8 g_mp_team_colors[][3];      /* team colour rgb; was D_800ABA0C */
extern s8 g_mp_team_count;           /* number of teams; was D_800E0FE0 */
extern s8 g_mp_team_size;           /* team size; was D_800E0FE1 */
extern s8 g_mp_team_color_ids[4];        /* team colour index; was D_800E0FF8 */
extern s8 g_menu_team_size_shift;           /* team 0 / 1 size shift (two teams); was D_80090164 */
extern u8 g_str_team_title[], g_str_team_name_4[], g_str_team_name_5[], g_str_team_name_7[], g_str_team_name_8[], g_str_team_name_9[], g_str_team_name_other[], /* was D_800ABC60; was D_800ABC64; was D_800ABC68; was D_800ABC6C; was D_800ABC70; was D_800ABC74; was D_800ABC78 */
    g_str_team_player[], g_str_team_score[], g_str_team_cpu[], g_str_team_shift_mid[], g_str_team_shift_left[], g_str_team_shift_right[];
s8 mp_slot_query(s32);
// menu_team_select_page: multiplayer team page (main page 1). Fades the page alpha g_menu_page_alpha (out to the pending
// page g_menu_pending_page). The menu entry's g_mp_team_layouts row gives the team count g_mp_team_count, the team colours, and the
// total min / max and per-team limits (by player count g_menu_joined_count). Each joined player (queue g_menu_player_queue) moves
// between teams with left / right (team index masked by count - 1, refused when the team is full) and changes the
// extra team size g_menu_extra_slots with up / down; the team size g_mp_team_size = largest team + extra, clamped so
// size * teams stays within min..max; team 1 may have a fixed size; with two teams C-left / C-right shift
// g_menu_team_size_shift sizes between them (not with 3+ players). Free places become computer players (queue -2). Draws the
// team headers in their colours and one line per player (number, score from mp_slot_query when it reports one,
// or the CPU label), alternating columns. A / Start: mode 7 with fade callback mp_start_intro_scene, B: page 4. Sfx 0x4FF
// on moves, 0x500 on accept.
/* was func_151E1EDC */
void menu_team_select_page(void) {
    MenuState *rec;
    s8 *row;
    s32 alpha;
    s32 sfx;
    s32 n;
    s32 i;
    s32 teams;
    s32 min, max, size;
    s32 old;
    s32 team;
    s32 total;
    s32 shift;
    s32 lim;
    s32 v;
    s16 step, x;
    s16 px;
    s16 py;
    s8 fixed1;
    /* as in the asm frame, want[] / maxIn[] / off[] and colY[] / colX[] are adjacent: a team index past the team
     * count (stale g_mp_player_team entries of removed players) reads the next array */
    s8 bytes[12];
    s16 cols[8];
    s8 *want = bytes;
    s8 *maxIn = bytes + 4;
    s8 *off = bytes + 8;
    s16 *colY = cols;
    s16 *colX = cols + 4;
    s8 members[8];
    s32 scores[8];
    s8 haveScores;
    u16 pad;

    *(s32 *) off = *(s32 *) D_eu_800902E4;
    sfx = 0;
    if ((s8) g_menu_pending_page != -1) {
        ((MenuState *) g_menu_state)->input &= ~0x20;
        alpha = g_menu_page_alpha - (g_frame_ticks << 5);
        if (alpha <= 0) {
            g_menu_page_alpha = 0;
            ((MenuState *) g_menu_state)->mainPage = g_menu_pending_page;
            g_menu_pending_page = -1;
            return;
        }
        g_menu_page_alpha = alpha;
    } else {
        alpha = g_menu_page_alpha + (g_frame_ticks << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        g_menu_page_alpha = alpha;
    }
    text_set_color(0xFF, 0xFF, 0xFF, alpha);
    rec = (MenuState *) g_menu_state;
    row = g_mp_team_layouts[(&g_menu_modes_code)[rec->x42 * 10]];
    g_mp_team_count = row[0];
    fixed1 = row[7];
    g_mp_team_color_ids[0] = row[8];
    g_mp_team_color_ids[1] = row[9];
    g_mp_team_color_ids[2] = row[10];
    g_mp_team_color_ids[3] = row[11];
    n = g_menu_joined_count;
    if (n < 3) {
        min = row[1];
        max = row[2];
        size = row[3];
    } else {
        min = row[4];
        max = row[5];
        size = row[6];
    }
    for (i = 0; i < 4; i++) {
        maxIn[i] = (i != 0 && fixed1 != 0) ? fixed1 : size;
    }
    teams = g_mp_team_count;
    for (i = 0; i < teams; i++) {
        members[i] = 0;
        colY[i] = 0x6E;
    }
    for (i = 0; i < n; i++) {
        members[g_mp_player_team[i]]++;
    }
    for (i = n; i < 16; i++) {
        (&g_menu_player_queue)[i] = -1;
    }
    for (i = 0; i < n; i++) {
        if ((&g_menu_player_queue)[i] < 0) {
            continue;
        }
        pad = rec->padInput[(&g_menu_player_queue)[i]];
        old = g_mp_player_team[i];
        if (pad & 0xF) {
            sfx = 0x4FF;
        }
        if (pad & 8) {
            g_mp_player_team[i]++;
        }
        if (pad & 4) {
            g_mp_player_team[i]--;
        }
        if (pad & 2) {
            g_menu_extra_slots++;
        }
        if (pad & 1) {
            g_menu_extra_slots--;
        }
        if (g_menu_extra_slots < 0) {
            g_menu_extra_slots = 0;
            sfx = 0;
        }
        g_mp_player_team[i] &= teams - 1;
        if (members[g_mp_player_team[i]] >= maxIn[g_mp_player_team[i]]) {
            g_mp_player_team[i] = old;
        }
        members[g_mp_player_team[i]]++;
        members[old]--;
    }
    g_mp_team_size = 1;
    for (i = 0; i < teams; i++) {
        if (g_mp_team_size < members[i]) {
            g_mp_team_size = members[i];
        }
    }
    g_mp_team_size += g_menu_extra_slots;
    while (g_mp_team_size * teams < min) {
        g_mp_team_size++;
        g_menu_extra_slots++;
    }
    while (max < g_mp_team_size * teams) {
        g_mp_team_size--;
        g_menu_extra_slots--;
        if (g_menu_extra_slots < 0) {
            g_menu_extra_slots = 0;
        }
    }
    if (fixed1 != 0 && g_mp_team_size == 1) {
        fixed1 = 1;
    }
    for (i = 0; i < 4; i++) {
        want[i] = (i == 1 && fixed1 != 0) ? fixed1 : g_mp_team_size;
    }
    if (teams == 2) {
        if (rec->input & 0x40) {
            g_menu_team_size_shift++;
        } else if (rec->input & 0x80) {
            g_menu_team_size_shift--;
        }
        if (n >= 3) {
            g_menu_team_size_shift = 0;
        }
        shift = g_mp_team_size;
        if (g_menu_team_size_shift < -shift) {
            g_menu_team_size_shift = -shift;
        } else if (shift < g_menu_team_size_shift) {
            g_menu_team_size_shift = shift;
        } else if (rec->input & 0xC0) {
            sfx = 0x4FF;
        }
        want[0] += g_menu_team_size_shift;
        want[1] -= g_menu_team_size_shift;
        for (i = 0; i < 2; i++) {
            lim = (i == 1 && fixed1 != 0) ? fixed1 : 8;
            if (want[i] <= 0) {
                want[i] = 1;
            }
            if (lim < want[i]) {
                want[i] = lim;
            }
        }
    }
    step = 0x128 / teams;
    x = step >> 1;
    total = (s16) n;
    for (i = 0; i < teams; i++) {
        colX[i] = x;
        x += step;
        while (members[i] < want[i]) {
            (&g_menu_player_queue)[total] = -2;
            g_mp_player_team[total] = i;
            members[i]++;
            total = (s16) (total + 1);
        }
    }
    if (alpha == 0xFF) {
        if (rec->input & 0x10) {
            g_game_mode = 7;
            g_menu_fade_callback = (s32 *) mp_start_intro_scene;
            g_menu_fade_speed = 8;
            sfx = 0x500;
        } else if (rec->input & 0x20) {
            g_menu_pending_page = 4;
        }
    }
    rec->input &= ~0x20;
    text_set_color(0xFF, 0xFF, 0, alpha);
    text_set_pos(0x94, (s16) ((g_mp_team_count == 4) * 32 + 0x78));
    text_printf((s32) g_str_team_title, 0x1A);
    for (i = 0; i < g_mp_team_count; i++) {
        text_set_color(g_mp_team_colors[g_mp_team_color_ids[i]][0], g_mp_team_colors[g_mp_team_color_ids[i]][1], g_mp_team_colors[g_mp_team_color_ids[i]][2], alpha);
        text_set_pos(colX[i], 0x50);
        v = g_mp_team_color_ids[i];
        if (v == 4) {
            text_printf((s32) g_str_team_name_4, 9);
        } else if (v == 5) {
            text_printf((s32) g_str_team_name_5, 8);
        } else if (v == 7) {
            text_printf((s32) g_str_team_name_7, 0xA);
        } else if (v == 8) {
            text_printf((s32) g_str_team_name_8, 0xB);
        } else if (v == 9) {
            text_printf((s32) g_str_team_name_9, 0x34);
        } else {
            text_printf((s32) g_str_team_name_other, v + (v < 4 ? 0x59 : 0x4C));
        }
    }
    haveScores = mp_slot_query((s32) scores);
    text_set_color(0xFF, 0xFF, 0xFF, alpha);
    for (i = 0; i < total; i++) {
        team = g_mp_player_team[i];
        if (total == g_mp_team_count) {
            off[team] = 0;
        }
        px = off[team] + colX[team];
        py = colY[team];
        off[team] = -off[team];
        if (off[team] < 0) {
            colY[team] = py + 0x18;
        }
        text_set_pos(px, py);
        if ((&g_menu_player_queue)[i] < 0) {
            text_printf((s32) g_str_team_cpu, 5);
        } else {
            text_printf((s32) g_str_team_player, (&g_menu_player_queue)[i] + 1);
            if (haveScores) {
                text_printf((s32) g_str_team_score, scores[i] + 1);
            }
        }
    }
    if (sfx != 0) {
        sound_play_2d(sfx, sfx == 0x4FF ? 0x4650 : 0x7D00, 0x40, 0, 0);
    }
    if (g_mp_team_count == 2) {
        text_printf_at(0x94, 0xB4, 0x81, (s32) g_str_team_shift_mid, 0x3A);
        text_printf_at(0x7B, 0xB4, 0x81, (s32) g_str_team_shift_left, 0x3B);
        text_printf_at(0xAD, 0xB4, 0x81, (s32) g_str_team_shift_right, 0x3C);
    }
}

void screen_fade_update(void);
void menu_level_start_page(void);

/* was func_151E2A1C */
void menu_run_level_start(void) {
    g_menu_scene_start_state = 3;
    screen_fade_update();
    menu_level_start_page();
    g_menu_scene_start_state = 0;
}

void settings_clamp_to_range(void); /* P85: takes no arguments (the asm reads none) */
extern s32 g_save_config_recs_ptr; /* was D_80082F4C */
extern s32 g_menu_modes_settings_set; /* was D_800ABA74 */

/* was func_151E2A54 */
void settings_load_from_save(void) {
    s8 temp_a1;
    u8 var_v1;
    u8 *temp_v0;

    temp_a1 = *(s8 *)((u8 *)&g_menu_modes_settings_set + *(s8 *)((u8 *)g_menu_state + 0x42) * 0xA);
    temp_v0 = (temp_a1 * 0xA) + g_save_config_recs_ptr;
    var_v1 = (*(u8 *)((u8 *)temp_v0 + 3));
    if ((s32) var_v1 >= 5) {
        (*(u8 *)((u8 *)temp_v0 + 3)) = 4U;
        var_v1 = 4 & 0xFF;
    }
    if ((s32) var_v1 < 0) {
        (*(u8 *)((u8 *)temp_v0 + 3)) = 0U;
    }
    if ((*(s8 *)((u8 *)temp_v0 + 1)) <= 0) {
        (*(s8 *)((u8 *)temp_v0 + 1)) = 1;
    }
    (*(s8 *)((u8 *)g_settings + 2)) = (*(s8 *)((u8 *)temp_v0 + 1));
    (*(s8 *)((u8 *)g_settings + 0xB)) = 0;
    (*(s8 *)((u8 *)g_settings + 3)) = (s8) (*(s8 *)((u8 *)temp_v0 + 2));
    (*(u8 *)((u8 *)g_settings + 0x10)) = (u8) (*(u8 *)((u8 *)temp_v0 + 3));
    (*(u8 *)((u8 *)g_settings + 0x11)) = (u8) (*(u8 *)((u8 *)temp_v0 + 4));
    if (temp_a1 == 0) {
        (*(u8 *)((u8 *)g_settings + 4)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 1 || temp_a1 == 2) {
        (*(u8 *)((u8 *)g_settings + 0xD)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
        (*(u8 *)((u8 *)g_settings + 0xE)) = (u8) (*(u8 *)((u8 *)temp_v0 + 6));
    } else if (temp_a1 == 7) {
        (*(u8 *)((u8 *)g_settings + 0x12)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 5) {
        (*(u8 *)((u8 *)g_settings + 0x11)) = 0U;
        (*(u8 *)((u8 *)g_settings + 0x12)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 8 || temp_a1 == 9) {
        (*(u8 *)((u8 *)g_settings + 7)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
        (*(u8 *)((u8 *)g_settings + 0x11)) = 1U;
        (*(s8 *)((u8 *)g_settings + 3)) = 2;
        (*(u8 *)((u8 *)g_settings + 0x13)) = (u8) (*(u8 *)((u8 *)temp_v0 + 6));
    }
    (*(u8 *)((u8 *)g_settings + 0x16)) = (u8) (*(u8 *)((u8 *)temp_v0 + 8));
    (*(u8 *)((u8 *)g_settings + 6)) = (u8) (*(u8 *)((u8 *)temp_v0 + 9));
    settings_clamp_to_range();
}
// settings_save: P127: the inverse of settings_load_from_save: copies the settings bytes g_settings into the 10-byte save
// record of the menu's settings set (g_menu_modes_settings_set row of the save slot x42; record g_save_config_recs_ptr + set * 10): byte 0
// cleared, 1..4 = settings 2, 3, 0x10, 0x11, the set-specific bytes 5 / 6 (set 0: 4; sets 1, 2: 0xD, 0xE; sets 5, 7:
// 0x12; sets 8, 9: 7, 0x13; others none), 8 = 0x16, 9 = 6, then writes the save (save_request_config_write).
/* was func_151E2B9C */
void settings_save(void) {
    s32 set;
    s8 *rec;

    set = ((s8 *) &g_menu_modes_settings_set)[((MenuState *) g_menu_state)->x42 * 10];
    rec = (s8 *) g_save_config_recs_ptr + set * 10;
    rec[0] = 0;
    rec[1] = g_settings[2];
    rec[2] = g_settings[3];
    rec[3] = g_settings[0x10];
    rec[4] = g_settings[0x11];
    switch (set) {
        case 0:
            rec[5] = g_settings[4];
            break;
        case 1:
        case 2:
            rec[5] = g_settings[0xD];
            rec[6] = g_settings[0xE];
            break;
        case 5:
        case 7:
            rec[5] = g_settings[0x12];
            break;
        case 8:
        case 9:
            rec[5] = g_settings[7];
            rec[6] = g_settings[0x13];
            break;
    }
    rec[8] = g_settings[0x16];
    rec[9] = g_settings[6];
    save_request_config_write();
}

extern s8 g_menu_player_queue; /* was D_800901E4 */
extern s32 g_menu_player_queue_4; /* was D_800901E8 */
extern s32 g_menu_modes_slot_type; /* was D_800ABA78 */
extern u8 g_cont_connected_mask; /* was D_800BEB60 */
extern s32 g_mp_pad_share_slot; /* was D_800E0FFE */
extern s8 g_settings_byte_e; /* was D_800E101E */

/* was func_151E2C88 */
s8 mp_slot_query(s32 arg0) {
    struct {
        s8 u28;
        u8 pad29[0x3];
        s8 u2C;
        u8 pad2D[0x3];
        s32 u30;
        u8 pad34[0xC];
    } sp;
    s32 temp_a1;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t5;
    s32 var_a2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a3;
    s32 var_a3_5;
    s8 *var_a2_2;
    s8 *var_a3_2;
    s8 *var_a3_3;
    s8 *var_t0;
    s8 *var_t0_2;
    s8 *var_t0_3;
    s8 *var_t0_4;
    s8 *var_t0_5;
    s8 *var_t0_6;
    s8 *var_t2;
    s8 *var_t2_2;
    s8 *var_t3;
    s8 *var_t3_2;
    s8 temp_a3;
    s8 temp_t6;
    s8 temp_t6_2;
    s8 temp_t9;
    s8 temp_t9_2;
    s8 var_a2_5;
    s8 var_a3_4;
    s8 var_v1;

    if (arg0 == 0) {
        (*(s8 *)((u8 *)(&g_mp_pad_share_slot) + 0)) = 0;
        (*(s8 *)((u8 *)(&g_mp_pad_share_slot) + 1)) = 0;
    }
    if (*((s8 *) &g_menu_modes_slot_type + (*(s8 *)((u8 *)g_menu_state + 0x42)) * 0xA) == 8) {
        var_a2 = 0;
        var_v1 = 0;
        var_t0 = &sp.u2C;
        if (g_settings_byte_e != 0) {
            do {
                var_t0 += 1;
                (*(s8 *)((u8 *)var_t0 + -1)) = 0;
            } while ((u32) var_t0 < (u32) &sp.u30);
            var_t0_2 = &g_menu_player_queue;
            do {
                temp_a3 = *var_t0_2;
                var_t0_2 += 1;
                if (temp_a3 >= 0) {
                    var_v1 += 1;
                    (&sp.u2C)[temp_a3] = 1;
                    var_a2 = (var_a2 | (1 << temp_a3)) & 0xFF;
                }
            } while ((u32) var_t0_2 < (u32) &g_menu_player_queue_4);
            if (var_v1 < 3) {
                var_a3 = 0;
                if (g_cont_connected_mask & ~var_a2 & 0xFF) {
                    var_a2_2 = &sp.u28;
                    do {
                        *var_a2_2 = 1;
                        if ((var_v1 == 1) && !(g_cont_connected_mask & (1 << var_a3))) {
                            *var_a2_2 = 0;
                        }
                        var_a3 += 1;
                        var_a2_2 += 1;
                    } while (var_a3 < 4);
                    var_a2_3 = 0;
                    if (arg0 == 0) {
                        temp_a1 = var_v1 * 2;
                        var_a2_4 = 0x10;
                        if (temp_a1 < 0x11) {
                            temp_t5 = -((0x11 - temp_a1) & 3);
                            if (temp_t5 != 0) {
                                temp_t1 = 0x10 - var_v1;
                                var_t2 = g_mp_player_team + 0x10;
                                var_t3 = &g_mp_player_team[temp_t1];
                                var_t0_3 = &(&g_menu_player_queue)[temp_t1];
                                var_a3_2 = &g_menu_player_queue + 0x10;
                                do {
                                    temp_t9 = *var_t0_3;
                                    temp_t6 = *var_t3;
                                    var_a2_4 -= 1;
                                    var_a3_2 -= 1;
                                    var_t0_3 -= 1;
                                    var_t2 -= 1;
                                    var_t3 -= 1;
                                    (*(s8 *)((u8 *)var_a3_2 + 1)) = temp_t9;
                                    (*(s8 *)((u8 *)var_t2 + 1)) = temp_t6;
                                } while ((temp_t5 + 0x10) != var_a2_4);
                                if ((var_a2_4 + 1) != temp_a1) {
                                    goto block_23;
                                }
                            } else {
block_23:
                                temp_t1_2 = var_a2_4 - var_v1;
                                var_t0_4 = &(&g_menu_player_queue)[temp_t1_2];
                                var_t3_2 = &g_mp_player_team[temp_t1_2];
                                var_a3_3 = &(&g_menu_player_queue)[var_a2_4];
                                var_t2_2 = &g_mp_player_team[var_a2_4];
                                do {
                                    var_t2_2 -= 4;
                                    *var_a3_3 = (*(s8 *)((u8 *)var_t0_4 + 0));
                                    (*(s8 *)((u8 *)var_t2_2 + 4)) = (s8) (*(s8 *)((u8 *)var_t3_2 + 0));
                                    var_a3_3 -= 4;
                                    (*(s8 *)((u8 *)var_t2_2 + 3)) = (s8) (*(s8 *)((u8 *)var_t3_2 + -1));
                                    (*(s8 *)((u8 *)var_a3_3 + 3)) = (s8) (*(s8 *)((u8 *)var_t0_4 + -1));
                                    temp_t6_2 = (*(s8 *)((u8 *)var_t0_4 + -2));
                                    var_t0_4 -= 4;
                                    (*(s8 *)((u8 *)var_a3_3 + 2)) = temp_t6_2;
                                    (*(s8 *)((u8 *)var_t2_2 + 2)) = (s8) (*(s8 *)((u8 *)var_t3_2 + -2));
                                    temp_t9_2 = (*(s8 *)((u8 *)var_t3_2 + -3));
                                    var_t3_2 -= 4;
                                    (*(s8 *)((u8 *)var_t2_2 + 1)) = temp_t9_2;
                                    (*(s8 *)((u8 *)var_a3_3 + 1)) = (s8) (*(s8 *)((u8 *)var_t0_4 + 1));
                                } while (var_t2_2 != (temp_a1 - 1 + g_mp_player_team));
                            }
                        }
                        var_a2_5 = var_v1;
                        var_a3_4 = 0;
                        if (var_v1 < temp_a1) {
                            var_t0_5 = &sp.u2C;
loop_27:
                            if (*var_t0_5 == 0) {
                                temp_t1_3 = var_a2_5 - var_v1;
                                if ((&sp.u28)[var_a3_4] != 0) {
                                    (&g_menu_player_queue)[var_a2_5] = var_a3_4;
                                    g_mp_player_team[var_a2_5] = g_mp_player_team[temp_t1_3];
                                    *(&g_mp_pad_share_slot + temp_t1_3) = var_a2_5;
                                    g_player_start_state[var_a2_5] = 0xA;
                                    var_a2_5 += 1;
                                }
                            }
                            var_a3_4 += 1;
                            var_t0_5 += 1;
                            if (var_a3_4 < 4) {
                                if (var_a2_5 >= temp_a1) {
                                    return var_v1;
                                }
                                goto loop_27;
                            }
                            goto block_40;
                        }
                        goto block_40;
                    }
                    var_a3_5 = 0;
                    if (var_v1 > 0) {
                        var_t0_6 = &sp.u2C;
loop_35:
                        if ((*var_t0_6 == 0) && ((&sp.u28)[var_a3_5] != 0)) {
                            *(s32 *)(arg0 + (var_a2_3 * 4)) = var_a3_5;
                            var_a2_3 += 1;
                        }
                        var_a3_5 += 1;
                        var_t0_6 += 1;
                        if ((var_a3_5 < 4) && (var_a2_3 < var_v1)) {
                            goto loop_35;
                        }
                    }
block_40:
                    return var_v1;
                }
            }
            goto block_41;
        }
    }
block_41:
    return 0;
}
extern s8 g_menu_modes[][10];     /* menu modes (rows of 10, by MenuState x42); was D_800ABA70 */
extern u16 g_mp_hud_flags; /* was D_80090160 */
extern s16 g_mp_game_flags; /* was D_8009015C */
extern s8 g_rail_mirrored; /* was D_800D27C8 */
extern s32 g_settings_set_item_masks[]; /* was D_800ABB38 */
extern u8 g_level_zoom_in_request; /* was D_800E0FC9 */
extern s8 g_humans_alive; /* was D_80090134 */
extern s8 g_players_alive; /* was D_800BEA38 */
extern u8 g_chapter_replay; /* was D_800D3260 */
extern s8 g_menu_queue_drop_count; /* was D_80090110 */
extern s8 g_menu_player_queue;           /* first of the 16-byte player queue; was D_800901E4 */
extern s32 g_save_stat9; /* was D_800BE804 */
s8 mp_slot_query(s32);
void menu_settings_apply_checked(void);
void game_request_transition(s32, s32, s32, s32, s32);
extern s8 g_pause_drop_queue;            /* set: drop the first g_menu_queue_drop_count queue entries on the next start; was D_80090110; was D_8009013C */
extern s32 g_mp_time_left;           /* time limit (settings byte 3 * 3000) or 0; was D_80090118 */
extern s8 g_race_difficulty; /* was D_800E1000 */
extern s8 g_spawn_ctl_19a_init; /* was D_800D2550 */
extern s8 g_mp_team_mark_count; /* was D_80087608 */
extern s8 g_menu_queue_count;            /* player count (queue entries); was D_80090128 */
extern u8 g_menu_chars_changeable; /* was D_800E0FBC */
extern s8 g_menu_player_chars[]; /* was D_800E0FC0 */
extern u8 g_menu_characters[][8]; /* was D_800AB95C */
extern u8 g_mp_human_teams; /* was D_800E0ED8 */
extern u8 g_mp_last_hitter[]; /* was D_800E0FE8 */
extern s8 g_mp_match_eda; /* was D_800E0EDA */
extern s8 g_mp_next_placing; /* was D_800E0ED9 */
extern s8 g_mp_fixed_placings[16]; /* was D_800E0EE0 */
extern s8 g_mp_placings[16]; /* was D_800E0EF0 */
extern u8 g_mp_hits_taken[]; /* was D_800E0F00 */
extern s16 g_mp_result_time_b[2]; /* was D_800E1040 */
extern s32 g_mp_result_time_a[2]; /* was D_800E1048 */
extern s16 g_mp_team_scores[2]; /* was D_800E0ED0 */
extern s8 g_mp_match_over; /* was D_800E1050 */
extern s8 g_mp_p0_start_state; /* was D_8009011C */
extern s8 g_mp_transition_arg[];          /* player count -> argument of game_request_transition; was D_800902E7 */
extern s16 g_mp_set_hud_flags[];         /* settings set -> g_mp_hud_flags flags; was D_800ABB60; was D_80090160 */
extern s16 g_mp_set_game_flags[];         /* settings set -> g_mp_game_flags flags; was D_8009015C; was D_800ABB74 */

// menu_game_start: P127: start callback of the main menu: applies the settings of the chosen mode (g_menu_modes row
// x42: +2 level, +4 settings set, +5 < 0 = fill free slots, +8 slot type): drops the first g_menu_queue_drop_count entries of the
// player queue (g_menu_player_queue / g_mp_player_team) when g_pause_drop_queue asks for it, clears the menu / game state, sets the game
// flags g_mp_hud_flags / g_mp_game_flags from the set's tables and the settings bytes g_settings (time limit g_mp_time_left =
// byte 3 * 3000, g_rail_mirrored, g_race_difficulty, g_player_start_lives / g_mp_team_mark_count), counts the players (g_menu_queue_count, slot mask), fills
// the 16 slot types g_player_start_state (mode 8: mp_slot_query; else character records / per-mode rules), assigns free slot
// numbers when +5 < 0, resets g_mp_fixed_placings / g_mp_placings / g_mp_result_time_b.. and starts the game: game_request_transition(6, level, 0,
// g_mp_transition_arg[players], slot mask).
/* was func_151E2FCC */
void menu_game_start(void) {
    s8 *rec;
    s32 flags;
    s32 level;
    s32 mask;
    s32 n;
    s32 i;
    s32 used;
    s32 next;
    s8 *slot;

    rec = g_menu_modes[((MenuState *) g_menu_state)->x42];
    if (g_settings[3] < 3) {
        g_settings[3] = 0;
    }
    if (g_pause_drop_queue != 0) {
        n = g_menu_queue_drop_count;
        if (n != 0 && n < 16 - n) {
            for (i = n; i < 16 - n; i++) {
                (&g_menu_player_queue)[i] = (&g_menu_player_queue)[i + n];
                g_mp_player_team[i] = g_mp_player_team[i + n];
            }
        }
    }
    g_pause_drop_queue = 0;
    g_menu_queue_drop_count = 0;
    level_state_clear();
    g_save_stat9 = 0;
    bzero(g_menu_state + 0x66, 0x30);
    bzero(g_menu_state + 0x46, 0x20);
    bzero(g_mp_hits_taken, 0x20);
    g_pause_open = 0;
    g_game_paused = 0;
    g_game_mode = 0;
    g_save_cur_slot = -1;
    g_player_pad_map[1] = 0xFF;
    g_player_pad_map[2] = 0xFF;
    g_player_pad_map[3] = 0xFF;

    level = *(s16 *) (rec + 2);
    g_mp_free_for_all = rec[5] < 0;
    flags = g_settings_set_item_masks[rec[4]];
    g_mp_hud_flags = g_mp_set_hud_flags[rec[4]];
    g_mp_game_flags = g_mp_set_game_flags[rec[4]] | 1;
    if (flags & 0x80000) {
        g_rail_mirrored = g_settings[0x13];
    } else {
        g_rail_mirrored = 0;
    }
    if (flags & 8) {
        g_mp_time_left = g_settings[3] * 3000;
    } else {
        g_mp_time_left = 0;
    }
    if (flags & 0x10000) {
        g_race_difficulty = g_settings[0x10];
    } else {
        g_race_difficulty = 2;
    }
    if ((flags & 4) && g_mp_time_left == 0) {
        g_mp_hud_flags |= 2;
        g_mp_game_flags &= 0xFFFE;
    }
    if (g_mp_hud_flags & 0x80) {
        g_mp_hud_flags |= 0x1000;
    }
    if ((flags & 0x20000) && g_settings[0x11] != 0) {
        g_mp_hud_flags |= 0x20;
    }
    if ((g_mp_hud_flags & 0x100) && g_mp_time_left != 0) {
        g_mp_hud_flags = (g_mp_hud_flags & ~0x100) | 0x200;
    }
    g_player_start_lives = g_settings[2];
    g_spawn_ctl_19a_init = 3;
    g_player_start_stat9 = 0;
    g_transition_air_time = 0;
    g_mp_team_mark_count = g_settings[4];
    if (g_settings[3] >= 3) {
        g_player_start_lives = 99;
    }
    if (rec[8] == 8) {
        for (i = 0; i < 16; i++) {
            g_player_start_state[i] = 8;
        }
        g_menu_queue_drop_count = mp_slot_query(0);
    }

    /* players: queue entries != -1 (entry 0 always counts) */
    mask = 1;
    g_menu_queue_count = 1;
    if ((&g_menu_player_queue)[1] != -1) {
        mask = 3;
        g_player_pad_map[1] = (&g_menu_player_queue)[1];
        g_menu_queue_count++;
    }
    if ((&g_menu_player_queue)[2] != -1) {
        mask |= 4;
        g_menu_queue_count++;
        g_player_pad_map[2] = (&g_menu_player_queue)[2];
    }
    if ((&g_menu_player_queue)[3] != -1) {
        mask |= 8;
        g_player_pad_map[3] = (&g_menu_player_queue)[3];
        g_menu_queue_count++;
    }
    for (i = 4; i < 16; i++) {
        if ((&g_menu_player_queue)[i] != -1) {
            mask |= 1 << i;
            g_menu_queue_count++;
        }
    }

    if (rec[8] != 8) {
        i = 0;
        if (g_menu_chars_changeable != 0 && (&g_menu_player_queue)[0] >= 0) {
            do {
                g_player_start_state[i] = g_menu_characters[g_menu_player_chars[i]][6];
                i++;
            } while ((&g_menu_player_queue)[i] >= 0 && i != 4);
        }
        for (; i < 16; i++) {
            s32 mode;

            slot = &g_player_start_state[i];
            *slot = rec[8];
            mode = ((MenuState *) g_menu_state)->x42;
            if (mode == 7) {
                if ((&g_menu_player_queue)[i] < -1) {
                    *slot = 0xB;
                }
            } else if (mode == 2) {
                if (g_mp_player_team[i] == 0) {
                    *slot = 0xB;
                }
            } else if (mode == 8) {
                if (g_mp_player_team[i] != 0) {
                    *slot = 3;
                } else {
                    *slot = (random_int() & 0xF) + 0x11;
                }
            } else if (g_mp_player_team[i] != 0 && rec[8] == 4) {
                *slot = 3;
            } else if ((&g_menu_player_queue)[i] < -1 && rec[8] == 0xB) {
                *slot = (i & 3) + 0xC;
            }
        }
    }

    g_level_zoom_in_request = 2;
    n = g_menu_queue_count;
    g_human_player_count = 0;
    g_mp_human_teams = 0;
    g_player_count = n;
    for (i = 0; i < n; i++) {
        if ((&g_menu_player_queue)[i] >= 0) {
            g_human_player_count++;
            g_mp_human_teams |= 1 << g_mp_player_team[i];
        }
    }
    g_humans_alive = g_human_player_count;
    g_players_alive = g_player_count;
    bzero(g_mp_last_hitter, 0x10);
    g_mp_match_eda = -1;
    g_mp_next_placing = 4;
    for (i = 0; i < 16; i++) {
        g_mp_fixed_placings[i] = -1;
        g_mp_placings[i] = 0;
    }
    if (g_mp_free_for_all != 0) {
        n = g_menu_queue_count;
        g_mp_next_placing = g_player_count;
        used = 0;
        next = 0;
        for (i = 0; i < n; i++) {
            if ((&g_menu_player_queue)[i] >= 0) {
                g_mp_player_team[i] = (&g_menu_player_queue)[i];
                used |= 1 << g_mp_player_team[i];
            } else {
                while ((1 << next) & used) {
                    next++;
                }
                g_mp_player_team[i] = next;
                used |= 1 << next;
                next++;
            }
        }
    }
    g_mp_result_time_b[0] = -1;
    g_mp_result_time_b[1] = -1;
    g_mp_result_time_a[0] = -1;
    g_mp_result_time_a[1] = -1;
    g_mp_team_scores[0] = 0;
    g_mp_team_scores[1] = 0;
    menu_settings_apply_checked();
    g_mp_match_over = 0;
    g_chapter_replay = 0;
    g_mp_p0_start_state = g_player_start_state[0];
    game_request_transition(6, level, 0, g_mp_transition_arg[g_menu_queue_count], mask);
}

void menu_settings_apply_checked(void);
extern s8 g_mp_team_size; /* was D_800E0FE1 */
extern s8 g_players_alive; /* was D_800BEA38 */
extern s8 g_humans_alive; /* was D_80090134 */
extern u8 g_level_zoom_in_request; /* was D_800E0FC9 */
extern s16 g_mp_game_flags; /* was D_8009015C */
extern s8 g_rail_mirrored; /* was D_800D27C8 */
void save_unlocks_propagate(s32);
s32 save_route_table_load(s32, s32 *);
s32 save_route_check(s8, u8, s32 *, s32 *);
extern s8 g_menu_queue_drop_count; /* was D_80090110 */
extern s16 g_chapter_start_event; /* was D_8009014C */
extern u8 g_chapter_start_override; /* was D_80090154 */
extern s8 g_chapter_sel; /* was D_800902B0 */
extern u8 g_chapter_route_sel; /* was D_800902B4 */
extern s32 g_save_stat9; /* was D_800BE804 */
extern u8 g_level_start_point_override; /* was D_800E1001 */

/* was func_151E3864 */
void chapter_scene_start(void) {

    s32 sp24[3];

    sp24[0] = 0;
    if (g_chapter_start_override != 0) {
        sp24[1] = (s32) g_chapter_start_event;
    } else {
        save_route_table_load(g_chapter_sel, &sp24[2]);
        save_route_check(g_chapter_sel, g_chapter_route_sel, &sp24[1], sp24);
        save_route_table_free();
    }
    level_state_clear();
    event_unlock_chain(sp24[1]);
    save_unlocks_propagate(sp24[1]);
    g_level_load_id = event_table_get_u16_8(sp24[1]);
    player_stat_modify(0, 9, sp24[0]);
    g_save_stat9 = sp24[0];
    g_warp_entry_ids = event_table_get_id_field(sp24[1]);
    if (g_chapter_start_override == 2) {
        g_warp_entry_ids = g_level_start_point_override;
    }
    g_menu_queue_drop_count = 0;
    g_rail_mirrored = 0;
    g_mp_game_flags = 0;
    g_save_cur_slot = -1;
    g_game_mode = 0;
    g_level_zoom_in_request = 1;
    g_player_count = 1;
    g_human_player_count = 1;
    g_humans_alive = 1;
    g_players_alive = 1;
    g_player_start_lives = 3;
    if (g_cheat_flags & 0x200) {
        g_player_start_lives = 0x33;
    }
    *g_player_start_state = 0;
    g_mp_respawning = 0;
    g_mp_team_size = 1;
    menu_settings_apply_checked();
    g_chapter_replay = 1;
    game_request_transition(6, (s32) g_level_load_id, event_table_get_id_field(sp24[1]), 0, 1);
}

void menu_settings_apply_checked(void);
extern s8 g_humans_alive; /* was D_80090134 */
extern s16 g_mp_game_flags; /* was D_8009015C */
extern s8 g_players_alive; /* was D_800BEA38 */
extern s8 g_rail_mirrored; /* was D_800D27C8 */
extern u8 g_level_zoom_in_request; /* was D_800E0FC9 */
extern s8 g_mp_team_size; /* was D_800E0FE1 */

/* was func_151E3A1C */
void slot_game_start(void) {
    g_player_start_lives = 3;
    if (g_cheat_flags & 0x200) {
        g_player_start_lives = 0x33;
    }
    *g_player_start_state = 0;
    g_player_count = 1;
    g_human_player_count = 1;
    g_humans_alive = 1;
    g_mp_game_flags = 0;
    g_players_alive = 1;
    g_rail_mirrored = 0;
    g_game_mode = 0;
    g_chapter_replay = 0;
    game_request_transition(6, (s32) (s8) g_save_resume_level, (s32) g_save_restart_entry, 0, 1);
    g_level_zoom_in_request = 1;
    g_mp_team_size = 1;
    menu_settings_apply_checked();
}

#ifdef PORT
/* port_warp_game_start: P327 TEST AID for ?warp (intro_mode_update): starts single-player gameplay on `level` with
 * start / scene argument `scene`, the way the title menu's "continue" does (title_slot_page accept + slot_game_start,
 * without the save slot load: g_save_cur_slot = -1 = no slot, so the fresh save is left alone). Game mode 0. */
void port_warp_game_start(s32 level, s32 scene) {
    g_save_cur_slot = -1;
    g_save_best_slot_score = -1;
    g_save_slot_refresh = 0;
    g_player_start_lives = 3;
    if (g_cheat_flags & 0x200) {
        g_player_start_lives = 0x33;
    }
    *g_player_start_state = 0;
    g_player_count = 1;
    g_human_player_count = 1;
    g_humans_alive = 1;
    g_mp_game_flags = 0;
    g_players_alive = 1;
    g_rail_mirrored = 0;
    g_game_mode = 0;
    g_chapter_replay = 0;
    game_request_transition(6, level, scene, 0, 1);
    g_level_zoom_in_request = 1;
    g_mp_team_size = 1;
    menu_settings_apply_checked();
}
#endif

f32 catmull_rom_eval(s32 points, s32 segment, f32 t);
f32 sinf(f32);
extern s8 g_settings_items[];         /* settings item table: per item label text, type, then (type >= 0) max + 1 choice texts; was D_800ABA2C */
extern s8 g_settings_changed;           /* settings changed; was D_80090180 */
extern s16 g_settings_value_fade;          /* value fade: 0xFF = steady, -0xFF.. = fading in a changed value; was D_800E0EB2 */
extern s8 g_settings_old_value;           /* the value before the change; was D_800E0EB4 */
extern s8 g_settings_time_limit; /* was D_800E1013 */
extern u8 g_str_settings_label[];         /* "#"; was D_800ABC98 */
extern u8 g_str_settings_choice[];         /* "#"; was D_800ABC9C */
extern u8 g_str_settings_int_a[];         /* "%d"; was D_800ABCA0 */
extern u8 g_str_settings_text_a[];         /* "%s"; was D_800ABCA4 */
extern u8 g_str_settings_int_b[];         /* "%d"; was D_800ABCA8 */
extern u8 g_str_settings_text_b[];         /* "%s"; was D_800ABCAC */
extern u8 g_str_settings_int_c[];         /* "%d"; was D_800ABCB0 */
extern u8 g_str_settings_thousands[];         /* "%d"; was D_800ABCB4 */
extern u8 g_str_settings_int_unit[];         /* "%d %s"; was D_800ABCB8 */
extern u8 g_str_settings_arrow_r[];         /* "#"; was D_800ABCC0 */
extern u8 g_str_settings_arrow_l[];         /* "#"; was D_800ABCC4 */

// settings_list_draw: draws and edits the settings list (28 items, bit i of mask = item i shown; values g_settings[i],
// clamped to g_settings_min / g_settings_max[i]). ringLayout != 0: the items sit on a rotating ring (Catmull-Rom over 2 columns,
// x 74 / 148 / 222, scrolled by g_settings_scroll), up / down change the value and left / right move the selection;
// ringLayout == 0: a plain column at x 0x94 from y 0x46 (0x22 apart), left / right change the value and up / down move.
// The selection g_settings_sel skips hidden items; a changed value fades in from its old value when fadeValues != 0
// (g_settings_value_fade / g_settings_old_value). showCursor != 0 draws the "#" cursor arrows that slide to the selected row
// (g_settings_arrow_row / g_menu_slide_phase). alphaArg = alpha.
/* was func_151E3AE4 */
void settings_list_draw(s32 mask, s32 ringLayout, s32 showCursor, s32 alphaArg, s32 fadeValues) {   /* params were arg1..arg4 (P367) */
    u8 alpha = alphaArg;
    s8 fadeIn = fadeValues;
    MenuState *rec;
    /* The ring points: y has only 14 slots and x follows it in one frame block, so with 13 or more shown items
       y[14..] lands on x[0..] (y[count + 1] = y[1] overwrites x[0] after the wrap). Kept as in the game. */
    f32 points[14 + 32];
    f32 *y = points;
    f32 *x = points + 14;
    s32 count;
    s32 half;
    s32 step;
    s32 pos;
    s32 i;
    s32 ring;
    f32 t;
    s32 itemAlpha;
    s32 a;
    s8 shownValue;
    s32 offset;
    s8 *item;
    s32 type;
    s32 value;
    s32 drawn;
    s32 cursorRow;
    s32 px;
    s32 py;
    s32 sel;
    s32 oldSel;
    s8 *p;
    s8 old;
    s32 changed;
    s32 forward;
    s32 arrowX;
    s32 arrowY;

    count = 0;
    for (i = 0; i < 0x1C; i++) {
        if ((1 << i) & mask) {
            count++;
        }
    }
    half = count >> 1;
    ring = half;
    if (showCursor != 0 && g_menu_slide_phase != 0.0f) {
        ((MenuState *) g_menu_state)->input &= ~3;
    }
    pos = 0x46;
    if (ringLayout != 0) {
        /* ring layout: column x per slot (148 top, 222 right side going down, 148 bottom, 74 left side going up) */
        a = half;
        if (count >= 4 && (count & 1)) {
            a = half + 1;
        }
        step = 0x82 / (a + 1);
        if (count >= 4) {
            step -= 5;
        }
        i = 0;
        if (count > 0) {
            if (count & 1) {
                i = 1;
                pos = step + 0x46;
                y[1] = (f32) 0x46;
                x[1] = 148.0f;
            }
            for (; i != count; i += 2) {
                y[i + 1] = (f32) pos;
                if (i == 0) {
                    pos += step;
                    x[i + 1] = 148.0f;
                } else if (i < half) {
                    x[i + 1] = 222.0f;
                    pos += step;
                    if (i + 1 != half || (count & 1)) {
                        pos += 0x10;
                    }
                } else if (i == half) {
                    if (count & 1) {
                        x[i + 1] = 222.0f;
                    } else {
                        pos -= step;
                        x[i + 1] = 148.0f;
                    }
                } else {
                    pos = pos - step - 0x10;
                    x[i + 1] = 74.0f;
                }
                y[i + 2] = (f32) pos;
                if (i < half - 1) {
                    x[i + 2] = 222.0f;
                    pos += step;
                    if (i + 2 != half || (count & 1)) {
                        pos += 0x10;
                    }
                } else if (i == half - 1) {
                    if (count & 1) {
                        x[i + 2] = 222.0f;
                    } else {
                        x[i + 2] = 148.0f;
                        pos -= step;
                    }
                } else {
                    pos = pos - step - 0x10;
                    x[i + 2] = 74.0f;
                }
            }
            pos = 0x46;
        }
        /* wrap the ring for the spline */
        x[0] = x[count];
        y[0] = y[count];
        x[count + 1] = x[1];
        y[count + 1] = y[1];
        x[count + 2] = x[2];
        y[count + 2] = y[2];
        t = sinf(g_settings_scroll * 3.14159f - 1.570795f) * 0.5f + 0.5f;
        /* ring slot of the first item = number of shown items before the selection */
        ring = 0;
        for (i = 0; i < 0x1C; i++) {
            if (i < g_settings_sel && ((1 << i) & mask)) {
                ring++;
            }
        }
        if (ring >= count) {
            ring = 0;
        }
    }

    if (fadeIn != 0) {
        g_settings_value_fade += 0x5C;
        if (g_settings_value_fade >= 0x100) {
            g_settings_value_fade = 0xFF;
        }
        a = g_settings_value_fade;
        if (a < 0) {
            a = -a;
        }
        a = (alpha * a) >> 8;
        if (a >= 0xFE) {
            a = 0xFF;
        }
        if (g_settings_value_fade < 0) {
            shownValue = g_settings_old_value;
        } else {
            shownValue = g_settings[g_settings_sel];
        }
        itemAlpha = a;
    } else {
        g_settings_value_fade = 0xFF;
        itemAlpha = alpha;
    }

    cursorRow = 0;
    offset = 0;
    drawn = 0;
    for (i = 0; i < 0x1C; i++) {
        item = &g_settings_items[offset];
        type = item[1];
        if ((1 << i) & mask) {
            value = g_settings[i];
            if (i == g_settings_sel) {
                cursorRow = drawn;
            }
            if (ringLayout != 0) {
                px = (s32) catmull_rom_eval((s32) x, ring, t);
                py = (s32) catmull_rom_eval((s32) y, ring, t);
                ring--;
                if (ring < 0) {
                    ring += count;
                }
            } else {
                py = pos;
                px = 0x94;
                pos += 0x22;
            }
            /* label */
            text_set_color(0xFF, 0xFF, 0xFF, (u8) itemAlpha);
            text_set_pos(px, py);
            if (item[0] >= 0) {
                text_printf(((s32 *) g_text_strings)[item[0]]);
            } else if (item[0] < -1) {
                text_set_pos(px, py + 9);
                text_printf((s32) g_str_settings_label, -item[0]);
                text_set_pos(px, py + 0x16);
            }
            /* value */
            if (i == g_settings_sel && g_settings_scroll <= 0.0f) {
                text_set_color(0xFF, 0xFF, 0xFF, (u8) itemAlpha);
                if (fadeIn != 0) {
                    value = shownValue;
                }
            } else if (fadeIn != 0) {
                text_set_color(0xFF, 0xFF, 0xFF, alpha);
            } else {
                text_set_color(0xFF, 0xFF, 0xFF, (alpha >> 2) & 0xFF);
            }
            if (type < 0) {
                if (type < -1) {
                    text_printf((s32) g_str_settings_choice, value - type);
                }
            } else {
                switch (type) {
                    case 0x79:
                        break;
                    case 0x7A:
                        if (value == 0) {
                            text_printf((s32) g_str_settings_text_a, ((s32 *) g_text_strings)[0x73]);
                        } else {
                            text_printf((s32) g_str_settings_int_b, value);
                        }
                        break;
                    case 0x7B:
                        if (g_settings_time_limit >= 3) {
                            text_printf((s32) g_str_settings_text_b, ((s32 *) g_text_strings)[0x2D]);
                        } else {
                            text_printf((s32) g_str_settings_int_c, value);
                        }
                        break;
                    case 0x7C:
                        text_printf((s32) g_str_settings_thousands, value * 1000);
                        break;
                    case 0x7D:
                        if (value >= 3) {
                            text_printf((s32) g_str_settings_int_unit, value, ((s32 *) g_text_strings)[0x72]);
                        } else {
                            text_printf(((s32 *) g_text_strings)[0x73]);
                        }
                        break;
                    case 0x7E:
                        text_printf((s32) g_str_settings_int_a, value);
                        break;
                    case 0x7F:
                        text_printf(((s32 *) g_text_strings)[value != 0]);
                        break;
                    default:
                        text_printf(((s32 *) g_text_strings)[item[1 + value]]);
                        break;
                }
            }
            drawn++;
        }
        /* next item: label + type, plus the choice texts of a list item */
        if (type >= 0x79 && type <= 0x7F) {
            offset += 2;
        } else if (type >= 0) {
            offset += g_settings_max[i] + 2;
        } else {
            offset += 2;
        }
        if (g_settings[i] < g_settings_min[i]) {
            g_settings[i] = g_settings_min[i];
            g_settings_changed = 1;
        }
        if (g_settings_max[i] < g_settings[i]) {
            g_settings[i] = g_settings_max[i];
            g_settings_changed = 1;
        }
    }

    /* input */
    sel = g_settings_sel;
    forward = 1;
    rec = (MenuState *) g_menu_state;
    if (g_settings_value_fade != 0xFF) {
        rec->input = 0;
    }
    p = &g_settings[sel];
    old = *p;
    oldSel = sel;
    if (g_settings_scroll <= 0.0f) {
        changed = 0;
        rec = (MenuState *) g_menu_state;
        if (ringLayout != 0) {
            if (rec->input & 1) {
                *p = old + 1;
                g_settings_changed = 1;
                changed = 1;
            } else if (rec->input & 2) {
                *p = old - 1;
                g_settings_changed = 1;
                changed = 1;
            } else if (rec->input & 8) {
                g_settings_scroll_speed = 0.075f;
            } else if (rec->input & 4) {
                sel--;
                p--;
                if (sel < 0) {
                    sel += 0x1C;
                    p += 0x1C;
                }
                forward = 0;
                g_settings_scroll_speed = -0.075f;
                g_settings_scroll = 1.0f;
            }
        } else {
            if (rec->input & 4) {
                *p = old - 1;
                g_settings_changed = 1;
                changed = 1;
            } else if (rec->input & 8) {
                *p = old + 1;
                g_settings_changed = 1;
                changed = 1;
            } else if (rec->input & 2) {
                g_settings_scroll_speed = 1.0f;
            } else if (rec->input & 1) {
                sel--;
                p--;
                if (sel < 0) {
                    sel += 0x1C;
                    p += 0x1C;
                }
                forward = 0;
                g_settings_scroll = 0.0f;
            }
        }
        if (changed != 0 && sel == 2) {
            g_settings[3] = 2;
        }
        if (rec->input & 0xF) {
            sound_play_2d(0x4FF, 0x4650, 0x40, 0, 0);
        }
        /* values wrap around */
        if (*p < g_settings_min[sel]) {
            *p = g_settings_max[sel];
            g_settings_changed = 1;
        }
        if (g_settings_max[sel] < *p) {
            *p = g_settings_min[sel];
            g_settings_changed = 1;
        }
    }
    g_settings_scroll += g_settings_scroll_speed * (f32) g_frame_ticks;
    if (g_settings_scroll >= 1.0f) {
        sel++;
        p++;
        if (sel >= 0x1C) {
            sel -= 0x1C;
            p -= 0x1C;
        }
        g_settings_scroll_speed = 0.0f;
        g_settings_scroll = 0.0f;
    } else if (g_settings_scroll <= 0.0f) {
        g_settings_scroll_speed = 0.0f;
        g_settings_scroll = 0.0f;
    }
    /* skip hidden items */
    while (forward != 0 && !((1 << sel) & mask)) {
        sel++;
        p++;
        if (sel >= 0x1C) {
            sel -= 0x1C;
            p -= 0x1C;
        }
    }
    while (forward == 0 && !((1 << sel) & mask)) {
        sel--;
        p--;
        if (sel < 0) {
            sel += 0x1C;
            p += 0x1C;
        }
    }
    if (sel == oldSel && old != *p) {
        g_settings_value_fade = -0xFF;
        g_settings_old_value = old;
    }
    g_settings_sel = sel;

    if (showCursor != 0) {
        /* cursor arrows left and right of the selected row */
        arrowX = (s32) ((100.0f + g_menu_slide_phase * (f32) 0) * 0.5f);
        arrowY = (s32) ((f32) (g_settings_arrow_row * 0x22 + 0x46) + g_menu_slide_phase * (f32) ((cursorRow - g_settings_arrow_row) * 0x22));
        arrowX = (s32) ((f32) arrowX + 20.0f * sinf(g_menu_slide_phase * 3.1415f));
        text_set_color(0xFF, 0xFF, 0xFF, alpha);
        text_printf_at(arrowX + 0x94, arrowY, 1, (s32) g_str_settings_arrow_r, 0x1A);
        text_printf_at(0x94 - arrowX, arrowY, 1, (s32) g_str_settings_arrow_l, 0x1A);
        if (cursorRow != g_settings_arrow_row) {
            g_menu_slide_phase += 0.1f * (f32) g_frame_ticks;
            if (g_menu_slide_phase >= 1.0f) {
                g_settings_arrow_row = cursorRow;
                g_menu_slide_phase = 0.0f;
            }
        }
    }
}
s32 mp3_stream_get_state();
void mp3_stream_set_volume(s32, s32);
extern s32 *g_menu_fade_callback; /* was D_800E0EB8 */
void menu_game_start(void);

/* was func_151E49C8 */
void level_intro_mode_update(void) {
    if ((u8) g_menu_scene_start_state != 0) {
        g_menu_scene_start_state = 0;
        return;
    }
    screen_fade_update();
    if ((g_menu_pressed != 0) || (g_cutscene_slot_state != 1)) {
        if ((g_cutscene_slot_state == 1) && (mp3_stream_get_state() == 1)) {
            mp3_stream_set_volume(0, 0x370C);
        }
        g_game_mode = 7;
        g_menu_fade_callback = &menu_game_start;
        g_menu_fade_speed = 8;
    }
}

void cutscene_scene_load(s32, s32, s32, s32, s32);
extern u8 g_menu_modes_intro[][10]; /* was D_800ABA76 */
extern s16 g_mp_intro_scenes[][2]; /* was D_800ABB88 */
/* was func_151E4A78 */
void mp_start_intro_scene(void) {
    s8 *p;
    s8 temp_v1;
    s8 var_a1;
    temp_v1 = g_menu_modes_intro[((s8 *)g_menu_state)[0x42]][0];
    if (temp_v1 >= 0) {
        if (g_mp_player_team[0] != 0) {
            p = (s8 *)&g_mp_intro_scenes[temp_v1];
            var_a1 = p[3];
        } else {
            p = (s8 *)&g_mp_intro_scenes[temp_v1];
            var_a1 = p[2];
        }
        cutscene_scene_load(*(s16 *)p, var_a1, 0, 0, 0);
        *(u8 *)&g_menu_scene_start_state = 1; // fakematch: u8 store keeps the constant out of the CSE
        g_game_mode = 5;
        g_player_count = 1;
        g_human_player_count = 1;
        return;
    }
    menu_game_start();
}

typedef struct {
    s16 level;
    s8 scene;     /* +2: scene to start */
    s8 sceneAlt;  /* +3: alternative scene (see below) */
} MenuLevelStart;
extern s8 g_menu_modes_next_level;           /* per menu entry (rows of 10, as g_menu_modes_code): byte 2 = index into g_menu_level_starts; was D_800ABA75; was D_800ABA77; was D_800ABBA0 */
extern MenuLevelStart g_menu_level_starts[]; /* was D_800ABBA0 */
extern s8 g_mp_placings[16]; /* was D_800E0EF0 */
extern s8 g_mp_team_color_ids[4]; /* was D_800E0FF8 */
extern s8 D_eu_800902EC;        /* last stick y of this page (edge detection) */
extern s8 g_cont_pads_stick_x;           /* controller 1 stick y; was D_800BED3A */
extern u8 g_cutscene_finish_state; /* was D_800C40AC */
extern u8 g_str_lvstart_title[], g_str_lvstart_title2[], g_str_lvstart_player[], g_str_lvstart_sep_a[], g_str_lvstart_sep_b[], g_str_lvstart_tie[], g_str_lvstart_who[], /* was D_800ABCC8; was D_800ABCCC; was D_800ABCD0; was D_800ABCDC; was D_800ABCE0; was D_800ABCE4; was D_800ABCE8 */
    g_str_lvstart_result[], g_str_lvstart_team[], g_str_lvstart_team_won[], g_str_lvstart_yes[], g_str_lvstart_sep[], g_str_lvstart_no[];
void hud_time_draw(s32 x, s32 y, s32 value, s32 arg3);
extern s8 g_text_box_fade; /* was D_800E100C */
void menu_return_to_title(void);
// menu_level_start_page: main page 3 / level start prompt, driven by g_menu_scene_start_state. State 1 starts the level of
// menu entry rec->x42 through cutscene_scene_load (scene byte 2 of its g_menu_level_starts row, byte 3 instead when no joined
// player (entry 0) / player 0 (other entries) is flagged 1 in g_mp_placings) and clears g_menu_scene_start_state. States 2..4:
// fades in g_hud_fade_alpha (+4 per tick to 0xFF; g_text_box_fade = its inverse), draws the title text, then for multiplayer
// entries (g_menu_modes_code row byte < 0, only entries 0xB / 0xC) one line per joined player (name text 0x174 + 4 *
// character, two numbers g_mp_result_time_a / g_mp_result_time_b, separators), else a "who" line (several players flagged / the
// single player's flag / the first flagged player's character g_mp_team_color_ids), and the yes / no choice g_menu_cursor
// (stick y edge at +-30 toggles it with sfx 0x62D). Accept (g_menu_pressed & 0x8000) or the 2000-tick timeout (forces
// "no") ends the page: yes drops the g_menu_queue_drop_count dropped queue entries and sets the fade callback menu_game_start,
// no goes to main page 4 (state 3: mode 3, else callback menu_return_to_title); mode 7, g_menu_fade_speed = 8, player_order_reset.
// Other states: g_menu_pressed != 0 or g_cutscene_finish_state == 2 resets the fade and enters state 2. Clears input bit 0x20.
/* was func_151E4B40 */
void menu_level_start_page(void) {
    MenuState *rec;
    MenuLevelStart *start;
    s32 scene;
    s32 entry;
    s32 none;
    s32 i;
    s32 y;
    s32 joined;
    s8 flagged;
    s8 stickY;
    s8 prevY;
    s8 n;
    s32 last;

    if (g_menu_scene_start_state == 1) {
        entry = ((MenuState *) g_menu_state)->x42;
        start = &g_menu_level_starts[(&g_menu_modes_next_level)[entry * 10]];
        scene = start->scene;
        if (entry == 0) {
            none = 1;
            for (i = 0; i < g_menu_queue_count; i++) {
                if ((&g_menu_player_queue)[i] >= 0 && g_mp_placings[g_mp_player_team[i]] == 1) {
                    none = 0;
                }
            }
            if (none) {
                scene = start->sceneAlt;
            }
        } else if (g_mp_placings[0] != 1) {
            scene = start->sceneAlt;
        }
        cutscene_scene_load(start->level, scene, 0, 0, 0);
        g_menu_scene_start_state = 0;
        return;
    }
    entry = ((MenuState *) g_menu_state)->x42;
    if (entry != 0xB && entry != 0xC) {
        screen_fade_update();
    }
    if (g_menu_scene_start_state == 2 || g_menu_scene_start_state == 3 || g_menu_scene_start_state == 4) {
        g_hud_fade_alpha += g_frame_ticks * 4;
        if (g_hud_fade_alpha >= 0x100) {
            g_hud_fade_alpha = 0xFF;
        }
        g_text_box_fade = 0xFF - g_hud_fade_alpha;
        text_set_color(0xFF, 0xFF, 0, g_hud_fade_alpha);
        text_printf_at(0x94, 0x14, 0x81, (s32) g_str_lvstart_title, 0x4B);
        text_printf((s32) g_str_lvstart_title2);
        text_set_color(0xFF, 0xFF, 0xFF, g_hud_fade_alpha);
        text_set_pos(0x94, 0x32);
        if (g_menu_scene_start_state == 4) {
            g_player_views->unk2C = 0x80000;
        }
        entry = ((MenuState *) g_menu_state)->x42;
        if ((&g_menu_modes_code)[entry * 10] < 0) {
            if (entry == 0xB || entry == 0xC) {
                y = 0x48;
                for (i = 0; i < g_menu_queue_count; i++) {
                    if ((&g_menu_player_queue)[i] < 0) {
                        continue;
                    }
                    text_printf_at(0x58, y, 0x81, (s32) g_str_lvstart_player,
                                  *(s32 *) ((u8 *) g_text_strings + g_mp_placings[i] * 4 + 0x174));
                    hud_time_draw(0x8A, y, g_mp_result_time_a[i], 0x80);
                    hud_time_draw(0xBC, y, g_mp_result_time_b[i], 0x80);
                    text_printf_at(0xA8, y, 0x80, (s32) g_str_lvstart_sep_a);
                    text_printf_at(0xD6, y, 0x80, (s32) g_str_lvstart_sep_b);
                    y += 0x12;
                }
            }
        } else {
            joined = 0;
            for (i = 0; i < g_menu_queue_count; i++) {
                if ((&g_menu_player_queue)[i] >= 0) {
                    joined++;
                }
            }
            flagged = 0;
            for (i = 0; i < 4; i++) {
                if (g_mp_placings[i] == 1) {
                    flagged++;
                }
            }
            if (flagged >= 2) {
                text_printf_at(0x94, 0x32, 0x81, (s32) g_str_lvstart_tie, 0x58);
            } else if (joined == 1) {
                text_printf_at(0x76, 0x32, 0x81, (s32) g_str_lvstart_who, 0x52);
                text_printf_at(0xB2, 0x32, 0x81, (s32) g_str_lvstart_result, g_mp_placings[g_mp_player_team[0]] == 1 ? 0x56 : 0x57);
            } else {
                for (i = 0; i < 4; i++) {
                    if (g_mp_placings[i] == 1) {
                        text_printf_at(0x71 - (g_mp_team_color_ids[i] == 4 ? -0xC : 0), 0x32, 0x81, (s32) g_str_lvstart_team,
                                      g_mp_team_color_ids[i] + 0x4C);
                        text_printf_at((g_mp_team_color_ids[i] == 4 ? 0x15 : 0) + 0xB7, 0x32, 0x81, (s32) g_str_lvstart_team_won, 0x56);
                        break;
                    }
                }
            }
        }
        prevY = D_eu_800902EC;
        stickY = g_cont_pads_stick_x;
        if ((prevY >= -0x1E && stickY < -0x1E) || (prevY < 0x1F && stickY >= 0x1F)) {
            g_menu_cursor = 1 - (s8) g_menu_cursor;
            sound_play_2d(0x62D, 0x4650, 0x40, 0, 0);
        }
        D_eu_800902EC = stickY;
        text_printf_at(0x53, 0xB4, 1, (s32) g_str_lvstart_yes, ((s8) g_menu_cursor == 0) + 0x21);
        text_printf_at(0xD5, 0xB4, 1, (s32) g_str_lvstart_no, ((s8) g_menu_cursor == 1) + 0xE);
        text_printf_at(0x94, 0xB4, 1, (s32) g_str_lvstart_sep, 0x1A);
        if ((g_menu_pressed & 0x8000) || g_game_mode_timer > 0x7D0) {
            if (g_cutscene_slot_state == 1 && mp3_stream_get_state() == 1) {
                mp3_stream_set_volume(0, 0x370C);
            }
            if (g_game_mode_timer > 0x7D0) {
                g_menu_cursor = 1;
            }
            g_game_mode = 7;
            if ((s8) g_menu_cursor == 0) {
                n = g_menu_queue_drop_count;
                if (n != 0) {
                    last = 0x10 - n;
                    for (i = n; i < last; i++) {
                        (&g_menu_player_queue)[i] = (&g_menu_player_queue)[i + n];
                        g_mp_player_team[i] = g_mp_player_team[i + n];
                    }
                    g_menu_queue_drop_count = 0;
                }
                g_menu_fade_callback = (s32 *) menu_game_start;
            } else {
                ((MenuState *) g_menu_state)->mainPage = 4;
                if (g_menu_scene_start_state == 3) {
                    g_game_mode = 3;
                } else {
                    g_menu_fade_callback = (s32 *) menu_return_to_title;
                }
            }
            g_menu_fade_speed = 8;
            g_menu_scene_start_state = 0;
            player_order_reset();
            g_player_count = 1;
            g_human_player_count = 1;
        }
    } else if (g_menu_pressed != 0 || g_cutscene_finish_state == 2) {
        g_hud_fade_alpha = 0;
        g_menu_scene_start_state = 2;
    }
    ((MenuState *) g_menu_state)->input &= ~0x20;
}

extern u8 g_mp_match_quit;           /* set by mp_match_end: nonzero = the match was quit, not finished; was D_800E0EB6 */
// mp_match_end_continue: P232. Menu fade callback (g_menu_fade_callback, set by mp_match_end) run when a multiplayer match
// has ended: closes the pause / menu state, keeps only some of the g_mp_hud_flags flags and picks what comes next from
// the menu mode row g_menu_modes[x42]: byte 7 = the level to go on with (an index into g_menu_level_starts, -1 none, -2 back
// to the menu), byte 5 >= 0 = a multi-round mode, where two or more players placed first (g_mp_placings[0..3] == 1)
// replays it (main page 3 state 4). Otherwise the next level g_menu_level_starts[byte 7] is started (state 1); a finished
// match of mode -2 goes back to the menu (state 2) without restarting; anything else restarts level 0x1D. A
// restart sets main page 6 (3 when nothing is left), calls game_request_transition(6, level, 0, 0, 1), resets the player
// order (player_order_reset) and sets g_player_count / g_human_player_count to 1.
/* was func_151E533C */
void mp_match_end_continue(void) {
    s8 *mode;
    s32 next;
    s8 tie = 0;
    s8 n;
    s32 level;

    g_menu_cursor = 0;
    g_pause_open = 0;
    g_menu_setup_step = 0;
    g_game_mode_timer = 0;
    mode = g_menu_modes[(s8) g_menu_state[0x42]];
    next = mode[7];
    g_mp_hud_flags &= 0xF369;
    if (g_menu_modes[(s8) g_menu_state[0x42]][5] >= 0) {
        n = 0;
        if (g_mp_placings[0] == 1) {
            n = 1;
        }
        if (g_mp_placings[1] == 1) {
            n++;
        }
        if (g_mp_placings[2] == 1) {
            n++;
        }
        if (g_mp_placings[3] == 1) {
            n++;
        }
        tie = (n >= 2);
    }
    if (next >= 0 && !tie) {
        g_game_mode = 6;
        level = g_menu_level_starts[next].level;
        g_menu_scene_start_state = 1;
    } else if (next == -2 && (s8) g_mp_match_quit == 0) {
        g_game_mode = 6;
        g_menu_scene_start_state = 2;
        g_mp_hud_flags = 0;
        return;
    } else if (!tie) {
        level = 0x1D;
        g_game_mode = 3;
    } else {
        level = 0x1D;
        g_game_mode = 6;
        g_menu_scene_start_state = 4;
    }
    g_chapter_replay = 0;
    game_request_transition(6, level, 0, 0, 1);
    player_order_reset();
    g_player_count = 1;
    g_human_player_count = 1;
}

/* was func_151E5528 */
void game_mode_set_10(void) {
    g_game_mode = 10;
}

/* was func_151E553C */
void wait_button_mode_update(void) {
    if (g_menu_pressed & 0x8020) {
        g_game_mode = 4;
    }
}

/* was func_151E5564 */
void menu_return_to_title(void) {
    g_hud_fade_alpha = 0;
    player_order_reset();
    g_game_mode = 3;
    g_menu_setup_step = 0;
    g_menu_scene_start_state = 0;
    g_chapter_replay = 0;
    game_request_transition(6, 0x1D, 0, 0, 1);
}

s32 menu_blink_update();
extern s32 *g_menu_fade_callback; /* was D_800E0EB8 */
void menu_return_to_title(void);

/* was func_151E55C8 */
void end_screen_mode_update(void) {
    screen_fade_update();
    menu_blink_update();
    if (g_game_mode_timer >= 0x3E9) {
        g_menu_pressed |= 0x8000;
    }
    if (g_menu_pressed != 0) {
        g_game_mode = 7;
        g_menu_fade_callback = &menu_return_to_title;
        g_menu_fade_speed = 8;
    }
}

extern f32 g_menu_fade_amount; /* was D_80090170 */
extern f32 g_fade_lens_zoom_k_be30; /* was D_800ABE30 */
extern f32 g_fade_lens_rate_early; /* was D_800ABE34 */
extern f32 g_fade_lens_rate_late; /* was D_800ABE38 */

/* was func_151E564C */
void fade_mode_update(void)
{
  unsigned int n; // fakematch: permuter temp
  int ff; // fakematch: constant in a register gives beq a2,v0 operand order
  s32 v;
  f32 f;
  v = *((u8 *) (&g_screen_fade_alpha));
  ff = 0xFF; // fakematch
  g_menu_fade_amount = 1.0f - (((u32) v) / 255.0f);
  if (((u8) g_menu_fade_speed) == 0xFF)
  {
    f = g_hud_lens_zoom;
    if (g_fade_lens_zoom_k_be30 < f)
    {
      v = (u8) (g_screen_fade_alpha = v + g_frame_ticks);
      if (v < 0x55)
      {
        g_hud_lens_zoom_rate = g_fade_lens_rate_early;
      }
      else
      {
        g_hud_lens_zoom_rate = g_fade_lens_rate_late;
      }
    }
    if (f < ((float) 1.0f))
    {
      return;
    }
    if (v < 0x6E)
    {
      return;
    }
  }
  else
  {
    n = (u8) g_menu_fade_speed;
    if (v != ff)
    {
      v += g_frame_ticks * n;
      if (v >= 0x100)
      {
        v = 0xFF;
      }
      g_screen_fade_alpha = v;
      return;
    }
  }
  *((u8 *) (&g_screen_fade_alpha)) = 0xFF;
  g_menu_fade_speed = 8;
  g_menu_fade_amount = 1.0f;
  if (1) // fakematch: empty ifs on separate lines
  {
  }
  if (1)
  {
  }
  ((void (*)(void)) g_menu_fade_callback)();
}

/* was func_151E5798 */
void menu_state_reset(void) {
    (*(f32 *)g_menu_state) = 0.0f;
    (*(f32 *)((u8 *)g_menu_state + 4)) = 0.0f;
    (*(s8 *)((u8 *)g_menu_state + 0x2B)) = 0;
    (*(s16 *)((u8 *)g_menu_state + 0x20)) = 0;
    (*(s8 *)((u8 *)g_menu_state + 0x3E)) = 0;
    (*(s8 *)((u8 *)g_menu_state + 0x3F)) = 0;
    (*(s8 *)((u8 *)g_menu_state + 0x41)) = 0;
    (*(s8 *)((u8 *)g_menu_state + 0x43)) = 0;
    (*(s8 *)((u8 *)g_menu_state + 0x44)) = 0;
    (*(f32 *)((u8 *)g_menu_state + 0x10)) = 0.0f;
    (*(s8 *)((u8 *)g_menu_state + 0x2A)) = 0;
    (*(f32 *)((u8 *)g_menu_state + 0x14)) = 0.0f;
    (*(f32 *)((u8 *)g_menu_state + 0x18)) = 0.0f;
    (*(f32 *)((u8 *)g_menu_state + 0x1C)) = 0.0f;
    (*(f32 *)((u8 *)g_menu_state + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)g_menu_state + 8)) = 0.0f;
}

void text_bank_reset(void);
extern u8 g_menu_state_rec[]; /* was D_800E0F20 */
extern u8 g_menu1_stop_pages[]; /* was D_800AB950 */
extern u8 g_game_mode_prev; /* was D_800E0FC5 */

/* was func_151E582C */
void menu_init(void) {
    s32 i;

    i = 0;
    do {
        g_settings[i] = g_settings_defaults[i];
        i++;
    } while (i < 0x1C);
    g_game_mode_timer = 0;
    text_bank_reset();
    if (g_menu_state == NULL) {
        g_menu_state = g_menu_state_rec;
        menu_state_reset();
        if (*(s8 *)(g_menu_state + 0x3E) == 1) {
            *(s8 *)(g_menu_state + 0x2C) = g_menu1_stop_pages[*(s8 *)(g_menu_state + 0x2C)];
        }
    }
    level_state_clear();
    g_game_mode = 11;
    g_chapter_replay = 0;
    game_request_transition(6, 0x25, 0, 0, 1);
    g_game_mode_prev = g_game_mode;
}

// Per-frame game-mode step: screen offset/scale from the g_settings settings, input snapshot,
// the mode's handler from the table g_game_mode_fns[g_game_mode], and the time-in-mode counter
// g_game_mode_timer (reset and the previous mode kept in g_game_mode_prev when the mode changed; mode 7 keeps it).
extern f32 g_vi_window_scale_step; /* was D_800ABE3C */
extern s8 g_text_box_fade; /* was D_800E100C */
extern u16 g_cont_pressed; /* was D_800BED50 */
extern u8 g_game_mode_prev; /* was D_800E0FC5 */
extern void (*g_game_mode_fns[])(void); /* was D_8009018C */
void vi_mode_set_window(s32 x, s32 y, f32 scaleY, f32 scaleX);
void text_bank_load(s32 arg0);

/* was func_151E5928 */
void game_mode_frame_step(void) {
    u8 prevMode = g_game_mode;

    vi_mode_set_window((g_settings[0x17] - 16) * 2, (g_settings[0x18] - 8) * 2, g_settings[0x1A] * g_vi_window_scale_step + 1.0f,
                  g_settings[0x1B] * g_vi_window_scale_step + 1.0f);
    g_dbg_crash_marker = 0x08000000;
    g_text_box_fade = 0xFF;
    text_set_flags(0x81);
    g_menu_pressed = g_cont_pressed;
    if (g_menu_input_lock_frames != 0) {
        g_menu_input_lock_frames--;
        g_menu_pressed = 0;
    }
    if (g_game_mode == 0) {
        text_bank_load(2);
    } else if (g_game_mode == 8) {
        text_bank_load(4);
    } else {
        text_bank_load(1);
    }
    g_game_mode_fns[g_game_mode]();
    if (g_game_mode != 7) {
        g_game_mode_timer += g_frame_ticks;
        if (prevMode != g_game_mode) {
            g_game_mode_prev = prevMode;
            g_game_mode_timer = 0;
        }
    }
    g_dbg_crash_marker = 0;
}
/* was func_151E5AB8 */
void screen_fade_update(void)
{
  f32 temp_f0;
  s32 var_v1_2;
  if (g_game_mode != 2)
  {
    if (((u8) g_screen_fade_alpha) != 0)
    {
      var_v1_2 = ((u8) g_screen_fade_alpha) - (g_frame_ticks * ((u8) g_menu_fade_speed));
      if (var_v1_2 < 0)
      {
        var_v1_2 = 0;
      }
      g_screen_fade_alpha = var_v1_2;
    }
    if (((g_menu_state != 0) && ((*((s8 *) (((u8 *) g_menu_state) + 0x2B))) == 0)) && ((*((f32 *) (((u8 *) g_menu_state) + 0xC))) > 0.0f))
    {
      temp_f0 = *((f32 *) (((u8 *) g_menu_state) + 8));
      if (temp_f0 > 0.5f)
      {
        var_v1_2 = (s32) ((temp_f0 - 0.5f) * 524.0f);
        if (var_v1_2 >= 0x100)
        {
          var_v1_2 = 0xFF;
        }
        g_screen_fade_alpha = (s8) var_v1_2;
      }
    }
  }
}

void mp_match_end_continue(void);
extern u8 g_menu_cursor; /* was D_800901CC */
extern u16 g_mp_hud_flags; /* was D_80090160 */
extern u8 g_mp_match_quit; /* was D_800E0EB6 */
extern s8 g_menu_modes[][10]; /* was D_800ABA70 */

/* was func_151E5B94 */
void mp_match_end(s32 arg0) {
    s32 i;

    g_game_mode_timer = 0;
    g_menu_cursor = 0;
    g_player_start_state[0] = 0;
    if (g_mp_mode_active != 0) {
        g_game_mode = 7;
        g_menu_fade_speed = 8;
        if (g_menu_modes[(s8)g_menu_state[0x42]][7] != -1) {
            g_menu_state[0x3F] = 4;
            g_menu_fade_callback = (s32 *)&mp_match_end_continue;
        } else {
            g_menu_state[0x3F] = 3;
            g_menu_fade_callback = (s32 *)&pause_quit_to_menu;
        }
        for (i = 0; i < g_human_player_count; i++) {
            *(s16 *)(g_menu_state + i * 12 + 0x6C) = *(s16 *)(*(u8 **)((u8 *)&g_objects[i] + 0x31C) + 0x1AA);
        }
        g_mp_hud_flags &= 0xE35F;
        g_mp_match_quit = arg0;
        if (g_menu_modes[(s8)g_menu_state[0x42]][7] == -2) {
            if (arg0 == 0) {
                mp_match_end_continue();
            } else {
                g_menu_fade_callback = (s32 *)&pause_quit_to_menu;
                g_menu_state[0x3F] = 3;
            }
        }
    } else {
        g_game_mode = 4;
    }
}

/* was func_151E5D28 */
void player_order_reset(void) {
    g_player_pad_map[0] = 0;
    g_player_pad_map[1] = 1;
    g_player_pad_map[2] = 2;
    g_player_pad_map[3] = 3;
}

/* was func_151E5D54 */
s32 menu_blink_update(void) {
    s32 d;
    s32 v;

    if ((u8)g_menu_blink_dir == 0) {
        d = g_frame_ticks * 8;
    } else {
        d = -g_frame_ticks * 8;
    }
    v = (u8)g_menu_blink_alpha;
    v += d;
    if (v >= 0x100) {
        v = 0x1FE - v;
        g_menu_blink_dir = (u8)g_menu_blink_dir ^ 1;
    } else if (v < 0) {
        v = -v;
        g_menu_blink_dir = (u8)g_menu_blink_dir ^ 1;
    }
    g_menu_blink_alpha = v;
}

/* was func_151E5DD8 */
void menu_clear_flag_ebc(void) {
    if (g_menu_flag_ebc != 0) {
        g_menu_flag_ebc = 0;
    }
}

/* was func_151E5DF8 */
s8 mp_is_free_for_all(void) {
    return g_mp_free_for_all;
}

extern s8 g_settings_score_limit;            /* score limit of the scored game modes (0 = none); was D_800E1016 */
/* mp_match_rules_update: once per frame in a multiplayer match. Decides whether the match is over (sets and returns
 * the match-over flag g_mp_match_over, 1 = over; 1 straight away when it is already set) and writes each player's / team's
 * placing to g_mp_placings[] (1 = first; a fixed placing already in g_mp_fixed_placings[] wins, -1 = none). The match ends on the
 * time limit (settings byte 3 >= 3 and g_mp_time_left run out). Free-for-all (g_mp_free_for_all set): a player reaching the
 * score limit g_settings_score_limit, fewer than two players left in the queue (g_players_alive / g_humans_alive minus g_menu_queue_drop_count);
 * placings by score (+1000 for those at the limit) minus the handicap g_mp_hits_taken[], then the +0x1AA tie-break, then
 * the lower index; mode bit 0x80 copies the placings from the player records (g_race_records +0x2A, else +0x29).
 * Team games: per-team totals (scores, player_stat_get kills 4 / deaths 3 * 6, player_stat_get(team, 6), +0x1AA), a
 * mode-dependent column (g_menu_state +0x42) against its limit, placings by that column then score then +0x1AA; the
 * match also ends when fewer than two teams have live players or none of them is a human team (g_mp_human_teams);
 * eliminated players and teams get the next placing from the down counter g_mp_next_placing. */
/* was func_151E5E08 */
s32 mp_match_check_over(void) {
    s32 tm[16];                  /* 4 columns of 4 teams: score, kill points, player_stat_get(team, 6), +0x1AA */
    s32 over = 0;
    s32 i, j, n, col, team, kills, live, humans;
    s16 lim, a, b;
    s8 limit, mask;
    s8 *out;

    if (g_mp_match_over != 0) {
        return 1;
    }
    if (g_settings[3] >= 3 && g_mp_time_left <= 0) {
        g_mp_match_eda = -1;
        over = 1;
    }
    if (g_mp_free_for_all != 0) {
        n = g_player_count;
        lim = -1;
        for (i = 0; i < n; i++) {
            if (g_settings_score_limit != 0 && *(s16 *) (g_menu_state + 0x46 + i * 2) >= g_settings_score_limit) {
                over = 1;
                lim = g_settings_score_limit;
            }
            if ((g_player_view_hidden_mask & (1 << i)) && g_mp_fixed_placings[i] == -1) {
                g_mp_fixed_placings[i] = g_mp_next_placing--;
            }
        }
        g_mp_match_eda = -1;
        if (g_players_alive - g_menu_queue_drop_count < 2 || g_humans_alive - g_menu_queue_drop_count <= 0) {
            over = 1;
        }
        if (g_mp_hud_flags & 0x80) {
            for (i = 0; i < g_human_player_count; i++) {
                if (g_mp_fixed_placings[i] != -1) {
                    g_mp_placings[i] = g_mp_fixed_placings[i];
                } else if ((s8) g_race_records[i].pad28[2] != 0x7F) {
                    g_mp_placings[i] = g_race_records[i].pad28[2];
                } else {
                    g_mp_placings[i] = g_race_records[i].pad28[1];
                }
            }
        } else {
            for (i = 0; i < g_human_player_count; i++) {
                if (g_player_start_state[i] == 10) {
                    continue;
                }
                out = &g_mp_placings[i];
                if (g_mp_fixed_placings[i] != -1) {
                    *out = g_mp_fixed_placings[i];
                    continue;
                }
                *out = 1;
                a = *(s16 *) (g_menu_state + 0x46 + i * 2);
                if (a >= lim) {
                    a += 1000;
                }
                a -= ((s16 *) g_mp_hits_taken)[i];
                for (j = 0; j < n; j++) {
                    if (j == i || g_mp_fixed_placings[j] != -1 || g_player_start_state[j] == 10) {
                        continue;
                    }
                    b = *(s16 *) (g_menu_state + 0x46 + j * 2);
                    if (b >= lim) {
                        b += 1000;
                    }
                    b -= ((s16 *) g_mp_hits_taken)[j];
                    if (a < b) {
                        (*out)++;
                    } else if (a == b) {
                        if (g_objects[j].unk31C->unk1AA < g_objects[i].unk31C->unk1AA) {
                            (*out)++;
                        } else if (g_objects[i].unk31C->unk1AA == g_objects[j].unk31C->unk1AA && j < i &&
                                   g_last_player_index < j) {
                            (*out)++;
                        }
                    }
                }
            }
        }
        g_mp_match_over = over;
        return over;
    }

    for (i = 0; i < 16; i++) {
        tm[i] = 0;
    }
    for (i = 0; i < g_player_count; i++) {
        team = g_objects[i].unk128;
        tm[team] += *(s16 *) (g_menu_state + 0x46 + i * 2);
        kills = player_stat_get(i, 4);
        tm[4 + team] += player_stat_get(i, 3) * 6 + kills;
        tm[8 + team] = player_stat_get(team, 6);
        tm[12 + team] += g_objects[i].unk31C->unk1AA;
    }
    col = 8;
    limit = -1;
    switch (g_menu_state[0x42]) {
        case 0:
            limit = g_settings[4];
            break;
        case 2:
        case 8:
        case 10:
            limit = g_settings[0x12];
            break;
        case 9:
            col = 0;
            if (g_settings[3] < 3) {
                col = 4;
            }
            break;
    }
    if (limit > 0) {
        for (i = 0; i < g_mp_team_count; i++) {
            if (tm[col + i] >= limit) {
                over = 1;
                g_mp_match_eda = i;
            }
        }
    }
    text_set_pos(20, 20);
    n = g_mp_team_count;
    for (i = 0; i < n; i++) {
        if (g_mp_fixed_placings[i] != -1) {
            g_mp_placings[i] = g_mp_fixed_placings[i];
            continue;
        }
        g_mp_placings[i] = 1;
        for (j = 0; j < n; j++) {
            if (j == i || g_mp_fixed_placings[j] != -1) {
                continue;
            }
            if (tm[col + i] < tm[col + j]) {
                g_mp_placings[i]++;
            } else if (tm[col + i] == tm[col + j]) {
                if (tm[i] < tm[j]) {
                    g_mp_placings[i]++;
                } else if (tm[i] == tm[j] && tm[12 + j] < tm[12 + i]) {
                    g_mp_placings[i]++;
                }
            }
        }
    }
    mask = 0;
    n = g_player_count;
    for (i = 0; i < n; i++) {
        if (g_player_start_state[i] != 10 && !(g_player_view_hidden_mask & (1 << i))) {
            mask |= 1 << g_objects[i].unk128;
        }
    }
    live = 0;
    humans = 0;
    for (i = 0; i < 4; i++) {
        if (mask & (1 << i)) {
            live++;
            if (g_mp_human_teams & (1 << i)) {
                humans++;
            }
        } else if (g_mp_fixed_placings[i] == -1) {
            g_mp_fixed_placings[i] = g_mp_next_placing--;
        }
    }
    if (humans == 0 || live < 2) {
        over = 1;
        g_mp_match_eda = -1;
    }
    g_mp_match_over = over;
    return over;
}

/* was func_151E6710 */
s32 mp_player_team(s32 arg0) {
    s8 var_v1;
    if ((g_mp_mode_active != 0) || (g_game_mode != 0)) {
        var_v1 = g_mp_player_team[arg0];
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    return arg0;
}

/* was func_151E6758 */
s8 mp_human_player_count(void) {
    if (g_settings_cpu_views != 0) {
        if (g_player_count >= 5) {
            return g_human_player_count;
        }
        return g_player_count;
    }
    return g_human_player_count;
}

extern s16 g_mp_game_flags; /* was D_8009015C */
extern u8 g_mp_last_hitter[]; /* was D_800E0FE8 */
s32 random_int(void);
s32 sound_pick_variant(s32, s32);
void actor_sound_play2_delayed(u16, struct127 *, s32, s32, s32, s32);

/* Per-player multiplayer stats in the menu record g_menu_state: s16 counters at 0x46 + 2 * player and in 12-byte
 * rows at 0x66 + 12 * player. */
#define MP_KILLS(p) (*(s16 *)(g_menu_state + 0x46 + (p) * 2))
#define MP_ROW(p, off) (*(s16 *)(g_menu_state + (p) * 0xC + (off)))

// mp_report_hit: multiplayer hit report. `attacker` hit `victim` with damage kind `kind`. The scoring player is the
// attacker's slot in g_objects or, for a non-player attacker, its owner (unk124 = slot + 1); no player -> nothing.
// Marks the victim's last hitter (g_mp_last_hitter[victim] = player | 0x80); for human players (< g_human_player_count) counts hits
// on other teams (g_mp_player_team = team; row +0x66, +0x6A for kind 0x2E) and team kills (row +0x70, not kind 0x2D); a
// kill of another team's player raises the kill score (+0x46, capped at 9999; player_stat_modify when flag 0x200 of
// g_mp_game_flags is set); the victim counts a hit taken (row +0x6E). Then the scoring character (by id 0x75 / 0x80 /
// 0x3B / 0x88) may say a taunt: sound id (sound_pick_variant picks one of `n` variants) played by actor_sound_play2_delayed.
// Kind 0x33 instead plays sound 0x510 on the victim when its character type (unk31C + 0x78) is 0x21 / 0x22.
/* was func_151E67A0 */
void mp_report_hit(struct127 *attacker, struct127 *victim, s32 kind) {
    struct127 *src = attacker;
    s32 player = (s32)((u8 *)attacker - (u8 *)g_objects) / 0x32C;
    s32 vi;
    s32 sound;
    s32 n;
    s32 arg5;
    s32 mode;
    s32 r;

    if (player >= g_player_count) {
        player = attacker->unk124 - 1;
        if (player >= 0) {
            src = &g_objects[player];
        }
    }
    if (player < 0 || player >= g_player_count) {
        return;
    }
    vi = (s32)((u8 *)victim - (u8 *)g_objects) / 0x32C;
    g_mp_last_hitter[vi] = player | 0x80;
    if (player < g_human_player_count) {
        if (g_mp_player_team[player] != g_mp_player_team[vi]) {
            MP_ROW(player, 0x66)++;
            if (kind == 0x2E) {
                MP_ROW(player, 0x6A)++;
            }
        }
        if (victim->health == 0 && g_mp_player_team[player] == g_mp_player_team[vi] && kind != 0x2D) {
            MP_ROW(player, 0x70)++;
        }
    }
    if (victim->health == 0 && MP_KILLS(player) < 9999 && g_mp_player_team[player] != g_mp_player_team[vi]) {
        MP_KILLS(player)++;
        if ((u16)g_mp_game_flags & 0x200) {
            player_stat_modify(g_mp_player_team[player] != 0, 10, 1);
        }
    }
    if (vi < g_human_player_count) {
        MP_ROW(vi, 0x6E)++;
    }
    if (src == victim || victim->unk31C == NULL || src->health == 0) {
        return;
    }
    sound = 0;
    *((u8 *)src->unk31C + 0xAF) = 0;
    arg5 = 0;
    n = 0;
    if (kind == 0x33) {
        r = *((u8 *)victim->unk31C + 0x78);
        if (r == 0x21 || r == 0x22) {
            actor_sound_play_untracked(0x510, victim, 0x61A8, 0x12C, 0x190);
        }
        return;
    }
    if (src->id == 0x75 && victim->health == 0) {
        if (victim->id == 0x75) {
            if (vi < g_human_player_count && MP_ROW(vi, 0x70) >= 4) {
                sound = 0x665;
                n = 4;
            }
        } else if (kind == 0x34) {
            if ((random_int() & 3) == 3) {
                sound = 0x52A;
            }
        } else {
            sound = 0x4D1;
            n = 3;
        }
        if (sound == 0) {
            return;
        }
        if (n != 0) {
            sound = sound_pick_variant(sound, n);
        }
        actor_sound_play2_delayed((u16)sound, src, 0x6D60, 0x320, 0xBB8, 0);
    } else if (src->id == 0x80) {
        mode = -1;
        if (attacker != src && attacker->interaction_state == 4) {
            mode = (u16)attacker->unk278;
        }
        if (victim->id == 0x80) {
            if (vi < g_human_player_count && MP_ROW(vi, 0x70) >= 4) {
                n = 8;
                sound = 0x65A;
            }
        } else if (mode == 2) {
            if (victim->health == 0 || (random_int() & 7) == 0) {
                sound = 0x571;
                n = 3;
            }
        } else if (*((u8 *)victim->unk31C + 0x1AC) != 0) {
            if (kind != 0x21 && (victim->health == 0 || (random_int() & 3) == 3)) {
                n = 4;
                sound = 0x582;
                arg5 = 25;
            }
        } else if (kind == 0x2E) {
            arg5 = 25;
            if (*((u8 *)src->unk31C + 0x78) == 0x23 && (random_int() & 3) == 0) {
                sound = 0x587;
            } else {
                sound = 0x579;
                n = 3;
            }
        } else if (kind == 0x2F) {
            if (random_int() & 1) {
                sound = 0x588;
                arg5 = 25;
            }
        } else if (kind == 0x2C) {
            sound = 0x56D;
            n = 7;
            arg5 = 50;
        } else if (kind == 0x21 || kind == 0x20 || kind == 0x31) {
            if (victim->health == 0 || (random_int() & 7) == 3) {
                sound = 0x571;
                n = 3;
                arg5 = 25;
            }
        }
        if (sound == 0) {
            return;
        }
        if (n != 0) {
            sound = sound_pick_variant(sound, n);
        }
        actor_sound_play2_delayed((u16)sound, src, 0x7D00, 0x258, 0x7D0, arg5);
    } else if (src->id == 0x3B) {
        mode = -1;
        if (attacker != src && attacker->interaction_state == 4) {
            mode = (u16)attacker->unk278;
        }
        if (mode == 2) {
            if (victim->health == 0 || (random_int() & 7) == 7) {
                sound = 0x538;
                n = 3;
            }
        } else if (kind == 0x2E) {
            sound = 0x52F;
            n = 3;
            arg5 = 25;
        } else if (kind == 0x2C || kind == 0x2F) {
            sound = 0x540;
            n = 2;
            arg5 = 50;
        } else if (kind == 0x25 || kind == 0x26) {
            if (player & 1) {
                if (victim->health >= 2) {
                    sound = 0x55F - victim->health;
                    arg5 = 25;
                }
            } else {
                sound = 0x565 - victim->health;
                arg5 = 25;
            }
        } else if (kind == 0x21) {
            if ((random_int() & 3) == 3) {
                sound = 0x52C;
                arg5 = 25;
            }
        } else if (kind == 0x20) {
            r = random_int() & 0xF;
            if (r != 0) {
                r++;
            }
            if (r < 4) {
                sound = r + 0x52B;
                arg5 = 25;
            }
        }
        if (sound == 0) {
            return;
        }
        if (n != 0) {
            sound = sound_pick_variant(sound, n);
        }
        actor_sound_play2_delayed((u16)sound, src, 0x7D00, 0x258, 0x7D0, arg5);
    } else if (src->id == 0x88) {
        if (victim->health != 0) {
            return;
        }
        if (kind == 0x34) {
            if ((random_int() & 3) == 3) {
                sound = 0x52A;
            }
        } else if (kind == 0x21) {
            sound = 0x41A;
        } else {
            sound = 0x415;
            arg5 = 25;
            n = 5;
        }
        if (sound == 0) {
            return;
        }
        if (n != 0) {
            sound = sound_pick_variant(sound, n);
        }
        actor_sound_play2_delayed((u16)sound, src, 0x6D60, 0x320, 0xBB8, arg5);
    }
}
#undef MP_KILLS
#undef MP_ROW

/* Load the text bank `bank` (1, 2, 4: picked per game mode by game_mode_frame_step) for the current language.
 * g_settings_language = language, g_text_bank_lang = language of the loaded banks, g_text_bank_loaded = loaded bank (0 = none).
 * A bank is a block of NUL-terminated strings (runs of NULs between them), loaded with asset_load
 * (asset group 3, type 0x1C, language, entry bank - 1) into g_text_bank_data; g_text_strings = its string pointer table.
 * Bank 1 also loads entry 2 into g_text_bank1_extra with an 80-entry table g_text_scene_names. The old banks are freed
 * with heap_free first (the bank-1 extras only when they exist). */
extern u8 g_text_bank_lang; /* was D_800BEECB */
extern s8 g_settings_language; /* was D_800E101A */
extern u8 **g_text_scene_names; /* was D_800E0FB8 */
u8 *asset_load(s32 *size, s32 group, s32 type, s32 lang, s32 entry);
void *allocate_memory(s32, s32, s32, s32);
void heap_free(s32);

/* was func_151E7110 */
void text_bank_load(s32 bank) {
    s32 size;
    s32 entry;
    s32 count;
    s32 i;
    u8 *p;
    u8 *end;

    if (g_text_bank_lang != g_settings_language) {
        g_text_bank_lang = g_settings_language;
        g_text_bank_loaded = 0;
    }
    if (bank == g_text_bank_loaded) {
        return;
    }
    if (g_text_bank_data != 0) {
        heap_free(g_text_bank_data);
        g_text_bank_data = 0;
        if (g_text_bank1_extra != 0) {
            heap_free(g_text_bank1_extra);
            heap_free((s32)g_text_scene_names);
            heap_free((s32)g_text_strings);
            g_text_bank1_extra = 0;
        }
    }
    g_text_bank_loaded = bank;
    if (g_text_bank_loaded == 0) {
        return;
    }

    entry = bank - 1;
    p = asset_load(&size, 3, 0x1C, g_text_bank_lang, entry);
    g_text_bank_data = (s32)p;
    end = p + size;
    count = 0;
    do {
        while (*p != 0) p++;
        while (*p == 0) p++;
        count++;
    } while (p < end);

    g_text_strings = allocate_memory((count + 1) * 4, 1, 0, 0);
    p = (u8 *)g_text_bank_data;
    end = p + size;
    i = 0;
    do {
        ((u8 **)g_text_strings)[i++] = p;
        while (*p != 0) p++;
        while (*p == 0) p++;
    } while (p < end);

    if (entry != 0) {
        return;
    }
    g_text_bank1_extra = (s32)asset_load(&size, 3, 0x1C, g_text_bank_lang, 2);
    g_text_scene_names = allocate_memory(80 * sizeof(u8 *), 1, 0, 0);
    p = (u8 *)g_text_bank1_extra;
    for (i = 0; i != 80; i++) {
        g_text_scene_names[i] = p;
        while (*p != 0) p++;
        while (*p == 0) p++;
    }
}

/* was func_151E73A8 */
void text_bank_reset(void) {
    g_text_bank_loaded = 0;
    g_text_bank_data = 0;
    g_text_bank1_extra = 0;
}

s32 rail_node_find_by_tag(s32 id);
s32 rail_node_position(s32 point, f32 *x, f32 *y, f32 *z);
f32 catmull_rom_eval(s32 points, s32 segment, f32 t);
void music_play_song(s32 sound, s32 prevSound, s32 arg2);
u8 *world_record_find(u8 id);
f32 sinf(f32);
extern u8 g_menu0_stop_points[];         /* menu 0: carousel stop -> path point id (6 stops); was D_800902F0 */
extern f32 g_menu0_zoom_speeds[];        /* menu 0: zoom speed per stop; was D_800902F8 */
extern u8 g_menu1_stop_points[];         /* menu 1: carousel stop -> path point id (8 stops); was D_80090338 */
extern f32 g_menu1_zoom_speeds[];        /* menu 1: zoom speed per stop; was D_80090340 */
extern u16 g_menu0_stop_sounds[][2];     /* menu 0: sound per stop: [0] accept, [1] back; was D_800ABD04 */
extern u16 g_menu1_stop_sounds[][2];     /* menu 1; was D_800ABD1C */
extern f32 D_eu_80090310[];     /* menu 0: per-page zoom damping (scaled by g_menu_fade_amount); was D_80090170 */
extern f32 g_menu_fade_amount; /* was D_80090170 */
extern s8 g_menu0_show_zoom_pct[];         /* menu 0: per-page zoom percent that shows the page objects; was D_80090328 */
extern s8 g_menu0_hide_zoom_pct[];         /* menu 0: per-page zoom percent that hides them again; was D_80090330 */
extern u8 g_menu0_page_objects[][6];      /* menu 0: 2 world objects (ids) per title page, 0xFF = none; was D_80090360 */
extern u8 g_menu1_stop_pages[];         /* menu 1: carousel stop -> main menu page; was D_800AB950 */
extern u8 g_menu_song;           /* last menu sound; was D_800E0EC7 */

// menu_camera_update: the title / main menu camera (object behaviour of the menu camera, arg0 = camera index into
// g_player_views). It is the carousel: left / right (input 4 / 8) slide the camera to the previous / next stop
// (rec->x0 runs 1 -> 0 or 0 -> 1 at rec->x4 per tick, rec->x2B is the target stop), accept (0x10) zooms in towards the
// stop (rec->fade 0 -> 1 at rec->xC, the zoom speed of the stop; the handler shows the page from fade 0.5), back
// (0x20) zooms out. A full zoom into stop 0 toggles title <-> main menu (rec->menu) and restarts at fade 0.99 going
// back out. The eye moves along a path of world points: from the base point (0 / 0x10) to the stop's point and
// on through the point graph g_rail_nodes (5 links per 16-byte node, never back to the previous node), with a
// Catmull-Rom spline (catmull_rom_eval) when the path has 4+ points, linear otherwise; when not zoomed the look-at
// point follows the carousel between the previous, current and next stops. rec->x10 * (x14, x18, x1C) is a decaying
// offset used when the main menu camera jumps to the "back" stop 4 (rec->x2A modes 1 / 2 / 3). Writes
// rec->titlePage (the page shown: the stop, +1 past the slide midpoint; main menu through g_menu1_stop_pages) and x2D,
// and the visibility (+0x80) of the page's world objects and of objects 0xF6 / 0xF7 / 0xF8 (+0x6E).
/* was func_151E73C8 */
void menu_camera_update(s32 arg0) {
    MenuState *rec;
    struct108 *cam;
    s32 base;
    s32 stops;
    u8 *stopPoints;
    f32 *zoomSpeed;
    u16 (*sounds)[2];
    f32 slide;
    f32 zoom;
    f32 rawZoom;
    s8 ids[16];
    f32 x[16];
    f32 y[16];
    f32 z[16];
    u8 *node;
    u8 *cur;
    u8 next;
    s32 count;
    s32 i;
    s32 k;
    s32 segment;
    f32 t;
    f32 bx, by, bz;
    f32 px, py, pz;
    f32 qx, qy, qz;
    s32 jump;
    u8 *obj;
    u8 *objB;

    cam = &g_player_views[arg0];
    if (((MenuState *) g_menu_state)->menu == 0) {
        base = 0;
        stops = 6;
        stopPoints = g_menu0_stop_points;
        zoomSpeed = g_menu0_zoom_speeds;
        sounds = g_menu0_stop_sounds;
    } else {
        base = 0x10;
        stops = 8;
        stopPoints = g_menu1_stop_points;
        zoomSpeed = g_menu1_zoom_speeds;
        sounds = g_menu1_stop_sounds;
    }
    rail_node_position(rail_node_find_by_tag(base), &cam->unk2F8, &cam->unk2FC, &cam->unk300);

    rec = (MenuState *) g_menu_state;
    if (rec->x4 != 0.0f) {
        /* sliding to the neighbouring stop */
        rec->x0 += rec->x4 * (f32) g_frame_ticks;
        if (rec->x0 <= 0.0f) {
            rec->x0 = 0.0f;
            rec->x4 = 0.0f;
        }
        if (rec->x0 >= 1.0f) {
            rec->x0 = 0.0f;
            rec->x4 = 0.0f;
            rec->x2B++;
            if (rec->x2B >= stops) {
                rec->x2B -= stops;
            }
        }
    } else if (rec->xC != 0.0f || rec->fade != 0.0f) {
        /* zoomed in or zooming: back zooms out, accept zooms in */
        if ((rec->input & 0x20) && (rec->menu == 0 || rec->x2B != 0)) {
            rec->xC = -zoomSpeed[rec->x2B];
            music_play_song(sounds[rec->x2B][1], g_menu_song, 0);
            g_menu_song = sounds[rec->x2B][1];
        }
        if (rec->x2A != 0 && rec->menu == 1 && rec->x2B == 0) {
            if (rec->input & 0x20) {
                rec->xC = zoomSpeed[rec->x2B];
            }
        } else if (rec->input & 0x10) {
            rec->xC = zoomSpeed[rec->x2B];
        }
        rec->fade += rec->xC * (f32) g_frame_ticks;
        if (rec->fade >= 1.0f) {
            rec->fade = 1.0f;
            rec->xC = 0.0f;
        } else if (rec->fade < 0.0f) {
            rec->fade = 0.0f;
            rec->xC = 0.0f;
            if (rec->titlePage == 0 && rec->menu == 1 && rec->x44 != 0) {
                rec->x43 = 1;
                rec->x44 = 0;
            }
        }
    } else if (rec->input & 0x10) {
        /* at rest: accept starts the zoom */
        rec->xC = zoomSpeed[rec->x2B];
        music_play_song(sounds[rec->x2B][0], g_menu_song, 0);
        g_menu_song = sounds[rec->x2B][0];
    } else {
        /* at rest: left goes back one stop (sliding 1 -> 0), right / x43 starts the slide to the next */
        if (rec->input & 4) {
            rec->x2B--;
            rec->x0 = 1.0f;
            rec->x4 = -0.05f;
            if (rec->x2B < 0) {
                rec->x2B += stops;
            }
        }
        if ((rec->input & 8) || rec->x43 != 0) {
            rec->x4 = 0.05f;
        }
        rec->x43 = 0;
        if (rec->x2B < 0) {
            rec->x2B += stops;
        }
        if (rec->x2B >= stops) {
            rec->x2B -= stops;
        }
    }

    rawZoom = rec->fade;
    if (rec->menu == 0) {
        rawZoom *= 1.0f - D_eu_80090310[rec->titlePage] * g_menu_fade_amount;
    } else if (rec->titlePage != 0) {
        rawZoom *= 0.6f;
    }
    slide = sinf(rec->x0 * 3.14159f - 1.570795f) * 0.5f + 0.5f;
    zoom = sinf(rawZoom * 3.14159f - 1.570795f) * 0.5f + 0.5f;

    if (((MenuState *) g_menu_state)->menu == 0) {
        /* the title page's world objects appear / disappear at the page's zoom percentages */
        for (i = 0; i < 2; i++) {
            if (g_menu0_page_objects[i][rec->titlePage] != 0xFF) {
                obj = world_record_find(g_menu0_page_objects[i][rec->titlePage]);
                if (obj != NULL) {
                    rec = (MenuState *) g_menu_state;
                    if (rec->xC > 0.0f || g_menu_fade_amount < 1.0f) {
                        if (g_menu0_show_zoom_pct[rec->titlePage] < (s32) (rawZoom * 100.0f)) {
                            *(s32 *) (obj + 0x80) = 1;
                        }
                    } else if (rec->xC < 0.0f) {
                        if (g_menu0_hide_zoom_pct[rec->titlePage] >= (s32) (rawZoom * 100.0f)) {
                            *(s32 *) (obj + 0x80) = 0;
                        }
                    }
                }
            }
        }
    }

    cam->unk3D0->unk25C |= 0x200;
    cam->unk3D0->y_position = 1000.0f;

    if (rawZoom > 0.0f) {
        /* zooming: path from the base point through the stop's point along the point graph */
        ids[0] = rail_node_find_by_tag(base);
        ids[1] = rail_node_find_by_tag(stopPoints[((MenuState *) g_menu_state)->x2B]);
        count = 1;
        node = (u8 *) g_rail_nodes + ids[1] * 16;
        while (node != NULL) {
            cur = node;
            node = NULL;
            for (k = 0; k < 5; k++) {
                next = cur[9 + k];
                if (next != 0xFF && next != ids[count - 1]) {
                    ids[count + 1] = next;
                    count++;
                    k = 5;
                    node = (u8 *) g_rail_nodes + next * 16;
                }
            }
        }
        count++;
        if (count >= 4) {
            t = zoom * ((f32) count - 2.0f);
            segment = (s32) t;
            t -= (f32) segment;
            if (segment >= count - 2) {
                segment--;
                t = 1.0f;
            }
            for (i = 0; i < count; i++) {
                rail_node_position(ids[i], &x[i + 1], &y[i + 1], &z[i + 1]);
            }
            /* end points mirrored for the spline */
            x[0] = x[1] - (x[2] - x[1]);
            y[0] = y[1] - (y[2] - y[1]);
            z[0] = z[1] - (z[2] - z[1]);
            x[count + 1] = (x[count - 1] - x[count]) + x[count];
            y[count + 1] = (y[count - 1] - y[count]) + y[count];
            z[count + 1] = (z[count - 1] - z[count]) + z[count];
            cam->unk2F8 = catmull_rom_eval((s32) x, segment, t);
            cam->unk2FC = catmull_rom_eval((s32) y, segment, t);
            cam->unk300 = catmull_rom_eval((s32) z, segment, t);
            cam->unk2A4 = catmull_rom_eval((s32) x, segment + 1, t);
            cam->unk2A8 = catmull_rom_eval((s32) y, segment + 1, t);
            *(f32 *) &cam->unk2AC = catmull_rom_eval((s32) z, segment + 1, t);
        } else {
            rail_node_position(ids[0], &x[0], &y[0], &z[0]);
            rail_node_position(ids[1], &x[1], &y[1], &z[1]);
            if (count == 3) {
                rail_node_position(ids[2], &x[2], &y[2], &z[2]);
            } else {
                x[2] = (x[1] - x[0]) + x[1];
                y[2] = (y[1] - y[0]) + y[1];
                z[2] = (z[1] - z[0]) + z[1];
            }
            cam->unk2F8 = (x[1] - x[0]) * zoom + x[0];
            cam->unk2FC = (y[1] - y[0]) * zoom + y[0];
            cam->unk300 = (z[1] - z[0]) * zoom + z[0];
            cam->unk2A4 = (x[2] - x[1]) * zoom + x[1];
            cam->unk2A8 = (y[2] - y[1]) * zoom + y[1];
            *(f32 *) &cam->unk2AC = (z[2] - z[1]) * zoom + z[1];
        }
    } else {
        /* not zoomed: look at the carousel (previous, current, next, next + 1 stops) */
        k = ((MenuState *) g_menu_state)->x2B - 1;
        if (k < 0) {
            k += stops;
        }
        for (i = 0; i < 4; i++) {
            rail_node_position(rail_node_find_by_tag(stopPoints[k]), &x[i], &y[i], &z[i]);
            k++;
            if (k >= stops) {
                k -= stops;
            }
        }
        cam->unk2A4 = catmull_rom_eval((s32) x, 0, slide);
        cam->unk2A8 = catmull_rom_eval((s32) y, 0, slide);
        *(f32 *) &cam->unk2AC = catmull_rom_eval((s32) z, 0, slide);
    }

    rec = (MenuState *) g_menu_state;
    if (rec->x2A != 0) {
        /* look away from the eye: mirror the look-at point through it */
        cam->unk2A4 = cam->unk2F8 + (cam->unk2F8 - cam->unk2A4);
        cam->unk2A8 = cam->unk2FC + (cam->unk2FC - cam->unk2A8);
        *(f32 *) &cam->unk2AC = cam->unk300 + (cam->unk300 - *(f32 *) &cam->unk2AC);
    }
    cam->unk2A4 += rec->x10 * rec->x14;
    cam->unk2A8 += rec->x10 * rec->x18;
    *(f32 *) &cam->unk2AC += rec->x10 * rec->x1C;
    if (rec->x2A != 3) {
        rec->x10 *= 0.85f;
    } else {
        rec->x10 = -((0.25f - rec->fade) * 4.0f);
    }

    jump = 0;
    if (rec->menu == 1) {
        /* main menu: back at stop 0 jumps to stop 4 (x2A 1 -> 2 -> 3), with a decaying look-at offset */
        rail_node_position(rail_node_find_by_tag(base), &bx, &by, &bz);
        k = rec->x2B;
        if (k >= stops) {
            k = 0;
        }
        rail_node_position(rail_node_find_by_tag(stopPoints[k]), &px, &py, &pz);
        px -= bx;
        py -= by;
        pz -= bz;
        if (rec->x2A != 0) {
            px = -px;
            py = -py;
            pz = -pz;
        }
        if (rec->fade == 0.0f && (rec->input & 0x20) && rec->x10 < 0.01f && rec->x4 == 0.0f) {
            rec->x2B = 0;
            if (rec->x2D >= 2 && rec->x2D < 7) {
                rec->x2A = 2;
            }
            jump = 1;
            rec->xC = zoomSpeed[rec->x2B];
            music_play_song(sounds[rec->x2B][0], g_menu_song, 0);
            g_menu_song = sounds[rec->x2B][0];
        }
        if (rec->fade < 0.25f && rec->x2A == 1) {
            rec->x2B = 4;
            jump = 2;
            rec->x2A = 0;
        }
        if (rec->fade == 0.0f && rec->x2A == 3) {
            rec->x2B = 4;
            rec->x2A = 0;
            rec->x10 = 0.0f;
        }
        if (jump != 0) {
            rail_node_position(rail_node_find_by_tag(stopPoints[rec->x2B]), &qx, &qy, &qz);
            qx -= bx;
            qy -= by;
            qz -= bz;
            if (rec->x2A != 0) {
                qx = -qx;
                qy = -qy;
                qz = -qz;
            }
            rec->x10 = 1.0f;
            rec->x14 = px - qx;
            rec->x18 = py - qy;
            rec->x1C = pz - qz;
        }
        if (jump == 2) {
            rec->x10 = 0.0f;
            rec->x2B = 0;
            rec->x2A = 3;
        }
    }

    if (rec->fade >= 1.0f && rec->x2B == 0) {
        /* fully zoomed into stop 0: switch title <-> main menu and zoom back out */
        rec->menu = 1 - rec->menu;
        rec->fade = 0.99f;
        if (rec->menu != 0) {
            rec->xC = -g_menu1_zoom_speeds[0];
        } else {
            rec->xC = -g_menu0_zoom_speeds[0];
        }
        if (rec->menu != 0) {
            rec->x2A = 1;
        } else {
            rec->x2A = 0;
        }
    }
    rec->titlePage = rec->x2B;
    if (rec->x0 > 0.5f) {
        rec->titlePage++;
    }
    if (rec->titlePage < 0) {
        rec->titlePage += stops;
    }
    if (rec->titlePage >= stops) {
        rec->titlePage -= stops;
    }
    rec->x2D = rec->titlePage;
    if (rec->menu == 1) {
        rec->titlePage = g_menu1_stop_pages[rec->titlePage];
    }

    cam->unk2BC = cam->unk2A4;
    cam->unk2C0 = cam->unk2A8;
    cam->unk2C4 = *(f32 *) &cam->unk2AC;
    cam->unk390 = 0.0f;
    cam->unk1A4 = 20.0f;
    cam->unk19C = 20.0f;
    cam->unk1A8 = 15.0f;
    cam->unk1A0 = 15.0f;

    obj = world_record_find(0xF8);
    if (obj != NULL) {
        obj[0x6E] = 1;
    }
    obj = world_record_find(0xF6);
    objB = world_record_find(0xF7);
    if (obj != NULL && objB != NULL) {
        if (((MenuState *) g_menu_state)->menu == 0) {
            obj[0x6E] = 0;
            objB[0x6E] = 1;
        } else {
            obj[0x6E] = 1;
            objB[0x6E] = 0;
        }
    }
}
extern f32 g_menu_k_be94; /* was D_800ABE94 */
u8 *world_record_find(u8);
extern u8 g_menu0_page_objects[][6]; /* was D_80090360 */

/* was func_151E856C */
void menu_show_stop_objects(void)
{
  s32 var_s0;
  u8 var_a0;
  u8 *temp_v0;
 var_s0 = 0; if ((!((*((f32 *) (((u8 *) g_menu_state) + 8))) < g_menu_k_be94)) || ((*((s8 *) (((u8 *) g_menu_state) + 0x3E))) != 0)) { do { if ((*((s8 *) (((u8 *) g_menu_state) + 0x3E))) == 0) { var_a0 = g_menu0_page_objects[var_s0][*((s8 *) (((u8 *) g_menu_state) + 0x2C))];
      }
      else
      {
        var_a0 = g_menu0_page_objects[var_s0][0];
      }
      temp_v0 = world_record_find(var_a0);
      var_s0 += 1;
      if (temp_v0 != 0)
      {
        *((s32 *) (((u8 *) temp_v0) + 0x80)) = 2;
      }
    }
    while (var_s0 != 2);
  }
}

extern s8 g_settings_sound_mode; /* was D_800E1019 */

/* was func_151E8648 */
void settings_apply_sound_mode(void) {
    if (g_settings_sound_mode == 2) {
        audio_set_output_mode(1U);
        return;
    }
    if (g_settings_sound_mode == 0) {
        audio_set_output_mode(2U);
        return;
    }
    audio_set_output_mode(4U);
}

// menu_settings_apply_checked: P127 (port): applies the sound mode (settings_apply_sound_mode). The N64 build then sums the code
// words of game_pause_update..menu_reset_and_enter and, on a mismatch (anti-tamper), writes 0 over osSpTaskLoad; the port has
// no MIPS code words there (the sum is 0) and the write lands in the null zone, so the NON_MATCHING build skips it.
/* was func_151E86A4 */
void menu_settings_apply_checked(void) {
    settings_apply_sound_mode();
}

void obj_remove(struct127 *arg0, s32 arg1);
s32 setup_entry_find_by_id(u8);
s32 setup_entry_spawn(u8 *, s32, s32, s32, s32);
void obj_apply_setup_variant(struct127 *, s32);
void obj_start_anim(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6);
void *allocate_memory(s32, s32, s32, s32);
extern s32 g_menu_char_objs;           /* struct127 *[4]: the menu's character object per slot; was D_800E0FD0 */
extern u8 g_menu_characters[][8];       /* characters: +0 f32 scale, +4 s8 y offset, +5 object type, +6 animation; was D_800AB95C */
extern u8 g_menu_char_places[][8];       /* menu slot placement: +0 x, +2 y, +4 z (s16), +6 byte; was D_800ABD3C */

// menu_spawn_character: replaces the menu slot's character object: frees the old one (obj_remove), fills a
// spawn record (setup_entry_find_by_id(slot + 0x10) -> g_setup_entries[], 0x30 bytes) with the character's type (g_menu_characters[ch][5])
// at the slot's position (g_menu_char_places[slot], the next slot's on title page 7, y + the character's offset) and spawns
// it (setup_entry_spawn, 1-based object index). The new object gets flags 3 at 0x2F8, state 7 at +5, the scale at
// 0x14C / 0x150, a 0x1C0 zeroed work block at 0x31C if its +4 is 0 or 0x80, +0x68 = slot + 1 for type 0x3B, the
// character's animation (obj_apply_setup_variant) and obj_start_anim(obj, 0xF, 1.0, 0, 0, 0, 0).
/* was func_151E870C */
void menu_spawn_character(s32 slot, s32 character) {
    struct127 **slotObj = &((struct127 **) &g_menu_char_objs)[slot];
    u8 *spawn;
    u8 *ch;
    s16 *place;
    s32 rec;
    s32 pos;
    s32 type;
    s32 index;
    struct127 *obj;
    void *work;

    if (*slotObj != NULL) {
        obj_remove(*slotObj, 1);
    }
    rec = setup_entry_find_by_id((slot + 0x10) & 0xFF);
    ch = g_menu_characters[character];
    type = ch[5];
    spawn = (u8 *) g_setup_entries + rec * 0x30;
    pos = slot;
    if (*(s8 *) ((u8 *) g_menu_state + 0x2C) == 7) { /* title page */
        pos = slot + 1;
    }
    place = (s16 *) g_menu_char_places[pos];
    spawn[4] = type;
    *(s16 *) (spawn + 6) = place[0];
    *(s16 *) (spawn + 8) = place[1];
    *(s16 *) (spawn + 8) += (s8) ch[4];
    *(s16 *) (spawn + 0xA) = place[2];
    spawn[0xC] = ((u8 *) place)[6];
    if (type == 0x53) {
        spawn[0xD] = 0x24;
    } else {
        spawn[0xD] = 0xE;
    }
    index = setup_entry_spawn(spawn, rec, 0, 0, 0);
    if (index == 0) {
        return;
    }
    obj = &g_objects[index - 1];
    *slotObj = obj;
    *(u16 *) ((u8 *) obj + 0x2F8) |= 3;
    *((u8 *) obj + 5) = 7;
    *(f32 *) ((u8 *) obj + 0x150) = *(f32 *) ch;
    *(f32 *) ((u8 *) obj + 0x14C) = *(f32 *) ch;
    if (*((u8 *) obj + 4) == 0 || *((u8 *) obj + 4) == 0x80) {
        work = allocate_memory(0x1C0, 1, 0, 0);
        *(void **) ((u8 *) obj + 0x31C) = work;
        bzero(work, 0x1C0);
    }
    obj = &g_objects[index - 1];
    if (type == 0x3B) {
        *((u8 *) obj + 0x68) = slot + 1;
    }
    obj_apply_setup_variant(obj, ch[6]);
    obj_start_anim(obj, 0xF, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

extern s32 g_menu_char_objs; /* was D_800E0FD0 */
extern s32 g_menu_char_objs_p1; /* was D_800E0FD4 */
extern s32 g_menu_char_objs_p2; /* was D_800E0FD8 */
extern s32 g_menu_char_objs_p3; /* was D_800E0FDC */
extern s8 g_cutscene_menu_skip_req; /* was D_80090124 */

/* was func_151E8998 */
void menu_char_slots_clear(void) {
    g_menu_char_objs_p1 = 0;
    g_menu_char_objs = 0;
    g_menu_char_objs_p2 = 0;
    g_menu_char_objs_p3 = 0;
    g_cutscene_menu_skip_req = 0;
}
s32 screen_fade_all_active();
extern s16 g_credits_line; /* was D_800E0EB0 */

/* was func_151E89C0 */
void credits_start(void) {
    if (g_game_mode != 8) {
        if (screen_fade_all_active() == 0) {
            g_game_mode_timer = 0;
        }
        if (g_game_mode_timer >= 0xA1) {
            g_hud_fade_alpha = 0;
            g_game_mode = 8;
            g_player_count = 1;
            g_human_player_count = 1;
            g_menu_setup_step = 0;
            g_credits_line = -2;
            g_game_mode_timer = 0;
            g_game_over_pending = 1;
        }
    }
}

void screen_fade_update(void);

/* was func_151E8A64 */
void credits_mode_update(void) {
    screen_fade_update();
    if (g_credits_line == -1 && g_game_mode_timer >= 0x79) {
        g_game_mode = 9;
        g_game_mode_timer = 0;
        g_hud_fade_alpha = 0xFF;
        g_credits_line = 0;
        game_request_transition(6, 0x1D, 0, 0, 1);
        return;
    }
    if (g_credits_line == -2) {
        g_credits_line = 0;
    }
    if (g_game_mode_timer >= 0x173 && g_credits_line >= 0) {
        while (((u8 **)g_text_strings)[g_credits_line][0] != 0x2A) {
            g_credits_line++;
        }
        g_credits_line++;
        if (((u8 **)g_text_strings)[g_credits_line][0] == 0x3D) {
            g_credits_line = -1;
        }
        g_game_mode_timer = 0;
    }
}

void cutscene_scene_load(s32, s32, s32, s32, s32);

/* was func_151E8B94 */
void credits_end_mode_update(void) {
    if (g_credits_line == 0) {
        g_credits_line = -1;
        cutscene_scene_load(0x1D, 6, 0, 0, 0);
    }
    screen_fade_update();
    if (screen_fade_all_active() == 0) {
        g_game_mode_timer = 0;
    }
    if (g_game_mode_timer >= 0x65) {
        menu_state_reset();
        g_menu_setup_step = 0;
        g_game_mode = 1;
        g_game_mode_timer = 0;
        g_chapter_replay = 0;
        game_request_transition(6, 0x21, 0, 0, 1);
    }
}
