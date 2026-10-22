void func_15047680(f32 mf[4][4], f32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_15059B54(struct127 *arg0, u16 arg1);
struct216 *func_1507BB28(s32, s32);
extern f32 D_800CC704;
extern f32 D_800CC70C;
extern s32 D_800D1968;

void func_15056B08(struct127 *arg0) {
    f32 sp98[4][4];
    u8 *temp_v0_13;
    u8 var_v1_4;
    u8 var_v1_2;
    u8 var_v1;
    u8 var_t0_2;
    u8 var_t0;
    u8 temp_v1_7;
    u8 temp_v1_6;
    u8 temp_v1_5;
    u8 temp_v1_2;
    u8 temp_v0_9;
    u8 temp_v0_8;
    u8 temp_v0_5;
    u8 temp_v0_4;
    u8 temp_v0_2;
    u8 temp_v0_17;
    u8 temp_v0_16;
    u8 temp_v0_15;
    u8 temp_v0_11;
    u8 temp_v0;
    u8 temp_t9;
    u8 temp_t8_2;
    u8 temp_t8;
    u8 temp_t6;
    u8 temp_t5;
    u8 temp_t4;
    u8 temp_t1_2;
    u8 temp_t1;
    u8 temp_a0_2;
    u8 temp_a0;
    u16 var_v0_2;
    u16 var_a2_3;
    u16 temp_v1_3;
    u16 temp_v0_10;
    u16 temp_t3;
    u16 temp_a1;
    struct216 *var_v0;
    struct127 *var_a2;
    struct127 *var_a0;
    struct127 *temp_v1_4;
    struct127 *temp_v0_18;
    struct127 *temp_v0_14;
    struct127 *temp_v0_12;
    struct126 *temp_v0_7;
    struct126 *temp_v0_6;
    s8 temp_v1_8;
    s32 var_v1_3;
    s32 var_a3;
    s32 var_a2_2;
    s32 var_a1;
    s32 temp_v1;
    s32 temp_v0_3;
    s32 temp_v0_19;
    s32 temp_t7;
    s32 temp_hi;
    f32 var_f8_3;
    f32 var_f8_2;
    f32 var_f8;
    f32 var_f6_3;
    f32 var_f6_2;
    f32 var_f6;
    f32 var_f4;
    f32 var_f2_3;
    f32 var_f2_2;
    f32 var_f2;
    f32 var_f16_2;
    f32 var_f16;
    f32 var_f14;
    f32 var_f12;
    f32 var_f10_2;
    f32 var_f10;
    f32 var_f0_3;
    f32 var_f0_2;
    f32 var_f0;
    f32 temp_f8_2;
    f32 temp_f8;
    f32 temp_f4_5;
    f32 temp_f4_4;
    f32 temp_f4_3;
    f32 temp_f4_2;
    f32 temp_f4;
    f32 temp_f2_5;
    f32 temp_f2_4;
    f32 temp_f2_3;
    f32 temp_f2_2;
    f32 temp_f2;
    f32 temp_f18;
    f32 temp_f16;
    f32 temp_f14_3;
    f32 temp_f14_2;
    f32 temp_f14;
    f32 temp_f12_6;
    f32 temp_f12_5;
    f32 temp_f12_4;
    f32 temp_f12_3;
    f32 temp_f12_2;
    f32 temp_f12;
    f32 temp_f10;
    f32 temp_f0_3;
    f32 temp_f0_2;
    f32 temp_f0;
    f32 sp3C;
    struct127 *sp48;
    s32 sp4C;
    f32 sp60;
    f32 sp64;
    f32 sp68;
    u16 sp78;
    f32 sp7C;
    f32 sp80;
    f32 sp84;
    s32 sp88;
    f32 sp8C;
    f32 sp90;
    f32 sp94;
    f32 spE0;
    f32 spE4;
    u8 spEB;
    s32 spF0;
    f32 spF4;
    f32 sp100;
    s32 sp104;
    s32 sp108;
    s32 sp10C;
    f32 sp11C;
    f32 sp120;
    f32 sp124;
    f32 sp12C;
    f32 sp130;
    struct124 *sp134;
    u8 sp13B;
    f32 sp13C;
    f32 sp144;
    u8 sp149;
    u16 sp14A;
    f32 sp14C;
    u8 sp153;
    f32 sp154;
    f32 sp158;
    u8 sp15F;
    f32 sp160;
    f32 sp164;
    f32 sp16C;
    f32 sp170;
    f32 sp174;

    sp13B = 1;
    temp_v0 = arg0->unk23A;
    if (temp_v0 != 0) {
        arg0->unk218 = func_1507BB28(4, temp_v0);
        arg0->unk21C = 0;
        arg0->unk23A = 0;
    }
    if ((D_800C3638 == 0) || (func_15022A8C(arg0) == 0)) {
        if ((arg0->unkF4 & 0x1000) && (arg0->unk28 < 0.2f)) {
            arg0->unk21C = 0;
        }
        func_1507BC14(arg0);
        var_v1 = arg0->unk223;
        var_t0 = var_v1;
        if ((var_v1 == 0xE) || (var_v1 == 0xF) || (var_v1 == 0x10)) {
            var_v1 = 1;
            var_t0 = 1;
        }
        if (var_t0 == 0x11) {
            var_v1 = 0;
        }
        if (arg0->stunned == 0) {
            sp14A = (u16) ((s32) (((arg0->unk1E5 << 8) + arg0->unk1E7) * D_800CC264) / 100);
            sp149 = arg0->unk1E6;
            temp_v0_2 = arg0->unk13F;
            if (D_800D2528[temp_v0_2] == 0) {
                arg0->xz_velocity = 0.0f;
                func_1505841C(arg0, 0.0f);
                return;
            }
            var_t0_2 = var_v1;
            sp134 = D_800D1C90[arg0->id];
            temp_a0 = arg0->unk23D;
            if (temp_a0 == 0xFF) {
                sp164 = 1e9f;
            } else {
                temp_f4 = (f32) (temp_a0 * 8);
                sp164 = temp_f4;
                sp164 = temp_f4 * temp_f4;
            }
            temp_v1 = D_800D2104[temp_v0_2];
            if ((*(u16 *)((u8 *)temp_v1 + 6)) != 0) {
                sp174 = (f32) (*(s16 *)((u8 *)temp_v1 + 0)) - arg0->x_position;
                sp170 = (f32) (*(s16 *)((u8 *)temp_v1 + 4)) - arg0->z_position;
            }
            temp_v0_3 = arg0->unk25C;
            if ((temp_v0_3 & 4) && !(temp_v0_3 & 1) && ((var_t0_2 == 1) || (var_t0_2 == 3))) {
                arg0->unk21C = 0;
            }
            if ((arg0->unk25C & 1) && ((var_t0_2 == 0) || (var_t0_2 == 5))) {
                sp4C = (s32) var_t0_2;
                var_t0_2 = (u8) sp4C;
                if (func_1505693C(arg0, (s32) arg0->unk25B) != 0) {
                    sp4C = (s32) var_t0_2;
                    temp_v1_2 = arg0->unk25B;
                    var_t0_2 = (u8) sp4C;
                    arg0->unk218 = func_1507BB28(1, arg0->unk233);
                    arg0->unk21C = 0;
                    arg0->unkA8 = temp_v1_2 | 0x80;
                    arg0->unk222 = temp_v1_2;
                }
            }
            temp_v0_4 = arg0->unk25A;
            if (temp_v0_4 != 0) {
                var_f10 = (f32) temp_v0_4;
                if ((s32) temp_v0_4 < 0) {
                    var_f10 += 4294967296.0f;
                }
                arg0->unk44 = var_f10;
            }
            if ((var_t0_2 == 1) || (var_t0_2 == 0xC) || (var_t0_2 == 2) || (var_t0_2 == 3) || (var_t0_2 == 9) || (var_t0_2 == 0xA) || ((var_t0_2 == 6) && !(arg0->unk22C & 1))) {
                var_v1_2 = arg0->unk222;
                var_a2 = &D_800CC2D0[var_v1_2];
                sp174 = var_a2->x_position;
                sp170 = var_a2->z_position;
                sp16C = var_a2->y_position;
                if (arg0->unk223 == 0x10) {
                    sp15F = var_v1_2;
                    sp48 = var_a2;
                    sp4C = (s32) var_t0_2;
                    temp_f0 = func_1505A72C(var_a2, arg0);
                    sp120 = temp_f0;
                    temp_t6 = arg0->unk231;
                    var_f8 = (f32) temp_t6;
                    if ((s32) temp_t6 < 0) {
                        var_f8 += 4294967296.0f;
                    }
                    temp_f4_2 = sp48->xz_velocity * (temp_f0 / var_f8);
                    sp124 = temp_f4_2;
                    func_1505A184(sp48->unk76, temp_f4_2, 0.0f, &sp124, &sp120, &sp11C);
                    var_v1_2 = sp15F;
                    var_t0_2 = (u8) sp4C;
                    var_a2 = sp48;
                    sp174 += sp124;
                    sp170 += sp120;
                }
                temp_f8 = sp174 - arg0->x_position;
                sp130 = temp_f8;
                var_f16 = sp170 - arg0->z_position;
                var_f12 = sqrtf((temp_f8 * temp_f8) + (var_f16 * var_f16));
                if ((var_t0_2 == 1) && (arg0->unk44 > 1.0f) && (sqrtf(sp164) < (var_f12 * 0.8f))) {
                    arg0->unk21C = 0;
                }
                temp_v0_5 = arg0->id;
                if (temp_v0_5 != 0x16) {
                    if ((var_t0_2 == 1) && (arg0->unk234 != 0) && ((var_f12 < 370.0f) || (temp_v0_5 == 0x21)) && ((s32) var_v1_2 < 4) && ((arg0->xz_velocity > 15.0f) || (temp_v0_5 == 0x53))) {
                        temp_v0_6 = var_a2->unk31C;
                        if (temp_v0_6 != NULL) {
                            temp_v0_6->chased = 0xA;
                        }
                    }
                    if ((var_t0_2 == 2) && (var_f12 < 470.0f) && ((s32) var_v1_2 < 4) && (((arg0->unk76 - var_a2->unk76) - 0x4000) & 0x8000)) {
                        temp_v0_7 = var_a2->unk31C;
                        if (temp_v0_7 != NULL) {
                            temp_v0_7->chasing = 6;
                        }
                    }
                }
                switch (var_t0_2) {                 /* irregular */
                case 9:
                    break;
                default:
                    sp13B = 0;
                    /* fallthrough */
                case 10:
                case 12:
                    if ((arg0->unk22C & 0x80) && (fabsf((arg0->y_position - arg0->unk28) - (var_a2->y_position - var_a2->unk28)) > 30.0f)) {
                        arg0->unk21C = 0;
                    }
                    sp48 = var_a2;
                    if (arg0->unk223 != 0xF) {
                        sp12C = var_f16;
                        sp160 = var_f12;
                        sp4C = (s32) var_t0_2;
                        sp48 = var_a2;
                        var_t0_2 = (u8) sp4C;
                        var_f12 = sp160;
                        var_f16 = sp12C;
                        if (func_1505693C(arg0, (s32) arg0->unk222) == 0) {
                            arg0->unk21C = 0;
                        }
                    }
                    if ((u16) arg0->unk22E != 0) {
                        var_f2 = 0.0f;
                    } else {
                        temp_v0_8 = arg0->unk236;
                        if (temp_v0_8 == 0) {
                            var_f2 = (f32) (arg0->unk23C * 8);
                        } else if (temp_v0_8 == 0xFF) {
                            var_f2 = 3000000.0f;
                        } else {
                            var_f2 = (f32) (temp_v0_8 * 8);
                        }
                    }
                    if (((var_t0_2 == 1) || (var_t0_2 == 6) || (var_t0_2 == 0xA)) && (arg0->unk234 != 0) && (var_f12 < var_f2)) {
                        var_v1_3 = 1;
                        if ((arg0->id == 8) && (var_f2 < fabsf(arg0->y_position - sp48->y_position))) {
                            var_v1_3 = 0;
                        }
                        temp_v0_9 = arg0->unk22A;
                        if (temp_v0_9 != 0) {
                            var_f4 = (f32) temp_v0_9;
                            if ((s32) temp_v0_9 < 0) {
                                var_f4 += 4294967296.0f;
                            }
                            if ((D_800C3E78 != 0) && (fabsf(arg0->y_position - *D_800CC2E8) < (var_f4 * 8.0f))) {
                                var_v1_3 = 0;
                            }
                        }
                        if (var_v1_3 != 0) {
                            sp4C = (s32) var_t0_2;
                            temp_v0_10 = func_1505A630(sp130, -var_f16, 0);
                            temp_a0_2 = arg0->unk237;
                            var_t0_2 = (u8) sp4C;
                            if ((temp_a0_2 != 0) && (((((s32) (arg0->unk76 - temp_v0_10) >> 8) + ((s32) temp_a0_2 / 2)) & 0xFF) < (s32) temp_a0_2)) {
                                sp4C = (s32) var_t0_2;
                                var_t0_2 = (u8) sp4C;
                                arg0->unk218 = func_1507BB28(2, arg0->unk234);
                                arg0->unk21C = 0;
                            }
                        }
                    }
                    break;
                }
            }
            if (sp13B != 0) {
                temp_v1_3 = (u16) arg0->unk22E;
                if (arg0->unk235 != 0) {
                    sp10C = 0;
                } else {
                    sp10C = 1;
                }
                if (temp_v1_3 != 0) {
                    if ((s32) D_800BE9A0 >= (s32) temp_v1_3) {
                        arg0->unk22E = 0;
                    } else {
                        arg0->unk22E = temp_v1_3 - D_800BE9A0;
                    }
                }
                if (arg0->unk241 != 0) {
                    var_a3 = 0;
                    var_a0 = D_800CC2D0;
                    var_a1 = 0;
                    var_f16_2 = (f32) (arg0->unk23F * 8);
                    do {
                        if ((var_a0->interaction_state != 0) && (arg0->unk240 == var_a0->id) && (var_a0->unk2FA != 0)) {
                            temp_f12 = var_a0->x_position - arg0->x_position;
                            temp_f14 = arg0->z_position - var_a0->z_position;
                            temp_f2 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14));
                            if (temp_f2 < var_f16_2) {
                                sp100 = var_f16_2;
                                spF4 = temp_f2;
                                spF0 = (s32) (sp134->unk17 * 3) / 2;
                                sp4C = (s32) var_t0_2;
                                sp104 = var_a3;
                                sp108 = var_a1;
                                sp48 = var_a0;
                                var_a0 = sp48;
                                var_a1 = sp108;
                                var_a3 = sp104;
                                var_t0_2 = (u8) sp4C;
                                var_f16_2 = sp100;
                                if ((((((s32) arg0->unk7A >> 8) - (func_1505A630(temp_f12, temp_f14, 0) >> 8)) + (spF0 / 2)) & 0xFF) < spF0) {
                                    var_a3 = var_a1 + 1;
                                    var_f16_2 = spF4;
                                }
                            }
                        }
                        var_a1 += 1;
                        var_a0 += 1;
                    } while (var_a1 != 0x19);
                    if (var_a3 != 0) {
                        sp4C = (s32) var_t0_2;
                        sp104 = var_a3;
                        var_t0_2 = (u8) sp4C;
                        arg0->unk218 = func_1507BB28(0, arg0->unk241);
                        arg0->unk21C = 0;
                        arg0->unk222 = sp104 - 1;
                        arg0->unkA8 = sp104 + 0x7F;
                        arg0->unk22E = 5;
                        if (arg0->unk242 != 0) {
                            temp_v1_4 = &D_800CC2D0[sp104];
                            D_800D154C = temp_v1_4 - 1;
                            sp4C = (s32) var_t0_2;
                            sp48 = temp_v1_4;
                            (*(struct216 **)((u8 *)sp48 + -0x114)) = func_1507BB28(0, arg0->unk242);
                            (*(s16 *)((u8 *)sp48 + -0x110)) = 0;
                            var_t0_2 = (u8) sp4C;
                            (*(u8 *)((u8 *)sp48 + -0x10A)) = (u8) D_800C3E78;
                            D_800D154C = arg0;
                        }
                    }
                }
                if (((u16) arg0->unk22E == 0) && (var_t0_2 != 4) && (var_t0_2 != 7) && (((sp10C == 0) && (arg0->unk235 != 0)) || ((sp10C == 1) && (arg0->unk233 != 0) && !(arg0->unk25C & 4)))) {
                    temp_t8 = (*(u8 *)((u8 *)sp134 + 0x18));
                    var_f10_2 = (f32) temp_t8;
                    if ((s32) temp_t8 < 0) {
                        var_f10_2 += 4294967296.0f;
                    }
                    if (var_f10_2 <= arg0->xz_velocity) {
                        sp4C = (s32) var_t0_2;
                        var_t0_2 = (u8) sp4C;
                        if (func_1505693C(arg0, 0) != 0) {
                            spEB = 0;
                            temp_f12_2 = D_800CC704 - (f32) arg0->unk1A4;
                            temp_f14_2 = (f32) arg0->unk1A8 - D_800CC70C;
                            if ((arg0->id == 0x9E) && (arg0->unk2E4 == 0)) {
                                sp164 = 129600.0f;
                            }
                            temp_f0_2 = (temp_f12_2 * temp_f12_2) + (temp_f14_2 * temp_f14_2);
                            if ((temp_f0_2 < sp164) && (temp_f0_2 < 1e8f)) {
                                sp4C = (s32) var_t0_2;
                                spE4 = temp_f12_2;
                                spE0 = temp_f14_2;
                                var_t0_2 = (u8) sp4C;
                                if (func_1505693C(arg0, 0) != 0) {
                                    temp_v0_11 = arg0->unk229;
                                    if (temp_v0_11 == 0xFF) {
                                        var_f2_2 = sqrtf(sp164);
                                    } else {
                                        var_f6 = (f32) temp_v0_11;
                                        if ((s32) temp_v0_11 < 0) {
                                            var_f6 += 4294967296.0f;
                                        }
                                        var_f2_2 = var_f6 * 8.0f;
                                    }
                                    if ((D_800C3E78 != 0) && ((temp_v0_11 == 0) || (fabsf(arg0->y_position - *D_800CC2E8) < var_f2_2))) {
                                        if (arg0->id == 0x9E) {
                                            sp4C = (s32) var_t0_2;
                                            func_1505A184(arg0->unk7A, 9000.0f, arg0->unkB8, &sp94, &sp90, &sp8C);
                                            temp_f10 = sp94 + arg0->x_position;
                                            sp94 = temp_f10;
                                            temp_f8_2 = sp90 + arg0->z_position;
                                            sp90 = temp_f8_2;
                                            temp_f4_3 = sp8C + arg0->y_position;
                                            sp8C = temp_f4_3;
                                            func_15047680(sp98, arg0->x_position, arg0->y_position, arg0->z_position, temp_f10, temp_f4_3, temp_f8_2, 0.0f, 1.0f, 0.0f);
                                            var_t0_2 = (u8) sp4C;
                                            if (func_15049440(sp98, D_800CC704, *D_800CC2E8, D_800CC70C, 80.0f, 80.0f, 0.0f, 4000.0f, 320.0f, 320.0f) != 0) {
                                                spEB = 1;
                                            }
                                        } else {
                                            var_v1_4 = sp134->unk17;
                                            if (sp10C == 0) {
                                                var_v1_4 *= 3;
                                            }
                                            sp88 = (s32) var_v1_4;
                                            sp4C = (s32) var_t0_2;
                                            var_t0_2 = (u8) sp4C;
                                            if (((((((s32) arg0->unk7A >> 8) + arg0->unk2CA) - (func_1505A630(spE4, spE0, 0) >> 8)) + (sp88 / 2)) & 0xFF) < sp88) {
                                                spEB = 1;
                                            }
                                        }
                                    }
                                }
                            }
                            if (spEB != 0) {
                                if (sp10C == 0) {
                                    sp4C = (s32) var_t0_2;
                                    var_v0 = func_1507BB28(3, arg0->unk235);
                                    var_t0_2 = (u8) sp4C;
                                } else {
                                    sp4C = (s32) var_t0_2;
                                    var_v0 = func_1507BB28(1, arg0->unk233);
                                    var_t0_2 = (u8) sp4C;
                                }
                                arg0->unk218 = var_v0;
                                arg0->unk21C = 0;
                                arg0->unk222 = spEB - 1;
                                arg0->unkA8 = spEB + 0x7F;
                            }
                        }
                    }
                }
                if (var_t0_2 != 9) {
                    if ((var_t0_2 == 6) || (var_t0_2 == 0xC)) {
                        temp_v0_12 = &D_800CC2D0[arg0->unk222];
                        sp174 = temp_v0_12->x_position;
                        sp170 = temp_v0_12->z_position;
                        sp16C = temp_v0_12->y_position;
                    } else {
                        temp_v0_13 = D_800D2104[arg0->unk13F] + (arg0->unk21E * 8);
                        sp174 = (f32) (*(s16 *)((u8 *)temp_v0_13 + 8));
                        sp170 = (f32) (*(s16 *)((u8 *)temp_v0_13 + 0xC));
                        sp16C = (f32) (*(s16 *)((u8 *)temp_v0_13 + 0xA));
                    }
                    if ((var_t0_2 == 5) || (var_t0_2 == 6)) {
                        if ((var_t0_2 == 6) && (arg0->unk22C & 1)) {
                            arg0->unk86 = (u8) (D_800CC2D0[arg0->unk222].unk7A >> 8);
                        }
                        temp_t4 = arg0->unk258;
                        arg0->unk86 += arg0->unk257;
                        var_f8_2 = (f32) temp_t4;
                        if ((s32) temp_t4 < 0) {
                            var_f8_2 += 4294967296.0f;
                        }
                        temp_f4_4 = var_f8_2 * 16.0f;
                        sp84 = temp_f4_4;
                        sp4C = (s32) var_t0_2;
                        func_1505A184((arg0->unk86 << 8) & 0xFFFF, temp_f4_4, 0.0f, &sp84, &sp80, &sp7C);
                        var_t0_2 = (u8) sp4C;
                        sp174 += sp84;
                        sp170 += sp80;
                    }
                }
            }
            temp_f12_3 = arg0->unk44;
            sp14C = temp_f12_3;
            if ((var_t0_2 != 7) && (var_t0_2 != 8)) {
                temp_f16 = arg0->x_position;
                temp_f4_5 = sp174 - temp_f16;
                sp174 = temp_f4_5;
                temp_f18 = arg0->z_position;
                sp170 = temp_f18 - sp170;
                sp16C = arg0->y_position - sp16C;
                if ((var_t0_2 == 6) && (arg0->unk22C & 1) && ((fabsf(sp170) + fabsf(temp_f4_5)) < 100.0f)) {
                    sp14C = 0.0f;
                    sp4C = (s32) var_t0_2;
                    temp_v0_14 = &D_800CC2D0[arg0->unk222];
                    sp174 = temp_v0_14->x_position - temp_f16;
                    sp170 = temp_f18 - temp_v0_14->z_position;
                    var_v0_2 = func_1505A630(sp174, sp170, 0);
                    var_t0_2 = (u8) sp4C;
                    goto block_182;
                }
                if ((temp_f12_3 >= 0.5f) && !(arg0->unkF4 & 0x40)) {
                    sp4C = (s32) var_t0_2;
                    var_v0_2 = func_1505A630(sp174, sp170, 0);
                    var_t0_2 = (u8) sp4C;
block_182:
                    arg0->unk78 = var_v0_2;
                }
            }
            temp_t8_2 = arg0->unk247;
            var_f6_2 = (f32) temp_t8_2;
            if ((s32) temp_t8_2 < 0) {
                var_f6_2 += 4294967296.0f;
            }
            sp158 = var_f6_2 / 10.0f;
            temp_f12_4 = (sp174 * sp174) + (sp170 * sp170);
            var_f2_3 = temp_f12_4;
            if (arg0->unk22C & 8) {
                var_f2_3 = temp_f12_4 + (sp16C * sp16C);
            }
            temp_f2_2 = sqrtf(var_f2_3);
            if ((var_t0_2 != 4) && (var_t0_2 != 7) && (var_t0_2 != 8)) {
                sp78 = arg0->unk76;
                if (var_t0_2 == 2) {
                    temp_t3 = arg0->unk78 ^ 0x8000;
                    arg0->unk78 = temp_t3;
                    if (!(arg0->unkF4 & 0x4000)) {
                        arg0->unk78 = temp_t3 + (((((s32) arg0->unk21C / 100) & 0x20) - 0x10) << 8);
                    }
                }
                if (arg0->unk223 == 0x11) {
                    arg0->unk78 += ((((s32) arg0->unk21C / 100) & 0x10) - 8) << 9;
                }
                if ((arg0->unkF4 & 0x200) && (arg0->unk1F4 < 3.0f)) {
                    sp14A = 0;
                    sp149 = 0;
                }
                sp3C = temp_f12_4;
                sp144 = temp_f2_2;
                sp4C = (s32) var_t0_2;
                sp13C = (f32) (arg0->unk23E * 8);
                temp_v0_15 = func_15059B54(arg0, sp14A);
                sp153 = temp_v0_15;
                if (sp4C != 0xD) {
                    temp_v1_5 = (u8) arg0->unk24F;
                    if ((temp_v1_5 != 0) && ((sp4C != 0) || (sp13C < sp144))) {
                        temp_t9 = (temp_v1_5 - 1) & 0xFF;
                        if ((s32) *D_80099DFC[temp_t9] < (temp_v0_15 & 0xFF)) {
                            arg0->unk76 = sp78;
                            func_15056A00(arg0, (s32) sp153, temp_t9);
                        }
                    }
                }
                if (sp4C == 0xD) {
                    sp14A = 0;
                    sp149 = 0;
                }
                if (((s32) (*(u8 *)((u8 *)sp134 + 0x19)) < (s32) sp153) && (sp4C != 2)) {
                    sp14C = 0.0f;
                    temp_v0_16 = arg0->unk24A;
                    if ((temp_v0_16 != 0) && (arg0->xz_velocity > 15.0f)) {
                        arg0->unk218 = func_1507BB28(6, temp_v0_16);
                        arg0->unk21C = 0;
                        arg0->unk222 = 0;
                    }
                }
                if (((sp4C == 0) || (sp4C == 0xA)) && (sp144 < sp13C)) {
                    temp_v0_17 = arg0->unk13F;
                    temp_v1_6 = arg0->unk21F;
                    var_a2_2 = (D_800D2528[temp_v0_17] - 1) & 0xFF;
                    if (temp_v1_6 != 0) {
                        var_a2_2 = temp_v1_6 & 0xFF;
                    }
                    temp_a1 = arg0->unk22C;
                    if (temp_a1 & 4) {
                        temp_t7 = arg0->unk21E * 8;
                        arg0->x_position = (f32) (*(s16 *)((u8 *)((D_800D2104[temp_v0_17] + temp_t7)) + 8));
                        arg0->unk1FC |= 8;
                        arg0->z_position = (f32) (*(s16 *)((u8 *)((D_800D2104[temp_v0_17] + temp_t7)) + 0xC));
                        if (temp_a1 & 8) {
                            arg0->y_position = (f32) (*(s16 *)((u8 *)((D_800D2104[temp_v0_17] + temp_t7)) + 0xA));
                        }
                    }
                    if (!(arg0->unkF4 & 0x10)) {
                        arg0->unk21C = 0;
                    }
                    temp_v1_7 = arg0->unk220;
                    temp_t5 = arg0->unk21E + arg0->unk221;
                    temp_t1 = (temp_t5 & 0xFF) + var_a2_2;
                    temp_hi = (s32) (temp_t1 & 0xFF) % var_a2_2;
                    arg0->unk21E = temp_t5;
                    arg0->unk21E = temp_t1;
                    arg0->unk21E = (u8) temp_hi;
                    if ((temp_hi & 0xFF) < (s32) temp_v1_7) {
                        arg0->unk21E = temp_v1_7;
                    }
                }
                var_a2_3 = arg0->unk78;
                if (arg0->unkF4 & 0x20000) {
                    temp_v0_18 = &D_800CC2D0[arg0->unk222];
                    var_a2_3 = func_1505A630(temp_v0_18->x_position - arg0->x_position, arg0->z_position - temp_v0_18->z_position, 0) & 0xFFFF;
                }
                sp153 = func_150599C8(arg0, sp149, var_a2_3);
                temp_t1_2 = arg0->unk248;
                var_f6_3 = (f32) temp_t1_2;
                if ((s32) temp_t1_2 < 0) {
                    var_f6_3 += 4294967296.0f;
                }
                sp154 = var_f6_3 / 10.0f;
                temp_v1_8 = arg0->unk3A;
                if ((temp_v1_8 != 0) && (arg0->unk28 == 0.0f) && !(temp_v1_8 & 3 & D_800D1968)) {
                    arg0->unk84.uh = 0xFF;
                    arg0->y_velocity = (f32) temp_v1_8;
                }
                temp_v0_19 = arg0->unkF4;
                if (temp_v0_19 & 1) {
                    sp14C = 0.0f;
                }
                if ((arg0->unk22C & 0x10) && (arg0->unk28 == 0.0f)) {
                    sp14C = 0.0f;
                    sp158 = 1.0f;
                }
                if (arg0->interaction_state == 1) {
                    arg0->unk44 = sp14C;
                    return;
                }
                if (temp_v0_19 & 0x80000) {
                    temp_f0_3 = sp16C + 70.0f;
                    var_f14 = temp_f0_3;
                    if (D_800BE9F0 == 0x26) {
                        var_f14 = temp_f0_3 - (45.0f * arg0->y_scale);
                    }
                    func_1504C9E4(arg0, (s8) ((s16) func_1505A630(sqrtf(sp3C), var_f14, 0) / 200), 0);
                } else if (arg0->unk1D1 != 0) {
                    func_1504C9E4(arg0, 0, 0);
                }
                if (arg0->unkF8 & 0x40000) {
                    sp14C = arg0->unk44;
                    func_1505A184(arg0->unk78, sp14C, 0.0f, &sp68, &sp64, &sp60);
                    if ((sp14C < 1.0f) || (var_f0 = sp158, ((((sp78 - arg0->unk78) + 0x4000) & 0x8000) != 0))) {
                        var_f0 = sp154;
                    }
                    func_1505A250(sp68, sp64, var_f0, &arg0->unk174, &arg0->unk178);
                    temp_f2_3 = arg0->unk174;
                    temp_f12_5 = arg0->unk178;
                    arg0->unk76 = func_1505A630(arg0->unk174, -arg0->unk178, 0);
                    arg0->xz_velocity = 2.0f * sqrtf((temp_f2_3 * temp_f2_3) + (temp_f12_5 * temp_f12_5));
                } else {
                    func_1505A3A8(sp14C, arg0, sp158, sp154, (u8) (s32) sp153);
                }
                goto block_251;
            }
            sp3C = temp_f12_4;
            func_150599C8(arg0, arg0->unk1E6, arg0->unk78);
            arg0->unk76 = arg0->unk78;
            arg0->xz_velocity = sp14C;
block_251:
            func_1505841C(arg0, sp158);
            if ((arg0->unk22C & 8) && !(arg0->unk1FC & 8)) {
                temp_f2_4 = (f32) func_1505A630(sqrtf(sp3C), sp16C, 0) * 0.005493164f;
                var_f0_2 = temp_f2_4;
                if (temp_f2_4 > 180.0f) {
                    var_f0_2 = temp_f2_4 - 360.0f;
                }
                temp_f12_6 = arg0->unkB8;
                var_f0_3 = (var_f0_2 - temp_f12_6) * 0.25f;
                var_f8_3 = (f32) sp14A;
                if ((s32) sp14A < 0) {
                    var_f8_3 += 4294967296.0f;
                }
                temp_f2_5 = var_f8_3 * 0.005493164f;
                temp_f14_3 = -temp_f2_5;
                if (temp_f2_5 < var_f0_3) {
                    var_f0_3 = temp_f2_5;
                }
                if (var_f0_3 < temp_f14_3) {
                    var_f0_3 = temp_f14_3;
                }
                arg0->unkB8 = temp_f12_6 + var_f0_3;
            }
        }
    }
}
