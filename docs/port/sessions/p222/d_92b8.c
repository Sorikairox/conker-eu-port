/* P222: readable C for func_150C92B8 (game_eu_F6060, 767 words): draw callback of render layer 0x31 (the ring
 * effect; layer at D_8008B848 + 0x31 * 0x34: update func_150C8F68, draw func_150C92B8). */
typedef struct {
    s32 n;          /* 5 */
    f32 (*pt)[2];   /* D_800A08D0: (radial offset, height) */
} RingProfile;
extern RingProfile D_80088BC0;
extern s32 *D_80091234;  /* the ring texture's id */
extern s32 D_800A4EA8[]; /* render mode pairs (2 words each) */
s32 func_1510D66C(s32, s32 *, s32, s32);
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear);
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
Gfx *func_15142CF0(Gfx *gfx, s32 m, s32 l, s32 r, s32 g, s32 b, s32 a, u8 *arg7);
Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3);
Gfx *func_1513F4E4(Gfx *arg0, u8 arg1, u8 *arg2);
void func_150CD2A0(f32, f32 *, f32 *, f32 *);

#define RING_DL(a, b) (gdl->words.w0 = (a), gdl->words.w1 = (b), gdl++)

// ring_effect_draw: draws a ring effect node: render state (geometry mode, colours, combiner 0x21, render mode
// D_800A4EA8 entry 14), the ring texture (func_1510D66C(*D_80091234): CI4 with 6 mip levels in tiles 0..5, its TLUT is
// the last 0x20 bytes) and a surface of revolution: the cross-section D_80088BC0 (radial offset, height, scaled by
// +0x40) swept around the centre +0x10 / +0x14 / +0x18 at radius +0x44, one vertex column per direction (+0x360:
// cos / sin pairs, +0x24 of them, the last column repeats the first). Columns farther than 3300.6 from the world
// origin (x / z) are flat and transparent. Vertex colours: func_150CD2A0(z); texture coordinates from x / z. The
// vertices go to the node's buffer for this frame (+0x54[D_800BE9C0]); after each new column, gSPVertex of it and
// the previous one and two triangles per cross-section edge. arg2 (the layer's argument) is unused. Returns the DL end.
Gfx *func_150C92B8(Gfx *gdl, u8 *node, s16 arg2) {
    u8 flag = 1;
    s32 size;
    s32 tex;
    Vtx *buf;
    Vtx *v;
    f32 *dir;
    f32 cx, cz, px, py, x, z, r, g, b;
    s32 near;
    s32 nv = 0;
    s32 col, i, n;

    gdl = func_15142B7C(gdl, 0x200205, 0x70400);
    gdl = func_15142C10(gdl, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
    gdl = func_15142CF0(gdl, 0xF2, 0, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
    gdl = func_1513F4E4(gdl, 0x21, &flag);
    gdl = func_15142FBC(gdl, 0x1DACA0, D_800A4EA8[29] | D_800A4EA8[28], &flag);
    tex = func_1510D66C(*D_80091234, &size, 3, 0);
    gSPTexture(gdl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    RING_DL(0xFD500000, tex);        /* texture image: CI, 16-bit words (block load) */
    RING_DL(0xF5500000, 0x07000000); /* tile 7: load tile */
    RING_DL(0xF3000000, 0x073EF000); /* load block 0x3EF+1 texels */
    RING_DL(0xF5400400, 0x01018050); /* tile 1 (mip 1) */
    RING_DL(0xF2402402, 0x0147E4FE);
    RING_DL(0xF5400280, 0x02014441); /* tile 2 */
    RING_DL(0xF2202202, 0x0223E27E);
    RING_DL(0xF54002A0, 0x03010832); /* tile 3 */
    RING_DL(0xF2102102, 0x0311E13E);
    RING_DL(0xF54002B0, 0x0400CC23); /* tile 4 */
    RING_DL(0xF2082082, 0x0408E09E);
    RING_DL(0xF54002B8, 0x05009014); /* tile 5 */
    RING_DL(0xF2042042, 0x0504604E);
    RING_DL(0xF56004BC, 0x00017C5F); /* tile 0 (mip 0) */
    RING_DL(0xF2802802, 0x0087E87E);
    RING_DL(0xFD100000, tex + size - 0x20); /* TLUT image: the texture's last 16 colours */
    RING_DL(0xF5600100, 0x06000000);         /* tile 6: TLUT at tmem 0x100 */
    gDPLoadSync(gdl++);
    gDPLoadTLUTCmd(gdl++, 6, 15);
    gSPTexture(gdl++, 0xFFFF, 0xFFFF, 4, G_TX_RENDERTILE, G_ON);

    buf = ((Vtx **) (node + 0x54))[D_800BE9C0];
    /* column 0 is direction 0; column col > 0 is direction col (the last one, col == +0x24, wraps to 0) */
    for (col = 0; col == 0 || col <= *(s32 *) (node + 0x24); col++) {
        dir = *(f32 **) (node + 0x360) + (col == *(s32 *) (node + 0x24) ? 0 : col) * 2;
        cx = *(f32 *) (node + 0x10) + *(f32 *) (node + 0x44) * dir[0];
        cz = *(f32 *) (node + 0x18) + *(f32 *) (node + 0x44) * dir[1];
        near = (cx * cx + cz * cz < 10894295.0f);
        v = buf + nv;
        for (i = 0; i < D_80088BC0.n; i++, v++) {
            px = D_80088BC0.pt[i][0] * *(f32 *) (node + 0x40);
            py = D_80088BC0.pt[i][1] * *(f32 *) (node + 0x40);
            x = cx + px * dir[0];
            z = cz + px * dir[1];
            v->v.ob[0] = x;
            v->v.ob[1] = (near ? py : 0.0f) + *(f32 *) (node + 0x14);
            v->v.ob[2] = z;
            v->v.tc[0] = -((x * 0.03988662f + z * 0.03713737f + 110.230064f) * 32.0f);
            v->v.tc[1] = -((x * 0.054123953f + z * -0.058144543f + 50.14429f) * 32.0f);
            func_150CD2A0(z, &r, &g, &b);
            nv++;
            v->v.cn[0] = (u32) r;
            v->v.cn[1] = (u32) g;
            v->v.cn[2] = (u32) b;
            v->v.cn[3] = near ? 0xFF : 0;
        }
        if (col == 0) {
            continue;
        }
        n = D_80088BC0.n;
        gSPVertex(gdl++, ((Vtx **) (node + 0x54))[D_800BE9C0] + (nv - n * 2), n * 2, 0);
        for (i = 0; i < D_80088BC0.n - 1; i++) {
            gSP1Triangle(gdl++, i, i + 1, i + D_80088BC0.n + 1, 0);
            gSP1Triangle(gdl++, i, i + D_80088BC0.n + 1, i + D_80088BC0.n, 0);
        }
    }
    return gdl;
}
