s32 func_1514672C(u8 *);
s32 func_15046F70(f32 *, s32, f32, f32 *);
void func_151DAB58(u8, f32, u8, f32 *, u8, u8, s32);
void func_151DBCBC(u8, f32, s16, s32, void *, u8, s32);
extern f32 D_800A83FC;
extern f32 D_800A8400;
// drop_fall_update: update handler (D_8008A058 slot 13) of a falling drop / debris sprite. Motion block at +0x110:
// velocity x/y/z, gravity +0x11C, drag +0x120 (x / z speeds times drag * dt each frame), trail easing +0x128 (the
// trail point +0x40 follows the position +0x34). Ends (0) when func_1514672C rejects the new position (out of the
// level); a floor probe (func_15046F70, floor y to +0x148) that hits also ends it and spawns a splash at the floor,
// sized by width +0x2C * height +0x30: kind +0x165 == 3 -> func_151DBCBC (0.25), else randomly func_151D9B8C
// (D_800A83FC, life 80..120) or the ring func_151DAB58 (D_800A8400), of type +0x16C, owner data +0x14C.
s32 func_15191A90(u8 *fx) {
    f32 *mv = (f32 *)(fx + 0x110);
    f32 probe[3];
    f32 y0, vx0, vz0, vy, dvy;
    f32 dx, dy, dz;
    f32 x, y, z;
    s8 ret;

    y0 = *(f32 *)(fx + 0x38);
    vx0 = mv[0];
    vz0 = mv[2];
    ret = 1;
    mv[0] = vx0 * (mv[4] * D_800BE9A4);
    mv[2] = vz0 * (mv[4] * D_800BE9A4);
    dx = (mv[0] + vx0) * 0.5f * D_800BE9A4;
    vy = mv[1];
    dvy = mv[3] * D_800BE9A4;
    dy = vy * D_800BE9A4 + dvy * D_800BE9A4 * 0.5f;
    dz = (mv[2] + vz0) * 0.5f * D_800BE9A4;
    mv[1] = vy + dvy;
    *(f32 *)(fx + 0x34) += dx;
    *(f32 *)(fx + 0x38) = y0 + dy;
    *(f32 *)(fx + 0x3C) += dz;
    *(f32 *)(fx + 0x40) += dx;
    *(f32 *)(fx + 0x44) += dy;
    *(f32 *)(fx + 0x48) += dz;
    x = *(f32 *)(fx + 0x34);
    y = *(f32 *)(fx + 0x38);
    z = *(f32 *)(fx + 0x3C);
    *(f32 *)(fx + 0x40) = x + (*(f32 *)(fx + 0x40) - x) * mv[6];
    *(f32 *)(fx + 0x44) = y + (*(f32 *)(fx + 0x44) - y) * mv[6];
    *(f32 *)(fx + 0x48) = z + (*(f32 *)(fx + 0x48) - z) * mv[6];
    probe[0] = x;
    probe[1] = y0 - *(f32 *)(fx + 0x30);
    probe[2] = *(f32 *)(fx + 0x3C);
    if (func_1514672C((u8 *)probe) == 0) {
        return 0;
    }
    if (func_15046F70(probe, 0, *(f32 *)(fx + 0x38) - *(f32 *)(fx + 0x30), (f32 *)(fx + 0x148)) != 0) {
        probe[1] = *(f32 *)(fx + 0x148);
        if (fx[0x165] == 3) {
            func_151DBCBC(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * 0.25f, fx[0x5C], (s32)(fx + 0x14C),
                          probe, fx[0xC], fx[1]);
        } else if (func_150ADA20() & 1) {
            func_151D9B8C(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * D_800A83FC, fx[0x5C],
                          (s32)(fx + 0x14C), (struct17 *)probe, (func_150ADA20() % 41U) + 0x50, 1, 1, 0, fx[0xC],
                          fx[1]);
        } else {
            func_151DAB58(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * D_800A8400, fx[0x5C], probe, 1,
                          fx[0xC], fx[1]);
        }
        ret = 0;
    }
    return ret;
}
