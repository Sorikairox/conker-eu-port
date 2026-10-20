extern f32 D_800BE9A4;

s32 func_151CEFD0(u8 *arg0) {
    f32 a;
    f32 v;

    a = *(f32 *)(arg0 + 0x40);
    v = *(f32 *)(arg0 + 0x44);
    *(f32 *)(arg0 + 0x44) = v + a * D_800BE9A4;
    *(f32 *)(arg0 + 0x38) = *(f32 *)(arg0 + 0x38) + (v + 0.5f * a * D_800BE9A4) * D_800BE9A4;
    *(f32 *)(arg0 + 0x50) = *(f32 *)(arg0 + 0x50) + *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
    if (1.0f < *(f32 *)(arg0 + 0x50)) {
        *(f32 *)(arg0 + 0x50) = 1.0f;
    }
    return 1;
}
