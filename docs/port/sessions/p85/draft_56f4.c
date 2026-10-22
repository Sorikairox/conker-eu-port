s32 func_151ACBD4(s8 *, s32);

/*
 * P85: spawn handler: a vertical zone from record rec (s16 position +0 / +2 / +4, s16 length +8, angles +0xC / +0x10
 * as f32 bits, kind +0x18). Kinds below 6 / 7 / 2 are skipped on levels 0xB / 0x2C / 0x26. The far end is the
 * (0, length, 0) direction rotated by the angles (not added to the position, as in the original); the upper / lower
 * point (by y) and the height |dy| go to func_151ACBD4 with the kind. Always returns 1.
 */
s32 func_150156F4(u8 *rec) {
    f32 m[4][4];
    f32 pos[3];
    f32 pts[2][3];
    struct {
        s8 kind;
        u8 pad1[3];
        f32 top[3];    /* the point with the larger y */
        f32 bottom[3];
        f32 height;
        s8 flag;
    } zone;
    s32 i;

    if (D_800BE9F0 == 0xB) {
        if (*(u32 *) (rec + 0x18) < 6) {
            return 1;
        }
    } else if (D_800BE9F0 == 0x2C) {
        if (*(u32 *) (rec + 0x18) < 7) {
            return 1;
        }
    } else if (D_800BE9F0 == 0x26) {
        if (*(u32 *) (rec + 0x18) < 2) {
            return 1;
        }
    }
    func_150A8050(m, *(f32 *) (rec + 0xC), *(f32 *) (rec + 0x10), 0.0f);
    pos[0] = *(s16 *) (rec + 0);
    pos[1] = *(s16 *) (rec + 2);
    pos[2] = *(s16 *) (rec + 4);
    func_150A7E40(m, 0.0f, *(s16 *) (rec + 8), 0.0f, &pts[1][0], &pts[1][1], &pts[1][2]);
    pts[0][0] = *(s16 *) (rec + 0);
    pts[0][1] = *(s16 *) (rec + 2);
    pts[0][2] = *(s16 *) (rec + 4);
    zone.kind = *(s32 *) (rec + 0x18);
    i = (pts[0][1] < pts[1][1]) ? 1 : 0;
    zone.top[0] = pts[i][0];
    zone.top[1] = pts[i][1];
    zone.top[2] = pts[i][2];
    i = (pts[1][1] < pts[0][1]) ? 1 : 0;
    zone.bottom[0] = pts[i][0];
    zone.bottom[1] = pts[i][1];
    zone.bottom[2] = pts[i][2];
    zone.flag = 0;
    zone.height = fabsf(pts[1][1] - pts[0][1]);
    func_151ACBD4(&zone.kind, 0);
    return 1;
}
