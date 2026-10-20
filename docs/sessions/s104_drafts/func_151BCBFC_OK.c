typedef struct { s32 x[3]; } S12_CBFC;
typedef struct { S12_CBFC pos; s16 t; u8 a; u8 pad[5]; } E20_CBFC;
s32 func_151BCBFC(u8 *arg0) {
    s16 temp_a2;
    s32 temp_lo;
    u8 *temp_v0;
    s32 var_a1;
    u8 *temp_t4;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u16 *)((u8 *)arg0 + 0x1E)) & 8)) {
        return 0;
    }
    var_a1 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a1 -= 1;
            if (var_a1 < 0) {
                var_a1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v1 = (var_a1 * 0x14) + temp_v0;
            (*(s16 *)((u8 *)temp_v1 + 0xC)) = (s16) ((*(s16 *)((u8 *)temp_v1 + 0xC)) - D_800BE9E4);
            temp_a2 = (*(s16 *)((u8 *)temp_v1 + 0xC));
            if (temp_a2 < 0) {
                if (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
            } else if (temp_a2 < 0xA) {
                temp_lo = temp_a2 * 0x19;
                if (temp_lo < (s32) (*(u8 *)((u8 *)temp_v1 + 0xE))) {
                    (*(u8 *)((u8 *)temp_v1 + 0xE)) = (u8) temp_lo;
                }
            }
        } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        *(S12_CBFC *)(arg0 + 0x54) = ((E20_CBFC *)temp_v0)[*(s8 *)(arg0 + 0x2D)].pos;
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}
