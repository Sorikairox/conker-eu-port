extern f32 D_800DE45C;  /* shadow alpha at the near depth */
ClipVtx_60C4 *func_15186344(ClipVtx_60C4 *in, s32 n, s32 plane, ClipVtx_60C4 *out);

// shadow_clip_triangle: clips one projected shadow polygon (n 20-byte shadow vertices at in: x, y, w, source
// vertex pointer) and converts it into 16-byte Vtx at out. The polygon (with the source vertex's s16 x / y / z
// as s / t / u) is clipped against planes 0..5 (|x| <= -w, |y| <= -w, near, far) in two ping-pong buffers. With
// split, planes 6 / 7 cut it into the halves x <= 0 / x > 0 and planes 8 / 9 cut each half into y > 0 / y <= 0:
// counts[0..4] are the start indices of the four quadrant pieces (A y>0, B y>0, A y<=0, B y<=0) and their end;
// without split all four pieces are the whole polygon (counts = 0, n, n, n, n). Each output vertex: position =
// the source vertex, texture s = 1024 - 1020 x / w, t = 1020 y / w + 1024, colour 0, alpha fading from
// D_800DE45C at the near depth D_800D3AAC to 0 at the far depth D_800D3AA8. Returns the number of vertices.
s32 func_15186494(s32 inAddr, s32 n, s32 unused, s32 outAddr, s32 *counts, s32 split) {
    u8 *in = (u8 *) inAddr;
    u8 *out = (u8 *) outAddr;
    ClipVtx_60C4 buf[2][26];
    s32 half[3];
    ClipVtx_60C4 *src;
    ClipVtx_60C4 *dst;
    ClipVtx_60C4 *v;
    s16 *pos;
    f32 k, a;
    s32 alpha;
    s32 plane;
    s32 i;

    for (i = 0; i < n; i++) {
        pos = *(s16 **) (in + i * 20 + 0xC);
        buf[0][i] = *(ClipVtx_60C4 *) (in + i * 20);
        buf[0][i].s = pos[0];
        buf[0][i].t = pos[1];
        buf[0][i].u = pos[2];
    }
    for (plane = 0; plane != 6; plane++) {
        dst = buf[(plane & 1) ^ 1];
        n = (u32) ((u8 *) func_15186344(buf[plane & 1], n, plane, dst) - (u8 *) dst) / 20;
    }
    half[0] = 0;
    counts[0] = 0;
    if (split != 0) {
        src = buf[plane & 1];
        dst = buf[(plane & 1) ^ 1];
        for (i = 0; i < 2; i++) {
            half[i + 1] = (u32) ((u8 *) func_15186344(src, n, i + 6, dst + half[i]) - (u8 *) dst) / 20;
        }
        plane++;
        src = buf[plane & 1];
        dst = buf[(plane & 1) ^ 1];
        for (i = 0; i < 4; i += 2) {
            counts[i + 1] = (u32) ((u8 *) func_15186344(src + half[0], half[1] - half[0], (i >> 1) + 8,
                                                        dst + counts[i]) - (u8 *) dst) / 20;
            counts[i + 2] = (u32) ((u8 *) func_15186344(src + half[1], half[2] - half[1], ((i + 1) >> 1) + 8,
                                                        dst + counts[i + 1]) - (u8 *) dst) / 20;
        }
        n = counts[4];
        plane++;
    } else {
        counts[4] = n;
        counts[3] = n;
        counts[2] = n;
        counts[1] = n;
    }
    v = buf[plane & 1];
    for (i = 0; i < n; i++, v++, out += 16) {
        *(s16 *) (out + 0) = v->s;
        *(s16 *) (out + 2) = v->t;
        *(s16 *) (out + 4) = v->u;
        k = 1020.0f / v->z;
        v->x = v->x * k;
        v->y = v->y * k;
        *(s16 *) (out + 8) = (s32) (1024.0f - v->x);
        out[0xC] = 0;
        out[0xD] = 0;
        out[0xE] = 0;
        *(s16 *) (out + 0xA) = (s32) (v->y + 1024.0f);
        a = D_800DE45C - ((v->z - D_800D3AAC) / (D_800D3AA8 - D_800D3AAC)) * D_800DE45C;
        /* IDO's float -> u32 (written out: NaN, <= -1 and >= 2^32 give 0xFFFFFFFF) */
        if (a != a || a <= -1.0f || a >= 4294967296.0f) {
            alpha = -1;
        } else if (a >= 2147483648.0f) {
            alpha = (s32) (a - 2147483648.0f);
        } else {
            alpha = (s32) a;
        }
        out[0xF] = alpha;
        *(s16 *) (out + 6) = 0;
    }
    return n;
}
