extern f32 D_80096014[];
s32 func_1500AF08(s32, s32, s32, s16, s32, s32, s32, s32, s32);

s32 func_1500B1F4(s16 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, s16 **arg5) {
    s32 i;
    f32 *t;
    f32 x;
    f32 y;
    f32 z;
    s16 X;
    s32 Y;
    s32 Z;
    s16 *a;
    s16 *b;
    s16 *c;

    i = 0;
    if (arg0 != 0) {
        t = D_80096014;
        do {
            b = arg5[1];
            a = arg5[0];
            c = arg5[2];
            x = ((f32) (b[0] - a[0]) * t[0]) + (f32) a[0];
            X = (((f32) c[0] - x) * t[1]) + x;
            y = ((f32) (b[1] - a[1]) * t[0]) + (f32) a[1];
            Y = (((f32) c[1] - y) * t[1]) + y;
            z = ((f32) (b[2] - a[2]) * t[0]) + (f32) a[2];
            Z = (((f32) c[2] - z) * t[1]) + z;
            arg4 = func_1500AF08(arg4, arg2, arg3, X, Y, Z, 0x80, arg1, arg4);
            i++;
            t += 2;
        } while (i != arg0);
    }
    return arg4;
}
