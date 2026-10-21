void func_151CCAD4(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    Spawn559A a;
    s32 pad2; // fakematch: 4-byte hole between blocks
    Spawn559B b;
    s32 ret;

    b.u0 = arg0;
    b.u4 = 0.0f;
    b.u8 = 130.0f;
    b.uD = 0;
    b.uC = 0;
    a.u50 = 0.0f;
    a.u54 = 0.0f;
    a.u12 = 0x12C;
    a.u14 = (arg4 ? 0x40 : 0) | 0x390 | (1 << (arg0[0x23D] + 0xB));
    a.u16 = 1;
    a.u18 = 0xFF;
    a.u1A = 7;
    a.u1B = arg1;
    a.u1C = arg2;
    a.u1D = arg3;
    a.u1E = 0x82;
    a.u1F = 0xFF;
    a.u20 = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u30 = 8;
    a.u34 = 0x44;
    a.u38 = 0x80;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 0xA;
    a.u48 = 0.2f;
    a.u44 = arg0[0x23D];
    a.u4C = 1.0f;
    a.u8 = 30.0f;
    a.uC = 4.2f;
    a.u4 = -37.0f;
    a.u10 = 0x9A;
    a.u0 = 0.0f;
    ret = func_151559FC(&a, 9, 0, 0, 0x58, arg5, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
    a.u0 = -37.0f;
    a.u4 = 0.0f;
    a.u8 = 4.2f;
    a.uC = 30.0f;
    a.u10 = 0x9B;
    a.u48 = 1.0f;
    a.u4C = 0.2f;
    ret = func_151559FC(&a, 9, 0, 0, 0x58, arg5, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
}
