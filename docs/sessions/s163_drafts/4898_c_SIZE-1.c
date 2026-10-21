void func_151D4898(f32 *arg0, f32 *arg1, u8 *arg2, s32 arg3, s32 arg4) {
    u16 ang;
    s32 t;

    if (arg1 != NULL) {
        t = (u32)(func_150484A0(arg1[0], arg1[2]) * 10430.378f);
        t -= 0x4000;
        ang = t | 1;
    } else {
        ang = 0;
    }
    func_1505D1C4(arg0[0], arg0[1], arg0[2], arg4, (arg2 - (u8 *)D_800CC2D0) / 0x32C, ang, 0, 0);
}
