s32 func_151A2C9C(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void (**D_8008FC00[])(u8 *);
extern s32 D_8008FC88;

void func_151A31D4(s32 arg0, s32 arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 argA, f32 argB, s16 argC, s16 argD, s16 argE, s16 argF, s16 arg10, s16 arg11, s8 arg12, u8 arg13, s32 arg14, u8 arg15) {
    s16 spFE;
    void (*spF0)(f32 *, s32, s32, s32, f32, f32 *); /* compiler-managed */
    s32 spE4;
    s32 spD8;
    s32 spC8;
    s32 spB0;
    u32 spAC;
    s32 spA8;
    f32 temp_f22;
    f32 temp_f24;
    f32 var_f20;
    s16 temp_s4;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 var_s0;
    s32 var_s3;
    u8 *temp_v0;

    if (arg15 == 0) {
        spF0 = func_151A3134;
    } else {
        spF0 = func_151A3180;
    }
    if (arg10 < arg11) {
        spFE = arg10;
    } else {
        spFE = arg11;
    }
    var_s3 = arg7;
    var_f20 = 0.0f;
    temp_f24 = 1.0f / (f32) var_s3;
    if (var_s3 != 0) {
        spB0 = (s32) argC;
        spAC = argF + 1;
        spA8 = (s32) argE;
        do {
            temp_s4 = (func_150ADA20() % (u32) (argD + 1)) + spB0;
            temp_s1 = func_150ADA20();
            temp_s0 = func_150ADA20();
            func_15143794((s16) (temp_s1 & 0xFF), (s16) (temp_s0 & 0xFF), func_150ADA68() * arg8, (s32) &spE4);
            spF0(arg1, arg2, arg3, arg4, var_f20, (s32) &spD8);
            (*(s32 *)((u8 *)(&spC8) + 0)) = (s32) (*(s32 *)((u8 *)(&D_8008FC88) + 0));
            (*(s32 *)((u8 *)(&spC8) + 4)) = (s32) (*(s32 *)((u8 *)(&D_8008FC88) + 4));
            (*(s32 *)((u8 *)(&spC8) + 8)) = (s32) (*(s32 *)((u8 *)(&D_8008FC88) + 8));
            temp_s2 = func_150ADA20() & 3;
            temp_f22 = func_150ADA68();
            temp_s1_2 = func_150ADA20();
            if (func_150ADA68() < 0.0802f) {
                var_s0 = 0x19;
            } else {
                var_s0 = -1;
            }
            temp_v0 = &spC8 + (temp_s2 * 3);
            func_151A2C9C(arg0, &spE4, &spD8, arg9, (temp_f22 * argB) + argA, (arg6 * var_f20) + arg5, temp_s4 + spFE, ((u32) temp_s1_2 % spAC) + spA8, (s32) arg10, (s32) arg11, var_s0, (s32) arg12, (s32) (*(u8 *)((u8 *)temp_v0 + 0)), (s32) (*(u8 *)((u8 *)temp_v0 + 1)), (s32) (*(u8 *)((u8 *)temp_v0 + 2)), (s32) arg13, arg14);
            var_f20 += temp_f24;
            var_s3 -= 1;
        } while (var_s3 != 0);
    }
}
