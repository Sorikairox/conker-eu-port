typedef struct { u8 rgb[4][3]; } S8FC88;
extern S8FC88 D_8008FC88;
extern f32 D_800A910C;
s32 func_151A2C9C(s32, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef void (*Fn31D4)(s32, s16, s16, f32, f32, f32 *);

s32 func_151A31D4(s32 arg0, s32 arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 argA, f32 argB, s16 argC, s16 argD, s16 argE, s16 argF, s16 arg10, s16 arg11, s8 arg12, u8 arg13, s32 arg14, u8 arg15) {
    s16 minv;
    Fn31D4 fn;
    f32 dir[3];
    f32 pos[3];
    S8FC88 cols;
    f32 t;
    f32 step;
    s16 r0;
    s32 r1;
    s32 r2;
    s32 ci;
    f32 fr;

    if (arg15 == 0) {
        fn = (Fn31D4)func_151A3134;
    } else {
        fn = (Fn31D4)func_151A3180;
    }
    if (arg10 < arg11) {
        minv = arg10;
    } else {
        minv = arg11;
    }
    t = 0.0f;
    step = 1.0f / (f32)arg7;
    for (; arg7 != 0; arg7--) {
        r0 = (func_150ADA20() % (u32)(argD + 1)) + argC;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_15143794(r1 & 0xFF, r2 & 0xFF, func_150ADA68() * arg8, dir);
        fn(arg1, arg2, arg3, arg4, t, pos);
        cols = D_8008FC88;
        ci = func_150ADA20() & 3;
        fr = func_150ADA68();
        r1 = func_150ADA20();
        if (func_150ADA68() < D_800A910C) {
            r2 = 0x19;
        } else {
            r2 = -1;
        }
        func_151A2C9C(arg0, dir, pos, arg9, fr * argB + argA, arg6 * t + arg5, r0 + minv, ((u32)r1 % (argF + 1)) + argE, arg10, arg11, r2, arg12, cols.rgb[ci][0], cols.rgb[ci][1], cols.rgb[ci][2], arg13, arg14);
        t += step;
    }
}
