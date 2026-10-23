void func_15048F90(struct17 *a, struct17 *b, struct17 *out);
void func_1504917C(struct17 *v, struct17 *out);
void func_15049148(struct17 *v, f32 len, struct17 *out);
void func_150498A0(f32 *cur, f32 target, f32 *vel, f32 arg3, f32 arg4, f32 arg5);
s32 func_150A44A4(f32 x, f32 z, s32 tri, u8 *packed, f32 *out);
void func_1510ED24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
s32 func_1512C6C0(struct108 *);
void func_151236D0(struct108 *);
extern s16 D_800898F0;
extern f32 D_800A39F4;
extern f32 D_800A39F8;
extern f32 D_800A39FC;
/* camera_follow_update: camera mode 0x40 (func_151283B8). Unless D_800898F0 is 0 or +0x73C is set: the pivot
 * +0x27C = +0x288; the camera target is the pivot plus the direction pivot -> eye (+0x2BC) scaled to the eye
 * distance minus +0x278 (at least 0), its y part scaled by D_800A39F4 unless +0x704 & 0xF. The camera position
 * +0x2F8 eases towards it (func_150498A0 with velocity +0x3C0, rates 3 / 2 / 3, +0x7B4), or snaps there (also
 * +0x304, velocity 0) when +0x23C. Then func_1512C6C0; when snapped, flag 0x400000 of +0x84, or no floor under
 * the camera (func_150A44A4 into +0x35C), the collision probe func_1510ED24 runs (+0x360 kept unless the result
 * +0x364 equals D_800A39FC) and func_151236D0. Finally the four zoom pairs +0x964..+0x980 = 1 / 2. */
void func_15129EA4(struct108 *cam) {
    u8 *c = (u8 *) cam;
    f32 dir[3];
    s32 probe[4];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 tx;
    f32 ty;
    f32 tz;

    if (D_800898F0 == 0 || *(s16 *) (c + 0x73C) != 0) {
        return;
    }
    *(f32 *) (c + 0x27C) = *(f32 *) (c + 0x288);
    *(f32 *) (c + 0x280) = *(f32 *) (c + 0x28C);
    *(f32 *) (c + 0x284) = *(f32 *) (c + 0x290);
    func_15048F90((struct17 *) (c + 0x27C), (struct17 *) (c + 0x2BC), (struct17 *) dir);
    func_1504917C((struct17 *) dir, (struct17 *) dir);
    dx = *(f32 *) (c + 0x2BC) - *(f32 *) (c + 0x27C);
    dy = *(f32 *) (c + 0x2C0) - *(f32 *) (c + 0x280);
    dz = *(f32 *) (c + 0x2C4) - *(f32 *) (c + 0x284);
    dist = sqrtf(dx * dx + dy * dy + dz * dz) - *(f32 *) (c + 0x278);
    if (dist < 0.0f) {
        dist = 0.0f;
    }
    func_15049148((struct17 *) dir, dist, (struct17 *) dir);
    tx = *(f32 *) (c + 0x27C) + dir[0];
    if (*(s32 *) (c + 0x704) & 0xF) {
        ty = *(f32 *) (c + 0x280);
    } else {
        ty = *(f32 *) (c + 0x280) + dir[1] * D_800A39F4;
    }
    tz = *(f32 *) (c + 0x284) + dir[2];
    if (c[0x23C] != 0) {
        *(f32 *) (c + 0x2F8) = tx;
        *(f32 *) (c + 0x304) = tx;
        *(f32 *) (c + 0x3C0) = 0.0f;
    } else {
        func_150498A0((f32 *) (c + 0x2F8), tx, (f32 *) (c + 0x3C0), 1.0f, 3.0f, *(f32 *) (c + 0x7B4));
    }
    if (c[0x23C] != 0) {
        *(f32 *) (c + 0x2FC) = ty;
        *(f32 *) (c + 0x308) = ty;
        *(f32 *) (c + 0x3C4) = 0.0f;
    } else {
        func_150498A0((f32 *) (c + 0x2FC), ty, (f32 *) (c + 0x3C4), 1.0f, 2.0f, *(f32 *) (c + 0x7B4));
    }
    if (c[0x23C] != 0) {
        *(f32 *) (c + 0x300) = tz;
        *(f32 *) (c + 0x30C) = tz;
        *(f32 *) (c + 0x3C8) = 0.0f;
    } else {
        func_150498A0((f32 *) (c + 0x300), tz, (f32 *) (c + 0x3C8), 1.0f, 3.0f, *(f32 *) (c + 0x7B4));
    }
    func_1512C6C0(cam);
    if (c[0x23C] != 0 || (*(s32 *) (c + 0x84) & 0x400000) ||
        func_150A44A4(*(f32 *) (c + 0x2F8), *(f32 *) (c + 0x300), *(s32 *) (c + 0x644), c + 0x648,
                      (f32 *) (c + 0x35C)) == 0) {
        func_1510ED24(0, 0, (s32) probe, (s32) (c + 0x360), (s32) (c + 0x640), 0, *(f32 *) (c + 0x2F8),
                      *(f32 *) (c + 0x2FC), *(f32 *) (c + 0x300), *(f32 *) (c + 0x2FC), 0, 0, D_800A39F8,
                      *(f32 *) (c + 0x2FC));
        if (D_800A39FC != *(f32 *) (c + 0x364)) {
            *(f32 *) (c + 0x360) = *(f32 *) (c + 0x364);
        }
        func_151236D0(cam);
    }
    *(f32 *) (c + 0x974) = 1.0f;
    *(f32 *) (c + 0x964) = 1.0f;
    *(f32 *) (c + 0x97C) = 1.0f;
    *(f32 *) (c + 0x96C) = 1.0f;
    *(f32 *) (c + 0x978) = 2.0f;
    *(f32 *) (c + 0x968) = 2.0f;
    *(f32 *) (c + 0x980) = 2.0f;
    *(f32 *) (c + 0x970) = 2.0f;
}
