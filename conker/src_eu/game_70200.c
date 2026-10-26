#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include <stdarg.h>
// hoisted declarations of the NON_MATCHING bodies
Gfx *text_queue_draw(Gfx *arg0);
void text_queue_vprintf(s32 fmtArg, s32 *args);
u8 *allocate_memory(s32, s32, s32, s32);
int game_sprintf(char *s, const char *fmt, ...);
extern u8 g_text_bg_r; /* was D_800CC18C */
extern u8 g_text_bg_g; /* was D_800CC18D */
extern u8 g_text_bg_b; /* was D_800CC18E */
extern u8 g_text_bg_a; /* was D_800CC18F */
extern s32 g_text_queue_tail; /* was D_800CC188 */
extern char g_text_fmt_float[]; /* was D_80086060 */
extern char g_text_fmt_spec_buf[]; /* was D_80086064 */
extern char g_text_str_empty_a[]; /* was D_80098F40 */
extern char g_text_str_empty_b[]; /* was D_80098F44 */


/* was func_15042D50 */
void text_queue_reset(void) {
    g_text_queue_head = 0;
    text_queue_draw(0);
}

/* was func_15042D78 */
void text_set_flags(u8 arg0) {
    g_text_flags = arg0;
}

/* was func_15042D94 */
void text_printf_at(s32 arg0, s32 arg1, u8 arg2, s32 arg3, ...) {
    va_list ap;
    s32 args[16];
    s32 i;

    g_text_flags = arg2;
    g_text_pos_x = arg0;
    g_text_pos_y = arg1;
    va_start(ap, arg3);
    for (i = 0; i < 16; i++) {
        args[i] = va_arg(ap, s32);
    }
    text_queue_vprintf(arg3, args);
}
/* was func_15042E3C */
void text_printf(s32 arg0, ...) {
    va_list ap;
    s32 args[16];
    s32 i;

    va_start(ap, arg0);
    for (i = 0; i < 16; i++) {
        args[i] = va_arg(ap, s32);
    }
    text_queue_vprintf(arg0, args);
}
/* Text queue printf (used by text_printf_at / text_printf): one 0x5C node per line ('\n' splits) appended to the
 * g_text_queue_head list (tail g_text_queue_tail), text at +0x1C. Conversions are copied to g_text_fmt_spec_buf and handed to sprintf
 * (game_sprintf): d/x/X/s take an int word; f/F take a float pointer and use g_text_fmt_float = "%s%s" + spec (two empty
 * strings). "#c" puts the next argument in +0xD (icon). Position/scale/colour come from the D_800CBD6x/7x state. */
/* was func_15042ECC */
void text_queue_vprintf(s32 fmtArg, s32 *args) {
    u8 *fmt = (u8 *)fmtArg;
    s32 argi = 0;
    u8 *node;
    char *out;
    s32 done;
    s32 n;
    u8 c;

    if (*fmt != 0) {
        do {
            node = allocate_memory(0x5C, 1, 0, 1);
            if (node == NULL) {
                return;
            }
            *(s32 *)(node + 0x18) = 0;
            done = 0;
            out = (char *)node + 0x1C;
            if (g_text_queue_tail == 0) {
                g_text_queue_head = (s32)node;
            } else {
                *(u8 **)(g_text_queue_tail + 0x18) = node;
            }
            node[0xD] = 0;
            do {
                c = *fmt;
                if (c == '%') {
                    g_text_fmt_spec_buf[0] = '%';
                    fmt++;
                    n = 1;
                    do {
                        c = *fmt;
                        g_text_fmt_spec_buf[n + 1] = 0;
                        g_text_fmt_spec_buf[n] = c;
                        switch (c) {
                            case '%':
                                *out++ = *fmt;
                                *out = 0;
                                n = 0;
                                break;
                            case 'X':
                            case 'd':
                            case 'x':
                            case 's':
                                game_sprintf(out, g_text_fmt_spec_buf, args[argi++]);
                                while (*out != 0) {
                                    out++;
                                }
                                n = 0;
                                break;
                            case 'F':
                            case 'f':
                                game_sprintf(out, g_text_fmt_float, g_text_str_empty_a, g_text_str_empty_b, (f64) *(f32 *)args[argi++]);
                                while (*out != 0) {
                                    out++;
                                }
                                n = 0;
                                break;
                            default:
                                n++;
                                break;
                        }
                        fmt++;
                    } while (n != 0);
                } else if (c == '#') {
                    node[0xD] = args[argi++];
                    fmt += 2;
                } else if (c == '\n') {
                    fmt++;
                    done = 1;
                } else if (c == 0) {
                    done = 1;
                } else {
                    *out++ = c;
                    *out = 0;
                    fmt++;
                }
            } while (!done);
            node[0xC] = g_text_flags;
            *(u32 *)node = g_text_anchor_obj;
            if (g_text_anchor_obj != 0) {
                node[0xC] = g_text_flags | 1;
                *(s16 *)(node + 0xA) = g_text_anchor_yoff;
                if (g_human_player_count >= 2) {
                    *(f32 *)(node + 4) = g_text_scale + g_text_scale;
                } else {
                    *(f32 *)(node + 4) = g_text_scale;
                }
            } else {
                *(s16 *)(node + 8) = g_text_pos_x;
                *(s16 *)(node + 0xA) = g_text_pos_y;
                *(f32 *)(node + 4) = g_text_scale;
            }
            node[0xE] = g_text_color_r;
            node[0xF] = g_text_color_g;
            node[0x10] = g_text_color_b;
            node[0x11] = g_text_color_a;
            node[0x12] = g_text_bg_r;
            node[0x13] = g_text_bg_g;
            node[0x14] = g_text_bg_b;
            node[0x15] = g_text_bg_a;
            g_text_queue_tail = (s32)node;
            if (node[0xD] != 0) {
                node[0xE] = 0xFF;
                node[0xF] = 0xFF;
                node[0x10] = 0xFF;
            } else {
                g_text_pos_y += 0xB;
            }
        } while (*fmt != 0);
    }
    g_text_anchor_obj = 0;
}
/* was func_150432BC */
void text_set_scale(f32 arg0) {
    g_text_scale = arg0;
}

/* was func_150432CC */
void text_set_box(s32 arg0, s32 arg1) {
    g_text_flags = g_text_flags | 1;
    g_text_flags = g_text_flags;
    g_text_anchor_yoff = arg1;
    g_text_anchor_obj = arg0;
}

/* was func_150432FC */
void text_set_pos(s16 arg0, s16 arg1) {
    g_text_pos_x = arg0;
    g_text_pos_y = arg1;
}

/* was func_1504332C */
void text_set_color(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    g_text_color_r = arg0;
    g_text_color_g = arg1;
    g_text_color_b = arg2;
    g_text_color_a = arg3;
}

/* P13: difftest EQUIV on random inputs only (seeds 2, 3: 15 completed trials); runs with a poked single text/icon item
 * segfault Unicorn (exit 139), so the icon path is UNVERIFIED by difftest: runtime check in the browser.
 * On-screen text and icon queue flush (P13, hand C). Draws every queued item of g_text_queue_head (linked through
 * 0x18, freed with heap_free after drawing) and resets the queue state. Item: 0x00 world anchor (projected
 * with sprite_project_point), 0x04 f32 scale, 0x08/0x0A s16 x/y, 0x0C flags (0x40: x/y already in screen units,
 * 0x80: drop shadow, == 1: centred), 0x0D icon (0 = text), 0x0E..0x11 RGBA, 0x15 measure, 0x1C the string.
 * Icons come from the 8-byte table g_text_icon_table (w, h, scale/128, flags, texture) and go through the sprite
 * descriptor g_hud_sprite_desc and hud_image_draw; g_text_icon_animated's texture animates with the frame counter g_text_icon_anim_frame. */
extern s32 g_text_icon_anim_frame; /* was D_80086070 */
extern u8 g_text_render_dl[]; /* was D_80085D30 */
extern u8 g_text_icon_table[]; /* was D_80085D70 */
extern u8 g_text_icon_animated[]; /* was D_80085E38 */
extern u8 g_hud_sprite_desc[]; /* was D_80090410 */
extern f32 g_hud_scale_x; /* was D_800901BC */
extern f32 g_hud_scale_y; /* was D_800901C0 */
extern f32 g_text_anchor_proj_param; /* was D_80099014 */
extern s32 g_frame_count; /* was D_800BEDCC */
extern u8 g_text_bg_r; /* was D_800CC18C */
extern u8 g_text_bg_g; /* was D_800CC18D */
extern u8 g_text_bg_b; /* was D_800CC18E */
extern u8 g_text_bg_a; /* was D_800CC18F */
extern s32 g_text_queue_tail; /* was D_800CC188 */
s32 sprite_project_point(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 arg7);
void text_measure_string(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
Gfx *text_draw_string(Gfx *arg0, f32 arg1, f32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, s32 argA);
Gfx *hud_image_draw(Gfx *, void *, s32, s32, s32, s32, f32, s32);
void heap_free(s32);

/* was func_15043384 */
Gfx *text_queue_draw(Gfx *arg0) {
    Gfx *gdl = arg0;
    u8 *item;
    u8 *next;
    u8 *icon;
    u8 *anchor;
    s32 visible;
    s32 shadow;
    s32 w, h, d;
    s32 v;
    f32 sx, sy, sz, sw;
    f32 scale;

    g_text_icon_anim_frame++;
    item = (u8 *)g_text_queue_head;
    if (item != NULL) {
        gdl->words.w0 = 0xDE000000;
        gdl->words.w1 = (u32)g_text_render_dl;
        gdl++;
        gdl->words.w0 = 0xEF002C3F;
        gdl->words.w1 = 0x504240;
        gdl++;
        do {
            if (item[0xD] == 0) {
                visible = 1;
                shadow = 0;
                if (item[0xC] & 0x40) {
                    item[0xC] &= 0xBF;
                } else {
                    *(s16 *)(item + 0x8) = (s32)((f32) * (s16 *)(item + 0x8) * g_hud_scale_x);
                    *(s16 *)(item + 0xA) = (s32)((f32) * (s16 *)(item + 0xA) * g_hud_scale_y);
                }
                if (item[0xC] & 0x80) {
                    shadow = 1;
                    item[0xC] &= 0x7F;
                }
                anchor = *(u8 **)item;
                if (anchor != NULL) {
                    g_cur_view_player = 0;
                    visible = sprite_project_point(*(f32 *)(anchor + 0x14),
                                            *(f32 *)(anchor + 0x18) + (f32) * (s16 *)(item + 0xA),
                                            *(f32 *)(anchor + 0x1C), &sx, &sy, &sz, &sw, g_text_anchor_proj_param);
                    if (visible != 0) {
                        *(s16 *)(item + 0x8) = (s32)sx;
                        *(s16 *)(item + 0xA) = (s32)sy;
                    }
                }
                if (item[0xC] == 1 || item[0x15] != 0) {
                    text_measure_string(item + 0x1C, &w, &h, &d);
                    w = (s32)((f32)w * *(f32 *)(item + 0x4));
                }
                if (item[0xC] == 1) {
                    *(s16 *)(item + 0x8) -= w >> 1;
                }
                if (visible != 0) {
                    scale = *(f32 *)(item + 0x4) * 4096.0f;
                    if (shadow) {
                        gdl = text_draw_string(gdl, (f32)(*(s16 *)(item + 0x8) + 1), (f32)(*(s16 *)(item + 0xA) + 1),
                                            item + 0x1C, 0, 0, 0, item[0x11], scale, scale,
                                            strlen((char *)(item + 0x1C)));
                    }
                    gdl = text_draw_string(gdl, (f32) * (s16 *)(item + 0x8), (f32) * (s16 *)(item + 0xA), item + 0x1C,
                                        item[0xE], item[0xF], item[0x10], item[0x11], scale, scale,
                                        strlen((char *)(item + 0x1C)));
                }
                gdl->words.w0 = 0xE7000000;
                gdl->words.w1 = 0;
                gdl++;
                next = *(u8 **)(item + 0x18);
            } else {
                icon = g_text_icon_table + (item[0xD] - 1) * 8;
                gdl->words.w0 = 0xFC12D225;
                gdl->words.w1 = 0xFFA7FFFF;
                gdl++;
                scale = (f32)(u32)icon[2] * 0.0078125f;
                if (icon[3] & 2) {
                    *(s16 *)(g_hud_sprite_desc + 6) = 0x10;
                    *(s16 *)(g_hud_sprite_desc + 8) = 0x10;
                }
                if (icon[3] & 1) {
                    gdl->words.w0 = 0xE7000000;
                    gdl->words.w1 = 0;
                    gdl++;
                    gdl->words.w0 = 0xFB000000;
                    gdl->words.w1 = (item[0xE] << 24) | (item[0xF] << 16) | (item[0x10] << 8) | item[0x11];
                    gdl++;
                    *(s32 *)g_hud_sprite_desc = *(s32 *)(icon - 4);
                    gdl = hud_image_draw(gdl, g_hud_sprite_desc, *(s16 *)(item + 0x8), *(s16 *)(item + 0xA), icon[-8],
                                        icon[-7], scale, 0);
                    v = (g_frame_count * 2) & 0x7F;
                    if (v >= 0x40) {
                        v = 0x7F - v;
                    }
                    v = (s32)((u32)item[0x11] * (u32)(v * 3 + 0x3F)) >> 8;
                    if (v >= 0x100) {
                        v = 0xFF;
                    }
                    item[0x11] = v;
                }
                gdl->words.w0 = 0xE7000000;
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0xFB000000;
                gdl->words.w1 = (item[0xE] << 24) | (item[0xF] << 16) | (item[0x10] << 8) | item[0x11];
                gdl++;
                *(s32 *)g_hud_sprite_desc = *(s32 *)(icon + 4);
                if (icon == g_text_icon_animated) {
                    v = (g_text_icon_anim_frame >> 1) % 10;
                    if (v >= 6) {
                        v = 10 - v;
                    }
                    *(s32 *)g_hud_sprite_desc = *(s32 *)(icon + 4) + v;
                }
                gdl = hud_image_draw(gdl, g_hud_sprite_desc, *(s16 *)(item + 0x8), *(s16 *)(item + 0xA), icon[0], icon[1],
                                    scale, 0);
                gdl->words.w0 = 0xDE000000;
                gdl->words.w1 = (u32)g_text_render_dl;
                gdl++;
                gdl->words.w0 = 0xEF002C3F;
                gdl->words.w1 = 0x504240;
                gdl++;
                if (icon[3] & 2) {
                    *(s16 *)(g_hud_sprite_desc + 6) = 0x20;
                    *(s16 *)(g_hud_sprite_desc + 8) = 0x20;
                }
                next = *(u8 **)(item + 0x18);
            }
            heap_free((s32)item);
            item = next;
        } while (item != NULL);
        gdl->words.w0 = 0xE7000000;
        gdl->words.w1 = 0;
        gdl++;
    }
    g_text_color_r = 0xFF;
    g_text_color_g = 0xFF;
    g_text_color_b = 0xFF;
    g_text_color_a = 0xFF;
    g_text_bg_r = 0;
    g_text_bg_g = 0;
    g_text_bg_b = 0;
    g_text_bg_a = 0x80;
    g_text_pos_x = 10;
    g_text_pos_y = 10;
    g_text_scale = 1.0f;
    g_text_flags = 0;
    g_text_queue_head = 0;
    g_text_queue_tail = 0;
    g_text_anchor_obj = 0;
    return gdl;
}
/* was func_15043A00 */
void ring_buffer_init(struct105 *arg0, s32 arg1, s32 arg2) {
    if (arg0 != 0) {
        arg0->unk0 = arg1; // are these structs?
        arg0->unk4 = arg2;
        arg0->unkC = 0;
        arg0->unk8 = 0;
    }
}

// something with memcpy
/* was func_15043A20 */
s32 ring_buffer_write_wrap(u8 *buf, s32 size, s32 pos, u8 *src, s32 len) {
    s32 n;

    while (len != 0) {
        if (size < pos + len) {
            n = size - pos;
        } else {
            n = len;
        }
        memcpy(buf + pos, src, n);
        pos += n;
        src += n;
        len -= n;
        if (pos >= size) {
            pos = 0;
        }
    }
    return pos;
}
/* was func_15043AC8 */
s32 ring_buffer_read_wrap(u8 *buf, s32 size, s32 pos, u8 *dst, s32 len) {
    s32 n;

    while (len != 0) {
        if (size < pos + len) {
            n = size - pos;
        } else {
            n = len;
        }
        memcpy(dst, buf + pos, n);
        pos += n;
        dst += n;
        len -= n;
        if (pos >= size) {
            pos = 0;
        }
    }
    return pos;
}

/* was func_15043B70 */
s32 ring_buffer_advance(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n;

    while (arg3 != 0) {
        if (arg1 < arg2 + arg3) {
            n = arg1 - arg2;
        } else {
            n = arg3;
        }
        arg2 += n;
        arg3 -= n;
        if (arg2 >= arg1) {
            arg2 = 0;
        }
    }
    return arg2;
}
// text_queue_put: appends a record (u32 length padded to 4, then the bytes) to the ring buffer q (g_mp3_text_queue:
// +0 buffer, +4 size, +8 read, +C write); returns 1 when it does not fit, else 0 (also for no data). The padded
// length is copied from src too (up to 3 bytes past len, as on N64).
/* was func_15043BB8 */
s32 ring_buffer_put_record(struct105 *q, u8 *src, s32 len) {
    s32 total;
    s32 pos;

    if (len == 0) {
        return 0;
    }
    if (src != NULL) {
        total = (len + 4 + 3) & ~3;
        len = total;
        if (q->unkC < q->unk8) {
            if (!(q->unkC + total < q->unk8)) {
                return 1;
            }
        } else if (!(q->unkC + len - q->unk4 < q->unk8)) {
            return 1;
        }
        len -= 4;
        pos = ring_buffer_write_wrap((u8 *) q->unk0, q->unk4, q->unkC, (u8 *) &len, 4);
        q->unkC = ring_buffer_write_wrap((u8 *) q->unk0, q->unk4, pos, src, len);
    }
    return 0;
}

// text_queue_get: takes the next record from the ring buffer q (see ring_buffer_put_record) into dst (at most max - 1 bytes
// plus a 0 when it is longer; the rest is skipped); returns the record's length, 0 when the queue is empty.
/* was func_15043CA4 */
s32 ring_buffer_get_record(struct105 *q, u8 *dst, s32 max) {
    s32 len = 0;
    s32 pos = q->unk8;

    if (pos == q->unkC) {
        return 0;
    }
    pos = ring_buffer_read_wrap((u8 *) q->unk0, q->unk4, pos, (u8 *) &len, 4);
    if (max < len) {
        max--;
        pos = ring_buffer_read_wrap((u8 *) q->unk0, q->unk4, pos, dst, max);
        dst[max] = 0;
        pos = ring_buffer_advance(q->unk0, q->unk4, pos, len - max);
    } else if (len != 0) {
        pos = ring_buffer_read_wrap((u8 *) q->unk0, q->unk4, pos, dst, len);
    }
    q->unk8 = pos;
    return len;
}
