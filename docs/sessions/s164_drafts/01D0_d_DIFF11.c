s32 func_1507CD64(struct127 *, s32);
s32 func_150ADE40(s16, s16, s32, s32);
s32 func_15136C3C(struct127 *, s32, s32, s32, s32, s32, s32, s32);
void func_151601D0(struct127 *arg0, u8 *arg1) {
    s32 pad[2]; // fakematch: frame
    f32 scale;

    if (arg0->unk31C != NULL && arg0->unk31C->unk120 == 0) {
        if (*(u32 *)(arg1 + 0x1C) != 0) {
            scale = *(u32 *)(arg1 + 0x1C) * 0.01f;
            if (func_150ADE40(*(s16 *)(arg1 + 0), *(s16 *)(arg1 + 4), arg0->x_position, arg0->z_position) < *(s16 *)(arg1 + 6) * scale - arg0->unkE4) {
                return;
            }
        }
        func_1505D024(arg0, 0x2F, 0, -1);
        func_15136C3C(arg0, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50(arg0);
        func_1507CD64(arg0, 6);
    }
}
