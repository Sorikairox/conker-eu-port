void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
// sprite_quad_build: builds the 4 corner vertices (+-half width +0x2C, +-half height +0x30, z 0) of a sprite
// effect's quad for display list slot `slot`, rotated by the angles +0x40/+0x44/+0x48 and translated to
// +0x34/+0x38/+0x3C (no scale; func_1513E83C is the scaled variant). New vertex buffers from func_151D6310 are first
// filled (both 0x40-byte halves) from the template at +0xC0. Returns the vertices, or NULL when there is no buffer.
// (Draw-table D_8008A1BC entry.)
u8 *func_1513EE14(u8 *fx, s16 slot) {
    f32 mtx[4][4];
    f32 in[4][2];
    f32 out[4][3];
    u8 *vtx;
    u8 *start;
    u8 fresh;
    s32 i;

    func_151D6310((s32 *)(fx + 0x100), slot, 0x40, (s32 *)&vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **)(fx + 0x100 + slot * 4), fx + 0xC0, 0x40);
        memcpy(*(u8 **)(fx + 0x100 + slot * 4) + 0x40, fx + 0xC0, 0x40);
    }
    func_150A8050(mtx, *(f32 *)(fx + 0x40), *(f32 *)(fx + 0x44), *(f32 *)(fx + 0x48));
    mtx[3][0] = *(f32 *)(fx + 0x34);
    mtx[3][1] = *(f32 *)(fx + 0x38);
    mtx[3][2] = *(f32 *)(fx + 0x3C);
    in[0][0] = *(f32 *)(fx + 0x2C);
    in[0][1] = *(f32 *)(fx + 0x30);
    in[1][0] = -*(f32 *)(fx + 0x2C);
    in[1][1] = *(f32 *)(fx + 0x30);
    in[2][0] = -*(f32 *)(fx + 0x2C);
    in[2][1] = -*(f32 *)(fx + 0x30);
    in[3][0] = *(f32 *)(fx + 0x2C);
    in[3][1] = -*(f32 *)(fx + 0x30);
    for (i = 0; i < 4; i++) {
        func_150A7E40(mtx, in[i][0], in[i][1], 0.0f, &out[i][0], &out[i][1], &out[i][2]);
    }
    for (i = 0; i < 4; i++) {
        *(s16 *)(vtx + 0) = (s32)out[i][0];
        *(s16 *)(vtx + 2) = (s32)out[i][1];
        *(s16 *)(vtx + 4) = (s32)out[i][2];
        *(s16 *)(vtx + 6) = 0;
        vtx += 0x10;
    }
    return start;
}
