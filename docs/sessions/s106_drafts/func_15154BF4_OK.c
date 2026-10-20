void func_15143794(s16, s16, f32, void *);
void func_151C64F4(s32, void *, f32, s32, s32, s32, f32, s32, s32, u8, s32);
void func_15154BF4(u8 *arg0, u8 arg1, s32 arg2) {
    s32 sp80[4];
    s32 n;
    n = *(s16 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 2) + 1));
    if (n > 0) {
        do {
            func_15143794(func_150ADA20() & 0xFF, *(s16 *)(arg0 + 0xA) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0xE) + 1)),
                *(f32 *)(arg0 + 0x10) + *(f32 *)(arg0 + 0x14) * func_150ADA68(), sp80);
            func_151C64F4(*(s32 *)(arg0 + 4), sp80, *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * func_150ADA68(),
                *(s32 *)(arg0 + 0x20),
                *(u8 *)(arg0 + 0x24) + (func_150ADA20() % (u32)(*(u8 *)(arg0 + 0x25) + 1)),
                *(s16 *)(arg0 + 0x26) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x28) + 1)),
                *(f32 *)(arg0 + 0x2C) + *(f32 *)(arg0 + 0x30) * func_150ADA68(),
                func_150ADA68() < *(f32 *)(arg0 + 0x34), *(s32 *)(arg0 + 0x38), arg1, arg2);
            n--;
        } while (n > 0);
    }
}
