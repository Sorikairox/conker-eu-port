/* Projects the world point (x, y, z) with the current player's view matrix D_800D30C8[D_80082FA4]
 * (func_150A7EE0 -> *sx, *sy, *sz, *w). Behind / too far (w >= far) or too near (w <= D_800D9F40): returns 0.
 * Else *sx / *sy become screen coordinates of that player's viewport (D_800BE628 + player * 0x180: half
 * sizes +0x0C / +0x10 (+ 5), centre +0x34 / +0x38; y points down) and it returns 1. */
s32 func_15095A4C(f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz, f32 *w, f32 far) {
    u8 *vp;
    f32 inv;
    f32 px;
    f32 py;

    func_150A7EE0(D_800D30C8[D_80082FA4], x, y, z, sx, sy, sz, w);
    if (far <= *w || *w <= D_800D9F40) {
        return 0;
    }
    inv = 1.0f / *w;
    vp = (u8 *)D_800BE628 + D_80082FA4 * 0x180;
    px = *sx;
    py = *sy;
    *sx = (*(f32 *)(vp + 0xC) + 5.0f) * px * inv + *(f32 *)(vp + 0x34);
    *sy = *(f32 *)(vp + 0x38) - (*(f32 *)(vp + 0x10) + 5.0f) * py * inv;
    return 1;
}
