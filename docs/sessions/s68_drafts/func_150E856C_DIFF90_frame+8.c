

void func_150E856C(f32 arg0, s32 arg1, s32 arg2, f32 *arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, s32 argB) {
    s32 f1;
    struct {
        s32 u5C;
        s16 u60;
        u8 u62;
        u8 u63;
        s32 u64;
        s32 u68;
        u8 u6C;
        u8 u6D;
        u8 u6E;
        u8 u6F;
        u8 u70;
        u8 u71;
        u8 u72;
        u8 u73;
        s32 u74;
        u8 pad78[6];
        s16 u7E;
        s16 u80;
    } sp;
    s32 t58;
    s32 t54;
    s32 f3;
    s32 r2;
    s32 r1;

    sp.u7E = 0x14;
    sp.u80 = 0xC;
    sp.u62 = 0x4F;
    sp.u63 = 0;
    if (arg4 == -1) {
        f1 = 0;
    } else {
        f1 = 1;
    }


    sp.u5C = f1 | ((arg5 != 0) ? 0x400 : 0) | 0x9300 | 0x40000;
    if (arg4 == -1) {
        sp.u60 = 0x12C;
    } else {
        sp.u60 = arg4 + 0x14;
    }
    sp.u64 = 0;
    sp.u68 = 0;
    sp.u6C = arg1;
    sp.u6D = 0xFF;
    sp.u6E = arg7;
    sp.u6F = arg8;
    sp.u70 = arg9;
    sp.u71 = 0xFF;
    if (arg6 != 0) {
        f3 = 2;
    } else {
        f3 = 1;
    }

    sp.u72 = 0;
    sp.u73 = 6;
    sp.u74 = f3 + 0x480000;
    if (arg5 != 0) {
        t58 = 3;
        t54 = 0xFF;
    } else {
        t58 = 0;
        t54 = 0;
    }
    r1 = func_150ADA20();
    r2 = func_150ADA20();
    func_1513C650((s32) &sp.u5C, 0, 0, arg2, arg3[0], arg3[1], arg3[2], arg0, arg0, r1 & 0xFF, ((func_150ADA20() & 1) * 2) + (r2 & 1), t58, t54, 0, argA, argB);
}
