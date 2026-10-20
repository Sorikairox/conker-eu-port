typedef struct {
    u8 u0;
    s32 u4;
    f32 f8;
    f32 fC;
    f32 f10[5];
    s8 u24;
    s8 u25;
    s8 u26;
} S9670;
u8 *func_151A8B20(S9670 *, s32, s32, s32, s32);

void func_151A9670(s32 arg0, s32 arg1) {
    S9670 s;
    u8 b[1];
    f32 f;

    s.u0 = 2;
    s.u4 = arg0;
    f = arg1 & 1;
    s.f8 = f ? 1.4e-6f : 4e-7f;
    s.fC = f ? 8e-7f : 6e-7f;
    s.f10[0] = 0.0f;
    s.f10[1] = 0.0f;
    s.f10[2] = 0.0f;
    s.f10[3] = 0.0f;
    s.f10[4] = 0.0f;
    s.u24 = 1;
    s.u25 = -1;
    s.u26 = 0;
    b[0] = arg1;
    {
        u8 *r = func_151A8B20(&s, -1, 1, 0xFF, 0);
        if (r != NULL) {
            memcpy(r + 0x80, b, 1);
        }
    }
}
