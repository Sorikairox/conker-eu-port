extern u8 D_8008D3B0[][6];
Gfx *func_1517FAD4(Gfx *gfx) {
    u8 *c;
    s32 r, g;
    f32 t;
    s32 a;

    if (D_800DDE08 == 0) {
        return gfx;
    }
    if (D_800DE1BB == 0) {
        return gfx;
    }
    a = D_800DE1BB;
    if (D_800DE1BC != 0) {
        a = ((func_15048A40(D_800DE1B9) + 1.0f) * 0.5f) * D_800DE1BB;
        t = 0.0f;
    }
    c = D_8008D3B0[D_800DE1BA];
    r = (c[3] - c[0]) * t + c[0];
    g = (c[4] - c[1]) * t + c[1];
    return func_1517F5FC(gfx, a, r, g, (c[5] - c[2]) * t + c[2], 0);
}
