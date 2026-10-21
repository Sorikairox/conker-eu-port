s32 func_15045AF0(f32 *, s32, f32, u8 *);

s32 func_1519FA60(u8 *arg0) {
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    s16 temp_v0;
    s32 temp_fp;
    s32 var_s3;
    s32 var_s2;
    u8 *temp_s1;
    u8 *temp_s6;
    u8 *temp_v0_2;

    temp_s6 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_fp = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)temp_s6 + 4)) & 1)) {
        return 0;
    }
    var_s2 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_s2 -= 1;
            var_s3 = 0;
            if (var_s2 < 0) {
                var_s2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_s1 = (var_s2 * 0x24) + temp_fp;
            (*(s16 *)((u8 *)temp_s1 + 0x18)) = (s16) ((*(s16 *)((u8 *)temp_s1 + 0x18)) - D_800BE9E4);
            if ((*(s16 *)((u8 *)temp_s1 + 0x18)) < 0) {
                var_s3 = 1;
            }
            temp_v0 = (*(s16 *)((u8 *)temp_s1 + 0x12));
            (*(s16 *)((u8 *)temp_s1 + 0x14)) = 0xFF;
            if (temp_v0 > 0) {
                (*(s16 *)((u8 *)temp_s1 + 0x12)) = (s16) (temp_v0 - D_800BE9E4);
            } else {
                (*(s16 *)((u8 *)temp_s1 + 0x10)) = (s16) ((*(s16 *)((u8 *)temp_s1 + 0x10)) - ((*(s16 *)((u8 *)temp_s6 + 0x34)) * D_800BE9E4));
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((*(f32 *)((u8 *)temp_s6 + 0x3C)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_s1 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0)) + ((*(f32 *)((u8 *)temp_s1 + 0x1C)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_s1 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 4)) + ((*(f32 *)((u8 *)temp_s1 + 0x20)) * D_800BE9A4));
            sp58 = (*(f32 *)((u8 *)temp_s1 + 0));
            sp5C = (*(f32 *)((u8 *)temp_s1 + 8)) + 30.0f;
            sp60 = (*(f32 *)((u8 *)temp_s1 + 4));
            if ((fabsf(sp58) > 20000.0f) || (fabsf(sp60) > 20000.0f)) {
                goto block_17;
            }
            if (func_15045AF0(&sp58, 0, (*(f32 *)((u8 *)temp_s1 + 8)) - 30.0f, arg0 + 0x60) != 0) {
                (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x60));
            } else {
block_17:
                var_s3 = 1;
            }
            if ((*(s16 *)((u8 *)temp_s1 + 0x10)) < 0) {
                var_s3 = 1;
            }
            if (var_s3 != 0) {
                if (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
                (*(s16 *)((u8 *)((temp_fp + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24))) + 0x10)) = 0;
            }
        } while (var_s2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    (*(s16 *)((u8 *)temp_s6 + 0x46)) = (s16) ((*(s16 *)((u8 *)temp_s6 + 0x46)) + ((*(s16 *)((u8 *)temp_s6 + 0x48)) * D_800BE9E4));
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        temp_v0_2 = temp_fp + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24);
        (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0));
        (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 8));
        (*(f32 *)((u8 *)arg0 + 0x5C)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 4));
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}
