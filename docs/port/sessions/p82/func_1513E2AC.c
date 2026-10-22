s32 func_1510E908(s32, s32, f32 *, f32 *);
s32 func_15144E80(s32, f32 *, f32 *, s32 *);
s32 func_15145128(f32 *, f32 *, s32 *, s32 *);
/* Corners of a sprite quad (4 Vtx at vtx + 0x40): centre (x, y, z), half sizes w / h, rotated by angle in the
 * screen plane. With a camera (arg2) the quad uses the camera's right / up axes (func_15144E80, normalised by
 * func_15145128); without one it is built in x / z and tilted by the view slopes of func_1510E908(arg1).
 * Returns 0 when the axes are not available. */
s32 func_1513E2AC(s32 vtx, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, f32 w, f32 h, u8 angle) {
    s16 *v = (s16 *)(vtx + 0x40);
    f32 c = func_151423D8((u8)(angle - 0x40));
    f32 s = func_151423D8(angle);
    f32 right[3];
    f32 up[3];
    f32 rx, ry, rz;
    f32 ux, uy, uz;
    f32 ws, wc, hc, hs;
    f32 slopeX, slopeZ;
    f32 pt[4][2];
    f32 a, b, ta, tb, fa, fb;
    s16 i;

    if (arg2 != 0) {
        if (func_15144E80(arg2, right, up, NULL) == 0) {
            return 0;
        }
        func_15145128(right, right, NULL, NULL);
        func_15145128(up, up, NULL, NULL);
        ws = w * s;
        wc = w * c;
        rx = ws * right[0] + wc * up[0];
        ry = ws * right[1] + wc * up[1];
        rz = ws * right[2] + wc * up[2];
        hc = -h * c;
        hs = h * s;
        ux = hc * right[0] + hs * up[0];
        uy = hc * right[1] + hs * up[1];
        uz = hc * right[2] + hs * up[2];
        v[0] = (s32)((x - rx) + ux);
        v[1] = (s32)((y - ry) + uy);
        v[2] = (s32)((z - rz) + uz);
        v[8] = (s32)((x + rx) + ux);
        v[9] = (s32)((y + ry) + uy);
        v[10] = (s32)((z + rz) + uz);
        v[16] = (s32)((x + rx) - ux);
        v[17] = (s32)((y + ry) - uy);
        v[18] = (s32)((z + rz) - uz);
        v[24] = (s32)((x - rx) - ux);
        v[25] = (s32)((y - ry) - uy);
        v[26] = (s32)((z - rz) - uz);
        return 1;
    }
    if (func_1510E908(arg1, arg2, &slopeX, &slopeZ) == 0) {
        return 0;
    }
    ws = w * s;
    hc = h * c;
    hs = h * s;
    wc = w * c;
    pt[0][0] = ws - hc;
    pt[0][1] = hs + wc;
    pt[1][0] = -ws - hc;
    pt[1][1] = hs - wc;
    pt[2][0] = -ws + hc;
    pt[2][1] = -hs - wc;
    pt[3][0] = ws + hc;
    pt[3][1] = -hs + wc;
    for (i = 0; i < 4; i++) {
        b = pt[i][0];
        a = pt[i][1];
        ta = a * slopeZ;
        if (b == 0.0f) {
            tb = 0.0f;
            fb = 0.0f;
        } else {
            tb = b * slopeX;
            fb = fabsf(b) / sqrtf(b * b + tb * tb);
        }
        if (a == 0.0f) {
            ta = 0.0f;
            fa = 0.0f;
        } else {
            fa = fabsf(a) / sqrtf(a * a + ta * ta);
        }
        v[0] = (s32)(b * fb + x);
        v[1] = (s32)(((fb * tb + y) + fa * ta) + 0.5f);
        v[2] = (s32)(pt[i][1] * fa + z);
        v += 8;
    }
    return 1;
}
