#define MTX_96A0(a) (((f32 (*)[16])((a) + 0x78))[D_800BE9C0])
s32 func_151096A0(u8 *arg0, s16 arg1) {
    f32 spC8[16];
    f32 sp94[3];
    f32 *temp_v0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 var_f22;
    f32 var_f24;
    s16 var_s1;
    u8 *temp_s0;
    u8 *temp_s0_2;

    temp_s0 = arg0 + (*(s32 *)((u8 *)arg0 + 0x50)) + 0xF8;
    func_150A8050((f32 (*)[4]) spC8, (*(f32 *)((u8 *)temp_s0 + 0)), 0.0f, (*(f32 *)((u8 *)temp_s0 + 4)));
    spC8[13] = (*(f32 *)((u8 *)temp_s0 + 0x10));
    spC8[0] *= 0.157f;
    spC8[1] *= 0.157f;
    spC8[2] *= 0.157f;
    spC8[4] *= 0.157f;
    spC8[5] *= 0.157f;
    spC8[6] *= 0.157f;
    spC8[8] *= 0.157f;
    spC8[9] *= 0.157f;
    spC8[10] *= 0.157f;
    guMtxF2L((f32 (*)[4]) spC8, (Mtx *)MTX_96A0(arg0));
    temp_v0 = func_15144B34((s32) arg1);
    temp_f14 = (*(f32 *)((u8 *)temp_v0 + 0));
    var_s1 = 0;
    if ((fabsf(temp_f14) > 0.0001f) || (fabsf((*(f32 *)((u8 *)temp_v0 + 4))) > 0.0001f)) {
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 8));
        temp_f12 = 1.0f / sqrtf((temp_f14 * temp_f14) + (temp_f2 * temp_f2));
        var_f22 = temp_f2 * temp_f12;
        var_f24 = -temp_f14 * temp_f12;
    } else {
        var_f22 = 1.0f;
        var_f24 = 0.0f;
    }
    do {
        temp_s0_2 = (*(s32 *)((u8 *)((arg0 + (D_800BE9C0 * 0x10) + (arg1 * 4))) + 0x58)) + (var_s1 * 0x10);
        func_150A7E40((f32 (*)[4]) spC8, (f32) (*(s16 *)((u8 *)temp_s0_2 + 0)), (f32) (*(s16 *)((u8 *)temp_s0_2 + 2)), (f32) (*(s16 *)((u8 *)temp_s0_2 + 4)), sp94, &sp94[1], &sp94[2]);
        var_s1 += 1;
        (*(s16 *)((u8 *)temp_s0_2 + 8)) = (s16) (s32) (((((sp94[0] * var_f22) + (sp94[2] * var_f24)) * 0.21300001f) + 26.0f) * 32.0f);
        (*(s16 *)((u8 *)temp_s0_2 + 0xA)) = (s16) (s32) (((sp94[1] * 0.358f) + 81.0f) * 32.0f);
    } while (var_s1 != 0x10);
    return 1;
}
