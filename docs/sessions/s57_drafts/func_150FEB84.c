extern f32 D_800A23C0;
s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);

void func_150FEB84(struct127 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    f32 sp60[2];
    f32 two = 2.0f;
    u8 sp5F;
    s32 sp54;
    s32 sp50;
    struct108 *temp_v0_2;
    struct126 *temp_v0;

    if ((arg0->unk1D4 != NULL) && ((arg0->unk74 & 0xF) != 0xF)) {
        sp60[1] = (func_150ADA68() * two) + D_800A23C0;
        sp60[0] = (func_150ADA68() * 15.0f) + 35.0f;
        temp_v0 = arg0->unk31C;
        if ((temp_v0 != NULL) && (temp_v0->unk197 != 0) && (temp_v0_2 = arg0->camera, (temp_v0_2 != NULL))) {
            sp5F = ~(1 << temp_v0_2->unk23D);
        } else {
            sp5F = 0xFF;
        }
        sp50 = func_150ADA20();
        sp54 = func_150ADA20();
        func_151030B8(arg0, D_80088F34, "", "", sp60, ((u32) sp50 % 3U) + 4, ((u32) sp54 % 56U) + 0xC8, (func_150ADA68() * 301.0f) + 500.0f, arg1, (s32) sp5F, 0, -1, (s32) arg2, arg3);
    }
}
