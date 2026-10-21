s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);

void func_151CD2CC(u8 *arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 pad[6];
    struct {
        f32 u0;
        f32 u4;
        f32 u8;
        f32 uC;
        u8 u10;
        s16 u12;
        u16 u14;
        s16 u16;
        s16 u18;
        u8 u1A;
        u8 u1B;
        u8 u1C;
        u8 u1D;
        u8 u1E;
        u8 u1F;
        u8 u20;
        u8 u21;
        u8 u22;
        u8 u23;
        s32 u24;
        s32 u28;
        s32 u2C;
        s32 u30;
        s32 u34;
        s32 u38;
        s32 u3C;
        u8 u40;
        u8 u41;
        u8 u44;
    } sp;
    struct {
        u8 *p;
        f32 f4;
        f32 f8;
        s8 cC;
        s8 cD;
        u8 pad[0x4A];
    } b;
    s32 temp_v0;

    b.f4 = 0.0f;
    b.cD = 0;
    b.cC = 0;
    b.p = arg0;
    sp.u12 = 0x12C;
    b.f8 = 130.0f;
    sp.u14 = (1 << (arg0[0x23D] + 0xB)) | 0x50;
    sp.u1B = arg1;
    sp.u1C = arg2;
    sp.u1A = 7;
    sp.u1E = 0xB4;
    sp.u1F = 0xFF;
    sp.u16 = 1;
    sp.u20 = 0xFF;
    sp.u21 = 0xFF;
    sp.u1D = arg3;
    sp.u18 = 0xFF;
    sp.u22 = 0xFF;
    sp.u23 = 0xFF;
    sp.u24 = 0;
    sp.u28 = 0x200004;
    sp.u2C = 0x1F0601;
    sp.u30 = 8;
    sp.u34 = 0x44;
    sp.u38 = 0x80;
    sp.u3C = 0x20;
    sp.u40 = 0;
    sp.u41 = 0xA;
    sp.u0 = 0.0f;
    sp.u4 = 0.0f;
    sp.u10 = 0xB4;
    sp.u8 = 65.0f;
    sp.uC = 65.0f;
    sp.u44 = arg0[0x23D];
    temp_v0 = func_151559FC(&sp, 0, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &b, 0x58);
    }
}
