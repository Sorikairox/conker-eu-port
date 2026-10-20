s32 func_151597A0(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 r;
    if (*(f32 *)(arg1 + 0) != *(f32 *)(arg0 + 0x14) || *(f32 *)(arg1 + 4) != *(f32 *)(arg0 + 0x18) || *(f32 *)(arg1 + 8) != *(f32 *)(arg0 + 0x1C)) { if (arg2 == 1 || arg2 == 2) { r = 2; } else { r = 1; } } else { r = 0; }
    return r;
}
