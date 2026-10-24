extern f32 D_800D3A00;
extern u8 D_800D3A08[]; /* per-vertex cull flags, 4 bytes per vertex: x' < 0, inside the side planes, in front */

/* mesh_dl_cull_copy: P186: C for the hand-written asm func_150A55A0 (+ its loop func_150A563C / func_150A5654 /
 * func_150A5678 / func_150A57D4, which nothing else enters). Copies the F3DEX2 display list `dl` to gdl and drops
 * what the view (matrix mtx: f32[4][4], row vectors; x' = column 0, depth z' = column 2) cannot see:
 * - G_VTX (0x01): the vertices (address w1 + base, count (w0 >> 8) & 0xFFF0 bytes, always loaded from flag slot 0)
 *   get flags [0] = sign bit of x', [1] = |z'| > |x'| * D_800D3A00 (inside the side planes), [2] = !(z' >= 0)
 *   (in front). The command is copied; it replaces an output G_VTX directly before it (no triangle in between).
 * - G_TRI1 (0x05, vertex indices * 2 in bytes 1..3): dropped when no vertex is in front; kept when one is inside,
 *   or when the three x' signs differ (1 or 2 negative), else dropped.
 * - 0xF3 (G_LOADBLOCK): copied; a previous one with no kept triangle since is turned into a no-op (8 zero bytes).
 * - G_ENDDL (0xDF): not copied; returns the output end. Everything else is copied. arg3 / arg4 are not read. */
Gfx *func_150A55A0(s32 dl, Gfx *gdl, u8 *mtx, s32 arg3, s32 arg4, s32 base) {
    f32 *m = (f32 *) mtx;
    u32 *src = (u32 *) dl;
    u32 *out = (u32 *) gdl;
    u32 *lastLoad = NULL;
    u8 *f0, *f1, *f2;
    u8 *vtx, *end;
    u8 *fl;
    f32 x, y, z, sz;
    union { f32 f; u32 u; } sx;
    s32 inside, front, neg;
    s8 op;

    for (;;) {
        op = *(s8 *) src;
        if (op == 5) {
            f0 = &D_800D3A08[((u8 *) src)[1] * 2];
            f1 = &D_800D3A08[((u8 *) src)[2] * 2];
            f2 = &D_800D3A08[((u8 *) src)[3] * 2];
            inside = f0[1] + f1[1] + f2[1];
            front = f0[2] + f1[2] + f2[2];
            neg = f0[0] + f1[0] + f2[0];
            if (front == 0 || (inside == 0 && neg != 1 && neg != 2)) {
                src += 2;
                continue;
            }
            lastLoad = NULL;
        } else if (op == 1) {
            if (((s8 *) out)[-8] == 1) {
                out -= 2;
            }
            vtx = (u8 *) (src[1] + base);
            end = vtx + ((src[0] >> 8) & 0xFFF0);
            fl = D_800D3A08;
            do {
                x = *(s16 *) (vtx + 0);
                y = *(s16 *) (vtx + 2);
                z = *(s16 *) (vtx + 4);
                sz = x * m[2] + m[14] + y * m[6] + z * m[10];
                sx.f = x * m[0] + m[12] + y * m[4] + z * m[8];
                vtx += 0x10;
                fl[2] = !(0.0f <= sz);
                fl[0] = sx.u >> 31;
                fl[1] = !(fabsf(sz) <= fabsf(sx.f) * D_800D3A00);
                fl += 4;
            } while (vtx != end);
        } else if (op == -0xD) {
            if (lastLoad != NULL) {
                lastLoad[0] = 0;
                lastLoad[1] = 0;
            }
            lastLoad = out;
        } else if (op == -0x21) {
            return (Gfx *) out;
        }
        out[0] = src[0];
        out[1] = src[1];
        out += 2;
        src += 2;
    }
}
