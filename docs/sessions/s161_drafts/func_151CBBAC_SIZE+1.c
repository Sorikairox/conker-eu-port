extern f32 D_800AB164[];
extern f32 D_800AB18C[];

void func_151CBBAC(u8 *arg0, u8 arg1, u8 arg2, s8 arg3, u8 arg4) {
    Spawn559A a;
    s32 ret;
    Spawn559B b;

    b.u0 = arg0;
    b.u4 = 255.0f;
    b.u8 = 255.0f;
    b.uC = (arg3 == -1) ? 0 : 4;
    b.uD = arg1;
    b.u54 = arg3;
    b.u14 = 255.0f;
    a.u12 = 0x12C;
    a.u8 = 49.0f;
    b.u10 = 0.0f;
    a.uC = 18.0f;
    a.u14 = (arg2 ? 0x40 : 0) | 0x32 | (1 << (arg0[0x23D] + 0xB));
    a.u16 = 1;
    a.u18 = 0xFF;
    a.u1A = 7;
    a.u1B = 0xFF;
    a.u1C = 0xFF;
    a.u1D = 0xFF;
    a.u1F = 0xFF;
    a.u20 = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u30 = 7;
    a.u34 = 0x22;
    a.u38 = 0x80;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 7;
    a.u44 = arg0[0x23D];
    b.uE = 0;
    a.u1E = 0xFF;
    a.u10 = 0x7B;
    b.u1C = 0.0f;
    a.u0 = 88.0f;
    a.u4 = 91.0f;
    b.u18 = D_800AB164[D_80082FA0 == 1];
    b.u20 = D_800AB18C[D_80082FA0 == 1];
    ret = func_151559FC(&a, 5, 0, 0, 0x58, arg4, 0);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
    a.u1E = 0;
    a.u10 = 0x7C;
    ret = func_151559FC(&a, 5, 0, 0, 0x58, arg4, 0);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
    a.u14 &= ~2;
    a.u1E = 0xFF;
    a.u10 = 0x7B;
    b.uE = 1;
    a.u0 = -88.0f;
    a.u4 = 91.0f;
    ret = func_151559FC(&a, 5, 0, 0, 0x58, arg4, 0);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
    a.u1E = 0;
    a.u10 = 0x7C;
    ret = func_151559FC(&a, 5, 0, 0, 0x58, arg4, 0);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
}
