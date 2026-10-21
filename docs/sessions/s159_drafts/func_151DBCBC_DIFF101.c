extern u8 D_800AB7F4[][3];

typedef struct {
    s32 u0;
    s16 u4;
    u8 u6;
    u8 u7;
    s32 u8;
    s32 uC;
    u8 u10;
    u8 u11;
    u8 u12[3];
    u8 u15;
    u8 u16;
    u8 u17;
    s32 u18;
    s32 u1C;
    u8 u20;
    s16 u22;
    s16 u24;
} BlkBCBC;

void func_151DBCBC(u8 arg0, f32 arg1, s16 arg2, s32 arg3, void *arg4, u8 arg5, s32 arg6) {
    s32 r0;
    s32 r1;
    BlkBCBC s;
    u8 *c = D_800AB7F4[arg0];

    s.u0 = 0x67B02;
    s.u4 = 0x12C;
    s.u6 = 0x38;
    s.u7 = 0;
    s.u8 = 0;
    s.uC = 0x8000;
    s.u10 = arg2;
    s.u11 = 0xFF;
    s.u12[0] = c[0];
    s.u12[1] = c[1];
    s.u12[2] = c[2];
    s.u15 = 0xFF;
    s.u16 = 0;
    s.u17 = 6;
    s.u18 = 0x440001;
    s.u1C = 0;
    s.u20 = 0xFF;
    s.u22 = 1;
    s.u24 = 0xFF;
    if (arg3 != 0) {
        r0 = func_150ADA20();
        r1 = func_150ADA20();
        func_1513C73C((s32)&s, 0, 0, arg3, ((f32 *)arg4)[0], ((f32 *)arg4)[1], ((f32 *)arg4)[2], arg1, arg1, r0 & 0xFF, ((func_150ADA20() & 1) * 2) + (r1 & 1), 0, arg5, arg6);
        return;
    }
    func_1513C5B0((s32)&s, 0, 0, 0, ((f32 *)arg4)[0], ((f32 *)arg4)[1], ((f32 *)arg4)[2], arg1, arg1, 0, 0, 0, arg5, arg6);
}
