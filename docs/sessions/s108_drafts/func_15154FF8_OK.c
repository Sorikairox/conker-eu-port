s32 func_15154FF8(u8 *arg0) {
    f32 *p;
    f32 s;

    p = (f32 *)(arg0 + 0x170);
    s = sinf(p[3]);
    *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x1C) = p[1] * s;
    *(s8 *)(arg0 + 0x70) = (s8)(u32)(((u32)p[2] & 0xFF) * s);
    p[0] -= D_800BE9A4;
    if (p[0] <= 0.0f) {
        return 0;
    }
    p[3] += p[4] * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}
