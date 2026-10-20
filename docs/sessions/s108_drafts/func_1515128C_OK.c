void func_15143794(s16, s16, f32, void *);
s32 func_150ACEA0(f32, f32, s32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
s32 func_15145C90(s32);

void func_1515128C(u8 *arg0, u8 arg1, s32 arg2) {
    s32 n;
    f32 spC0[3];
    u8 spAC[0x14];
    f32 spA0[3];
    f32 sp9C;
    s32 sp98;
    u8 *hit;

    n = *(s32 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s32 *)(arg0 + 4) + 1));
    while (n != 0) {
        func_15143794(*(s16 *)(arg0 + 0x14) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1)),
            *(s16 *)(arg0 + 0x18) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1A) + 1)), 100.0f, spC0);
        hit = spAC; // fakematch: named pointer to spAC (permuter), both calls use it
        if (func_150ACEA0(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0xC), *(s32 *)(arg0 + 0x10), spC0[0], spC0[1], spC0[2], 0,
                hit, &spA0[0], &spA0[1], &spA0[2], &sp9C, &sp98, 0, 0.0f) != 0) {
            if (func_15145C90(sp98) != 0) {
                if (sp9C < *(f32 *)(arg0 + 0x1C)) {
                    func_151D9B8C(*(u8 *)(arg0 + 0x2C), *(f32 *)(arg0 + 0x20) + *(f32 *)(arg0 + 0x24) * func_150ADA68(),
                        (func_150ADA20() % 156U) + 100, (s32)hit, (struct17 *)spA0,
                        *(s16 *)(arg0 + 0x28) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x2A) + 1)),
                        1, 1, 1, arg1, arg2);
                }
            }
        }
        n--;
    }
}
