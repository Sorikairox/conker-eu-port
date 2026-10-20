typedef struct { f32 x, y, z; } V3;
void func_151D8CC8(f32 *arg0, f32 *arg1, f32 arg2);
s32 func_151D7FE8(u8 *arg0) {
    f32 spB4[3];
    f32 *temp_a0;
    f32 temp_f0;
    f32 temp_f18;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f22;
    f32 var_f2;
    f32 sp88[3];
    V3 *var_s4;
    u8 *sp70;
    f32 sp64;
    s32 temp_s3;
    s8 temp_v1;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s3 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_v0 = (*(u8 **)((u8 *)temp_s1 + 0));
    if (!((*(u8 *)((u8 *)temp_v0 + 0x2D)) & 1)) {
        return 0;
    }
    var_s4 = (V3 *)sp88;
    *(V3 *)spB4 = *(V3 *)(temp_v0 + 0x30);
    *(V3 *)(arg0 + 0x10) = *(V3 *)spB4;
    (*(f32 *)((u8 *)temp_s1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x14)) + (0.25f * D_800BE9A4));
    temp_f18 = (*(f32 *)((u8 *)temp_s1 + 0x14));
    if (temp_f18 > 1.0f) {
        temp_f0 = 1.0f / temp_f18;
        temp_v0_2 = temp_s1 + 4;
        *var_s4 = *(V3 *)temp_v0_2;
        var_f22 = (*(f32 *)((u8 *)temp_s1 + 0x10)) + D_800BE9A4;
        temp_f26 = var_f22 * temp_f0;
        temp_f28 = (spB4[0] - (*(f32 *)((u8 *)temp_s1 + 4))) * temp_f0;
        sp70 = temp_v0_2;
        temp_f30 = (spB4[1] - (*(f32 *)((u8 *)temp_s1 + 8))) * temp_f0;
        var_f2 = (spB4[2] - (*(f32 *)((u8 *)temp_s1 + 0xC))) * temp_f0;
        do {
            temp_a0 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x1C) + temp_s3;
            *(V3 *)temp_a0 = *var_s4;
            (*(f32 *)((u8 *)temp_a0 + 0xC)) = 0.0f;
            (*(f32 *)((u8 *)temp_a0 + 0x10)) = 0.0f;
            (*(s8 *)((u8 *)temp_a0 + 0x14)) = 0;
            (*(f32 *)((u8 *)temp_a0 + 0x18)) = 0.0f;
            sp64 = var_f2;
            func_151D8CC8(temp_a0, temp_a0 + 0xC, var_f22);
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            var_f22 -= temp_f26;
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v1 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v1 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            var_s4->x += temp_f28;
            var_s4->y += temp_f30;
            var_s4->z += var_f2;
            (*(f32 *)((u8 *)temp_s1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0x14)) > 1.0f);
        *(V3 *)sp70 = *var_s4;
        (*(f32 *)((u8 *)temp_s1 + 0x10)) = var_f22;
    }
    return 1;
}
