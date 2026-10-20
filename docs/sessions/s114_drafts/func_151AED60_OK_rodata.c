typedef struct {
    s32 u24;
    s32 u28;
    u8 u2C;
    u8 *u30;
    s8 u34;
    f32 u38;
    f32 u3C;
    f32 u40;
    f32 u44;
    f32 u48;
    s16 u4C;
    s8 u4E;
    s8 u4F;
    s8 u50;
    s8 u51;
} SpawnAED60;
s32 func_151AED60(u8 *arg0, f32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    s32 pad;
    SpawnAED60 sp;
    s16 *p2;

    if (arg0 == NULL) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x11);
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = arg0[0x3B];
    sp.u34 = 1;
    sp.u4E = 2;
    sp.u30 = arg0;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    if (arg0) {} // fakematch: with p2 below, puts arg2 in v0
    sp.u40 = 0.0f;
    sp.u44 = 15.400001f;
    sp.u48 = arg1;
    p2 = &arg2; // fakematch: address-taken arg2 (loaded into v0 from its home slot)
    if (*p2 != 0) {
        sp.u4C = *p2;
        sp.u4E = 6;
    } else {
        sp.u4C = 0x12C;
    }
    sp.u4F = 6;
    sp.u50 = -1;
    sp.u51 = 5;
    return func_1513418C(&sp, 0, arg3, arg4);
}
