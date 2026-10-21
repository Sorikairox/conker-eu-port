extern f32 D_8009FC40;
void func_150B0F40(u8 *arg0, u8 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5) {
    f32 r;
    f32 k;
    f32 s;
    f32 m;

    *arg5 = *(f32 *)(arg0 + 0x40) * D_8009FC40 - 128.0f;
    r = func_150ADA68() * 248.0f;
    s = func_150ADA68() + -0.5f;
    if (r < 122.0f) {
        arg4[0] = arg2[0] * -31.5f + arg3[0] * s * 122.0f;
        arg4[1] = 0.0f;
        arg4[2] = arg2[1] * -31.5f + arg3[1] * s * 122.0f;
    } else {
        s32 step; // fakematch: permuter temp, schedules `r -= 122.0f` after the 63/61 loads

        m = 61.0f;
        r -= 122.0f;
        step = 0x40;
        k = m;
        if (r < 63.0f) {
            k = -m;
            *arg5 += step;
        } else {
            *arg5 -= 0x40;
        }
        arg4[0] = arg2[0] * 63.0f * s + arg3[0] * k;
        arg4[1] = 0.0f;
        arg4[2] = arg2[1] * 63.0f * s + arg3[1] * k;
    }
    arg4[0] += *(f32 *)(arg0 + 0x14);
    arg4[1] += *(f32 *)(arg1 + 0x118);
    arg4[2] += *(f32 *)(arg0 + 0x1C);
}
