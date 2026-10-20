s32 func_151030B8(u8 *, u8, f32 *, f32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
s32 func_15145EA4(f32 **, f32 **, s32, s32);
s32 func_151C284C(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
extern f32 D_800A1A10[2][3];
extern f32 D_800A1A28[2][3];
extern u8 D_800A1A40[2];

s32 func_150F03F8(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    s32 ret;
    f32 a[3];
    f32 b[3];
    f32 *src[2];
    f32 *dst[2];
    Header header;
    Header2 header2;
    f32 f[2];

    if (arg0 == NULL) {
        return 0;
    }
    if (arg1 >= 2) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x1D4) == 0) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x2EC) < 0x5A) {
        return 0;
    }
    src[0] = D_800A1A10[arg1];
    src[1] = D_800A1A28[arg1];
    dst[0] = a;
    dst[1] = b;
    func_15145EA4(src, dst, (D_800A1A40[arg1] << 6) + *(s32 *)(arg0 + 0x1D4), 2);
    b[0] -= a[0];
    b[1] -= a[1];
    b[2] -= a[2];
    ret = func_151C284C(a, b, 0, 0, 0, 0, 150.0f, 0.006666667f, (func_150ADA68() * 19.0f) + 38.0f, (func_150ADA68() * 363.0f) + 149.0f, 50.0f, (func_150ADA20() % 1U) + 0xFF, arg0, 1, 1, 0, 8, 0, 1, 0, 0xA0038, 0.0f, 0xFF, -1, 0, arg2, arg3);
    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 5U) + 4;
    header.unk4 = 0;
    header2.unk0 = a[0];
    header2.unk4 = a[1];
    header2.unk8 = a[2];
    func_151602C0(&header, &header2, (func_150ADA20() % 51U) + 0x50, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg2, arg3);
    f[1] = ((func_150ADA68() * 1906.0f) + 969.0f) * 0.001f;
    f[0] = ((func_150ADA68() * 911.0f) + 628.0f) * 0.1f;
    func_151030B8(arg0, D_800A1A40[arg1], D_800A1A10[arg1], D_800A1A28[arg1], f, (func_150ADA20() % 3U) + 8, (func_150ADA20() % 1U) + 0xFF, (func_150ADA68() * 2000.0f) + 2000.0f, a, 0xFF, 0, -1, arg2, arg3);
    return ret;
}
