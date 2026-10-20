void func_151A15C0(f32 arg0, f32 arg1, f32 arg2, s16 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7) {
    s16 n;
    s16 m;
    s16 a;
    s16 b;
    s16 c;
    s16 d;

    n = arg3 - 0x20;
    m = n;
    if (n <= 0) {
        m = 1;
    }
    a = 70.0f * arg5;
    b = 30.0f * arg5;
    c = 1500.0f * arg4;
    d = 100.0f * arg4;
    func_151A177C(arg0, arg1, arg2, 250.0f * arg4, 1.0f, a, b, c, d, 0x12, 1.0f, 90.0f * arg5, 20.0f * arg5, c, d, m, 0x10, 1.0f, a, b, c, d, 15.0f * arg4, 10.0f * arg4, 0x12, n + 0x10, arg6, arg7);
}
