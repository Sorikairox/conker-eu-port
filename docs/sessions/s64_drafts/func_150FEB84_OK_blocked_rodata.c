extern f32 D_800A23C0;
s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);

void func_150FEB84(struct127 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    f32 sp60[2];
    u8 sp5F;

    if ((arg0->unk1D4 != NULL) && ((arg0->unk74 & 0xF) != 0xF)) {
        sp60[1] = (func_150ADA68() * 2) + D_800A23C0;
        sp60[0] = (func_150ADA68() * 15.0f) + 35.0f;
        if ((arg0->unk31C != NULL) && (arg0->unk31C->unk197 != 0) && (arg0->camera != NULL)) {
            sp5F = (~(1 << arg0->camera->unk23D)) & 0xFFFFu;
        } else {
            sp5F = 0xFF;
        }
        func_151030B8(arg0, D_80088F34, "", "", sp60, (func_150ADA20() % 3U) + 4, (func_150ADA20() % 56U) + 0xC8, (func_150ADA68() * 301.0f) + 500.0f, arg1, (s32) sp5F, 0, -1, (s32) arg2, arg3);
    }
}
