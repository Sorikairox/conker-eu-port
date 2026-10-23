s32 memcpy(void *, void *, s32);
// path_record_create: allocates a path record (func_15167A68 kind 0x2D, 0x80 bytes + `extra` + 24 bytes per point
// of def's count at +2), copies the 0x50-byte definition to +0x10, points +0x64 at the point array (+0x80) and +0x60
// past it, zeroes the first point and +0x68 / +0x6C..+0x7B, sets the last point to (0, 0, 1) and +0x7C to
// count * 64 + 0x140. Returns the record or NULL.
u8 *func_151A7F00(u8 *def, s32 extra, u8 arg2, s32 arg3) {
    u8 *rec;
    f32 *pt;
    s16 n = *(s16 *)(def + 2);

    rec = func_15167A68(0x2D, arg3, n * 24 + extra + 0x80, 1, arg2, 1);
    if (rec == NULL) {
        return NULL;
    }
    memcpy(rec + 0x10, def, 0x50);
    *(u8 **)(rec + 0x64) = rec + 0x80;
    *(f32 *)(rec + 0x68) = 0.0f;
    *(u8 **)(rec + 0x60) = rec + 0x80 + *(s16 *)(def + 2) * 24;
    pt = *(f32 **)(rec + 0x64);
    pt[0] = 0.0f;
    pt[1] = 0.0f;
    pt[2] = 0.0f;
    pt = (f32 *)(*(u8 **)(rec + 0x64) + *(s16 *)(def + 2) * 24) - 6;
    pt[0] = 0.0f;
    pt[1] = 0.0f;
    pt[2] = 1.0f;
    bzero(rec + 0x6C, 0x10);
    *(s32 *)(rec + 0x7C) = *(s16 *)(rec + 0x12) * 64 + 0x140;
    return rec;
}
