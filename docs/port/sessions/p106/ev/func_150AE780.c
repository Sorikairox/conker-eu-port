s32 func_150AE780(u8 *obj) {
    f32 *phase = (f32 *) (obj + 0x178);

    phase[0] += 0.065f * D_800BE9A4;
    phase[1] += 0.0484f * D_800BE9A4;
    phase[0] = func_15144B68(phase[0]);
    phase[1] = func_15144B68(phase[1]);
    *(f32 *) (obj + 0x20) = sinf(phase[0]) * 3.0860002f;
    *(f32 *) (obj + 0x28) = sinf(phase[1]) * 5.9140005f;
    return 1;
}
