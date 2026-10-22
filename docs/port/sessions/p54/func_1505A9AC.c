//HOIST void func_15060A9C(s32 arg0, struct127 *arg1);
void func_15055C88(struct127 *);
s32 func_1507CD64(struct127 *, s32);
void func_1513783C(struct127 *, s32, s32);
extern u8 D_800CC69C;

void func_1505A9AC(struct127 *arg0, f32 arg1) {
    u8 sp6F;
    u8 sp6E;
    u8 sp63;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    f32 sp50;
    s32 sp4C;
    u8 sp4B;
    s32 sp3C;
    s32 *temp_v0_4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f2;
    f32 var_f12;
    f32 var_f2;
    f32 var_f2_2;
    s32 temp_t3;
    s32 temp_t5;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 var_a3;
    s32 var_t0;
    s32 var_t0_3;
    s32 var_t1;
    s32 var_t2;
    s32 var_v1;
    struct126 *temp_v0;
    struct126 *temp_v0_5;
    u16 temp_v0_8;
    u8 temp_a0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_6;
    u8 temp_v0_7;
    u8 temp_v0_9;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 var_t0_2;

    sp6F = 0;
    sp6E = 1;
    var_f2 = arg0->y_position - arg1;
    if (arg0->unk31C->pad4F[0] != 0) {
        if (var_f2 < 0.0f) {
            arg0->unk1CC = arg1;
            var_f2 = 0.0f;
        }
        arg0->unk28 = var_f2;
        temp_f2 = arg0->y_position - (arg0->unk118 - 34.0f);
        if (temp_f2 < 70.0f) {
            temp_f0 = arg0->y_velocity;
            if (temp_f0 < 18.0f) {
                if (temp_f0 > -25.0f) {
                    arg0->unk31C->pad4F[0] = 2;
                }
                if (temp_f2 < 0.0f) {
                    if (arg0->y_velocity < -12.0f) {
                        arg0->unk81 = 0;
                        if (arg0->y_velocity < -25.0f) {
                            arg0->y_velocity = -30.0f;
                            arg0->xz_velocity *= 0.4f;
                        }
                        arg0->y_velocity *= 0.85f;
                    }
                    arg0->gravity = -1.9f;
                    return;
                }
                if ((arg0->y_velocity > 10.0f) && (arg0->y_velocity < 25.0f)) {
                    arg0->y_velocity = 10.0f;
                }
                arg0->gravity = 2.2f;
            }
        }
    } else {
        if (arg0->unk65 != 0) {
            if (var_f2 < 0.0f) {
                arg0->unk1CC = arg1;
                var_f2 = 0.0f;
                arg0->y_position = arg1;
            }
            goto block_172;
        }
        if (var_f2 < 0.0f) {
            sp63 = 0;
            if (arg0->in_water == 0) {
                arg0->unk137 = 0;
                arg0->gravity = 5.0f;
            }
            if (arg0->in_water == 0) {
                arg0->unk31C->unk55 = 4;
            }
            if (arg0->unk28 > 0.0f) {
                arg0->unk31C->pad4F[2] = 1;
                arg0->unk31C->unk31 = 0;
            }
            arg0->unk100 &= 0xFD;
            if ((((u32) arg0->unk184 >> 0xC) & 0xF) == 1) {
                if (D_800BE9F0 == 0x14) {
                    func_1513783C(arg0, 0xFF, 1);
                    func_1507CD64(arg0, 8);
                    return;
                }
                func_15055C88(arg0);
                return;
            }
            if (D_800BE9F0 == 0x43) {
                var_f2_2 = 1000.0f;
            } else {
                var_f2_2 = 600.0f * 3.0f;
            }
            if ((arg0->unk1CC - arg0->y_position) > 600.0f) {
                temp_v0 = arg0->unk31C;
                if ((temp_v0->unk120 == 0) && (temp_v0->unk78 != 1)) {
                    var_f12 = 1.3f;
                    temp_v0->unk95 = 0;
                    var_t2 = 0;
                    arg0->unk31C->pad4F[2] = 2;
                    var_t1 = 0;
                    var_a3 = 0;
                    var_t0 = 0x30;
                    if (D_800BE9F0 != 0x29) {
                        temp_v1 = arg0->unk184;
                        if (((((u32) temp_v1 >> 0xC) & 0xF) == 2) || ((temp_v1 == 0x13) & 0x1F)) {
                            sp58 = 0xC8;
                            sp54 = 0;
                            sp5C = 0;
                            func_15060B70(0x1B8, arg0);
                            var_f12 = 1.0f;
                            var_t0 = 0xC8;
                            var_t1 = 0;
                            var_t2 = 0;
                        } else {
                            temp_v0_2 = arg0->health;
                            if (temp_v0_2 != 0) {
                                if (arg0->unk31C->unk78 == 0x21) {
                                    var_t1 = 1;
                                }
                                if (arg0->id == 0x75) {
                                    var_t1 |= 2;
                                }
                            }
                            temp_f0_2 = arg0->unk1CC;
                            if ((temp_f0_2 < 90000.0f) && (var_f2_2 < (temp_f0_2 - arg0->y_position))) {
                                if (!(var_t1 & 2)) {
                                    arg0->health = 0;
                                    if ((temp_v1 & 0x1F) != 0xE) {
                                        sp4C = 0;
                                        sp58 = 0x30;
                                        sp54 = var_t1;
                                        sp50 = 1.3f;
                                        func_1513783C(arg0, 0xFF, 1);
                                        var_a3 = 0;
                                        var_t0 = 0x30;
                                        var_f12 = 1.3f;
                                        var_t2 = 1;
                                    }
                                } else {
                                    var_a3 = 1;
                                    if (temp_v0_2 != 0) {
                                        arg0->health = temp_v0_2 - 1;
                                    }
                                }
                            }
                            if (var_t1 == 0) {
                                temp_v0_3 = arg0->health;
                                arg0->stunned = 8;
                                if (temp_v0_3 != 0) {
                                    arg0->health = temp_v0_3 - 1;
                                }
                            }
                            if (var_t1 & 1) {
                                var_f12 = 1.0f;
                                var_t0 = 0x19D;
                            } else if (var_t1 & 2) {
                                if (var_a3 != 0) {
                                    goto block_64;
                                }
                                var_t0 = 9;
                            } else if (arg0->health != 0) {
block_64:
                                var_t0 = 0x27;
                            }
                            if ((var_t0 == 0x27) && (arg0->unk31C->unk78 == 0x25)) {
                                var_t0 = 0x1AA;
                            }
                        }
                    }
                    if (var_t2 == 0) {
                        sp54 = var_t1;
                        sp5C = var_t2;
                        func_1505E650(arg0, var_t0 & 0xFFFF, var_f12, 2.0f, 6.0f, 0.0f, 0);
                    }
                    arg0->stunned = 0;
                    arg0->unk83 = 0xFF;
                    arg0->disable_run = 0xFE;
                    if (var_t1 != 0) {
                        arg0->unk228 = 0xA;
                    } else {
                        arg0->unk228 = 0x1E;
                    }
                    arg0->unk28 = 0.0f;
                    arg0->unk100 &= 0x8B;
                    arg0->unk76 = arg0->unk7A;
                    arg0->unkA9 = 0;
                    arg0->y_position = arg1;
                    arg0->y_velocity = -4.0f;
                    arg0->unk1CC = arg1;
                    if (var_t2 == 0) {
                        func_15174690((s32) D_800C3E78, 0, 0x1F, 0, 0x199, 4, 0xAA, 0xFFU, 0);
                        return;
                    }
                    func_1507CD64(arg0, 8);
                    return;
                }
            }
            arg0->unk1CC = arg1;
            if (arg0->in_water != 0) {
                arg0->unk28 = 0.0f;
                arg0->y_position = arg1;
                return;
            }
            if (arg0->stunned == 0) {
                if ((arg0->unk7F == 0) && (arg0->xz_velocity < 9.0f)) {
                    arg0->unk76 = arg0->unk7A;
                }
                temp_t5 = ((s32) (arg0->unk76 - arg0->unk7A) >> 8) & 0xFF;
                var_v1 = temp_t5;
                if (temp_t5 >= 0x81) {
                    var_v1 = -temp_t5 & 0xFF;
                }
                if ((arg0->unk7F == 0) && (var_v1 < 0x50)) {
                    arg0->unk7F = 0xA;
                }
                if (arg0->unkA9 == 2) {
                    temp_v1_2 = arg0->unk274;
                    var_t0_2 = 0;
                    if (temp_v1_2 != 0) {
                        temp_v0_4 = &(*(s32 *)((u8 *)(&D_800CC2D0[temp_v1_2]) + -0x32C));
                        temp_a0 = (*(u8 *)((u8 *)temp_v0_4 + 0x24C));
                        if (temp_a0 != 0) {
                            var_t0_2 = 1;
                            (*(s32 *)((u8 *)temp_v0_4 + 0x218)) = 0;
                            (*(u8 *)((u8 *)temp_v0_4 + 0x232)) = temp_a0;
                        }
                    }
                    arg0->xz_velocity = 0.0f;
                    arg0->unk83 = 0xFF;
                    sp63 = 0xFF;
                    sp4B = var_t0_2;
                    func_1505E650(arg0, 0x4BU, 1.0f, 2.0f, 0.0f, 0.0f, 0);
                    if ((s32) D_800C3E78 < 4) {
                        arg0->unk31C->unk57 = 1;
                    }
                    if (var_t0_2 == 0) {
                        func_15060A9C(0x19, arg0);
                    }
                } else {
                    var_t0_3 = 0;
                    if ((s32) arg0->unk28 > 0) {
                        temp_v0_5 = arg0->unk31C;
                        temp_v1_3 = temp_v0_5->unk11A;
                        if ((temp_v1_3 != 1) && (temp_v1_3 != 3) && (temp_v0_5->unk4E == 0) && ((temp_v0_6 = arg0->unk100, temp_v1_4 = temp_v0_6 & 0x10, (temp_v1_4 != 0)) || (!(temp_v0_6 & 8) && (((arg0->unk44 == 0.0f) && (arg0->unkA8 == 0)) || (temp_v0_6 & 4))))) {
                            if (temp_v1_4 != 0) {
                                arg0->unk83 = 8;
                                if (!(temp_v0_6 & 0x40)) {
                                    arg0->xz_velocity = 0.0f;
                                    arg0->unk83 = 0xD;
                                    sp63 = 5;
                                }
                            } else if (temp_v0_6 & 4) {
                                arg0->unk83 = 0x14;
                                arg0->xz_velocity *= 0.7f;
                            } else {
                                arg0->xz_velocity = 0.0f;
                                arg0->unk83 = 0x10;
                            }
                            temp_v0_7 = arg0->unk31C->unk78;
                            if (temp_v0_7 == 0x21) {
                                var_t0_3 = 0x19D;
                            } else {
                                var_t0_3 = 0x36;
                                if (temp_v0_7 == 0x25) {
                                    var_t0_3 = 0xD8;
                                }
                            }
                        }
                    }
                    temp_v0_8 = arg0->unk84.uh;
                    if ((temp_v0_8 == 0x3B) || (temp_v0_8 == 0x3C)) {
                        sp63 = 0xFE;
                        sp6E = 0;
                        temp_t3 = arg0->unk184 & 0x1F;
                        arg0->unk83 = 0xFF;
                        if ((temp_t3 == 0xA) || (temp_t3 == 0xB) || (temp_t3 == 0xC) || (temp_t3 == 0xF) || (temp_t3 == 0x13)) {
                            sp3C = 0xC8;
                            func_15060B70(0x1B8, arg0);
                        } else if ((temp_t3 == 1) || (temp_t3 == 2) || (temp_t3 == 7) || (temp_t3 == 0x11)) {
                            sp3C = 0xC8;
                            func_15060B70(0xA7, arg0);
                        } else {
                            sp3C = 0x27;
                            func_15060B70(0xA7, arg0);
                        }
                        var_t0_3 = sp3C;
                    }
                    if ((var_t0_3 != 0) && !(arg0->unk100 & 0x20)) {
                        func_1505E650(arg0, var_t0_3 & 0xFFFF, 1.0f, 2.0f, 0.0f, 0.0f, 0);
                    }
                    if (!(arg0->unk100 & 0x80)) {
                        arg0->unk100 = 1;
                    }
                    if (sp6E == 0) {
                        arg0->unk100 = 0x90;
                    }
                }
                if ((arg0->unk28 > 0.0f) && !(arg0->unk100 & 8)) {
                    if (D_800CC69C != 0) {
                        if (arg0->xz_velocity > 20.0f) {
                            arg0->xz_velocity = 20.0f;
                        }
                    } else if (arg0->unk110 == 0) {
                        arg0->unk164 = 0.0f;
                        arg0->unk168 = 0.0f;
                    }
                    arg0->disable_run = sp63;
                    if ((arg0->unk31C->unk4E == 1) && (arg0->y_velocity < -10.0f)) {
                        sp6F = 2;
                    }
                }
                arg0->unkA9 = 0;
            }
            if (!(arg0->unk100 & 8)) {
                var_f2 = 0.0f;
            } else {
                var_f2 = 0.1f;
            }
            arg0->y_position = arg1;
            if ((arg0->stunned == 0) && !(sp6F & 2)) {
                arg0->y_velocity = -4.0f;
            } else {
                if (arg0->unkF4 & 0x80) {
                    arg0->y_velocity = -20.0f;
                } else {
                    temp_f0_3 = arg0->y_velocity;
                    if (temp_f0_3 > -10.0f) {
                        arg0->y_velocity = 0.0f;
                    } else {
                        arg0->y_velocity = temp_f0_3 * -0.5f;
                        if (arg0->y_velocity > 28.0f) {
                            arg0->y_velocity = 28.0f;
                        }
                    }
                }
                if (arg0->unk109 != 0) {
                    arg0->xz_velocity *= 0.6f;
                }
            }
            temp_v0_9 = arg0->unk7F;
            arg0->unk81 = 0;
            if ((s32) temp_v0_9 < 0xFA) {
                arg0->unk7F = temp_v0_9 + 1;
            }
            arg0->unk100 &= 0x9F;
            goto block_168;
        }
        if ((var_f2 < 1.0f) && (arg0->unk28 > 0.0f)) {
            var_f2 = 1.0f;
        }
block_168:
        if (var_f2 > 20.0f) {
            arg0->unk7F = 0;
        }
        if (arg0->in_water != 0) {
            arg0->unk1CC = arg0->y_position;
        }
block_172:
        arg0->unk28 = var_f2;
    }
}
