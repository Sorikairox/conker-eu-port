s32 func_1502DE10(s32);

struct124 *func_151846C0(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 sp3C;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f12;
    f32 var_f2;
    s32 temp_t2;
    s32 var_a0;
    s32 var_v0;
    struct127 *temp_t0;

    temp_t0 = &D_800CC2D0[arg0];
    sp3C = (s32) temp_t0->id;
    *arg3 = 0.0f;
    *arg2 = 0.0f;
    *arg1 = 0.0f;
    if ((temp_t0->unk1D4 == NULL) || (D_800C42B0 != 0)) {
        return NULL;
    }
    var_v0 = func_1502DE10(sp3C);
    if (var_v0 > 0) {
        var_a0 = 0;
        temp_t2 = var_v0 << 6;
        do {
            var_v0 = (s32) &temp_t0->unk1D4->pad0[var_a0];
            var_f0 = (*(f32 *)((u8 *)var_v0 + 0x30)) - temp_t0->x_position;
            var_a0 += 0x40;
            var_f2 = (*(f32 *)((u8 *)var_v0 + 0x34)) - temp_t0->y_position;
            var_f12 = (*(f32 *)((u8 *)var_v0 + 0x38)) - temp_t0->z_position;
            if (var_f0 < 0.0f) {
                var_f0 = -var_f0;
            }
            if (*arg1 < var_f0) {
                *arg1 = var_f0;
            }
            if (var_f2 < 0.0f) {
                var_f2 = -var_f2;
            }
            if (*arg2 < var_f2) {
                *arg2 = var_f2;
            }
            if (var_f12 < 0.0f) {
                var_f12 = -var_f12;
            }
            if (*arg3 < var_f12) {
                *arg3 = var_f12;
            }
        } while (var_a0 < temp_t2);
    }
    if ((*arg1 == 0.0f) || (*arg2 == 0.0f) || (*arg3 == 0.0f)) {
        temp_f2 = temp_t0->xz_scale * (f32) D_800D1C90[temp_t0->id]->unk1A;
        *arg3 = temp_f2;
        *arg1 = temp_f2;
        var_v0 = (s32) D_800D1C90[temp_t0->id];
        *arg2 = temp_t0->y_scale * (f32) ((*(s16 *)((u8 *)var_v0 + 0x1E)) + (*(s16 *)((u8 *)var_v0 + 0x1C)));
    }
    return (struct124 *) var_v0;
}
