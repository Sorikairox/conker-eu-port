extern s32 D_80091C98;

// hud_counter_box_open: replaces HUD box slot `slot` of D_800D9CB8 (the old one is removed with func_1516972C) by a
// new type-6 box effect (func_15169ED8) using the D_80091C98 graphics, `width` wide and 170 high (0x51 / 0x51
// offsets, 0x58 / 0x40 size, colour 0xFF / 0 / 0 / 0xFF, flags 7 / 0x15 / 1).
void func_150B7B9C(s32 width, s32 slot) {
    EffectTemplateE48B0 sp;
    s32 *box;

    sp.u30 = 6;
    sp.u2E = 0x40;
    box = &D_800D9CB8[slot];
    sp.u31 = 1;
    sp.u2C = 0x58;
    sp.u1C = width;
    sp.u14 = 0;
    sp.u16 = 0;
    sp.u18 = 0;
    sp.u0 = &D_80091C98;
    sp.u32 = 0xFF;
    sp.u33 = 0;
    sp.u34 = 0;
    sp.u35 = 0xFF;
    sp.u24 = 0;
    sp.u26 = 0;
    sp.u39 = 0;
    sp.u36 = 7;
    sp.u37 = 0x15;
    sp.u38 = 1;
    sp.u28 = 0x51;
    sp.u2A = 0x51;
    sp.u20 = 170.0f;
    if (*box != 0) {
        func_1516972C((struct102 *)*box);
    }
    *box = (s32)func_15169ED8(&sp);
}
