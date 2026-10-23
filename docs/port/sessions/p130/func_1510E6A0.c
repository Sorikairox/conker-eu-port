extern s32 D_800DD5E4;     /* texture of the last drawn blob shadow */
extern s32 D_80091B20[];   /* blob shadow texture ids */
void func_150A7D00(s16 *mtx, f32 x, f32 y, f32 z);
s32 func_1510D66C(s32, s32 *, s32, s32);
s32 func_1506196C(struct127 *, s32);

// blob_shadow_draw: emits the display list of a blob shadow record rec (set up by func_1510E004 this frame, which
// sets rec[0x123] when it is visible): its translation Mtx (this frame's +0x10 slot) to the floor point (+0x114 x,
// +0x11C floor y, +0x118 z), the texture D_80091B20[rec[0x121]] when it changed (D_800DD5E4), geometry mode off,
// the prim alpha rec[0x122] * owner alpha / 256 when it changed (D_800DD5F6) - owner alpha from func_1506196C for
// an object owner (rec[0x120] 0), else owner u8 +0x8A * u8 +0x8B[idx] / 256 - and the 4 vertices (+0x90 slot) as
// two triangles. Other owner kinds never get rec[0x123] (func_1510E004 returns first). Returns the DL end.
Gfx *func_1510E6A0(Gfx *g, u8 *rec, s16 idx) {
    s16 *mtx;
    u8 *owner;
    s32 tex;
    s32 alpha;

    if (rec[0x123] == 0) {
        return g;
    }
    mtx = (s16 *) (rec + D_800BE9C0 * 0x40 + 0x10);
    func_150A7D00(mtx, *(f32 *) (rec + 0x114), *(f32 *) (rec + 0x11C), *(f32 *) (rec + 0x118));
    g->words.w0 = 0xDA380003;                     /* gSPMatrix modelview, load, push */
    g->words.w1 = (s32) mtx;
    g++;
    if (rec[0x121] != D_800DD5E4) {
        D_800DD5E4 = rec[0x121];
        tex = func_1510D66C(D_80091B20[rec[0x121]], NULL, 0x3E, 0);
        g->words.w0 = 0xE7000000;                 /* gDPPipeSync */
        g->words.w1 = 0;
        g++;
        g->words.w0 = 0xFD900000;                 /* gDPSetTextureImage */
        g->words.w1 = tex;
        g++;
        g->words.w0 = 0xF3000000;                 /* gDPLoadBlock */
        g->words.w1 = 0x077FF000;
        g++;
    }
    g->words.w0 = 0xE7000000;
    g->words.w1 = 0;
    g++;
    g->words.w0 = 0xD9FFF9FF;                     /* gSPClearGeometryMode */
    g->words.w1 = 0;
    g++;
    owner = *(u8 **) (rec + 0x110);
    if (rec[0x120] == 0) {
        alpha = func_1506196C((struct127 *) owner, idx);
    } else if (rec[0x120] == 1) {
        alpha = (owner[0x8B + idx] * owner[0x8A] + 0xFF) >> 8;
    } else {
        alpha = 0; /* not reached (the asm reads a stale stack word) */
    }
    alpha = (rec[0x122] * alpha + 0xFF) >> 8;
    if (alpha != D_800DD5F6) {
        D_800DD5F6 = alpha;
        g->words.w0 = 0xE7000000;
        g->words.w1 = 0;
        g++;
        g->words.w0 = 0xFA000100;                 /* gDPSetPrimColor: alpha */
        g->words.w1 = alpha & 0xFF;
        g++;
    }
    g->words.w0 = 0x01004008;                     /* gSPVertex: 4 vertices */
    g->words.w1 = (s32) (rec + D_800BE9C0 * 0x40 + 0x90);
    g++;
    g->words.w0 = 0x05000204;                     /* gSP1Triangle 0 1 2 */
    g->words.w1 = 0;
    g++;
    g->words.w0 = 0x05000406;                     /* gSP1Triangle 0 2 3 */
    g->words.w1 = 0;
    g++;
    g->words.w0 = 0xE7000000;
    g->words.w1 = 0;
    g++;
    return g;
}
