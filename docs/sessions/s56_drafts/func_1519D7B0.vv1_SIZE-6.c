s32 func_1519D7B0(u8 *arg0) {
    s16 temp_t1;
    s32 temp_lo;
    s32 temp_v1;
    s32 var_a2;
    u8 *temp_a3;
    u8 *temp_t0;
    u8 *temp_t8;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)temp_v0 + 6)) & 1)) {
        return 0;
    }
    var_a2 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a2 -= 1;
            if (var_a2 < 0) {
                var_a2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_lo = var_a2 * 0x24;
            temp_a3 = temp_lo + temp_v1;
            (*(s8 *)((u8 *)temp_a3 + 0x20)) = 0xFF;
            temp_t0 = temp_v1 + temp_lo;
            temp_t1 = (*(s16 *)((u8 *)temp_a3 + 0x1E));
            (*(f32 *)((u8 *)temp_a3 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_a3 + 0xC)) * (*(f32 *)((u8 *)temp_v0 + 0x30)));
            (*(f32 *)((u8 *)temp_a3 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_a3 + 0x10)) + ((*(f32 *)((u8 *)temp_v0 + 0x24)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_a3 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_a3 + 0x14)) * (*(f32 *)((u8 *)temp_v0 + 0x30)));
            (*(f32 *)((u8 *)temp_a3 + 0)) = (f32) ((*(f32 *)((u8 *)temp_a3 + 0)) + ((*(f32 *)((u8 *)temp_t0 + 0xC)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_a3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_a3 + 4)) + ((*(f32 *)((u8 *)temp_t0 + 0x10)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_a3 + 8)) = (f32) ((*(f32 *)((u8 *)temp_a3 + 8)) + ((*(f32 *)((u8 *)temp_t0 + 0x14)) * D_800BE9A4));
            if (temp_t1 > 0) {
                (*(s16 *)((u8 *)temp_a3 + 0x1E)) = (s16) (temp_t1 - D_800BE9E4);
            } else {
                (*(s16 *)((u8 *)temp_a3 + 0x1C)) = (s16) ((*(s16 *)((u8 *)temp_a3 + 0x1C)) - (D_800BE9E4 * (*(s16 *)((u8 *)temp_v0 + 0x46))));
            }
            (*(f32 *)((u8 *)temp_a3 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_a3 + 0x18)) + (D_800BE9A4 * (*(f32 *)((u8 *)temp_v0 + 0x34))));
            if ((*(s16 *)((u8 *)temp_a3 + 0x1C)) < 0) {
                (*(u8 *)((u8 *)temp_v0 + 6)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 6)) & ~2);
                if (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
                (*(s16 *)((u8 *)((temp_v1 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24))) + 0x1C)) = 0;
            }
        } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        temp_t8 = temp_v1 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24);
        (*(s32 *)((u8 *)arg0 + 0x54)) = (s32) (*(s32 *)((u8 *)temp_t8 + 0));
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
        (*(s32 *)((u8 *)arg0 + 0x5C)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
    } else {
        (*(s32 *)((u8 *)arg0 + 0x54)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x58)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x5C)) = 0;
    }
    return 1;
}
