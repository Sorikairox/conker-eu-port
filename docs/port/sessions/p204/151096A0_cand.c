/* P204 */
// sky_dome_project_uv: D_80089FC8 kind-4 handler (s32 (u8 *, s32), called by func_1513B83C) of a double-buffered
// vertex record rec for player slot `slot`: builds this frame's matrix (rec +0x78 + D_800BE9C0 * 0x40) as a
// translation to (p[0], p[4], p[1]) with p = rec + +0x50 + 0xF8, scaled by 0.157, and maps the 16 vertices of the
// slot's copy (rec +0x58[D_800BE9C0 * 4 + slot]) to texture coordinates: each vertex goes through the matrix; s
// follows its position across the camera direction (func_15144B34(slot), x / z normalised; straight ahead when its
// x and y are both tiny) as 32 * (26 + 0.213 * side), t its height as 32 * (81 + 0.358 * y). Returns 1.
s32 func_151096A0(u8 *rec, s32 slot) {
    f32 mtx[4][4];
    f32 ox;
    f32 oy;
    f32 oz;
    f32 *p;
    f32 *cam;
    f32 inv;
    f32 cx;
    f32 cz;
    Vtx *v;
    s32 i;

    p = (f32 *) (rec + *(s32 *) (rec + 0x50) + 0xF8);
    func_150A8050(mtx, p[0], 0.0f, p[1]);
    mtx[3][1] = p[4];
    mtx[0][0] *= 0.157f;
    mtx[0][1] *= 0.157f;
    mtx[0][2] *= 0.157f;
    mtx[1][0] *= 0.157f;
    mtx[1][1] *= 0.157f;
    mtx[1][2] *= 0.157f;
    mtx[2][0] *= 0.157f;
    mtx[2][1] *= 0.157f;
    mtx[2][2] *= 0.157f;
    guMtxF2L(mtx, (Mtx *) (rec + 0x78 + D_800BE9C0 * 0x40));
    cam = func_15144B34((s16) slot);
    if (fabsf(cam[0]) > 0.0001f || fabsf(cam[1]) > 0.0001f) {
        inv = 1.0f / sqrtf(cam[0] * cam[0] + cam[2] * cam[2]);
        cx = cam[2] * inv;
        cz = -cam[0] * inv;
    } else {
        cx = 1.0f;
        cz = 0.0f;
    }
    for (i = 0; i < 16; i++) {
        v = *(Vtx **) (rec + D_800BE9C0 * 0x10 + (s16) slot * 4 + 0x58) + i;
        func_150A7E40(mtx, v->v.ob[0], v->v.ob[1], v->v.ob[2], &ox, &oy, &oz);
        v->v.tc[0] = (s32) (((ox * cx + oz * cz) * 0.21300001f + 26.0f) * 32.0f);
        v->v.tc[1] = (s32) ((oy * 0.358f + 81.0f) * 32.0f);
    }
    return 1;
}
