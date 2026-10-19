
void func_15166F10(s32 arg0, s32 arg1, s32 arg2, f32 arg3, u8 arg4, s32 arg5) {
    u8 *temp_v0;
    s32 var_s0;
    s32 var_s2;
    Mtx *var_s1;

    temp_v0 = func_15167A68(0xD, arg5, 0xE0, 1, (u8) (s32) arg4, 1U);
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 0xD0)) = 0xA;
        (*(s16 *)((u8 *)temp_v0 + 0xD2)) = (s16) arg0;
        (*(s16 *)((u8 *)temp_v0 + 0xD4)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0xD6)) = (s16) arg2;
        (*(f32 *)((u8 *)temp_v0 + 0xD8)) = arg3;
        var_s0 = func_150ADA20() & 0x7F;
        var_s2 = 0;
        var_s1 = temp_v0 + 0x10;
        do {
            if (arg3 != 1.0f) {
                func_15043D90(var_s1, 0.0f, (f32) var_s0, 0.0f, arg3, arg3, arg3, (f32) arg0, (f32) arg1, (f32) arg2);
            } else {
                func_15043E68(var_s1, 0.0f, (f32) var_s0, 0.0f, (f32) arg0, (f32) arg1, (f32) arg2);
            }
            var_s0 = var_s0 + (func_150ADA20() & 0x3F) + 0x5A;
            var_s2 += 0x40;
            var_s1 += 0x40;
        } while (var_s2 != 0xC0);
        func_1517E5CC(arg0, arg1, arg2);
    }
}
