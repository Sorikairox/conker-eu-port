s32 func_15142A5C(u8 *, u8 *);

s32 func_151C75E8(u8 *arg0) {
    u8 *p;
    f32 f;

    p = *(u8 **)(arg0 + 0x7C);
    if (*(u16 *)(p + 0x84) != 0xE9) {
        return 0;
    }
    if (func_15142A5C(p, arg0) != 0) {
        *(s32 *)(arg0 + 0x60) |= 0x20000;
    } else {
        *(s32 *)(arg0 + 0x60) &= ~0x20000;
    }
    f = *(f32 *)(p + 0x4C) * 35.0f;
    if (f > 255.0f) {
        f = 255;
    } else if (f < 0.0f) {
        f = 0.0f;
    }
    arg0[0x70] = f;
    return 1;
}
