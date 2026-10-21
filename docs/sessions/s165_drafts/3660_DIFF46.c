typedef struct {
    s32 u00;
    s32 u04;
    f32 pos[3];
    s16 u14;
    s16 u16;
    s16 u18;
    s16 u1A;
    f32 u1C;
    f32 u20;
    f32 u24;
    f32 u28;
    f32 u2C;
    s16 u30;
    s16 u32;
    s32 u34;
    s32 u38;
    s32 u3C;
    f32 u40;
    f32 u44;
    f32 u48;
    f32 u4C;
    f32 u50;
    f32 u54;
    f32 u58;
    f32 u5C;
    f32 u60;
    f32 u64;
    u8 u68[8];
    s8 u70;
    s8 u71;
    s16 u72;
    s16 u74;
} S3660;
s32 func_15142314(s32, s32, f32 *);
s32 func_15152A90(S3660 *, u8, s32);
void func_15193660(u8 *arg0, u8 arg1, s32 arg2) {
    S3660 s;
    s32 v;

    if (arg0 != NULL && *(s32 *)arg0 != 0) {
        v = *(s32 *)(arg0 + 0x1D4);
        if (v != 0) {
            func_15142314(v, 0xA, s.pos);
            s.u00 = 8;
            s.u04 = 7;
            s.u18 = -0x21;
            s.u1A = 0x18;
            s.u30 = 0x28;
            s.u32 = 0x23;
            s.u34 = 0xA0;
            s.u38 = 0x13;
            s.u70 = 0x21;
            s.u68[0] = 0xFF;
            s.u14 = 0;
            s.u16 = 0xFF;
            s.u3C = 0;
            s.u68[1] = 0xFF;
            s.u68[2] = 0xFF;
            s.u68[3] = 0xFF;
            s.u68[4] = 0xFF;
            s.u68[5] = 0xFF;
            s.u68[6] = 0xFF;
            s.u68[7] = 0xFF;
            s.u71 = 0xF;
            s.u72 = 0x19;
            s.u74 = 0xA;
            s.u58 = -12.86f;
            s.u50 = -12.86f;
            s.u64 = 25.38f;
            s.u5C = 25.38f;
            s.u1C = 12.403001f;
            s.u20 = 5.039f;
            s.u24 = 0.908871f;
            s.u28 = -0.707f;
            s.u2C = 0.261f;
            s.u44 = 1.96f;
            s.u40 = 0.0f;
            s.u4C = 0.0f;
            s.u54 = 0.0f;
            s.u60 = 0.0f;
            s.u48 = 0.307f;
            func_15152A90(&s, arg1, arg2);
        }
    }
}
