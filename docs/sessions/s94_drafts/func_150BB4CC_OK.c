extern f32 D_800A0244;
extern f32 D_800A0248;
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_150BB4CC(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0xC];
        f32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0xC];
    } sp;
    s32 obj;
    f32 scale;
    s16 spBE;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 temp_f2;

    spB8 = func_151423D8(arg8 - 0x40);
    spB4 = func_151423D8(arg8);
    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() % 36U) + 0x46;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 52U) + 0x5A;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (func_150ADA68() * 165.0f) + 800.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    spBE = (func_150ADA20() % 11U) - 0xC;
    spB0 = func_151423D8(spBE - 0x40);
    spAC = func_151423D8(spBE);
    temp_f2 = (func_150ADA68() * 11.0f) + 15.0f;
    sp.u7C[0] = temp_f2 * spAC * spB8;
    sp.u7C[1] = -temp_f2 * spB0;
    sp.u7C[2] = temp_f2 * spAC * spB4;
    sp.u88 = 0.0f;
    sp.u8C = 0xE05;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 2;
    sp.u97 = -1;
    sp.u52 = 0x16;
    sp.u54 = 0xB;
    sp.u56 = 1;
    sp.u58 = D_800A0244;
    scale = D_800A0248;
    obj = func_151308E4(&sp, 0, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}
