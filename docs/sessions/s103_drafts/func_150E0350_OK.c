typedef struct { u32 w0; u32 w1; } G8;

s32 func_150E0350(u8 *arg0, u8 *arg1) {
    f32 s;
    G8 *g;
    s32 i;
    s32 t;
    u32 w;

    if (*(s32 *)(arg1 + 0x2EC) != 0) {
        arg0[0x13] = 2;
        *(f32 *)(arg1 + 0x2D8) -= D_800BE9A4;
        if (*(f32 *)(arg1 + 0x2D8) < 0.0f) {
            *(s32 *)(arg1 + 0x2EC) = 0;
            return 1;
        }
        s = 1.0f - *(f32 *)(arg1 + 0x2D8) * *(f32 *)(arg1 + 0x2DC);
    } else {
        s = 0.0f;
        arg0[0x13] = 0;
    }
    g = **(G8 ***)(arg0 + 0x24);
    if (g != NULL) {
        i = 0;
        while (*(s8 *)&g[i] != -0xE) {
            i++;
        }
        w = g[i].w0;
        t = 2 - (s32)((w >> 12) & 0xFFF) / 3;
        while (t < 0) {
            t += 0x40;
        }
        g[i].w0 = (((s32)(500.0f * s + 2.0f) & 0xFFF) << 12) | 0xF2000000 | (t & 0xFFF);
    }
    return 0;
}
