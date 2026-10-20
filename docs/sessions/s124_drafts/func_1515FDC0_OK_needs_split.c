void func_1515FDC0(s32 arg0, s32 arg1) {
    f32 s;
    f32 r;
    f32 g;
    f32 b;
    u8 c[3];
    c[0] = ((u8 *)&D_800DCD20)[0];
    c[1] = ((u8 *)&D_800DCD20)[1];
    c[2] = ((u8 *)&D_800DCD20)[2];
    s = sinf(D_800DCDA0);
    r = (s * 29.5f) + 127.5f;
    g = (s * 71.0f) + 109.0f;
    b = (s * 26.0f) + 26.0f;
    D_800DCDA0 += 0.071f * D_800BE9A4;
    D_800DCDA0 = func_15144B68(D_800DCDA0);
    if (r != D_800DCD94) {
        D_800DCD94 += (r - D_800DCD94) * 0.5f;
        c[0] = D_800DCD94;
    }
    if (g != D_800DCD98) {
        D_800DCD98 += (g - D_800DCD98) * 0.5f;
        c[1] = D_800DCD98;
    }
    if (b != D_800DCD9C) {
        D_800DCD9C += (b - D_800DCD9C) * 0.5f;
        c[2] = D_800DCD9C;
    }
    func_1515D4D4(c[0], c[1], c[2], 0U);
}
