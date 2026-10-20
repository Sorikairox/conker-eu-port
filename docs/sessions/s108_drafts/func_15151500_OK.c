void func_15143794(s16, s16, f32, void *);
s32 func_1518A930(u8 *, f32 *, f32, f32 *, f32 *, f32, f32, u8, s32, u8, s32, u8, s32);

void func_15151500(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    f32 spBC[3];
    f32 d;
    s32 n;
    f32 spA8[3];
    f32 sp9C[3];

    d = 2.0f * *(f32 *)(arg0 + 0x2C);
    spBC[1] = 0.0f;
    n = func_150ADA20();
    n = *(s32 *)(arg0 + 0) + (n % (u32)(*(s32 *)(arg0 + 4) + 1));
    while (n != 0) {
        spA8[0] = func_150ADA68() * 360.0f;
        spA8[1] = func_150ADA68() * 360.0f;
        spA8[2] = func_150ADA68() * 360.0f;
        func_15143794(*(s16 *)(arg0 + 0x1C) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1E) + 1)),
            *(s16 *)(arg0 + 0x20) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x22) + 1)),
            *(f32 *)(arg0 + 0x24) + *(f32 *)(arg0 + 0x28) * func_150ADA68(), sp9C);
        spBC[0] = func_150ADA68() * d - *(f32 *)(arg0 + 0x2C);
        spBC[2] = func_150ADA68() * d - *(f32 *)(arg0 + 0x2C);
        func_1518A930(arg0 + 8, spA8, *(f32 *)(arg0 + 0x14) + *(f32 *)(arg0 + 0x18) * func_150ADA68(), sp9C, spBC,
            *(f32 *)(arg0 + 0x30) + *(f32 *)(arg0 + 0x34) * func_150ADA68(), *(f32 *)(arg0 + 0x38),
            *(u8 *)(arg0 + 0x3C), *(s16 *)(arg0 + 0x3E) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x40) + 1)),
            arg1, 0, arg2, arg3);
        n--;
    }
}
