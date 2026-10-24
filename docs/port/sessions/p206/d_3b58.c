s32 func_15086218(f32 y);
extern f32 D_8009E24C; /* radar world -> screen scale, 2-4 players (0.0135) */
extern f32 D_8009E250; /* radar zoom of the big radar (1.329) */
extern f32 D_8009E254; /* radar world -> screen scale, 1 player (0.02025) */
extern f32 D_8009E258; /* big radar disc size factor (0.858) */
extern f32 D_8009E25C; /* big radar texture step factor (1.1655) */
extern f32 D_8009E260; /* degrees -> radians */
extern u8 D_800ABA0C[]; /* radar dot colours: r, g, b per team (unk328 - 1) */
extern u16 D_800E0FFC;  /* bit per player object: hidden from the radar */

// radar_draw: P206: draws the multiplayer radar of every active view (func_1508FD38 / func_150918EC). The radar
// disc (texture 0xCF5, IA16 32x32) sits at the view's corner from the view rectangle (D_800BE628) and the layout
// table (table[7] / table[21] the corner offsets, table[16] the radius, table[24] in one-player mode, where the
// texture step is size * 2 / 3); `big` moves it by (-0x1C6, -0x46) quarter pixels and scales it. Every other
// object slot 0..24 with a team (unk328) inside the range is drawn as a coloured dot, rotated by the view's yaw
// (D_800DBFF0[p].unk37C, degrees); for the player slots below D_8008FD8C the dot is hidden when the player is
// out of the game (func_150859AC modes 3 / 4), flagged in D_800E0FFC, dead, or in state 0x21. A black mark above
// or below the dot shows a different height level (func_15086218). When the view's object is in state 0x25 the
// radar centres on player 0 (or 1 when its camera mode is 3), which is skipped as well. Returns the advanced DL,
// or `gdl` unchanged when the texture is not loaded.
Gfx *func_15093B58(Gfx *gdl, s32 size, s16 *table, s32 mode, s32 big) {
    struct_eu_BE628 *view;
    struct127 *me, *ref, *obj;
    u8 *col;
    s32 p, i, self, team, half, dot, x0, y0, r, dsdx, tex, cx, cy;
    s8 my_level, level;
    f32 scale, range, zoom, rx, rz, s, c, dx, dz, angle;

    scale = D_8009E24C;
    range = 3136.0f;
    half = table[16];
    if ((u8)big) {
        zoom = D_8009E250;
    } else {
        zoom = 1.0f;
    }
    if (D_80090130 == 1) {
        scale = D_8009E254;
        range = 7744.0f;
        size = (size * 2) / 3;
        half = table[24];
    }
    scale *= D_800901BC;
    range *= D_800901BC;
    dot = 6;
    if (D_800901BC == 1.0f) {
        dot = 4;
    }
    tex = func_1510D66C(0xCF5, NULL, 3, 0);
    if (tex == 0x80000000) {
        return gdl;
    }
    gdl->words.w0 = 0xFD700000; /* texture image IA16 */
    gdl->words.w1 = tex;
    gdl++;
    gdl->words.w0 = 0xF5700000;
    gdl->words.w1 = 0x07094250;
    gdl++;
    gdl->words.w0 = 0xE6000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xF3000000;
    gdl->words.w1 = 0x071FF000;
    gdl++;
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xF5680800;
    gdl->words.w1 = 0x00094250;
    gdl++;
    gdl->words.w0 = 0xF2000000;
    gdl->words.w1 = 0x0007C07C;
    gdl++;
    gdl->words.w0 = 0xEF000000 | ((mode | 0xF) & 0xFFFFFF); /* other modes */
    gdl->words.w1 = 0x00504244;
    gdl++;

    for (p = 0; p < D_80090130; p++) {
        if (func_150859AC((s16)p, 3) <= 0) {
            continue;
        }
        view = (struct_eu_BE628 *)D_800BE628 + p;
        x0 = ((s32)view->unk30 - table[7] - half) * 4;
        y0 = (table[21] + (s32)view->unk24 + half) * 4;
        me = &D_800CC2D0[p];
        if ((u8)big) {
            x0 -= 0x1C6;
            y0 -= 0x46;
        }
        gdl->words.w0 = 0xE7000000;
        gdl->words.w1 = 0;
        gdl++;
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = 0xFFFFFF80;
        gdl++;
        gdl->words.w0 = 0xFC129A25;
        gdl->words.w1 = 0xFF37FFFF;
        gdl++;
        if ((u8)big) {
            r = (f32)(half * 4) * D_8009E258;
            dsdx = (f32)(s32)(f32)size * D_8009E25C;
        } else {
            r = half * 4;
            dsdx = size;
        }
        /* the radar disc */
        gSPScisTextureRectangle(gdl++, x0 - r, y0 - r, x0 + r, y0 + r, G_TX_RENDERTILE, 0, 0, dsdx, dsdx);
        gdl->words.w0 = 0xE7000000;
        gdl->words.w1 = 0;
        gdl++;
        gdl->words.w0 = 0xFC62FEC5;
        gdl->words.w1 = 0xFFFFFBFD;
        gdl++;
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = 0xFF0000FF;
        gdl++;

        angle = D_800DBFF0[p].unk37C * D_8009E260;
        s = sinf(angle);
        c = cosf(angle);
        if (me->interaction_state != 0x25) {
            self = -1;
            ref = me;
        } else {
            self = 0;
            if (me->camera != NULL && me->camera->unk23D == 3) {
                self = 1;
            }
            ref = &D_800CC2D0[self];
        }
        rx = ref->x_position;
        rz = ref->z_position;
        my_level = func_15086218(ref->y_position);

        for (i = 0; i < 25; i++) {
            if (i == p || i == self) {
                continue;
            }
            obj = &D_800CC2D0[i];
            if (obj->interaction_state == 0 || obj->unk328 == 0) {
                continue;
            }
            team = obj->unk328 - 1;
            if (i < D_8008FD8C) {
                if (func_150859AC((s16)i, 3) <= 0 || func_150859AC((s16)i, 4) <= 0 || (D_800E0FFC & (1 << i)) ||
                    obj->health == 0 || (((u8 *)obj->unk31C)[0x75] & 0x7F) == 0x21) {
                    team = -1;
                }
            }
            if (team == -1) {
                continue;
            }
            dx = (obj->x_position - rx) * scale;
            dz = (obj->z_position - rz) * scale;
            if (!(dx * dx + dz * dz < range)) {
                continue;
            }
            col = &D_800ABA0C[team * 3];
            gdl->words.w0 = 0xE7000000;
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0xFB000000;
            gdl->words.w1 = (col[0] << 24) | (col[1] << 16) | (col[2] << 8) | 0xFF;
            gdl++;
            cx = (s32)((dx * c - dz * s) * zoom) + x0;
            cy = (s32)((dx * s + dz * c) * zoom) + y0;
            gSPScisTextureRectangle(gdl++, cx - dot, cy - dot, cx + dot, cy + dot, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);

            level = func_15086218(obj->y_position);
            if (level == my_level) {
                continue;
            }
            gdl->words.w0 = 0xE7000000;
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0xFB000000;
            gdl->words.w1 = 0x000000FF;
            gdl++;
            if (my_level < level) { /* higher: mark above the dot */
                gSPScisTextureRectangle(gdl++, cx - dot, cy - dot * 2, cx + dot, cy - dot, G_TX_RENDERTILE, 0, 0,
                                        0x400, 0x400);
            } else if (level < my_level) { /* lower: mark below */
                gSPScisTextureRectangle(gdl++, cx - dot, cy + dot, cx + dot, cy + dot * 2, G_TX_RENDERTILE, 0, 0,
                                        0x400, 0x400);
            }
        }
    }
    return gdl;
}
