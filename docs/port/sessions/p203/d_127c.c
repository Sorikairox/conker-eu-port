s32 func_150A66F0(f32 *m, f32 x, f32 y, f32 z, f32 r, f32 ry, f32 far);
s32 func_1510D66C(s32, s32 *, s32, s32);
extern f32 D_800A32F0; /* sky tile view-test far distance */
extern u8 D_800DC2DB;  /* 1 on level 0x3C: load every visible tile's texture, even beyond the distance limit */
extern u8 D_800DC2DC;  /* bit 0 of D_800D2E4C->unk14: sky 1 face 2 shows the replacement tiles 0x1675.. */
extern s32 D_800DC2B0; /* sky asset: one format byte per tile (0 = CI8, 1 = CI4) */

// sky_box_face_build: P203: builds one face of the sky box (func_15112074) as a grid of textured quads in the
// frame's vertex buffer and queues their texture loads. The face lies in the plane `axis` ('x' / 'y' / 'z') through
// the corner (x, y, z) * 8 and spans w x h texels in tiles of step_s x step_t texels (8 world units per texel); rows
// run down from the corner's second coordinate, columns along its first. Per tile: the view test func_150A66F0
// (centre of the quad, half sizes step * 8, far D_800A32F0) drops tiles outside the view; for the side faces
// (face < 4) only the first `dist` rows are kept with dist scaled from 0..320 to 0..rows (rounded up); the texture
// (tex + col * rows + row, or on sky 1 face 2 with D_800DC2DC the replacement 0x1675 + col * 3 + row - 10 for
// rows 4..6 / columns 2..3) is fetched with func_1510D66C(id, NULL, 3, 0) and queued in loads[] with the tile's
// format byte from the sky asset D_800DC2B0. On the 'y' faces the first and last columns grow by 3 units on each
// side (hides the seams). Every 16 vertices (4 quads) it emits one G_VTX and per quad the block / palette loads,
// a tile switch when the format changes (*last_fmt) and two triangles; *count / *first keep the partial batch for
// the caller, which flushes the rest. arg3 / arg4 are unused. Returns the advanced display list.
// Port: for an upper-case axis the asm leaves the start coordinates unset (garbage); the C starts them at 0.
Gfx *func_1511127C(Gfx *gdl, s32 *vtx, s32 tex, s32 arg3, s32 arg4, u32 w, u32 h, u32 step_s, u32 step_t, f32 x, f32 y, f32 z, s32 axis, f32 (*view)[4], s32 dist, s32 *count, s32 *first, SkyLoad *loads, s32 *last_fmt, u8 *arg19, u8 *arg20, s16 *tlut_offset, u8 *tlut_count, u8 *tile, s32 face) {
    s32 q[4][3]; /* the quad's corners in vertex order */
    s32 vbuf, cur_first, n, fmt_last;
    s32 fx, fy, fz;
    s32 u_start, v_start, u, u2, v, v2;
    s32 du, dv, row, col, rows, cols, id, addr, k, lrs, fmt;
    u32 spos, tpos;
    u16 s_hi, t_hi;
    s16 *vp;
    u8 ax;

    x *= 8.0f;
    y *= 8.0f;
    z *= 8.0f;
    vbuf = *vtx;
    cur_first = *first;
    n = *count;
    fmt_last = *last_fmt;
    ax = axis;
    if (ax == 'x') {
        u_start = (s32) z;
        v_start = (s32) y;
    } else if (ax == 'y') {
        u_start = (s32) x;
        v_start = (s32) z;
    } else if (ax == 'z') {
        u_start = (s32) x;
        v_start = (s32) y;
    } else {
        u_start = 0;
        v_start = 0;
    }
    row = 0;
    if (face < 4) {
        if (dist > 320) {
            dist = 320;
        }
        dist = (s32) (dist * (h / step_t) + 319) / 320;
    } else {
        dist = 0x7FFF;
    }
    dv = step_t * 8;
    v = v_start - dv;
    for (tpos = 0; tpos < h; tpos += step_t, row++, v -= dv) {
        col = 0;
        u = u_start;
        du = step_s * 8;
        for (spos = 0; spos < w; spos += step_s, col++, u = u2) {
            u2 = u + du;
            v2 = v + dv;
            switch (ax) {
                case 'X':
                case 'x':
                    fx = (s32) x;
                    q[0][0] = fx, q[0][1] = v, q[0][2] = u;
                    q[1][0] = fx, q[1][1] = v, q[1][2] = u2;
                    q[2][0] = fx, q[2][1] = v2, q[2][2] = u2;
                    q[3][0] = fx, q[3][1] = v2, q[3][2] = u;
                    break;
                case 'Y':
                case 'y':
                    fy = (s32) y;
                    q[0][0] = u, q[0][1] = fy, q[0][2] = v;
                    q[1][0] = u2, q[1][1] = fy, q[1][2] = v;
                    q[2][0] = u2, q[2][1] = fy, q[2][2] = v2;
                    q[3][0] = u, q[3][1] = fy, q[3][2] = v2;
                    break;
                case 'Z':
                case 'z':
                    fz = (s32) z;
                    q[0][0] = u, q[0][1] = v, q[0][2] = fz;
                    q[1][0] = u2, q[1][1] = v, q[1][2] = fz;
                    q[2][0] = u2, q[2][1] = v2, q[2][2] = fz;
                    q[3][0] = u, q[3][1] = v2, q[3][2] = fz;
                    break;
            }
            /* view test of the quad's centre (corners 0 and 2 are opposite) */
            if (func_150A66F0((f32 *) view, (f32) ((q[0][0] + q[2][0]) >> 1), (f32) ((q[0][1] + q[2][1]) >> 1),
                              (f32) ((q[0][2] + q[2][2]) >> 1), (f32) du, (f32) dv, D_800A32F0) == 0) {
                continue;
            }
            if (D_800DC2DB == 0 && row >= dist) {
                continue;
            }
            rows = h / step_t;
            id = tex + col * rows + row;
            if (D_800DC2DC != 0 && ((u8 *) D_800B0DF0)[9] == 1 && face == 2 && row >= 4 && row < 7 && col >= 2 &&
                col < 4) {
                id = 0x1675 + (col * 3 + row - 10);
            }
            addr = func_1510D66C(id, NULL, 3, 0);
            if (D_800DC2DB != 0 && row >= dist) {
                continue;
            }
            t_hi = (s32) (((f32) step_t + 0.5f) * 32.0f);
            s_hi = (s32) (((f32) step_s + 0.5f) * 32.0f);
            vp = (s16 *) (vbuf + (cur_first + n) * 16);
            cols = w / step_s;
            if (ax == 'y' && (spos == 0 || spos == w - step_s)) {
                q[0][0] -= 3;
                q[3][0] -= 3;
                q[2][0] += 3;
                q[1][0] += 3;
                q[0][2] -= 3;
                q[2][2] += 3;
                q[1][2] -= 3;
                q[3][2] += 3;
            }
            /* x, y, z, flag 0, s, t (10.5 fixed); the colour words stay */
            vp[0] = q[0][0], vp[1] = q[0][1], vp[2] = q[0][2], vp[3] = 0, vp[4] = 16, vp[5] = 16;
            vp[8] = q[1][0], vp[9] = q[1][1], vp[10] = q[1][2], vp[11] = 0, vp[12] = s_hi, vp[13] = 16;
            vp[16] = q[2][0], vp[17] = q[2][1], vp[18] = q[2][2], vp[19] = 0, vp[20] = s_hi, vp[21] = t_hi;
            vp[24] = q[3][0], vp[25] = q[3][1], vp[26] = q[3][2], vp[27] = 0, vp[28] = 16, vp[29] = t_hi;
            loads[n >> 2].addr = addr;
            loads[n >> 2].fmt = ((u8 *) D_800DC2B0)[col * rows + row + face * cols * rows];
            n += 4;
            if (n != 16) {
                continue;
            }
            /* a full batch: one G_VTX for the 16 vertices, then per quad its texture and two triangles */
            gdl->words.w0 = 0x01010020;
            gdl->words.w1 = vbuf + cur_first * 16;
            gdl++;
            for (k = 0; k < 16; k += 4) {
                fmt = loads[k >> 2].fmt;
                gdl->words.w0 = 0xE7000000;
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0xFD100000;
                gdl->words.w1 = loads[k >> 2].addr;
                gdl++;
                lrs = ((arg19[fmt] + 0x800) >> arg20[fmt]) - 1;
                if (lrs >= 0x7FF) {
                    lrs = 0x7FF;
                }
                gdl->words.w0 = 0xF3000000;
                gdl->words.w1 = 0x07000000 | ((lrs & 0xFFF) << 12);
                gdl++;
                gdl->words.w0 = 0xFD100000;
                gdl->words.w1 = tlut_offset[fmt] + loads[k >> 2].addr;
                gdl++;
                gdl->words.w0 = 0xE6000000;
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0xF0000000;
                gdl->words.w1 = 0x06000000 | (tlut_count[fmt] << 14);
                gdl++;
                if (fmt != fmt_last) {
                    fmt_last = fmt;
                    gdl->words.w0 = 0xD7000002 | ((tile[fmt] & 7) << 8);
                    gdl->words.w1 = 0xFFFFFFFF;
                    gdl++;
                }
                /* (k + 2, k, k + 1) and (k + 3, k, k + 2); G_TRI1 indices are vertex * 2 */
                gdl->words.w0 = 0x05000000 | (((k * 2 + 4) & 0xFF) << 16) | (((k * 2) & 0xFF) << 8) | ((k * 2 + 2) & 0xFF);
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0x05000000 | (((k * 2 + 6) & 0xFF) << 16) | (((k * 2) & 0xFF) << 8) | ((k * 2 + 4) & 0xFF);
                gdl->words.w1 = 0;
                gdl++;
            }
            n = 0;
            cur_first += 16;
        }
    }
    *count = n;
    *first = cur_first;
    *vtx = vbuf;
    return gdl;
}
