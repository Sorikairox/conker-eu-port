extern f32 D_80038400;         /* text scale x (screen units per glyph pixel) */
extern f32 D_80038404;         /* text scale y */
extern u8 *D_80085D20[];       /* [0] font texture (0xE0 bytes per glyph, I8) */
extern u8 *D_80085D24[];       /* [0] glyph metrics: width, height, x offset, y offset (4 bytes per glyph) */
extern Gfx D_80085D30[];
extern Gfx D_80087770[];
extern Gfx D_800877A8[];
extern u8 D_800A4EA8[];        /* render mode pairs (8 bytes each) */
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
s32 func_15042F30(s32 arg0);
void func_150418D0(s32 arg0, s32 *arg1, s32 *arg2, f32 *arg3, s32 *arg4, f32 *arg5);
Gfx *func_15095380(Gfx *, s32 *, s32, void *, s32, s32, s32, s32, s32);
Gfx *func_15095E58(Gfx *, void *, f32, f32);

/* the view of the current player (0x180-byte records): +0x14 / +0x18 scale, +0x24..+0x30 clip top / bottom / left / right */
#define TEXT_VIEW() ((u8 *) D_800BE628 + D_80082FA4 * 0x180)
#define VIEW_F(v, off) (*(f32 *) ((v) + (off)))

/*
 * P85: draw len characters of str at (x, y) in colour r, g, b, a with scales scaleX / scaleY (4096 = 1).
 * Characters go through func_15042F30 (glyph index). Glyphs are I8 texture rectangles from font 0 (D_80085D20 /
 * D_80085D24), clipped against the view; 0x60 is a space. Codes 0xA1..0xA7 change the colour (A1 reset, A2 red,
 * A3 green, A4 blue, A5 yellow), A6 starts flashing (alpha pulses with D_800CC17C), A7 starts the wave (glyphs
 * bob with D_800CC17E). Codes 0xA8..0xBB pick a button icon (sprite D_8009198C..., frame from D_800CC16E for some)
 * and the next code >= 0xA8 draws it (func_150418D0 size, func_15095380 / func_15095E58). Byte 0xBC is skipped
 * (the previous glyph is handled again, as in the original). When the display list is full, a pipe sync is
 * written and the commands of the current character are dropped.
 */
Gfx *func_15041A9C(Gfx *gdl, f32 x, f32 y, u8 *str, u8 r, u8 g, u8 b, u8 a, f32 scaleX, f32 scaleY, s32 len) {
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
    s32 *iconSprite;   /* sprite descriptor for func_15095380 */
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
            glyph = func_15042F30(*str_p);
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
                func_150418D0(glyph, &w, &h, &iconDy, &iconFlip, &iconScale);
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
                D_800D31CB = 1;
                gDPSetOtherMode(gdl++, 0x2C3F, ((u32 *) D_800A4EA8)[0x32] | ((u32 *) D_800A4EA8)[0x33] | 4);
                if (iconFlip == 0) {
                    gDPSetCombine(gdl++, 0xFFB3FF, 0xFF65FEFF);
                }
                gdl = func_15095380(gdl, iconSprite, iconFrame, &icon, 0, 0, 0, 2, 3);
                if (D_800D30C0 != (s32) 0x80000000) {
                    gdl = func_15095E58(gdl, &icon, x, y - iconDy);
                }
                gSPDisplayList(gdl++, D_800877A8);
                gSPDisplayList(gdl++, D_80085D30);
                D_800D31CB = 0;
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
