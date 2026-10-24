extern f32 D_8009A500; /* 1 / 12 */

// path_jump_to_point: P210: script command: jump (ballistic) to point D_800D1891 of the object's path
// (D_800D2104[unk13F]); unk21E = that point. Flight time t = 2 * distance / speed (unk44); below 12 the speed is
// scaled by t / 12 and t = 12. unk21C = t * 100, upward velocity = gravity * t / 2, unk223 = 4.
void func_1507602C(void) {
    s16 *pt;
    f32 dx, dz;
    f32 t;

    func_15075548();
    D_800D154C->unk21E = D_800D1891;
    pt = (s16 *)(D_800D2104[D_800D154C->unk13F] + D_800D1891 * 8 + 8);
    dx = pt[0] - D_800D154C->x_position;
    dz = pt[2] - D_800D154C->z_position;
    t = sqrtf(dx * dx + dz * dz) / D_800D154C->unk44;
    t = t + t;
    if (t < 12.0f) {
        D_800D154C->unk44 = D_800D154C->unk44 * (t * D_8009A500);
        t = 12.0f;
    }
    D_800D154C->unk21C = t * 100.0f;
    D_800D154C->y_velocity = D_800D154C->gravity * t * 0.5f;
    D_800D154C->unk223 = 4;
}
