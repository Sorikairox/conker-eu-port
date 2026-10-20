extern f32 D_8009FC40;
void func_150B0F40(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5) {
    f32 r;
    f32 s;
    f32 k;

    *arg5 = *(f32 *)(arg0 + 0x40) * D_8009FC40 - 128.0f;
    r = func_150ADA68() * 248.0f;
    s = func_150ADA68() + -0.5f;
    if (r < 122.0f) {
        arg4[1] = 0.0f;
        arg4[0] = arg3[0] * s * 122.0f + arg2[0] * -31.5f;
        arg4[2] = arg3[1] * s * 122.0f + arg2[1] * -31.5f;
    } else {
        k = 61.0f;
        if (r - 122.0f < 63.0f) {
            k = -61.0f;
            *arg5 += 0x40;
        } else {
            *arg5 -= 0x40;
        }
        arg4[1] = 0.0f;
        arg4[0] = arg3[0] * k + arg2[0] * 63.0f * s;
        arg4[2] = arg3[1] * k + arg2[1] * 63.0f * s;
    }
    arg4[0] += *(f32 *)(arg0 + 0x14);
    arg4[1] += *(f32 *)(arg1 + 0x118);
    arg4[2] += *(f32 *)(arg0 + 0x1C);
}
