typedef struct {
    void *u0;
    s32 u4;
    s32 u8;
    s32 uC;
    s32 u10;
    s16 u14;
    s16 u16;
    s16 u18;
    s16 pad1A;
    f32 u1C;
    f32 u20;
    s16 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s16 u2E;
    u8 u30;
    u8 u31;
    u8 u32;
    u8 u33;
    u8 u34;
    u8 u35;
    u8 u36;
    u8 u37;
    u8 u38;
    u8 u39;
    u8 pad3A[2];
} S59A0;
extern u8 D_80091CF8[];
extern u8 D_80091CE0[];
extern u8 D_80091CEC[];
extern u8 D_80091BA8[];
s32 func_15169ED8(S59A0 *);
void func_150F59A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    S59A0 s;
    s32 sum;

    if (arg3 != 0) {
        if (arg3 == 2) {
            s.u2C = 0xF0;
            s.u2E = 0xBA;
            s.u0 = D_80091CF8;
        } else {
            s.u2C = 0x10E;
            s.u2E = 0x7C;
            if (arg3 == 1) {
                s.u0 = D_80091CE0;
            } else {
                s.u0 = D_80091CEC;
            }
        }
        s.u30 = 9;
        s.u39 = 0x10;
        s.u28 = 0;
        s.u2A = 0;
        s.u36 = 8;
    } else {
        s.u0 = D_80091BA8;
        s.u30 = 0xA;
        s.u2C = 0xA0;
        s.u2E = 0xC0;
        s.u39 = 0x20;
        s.u28 = 0x1000;
        s.u2A = 0x1000;
        s.u36 = 0x18;
    }
    s.u8 = (arg0 << 16) | arg1;
    sum = arg0 + arg1 + arg2;
    s.uC = (arg2 << 16) | sum;
    s.u10 = 10000;
    s.u14 = sum;
    s.u18 = 0;
    s.u24 = 0;
    s.u26 = 0;
    s.u31 = 1;
    s.u32 = 0xFF;
    s.u33 = 0xFF;
    s.u34 = 0xFF;
    s.u37 = 0x11;
    s.u35 = 0;
    s.u16 = 0;
    s.u1C = 146.0f;
    s.u20 = 100.0f;
    func_15169ED8(&s);
}
