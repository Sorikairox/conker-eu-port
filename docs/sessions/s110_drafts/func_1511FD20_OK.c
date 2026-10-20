void func_1511FD20(u8 *arg0) {
    s32 pad[2]; // fakematch: frame size (unused locals)
    s32 lim;
    s32 pad2; // fakematch: frame slot
    s16 old;
    u32 st;

    old = *(f32 *)(arg0 + 0x18) + *(s16 *)(arg0 + 0x12);
    lim = *(s32 *)(arg0 + 0x3C);
    lim = lim * 50 / 60;
    if (D_800BE9B4 != 0) {
        *(s32 *)(arg0 + 0x7C) = func_150ADA20() & 0xFFFF;
    }
    *(f32 *)(arg0 + 0x18) = cosf(*(s32 *)(arg0 + 0x7C) * 0.005493164f) * 25.0f;
    st = *(s32 *)(arg0 + 0x80);
    *(s32 *)(arg0 + 0x7C) += D_800BE9E4 * 10;
    if (st == 1) {
        *(s32 *)(arg0 + 0x84) += D_800BE9E4;
        if (lim < *(s32 *)(arg0 + 0x84)) {
            *(s32 *)(arg0 + 0x80) = 2;
        }
    } else if (st == 2) {
        *(s16 *)(arg0 + 0x12) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x12) < -10000) {
            *(s8 *)(arg0 + 0x6E) = 1;
        }
    }
    *(s16 *)(arg0 + 0x5C) = (*(f32 *)(arg0 + 0x18) + *(s16 *)(arg0 + 0x12)) - old;
}
