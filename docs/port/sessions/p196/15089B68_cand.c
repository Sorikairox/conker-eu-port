void func_1512DAD0(u8 *, s32, void *);
u8 func_150894F8(u8 node, u8 type, u8 prev, u8 band);

// rail_camera_spline: spline camera of one player record (D_80087640 + i * 0x84, camera = player + 0x318).
// `release` != 0: camera mode 10 (rec + 0x4C params: +0x58 = 999, +0x5C = 120), then mode 6 with the camera's +0x23D,
// rec[0x49] = 0. Else, on the first call (rec[0x49] == 0): the first type-6 node of band D_800D27C8 + 1 and the next
// three type-6 nodes after it fill rec[0x44..0x47], the player position is kept at rec + 0x38, t (rec + 0x34) = 0,
// camera mode 5, rec[0x49] = 1. Each call t += 0.017 * D_800BE9E4; past 1 the four nodes shift on by one (t stays at
// 1 at the rail end). The eye points are the nodes rec[0x44 + k] (from rec + 0x38 behind the player's yaw +0x40 for
// the first missing one, then extrapolated), the targets their type-4 links; func_15049AD0 interpolates both at t
// into rec + 0x60 / + 0x6C and camera mode 7 takes rec + 0x4C.
void func_15089B68(u8 *rec, u8 *player, s32 release) {
    u8 *cam = *(u8 **) (player + 0x318);
    f32 pt[6][4]; // eye x / y / z, target x / y / z for the four nodes
    f32 t;
    f32 ang;
    u8 want;
    u8 old;
    u8 node;
    s32 had;
    s32 i;
    s32 k;
    s32 j;

    if (cam == NULL) {
        return;
    }
    if (release) {
        *(s32 *) (rec + 0x5C) = 120;
        *(f32 *) (rec + 0x58) = 999.0f;
        func_1512DAD0(*(u8 **) (player + 0x318), 10, rec + 0x4C);
        func_1512DAD0(*(u8 **) (player + 0x318), 6, (void *) (s32) cam[0x23D]);
        rec[0x49] = 0;
        return;
    }
    if ((s8) rec[0x49] == 0) {
        want = D_800D27C8 + 1;
        for (i = 0; i < D_80087630; i++) {
            if (((u8 *) &D_800D2778[i])[0xE] == 6 && ((u8 *) &D_800D2778[i])[0xF] == want) {
                rec[0x44] = i;
                break;
            }
        }
        rec[0x45] = func_150894F8(rec[0x44], 6, 0xFF, 0);
        rec[0x46] = func_150894F8(rec[0x45], 6, rec[0x44], 0);
        rec[0x47] = func_150894F8(rec[0x46], 6, rec[0x45], 0);
        *(f32 *) (rec + 0x38) = *(f32 *) (player + 0x14);
        *(f32 *) (rec + 0x3C) = *(f32 *) (player + 0x18);
        *(f32 *) (rec + 0x34) = 0.0f;
        *(f32 *) (rec + 0x40) = *(f32 *) (player + 0x1C);
        func_1512DAD0(*(u8 **) (player + 0x318), 5, (void *) (s32) cam[0x23D]);
        rec[0x49] = 1;
    }
    *(f32 *) (rec + 0x34) += 0.017f * (f32) D_800BE9E4;
    t = *(f32 *) (rec + 0x34);
    if (1.0f <= t) {
        node = rec[0x46];
        if (node == 0xFF) {
            *(f32 *) (rec + 0x34) = 1.0f;
        } else {
            old = rec[0x45];
            rec[0x45] = node;
            *(f32 *) (rec + 0x34) = t - 1.0f;
            rec[0x46] = rec[0x47];
            rec[0x44] = old;
            rec[0x47] = func_150894F8(rec[0x46], 6, node, 0);
        }
    }

    had = 0;
    for (k = 0; k < 4; k++) {
        if (rec[0x44 + k] != 0xFF) {
            had = 1;
            func_1508712C(rec[0x44 + k], &pt[0][k], &pt[1][k], &pt[2][k]);
            func_1508712C(func_150894F8(rec[0x44 + k], 4, 0xFF, 0), &pt[3][k], &pt[4][k], &pt[5][k]);
        } else if (had == 1) {
            had = 0;
            ang = *(f32 *) (player + 0x40) * 0.01745;
            pt[0][k] = *(f32 *) (rec + 0x38) - sinf(ang) * 500.0f;
            pt[1][k] = *(f32 *) (rec + 0x3C) + 180.0f;
            pt[2][k] = *(f32 *) (rec + 0x40) - cosf(ang) * 500.0f;
            pt[3][k] = *(f32 *) (rec + 0x38);
            pt[4][k] = *(f32 *) (rec + 0x3C) + 120.0f;
            pt[5][k] = *(f32 *) (rec + 0x40);
        } else if (k >= 2) {
            // the asm also extrapolates at k = 0 / 1 (rec[0x44] == 0xFF) from stack garbage; left 0 here
            for (j = 0; j < 6; j++) {
                pt[j][k] = (pt[j][k - 1] - pt[j][k - 2]) + pt[j][k - 1];
            }
        } else {
            for (j = 0; j < 6; j++) {
                pt[j][k] = 0.0f;
            }
        }
    }
    t = *(f32 *) (rec + 0x34);
    *(f32 *) (rec + 0x60) = func_15049AD0((s32 *) pt[0], 0, t);
    *(f32 *) (rec + 0x64) = func_15049AD0((s32 *) pt[1], 0, t);
    *(f32 *) (rec + 0x68) = func_15049AD0((s32 *) pt[2], 0, t);
    *(f32 *) (rec + 0x6C) = func_15049AD0((s32 *) pt[3], 0, t);
    *(f32 *) (rec + 0x70) = func_15049AD0((s32 *) pt[4], 0, t);
    *(f32 *) (rec + 0x74) = func_15049AD0((s32 *) pt[5], 0, t);
    *(s32 *) (rec + 0x4C) = 0;
    *(s32 *) (rec + 0x50) = 0;
    *(f32 *) (rec + 0x7C) = 30.0f;
    *(f32 *) (rec + 0x80) = 30.0f;
    *(f32 *) (rec + 0x78) = 0.0f;
    func_1512DAD0(*(u8 **) (player + 0x318), 7, rec + 0x4C);
}
