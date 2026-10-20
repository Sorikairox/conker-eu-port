s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
s32 func_151EFDD0(void);

void func_150E5AD8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    struct {
        f32 u28[13];
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        u8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 pad91[0x1];
        s8 u92;
        u8 pad93[0x1];
        s32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        u8 padA0[0x6];
    } sp;
    f32 a;
    f32 b;
    f32 t;

    bzero(&sp, sizeof(sp));
    if (arg4 != 0.0f) {
        a = func_150484A0(arg3, arg4) * 57.295776f;
    } else {
        a = 90.0f;
    }
    if (arg5 != 0.0f) {
        b = func_150484A0(arg3, arg5) * 57.295776f;
    } else {
        b = 90.0f;
    }
    sp.u28[5] = b;
    sp.u28[6] = a;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u28[0] = 1.0f;
    sp.u28[2] = 0.17f;
    sp.u28[3] = 0.17f;
    sp.u28[10] = arg0;
    sp.u28[11] = arg1;
    sp.u28[12] = arg2;
    sp.u28[4] = 0.0f;
    if (arg6 == 4) {
        sp.u28[1] = 0.6f;
        sp.u7E = 6;
    } else if (arg6 == 9) {
        sp.u28[1] = 0.3f;
        sp.u7E = 8;
    } else {
        sp.u28[1] = 0.3f;
        sp.u7E = 7;
    }
    sp.u7C = (func_151EFDD0() % 60) + 60;
    sp.u78 = 0x29E9;
    t = (func_150ADA68() * 4.6f) + 1.5f;
    sp.u74 = -0.78f;
    sp.u5C = t * arg3;
    sp.u60 = -t * arg4;
    sp.u64 = t * arg5;
    sp.u68 = (func_150ADA68() * 6.0f) + -3.0f;
    sp.u70 = (func_150ADA68() * 6.0f) + -3.0f;
    sp.u6C = (func_150ADA68() * 6.0f) + -3.0f;
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = 0xFF;
    sp.u89 = 1;
    sp.u8A = 0;
    sp.u8B = 3;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u92 = 2;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 0x20;
    sp.u9C = 7;
    func_15132FBC(&sp, 3, 0xFF, 0, 0xFF, 0);
}
