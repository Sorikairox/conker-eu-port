
void func_151664F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8) {
    f32 temp_f12;
    s32 var_a0;
    s32 var_a1;
    u8 *temp_v0;
    u8 *var_v1;

    temp_v0 = func_15167A68(4, arg8, 0xA8, 1, (u8) (s32) arg7, 1U);
    if (temp_v0 != NULL) {
        var_a0 = 0;
        if (arg0 == -1) {
            var_v1 = temp_v0;
            do {
                var_a0 += 0x40;
                var_v1 += 0x40;
                (*(s16 *)((u8 *)var_v1 + -0x2E)) = arg2;
                (*(s16 *)((u8 *)var_v1 + -0x1E)) = arg2;
                (*(s16 *)((u8 *)var_v1 + -0xE)) = arg2;
                (*(s16 *)((u8 *)var_v1 + 2)) = arg2;
                (*(s16 *)((u8 *)var_v1 + -0x2A)) = 0;
                (*(s16 *)((u8 *)var_v1 + -0x1A)) = 0;
                (*(s16 *)((u8 *)var_v1 + -0xA)) = 0;
                (*(s16 *)((u8 *)var_v1 + 6)) = 0;
            } while (var_a0 != 0x80);
            (*(s8 *)((u8 *)temp_v0 + 0x95)) = 0;
        } else {
            temp_f12 = (f32) arg0 * 0.017453292f;
            (*(s8 *)((u8 *)temp_v0 + 0x91)) = (s8) (s32) (sinf(temp_f12) * 127.0f);
            (*(s8 *)((u8 *)temp_v0 + 0x95)) = 1;
            (*(s8 *)((u8 *)temp_v0 + 0x90)) = (s8) (s32) (-cosf(temp_f12) * 127.0f);
        }
        var_a1 = 0;
        var_v1 = temp_v0;
        do {
            var_a1 += 1;
            var_v1 += 0x40;
            (*(s16 *)((u8 *)var_v1 + -0x28)) = 0x2000;
            (*(s16 *)((u8 *)var_v1 + -0x26)) = 0x2000;
            (*(s16 *)((u8 *)var_v1 + -0x18)) = 0x2800;
            (*(s16 *)((u8 *)var_v1 + -0x16)) = 0x2000;
            (*(s16 *)((u8 *)var_v1 + -8)) = 0x2800;
            (*(s16 *)((u8 *)var_v1 + -6)) = 0x2800;
            (*(s16 *)((u8 *)var_v1 + 8)) = 0x2000;
            (*(s16 *)((u8 *)var_v1 + 0xA)) = 0x2800;
        } while (var_a1 != 2);
        (*(s16 *)((u8 *)temp_v0 + 0x9A)) = arg2;
        (*(s16 *)((u8 *)temp_v0 + 0x9E)) = 1;
        (*(s8 *)((u8 *)temp_v0 + 0x92)) = (s8) arg5;
        (*(s8 *)((u8 *)temp_v0 + 0x93)) = (s8) arg5;
        (*(s16 *)((u8 *)temp_v0 + 0x98)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x9C)) = (s16) arg3;
        (*(s16 *)((u8 *)temp_v0 + 0x96)) = (s16) arg4;
        (*(s8 *)((u8 *)temp_v0 + 0x94)) = (s8) arg6;
        func_1517E5CC(arg1, arg2, arg3, temp_v0);
    }
}
