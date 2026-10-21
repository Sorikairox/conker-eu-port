extern f32 D_800AA1AC;
extern f32 D_800AA1B0;
s32 func_151AF820(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad;
    SpawnAED60 sp;

    if (arg0 == NULL) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x16);
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = arg0[0x3B];
    sp.u34 = 1;
    sp.u4E = 6;
    sp.u4C = 0x140;
    sp.u4F = 0xA;
    sp.u50 = -1;
    sp.u51 = 9;
    sp.u30 = arg0;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    sp.u40 = 0.0f;
    sp.u44 = D_800AA1AC;
    sp.u48 = D_800AA1B0;
    return func_1513418C(&sp, 0, arg1, arg2);
}
