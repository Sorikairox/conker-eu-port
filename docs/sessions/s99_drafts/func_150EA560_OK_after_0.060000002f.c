s32 func_15134DAC(void *, s32, u8 *, s16);
s32 func_150EA560(u8 *arg0, s16 arg1, f32 arg2, u8 arg3) {
    struct {
        u8 u2C;
        u8 *u30;
        u8 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        u8 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        u8 u5A;
        u8 u5B;
        u8 u5C;
        f32 u60;
        u8 u64;
        s8 u65;
    } sp;
    s32 obj;
    struct {
        s32 u18;
        s32 u1C;
        f32 u20;
        f32 u24;
    } t;

    sp.u2C = arg0[0x3B];
    sp.u38 = -9.0f;
    sp.u30 = arg0;
    sp.u34 = 8;
    sp.u3C = -14.0f;
    sp.u48 = -14.0f;
    sp.u50 = 2;
    sp.u52 = 0x3C;
    sp.u54 = 0x3C;
    sp.u56 = arg1;
    sp.u5A = 2;
    sp.u5B = 2;
    sp.u5C = 2;
    sp.u64 = 3;
    sp.u65 = -1;
    t.u18 = 0;
    t.u1C = 0x11111;
    sp.u40 = 27.0f;
    sp.u44 = -21.0f;
    sp.u4C = 41.0f;
    sp.u60 = 0.5f;
    t.u20 = 0.2f;
    t.u24 = 0.06f;
    obj = func_15134DAC(&sp, 0x10, arg0, arg1);
    if (obj != 0) {
        memcpy(obj + 0x80, &t, 0x10);
    }
    return obj;
}
