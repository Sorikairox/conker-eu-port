f32 func_150489B0(u8);

// path_point_from_object: P210: script command: sets point D_800D1890 & 0x3F of the current object's path
// (D_800D2104[unk13F], s16 x / y / z after an 8-byte header) to an offset from object unk222 (D_800CC2D0). The
// offset is x = 8 * (s8 D_800D1891 << 4 | D_800D1893 >> 4), z = 8 * (s8 D_800D1892 << 4 | D_800D1893 & 0xF),
// rotated by the object's heading (D_800D1890 bits 6-7 = 0), not rotated (1), or by the direction from the
// object to the current one (2, 3); y is the object's height. D_800D1890 keeps the masked point number.
void func_15078544(void) {
    u8 cmd = D_800D1890;
    struct127 *o;
    s32 mode;
    f32 ox, oz;
    f32 x, y, z;
    f32 s, c;
    s16 *pt;

    D_800D1890 = cmd & 0x3F;
    o = &D_800CC2D0[D_800D154C->unk222];
    ox = (((s8)D_800D1891 << 4) | (D_800D1893 >> 4)) << 3;
    oz = (((s8)D_800D1892 << 4) | (D_800D1893 & 0xF)) << 3;
    mode = cmd >> 6;
    y = o->y_position;
    x = o->x_position;
    z = o->z_position;
    if (mode == 0) {
        u8 a = (o->unk7A >> 8) - 0x40;

        s = func_15048A40(a);
        c = func_150489B0(a);
    } else if (mode == 1) {
        s = 0.0f;
        c = 1.0f;
    } else {
        f32 ang = func_150484A0(D_800D154C->x_position - x, D_800D154C->z_position - z);

        s = sinf(ang);
        c = cosf(ang);
    }
    x += ox * c + oz * s;
    z += oz * c - ox * s;
    pt = (s16 *)(D_800D2104[D_800D154C->unk13F] + D_800D1890 * 8 + 8);
    pt[0] = x;
    pt = (s16 *)(D_800D2104[D_800D154C->unk13F] + D_800D1890 * 8 + 8);
    pt[1] = y;
    pt = (s16 *)(D_800D2104[D_800D154C->unk13F] + D_800D1890 * 8 + 8);
    pt[2] = z;
}
