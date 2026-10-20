void func_150F4AF0(s32 *, s32 *, u8, f32, f32, f32, s32, s32, s32, s32);
void func_1514470C(s32, s32 *);
typedef struct { u8 n; u8 (*tab)[2]; f32 *scale; } FB06C_T;
extern FB06C_T D_80088ECC;
extern f32 D_800A2188;
extern f32 D_800A218C;

void func_150FB06C(u8 *arg0) {
    s32 a[3];
    s32 b[3];
    f32 *p;
    u8 i;
    f32 s;
    f32 r;

    p = (f32 *)(arg0 + 0x28);
    p[2] += (D_800A2188 + func_150ADA68() * D_800A218C) * D_800BE9A4;
    if (p[2] > 1.0f) do {
        func_1514470C(((s32 *)p)[0], a);
        func_1514470C(((s32 *)p)[1], b);
        i = func_150ADA20() % (u32)D_80088ECC.n;
        s = func_150ADA68() * 25.0f + 30.0f;
        r = func_150ADA68();
        func_150F4AF0(a, b, D_80088ECC.tab[i][1], s, 1.0f / s, (r * 1.0f + 1.0f) * D_80088ECC.scale[i], 1, func_150ADA20() % 3U + 0x2EE, arg0[0xC], arg0[1]);
        p[2] -= 1.0f;
    } while (p[2] > 1.0f);
}
