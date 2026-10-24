#ifdef NON_MATCHING
extern u8 D_800DA130[];
extern u8 *D_800CCA08;

// object_screen_uv_project: D_80089FC8 kind-3 handler (s32 (u8 *, s32), called by func_1513B83C; same scheme as
// sky_dome_project_uv) of a 20-vertex record rec attached to an object (rec + +0x50 + 0xF8 = {obj, obj id}) for
// player view `slot`: releases the record (func_1516972C) when the object is gone or replaced; returns 0 (not
// drawn) when the object has no matrix, is hidden ((+0x74 & 0xF) == 0xF) or is the object this view looks from
// (+0x318 / +0x31C rider check when D_800BE616, else D_800CCA08 / D_800CCA0C). Otherwise copies the object's
// matrix (+0x1D4 + 0x40, fixed point when D_800C42B0), with its fourth column set to (0, 0, 0, 1), into this frame's Mtx (rec +0x78 +
// D_800BE9C0 * 0x40), and maps each vertex of the slot's copy to texture coordinates: its screen position (object
// matrix, then view matrix D_800DA130[slot]) times 2.002, relative to the screen position of the object point
// (0, 67, 159) truncated to a multiple of 1024. Returns 1.
s32 func_151BA634(u8 *rec, s32 slot) {
    f32 view[4][4];
    f32 m[4][4];
    f32 ox, oy, oz;
    f32 cx, cy, cz;
    f32 wx, wy, wz;
    f32 sx, sy, sz;
    f32 baseX, baseY;
    u8 *p;
    u8 *obj;
    u8 *mtx;
    u8 *rider;
    Vtx *v;
    s32 i;

    slot = (s16) slot;
    p = rec + *(s32 *) (rec + 0x50) + 0xF8;
    obj = *(u8 **) p;
    if (*(s32 *) obj == 0 || p[4] != obj[0x3B]) {
        func_1516972C((struct102 *) rec);
    }
    mtx = *(u8 **) (obj + 0x1D4);
    if (mtx == NULL) {
        return 0;
    }
    if ((obj[0x74] & 0xF) == 0xF) {
        return 0;
    }
    if (D_800BE616) {
        rider = *(u8 **) (obj + 0x318);
        if (rider != NULL && *(u8 **) (obj + 0x31C) != NULL && (*(u8 **) (obj + 0x31C))[0x197] != 0
            && rider[0x23D] == slot) {
            return 0;
        }
    } else if (D_800CCA08 != NULL && D_800CCA0C != NULL && D_800CCA0C[0x197] != 0 && D_800CCA08[0x23D] == slot) {
        return 0;
    }
    if (D_800C42B0) {
        guMtxL2F(m, (Mtx *) (mtx + 0x40));
    } else {
        memcpy(m, mtx + 0x40, 0x40);
    }
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    guMtxF2L(m, (Mtx *) (rec + 0x78 + D_800BE9C0 * 0x40));
    memcpy(view, D_800DA130 + slot * 0x40, 0x40);
    view[0][3] = 0.0f;
    view[1][3] = 0.0f;
    view[2][3] = 0.0f;
    view[3][3] = 1.0f;
    func_150A7E40(m, 0.0f, 67.0f, 159.0f, &ox, &oy, &oz);
    func_150A7E40(view, ox, oy, oz, &cx, &cy, &cz);
    cx *= 2.002f;
    cy *= 2.002f;
    baseX = (s32) (cx * (1.0f / 1024.0f)) * 1024.0f;
    baseY = (s32) (cy * (1.0f / 1024.0f)) * 1024.0f;
    for (i = 0; i < 20; i++) {
        v = *(Vtx **) (rec + D_800BE9C0 * 0x10 + slot * 4 + 0x58) + i;
        func_150A7E40(m, v->v.ob[0], v->v.ob[1], v->v.ob[2], &wx, &wy, &wz);
        func_150A7E40(view, wx, wy, wz, &sx, &sy, &sz);
        sx *= 2.002f;
        sy *= 2.002f;
        v->v.tc[0] = (s32) (sx - baseX);
        v->v.tc[1] = (s32) (sy - baseY);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E7CC0/func_151BA634.s")
#endif
