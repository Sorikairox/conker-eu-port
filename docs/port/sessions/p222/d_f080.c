/* P222: readable C for func_1518F080 (game_eu_1BAF40, 273 words). */
/* func_151D6310 is declared above in game_eu_1BAF40.c: (s32, s16, s32, u8 **, u8 *) */

// line_quad_build: builds the camera-facing quad of a line effect for display list slot `slot`: the line runs from
// A = +0x34/+0x38/+0x3C towards B = +0x40/+0x44/+0x48, cut at P = A + (B - A) * +0x30. Each end gets two vertices,
// offset by +-(half width +0x2C) along the normal of the plane through the end, the line and the slot's camera
// (D_800DBFF0[slot] +0x2F8): A + n, A - n, P + n, P - n (a zero normal gives offset 0). func_151D6310 hands out the
// slot's vertex buffer (pointer table at +0x100); when it is new, both halves (0x40 bytes each) are first filled from
// the template at +0xC0. Returns the written vertices, or NULL when no buffer is available. (Draw-table entry.)
u8 *func_1518F080(u8 *fx, s16 slot) {
    u8 *vtx;
    u8 *start;
    u8 fresh;
    f32 *cam;
    f32 px, py, pz;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 nx, ny, nz;
    f32 len2, k;

    func_151D6310((s32) (fx + 0x100), slot, 0x40, &vtx, &fresh);
    start = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        memcpy(*(u8 **) (fx + 0x100 + slot * 4), (u8 **) (fx + 0xC0), 0x40);
        memcpy(*(u8 **) (fx + 0x100 + slot * 4) + 0x40, (u8 **) (fx + 0xC0), 0x40);
    }
    px = *(f32 *) (fx + 0x34) + (*(f32 *) (fx + 0x40) - *(f32 *) (fx + 0x34)) * *(f32 *) (fx + 0x30);
    py = *(f32 *) (fx + 0x38) + (*(f32 *) (fx + 0x44) - *(f32 *) (fx + 0x38)) * *(f32 *) (fx + 0x30);
    pz = *(f32 *) (fx + 0x3C) + (*(f32 *) (fx + 0x48) - *(f32 *) (fx + 0x3C)) * *(f32 *) (fx + 0x30);
    cam = (f32 *) ((u8 *) D_800DBFF0 + slot * 0x9A0 + 0x2F8);

    /* end A: normal = (P - A) x (A - camera) */
    dx = px - *(f32 *) (fx + 0x34);
    dy = py - *(f32 *) (fx + 0x38);
    dz = pz - *(f32 *) (fx + 0x3C);
    ex = *(f32 *) (fx + 0x34) - cam[0];
    ey = *(f32 *) (fx + 0x38) - cam[1];
    ez = *(f32 *) (fx + 0x3C) - cam[2];
    nx = dy * ez - ey * dz;
    ny = dz * ex - ez * dx;
    nz = dx * ey - ex * dy;
    len2 = nx * nx + ny * ny + nz * nz;
    if (len2 == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        k = *(f32 *) (fx + 0x2C) / sqrtf(len2);
        nx *= k;
        ny *= k;
        nz *= k;
    }
    *(s16 *) (vtx + 0) = *(f32 *) (fx + 0x34) + nx;
    *(s16 *) (vtx + 2) = *(f32 *) (fx + 0x38) + ny;
    *(s16 *) (vtx + 4) = *(f32 *) (fx + 0x3C) + nz;
    *(s16 *) (vtx + 6) = 0;
    vtx += 0x10;
    *(s16 *) (vtx + 0) = *(f32 *) (fx + 0x34) - nx;
    *(s16 *) (vtx + 2) = *(f32 *) (fx + 0x38) - ny;
    *(s16 *) (vtx + 4) = *(f32 *) (fx + 0x3C) - nz;
    *(s16 *) (vtx + 6) = 0;
    vtx += 0x10;

    /* end P: normal = (A - P) x (P - camera) */
    dx = -dx;
    dy = -dy;
    dz = -dz;
    ex = px - cam[0];
    ey = py - cam[1];
    ez = pz - cam[2];
    nx = dy * ez - ey * dz;
    ny = dz * ex - ez * dx;
    nz = dx * ey - ex * dy;
    len2 = nx * nx + ny * ny + nz * nz;
    if (len2 == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        k = *(f32 *) (fx + 0x2C) / sqrtf(len2);
        nx *= k;
        ny *= k;
        nz *= k;
    }
    *(s16 *) (vtx + 0) = px + nx;
    *(s16 *) (vtx + 2) = py + ny;
    *(s16 *) (vtx + 4) = pz + nz;
    *(s16 *) (vtx + 6) = 0;
    vtx += 0x10;
    *(s16 *) (vtx + 0) = px - nx;
    *(s16 *) (vtx + 2) = py - ny;
    *(s16 *) (vtx + 4) = pz - nz;
    *(s16 *) (vtx + 6) = 0;
    return start;
}
