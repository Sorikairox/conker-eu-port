// ambient_place_points_fixed_8: placer type 3: as type 2 with phase range 8.
s32 func_1500BAB8(s16 count, u8 kind, s32 slot, s32 mode, s32 index, s16 **tri) {
    s32 i;
    f32 a;
    s16 x;
    s32 y;
    s32 z;

    for (i = 0; i != count; i++) {
        a = (f32) (tri[1][0] - tri[0][0]) * D_80096014[i][0] + (f32) tri[0][0];
        x = (s32) (((f32) tri[2][0] - a) * D_80096014[i][1] + a);
        a = (f32) (tri[1][1] - tri[0][1]) * D_80096014[i][0] + (f32) tri[0][1];
        y = (s32) (((f32) tri[2][1] - a) * D_80096014[i][1] + a);
        a = (f32) (tri[1][2] - tri[0][2]) * D_80096014[i][0] + (f32) tri[0][2];
        z = (s32) (((f32) tri[2][2] - a) * D_80096014[i][1] + a);
        index = func_1500AF08(index, slot, mode, x, y, z, 0, kind, index);
    }
    D_800DE000[slot] = 8;
    return index;
}
