#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include <stdarg.h>
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
Gfx *text_queue_draw(Gfx *arg0);
void text_queue_vprintf(s32 fmtArg, s32 *args);
u8 *allocate_memory(s32, s32, s32, s32);
int game_sprintf(char *s, const char *fmt, ...);
extern u8 D_800CC18C;
extern u8 D_800CC18D;
extern u8 D_800CC18E;
extern u8 D_800CC18F;
extern s32 D_800CC188;
extern char D_80086060[];
extern char D_80086064[];
extern char D_80098F40[];
extern char D_80098F44[];
#endif


/* was func_15042D50 */
void text_queue_reset(void) {
    D_800CBD64 = 0;
    text_queue_draw(0);
}

/* was func_15042D78 */
void text_set_flags(u8 arg0) {
    D_800CBD74 = arg0;
}

/* was func_15042D94 */
void text_printf_at(s32 arg0, s32 arg1, u8 arg2, s32 arg3, ...) {
    va_list ap;
    s32 args[16];
    s32 i;

    D_800CBD74 = arg2;
    D_800CBD70 = arg0;
    D_800CBD72 = arg1;
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
#ifdef NON_MATCHING
/* Text queue printf (used by text_printf_at / text_printf): one 0x5C node per line ('\n' splits) appended to the
 * D_800CBD64 list (tail D_800CC188), text at +0x1C. Conversions are copied to D_80086064 and handed to sprintf
 * (game_sprintf): d/x/X/s take an int word; f/F take a float pointer and use D_80086060 = "%s%s" + spec (two empty
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
            if (D_800CC188 == 0) {
                D_800CBD64 = (s32)node;
            } else {
                *(u8 **)(D_800CC188 + 0x18) = node;
            }
            node[0xD] = 0;
            do {
                c = *fmt;
                if (c == '%') {
                    D_80086064[0] = '%';
                    fmt++;
                    n = 1;
                    do {
                        c = *fmt;
                        D_80086064[n + 1] = 0;
                        D_80086064[n] = c;
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
                                game_sprintf(out, D_80086064, args[argi++]);
                                while (*out != 0) {
                                    out++;
                                }
                                n = 0;
                                break;
                            case 'F':
                            case 'f':
                                game_sprintf(out, D_80086060, D_80098F40, D_80098F44, (f64) *(f32 *)args[argi++]);
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
            node[0xC] = D_800CBD74;
            *(u32 *)node = D_800CBD78;
            if (D_800CBD78 != 0) {
                node[0xC] = D_800CBD74 | 1;
                *(s16 *)(node + 0xA) = D_800CBD7C;
                if (D_80090130 >= 2) {
                    *(f32 *)(node + 4) = D_800CBD80 + D_800CBD80;
                } else {
                    *(f32 *)(node + 4) = D_800CBD80;
                }
            } else {
                *(s16 *)(node + 8) = D_800CBD70;
                *(s16 *)(node + 0xA) = D_800CBD72;
                *(f32 *)(node + 4) = D_800CBD80;
            }
            node[0xE] = D_800CBD60;
            node[0xF] = D_800CBD61;
            node[0x10] = D_800CBD62;
            node[0x11] = D_800CBD63;
            node[0x12] = D_800CC18C;
            node[0x13] = D_800CC18D;
            node[0x14] = D_800CC18E;
            node[0x15] = D_800CC18F;
            D_800CC188 = (s32)node;
            if (node[0xD] != 0) {
                node[0xE] = 0xFF;
                node[0xF] = 0xFF;
                node[0x10] = 0xFF;
            } else {
                D_800CBD72 += 0xB;
            }
        } while (*fmt != 0);
    }
    D_800CBD78 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/text_queue_vprintf.s")
#endif
/* was func_150432BC */
void text_set_scale(f32 arg0) {
    D_800CBD80 = arg0;
}

/* was func_150432CC */
void text_set_box(s32 arg0, s32 arg1) {
    D_800CBD74 = D_800CBD74 | 1;
    D_800CBD74 = D_800CBD74;
    D_800CBD7C = arg1;
    D_800CBD78 = arg0;
}

/* was func_150432FC */
void text_set_pos(s16 arg0, s16 arg1) {
    D_800CBD70 = arg0;
    D_800CBD72 = arg1;
}

/* was func_1504332C */
void text_set_color(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_800CBD60 = arg0;
    D_800CBD61 = arg1;
    D_800CBD62 = arg2;
    D_800CBD63 = arg3;
}

#ifdef NON_MATCHING
/* P13: difftest EQUIV on random inputs only (seeds 2, 3: 15 completed trials); runs with a poked single text/icon item
 * segfault Unicorn (exit 139), so the icon path is UNVERIFIED by difftest: runtime check in the browser.
 * On-screen text and icon queue flush (P13, hand C). Draws every queued item of D_800CBD64 (linked through
 * 0x18, freed with heap_free after drawing) and resets the queue state. Item: 0x00 world anchor (projected
 * with sprite_project_point), 0x04 f32 scale, 0x08/0x0A s16 x/y, 0x0C flags (0x40: x/y already in screen units,
 * 0x80: drop shadow, == 1: centred), 0x0D icon (0 = text), 0x0E..0x11 RGBA, 0x15 measure, 0x1C the string.
 * Icons come from the 8-byte table D_80085D70 (w, h, scale/128, flags, texture) and go through the sprite
 * descriptor D_80090410 and hud_image_draw; D_80085E38's texture animates with the frame counter D_80086070. */
extern s32 D_80086070;
extern u8 D_80085D30[];
extern u8 D_80085D70[];
extern u8 D_80085E38[];
extern u8 D_80090410[];
extern f32 D_800901BC;
extern f32 D_800901C0;
extern f32 D_80099014;
extern s32 D_800BEDCC;
extern u8 D_800CC18C;
extern u8 D_800CC18D;
extern u8 D_800CC18E;
extern u8 D_800CC18F;
extern s32 D_800CC188;
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

    D_80086070++;
    item = (u8 *)D_800CBD64;
    if (item != NULL) {
        gdl->words.w0 = 0xDE000000;
        gdl->words.w1 = (u32)D_80085D30;
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
                    *(s16 *)(item + 0x8) = (s32)((f32) * (s16 *)(item + 0x8) * D_800901BC);
                    *(s16 *)(item + 0xA) = (s32)((f32) * (s16 *)(item + 0xA) * D_800901C0);
                }
                if (item[0xC] & 0x80) {
                    shadow = 1;
                    item[0xC] &= 0x7F;
                }
                anchor = *(u8 **)item;
                if (anchor != NULL) {
                    D_80082FA4 = 0;
                    visible = sprite_project_point(*(f32 *)(anchor + 0x14),
                                            *(f32 *)(anchor + 0x18) + (f32) * (s16 *)(item + 0xA),
                                            *(f32 *)(anchor + 0x1C), &sx, &sy, &sz, &sw, D_80099014);
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
                icon = D_80085D70 + (item[0xD] - 1) * 8;
                gdl->words.w0 = 0xFC12D225;
                gdl->words.w1 = 0xFFA7FFFF;
                gdl++;
                scale = (f32)(u32)icon[2] * 0.0078125f;
                if (icon[3] & 2) {
                    *(s16 *)(D_80090410 + 6) = 0x10;
                    *(s16 *)(D_80090410 + 8) = 0x10;
                }
                if (icon[3] & 1) {
                    gdl->words.w0 = 0xE7000000;
                    gdl->words.w1 = 0;
                    gdl++;
                    gdl->words.w0 = 0xFB000000;
                    gdl->words.w1 = (item[0xE] << 24) | (item[0xF] << 16) | (item[0x10] << 8) | item[0x11];
                    gdl++;
                    *(s32 *)D_80090410 = *(s32 *)(icon - 4);
                    gdl = hud_image_draw(gdl, D_80090410, *(s16 *)(item + 0x8), *(s16 *)(item + 0xA), icon[-8],
                                        icon[-7], scale, 0);
                    v = (D_800BEDCC * 2) & 0x7F;
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
                *(s32 *)D_80090410 = *(s32 *)(icon + 4);
                if (icon == D_80085E38) {
                    v = (D_80086070 >> 1) % 10;
                    if (v >= 6) {
                        v = 10 - v;
                    }
                    *(s32 *)D_80090410 = *(s32 *)(icon + 4) + v;
                }
                gdl = hud_image_draw(gdl, D_80090410, *(s16 *)(item + 0x8), *(s16 *)(item + 0xA), icon[0], icon[1],
                                    scale, 0);
                gdl->words.w0 = 0xDE000000;
                gdl->words.w1 = (u32)D_80085D30;
                gdl++;
                gdl->words.w0 = 0xEF002C3F;
                gdl->words.w1 = 0x504240;
                gdl++;
                if (icon[3] & 2) {
                    *(s16 *)(D_80090410 + 6) = 0x20;
                    *(s16 *)(D_80090410 + 8) = 0x20;
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
    D_800CBD60 = 0xFF;
    D_800CBD61 = 0xFF;
    D_800CBD62 = 0xFF;
    D_800CBD63 = 0xFF;
    D_800CC18C = 0;
    D_800CC18D = 0;
    D_800CC18E = 0;
    D_800CC18F = 0x80;
    D_800CBD70 = 10;
    D_800CBD72 = 10;
    D_800CBD80 = 1.0f;
    D_800CBD74 = 0;
    D_800CBD64 = 0;
    D_800CC188 = 0;
    D_800CBD78 = 0;
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/text_queue_draw.s")
#endif
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
#ifdef NON_MATCHING
// text_queue_put: appends a record (u32 length padded to 4, then the bytes) to the ring buffer q (D_800427A0:
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/ring_buffer_put_record.s")
#endif

#ifdef NON_MATCHING
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/ring_buffer_get_record.s")
#endif
