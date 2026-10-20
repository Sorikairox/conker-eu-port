s32 func_1507E7E4(struct127 *, u8, u8, s32, s32);

s32 func_1506D584(void) {
    f32 f;
    u8 a;
    u8 b;
    u32 c;

    if (D_800D154C->unk70 != 0x2A) {
        f = D_800D154C->unk2D0->unk10;
        a = D_800D1580 >> 24;
        b = D_800D1580 >> 16;
        c = D_800D1580 & 0xFFFF;
        if (f == 0.0f) {
            f = 0.01f;
        }
        if (c != 0xFFFF) {
            c = (u32)(c / f) & 0xFFFF;
        }
        return func_1507E7E4(D_800D154C, a, b, c, 0);
    }
}
