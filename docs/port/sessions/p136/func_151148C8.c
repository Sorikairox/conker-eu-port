void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

/*
 * world_object_rotate_point: rotates the point (*px, *py, *pz) by world-object record idx (D_800DBEF4, 0xA0 bytes)
 * around its pivot (s16 +0x10/+0x12/+0x14). The record's three base angles (f32 +0 about X, +8 about Z, +4 about Y,
 * each skipped when 0) first turn the local axes X/Y/Z (guRotateF + func_150A7E40 on the two other axes); the
 * matrix is then R(+0x60, X) * R(+0x68, Z) * R(+0x64, Y) about those axes (func_150A7A48 = matrix product).
 * Rare's result kept: each coordinate gets s16 offset (+0x5A/+0x5C/+0x5E) + (rotated - unrotated) added, where
 * the unrotated value is relative to the pivot.
 */
void func_151148C8(s32 idx, f32 *px, f32 *py, f32 *pz) {
    f32 ax[3], ay[3], az[3];
    f32 m2[4][4];
    f32 m[4][4];
    f32 ox, oy, oz;
    f32 dx, dy, dz;
    f32 rx, ry, rz;
    u8 *rec;

    ax[0] = 1.0f; ax[1] = 0.0f; ax[2] = 0.0f;
    ay[0] = 0.0f; ay[1] = 1.0f; ay[2] = 0.0f;
    az[0] = 0.0f; az[1] = 0.0f; az[2] = 1.0f;
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    dx = *px - (f32) *(s16 *) (rec + 0x10);
    dy = *py - (f32) *(s16 *) (rec + 0x12);
    dz = *pz - (f32) *(s16 *) (rec + 0x14);
    if (*(f32 *) (rec + 0) != 0.0f) {
        guRotateF(m, *(f32 *) (rec + 0), 1.0f, 0.0f, 0.0f);
        func_150A7E40(m, ay[0], ay[1], ay[2], &ay[0], &ay[1], &ay[2]);
        func_150A7E40(m, az[0], az[1], az[2], &az[0], &az[1], &az[2]);
        rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    }
    if (*(f32 *) (rec + 8) != 0.0f) {
        guRotateF(m, *(f32 *) (rec + 8), az[0], az[1], az[2]);
        func_150A7E40(m, ay[0], ay[1], ay[2], &ay[0], &ay[1], &ay[2]);
        func_150A7E40(m, ax[0], ax[1], ax[2], &ax[0], &ax[1], &ax[2]);
        rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    }
    if (*(f32 *) (rec + 4) != 0.0f) {
        guRotateF(m, *(f32 *) (rec + 4), ay[0], ay[1], ay[2]);
        func_150A7E40(m, ax[0], ax[1], ax[2], &ax[0], &ax[1], &ax[2]);
        func_150A7E40(m, az[0], az[1], az[2], &az[0], &az[1], &az[2]);
        rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    }
    guRotateF(m, *(f32 *) (rec + 0x60), ax[0], ax[1], ax[2]);
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    guRotateF(m2, *(f32 *) (rec + 0x68), az[0], az[1], az[2]);
    func_150A7A48(m, m2, m);
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    guRotateF(m2, *(f32 *) (rec + 0x64), ay[0], ay[1], ay[2]);
    func_150A7A48(m, m2, m);
    func_150A7E40(m, dx, dy, dz, &ox, &oy, &oz);
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    rx = (f32) *(s16 *) (rec + 0x5A) + (ox - dx);
    ry = (f32) *(s16 *) (rec + 0x5C) + (oy - dy);
    rz = (f32) *(s16 *) (rec + 0x5E) + (oz - dz);
    *px += rx;
    *py += ry;
    *pz += rz;
}
