s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);

void func_151CCAD4(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    struct {
        f32 f0;
        f32 f4;
        f32 f8;
        f32 fC;
        u8 f10;
        u8 pad11[0x1];
        s16 f12;
        u16 f14;
        s16 f16;
        s16 f18;
        u8 f1A;
        u8 f1B;
        u8 f1C;
        u8 f1D;
        u8 f1E;
        u8 f1F;
        u8 f20;
        u8 f21;
        u8 f22;
        u8 f23;
        s32 f24;
        s32 f28;
        s32 f2C;
        s32 f30;
        s32 f34;
        s32 f38;
        s32 f3C;
        u8 f40;
        u8 f41;
        u8 pad42[0x2];
        u8 f44;
        u8 pad45[0x3];
        f32 f48;
        f32 f4C;
        f32 f50;
        f32 f54;
    } sp;
    struct {
        u8 * f0;
        f32 f4;
        f32 f8;
        s8 fC;
        s8 fD;
        u8 padE[0x4A];
    } b;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;

    b.f4 = 0.0f;
    b.fD = 0;
    b.fC = 0;
    sp.f50 = 0.0f;
    sp.f54 = 0.0f;
    sp.f12 = 0x12C;
    b.f0 = arg0;
    b.f8 = 130.0f;
    if (arg4 != 0) {
        var_v0 = 0x40;
    } else {
        var_v0 = 0;
    }
    sp.f16 = 1;
    sp.f14 = var_v0 | 0x390 | (1 << (arg0[0x23D] + 0xB));
    sp.f1B = arg1;
    sp.f1C = arg2;
    sp.f1A = 7;
    sp.f1E = 0x82;
    sp.f1F = 0xFF;
    sp.f20 = 0xFF;
    sp.f21 = 0xFF;
    sp.f1D = arg3;
    sp.f18 = 0xFF;
    sp.f22 = 0xFF;
    sp.f23 = 0xFF;
    sp.f24 = 0;
    sp.f28 = 0x200004;
    sp.f2C = 0x1F0601;
    sp.f30 = 8;
    sp.f34 = 0x44;
    sp.f38 = 0x80;
    sp.f3C = 0x20;
    sp.f40 = 0;
    sp.f41 = 0xA;
    sp.f10 = 0x9A;
    sp.f0 = 0.0f;
    sp.f48 = 0.2f;
    sp.f44 = arg0[0x23D];
    sp.f4C = 1.0f;
    sp.f8 = 28.0f;
    sp.fC = 4.2f;
    sp.f4 = -37.0f;
    temp_v0 = func_151559FC(&sp, 9, 0, 0, 0x58, (s32) arg5, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &b, 0x58);
    }
    sp.f10 = 0x9B;
    sp.f4 = 0.0f;
    sp.f48 = 1.0f;
    sp.f4C = 0.2f;
    sp.f8 = 4.2f;
    sp.fC = 28.0f;
    sp.f0 = -37.0f;
    temp_v0_2 = func_151559FC(&sp, 9, 0, 0, 0x58, (s32) arg5, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &b, 0x58);
    }
}
