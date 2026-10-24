s32 func_1510D66C(s32, s32 *, s32, s32);
Gfx *func_15091534(Gfx *gdl, s32 sheet, u8 *ready);
Gfx *func_15093B58(Gfx *, s32, s16 *, s32, s32);
extern Gfx D_80087730[];   /* 2D HUD setup display list */
extern u8 D_80087750[4];   /* initial bar lengths (all 0) */
extern u8 D_80087754[];    /* icon sheet: t of each icon row, in 32nds */
extern u8 D_8008775C[];    /* icon sheet: layout table index of each icon row's height */
extern u8 D_80087764[];    /* placing digits: s column (k & 3), in 32nds */
extern u8 D_80087768[];    /* placing digits: t row (k >> 2), in 32nds */
extern u16 D_80090160;     /* multiplayer HUD element bits */
extern u16 D_8009015C;
extern s8 D_800E0EF0[];    /* team of each view */
extern s8 D_800E1017;      /* number of laps */
extern char D_8009E0B8[];  /* "%d" */
extern char D_8009E0BC[];  /* "(%s)" */
extern char D_8009E0C4[];  /* "%s" */
extern char D_8009E0C8[];  /* "lap %d/%d" */
extern f32 D_8009E23C;     /* map world -> screen scale (0.013) */
extern f32 D_8009E240;     /* map scale factor in hi-res (1.56) */
extern f32 D_8009E244;     /* map centre y offset (3.4) */
extern f32 D_8009E248;     /* map centre x offset (3.6) */

// mp_hud_draw: P208: the multiplayer HUD overlay (func_1508FD38 when D_800BE616 is set). The layout table
// (33 entries, scaled by the hi-res factor D_800901BC, texture step `scale`) is the same as func_1508FD38's.
// D_80090160 selects the parts, each drawn per view (D_80082FA0 + 1 views, skipped when D_80087270[p] == 10;
// view rectangle D_800BE628: y top 0x24, y bottom 0x28, x left 0x2C, x right 0x30):
//   0x002: placing digit (sheet 0xD16, cell from func_150859AC(p, 3)) at the top left;
//   0x400 / 0x800: score (D_80090174 s16 table at 0x46) / "(team name)" text at the top centre;
//   0x010: two lives bars (sheet 0xD18 cell 0x620 / 0xA0, lengths from func_150859AC(p, 4));
//   0x004: status icons at the top right: icon by the player's state (sheet 0xD18 via func_15091534), and in
//          interaction state 0x1E the vehicle / weapon icons (sheet 0xD19) with a red ammo / fuel bar;
//   the "on fire" counter (sheet 0xD15) for players in state 0x26 / 0x3A, one icon per unit of 0x19A;
//   0x080 (race, D_80087640 records): best / current lap times and "lap n/m";
//   0x1000: the overview map (texture 0xCF3 / 0xCF4) with a dot per player (green = self, red = players,
//          white = other objects with a team);
//   0x020: the radar (func_15093B58, not big).
// Returns the advanced display list.
Gfx *func_150918EC(Gfx *gdl) {
    struct_eu_BE628 *view;
    struct127 *obj;
    struct_eu_80087640 *race;
    u8 *st;
    u8 bars[4];
    u8 bar_mode, fire, loaded, ready;
    s16 table[33];
    s32 scale, width, p, i, k, tex, x, y, right, row, icon, count, toff, trow, shift, s, t, ix, iy, h, dy, len;
    s32 wi, hi, size, dot, mx, my, r, cx, cy;
    s8 lap, laps;
    f32 f, zoom, fx, fy;

    for (i = 0; i < 4; i++) {
        bars[i] = D_80087750[i];
    }
    bar_mode = 0;
    fire = 0;
    width = ((struct_eu_BE628 *)D_800BE628)->unk30 - ((struct_eu_BE628 *)D_800BE628)->unk2C;
    gSPDisplayList(gdl++, D_80087730);
    func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);

    f = D_800901BC;
    scale = 0x400;
    if (f == 1.0f) {
        table[0] = 0;
        for (i = 1; i < 33; i++) {
            table[i] = i;
        }
    } else {
        scale = 1024.0f / f;
        for (i = 0; i < 33; i++) {
            table[i] = (f32)i * f;
        }
    }

    /* placing digit, score and team name */
    if (D_80090160 & 0xC02) {
        loaded = 0;
        ready = 0;
        for (p = 0; p <= D_80082FA0; p++) {
            if (D_80087270[p] == 10) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            y = (f32)table[6] + view->unk24;
            x = view->unk2C;
            if (D_80090160 & 2) {
                if (!loaded) {
                    loaded = 1;
                    tex = func_1510D66C(0xD16, NULL, 3, 0);
                    if (tex != 0x80000000) {
                        gdl->words.w0 = 0xFD180000; /* texture image CI8 */
                        gdl->words.w1 = tex;
                        gdl++;
                        gdl->words.w0 = 0xF5180000;
                        gdl->words.w1 = 0x07094250;
                        gdl++;
                        gDPLoadSync(gdl++);
                        gdl->words.w0 = 0xF3000000;
                        gdl->words.w1 = 0x073FF000;
                        gdl++;
                        gDPPipeSync(gdl++);
                        gdl->words.w0 = 0xF5181000;
                        gdl->words.w1 = 0x00094250;
                        gdl++;
                        gdl->words.w0 = 0xF2000000;
                        gdl->words.w1 = 0x0007C07C;
                        gdl++;
                        ready = 1;
                    }
                    gdl->words.w0 = 0xEF002C3F; /* other modes */
                    gdl->words.w1 = 0x00504244;
                    gdl++;
                    gDPPipeSync(gdl++);
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0x80);
                }
                ix = table[5] + x;
                k = func_150859AC((s16)p, 3);
                s = D_80087764[k & 3] << 5;
                t = D_80087768[k >> 2] << 5;
                if (ready) {
                    gSPScisTextureRectangle(gdl++, ix * 4, y * 4, (table[5] + ix) * 4, (table[7] + y) * 4,
                                            G_TX_RENDERTILE, s, t, scale, scale);
                }
            }
            if (D_80090160 & 0x400) {
                ix = (width >> 1) + x - 8;
                if (D_800901BC != 1.0f) {
                    ix -= 8;
                }
                func_15042D94(ix, y, 0x41, (s32)D_8009E0B8, *(s16 *)(D_80090174 + 0x46 + p * 2));
            }
            if (D_80090160 & 0x800) {
                ix = (width >> 1) + x + 16;
                if (D_800901BC != 1.0f) {
                    ix += 16;
                }
                func_15042D94(ix, y, 0x41, (s32)D_8009E0BC, ((u8 **)D_800E1008)[8 + D_800E0EF0[p]]);
            }
        }
    }

    /* state icons and lives bars */
    if (D_80090160 & 0x14) {
        loaded = 0;
        ready = 0;
        for (p = 0; p <= D_80082FA0; p++) {
            if (D_80087270[p] == 10) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            f = table[5];
            x = f + view->unk2C;
            right = view->unk30 - f;
            y = f + view->unk24;
            if (D_80090160 & 4) {
                obj = &D_800CC2D0[p];
                st = (u8 *)obj->unk31C;
                count = 1;
                k = st[0x75] & 0x7F;
                if (obj->interaction_state == 0x1F) {
                    k = 0;
                }
                switch (k) {
                case 0x09: icon = 0; break;
                case 0x16: icon = 1; break;
                case 0x14: case 0x3F: icon = 3; break;
                case 0x20: icon = 5; break;
                case 0x18: case 0x41: icon = 6; break;
                case 0x15: icon = 7; break;
                case 0x22: icon = 9; break;
                case 0x23: icon = 10; break;
                case 0x32: case 0x33: count = (s8)st[0x1AE]; icon = 11; break;
                case 0x21: icon = 12; break;
                case 0x24: icon = 13; break;
                case 0x25: icon = 14; break;
                case 0x40: icon = 4; toff = -3; break;
                case 0x26: case 0x3A: /* on fire: counter drawn below */
                    icon = -1;
                    if (obj->health != 0) {
                        fire = 1;
                    }
                    break;
                case 0x38: icon = -1; break;
                default:
                    icon = -1;
                    if (D_800BE9F0 == 0x1A) {
                        icon = 4;
                        toff = 4;
                    }
                    break;
                }
                if (obj->unk13C) {
                    icon = -1;
                }
                if (icon >= 0) {
                    if (!loaded) {
                        loaded = 1;
                        gdl = func_15091534(gdl, 0, &ready);
                    }
                    row = icon / 3;
                    ix = (right - table[25]) * 4;
                    h = table[D_8008775C[row]] * 4;
                    t = D_80087754[row] << 5;
                    dy = 0;
                    if (icon == 4) {
                        dy = 4;
                        h -= 8;
                        t += toff << 5;
                    }
                    if (icon == 1) {
                        h -= 4;
                    }
                    do {
                        if (ready) {
                            gSPTextureRectangle(gdl++, ix, y * 4 + dy, table[22] * 4 + ix, y * 4 + h + dy,
                                                G_TX_RENDERTILE, (icon % 3) * 800, t, scale, scale);
                        }
                        ix -= 18 * 4;
                    } while (--count > 0);
                }
            }
            if (D_80090160 & 0x10) {
                if (!loaded) {
                    gdl = func_15091534(gdl, 0, &ready);
                }
                k = func_150859AC((s16)p, 4);
                ix = table[22] + x;
                len = ((k + 1) >> 1) * 5;
                if (len != 0 && ready) {
                    gSPTextureRectangle(gdl++, (ix - table[len]) * 4, y * 4, ix * 4, (table[4] + y) * 4,
                                        G_TX_RENDERTILE, 0x620, 0xA0, scale, scale);
                }
                len = (k >> 1) * 5;
                if (len != 0 && ready) {
                    gSPTextureRectangle(gdl++, (ix - table[len]) * 4, (table[5] + y) * 4, ix * 4, (table[9] + y) * 4,
                                        G_TX_RENDERTILE, 0x620, 0xA0, scale, scale);
                }
            }
        }
    }

    /* vehicle / weapon icons (state 0x1E) and the second-sheet state icons */
    if (D_80090160 & 4) {
        loaded = 0;
        ready = 0;
        for (p = 0; p <= D_80082FA0; p++) {
            if (D_80087270[p] == 10) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            right = view->unk30 - 5.0f;
            y = view->unk24 + 5.0f;
            obj = &D_800CC2D0[p];
            count = 1;
            icon = -1;
            trow = 0;
            if (obj->interaction_state == 0x1E) {
                st = (u8 *)obj->unk31C;
                k = st[0x128];
                if (k & 1) {
                    icon = 6;
                    shift = 4;
                } else if (k & 2) {
                    icon = 3;
                } else if (k & 0x80) {
                    icon = 0;
                    shift = 6;
                } else if (k & 0x10) {
                    icon = 9;
                    shift = -3;
                }
                if (icon >= 0 && icon != 3) { /* bar from the ammo / fuel count */
                    bar_mode = 1;
                    if (shift > 0) {
                        bars[p] = *(u16 *)(st + 0x12C) >> shift;
                    } else {
                        bars[p] = *(u16 *)(st + 0x12C) << -shift;
                    }
                }
            } else {
                st = (u8 *)obj->unk31C;
                trow = 3;
                switch (st[0x75] & 0x7F) {
                case 0x30: case 0x31: count = (s8)st[0x1AE]; icon = 6; break;
                case 0x37: icon = 7; break;
                case 0x38: icon = 4; break;
                case 0x39: icon = 10; break;
                case 0x3E:
                    bars[p] = *(u16 *)(st + 0x12C) >> 4;
                    bar_mode = 2;
                    break;
                }
            }
            if (icon < 0) {
                continue;
            }
            if (!loaded) {
                loaded = 1;
                gdl = func_15091534(gdl, 1, &ready);
            }
            s = (icon % 3) * 800;
            ix = right - table[25];
            row = icon / 3;
            t = (D_80087754[row] + trow) << 5;
            do {
                if (ready) {
                    gSPTextureRectangle(gdl++, ix * 4, y * 4, (ix + table[22]) * 4, (table[D_8008775C[row]] + y) * 4,
                                        G_TX_RENDERTILE, s, t, scale, scale);
                }
                ix -= 18;
            } while (--count > 0);
        }
    }

    /* red bars */
    if (bar_mode) {
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xEF002C3F; /* other modes: fill */
        gdl->words.w1 = 0x0F0A4004;
        gdl++;
        gdl->words.w0 = 0xFCFFFFFF; /* combine: primitive */
        gdl->words.w1 = 0xFFFDF6FB;
        gdl++;
        gDPSetPrimColor(gdl++, 0, 0, 0xFF, 0x00, 0x00, 0xFF);
        x = (bar_mode == 2) ? 15 : 30;
        for (p = 0; p <= D_80082FA0; p++) {
            if (bars[p] == 0) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            ix = (s32)view->unk30 - x;
            iy = (s32)view->unk24 + 10;
            gDPFillRectangle(gdl++, ix - bars[p], iy, ix, iy + 4);
        }
    }

    /* on-fire counter */
    if (fire) {
        tex = func_1510D66C(0xD15, NULL, 3, 0);
        gdl->words.w0 = 0xFD100000; /* texture image RGBA16 */
        gdl->words.w1 = tex;
        gdl++;
        gdl->words.w0 = 0xF5100000;
        gdl->words.w1 = 0x07094250;
        gdl++;
        gDPLoadSync(gdl++);
        gdl->words.w0 = 0xF3000000;
        gdl->words.w1 = 0x073FF000;
        gdl++;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xF5101000;
        gdl->words.w1 = 0x00094250;
        gdl++;
        gdl->words.w0 = 0xF2000000;
        gdl->words.w1 = 0x0007C07C;
        gdl++;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xEF002C3F;
        gdl->words.w1 = 0x00504244;
        gdl++;
        for (p = 0; p <= D_80082FA0; p++) {
            obj = &D_800CC2D0[p];
            k = ((u8 *)obj->unk31C)[0x75] & 0x7F;
            if (k != 0x26 && k != 0x3A) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            ix = ((s32)view->unk30 - 15) * 4;
            iy = ((s32)view->unk24 + 5) * 4;
            if (D_800BE9F0 == 0x1A || D_800BE9F0 == 0x3F) {
                wi = 11, hi = 14, s = 0x200, t = 0x1E0;
            } else if (obj->id == 0x75 || obj->id == 0xB1) {
                wi = 5, hi = 20, s = 0xC0, t = 0x100;
            } else if (obj->id == 0x3B) {
                wi = 11, hi = 14, s = 0x200, t = 0x1E0;
            } else {
                wi = 8, hi = 9, s = 0x240, t = 0x60;
            }
            for (i = 0; i < ((u8 *)obj->unk31C)[0x19A]; i++) {
                gSPScisTextureRectangle(gdl++, ix, iy, table[wi] * 4 + ix, table[hi] * 4 + iy, G_TX_RENDERTILE, s, t,
                                        0x400, scale);
                ix -= 11 * 4;
            }
        }
    }

    /* race: lap times and lap counter */
    if ((D_80090160 & 0x80) && D_80087640 != NULL) {
        laps = D_800E1017;
        for (p = 0; p <= D_80082FA0; p++) {
            view = (struct_eu_BE628 *)D_800BE628 + p;
            iy = (s32)view->unk24 + 5;
            func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
            race = &D_80087640[p];
            if (*(s32 *)((u8 *)race + 0x20) > 0) { /* best lap */
                func_150916B4((s32)view->unk2C + 0x17, iy + 0x19, *(s32 *)((u8 *)race + 0x20), 0xC0);
                race = &D_80087640[p];
            }
            lap = race->unk27 + 1;
            ix = (s32)view->unk2C + (width >> 1);
            if (lap <= laps) {
                func_15042D94(ix, iy, 0xC1, (s32)D_8009E0C4, ((u8 **)D_800E1008)[8 + D_800E0EF0[p]]);
                func_15042D94((s32)view->unk2C + 0x1D, iy + 0xE, 0xC1, (s32)D_8009E0C8, lap, laps);
                func_150916B4(ix, (s32)view->unk28 - 0xC, *(s32 *)((u8 *)&D_80087640[p] + 0x1C), 0xC0);
            }
        }
    }

    /* overview map */
    if (D_800BEAC1 == 0 && (D_80090160 & 0x1000)) {
        zoom = D_8009E23C;
        mx = ((s32)((struct_eu_BE628 *)D_800BE628)->unk30 - table[32]) * 4;
        if (D_800901BC != 1.0f) {
            zoom = D_8009E23C * D_8009E240;
            size = 0x63;
            dot = 6;
        } else {
            size = 0x40;
            dot = 4;
        }
        tex = func_1510D66C((D_8009015C & 0x40) ? 0xCF4 : 0xCF3, NULL, 3, 0);
        gdl->words.w0 = 0xFD700000; /* texture image IA16 */
        gdl->words.w1 = tex;
        gdl++;
        gdl->words.w0 = 0xF5700000;
        gdl->words.w1 = 0x07098260;
        gdl++;
        gDPLoadSync(gdl++);
        gdl->words.w0 = 0xF3000000;
        gdl->words.w1 = 0x077FF000;
        gdl++;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xF5681000;
        gdl->words.w1 = 0x00098260;
        gdl++;
        gdl->words.w0 = 0xF2000000;
        gdl->words.w1 = 0x000FC0FC;
        gdl++;
        gdl->words.w0 = 0xEF002C3F;
        gdl->words.w1 = 0x00504244;
        gdl++;
        for (p = 0; p < D_80090130; p++) {
            if (func_150859AC((s16)p, 3) <= 0) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            my = (table[24] + (s32)view->unk24 + table[21]) * 4;
            gDPPipeSync(gdl++);
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0x80);
            gdl->words.w0 = 0xFC129A25; /* combine */
            gdl->words.w1 = 0xFF37FFFF;
            gdl++;
            r = table[32] * 4;
            gSPScisTextureRectangle(gdl++, mx - r, my - r, size * 4 + (mx - r), size * 4 + (my - r), G_TX_RENDERTILE,
                                    0, 0, scale, scale);
            gDPPipeSync(gdl++);
            gdl->words.w0 = 0xFC62FEC5;
            gdl->words.w1 = 0xFFFFFBFD;
            gdl++;
            for (i = 0; i < 25; i++) {
                obj = &D_800CC2D0[i];
                if (i != p && !(i < D_8008FD8C && func_150859AC((s16)i, 3) > 0) && obj->unk328 == 0) {
                    continue;
                }
                gDPPipeSync(gdl++);
                fy = (f32)my + D_8009E244;
                fx = (f32)mx + D_8009E248;
                if (i == p) {
                    gDPSetEnvColor(gdl++, 0x00, 0xFF, 0x00, 0xFF);
                } else if (i < D_8008FD8C) {
                    gDPSetEnvColor(gdl++, 0xFF, 0x00, 0x00, 0xFF);
                } else {
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0xFF);
                }
                cx = fx + (f32)(s32)(obj->x_position * zoom);
                cy = fy + (f32)(s32)(obj->z_position * zoom);
                gSPScisTextureRectangle(gdl++, cx - dot, cy - dot, cx + dot, cy + dot, G_TX_RENDERTILE, 0, 0, 0x400,
                                        0x400);
            }
        }
    }

    if (D_800BEAC1 == 0 && (D_80090160 & 0x20)) {
        gdl = func_15093B58(gdl, scale, table, 0x2C30, 0);
    }
    return gdl;
}
