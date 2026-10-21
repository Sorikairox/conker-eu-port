s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);
extern f32 D_800AB164[];
extern f32 D_800AB18C[];

void func_151CBBAC(u8 *arg0, u8 arg1, u8 arg2, s8 arg3, u8 arg4) {
    s32 pad[2];
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
        s8 fE;
        u8 padF[0x1];
        f32 f10;
        f32 f14;
        s32 f18;
        f32 f1C;
        s32 f20;
        u8 pad24[0x30];
        s8 f54;
        u8 pad55[0x3];
    } b;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_v1_2;
    s8 var_v1;

    b.f4 = 255.0f;
    b.f8 = 255.0f;
    b.fD = arg1;
    b.f0 = arg0;
    if (arg3 == -1) {
        var_v1 = 0;
    } else {
        var_v1 = 4;
    }
    b.fC = var_v1;
    b.f54 = arg3;
    b.f14 = 255.0f;
    sp.f12 = 0x12C;
    sp.f8 = 49.0f;
    b.f10 = 0.0f;
    sp.fC = 18.0f;
    if (arg2) {
        var_v1_2 = 0x40;
    } else {
        var_v1_2 = 0;
    }
    sp.f14 = var_v1_2 | 0x32 | (1 << (arg0[0x23D] + 0xB));
    sp.f1A = 7;
    sp.f1B = 0xFF;
    sp.f16 = 1;
    sp.f1C = 0xFF;
    sp.f1D = 0xFF;
    sp.f1F = 0xFF;
    sp.f20 = 0xFF;
    sp.f21 = 0xFF;
    sp.f18 = 0xFF;
    sp.f22 = 0xFF;
    sp.f23 = 0xFF;
    sp.f24 = 0;
    sp.f28 = 0x200004;
    sp.f2C = 0x1F0601;
    sp.f30 = 7;
    sp.f34 = 0x22;
    sp.f38 = 0x80;
    sp.f3C = 0x20;
    sp.f40 = 0;
    sp.f41 = 7;
    temp_t4 = D_80082FA0 == 1;
    b.fE = 0;
    sp.f1E = 0xFF;
    sp.f10 = 0x7B;
    b.f1C = 0.0f;
    sp.f44 = arg0[0x23D];
    sp.f0 = 88.0f;
    sp.f4 = 91.0f;
    b.f18 = D_800AB164[temp_t4];
    b.f20 = D_800AB18C[temp_t4];
    temp_v0 = func_151559FC(&sp, 5, 0, 0, 0x58, (s32) arg4, 0);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &b, 0x58);
    }
    sp.f1E = 0;
    sp.f10 = 0x7C;
    temp_v0_2 = func_151559FC(&sp, 5, 0, 0, 0x58, (s32) arg4, 0);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &b, 0x58);
    }
    sp.f14 &= 0xFFFD;
    sp.f1E = 0xFF;
    sp.f10 = 0x7B;
    b.fE = 1;
    sp.f0 = -88.0f;
    sp.f4 = 91.0f;
    temp_v0_3 = func_151559FC(&sp, 5, 0, 0, 0x58, (s32) arg4, 0);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x70, &b, 0x58);
    }
    sp.f1E = 0;
    sp.f10 = 0x7C;
    temp_v0_4 = func_151559FC(&sp, 5, 0, 0, 0x58, (s32) arg4, 0);
    if (temp_v0_4 != 0) {
        memcpy(temp_v0_4 + 0x70, &b, 0x58);
    }
}
