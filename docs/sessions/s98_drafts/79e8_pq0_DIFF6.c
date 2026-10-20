void func_15141F78(u8, s32 *, f32, s32, f32 *, u8);
void func_15142180(u8, f32 *, s32, f32, f32);
extern u8 (*D_800900BC)(void);
void func_151479E8(u8 *arg0, u8 arg1, s32 arg2) {
    f32 sp4C[3];
    s32 sp28[9];
    u8 **q = &arg0; // fakematch: arg0 reloaded from its home slot

    if (*(s32 *)(*q + 0x1D4) != 0) {
        if (func_15146E00(sp4C, *q, (s32)sp28, arg1) != 0) {
            func_15141F78(D_800900BC(), sp28, arg2 * 0.0076923077f, (u8)(*(f32 *)(*q + 0x40) * 0.7111111f), sp4C, arg1);
            if (arg2 >= 0x73) {
                func_15142180(6, sp4C, sp28[6], 1.0f, 1.0f);
            }
        }
    }
}
