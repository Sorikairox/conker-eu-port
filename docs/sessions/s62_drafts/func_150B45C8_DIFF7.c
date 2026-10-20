s32 func_150B45C8(u8 *arg0) {
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_a3;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)temp_v0 + 0x1C)) & 1)) {
        return 0;
    }
    var_a2 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a2 -= 1;
            var_a1 = 0;
            if (var_a2 < 0) {
                var_a2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_a3 = (0, temp_v1) + (var_a2 * 0x24);
            (*(s16 *)((u8 *)temp_a3 + 0x1C)) = 0xFF;
            (*(s16 *)((u8 *)temp_a3 + 0x1E)) = (s16) ((*(s16 *)((u8 *)temp_a3 + 0x1E)) - D_800BE9E4);
            if ((*(s16 *)((u8 *)temp_a3 + 0x1E)) < 0) {
                var_a1 = 1;
            }
            (*(f32 *)((u8 *)temp_a3 + 0x10)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0xC)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0x10)));
            (*(f32 *)((u8 *)temp_a3 + 0)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0xC)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0)));
            (*(f32 *)((u8 *)temp_a3 + 4)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0x10)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 4)));
            (*(f32 *)((u8 *)temp_a3 + 8)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0x14)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 8)));
            (*(f32 *)((u8 *)temp_a3 + 0x18)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0x28)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0x18)));
            if ((var_a1 != 0) && (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)))) {
                do {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                    if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                    }
                    (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
            }
        } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        temp_t6 = (0, temp_v1) + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24);
        (*(s32 *)((u8 *)arg0 + 0x54)) = (s32) (*(s32 *)((u8 *)temp_t6 + 0));
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) (*(s32 *)((u8 *)temp_t6 + 4));
        (*(s32 *)((u8 *)arg0 + 0x5C)) = (s32) (*(s32 *)((u8 *)temp_t6 + 8));
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}
