void func_151AF064(s32, u8, u8);
s32 func_151AEF34(f32 *, s32, s32, s32, s32, s32);


void func_151AEE40(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 var_a1;
    f32 temp_f0;
    s32 var_v0;

    sp2C = arg0;
    sp30 = arg1;
    sp34 = arg2;
    temp_f0 = func_150ADA68();
    if (!(temp_f0 < 0.15f)) {
        if (temp_f0 < 0.25f) {
            var_a1 = 0;
            if (func_150ADA68() > 0.0f) {
                var_a1 = 1;
            }
            ((void (*)(f32 *, s32, s32))func_151AF064)(&sp2C, var_a1, (*(u8 *)((u8 *)arg6 + 0xC)));
            return;
        }
        var_v0 = 0;
        if (func_150ADA68() > 0.80500007f) {
            var_v0 = 1;
        }
        func_151AEF34(&sp2C, arg3, arg4, arg5, var_v0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)));
    }
}
