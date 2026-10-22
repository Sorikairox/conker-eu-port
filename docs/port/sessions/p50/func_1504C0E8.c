//HOIST void func_1504C0E8(struct127 *arg0, s32 arg1, f32 arg2);
s32 func_15064F50(struct127 *, f32, f32, s32, f32);
extern u8 D_800CC69C;
extern u8 D_800CC6D1;
extern f32 D_800CC6D4;
extern s32 D_800CC6DC;

void func_1504C0E8(struct127 *arg0, s32 arg1, f32 arg2) {
    u8 temp_v0_4;
    u8 temp_a1;
    struct126 *var_v1;
    struct126 *temp_v1_4;
    struct126 *temp_v1_3;
    struct126 *temp_v1_2;
    struct126 *temp_v1;
    s32 var_t0;
    s32 temp_v0_3;
    s32 temp_t8;
    s16 temp_v0_2;
    s16 temp_v0;
    f32 var_f2;
    f32 var_f12_2;
    f32 var_f12;
    f32 temp_f0_2;
    f32 temp_f0;
    s32 sp28;
    f32 sp2C;
    f32 sp34;
    f32 sp38;
    f32 sp3C;

    if ((((s16) D_800CC6D2) == 0) && (temp_v1 = arg0->unk31C, temp_v0 = temp_v1->unk12, ((temp_v0 < -0x1D) == 0)) && (temp_v0 < 0x1E)) {
        temp_v1->unk12 = 0;
    } else {
        temp_v1_2 = arg0->unk31C;
        temp_v0_2 = temp_v1_2->unk12;
        temp_v1_2->unk12 = temp_v0_2 + (s32) ((*D_800D1550 / D_800CC6D4) * (f32) (((s16) D_800CC6D2) - temp_v0_2));
    }
    temp_v1_3 = arg0->unk31C;
    if (temp_v1_3->unk6B == 0) {
        var_t0 = 0x3E7;
        if ((arg0->unk65 != 0) && (arg0->stunned == 0)) {
            func_15064DD0(arg0);
            return;
        }
        if ((arg0->unk81 == 0) && (arg0->stunned == 0) && (arg0->in_water == 0)) {
            if ((arg0->unk83 == 0) && (temp_v1_3->unk11A != 3)) {
                arg0->unk80 = 1;
                arg0->unk100 &= 0xF3;
                D_800CC6DC |= 0x80;
                sp38 = 0.0f;
                sp3C = 4.0f;
                var_v1 = arg0->unk31C;
                var_f12 = 1.0f;
                var_f2 = (arg0->xz_velocity * 0.4f) + (arg2 * 0.6f);
                if (((*(s16 *)((u8 *)var_v1 + 0x46)) > 0) || (var_v1->unk4E != 0) || ((s32) arg0->unk13C >= 0x64) || (arg1 != 0) || ((*(u16 *)((u8 *)var_v1 + 0x32)) & 3) || (var_v1->unk78 != 0) || (var_v1->pad17[3] != 0) || (var_v1->unk8 > 0) || (var_v1->pad17[0] != 0)) {
                    sp28 = 0x3E7;
                    sp34 = var_f2;
                    sp2C = 1.0f;
                    temp_v0_3 = func_15064F50(arg0, var_f2, var_f2, arg1, arg2);
                    var_t0 = sp28;
                    var_f2 = sp34;
                    var_f12 = sp2C;
                    if (temp_v0_3 == 0) {
                        var_v1 = arg0->unk31C;
                        goto block_25;
                    }
                } else {
block_25:
                    temp_t8 = *(u16 *)D_800CC6A4 & 0x2000;
                    if ((temp_t8 == 0) || (D_800CC6D1 != 0) || (var_v1->unk78 != 0) || ((var_v1->unk4E & 0xF) == 1)) {
                        if (arg0->xz_velocity > 4.0f) {
                            var_v1->pad37 = 0;
                            var_v1 = arg0->unk31C;
                        }
                        temp_a1 = var_v1->unk4E;
                        if (((temp_a1 == 1) || (temp_a1 == 0x81)) && (var_f2 > 1.0f)) {
                            arg2 = 10.0f;
                            temp_f0 = arg0->xz_velocity;
                            var_t0 = 0x302;
                            var_f12_2 = (temp_f0 / 7.0f) + 0.2f;
                            if (temp_f0 > 23.0f) {
                                var_t0 = 0x303;
                                var_f12_2 = (temp_f0 / 23.0f) + 0.3f;
                            }
                        } else if ((var_v1->chased > 0) && (var_f2 >= 5.0f)) {
                            var_t0 = 0x2B;
                            var_f12_2 = var_f2 / 12.0f;
                        } else if ((var_v1->chasing > 0) && (var_f2 >= 5.0f)) {
                            var_t0 = 0xDF;
                            var_f12_2 = var_f2 / 12.0f;
                        } else {
                            temp_f0_2 = arg0->unk118;
                            if ((temp_f0_2 != -10000.0f) && (arg0->y_position < temp_f0_2) && (arg0->xz_velocity >= 1.0f) && (temp_a1 == 0)) {
                                var_t0 = 0x8B;
                                arg0->unkAA = 0x4B;
                                var_f12_2 = (var_f2 / 18.0f) + 0.2f;
                            } else if (var_f2 > 14.0f) {
                                var_t0 = 0x1B2;
                                if (D_800BE9F0 != 4) {
                                    var_t0 = 2;
                                }
                                var_f12_2 = (var_f2 / 23.0f) + 0.8f;
                            } else if ((var_f2 > 6.0f) || ((arg2 < 1.0f) && (arg0->xz_velocity > 1.0f))) {
                                var_t0 = 1;
                                var_f12_2 = (var_f2 * 0.125f) + 0.3f;
                            } else if (var_f2 > 1.0f) {
                                var_t0 = 0;
                                sp3C = 15.0f;
                                if (arg0->id == 0x80) {
                                    var_t0 = 1;
                                }
                                var_f12_2 = (var_f2 * 0.125f) + 0.1f;
                            } else {
                                sp2C = var_f12;
                                var_f12_2 = sp2C;
                                var_t0 = func_1504C078();
                            }
                        }
                        if ((arg0->unk28 > 60.0f) && (arg0->unk31C->unk4E == 0)) {
                            var_f12_2 = 0.5f;
                            var_t0 = 0x38;
                            arg0->unk100 |= 0x10;
                        }
                        if (arg0->xz_velocity > 18.0f) {
                            temp_v0_4 = arg0->unk31C->unk11A;
                            if ((temp_v0_4 != 1) && (temp_v0_4 != 3) && (arg2 == 0.0f) && (arg0->unk28 == 0.0f) && (D_800CC69C == 0)) {
                                var_f12_2 = 0.5f;
                                var_t0 = 0x21;
                                sp3C = 3.0f;
                                arg0->disable_run = 8;
                                arg0->unk83 = 0x11;
                            }
                        }
                        goto block_78;
                    }
                    sp2C = var_f12;
                    if (temp_t8 != 0) {
                        if (arg0->xz_velocity < 3.0f) {
                            var_v1->pad37 = 1;
                        }
                        if ((arg0->unk44 > 2.6f) && (temp_v1_4 = arg0->unk31C, (temp_v1_4->pad37 != 0))) {
                            (*(s32 *)((u8 *)temp_v1_4 + 4)) = 1;
                            arg0->unkAA = 0x28;
                            sp3C = 5.0f;
                            sp2C = (arg0->unk44 / 15.0f) + 0.5f;
                            var_t0 = func_1504C0B8();
                        } else {
                            var_f12_2 = 1.5f;
                            var_t0 = 0x16;
                            sp3C = 6.0f;
block_78:
                            sp2C = var_f12_2;
                        }
                    }
                    goto block_79;
                }
            } else {
block_79:
                if (var_t0 != 0x3E7) {
                    func_1505E650(arg0, var_t0 & 0xFFFF, sp2C, sp3C, sp38, 0.0f, 0);
                }
            }
        } else if ((arg0->unk84.uh == 0x21) && (D_800CC6D1 == 0) && (arg0->unk44 == 0.0f) && (*(u16 *)D_800CC6A4 & 0x2000)) {
            func_1505E650(arg0, 0x16U, 1.5f, 6.0f, 0.0f, 0.0f, 0);
        }
    }
}
