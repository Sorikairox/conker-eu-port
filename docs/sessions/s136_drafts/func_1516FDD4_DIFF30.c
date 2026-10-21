void func_1516FDD4(u8 *arg0) {
    s32 x;
    s32 v;

    x = (*(s16 *)(arg0 + 0xE) << 8) + arg0[0x2A];
    v = (*(s8 *)(arg0 + 0x26) << 8) + arg0[0x27];
    x += v * D_800BE9E4;
    *(s16 *)(arg0 + 0xE) = x >> 8;
    arg0[0x2A] = x;
    x = (*(s16 *)(arg0 + 0x12) << 8) + arg0[0x2B];
    v = (*(s8 *)(arg0 + 0x28) << 8) + arg0[0x29];
    x += v * D_800BE9E4;
    *(s16 *)(arg0 + 0x12) = x >> 8;
    arg0[0x2B] = x;
}
