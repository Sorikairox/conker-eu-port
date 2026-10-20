u8 *func_151B5590(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: frame slot
    Spawn5280 sp;

    if (arg0 == NULL) {
        return 0;
    }
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = arg0[0x3B];
    sp.u34 = 2;
    sp.u30 = arg0;
    sp.u38 = 0.0f;
    sp.u3C = -27.0f;
    sp.u40 = 16.0f;
    sp.u44 = 9.8f;
    sp.u48 = 0.143f;
    sp.u4E = 2;
    sp.u4C = 0x12C;
    sp.u4F = 9;
    sp.u50 = -1;
    sp.u51 = 8;
    return func_1513418C(&sp, 0, arg1, arg2);
}
