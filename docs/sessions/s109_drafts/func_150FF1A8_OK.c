s32 func_151030B8(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);

void func_150FF1A8(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    f32 v[2];
    s32 r[3];

    v[1] = func_150ADA68() * 1.001f + 0.60400003f;
    v[0] = func_150ADA68() * 5.9f + 14.1f;
    r[0] = func_150ADA20();
    r[1] = func_150ADA20();
    func_151030B8(arg0, arg1, arg2, arg3, v, (r[0] & 3) + 6, 0xFF, func_150ADA68() * 270.0f + 359.0f, arg4, 0xFF, 0, -1, arg5, arg6);
}
