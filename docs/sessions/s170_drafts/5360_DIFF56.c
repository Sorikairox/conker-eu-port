s32 func_150AD9A0(s32, s32, s32);
void func_151846C0(s32, f32 *, f32 *, f32 *);
extern f32 D_800A7758;
s32 func_15185360(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    u8 *o = (u8 *)&D_800CC2D0[arg0];
    u8 *p = (u8 *)&D_800DBFF0[arg1];
    f32 k;
    s32 d;

    d = func_150AD9A0(*(f32 *)(o + 0x14) - *(f32 *)(p + 0x2F8), *(f32 *)(o + 0x18) - *(f32 *)(p + 0x2FC), *(f32 *)(o + 0x1C) - *(f32 *)(p + 0x300));
    if (d > 2000) {
        D_800D3AAC = D_800D3AA8 = 0.0f;
        return 0;
    }
    func_151846C0(arg0, arg2, arg3, arg4);
    k = D_800A7758;
    *arg2 *= k;
    *arg3 *= k;
    *arg4 *= k;
    if (*arg2 == 0.0f || *arg3 == 0.0f || *arg4 == 0.0f) {
        D_800D3AAC = D_800D3AA8 = 0.0f;
        return 0;
    }
    return d;
}
