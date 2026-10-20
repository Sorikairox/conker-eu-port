typedef struct {
    s16 u0[4];
    f32 u8;
    f32 uC;
    f32 u10;
    s16 u14;
    s16 u16;
    f32 u18;
    f32 u1C;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    u8 u2C;
    u8 u2D;
    f32 u30;
    f32 u34;
    u8 u38;
    u8 u39;
    f32 u3C;
    u8 u40;
    f32 u44;
} S2700;
s32 func_151506E8(S2700 *, f32 *, s32, u8, s32);

s32 func_150C2700(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    extern f32 D_800A064C;
    S2700 s;

    s.u10 = arg4;
    s.u8 = arg2;
    s.uC = arg3;
    s.u14 = 6;
    s.u16 = 5;
    s.u0[0] = 0x6B;
    s.u0[1] = 0x46;
    s.u0[2] = -0x1F;
    s.u0[3] = 0x2E;
    s.u20 = 0x64;
    s.u22 = 0;
    s.u2C = 0x9B;
    s.u2D = 0x64;
    s.u34 = 0.0f;
    s.u38 = 1;
    s.u39 = 6;
    s.u3C = 0.0f;
    s.u40 = 1;
    s.u44 = 0.0f;
    s.u18 = 30.0f;
    s.u1C = 35.0f;
    s.u24 = -2.328f;
    s.u28 = 1.6630001f;
    s.u30 = D_800A064C;
    func_151506E8(&s, &s.u8, 0, argE, 1);
    return 1;
}
