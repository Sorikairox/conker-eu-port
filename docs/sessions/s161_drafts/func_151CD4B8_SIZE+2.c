extern f32 D_800AB16C[];
extern f32 D_800AB194[];
typedef struct { u8 v[4]; } Tbl4_D4B8;
extern Tbl4_D4B8 D_8008FFC8;

void func_151CD4B8(u8 *arg0, u8 arg1, s8 arg2, u8 arg3) {
    Spawn559A a;
    s32 pad;
    Spawn559B b;
    u8 i;
    u8 j;

    b.u1C = 0.0f;
    b.u18 = D_800AB16C[D_80082FA0 == 1];
    b.u20 = D_800AB194[D_80082FA0 == 1];
    b.u0 = arg0;
    b.u4 = 0.0f;
    b.u8 = 130.0f;
    b.uC = (arg2 == -1) ? 0 : 4;
    b.u54 = arg2;
    a.u12 = 0x12C;
    a.u14 = (arg1 ? 0x40 : 0) | 0x30;
    a.u16 = 1;
    a.u18 = 0xFF;
    a.u1A = 7;
    a.u1B = 0xFF;
    a.u1C = 0xFF;
    a.u1D = 0xFF;
    a.u1E = 0xFF;
    a.u1F = 0xFF;
    a.u20 = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u30 = 8;
    a.u34 = 0x13;
    a.u38 = 0x80;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 0;
    a.u44 = arg0[0x23D];
    a.u50 = 0.0f;
    a.u54 = 0.0f;
    a.u48 = 1.0f;
    a.u4C = 1.0f;
    a.u8 = 35.75f;
    a.uC = 16.0f;
    for (i = 0; i < 2; i++) {
        Tbl4_D4B8 tbl;
        s32 ret;
        tbl = D_8008FFC8;
        a.u4 = i ? 92.0f : -90.0f;
        a.u14 |= i ? 4 : 0;
        b.uD = i ? 5 : 4;
        for (j = 0; j < 4; j++) {
            a.u0 = ((f32)j * 71.5f + 35.75f) - 143.0f;
            a.u10 = tbl.v[j];
            ret = func_151559FC(&a, 0xB, 0, 0, 0x58, arg3, 1);
            if (ret != 0) {
                memcpy((void *)(ret + 0x70), &b, 0x58);
            }
        }
    }
}
