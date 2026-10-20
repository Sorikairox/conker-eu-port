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
struct260 *func_151A8B20(void *arg0, s16 arg1, s32 arg2, u8 arg3, s32 arg4);

void func_151A9670(s32 arg0, s32 arg1) {
    S9670 s;
    f32 f;
    u8 b[1];

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
        u8 *r = (u8 *)func_151A8B20(&s, -1, 1, 0xFF, 0);
        if (r != NULL) {
            memcpy(r + 0x80, b, 1);
        }
    }
}
