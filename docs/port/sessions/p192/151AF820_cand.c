// obj_steam_puff_spawn: plays sound 0x16 on the object (func_1516962C) and spawns a 9.8 / 0.143 effect of type 1
// attached to it (func_1513418C: life 0x140, flags 6 / 10 / -1 / 9) with arg1 / arg2 passed through; NULL object: 0.
s32 func_151AF820(u8 *obj, u8 arg1, s32 arg2) {
    SpawnAED60 sp;

    if (obj == NULL) {
        return 0;
    }
    func_1516962C(0x28, obj, 0x16);
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = obj[0x3B];
    sp.u30 = obj;
    sp.u34 = 1;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    sp.u40 = 0.0f;
    sp.u44 = 9.8f;
    sp.u48 = 0.143f;
    sp.u4C = 0x140;
    sp.u4E = 6;
    sp.u4F = 10;
    sp.u50 = -1;
    sp.u51 = 9;
    return func_1513418C(&sp, 0, arg1, arg2);
}
