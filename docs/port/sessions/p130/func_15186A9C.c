extern s8 D_800DE471;   /* != 0: only level triangles whose D_800D3668 flag is 1 cast shadows */
extern s32 D_800D3AB0;  /* triangle table for func_150A6070 / func_150A6324 */
extern s32 D_800D3AB4;  /* end of the triangle bit mask */
extern s32 D_800DC26C;  /* level triangle table: 3 vertex pointers per triangle */
extern s32 D_800DF518;  /* shadow box x min, x max, z min, z max */
extern s32 D_800DF51C;
extern s32 D_800DF520;
extern s32 D_800DF524;
void func_1510F800(s32);
s32 func_1510FCA0(s32, s32, s32, u8 **);
s32 func_150A6070(u32 *, s32, f32 *, s32);

// shadow_level_vertices: collects the level triangles under a shadow (box x / z +- r) and projects them.
// func_1510FCA0 returns up to 16 level cells around (x, z); each cell holds at +0xE a 0-terminated triangle list
// (byte < 0x80: index += byte; else ((byte << 8) | next byte) & 0x7FFF is the index). The triangles (< 0x1760,
// and with flag 1 in D_800D3668 when D_800DE471) become bits of a stack mask; func_150A6070 projects them with the
// light matrix (4x4 f32) into the 20-byte shadow vertices at buf (up to end). Returns the number of vertices written.
s32 func_15186A9C(s32 x, s32 z, s32 r, s32 buf, u8 *light, s32 end) {
    u8 *cells[16];
    u32 mask[0x2EC / 4];
    s32 n;
    u8 *p;
    u32 tri, last;
    u32 c;

    last = 0;
    func_1510F800(0);
    n = func_1510FCA0(x, z, r, cells);
    if (n == 0) {
        return 0;
    }
    bzero(mask, sizeof(mask));
    while (n != 0) {
        n--;
        p = cells[n] + 0xE;
        tri = 0;
        while ((c = *p) != 0) {
            if (c & 0x80) {
                tri = ((c << 8) | p[1]) & 0x7FFF;
                p += 2;
            } else {
                tri += c;
                p += 1;
            }
            if (tri >= 0x1760) {
                continue;
            }
            if (D_800DE471 != 0 && ((u8 *) D_800D3668)[tri] != 1) {
                continue;
            }
            mask[tri >> 5] |= 1 << (tri & 0x1F);
            if (last < tri) {
                last = tri;
            }
        }
    }
    D_800D3AB0 = D_800DC26C;
    D_800D3AB4 = (s32) &mask[(last >> 5) + 1];
    D_800DF518 = x - r;
    D_800DF51C = x + r;
    D_800DF520 = z - r;
    D_800DF524 = z + r;
    return (func_150A6070(mask, buf, (f32 *) light, end) - buf) / 20;
}
