extern f32 D_8002C598;
s32 func_1000D96C(s32, s32, s32);

s32 func_1000C7E8(s32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 dx;
    f32 v;
    f32 t;

    if (D_800BE9F0 == 0x31) {
        if (arg0 == 2) {
            return 0;
        }
        if (func_1000B1B0(9) == NULL) {
            func_1000E704(0x3E, 0, 0xFFFF);
            func_1000E40C(0x3E, 0x7FFF);
            func_1000D96C(0x3D, 0x3E, 4);
        }
        return 2;
    }
    if (D_8002B070 == 0) {
        D_8002B070 = 1;
    }
    if (arg0 != D_8002B070) {
        arg0 = D_8002B070;
    }
    dx = arg2 - -4000.0f;
    t = D_8002C598 - sqrtf(dx * dx + arg4 * arg4) * 10.0f;
    v = t;
    if (t < 100.0f) {
        v = 100.0f;
    } else if (t > D_8002C598) {
        v = D_8002C598;
    }
    func_1000E40C(0x3E, v);
    return arg0;
}
