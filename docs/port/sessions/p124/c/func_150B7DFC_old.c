extern s32 D_80091CBC;

s32 func_150B7DFC(void) {
    s8 sp5D;
    s8 sp5C;
    s8 sp5B;
    s8 sp5A;
    s8 sp59;
    s8 sp58;
    s8 sp57;
    s8 sp56;
    s8 sp55;
    s8 sp54;
    s16 sp52;
    s16 sp50;
    s16 sp4E;
    s16 sp4C;
    s16 sp4A;
    s16 sp48;
    f32 sp44;
    f32 sp40;
    s16 sp3C;
    s16 sp3A;
    s16 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 *sp24;
    s32 temp_v0;
    s32 temp_v0_2;

    if (D_800D9CB8[2] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[2]);
        D_800D9CB8[2] = 0;
    }
    sp55 = 3;
    sp50 = 0x40;
    sp52 = 0x10;
    sp54 = 5;
    sp48 = 0;
    sp4A = 0;
    sp38 = 0;
    sp3A = 0;
    sp3C = 0;
    sp24 = &D_80091CBC;
    sp28 = 0;
    sp2C = 0;
    sp34 = 0;
    sp56 = 0xFF;
    sp57 = 0;
    sp58 = 0;
    sp59 = 0x80;
    sp5A = 7;
    sp5B = 0x11;
    sp5C = 1;
    sp5D = 0;
    sp4C = 0x1000;
    sp4E = 0x1000;
    sp44 = 150.0f;
    sp40 = 230.0f;
    sp30 = (s32) 150.0f;
    if (D_800D9CB8[5] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[5]);
    }
    temp_v0_2 = func_15169ED8(&sp24);
    D_800D9CB8[5] = temp_v0_2;
    sp3A = 0x100;
    sp2C = 0x100;
    sp59 = 0xFF;
    sp44 = 170.0f;
    sp30 = (s32) 170.0f;
    if (D_800D9CB8[6] != 0) {
        func_1516972C((struct102 *) temp_v0_2);
    }
    D_800D9CB8[6] = func_15169ED8(&sp24);
    sp3A = 0x200;
    sp2C = 0x200;
    sp59 = 0x80;
    sp44 = 190.0f;
    sp30 = (s32) 190.0f;
    if (D_800D9CB8[7] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[5]);
    }
    D_800D9CB8[7] = func_15169ED8(&sp24);
    sp38 = 0;
    sp3A = 0;
    sp3C = 0;
    sp55 = 0;
    sp50 = 0x58;
    sp52 = 0x40;
    sp59 = 0xFF;
    sp54 = 0;
    sp24 = &D_80091C98;
    sp40 = 230.0f;
    sp44 = 170.0f;
    if (D_800D9CB8[9] != 0) {
        func_1516972C((struct102 *) D_800D9CB8[9]);
    }
    temp_v0 = func_15169ED8(&sp24);
    D_800D9CB8[9] = temp_v0;
    D_800D9CB0 = 3;
    return temp_v0;
}
