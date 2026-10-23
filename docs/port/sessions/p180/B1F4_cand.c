// ambient_place_points: placer type 0: `count` emitters on the triangle at the (u, v) points D_80096014[i]
// (p = v0 + (v1 - v0) u, then p + (v2 - p) v per axis), spread 0x80; returns the next emitter index.
s32 func_1500B1F4(s16 count, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    s32 i;
    f32 a;
    s16 x;
    s32 y;
    s32 z;

    if (count == 0) {
        return index;
    }
    for (i = 0; i != count; i++) {
        a = (f32) (tri[1][0] - tri[0][0]) * D_80096014[i][0] + (f32) tri[0][0];
        x = (s32) (((f32) tri[2][0] - a) * D_80096014[i][1] + a);
        a = (f32) (tri[1][1] - tri[0][1]) * D_80096014[i][0] + (f32) tri[0][1];
        y = (s32) (((f32) tri[2][1] - a) * D_80096014[i][1] + a);
        a = (f32) (tri[1][2] - tri[0][2]) * D_80096014[i][0] + (f32) tri[0][2];
        z = (s32) (((f32) tri[2][2] - a) * D_80096014[i][1] + a);
        index = func_1500AF08(index, slot, mode, x, y, z, 0x80, kind, index);
    }
    return index;
}
