s32 func_1510EDAC(s32 *, s32, f32 *, s32, s32 *, s32, f32, f32, f32, f32, s32, s32);
extern f32 D_800A7534;
extern f32 D_800A7538;
s32 func_15173090(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, u8 arg7) {
    f32 a;
    f32 c;
    f32 d;
    s32 unk;
    f32 y;
    s32 hit;

    a = (arg4 - 90.0f) * D_800A7534;
    c = cosf(a);
    d = arg5;
    arg1 += d * sinf(a);
    arg3 += d * c;
    func_1510EDAC(&hit, 0, &y, 0, &unk, 0, arg1, arg2, arg3, arg2, 0, 0);
    if (hit == 0) {
        return 0;
    }
    if (y == D_800A7538) {
        return 0;
    }
    return func_15172B6C(arg0, hit, arg1, y, arg3, arg4, arg6, arg7);
}
