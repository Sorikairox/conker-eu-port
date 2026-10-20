s32 func_15133D30(u8 *);

typedef struct { s32 u0; s16 u4; u8 u6; u8 u7; s32 u8; s32 uC; u8 u10, u11, u12, u13, u14, u15, u16, u17; s32 u18; s32 u1C; s16 u20; s16 u22; s16 u24; s16 u26; } E9_S;
s32 func_150E9C9C(u8 *arg0) {
    u8 *p;
    E9_S s;
    f32 f;

    func_15133D30(arg0);
    p = arg0 + 0x170;
    if (*(f32 *)(arg0 + 0x3C) < *(f32 *)(arg0 + 0x170)) {
        if ((*(s32 *)(p + 4) & 0x1F) == 0xA) {
            f = func_150ADA68() * 20.0f + 20.0f;
            s.u6 = 0xB;
            s.u0 = 0x9701;
            s.u4 = 0x64;
            s.u7 = 0;
            s.u8 = 0;
            s.uC = 0;
            s.u10 = 0xFF;
            s.u11 = 0xFF;
            s.u12 = 0xFF;
            s.u13 = 0xFF;
            s.u14 = 0xFF;
            s.u15 = 0xFF;
            s.u18 = 0x3B0003;
            s.u16 = 0;
            s.u17 = 7;
            s.u22 = 0x14;
            s.u24 = 0xC;
            func_1513C73C((s32)&s, 0, 0, (s32)(p + 8), *(f32 *)(arg0 + 0x38), *(f32 *)p + 5.0f, *(f32 *)(arg0 + 0x40), f, f, func_150ADA20() & 0xFF, 0, 0, arg0[0xC], arg0[1]);
        }
        return 0;
    }
    return 1;
}
