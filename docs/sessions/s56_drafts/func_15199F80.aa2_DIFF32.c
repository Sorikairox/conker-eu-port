void func_1519C38C(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3);
extern s32 D_8008FC5C;
extern s32 D_8008FC64;

s32 func_15199F80(u8 *arg0) {
    f32 *temp_s0;
    s32 temp_s6;
    s8 temp_v0;
    s8 temp_v0_2;
    s32 var_s1;
    u8 *temp_a0;
    u8 *temp_a2;
    u8 *temp_s4;
    u8 *temp_t7;
    u8 *temp_v1;

    temp_s4 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s6 = (*(s32 *)((u8 *)arg0 + 0x94));
    (*(u8 *)((u8 *)temp_s4 + 0x150)) = (u8) ((*(u8 *)((u8 *)temp_s4 + 0x150)) & 0xFFEF);
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u16 *)((u8 *)arg0 + 0x1E)) & 8)) {
        return 0;
    }
    temp_v0 = (*(s8 *)((u8 *)temp_s4 + 0x48));
    if ((temp_v0 != -1) && ((*(s32 (**)())((u8 *)&D_8008FC64 + (temp_v0 * 4)))(arg0) == 0)) {
        return 0;
    }
    var_s1 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_s1 -= 1;
            if (var_s1 < 0) {
                var_s1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_s0 = (var_s1 * 0x28) + temp_s6;
            func_1519C38C(temp_s0, temp_s0 + 0xC, (*(f32 *)((u8 *)temp_s4 + 0x20)), D_800BE9A4);
            (*(f32 *)((u8 *)temp_s0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x18)) + ((*(f32 *)((u8 *)temp_s4 + 0x30)) * D_800BE9A4));
        } while (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    temp_a2 = (*(u8 **)((u8 *)temp_s4 + 0x148));
    if ((temp_a2 != NULL) && ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2)) {
        temp_v1 = (*(u8 **)((u8 *)temp_a2 + 0x14));
        temp_a0 = ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x28) + temp_s6;
        (*(s16 *)((u8 *)temp_v1 + 0xE)) = (s16) (s32) (*(f32 *)((u8 *)temp_a0 + 0));
        (*(s16 *)((u8 *)temp_v1 + 0x10)) = (s16) (s32) (*(f32 *)((u8 *)temp_a0 + 4));
        (*(s16 *)((u8 *)temp_v1 + 0x12)) = (s16) (s32) (*(f32 *)((u8 *)temp_a0 + 8));
    }
    temp_v0_2 = (*(s8 *)((u8 *)temp_s4 + 0x38));
    if (temp_v0_2 != -1) {
        (*(s32 (**)())((u8 *)&D_8008FC5C + (temp_v0_2 * 4)))(arg0);
    }
    (*(u8 *)((u8 *)temp_s4 + 0x150)) = (u8) ((*(u8 *)((u8 *)temp_s4 + 0x150)) & 0xFFFE);
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        temp_t7 = temp_s6 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x28);
        (*(s32 *)((u8 *)arg0 + 0x54)) = (s32) (*(s32 *)((u8 *)temp_t7 + 0));
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) (*(s32 *)((u8 *)temp_t7 + 4));
        (*(s32 *)((u8 *)arg0 + 0x5C)) = (s32) (*(s32 *)((u8 *)temp_t7 + 8));
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}
