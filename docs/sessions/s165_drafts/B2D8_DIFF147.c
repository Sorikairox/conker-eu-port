typedef struct { u8 *u0; u8 *u4; u8 *u8; s32 uC; s32 u10; } SB2D8c;
typedef struct { u8 u0; s8 u1; u8 u2; u8 pad3; s16 u4; s8 u6; u8 pad7; } SB2D8d;
s32 func_151604E4(SB2D8d *, s32, s32, s32);
s32 func_151CB2D8(u8 *arg0, u8 arg1) {
    Spawn559A a;
    s32 ret;
    Spawn559B b;
    SB2D8d d;
    SB2D8c c;
    u8 *p;

    b.uD = 0;
    b.uC = 0;
    a.uC = 25.0f;
    a.u8 = 25.0f;
    b.u0 = arg0;
    b.u4 = 0.0f;
    b.u8 = 130.0f;
    if (D_80082FA0 > 0) {
        a.u10 = 0x72;
    } else {
        a.u10 = 0x65;
    }
    a.u12 = 0x12C;
    a.u14 = (1 << (arg0[0x23D] + 0xB)) | 0x50;
    a.u16 = 1;
    a.u1A = 7;
    a.u1C = 0xFF;
    a.u1E = 0x82;
    a.u20 = 0xFF;
    a.u1F = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u30 = 8;
    a.u38 = 0x80;
    a.u18 = 0xFF;
    a.u1B = 0;
    a.u1D = 0;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u34 = 0x44;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 0xA;
    a.u14 &= ~6;
    a.u14 |= 6;
    a.u0 = 25.0f;
    a.u4 = 25.0f;
    a.u44 = arg0[0x23D];
    ret = func_151559FC(&a, (u8)(arg1 ? 4 : 0), 0, 0, 0x58, 0xFF, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
    a.u14 = (a.u14 & ~6) | 4;
    a.u0 = -25.0f;
    a.u4 = 25.0f;
    ret = func_151559FC(&a, (u8)(arg1 ? 4 : 0), 0, 0, 0x58, 0xFF, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
    a.u14 &= ~6;
    a.u0 = -25.0f;
    a.u4 = -25.0f;
    ret = func_151559FC(&a, (u8)(arg1 ? 4 : 0), 0, 0, 0x58, 0xFF, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
    a.u14 = (a.u14 & ~6) | 2;
    a.u0 = 25.0f;
    a.u4 = -25.0f;
    ret = func_151559FC(&a, (u8)(arg1 ? 4 : 0), 0, 0, 0x58, 0xFF, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
    if (D_800BE616 == 0) {
        c.u0 = arg0;
        c.u4 = p = arg0[0x23D] * 0x180 + D_800BE628;
        c.uC = *(f32 *)(p + 0x34) - 12.0f;
        d.u0 = 0xE;
        d.u1 = -1;
        d.u2 = 1;
        d.u4 = 0x12C;
        d.u6 = 1;
        c.u10 = (s32)(*(f32 *)(p + 0x38) - 12.0f) * D_800BE620;
        ret = func_151604E4(&d, 0x498, 0xFF, 1);
        if (ret != 0) {
            c.u8 = (u8 *)(ret + 0x30);
            memcpy((void *)(ret + 0x18), &c, 0x14);
        }
    }
}
