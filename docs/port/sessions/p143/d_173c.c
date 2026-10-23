extern f32 D_800AA6D0;
extern f32 D_800AA6D4;
extern f32 D_800AA6D8;
// debris_fall_update: update handler (D_8008A058 slot 16) of a falling debris sprite. Motion block at +0x110:
// velocity x/y/z, gravity +0x11C; x / z speeds are multiplied by 0.25 * dt each frame, y gains gravity * dt; the
// position +0x34 moves by the mean speed, the trail point +0x40 moves with it and then eases back towards the
// position (factor D_800AA6D0). With floor check (+0x134) a floor probe (func_15046F70, from the previous height
// minus the half height +0x30) that hits ends the sprite (0) and spawns a splash at the floor + 5: either
// func_151D9B8C (scale D_800AA6D4) or the ring func_151DAB58 (scale D_800AA6D8), of type +0x135, sized by the mean
// of +0x124 + +0x12C / 2 and +0x128 + +0x130 / 2. Returns 1 while it keeps falling.
s32 func_151B173C(u8 *fx) {
    f32 *mv = (f32 *)(fx + 0x110);
    f32 probe[3];
    f32 hit[3];
    f32 y0, vx0, vz0, vy, dvy;
    f32 dx, dy, dz;
    f32 x, y, z;
    f32 size;
    s8 ret;

    y0 = *(f32 *)(fx + 0x38);
    vx0 = mv[0];
    vz0 = mv[2];
    ret = 1;
    mv[0] = vx0 * (0.25f * D_800BE9A4);
    mv[2] = vz0 * (0.25f * D_800BE9A4);
    dx = (mv[0] + vx0) * 0.5f * D_800BE9A4;
    vy = mv[1];
    dvy = mv[3] * D_800BE9A4;
    dy = vy * D_800BE9A4 + dvy * D_800BE9A4 * 0.5f;
    dz = (mv[2] + vz0) * 0.5f * D_800BE9A4;
    mv[1] = vy + dvy;
    *(f32 *)(fx + 0x38) = y0 + dy;
    *(f32 *)(fx + 0x34) += dx;
    *(f32 *)(fx + 0x3C) += dz;
    *(f32 *)(fx + 0x40) += dx;
    *(f32 *)(fx + 0x44) += dy;
    *(f32 *)(fx + 0x48) += dz;
    x = *(f32 *)(fx + 0x34);
    y = *(f32 *)(fx + 0x38);
    z = *(f32 *)(fx + 0x3C);
    *(f32 *)(fx + 0x40) = x + (*(f32 *)(fx + 0x40) - x) * D_800AA6D0;
    *(f32 *)(fx + 0x44) = y + (*(f32 *)(fx + 0x44) - y) * D_800AA6D0;
    *(f32 *)(fx + 0x48) = z + (*(f32 *)(fx + 0x48) - z) * D_800AA6D0;
    if (fx[0x134] != 0) {
        probe[0] = x;
        probe[1] = y0 - *(f32 *)(fx + 0x30);
        probe[2] = *(f32 *)(fx + 0x3C);
        if (func_15046F70(probe, 0, *(f32 *)(fx + 0x38) - *(f32 *)(fx + 0x30), (f32 *)(fx + 0x78)) != 0) {
            hit[0] = probe[0];
            hit[1] = *(f32 *)(fx + 0x78) + 5.0f;
            hit[2] = probe[2];
            size = ((mv[5] + mv[7] * 0.5f) + (mv[6] + mv[8] * 0.5f)) * 0.5f;
            if (func_150ADA20() & 1) {
                func_151D9B8C(fx[0x135], size * D_800AA6D4, fx[0x5C], (s32)(fx + 0x7C), (struct17 *)hit, 100, 0, 1, 0,
                              fx[0xC], fx[1]);
            } else {
                func_151DAB58(fx[0x135], size * D_800AA6D8, fx[0x5C], hit, 1, fx[0xC], fx[1]);
            }
            ret = 0;
        }
    }
    return ret;
}
