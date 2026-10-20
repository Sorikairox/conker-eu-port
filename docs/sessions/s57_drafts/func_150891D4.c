f32 func_15144BC8(f32);
f32 func_15049AD0(s32 *, s32, f32);
f32 func_15049B94(s32 *, s32, f32, s32 *);
s32 func_15088E84(struct_eu_80087640 *, f32, struct_eu_800D2778 *);
s32 func_150893AC(struct_eu_80087640 *, s32 *, s32 *, s32 *);

void func_150891D4(u8 *arg0) {
    s32 sp98[2];
    s32 sp88[4];
    s32 sp78[4];
    s32 sp68[4];
    f32 temp_f0;
    s16 temp_v0_2;
    s32 temp_v0;
    s32 var_v0;
    struct_eu_80087640 *temp_s4;
    struct_eu_800D2778 *temp_a1;
    struct_eu_800D2778 *var_v1;
    u8 temp_a0;
    u8 var_s0;

    temp_v0 = func_150889D8(arg0);
    if (temp_v0 >= 0) {
        temp_s4 = &D_80087640[temp_v0];
        temp_s4->unk0 = 0.5f;
        temp_s4->unk4 = 0.5f;
        temp_s4->unk8 = 0.5f;
        do {
            var_s0 = 0;
            var_v0 = 0;
            var_v1 = &D_800D2778[temp_s4->pad28[4]];
loop_3:
            temp_a0 = var_v1->pad8[1];
            var_v0 += 1;
            if (temp_a0 != 0xFF) {
                temp_a1 = &D_800D2778[temp_a0];
                if (temp_a1->pad8[6] == 4) {
                    var_s0 = temp_a1->pad8[7];
                }
            }
            var_v1 += 1;
            if (var_v0 != 5) {
                goto loop_3;
            }
            if (var_s0 != 0) {
                func_15088E84(temp_s4, 0x3F800000, D_800D2778);
            }
        } while (var_s0 != 0);
        temp_s4->unk8 = 0.0f;
        func_150893AC(temp_s4, sp88, sp78, sp68);
        (*(f32 *)((u8 *)arg0 + 0x14)) = func_15049B94(sp88, 0, temp_s4->unk8, &sp98[1]);
        (*(f32 *)((u8 *)arg0 + 0x18)) = func_15049AD0(sp78, 0, temp_s4->unk8);
        (*(f32 *)((u8 *)arg0 + 0x1C)) = func_15049B94(sp68, 0, temp_s4->unk8, sp98);
        temp_f0 = func_15144BC8((f32) (func_1505A630((*(f32 *)((u8 *)temp_s4 + 0x10)), (*(f32 *)((u8 *)temp_s4 + 0xC)), 0) + 0x8000) * 0.005493164f);
        (*(f32 *)((u8 *)arg0 + 0x40)) = temp_f0;
        temp_v0_2 = (s32) (temp_f0 * 182.04445f) - 0x4000;
        (*(s16 *)((u8 *)arg0 + 0x7A)) = temp_v0_2;
        (*(s16 *)((u8 *)arg0 + 0x78)) = temp_v0_2;
        (*(s16 *)((u8 *)arg0 + 0x76)) = temp_v0_2;
    }
}
