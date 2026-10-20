extern f32 D_800A1F40;
s32 func_15134DAC(void *, s32, u8 *, s16);

void func_150F6E10(u8 *arg0, s16 arg1, f32 arg2, u8 arg3) {
    struct {
        u8 u2C;
        u8 *u30;
        u8 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        u8 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        u8 u5A;
        u8 u5B;
        s8 u5C;
        f32 u60;
        u8 u64;
        s8 u65;
    } sp;

    sp.u2C = arg0[0x3B];
    sp.u30 = arg0;
    sp.u34 = 3;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    sp.u40 = 0.0f;
    sp.u44 = 0.0f;
    sp.u50 = 2;
    sp.u52 = 0x28;
    sp.u54 = 0x10;
    sp.u56 = arg1;
    sp.u5A = 5;
    sp.u5B = 8;
    sp.u5C = -1;
    sp.u64 = 0;
    sp.u65 = -1;
    sp.u58 = 0;
    sp.u48 = D_800A1F40;
    sp.u4C = 8.5f;
    sp.u60 = 1.0f;
    func_15134DAC(&sp, 0, arg0, arg1);
}
