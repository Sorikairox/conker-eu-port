s32 func_1510E908(s32, s32, f32 *, f32 *);
s32 func_1513D6FC(struct211 *arg0, s16 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    f32 spBC;
    f32 spB8;
    f32 spB4;
    s32 spB0;
    f32 spAC;
    s32 spA8;
    f32 spA4;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    s32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54; // ?
    s32 sp50; // ?
    s32 sp4C; // ?
    s32 sp48; // ?
    s32 sp44; // ?
    s32 sp40; // ?
    s32 sp3C; // ?
    s32 sp38; // ?
    s32 sp34; // ?
    s32 sp30; // ?
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f18;
    f32 phi_f12;
    f32 phi_f14;
    f32 phi_f12_2;

    if (arg6 != 0) {
        spB4 = func_151423D8(arg1 - 64);
        temp_f0 = func_151423D8(arg1);
        spAC = arg2 * temp_f0;
        spA4 = arg3 * temp_f0;
        if (func_1510E908(arg4, arg5, &spBC, &spB8) == 0) {
            return 0;
        }
        temp_f18 = spA4 * spB8;
        sp2C = fabsf(spA4);
        temp_f16 = arg3 * spB4;
        sp28 = sqrtf((spA4 * spA4) + (temp_f18 * temp_f18));
        if (temp_f16 != 0.0f) {
            sp8C = temp_f16 * spBC;
            sp88 = fabsf(temp_f16) / sqrtf((temp_f16 * temp_f16) + (sp8C * sp8C));
        } else {
            sp8C = 0.0f;
            sp88 = 0.0f;
        }
        if (spA4 != 0.0f) {
            sp84 = temp_f18;
            phi_f12 = sp2C / sp28;
        } else {
            sp84 = 0.0f;
            phi_f12 = 0.0f;
        }
        arg0->unk0 = sp88 * temp_f16;
        arg0->unk8 = phi_f12 * spA4;
        arg0->unk4 = (sp88 * sp8C) + (phi_f12 * sp84) + 0.5f;
        temp_f18 = -(arg2 * spB4);
        temp_f16 = temp_f18 * spB8;
        sp28 = fabsf(temp_f18);
        sp2C = temp_f16;
        sp24 = sqrtf((temp_f18 * temp_f18) + (temp_f16 * temp_f16));
        if (spAC != 0.0f) {
            temp_f0 = spAC * spBC;
            sp8C = temp_f0;
            phi_f14 = fabsf(spAC) / sqrtf((spAC * spAC) + (temp_f0 * temp_f0));
        } else {
            sp8C = 0.0f;
            sp88 = 0.0f;
            phi_f14 = 0.0f;
        }
        if (temp_f18 != 0.0f) {
            sp84 = sp2C;
            phi_f12_2 = sp28 / sp24;
        } else {
            sp84 = 0.0f;
            phi_f12_2 = 0.0f;
        }
        arg0->unkC = phi_f14 * spAC;
        arg0->unk14 = phi_f12_2 * temp_f18;
        arg0->unk10 = (phi_f14 * sp8C) + (phi_f12_2 * sp84) + 0.5f;
    } else {
        sp7C = func_151423D8(arg1 - 64);
        sp78 = func_151423D8(arg1);
        if (func_15144E80(arg5, &sp6C, &sp60, &sp54) == 0) {
            return 0;
        }
        if (func_15145128(&sp6C, &sp6C, &sp50, &sp4C) == 0) {
            return 0;
        }
        if (func_15145128(&sp60, &sp60, &sp50, &sp4C) == 0) {
            return 0;
        }
        temp_f0 = arg2 * sp78;
        temp_f18 = arg2 * sp7C;
        arg0->unk0 = (temp_f0 * sp6C) + (temp_f18 * sp60);
        arg0->unk4 = (temp_f0 * sp70) + (temp_f18 * sp64);
        arg0->unk8 = (temp_f0 * sp74) + (temp_f18 * sp68);
        temp_f0 = -arg3 * sp7C;
        temp_f18 = arg3 * sp78;
        arg0->unkC = (temp_f0 * sp6C) + (temp_f18 * sp60);
        arg0->unk10 = (temp_f0 * sp70) + (temp_f18 * sp64);
        arg0->unk14 = (temp_f0 * sp74) + (temp_f18 * sp68);
    }
    return 1;
}
