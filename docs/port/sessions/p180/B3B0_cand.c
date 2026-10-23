// ambient_place_shape: placer type 4: emitters at the (x, z) offsets of point list D_80083110[shape] around the
// triangle's centroid, y on the triangle's plane (func_15049350; the centroid's y when the plane is vertical);
// phase = D_800BE850 >> slot, then the slot's D_800BE850 bit flips. Returns the next emitter index.
s32 func_1500B3B0(s16 shape, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    f32 v[3][3];
    f32 cx = 0.0f;
    f32 cy = 0.0f;
    f32 cz = 0.0f;
    f32 *pts;
    u32 k;
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < 3; i++) {
        v[i][0] = tri[i][0];
        v[i][1] = tri[i][1];
        v[i][2] = tri[i][2];
        cx += v[i][0] / 3.0f;
        cy += v[i][1] / 3.0f;
        cz += v[i][2] / 3.0f;
    }
    func_15049350(*(s32 *) &v[0][0], v[0][1], v[0][2], v[1][0], v[1][1], v[1][2], v[2][0], v[2][1], v[2][2]);
    pts = D_80083110[shape];
    for (k = 1; (f32) k <= pts[0] * 2.0f; k += 2) {
        x = pts[k] + cx;
        z = pts[k + 1] + cz;
        if (D_800CC634 == 0.0f) {
            y = cy;
        } else {
            y = (D_800CC63C - D_800CC630 * x - D_800CC638 * z) / D_800CC634;
        }
        index = func_1500AF08(index, slot, mode, (s32) x, (s32) y, (s32) z, 0x80, kind, D_800BE850 >> slot);
    }
    D_800BE850 ^= 1 << slot;
    return index;
}
