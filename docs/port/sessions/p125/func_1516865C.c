extern u8 *D_8008CDEC[];

/* sprite_quad_init: fills the two 4-vertex quads at the start of a sprite spawn record (8 Vtx, 0x80 bytes) with
 * colour (r, g, b, a) and flag 0, and their texture coordinates from the texture D_8008CDEC[rec[0xA0]] (u16 width
 * +6, height +8; S10.5 coordinates (size + 256) << 5, the other edge 256 << 5). Record flags u16 +0x98: 0x80 flips
 * t, 0x100 flips s. Also clears the s16 at +0x88, +0x9C and +0x9E. The colour parameters are bytes. Returns the
 * last t value (what the asm leaves in v0; the callers, declared s32, ignore it). */
s32 func_1516865C(u8 *rec, s32 r, s32 g, s32 b, s32 a) {
    Vtx *v = (Vtx *) rec;
    u8 *tex;
    u16 flags;
    s16 s0, s1, t0, t1;
    s32 i;

    tex = D_8008CDEC[rec[0xA0]];
    s0 = 0x2000;
    t0 = 0x2000;
    s1 = (*(u16 *) (tex + 6) + 0x100) << 5;
    t1 = (*(u16 *) (tex + 8) + 0x100) << 5;
    for (i = 0; i < 8; i++) {
        v[i].v.flag = 0;
        v[i].v.cn[0] = r;
        v[i].v.cn[1] = g;
        v[i].v.cn[2] = b;
        v[i].v.cn[3] = a;
    }
    flags = *(u16 *) (rec + 0x98);
    if (flags & 0x80) {
        t1 = 0x2000;
        t0 = (*(u16 *) (D_8008CDEC[rec[0xA0]] + 8) + 0x100) << 5;
    }
    if (flags & 0x100) {
        s1 = 0x2000;
        s0 = (*(u16 *) (D_8008CDEC[rec[0xA0]] + 6) + 0x100) << 5;
    }
    v[6].v.tc[0] = s0;
    v[7].v.tc[1] = t0;
    v[7].v.tc[0] = s1;
    v[1].v.tc[0] = v[5].v.tc[0] = v[2].v.tc[0] = v[6].v.tc[0];
    v[5].v.tc[1] = t1;
    *(s16 *) (rec + 0x88) = 0;
    v[2].v.tc[1] = v[6].v.tc[1] = v[3].v.tc[1] = v[7].v.tc[1];
    *(s16 *) (rec + 0x9C) = 0;
    *(s16 *) (rec + 0x9E) = 0;
    v[0].v.tc[0] = v[4].v.tc[0] = v[3].v.tc[0] = v[7].v.tc[0];
    v[0].v.tc[1] = v[4].v.tc[1] = v[1].v.tc[1] = v[5].v.tc[1];
    return t0;
}
