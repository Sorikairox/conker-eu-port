s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);

void func_151CB128(u8 *arg0, u8 arg1) {
    s32 pad[4];
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
    } sp;
    struct {
        u8 * f0;
        f32 f4;
        f32 f8;
        s8 fC;
        s8 fD;
        u8 padE[0x4A];
    } b;
    f32 var_f0;
    s32 temp_v0;
    s32 var_v0;

    b.f0 = arg0;
    b.f4 = 0.0f;
    b.fD = 0;
    b.fC = 0;
    b.f8 = 130.0f;
    if (D_80082FA0 > 0) {
        var_f0 = 2.0f;
    } else {
        var_f0 = 1.0f;
    }
    sp.f10 = 0x64;
    sp.f12 = 0x12C;
    sp.fC = var_f0 * 12.0f;
    sp.f8 = sp.fC;
    sp.f14 = (1 << (arg0[0x23D] + 0xB)) | 0x50;
    sp.f1A = 7;
    sp.f18 = 0xFF;
    sp.f16 = 1;
    sp.f1B = 0xFF;
    sp.f1C = 0xC8;
    sp.f1E = 0x82;
    sp.f1F = 0xFF;
    sp.f20 = 0xFF;
    sp.f1D = 0;
    sp.f21 = 0xFF;
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
    sp.f0 = 0.0f;
    sp.f4 = 0.0f;
    sp.f44 = arg0[0x23D];
    if (arg1) {
        var_v0 = 4;
    } else {
        var_v0 = 0;
    }
    temp_v0 = func_151559FC(&sp, var_v0 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &b, 0x58);
    }
}
