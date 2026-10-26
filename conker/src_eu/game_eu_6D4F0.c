#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s16 g_select_menu_stick_delay; /* was D_80084814 */

/* was func_1503FCE0 */
void select_menu_read_stick(s16 arg0, s16 *arg1, s16 *arg2) {
    s16 temp_v1;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 var_v0;
    s16 var_v0_2;
    s8 temp_a0;
    s8 temp_v1_2;
    u8 *temp_v0;

    temp_v1 = g_select_menu_stick_delay - 1;
    temp_v0 = *(s32 *)(*g_cont_frame + (arg0 * 4));
    if (temp_v1 != 0) {
        g_select_menu_stick_delay = temp_v1;
        *arg1 = 0;
        *arg2 = 0;
        return;
    }
    temp_a0 = (*(s8 *)((u8 *)temp_v0 + 2));
    g_select_menu_stick_delay = 5;
    if ((temp_a0 < -0x14) || (temp_a0 >= 0x15)) {
        *arg1 = (s16) temp_a0;
    } else {
        *arg1 = 0;
    }
    temp_v1_2 = (*(s8 *)((u8 *)temp_v0 + 3));
    if ((temp_v1_2 < -0x14) || (temp_v1_2 >= 0x15)) {
        *arg2 = (s16) temp_v1_2;
    } else {
        *arg2 = 0;
    }
    (*(s8 *)((u8 *)temp_v0 + 2)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 3)) = 0;
    temp_v1_3 = *arg1;
    if (temp_v1_3 < -1) {
        *arg1 = -1;
    } else {
        var_v0 = temp_v1_3;
        if (temp_v1_3 >= 2) {
            var_v0 = 1;
        }
        *arg1 = var_v0;
    }
    temp_v1_4 = *arg2;
    if (temp_v1_4 < -1) {
        *arg2 = -1;
        return;
    }
    var_v0_2 = temp_v1_4;
    if (temp_v1_4 >= 2) {
        var_v0_2 = 1;
    }
    *arg2 = var_v0_2;
}
/* was func_1503FB08 */
void select_menu_reset(void) {
    g_select_menu_scroll_dir = 0;
    g_select_menu_scroll = 0.0f;
    g_select_menu_reset_timer = 0;
    g_select_menu_blink_timer = 30;
    g_select_menu_blink_on = 0;
}

s32 event_table_count(void);
s32 event_table_find_by_word4(s32);
u8 *event_table_get_block(s32);
s32 event_table_get_word4(s32);
void text_measure_string(u8 *, s32 *, s32 *, s32 *);
Gfx *text_draw_string(Gfx *, f32, f32, u8 *, s32, s32, s32, s32, f32, f32, s32);
s32 strlen(const char *);
extern u16 g_pad_pressed;     /* buttons pressed this frame; was D_800BEB30 */
extern u8 g_select_menu_sel;      /* selected entry; was D_80084828 */
extern u8 g_text_render_dl[];    /* text display list; was D_80085D30 */
extern u8 g_str_select_locked[];    /* text shown while the menu is locked; was D_80098CE0 */
extern u8 g_str_select_marker[];    /* marker line drawn above some entries; was D_80098CF4 */
extern u8 g_str_select_blink[];    /* blink text of the selected entry; was D_80098CF8 */
extern u8 g_str_select_empty[];    /* empty text; was D_8008482C */

// menu_list_update_draw: scrolling text menu of event_table_count() entries (19 rows shown, the selected entry
// g_select_menu_sel in the middle). `select` buttons pick the selected entry when it is unlocked (bit event_table_find_by_word4(i + 1) of
// g_save_progress_bits) and return its id; `cancel` or B (0x4000) return -1. Up (4) / down (8) or the stick (select_menu_read_stick)
// start a scroll (g_select_menu_scroll_dir = -1 / 1) that moves the offset g_select_menu_scroll by 1.25 per tick up to +-11, then steps the
// selection by 1 (3 with Z held). Pressing 0x30 together locks the menu for 60 ticks (level_state_clear /
// level_state_init, g_select_menu_reset_timer) and shows g_str_select_locked on every row. Rows fade in / out at the edges (alpha 64 per
// row); the selected row is red (blinking g_str_select_blink every 30 ticks, g_select_menu_blink_timer / g_select_menu_blink_on), others white;
// entries with event_table_get_word4 < 0 get the marker g_str_select_marker above them. Returns -2 while no choice is made.
/* was func_1503FE30 */
s32 select_menu_update_draw(Gfx **gfxp, u16 cancel, u16 select) {
    u16 buttons;
    s32 count;
    u8 visible;
    u8 idx;
    u8 i;
    u8 alpha;
    s32 id;
    s32 a;
    s32 b;
    s32 step;
    s32 row;
    s32 y;
    s32 w, h, d;
    s32 w2, h2;
    s32 hSel;
    s16 stickX, stickY;
    u8 *text;
    f32 top;
    f32 x;
    f32 yy;
    f32 off;
    Gfx *g;

    buttons = g_pad_pressed;
    alpha = 0;
    i = 0;
    row = 0;
    w = 0;
    h = 0;
    count = event_table_count();
    g = *gfxp;
    *gfxp = g + 1;
    ((s32 *) g)[0] = 0xDE000000; /* gSPDisplayList(g_text_render_dl) */
    ((s32 *) g)[1] = (s32) g_text_render_dl;
    visible = (count < 19) ? count : 19;
    y = 1;

    if (g_select_menu_reset_timer == 0 && (buttons & 0x20) && (buttons & 0x10)) {
        g_select_menu_reset_timer = 60;
        level_state_clear();
        level_state_init();
    }
    if (g_select_menu_reset_timer != 0) {
        buttons = 0;
        g_select_menu_reset_timer -= g_frame_ticks;
        if (g_select_menu_reset_timer <= 0) {
            g_select_menu_reset_timer = 0;
        }
    }

    if (buttons & select) {
        a = event_table_find_by_word4(g_select_menu_sel + 1);
        b = event_table_find_by_word4(g_select_menu_sel + 1);
        if (!(((u8 *) g_save_progress_bits)[a >> 3] & (1 << (b & 7)))) {
            return event_table_find_by_word4(g_select_menu_sel + 1);
        }
    }
    if ((buttons & cancel) || (buttons & 0x4000)) {
        return -1;
    }

    select_menu_read_stick(0, &stickX, &stickY);
    if (g_select_menu_scroll_dir != 0) {
        g_select_menu_scroll += 1.25f * (s32) (g_select_menu_scroll_dir * g_frame_ticks);
        if (g_select_menu_scroll < -11.0f) {
            g_select_menu_scroll = -11.0f;
        } else {
            g_select_menu_scroll = (11.0f < g_select_menu_scroll) ? 11.0f : g_select_menu_scroll;
        }
        if (11.0f <= fabsf(g_select_menu_scroll)) {
            step = 1;
            if (**(u16 **) g_cont_frame[0] & 0x2000) {
                step = 3;
            }
            if (g_select_menu_scroll_dir == 1) {
                g_select_menu_sel -= step;
                if (count < g_select_menu_sel) {
                    g_select_menu_sel += count;
                }
            } else if (g_select_menu_scroll_dir == -1) {
                g_select_menu_sel = (g_select_menu_sel + step) % count;
            }
            g_select_menu_scroll_dir = 0;
            g_select_menu_scroll = 0.0f;
        }
    } else if (buttons & 4) {
        g_select_menu_scroll_dir = -1;
        g_select_menu_scroll = 0.0f;
    } else if (stickY == -1) {
        g_select_menu_scroll_dir = -1;
        g_select_menu_scroll = 0.0f;
    } else if ((buttons & 8) || stickY == 1) {
        g_select_menu_scroll_dir = 1;
        g_select_menu_scroll = 0.0f;
    }

    /* first row: the selected entry minus half the rows, wrapped */
    idx = g_select_menu_sel - ((visible - 1) >> 1);
    if (count < idx) {
        idx += count;
    }
    *(s8 *) &g_select_menu_blink_timer -= g_frame_ticks;
    if (*(s8 *) &g_select_menu_blink_timer <= 0) {
        *(s8 *) &g_select_menu_blink_timer = 30;
        g_select_menu_blink_on ^= 1;
    }

    do {
        id = event_table_find_by_word4(idx + 1);
        if (g_select_menu_reset_timer != 0) {
            text = g_str_select_locked;
            text_measure_string(text, &w, &h, &d);
        } else {
            text_measure_string(event_table_get_block(id), &w, &h, &d);
            if (((u8 *) g_save_progress_bits)[id >> 3] & (1 << (id & 7))) {
                if (g_select_menu_sel == idx) {
                    text = g_select_menu_blink_on ? g_str_select_blink : event_table_get_block(id);
                    text_measure_string(text, &w, &hSel, &d);
                } else {
                    text = event_table_get_block(id);
                }
            } else {
                text = event_table_get_block(id);
            }
        }
        x = g_framebuffer_width * 0.5f - (w >> 1);
        top = y + 1.0f;
        yy = top + g_select_menu_scroll;
        if (event_table_get_word4(id) < 0) {
            text_measure_string(g_str_select_marker, &w2, &h2, &d);
            off = g_select_menu_scroll;
            *gfxp = text_draw_string(*gfxp, g_framebuffer_width * 0.5f - (w2 >> 1), top + off, g_str_select_marker, 0xFF, 0xFF, 0xFF, alpha,
                                  4096.0f, 4096.0f, strlen((char *) g_str_select_marker));
            y += h2;
            yy += h2;
        }
        if (row < 3) {
            alpha = row * 64 + 64;
        } else if (visible - 3 < row) {
            alpha = (visible - row) << 6;
        } else {
            alpha = 0xFF;
        }
        if (text == NULL) {
            text = g_str_select_empty;
        }
        if (g_select_menu_reset_timer == 0 && (g_select_menu_sel != idx || g_select_menu_scroll_dir != 0)) {
            *gfxp = text_draw_string(*gfxp, x, yy, text, 0xFF, 0xFF, 0xFF, alpha, 4096.0f, 4096.0f, strlen((char *) text));
        } else {
            *gfxp = text_draw_string(*gfxp, x, yy, text, 0xFF, 0, 0, alpha, 4096.0f, 4096.0f, strlen((char *) text));
        }
        idx++;
        y += h;
        row++;
        idx %= count;
        i++;
    } while (i < visible);
    return -2;
}
