#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include <stdarg.h>
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
Gfx *func_15043384(Gfx *arg0);
#endif


void func_15042D50(void) {
    D_800CBD64 = 0;
    func_15043384(0);
}

void func_15042D78(u8 arg0) {
    D_800CBD74 = arg0;
}

void func_15042D94(s32 arg0, s32 arg1, u8 arg2, s32 arg3, ...) {
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
    func_15042ECC(arg3, args);
}
void func_15042E3C(s32 arg0, ...) {
    va_list ap;
    s32 args[16];
    s32 i;

    va_start(ap, arg0);
    for (i = 0; i < 16; i++) {
        args[i] = va_arg(ap, s32);
    }
    func_15042ECC(arg0, args);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15042ECC.s")

void func_150432BC(f32 arg0) {
    D_800CBD80 = arg0;
}

void func_150432CC(s32 arg0, s32 arg1) {
    D_800CBD74 = D_800CBD74 | 1;
    D_800CBD74 = D_800CBD74;
    D_800CBD7C = arg1;
    D_800CBD78 = arg0;
}

void func_150432FC(s16 arg0, s16 arg1) {
    D_800CBD70 = arg0;
    D_800CBD72 = arg1;
}

void func_1504332C(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_800CBD60 = arg0;
    D_800CBD61 = arg1;
    D_800CBD62 = arg2;
    D_800CBD63 = arg3;
}

#ifdef NON_MATCHING
/* P13: difftest EQUIV on random inputs only (seeds 2, 3: 15 completed trials); runs with a poked single text/icon item
 * segfault Unicorn (exit 139), so the icon path is UNVERIFIED by difftest: runtime check in the browser.
 * On-screen text and icon queue flush (P13, hand C). Draws every queued item of D_800CBD64 (linked through
 * 0x18, freed with func_10004074 after drawing) and resets the queue state. Item: 0x00 world anchor (projected
 * with func_15095A4C), 0x04 f32 scale, 0x08/0x0A s16 x/y, 0x0C flags (0x40: x/y already in screen units,
 * 0x80: drop shadow, == 1: centred), 0x0D icon (0 = text), 0x0E..0x11 RGBA, 0x15 measure, 0x1C the string.
 * Icons come from the 8-byte table D_80085D70 (w, h, scale/128, flags, texture) and go through the sprite
 * descriptor D_80090410 and func_151EDBE8; D_80085E38's texture animates with the frame counter D_80086070. */
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
s32 func_15095A4C(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 arg7);
void func_15042BC4(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
Gfx *func_15041A9C(Gfx *arg0, f32 arg1, f32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, s32 argA);
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
void func_10004074(s32);

Gfx *func_15043384(Gfx *arg0) {
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
                    visible = func_15095A4C(*(f32 *)(anchor + 0x14),
                                            *(f32 *)(anchor + 0x18) + (f32) * (s16 *)(item + 0xA),
                                            *(f32 *)(anchor + 0x1C), &sx, &sy, &sz, &sw, D_80099014);
                    if (visible != 0) {
                        *(s16 *)(item + 0x8) = (s32)sx;
                        *(s16 *)(item + 0xA) = (s32)sy;
                    }
                }
                if (item[0xC] == 1 || item[0x15] != 0) {
                    func_15042BC4(item + 0x1C, &w, &h, &d);
                    w = (s32)((f32)w * *(f32 *)(item + 0x4));
                }
                if (item[0xC] == 1) {
                    *(s16 *)(item + 0x8) -= w >> 1;
                }
                if (visible != 0) {
                    scale = *(f32 *)(item + 0x4) * 4096.0f;
                    if (shadow) {
                        gdl = func_15041A9C(gdl, (f32)(*(s16 *)(item + 0x8) + 1), (f32)(*(s16 *)(item + 0xA) + 1),
                                            item + 0x1C, 0, 0, 0, item[0x11], scale, scale,
                                            strlen((char *)(item + 0x1C)));
                    }
                    gdl = func_15041A9C(gdl, (f32) * (s16 *)(item + 0x8), (f32) * (s16 *)(item + 0xA), item + 0x1C,
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
                    gdl = func_151EDBE8(gdl, D_80090410, *(s16 *)(item + 0x8), *(s16 *)(item + 0xA), icon[-8],
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
                gdl = func_151EDBE8(gdl, D_80090410, *(s16 *)(item + 0x8), *(s16 *)(item + 0xA), icon[0], icon[1],
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
            func_10004074((s32)item);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043384.s")
#endif
void func_15043A00(struct105 *arg0, s32 arg1, s32 arg2) {
    if (arg0 != 0) {
        arg0->unk0 = arg1; // are these structs?
        arg0->unk4 = arg2;
        arg0->unkC = 0;
        arg0->unk8 = 0;
    }
}

// something with memcpy
s32 func_15043A20(u8 *buf, s32 size, s32 pos, u8 *src, s32 len) {
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
s32 func_15043AC8(u8 *buf, s32 size, s32 pos, u8 *dst, s32 len) {
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

s32 func_15043B70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043BB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043CA4.s")
