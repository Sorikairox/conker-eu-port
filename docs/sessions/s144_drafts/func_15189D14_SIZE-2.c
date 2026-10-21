s32 func_15113D54(s32, u8 *, s32, s16, s32, s32);

s32 func_15189D14(s32 arg0, u8 *arg1, s16 arg2) {
    s32 saved;
    s32 i;
    u8 n;
    u8 k;

    n = arg1[2];
    if (n == 0) {
        return arg0;
    }
    k = arg1[3];
    saved = (*(u8 **)(arg1 + 0x10))[0x8A];
    for (i = 0; i < n; i++) {
        (*(u8 **)(arg1 + 0x10))[0x8A] = ((i + 3) * k * 32) >> 8;
        arg0 = func_15113D54(arg0, *(u8 **)(arg1 + 0x10), *(s32 *)(arg1 + 8) + ((D_800BE9C0 * arg1[1] + i) << 6), arg2, 0, 0);
    }
    (*(u8 **)(arg1 + 0x10))[0x8A] = saved;
    return arg0;
}
