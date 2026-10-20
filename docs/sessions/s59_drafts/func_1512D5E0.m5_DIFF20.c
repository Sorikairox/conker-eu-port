extern Mtx *D_800DC6D0[];
s32 func_150498A0(u8 *, f32, u8 *, s32, f32, f32);

void func_1512D5E0(u8 *arg0) {
    Mtx sp78;
    f32 sp38[16];

    Mtx *temp_a0;
    f32 var_f2;
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x2C));
    temp_v0 = temp_v1 & 0x80000;
    if (temp_v0 != 0) {
        var_f2 = 0.003f;
    } else if ((*(s16 *)((u8 *)arg0 + 0x298)) != 0) {
        var_f2 = 0.04f;
    } else {
        var_f2 = 0.03f;
    }
    if ((temp_v0 != 0) || (temp_v0 = (*(s32 *)((u8 *)arg0 + 0x5F0)), ((temp_v0 & 1) != 0)) || ((temp_v1 != 0x40000) && (temp_v0 & 8))) {
        (*(f32 *)((u8 *)arg0 + 0x7B0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x7B0)) + (0.04363323f * (f32) D_800BE9E4));
        if ((*(f32 *)((u8 *)arg0 + 0x7B0)) > 3.1415927f) {
            (*(f32 *)((u8 *)arg0 + 0x7B0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x7B0)) - 6.2831855f);
        }
    } else {
        var_f2 = 0.0f;
    }
    if (((*(u8 *)((u8 *)arg0 + 0x23C)) != 0) || ((*(s32 *)((u8 *)arg0 + 0x5F0)) & 4)) {
        (*(f32 *)((u8 *)arg0 + 0x7DC)) = var_f2;
    } else {
        func_150498A0(arg0 + 0x7DC, var_f2, arg0 + 0x7D8, 0x3E4CCCCD, 0.4f, (*(f32 *)((u8 *)arg0 + 0x7B4)));
    }
    guMtxIdentF((f32 (*)[4]) &sp38[0]);
    sp38[0] = (2.0f * (func_150AD78C((*(f32 *)((u8 *)arg0 + 0x7B0))) * (*(f32 *)((u8 *)arg0 + 0x7DC)))) + (2.0f * (*(f32 *)((u8 *)arg0 + 0x7DC))) + 1.0f;
    sp38[5] = (func_150AD780((*(f32 *)((u8 *)arg0 + 0x7B0))) * (*(f32 *)((u8 *)arg0 + 0x7DC))) + (*(f32 *)((u8 *)arg0 + 0x7DC)) + 1.0f;
    guMtxF2L((f32 (*)[4]) &sp38[0], &sp78);
    temp_a0 = (u8 *)D_800DC6D0[D_800BE9C0] + ((*(u8 *)((u8 *)arg0 + 0x23D)) << 6);
    guMtxCatL(temp_a0, &sp78, temp_a0);
}
