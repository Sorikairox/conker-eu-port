s32 func_1500F240(f32 arg0, f32 arg1, f32 arg2) {
    struct {
        s32 u48;
        s16 u4C;
        s8 u4E;
        u8 pad4F[0x1];
        s32 u50;
        s32 u54;
        s8 u58;
        s8 u59;
        s8 u5A;
        s8 u5B;
        s8 u5C;
        s8 u5D;
        u8 pad5E[0x2];
        s32 u60;
    } sp;

    sp.u4E = 0x38;
    sp.u50 = 0;
    sp.u54 = (func_151EFDD0() % 4096) + 0x4000;
    sp.u48 = 0x20014;
    sp.u4C = 1;
    sp.u58 = 0xFF;
    sp.u59 = 0xFF;
    sp.u5A = 0;
    sp.u5B = 0;
    sp.u5C = 0;
    sp.u5D = 0xFF;
    sp.u60 = 0x30001;
    return func_1513C5B0((s32) &sp.u48, 0, 0U, 0U, arg0, arg1, arg2, 110.0f, 110.0f, 0U, 0U, 0, 0xFFU, 0);
}
