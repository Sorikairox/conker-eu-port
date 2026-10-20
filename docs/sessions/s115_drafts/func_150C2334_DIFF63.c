typedef struct {
    f32 x, y, z;
    u8 pad0C[0x16 - 0x0C];
    s16 u16, u18, u1A, u1C, u1E, u20, u22, u24, u26;
    u8 u28, u29, u2A, u2B, u2C, u2D, u2E, u2F, u30, u31;
} S2334;
extern f64 D_800A05F8;
void func_151429E0(u8, u8 *, u8 *, u8 *);
void func_1518CFF0(S2334 *, s32);
s32 func_150C2334(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, f32 argC) {
    S2334 s;

    s.x = arg2;
    s.y = arg3;
    s.z = arg4;
    s.u22 = 150;
    s.u26 = 600;
    s.u1E = (arg2 - arg5) * 10.0f;
    s.u24 = 20;
    s.u20 = (arg4 - arg7) * 10.0f;
    s.u16 = s.u18 = argC;
    s.u1C = s.u1A = argC * D_800A05F8;
    func_151429E0(0, &s.u28, &s.u29, &s.u2A);
    func_151429E0(0, &s.u2B, &s.u2C, &s.u2D);
    s.u2E = 0xFF;
    s.u2F = 0xFF;
    s.u30 = (func_150ADA20() & 0xF) + 12;
    s.u31 = 1;
    func_1518CFF0(&s, 1);
    return 1;
}
