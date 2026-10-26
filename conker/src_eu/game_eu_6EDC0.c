#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
Gfx *dbgfont_draw_char(Gfx *gdl, s32 x, s32 y, s32 idx);
s32 dbgfont_char_index(u8 arg0);
s32 text_char_to_glyph(s32 arg0);


extern s32 D_80084CC0;

/* was func_150415B0 */
u8 *dbgfont_setup_dl(u8 *arg0) {
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;

    (*(s32 *)((u8 *)arg0 + 4)) = -1;
    (*(s32 *)((u8 *)arg0 + 0)) = 0xD7000002;
    temp_a0_2 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0;
    temp_a0_3 = temp_a0_2 + 8;
    (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xFCFFFFFF;
    (*(s32 *)((u8 *)temp_a0_3 + 4)) = 0xFFFCF279;
    temp_a0_4 = temp_a0_3 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xEF002C0F;
    (*(s32 *)((u8 *)temp_a0_4 + 4)) = 0x55204C;
    temp_a0_5 = temp_a0_4 + 8;
    (*(s32 *)((u8 *)temp_a0_5 + 0)) = 0xFD90003F;
    (*(s32 **)((u8 *)temp_a0_5 + 4)) = &D_80084CC0;
    temp_a0_6 = temp_a0_5 + 8;
    (*(s32 *)((u8 *)temp_a0_6 + 0)) = 0xFD900000;
    (*(s32 **)((u8 *)temp_a0_6 + 4)) = &D_80084CC0;
    temp_a0_7 = temp_a0_6 + 8;
    (*(s32 *)((u8 *)temp_a0_7 + 4)) = 0x07000000;
    (*(s32 *)((u8 *)temp_a0_7 + 0)) = 0xF5900000;
    temp_a0_8 = temp_a0_7 + 8;
    (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xE6000000;
    (*(s32 *)((u8 *)temp_a0_8 + 4)) = 0;
    temp_a0_9 = temp_a0_8 + 8;
    (*(s32 *)((u8 *)temp_a0_9 + 0)) = 0xF3000000;
    (*(s32 *)((u8 *)temp_a0_9 + 4)) = 0x077FF200;
    temp_a0_10 = temp_a0_9 + 8;
    (*(s32 *)((u8 *)temp_a0_10 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_a0_10 + 4)) = 0;
    temp_a0_11 = temp_a0_10 + 8;
    (*(s32 *)((u8 *)temp_a0_11 + 0)) = 0xF5800800;
    (*(s32 *)((u8 *)temp_a0_11 + 4)) = 0;
    temp_a0 = temp_a0_11 + 8;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xF2000000;
    (*(s32 *)((u8 *)temp_a0 + 4)) = 0xFC1FC;
    return temp_a0 + 8;
}
/* was func_150416EC */
Gfx *dbgfont_draw_string(Gfx *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    Gfx *temp_v0;
    Gfx *var_s2;
    s32 var_s1;
    u8 *var_s0;
    u8 temp_t6;
    u8 var_a0;

    var_s2 = arg0;
    temp_t6 = *arg3;
    var_s0 = arg3;
    var_s1 = arg1;
    var_a0 = temp_t6 & 0xFF;
    if (temp_t6 != 0) {
        do {
            temp_v0 = dbgfont_draw_char(var_s2, var_s1, arg2, dbgfont_char_index(var_a0));
            var_a0 = (*(u8 *)((u8 *)var_s0 + 1));
            var_s2 = temp_v0;
            var_s0 += 1;
            var_s1 += 8;
        } while (var_a0 != 0);
    }
    return var_s2;
}
extern u8 D_80084C60[];
/* was func_15041770 */
s32 dbgfont_char_index(u8 arg0) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_80084C60[i]) {
            return i;
        }
    }
    return i;
}

/* was func_150417F8 */
Gfx *dbgfont_draw_char(Gfx *gdl, s32 x, s32 y, s32 idx) {
    s32 col = idx % 8; // fakematch: locals keep the unfolded mod/sub/div
    s32 s = col * 8;
    s32 row = (idx - col) / 8;

    gSPTextureRectangle(gdl++, x << 2, y << 2, (x + 8) << 2, (y + 12) << 2, 0, s * 32, (row * 3) << 7, 0x400, 0x400);
    return gdl;
}

/* was func_150418D0 */
void text_icon_metrics(s32 arg0, s32 *arg1, s32 *arg2, f32 *arg3, s32 *arg4, f32 *arg5) {
    if ((arg0 >= 0xA8) && (arg0 < 0x100)) {
        *arg5 = 1.0f;
        switch (arg0) {
        case 0xA8:
        case 0xA9:
            *arg1 = 0x20;
            *arg2 = 0x12;
            *arg3 = 3.1f;
            *arg4 = 1;
            return;
        case 0xAA:
        case 0xAB:
        case 0xAC:
        case 0xAD:
            *arg1 = 0x20;
            *arg2 = 0x1B;
            *arg3 = 2.0f;
            *arg4 = 1;
            *arg5 = 0.603f;
            return;
        case 0xAE:
            *arg1 = 0x10;
            *arg2 = 0x11;
            *arg3 = -1.6f;
            *arg4 = 1;
            return;
        case 0xAF:
        case 0xB0:
            *arg1 = 0x2E;
            *arg2 = 0x10;
            *arg3 = 2.0f;
            *arg4 = 1;
            return;
        case 0xB6:
        case 0xB7:
        case 0xB8:
        case 0xB9:
            *arg1 = 0x10;
            *arg2 = 0xC;
            *arg3 = 2.0f;
            *arg4 = 0;
            return;
        case 0xBA:
            *arg4 = 0;
            *arg3 = 0.2f;
            *arg1 = 0x37;
            *arg2 = 0xC;
            return;
        case 0xB1:
            *arg1 = 0x26;
            *arg2 = 0x18;
            *arg3 = 2.0f;
            *arg4 = 1;
            *arg5 = 0.726f;
            return;
        default:
            *arg1 = 0xC;
            *arg2 = 0x10;
            *arg3 = 2.0f;
            *arg4 = 0;
            return;
        }
    } else {
        *arg3 = 0.0f;
        *arg1 = 0;
        *arg2 = 0;
    }
}

extern f32 D_80038400;         /* text scale x (screen units per glyph pixel) */
extern f32 D_80038404;         /* text scale y */
extern u8 *D_80085D20[];       /* [0] font texture (0xE0 bytes per glyph, I8) */
extern u8 *D_80085D24[];       /* [0] glyph metrics: width, height, x offset, y offset (4 bytes per glyph) */
extern Gfx g_text_render_dl[]; /* was D_80085D30 */
extern Gfx D_80087770[];
extern Gfx D_800877A8[];
extern u8 g_render_mode_pairs[];        /* render mode pairs (8 bytes each); was D_800A4EA8 */
extern s32 D_800BEFC4;         /* display list capacity (commands) */
extern u16 D_800CC16E;         /* controller layout bits: picks the icon of the B1 / B2-B5 / BB codes */
extern u8 D_800CC170;          /* current control code (0xFF: none) */
extern u8 D_800CC177;          /* primitive colour last sent: r */
extern u8 D_800CC178[4];       /* g, b, a, flashing flag */
extern u8 D_800CC17C;          /* flashing phase */
extern u8 D_800CC17D;          /* wave flag */
extern u8 D_800CC17E;          /* wave phase */
extern s32 D_800D30C0;
extern s32 D_8009198C[], D_8009199C[], D_800919AC[], D_800919BC[], D_800919CC[], D_800919DC[], D_800919EC[],
    D_800919FC[], D_80091A0C[], D_80091A40[], D_80091A5C[], D_80091A78[], D_80091A94[], D_80091AB0[], D_80091AC0[],
    D_80091AD0[], D_80091AE0[], D_80091AF0[], D_80091B00[], D_80091B14[];
s32 text_char_to_glyph(s32 arg0);
void text_icon_metrics(s32 arg0, s32 *arg1, s32 *arg2, f32 *arg3, s32 *arg4, f32 *arg5);
Gfx *sprite_load_texture(Gfx *, s32 *, s32, void *, s32, s32, s32, s32, s32);
Gfx *sprite_draw_at_screen(Gfx *, void *, f32, f32);

/* the view of the current player (0x180-byte records): +0x14 / +0x18 scale, +0x24..+0x30 clip top / bottom / left / right */
#define TEXT_VIEW() ((u8 *) D_800BE628 + g_cur_view_player * 0x180)
#define VIEW_F(v, off) (*(f32 *) ((v) + (off)))

/*
 * P85: draw len characters of str at (x, y) in colour r, g, b, a with scales scaleX / scaleY (4096 = 1).
 * Characters go through text_char_to_glyph (glyph index). Glyphs are I8 texture rectangles from font 0 (D_80085D20 /
 * D_80085D24), clipped against the view; 0x60 is a space. Codes 0xA1..0xA7 change the colour (A1 reset, A2 red,
 * A3 green, A4 blue, A5 yellow), A6 starts flashing (alpha pulses with D_800CC17C), A7 starts the wave (glyphs
 * bob with D_800CC17E). Codes 0xA8..0xBB pick a button icon (sprite D_8009198C..., frame from D_800CC16E for some)
 * and the next code >= 0xA8 draws it (text_icon_metrics size, sprite_load_texture / sprite_draw_at_screen). Byte 0xBC is skipped
 * (the previous glyph is handled again, as in the original). When the display list is full, a pipe sync is
 * written and the commands of the current character are dropped.
 */
/* was func_15041A9C */
Gfx *text_draw_string(Gfx *gdl, f32 x, f32 y, u8 *str, u8 r, u8 g, u8 b, u8 a, f32 scaleX, f32 scaleY, s32 len) {
    struct {
        u8 pad0[6];
        s16 w;
        s16 h;
        u8 alpha;
        u8 padB[2];
        u8 flags;
        u8 padE[2];
        void *img;
    } icon;
    f32 iconScale;
    f32 iconDy;
    s32 iconFlip;
    u8 *view;
    u8 *metrics;
    u8 *str_p;
    s32 *iconSprite;   /* sprite descriptor for sprite_load_texture */
    Gfx *start;
    f32 flash;
    f32 wave;
    f32 rise;
    f32 dy;
    f32 halfW;
    f32 halfH;
    f32 sx;
    f32 sy;
    s32 iconFrame;
    s32 font;
    s32 draw;
    s32 i;
    s32 w;
    s32 h;
    s32 prevW;
    s32 prevH;
    s32 isx;
    s32 isy;
    s32 dsdx;
    s32 dtdy;
    s32 iy;
    u8 curR;
    u8 curG;
    u8 curB;
    u8 primA;
    u8 waveStep;
    u8 glyph;

    if (str == NULL) {
        return gdl;
    }
    view = TEXT_VIEW();
    scaleX = scaleX * VIEW_F(view, 0x14) * D_80038400;
    scaleY = scaleY * VIEW_F(view, 0x18) * D_80038404;
    prevH = -1;
    prevW = -1;
    w = 0;
    h = 0;
    font = 0; /* only ever 0: the font == 1 test below never passes */
    iconFrame = 0;
    iconSprite = NULL;
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 1, 0, r, g, b, a);
    D_800CC177 = r;
    D_800CC178[0] = g;
    D_800CC178[1] = b;
    D_800CC178[2] = a;
    D_800CC178[3] = 0;
    D_800CC17D = 0;
    D_800CC17E += D_800BE9E4 * 6;
    curR = r;
    curG = g;
    curB = b;
    primA = a;
    waveStep = 0;
    glyph = 0;
    flash = 0.0f;
    wave = 0.0f;
    str_p = str;
    for (i = 0; i < len; i++, str_p++) {
        start = gdl;
        if (D_800CC177 != curR || D_800CC178[0] != curG || D_800CC178[1] != curB || D_800CC178[2] != a) {
            D_800CC177 = curR;
            D_800CC178[0] = curG;
            D_800CC178[1] = curB;
            D_800CC178[2] = a;
            primA = a;
            gDPSetPrimColor(gdl++, 1, 0, D_800CC177, D_800CC178[0], D_800CC178[1], D_800CC178[2]);
        }
        if (D_800CC178[3] != 0) {
            primA = (u32) ((f32) (D_800CC178[2] - 127) * flash + 127.0f);
            if (D_800CC178[2] < primA) {
                primA = D_800CC178[2];
            }
            gDPSetPrimColor(gdl++, 1, 0, D_800CC177, D_800CC178[0], D_800CC178[1], primA);
        }
        if (D_800CC17D != 0) {
            wave = (cosf((u8) (D_800CC17E + waveStep) * (3.1415927f / 128.0f)) + 1.0f) * 1.5f;
            waveStep += 0x4E;
        }
        if (*str_p == 0xBC) {
            D_800CC170 = 0xFF;
        } else {
            font = 0;
            glyph = text_char_to_glyph(*str_p);
            D_800CC170 = (glyph >= 0xA1) ? glyph : 0xFF;
        }
        switch (D_800CC170) {
            case 0xA1: /* back to the caller's colour, no effects */
                D_800CC178[3] = 0;
                curR = r;
                curG = g;
                curB = b;
                D_800CC17D = 0;
                break;
            case 0xA2:
                curR = 0xFF;
                curG = 0;
                curB = 0;
                break;
            case 0xA3:
                curR = 0;
                curG = 0xFF;
                curB = 0;
                break;
            case 0xA4:
                curR = 0;
                curG = 0;
                curB = 0xFF;
                break;
            case 0xA5:
                curR = 0xFF;
                curG = 0xFF;
                curB = 0;
                break;
            case 0xA6: /* flashing */
                D_800CC178[3] = 1;
                D_800CC17C += D_800BE9E4 * 8;
                flash = (cosf(D_800CC17C * (3.1415927f / 128.0f)) + 1.0f) * 0.5f;
                break;
            case 0xA7: /* wave */
                D_800CC17D = 1;
                break;
            case 0xA8: iconSprite = D_8009198C; iconFrame = 0; break;
            case 0xA9: iconSprite = D_8009199C; iconFrame = 0; break;
            case 0xAA: iconSprite = D_800919DC; iconFrame = 0; break;
            case 0xAB: iconSprite = D_800919EC; iconFrame = 0; break;
            case 0xAC: iconSprite = D_800919FC; iconFrame = 0; break;
            case 0xAD: iconSprite = D_80091A0C; iconFrame = 0; break;
            case 0xAE: iconSprite = D_800919AC; iconFrame = 0; break;
            case 0xAF: iconSprite = D_800919BC; iconFrame = 0; break;
            case 0xB0: iconSprite = D_800919CC; iconFrame = 0; break;
            case 0xB1: iconSprite = D_80091A40; iconFrame = (D_800CC16E >> 8) % 10; break;
            case 0xB2: iconSprite = D_80091A5C; iconFrame = (D_800CC16E >> 8) & 3; break;
            case 0xB3: iconSprite = D_80091A94; iconFrame = (D_800CC16E >> 8) & 3; break;
            case 0xB4: iconSprite = D_80091A78; iconFrame = (D_800CC16E >> 8) & 3; break;
            case 0xB5: iconSprite = D_80091AB0; iconFrame = (D_800CC16E >> 8) & 3; break;
            case 0xB6: iconSprite = D_80091AC0; iconFrame = 0; break;
            case 0xB7: iconSprite = D_80091AD0; iconFrame = 0; break;
            case 0xB8: iconSprite = D_80091AE0; iconFrame = 0; break;
            case 0xB9: iconSprite = D_80091AF0; iconFrame = 0; break;
            case 0xBA: iconSprite = D_80091B00; iconFrame = 0; break;
            case 0xBB: iconSprite = D_80091B14; iconFrame = (D_800CC16E >> 10) & 1; break;
        }
        gDPPipeSync(gdl++);

        draw = 1;
        if (font != 1) {
            draw = 0;
            if (glyph == 0x60) {
                x += 4.0f * D_80038400; /* space */
            } else if (glyph >= 0xA1 && glyph < 0xA8) {
                /* colour / effect code: nothing drawn */
            } else if (glyph < 0xA8) {
                draw = 1;
            } else {
                /* button icon, centred on the pen position */
                text_icon_metrics(glyph, &w, &h, &iconDy, &iconFlip, &iconScale);
                if (D_800CC17D != 0) {
                    iconDy += wave;
                }
                view = TEXT_VIEW();
                halfW = VIEW_F(view, 0x14) * ((f32) (w >> 1) * iconScale) * D_80038400;
                x += halfW;
                halfH = VIEW_F(view, 0x18) * ((f32) (h >> 1) * iconScale) * D_80038404;
                y += halfH;
                iconFrame <<= 8;
                icon.w = scaleX * iconScale;
                icon.h = scaleY * iconScale;
                icon.flags = 0;
                icon.alpha = primA;
                gSPDisplayList(gdl++, D_80087770);
                g_sprite_keep_prim_colour = 1;
                gDPSetOtherMode(gdl++, 0x2C3F, ((u32 *) g_render_mode_pairs)[0x32] | ((u32 *) g_render_mode_pairs)[0x33] | 4);
                if (iconFlip == 0) {
                    gDPSetCombine(gdl++, 0xFFB3FF, 0xFF65FEFF);
                }
                gdl = sprite_load_texture(gdl, iconSprite, iconFrame, &icon, 0, 0, 0, 2, 3);
                if (D_800D30C0 != (s32) 0x80000000) {
                    gdl = sprite_draw_at_screen(gdl, &icon, x, y - iconDy);
                }
                gSPDisplayList(gdl++, D_800877A8);
                gSPDisplayList(gdl++, g_text_render_dl);
                g_sprite_keep_prim_colour = 0;
                y -= halfH;
                x += halfW * 0.5f;
            }
        }

        if (draw) {
            sx = scaleX * (1.0f / 4096.0f);
            sy = scaleY * (1.0f / 4096.0f);
            metrics = D_80085D24[font] + glyph * 4;
            w = metrics[0];
            h = metrics[1];
            rise = 0.0f;
            if (D_800CC17D != 0) {
                rise += wave;
            }
            x += (f32) metrics[2] * D_80038400 * sx;
            dy = ((f32) metrics[3] - rise) * D_80038404;
            y += dy * sy;
            view = TEXT_VIEW();
            if (VIEW_F(view, 0x2C) <= x + (f32) w * D_80038400 && x < VIEW_F(view, 0x30) &&
                VIEW_F(view, 0x24) <= y + (f32) h * D_80038404 && y < VIEW_F(view, 0x28)) {
                isx = scaleX;
                isy = scaleY;
                dsdx = 0x400000 / isx;
                dtdy = 0x400000 / isy;
                if (w != prevW || h != prevH) {
                    gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_8b, (w + 7) >> 3, 0, 3, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP,
                               0, 0);
                    gDPSetTileSize(gdl++, 3, 0, 0, (((w + 7) & 0xFFF8) - 1) << 2, h << 2);
                }
                gDPSetTextureImage(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 1, D_80085D20[font] + glyph * 0xE0);
                gDPLoadBlock(gdl++, 1, 0, 0, ((((w + 7) & 0xFFF8) * (h + 1) + 1) >> 1) - 1, 0);
                iy = y;
                gSPScisTextureRectangle(gdl++, x * 4.0f, iy << 2, x * 4.0f + (f32) ((w * isx) / 4096) * 4.0f,
                                        ((s32) (f32) ((h * isy) / 4096) + iy) << 2, 3, 0,
                                        ((-(s32) ((y - (f32) iy) * 32.0f) << 12) + 0x20000) / isy, dsdx, dtdy);
                metrics = D_80085D24[font] + glyph * 4;
                dy = ((f32) metrics[3] - rise) * D_80038404;
            }
            y -= dy * sx; /* (sic) x scale for y, y scale for x */
            x += (f32) (metrics[0] - 1) * D_80038400 * sy;
        }

        prevW = w;
        prevH = h;
        if (gdl != NULL && gdl - D_800BEDE8[D_800BE9C0] > D_800BEFC4) {
            gDPPipeSync(gdl);
            return start;
        }
    }
    return gdl;
}

extern f32 D_80038400;
extern f32 D_80038404;
extern u8 *D_80085D24[]; /* [0] glyph metrics (4 bytes per glyph) */

/* was func_15042BC4 */
void text_measure_string(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    struct {
        f32 u54;
        s32 u58;
        f32 u5C;
        s32 u60;
        s32 u64;
        s32 u68;
    } sp;
    s32 temp_a0;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_s5;
    s32 var_t0;
    u8 *var_s2;
    u8 var_a0;
    u8 var_v0;
    u8 *temp_v0_4;
    u8 *temp_v0_5;

    if (arg0 != NULL) {
        *arg1 = 0;
        *arg2 = 0;
        *arg3 = 0;
        var_s5 = 0;
        var_s0 = 0;
        if (*arg0 == 0) {
            *arg2 += 0xC;
        }
        var_s2 = arg0;
        if (*arg0 != 0) {
            var_a0 = *var_s2;
            var_v0 = var_a0;
            do {
                if (var_v0 == 0xBC) {
                    var_s2 += 2;
                } else {
                    temp_v0 = text_char_to_glyph(var_a0);
                    temp_v1 = temp_v0 & 0xFF;
                    temp_s3 = temp_v0 & 0xFF;
                    var_t0 = 0;
                    if (temp_v1 == 0x60) {
                        *arg1 += 4;
                        if (var_s0 < 0xC) {
                            var_s0 = 0xC;
                        }
                    } else if ((temp_v1 < 0xA1) || (temp_v1 >= 0xA8)) {
                        if ((temp_v1 >= 0xA8) && (temp_v1 < 0x100)) {
                            sp.u68 = 0;
                            text_icon_metrics(temp_s3, &sp.u64, &sp.u60, &sp.u5C, &sp.u58, &sp.u54);
                            var_t0 = sp.u68;
                            *arg1 = (s32) ((f32) *arg1 + ((f32) sp.u64 * sp.u54));
                            temp_v0_2 = (s32) ((f32) (s32) ((f32) sp.u60 * sp.u54) - sp.u5C) + 1;
                            if (var_s0 < temp_v0_2) {
                                var_s0 = temp_v0_2;
                            }
                            if ((f32) *arg3 < sp.u5C) {
                                *arg3 = (s32) sp.u5C;
                            }
                        } else if (temp_v1 < 0xA1) {
                            if (*var_s2 == 0xA) {
                                temp_v0_3 = *arg1;
                                if (var_s5 < temp_v0_3) {
                                    var_s5 = temp_v0_3;
                                }
                                *arg1 = 0;
                                if (var_s0 < 0xC) {
                                    var_s0 = 0xC;
                                }
                                *arg2 += var_s0;
                                var_s0 = 0;
                            } else {
                                var_t0 = 1;
                            }
                        }
                    }
                    var_s2 += 1;
                    if (var_t0 != 0) {
                        temp_v1_2 = temp_s3 * 4;
                        temp_v0_4 = D_80085D24[0] + temp_v1_2;
                        *arg1 = (*arg1 + (*(u8 *)((u8 *)temp_v0_4 + 0)) + (*(u8 *)((u8 *)temp_v0_4 + 2))) - 1;
                        temp_v0_5 = D_80085D24[0] + temp_v1_2;
                        temp_a0 = (*(u8 *)((u8 *)temp_v0_5 + 3)) + (*(u8 *)((u8 *)temp_v0_5 + 1));
                        if (temp_a0 >= var_s0) {
                            var_s0 = temp_a0;
                        }
                    }
                }
                var_a0 = *var_s2;
                var_v0 = var_a0;
            } while (var_a0 != 0);
        }
        if (*arg1 < var_s5) {
            *arg1 = var_s5;
        }
        *arg2 += var_s0;
        *arg1 = (s32) ((f32) *arg1 * D_80038400);
        *arg2 = (s32) ((f32) *arg2 * D_80038404);
        *arg3 = (s32) ((f32) *arg3 * D_80038400);
    }
}
extern u8 D_80085CC0;
extern u8 D_80085CC1;
extern u8 D_80085CC2;
extern s32 D_80085CC3;

/* was func_15042F30 */
s32 text_char_to_glyph(s32 arg0) {
    s32 *var_v0_2;
    s32 temp_t6;
    s32 var_a0;
    s32 var_v0;

    temp_t6 = arg0 & 0xFF;
    if ((temp_t6 >= 0x61) && (temp_t6 < 0x7B)) {
        var_v0 = (temp_t6 - 0x20) & 0xFF;
    } else {
        var_v0 = temp_t6 & 0xFF;
    }
    if (temp_t6 == 0x20) {
        return 0x60;
    }
    if (var_v0 == D_80085CC0) {
        return 0;
    }
    if (var_v0 == D_80085CC1) {
        return 1;
    }
    var_v0_2 = &D_80085CC3;
    var_a0 = 3;
    if (var_v0 == D_80085CC2) {
        return 2;
    }
loop_13:
    if (var_v0 == (*(u8 *)((u8 *)var_v0_2 + 0))) {
        return var_a0;
    }
    if (var_v0 == (*(u8 *)((u8 *)var_v0_2 + 1))) {
        return var_a0 + 1;
    }
    if (var_v0 == (*(u8 *)((u8 *)var_v0_2 + 2))) {
        return var_a0 + 2;
    }
    if (var_v0 == (*(u8 *)((u8 *)var_v0_2 + 3))) {
        return var_a0 + 3;
    }
    var_a0 += 4;
    var_v0_2 = (s32 *)((u8 *)var_v0_2 + (4));
    if (var_a0 == 0x5F) {
        return temp_t6;
    }
    goto loop_13;
}