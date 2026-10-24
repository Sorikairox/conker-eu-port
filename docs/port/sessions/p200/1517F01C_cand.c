void func_151108E0(s32, f32 (*)[4], f32, f32, f32);
void func_150A7EE0(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *, f32 *);

// world_to_screen: projects (x, y, z) with the current player's camera (D_800DBFF0[D_80082FA4]: view matrix from
// func_151108E0 with -pitch +0x388, -yaw +0x380 and +0x5EC) into its viewport (D_800BE628 + player * 0x180: half
// width +0xC, half height +0x10). In front (w > 10): *outX / *outY = viewport centre + projected x / - projected y,
// returns 1; else both 0 and returns 0.
s32 func_1517F01C(f32 x, f32 y, f32 z, f32 *outX, f32 *outY) {
    f32 mtx[4][4];
    u8 *cam;
    u8 *vp;
    f32 hw;
    f32 hh;
    f32 inv;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 w;

    cam = (u8 *) D_800DBFF0 + D_80082FA4 * 0x9A0;
    func_151108E0(D_80082FA4, mtx, -*(f32 *) (cam + 0x388), -*(f32 *) (cam + 0x380), *(f32 *) (cam + 0x5EC));
    vp = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
    hw = *(f32 *) (vp + 0xC);
    hh = *(f32 *) (vp + 0x10);
    func_150A7EE0(mtx, x, y, z, &sx, &sy, &sz, &w);
    if (10.0f < w) {
        inv = 1.0f / w;
        sx = sx * hw * inv;
        sy = sy * hh * inv;
        *outX = hw + sx;
        *outY = hh - sy;
        return 1;
    }
    *outX = 0.0f;
    *outY = 0.0f;
    return 0;
}
