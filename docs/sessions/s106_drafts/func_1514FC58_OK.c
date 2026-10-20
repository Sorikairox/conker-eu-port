s32 func_15145128(u8 *, u8 *, void *, void *);
s32 func_15146078(u8 *, s32 *, s32 *);
s32 func_1514FC58(u8 *arg0) {
    s32 f;
    f = arg0[0];
    if (!(f & 1)) {
        if (func_15145128(arg0 + 4, arg0 + 4, 0, 0) == 0) {
            return 0;
        }
        *(f32 *)(arg0 + 4) *= 1000.0f;
        f = arg0[0] |= 1;
        *(f32 *)(arg0 + 8) *= 1000.0f;
        *(f32 *)(arg0 + 0xC) *= 1000.0f;
    }
    if (!(f & 2)) {
        if (func_15146078(arg0 + 4, (s32 *)(arg0 + 0x10), (s32 *)(arg0 + 0x1C)) == 0) {
            return 0;
        }
        f = arg0[0] |= 6;
    }
    if (!(f & 4)) {
        if (func_15145128(arg0 + 0x10, arg0 + 0x10, 0, 0) == 0) {
            return 0;
        }
        if (func_15145128(arg0 + 0x1C, arg0 + 0x1C, 0, 0) == 0) {
            return 0;
        }
        arg0[0] |= 4;
    }
    return 1;
}
