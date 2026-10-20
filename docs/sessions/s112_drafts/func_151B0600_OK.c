void func_15143794(s16, s16, f32, void *);
s32 func_151DA6F8(f32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_151B0600(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s16 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    f32 v[3];
    f32 sp68[3];
    f32 r;

    v[0] = arg2;
    v[1] = arg3;
    v[2] = arg4;
    r = func_150ADA68();
    func_15143794(arg9, arg8, (r * 5.3f) + 4.4f, sp68);
    func_151DA6F8(v, sp68, (func_150ADA68() * (f32)0) + 0.68f, (func_150ADA20() % 20U) + 0x1F, (func_150ADA20() % 101U) + 0x9B, (func_150ADA68() * 2.33f) + 6.7f, (func_150ADA20() & 1) + 3, 1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, argE, 1); // fakematch: (f32)0 keeps the rand * 0 multiply (0.0f folds it)
    return 1;
}
