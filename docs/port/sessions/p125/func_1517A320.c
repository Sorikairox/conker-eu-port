extern u8 D_8008D450[];

/* flag_wave_update: waves the two vertex buffers of animated mesh slot i (D_800DDE80 entry: Vtx *buf +8 and +4;
 * D_8008D450 entry (0x38 bytes): f32 speed +0x18 / +0x1C, angle (degrees) +0x20 / +0x24, amplitude +0x28). Per
 * buffer: h = sin(angle) * amplitude; vertices 2 and 3 get x = h, the seven vertices of the rodata list
 * D_800A75F0 (4, 9, 13, 14, 15, 17, 19) x = -h / 2,
 * vertex 6 x = -h / 2 + 18 and vertex 8 x = -h / 2 - 18; then the angle advances by its speed, wrapped below 360. */
void func_1517A320(u8 i) {
    static const u8 rows[7] = { 4, 9, 13, 14, 15, 17, 19 };
    s32 *slot;
    u8 *e;
    s16 *buf[2];
    f32 *angle[2];
    f32 *speed[2];
    s16 h;
    s16 m;
    s32 k;
    s32 j;

    slot = &D_800DDE80[i * 5];
    e = D_8008D450 + i * 0x38;
    angle[0] = (f32 *) (e + 0x20);
    angle[1] = (f32 *) (e + 0x24);
    speed[0] = (f32 *) (e + 0x18);
    speed[1] = (f32 *) (e + 0x1C);
    buf[1] = (s16 *) slot[1];
    buf[0] = (s16 *) slot[2];
    for (k = 0; k < 2; k++) {
        h = (s32) (sinf(*angle[k] * 0.017453292f) * *(f32 *) (e + 0x28));
        buf[k][0x20 / 2] = h;
        m = -(h >> 1);
        buf[k][0x30 / 2] = h;
        for (j = 0; j < 7; j++) {
            buf[k][rows[j] * 8] = m;
        }
        buf[k][0x60 / 2] = m + 0x12;
        buf[k][0x80 / 2] = m - 0x12;
        *angle[k] += *speed[k];
        if (*angle[k] >= 360.0f) {
            *angle[k] -= 360.0f;
        }
    }
}
