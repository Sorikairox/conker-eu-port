void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
// sprite_quad_build_scaled: builds the 4 corner vertices (+-half width +0x2C, +-half height +0x30, z 0) of a
// sprite effect's quad for display list slot `slot`: rotation from the angles +0x40/+0x44/+0x48, matrix rows scaled
// by +0x4C/+0x50/+0x54, translated to +0x34/+0x38/+0x3C. func_151D6310 hands out the slot's vertex buffer (pointer
// table at +0x100); when it is new, both halves (0x40 bytes each) are first filled from the template at +0xC0.
// Returns the written vertices, or NULL when no buffer is available. (Draw-table D_8008A1BC entry.)
u8 *func_1513E83C(u8 *fx, s16 slot) {
    f32 corner[4][3];
    f32 mtx[4][4];
    u8 *vtx;
    u8 *start;
    u8 fresh;
    s16 i;

    func_151D6310((s32 *)(fx + 0x100), slot, 0x40, (s32 *)&vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **)(fx + 0x100 + slot * 4), fx + 0xC0, 0x40);
        memcpy(*(u8 **)(fx + 0x100 + slot * 4) + 0x40, fx + 0xC0, 0x40);
    }
    corner[0][0] = *(f32 *)(fx + 0x2C);
    corner[0][1] = *(f32 *)(fx + 0x30);
    corner[1][0] = -*(f32 *)(fx + 0x2C);
    corner[1][1] = *(f32 *)(fx + 0x30);
    corner[2][0] = -*(f32 *)(fx + 0x2C);
    corner[2][1] = -*(f32 *)(fx + 0x30);
    corner[3][0] = *(f32 *)(fx + 0x2C);
    corner[3][1] = -*(f32 *)(fx + 0x30);
    func_150A8050(mtx, *(f32 *)(fx + 0x40), *(f32 *)(fx + 0x44), *(f32 *)(fx + 0x48));
    mtx[3][0] = *(f32 *)(fx + 0x34);
    mtx[3][1] = *(f32 *)(fx + 0x38);
    mtx[3][2] = *(f32 *)(fx + 0x3C);
    mtx[0][0] *= *(f32 *)(fx + 0x4C);
    mtx[0][1] *= *(f32 *)(fx + 0x4C);
    mtx[0][2] *= *(f32 *)(fx + 0x4C);
    mtx[1][0] *= *(f32 *)(fx + 0x50);
    mtx[1][1] *= *(f32 *)(fx + 0x50);
    mtx[1][2] *= *(f32 *)(fx + 0x50);
    mtx[2][0] *= *(f32 *)(fx + 0x54);
    mtx[2][1] *= *(f32 *)(fx + 0x54);
    mtx[2][2] *= *(f32 *)(fx + 0x54);
    for (i = 0; i < 4; i++) {
        func_150A7E40(mtx, corner[i][0], corner[i][1], 0.0f, &corner[i][0], &corner[i][1], &corner[i][2]);
        *(s16 *)(vtx + 0) = (s32)corner[i][0];
        *(s16 *)(vtx + 2) = (s32)corner[i][1];
        *(s16 *)(vtx + 4) = (s32)corner[i][2];
        *(s16 *)(vtx + 6) = 0;
        vtx += 0x10;
    }
    return start;
}
