s32 func_151308E4(void *, s32, s32, u8, s32);
typedef struct {
    f32 x, y, z;
} V3_2C9C;
s32 func_151A2C9C(V3_2C9C *arg0, V3_2C9C *arg1, V3_2C9C *arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, s16 arg8, s16 arg9, s16 argA, s8 argB, u8 argC, u8 argD, u8 argE, u8 argF, s32 arg10) {
    struct {
        f32 u9C;
        s16 uA0;
        s16 uA2;
        s16 uA4;
        s8 uA6;
    } x;
    s32 obj;
    struct {
        s32 u28;
        s32 u2C;
        s16 u30;
        s16 u32;
        s32 u34;
        s32 u38;
        u8 u3C;
        u8 u3D;
        u8 u3E;
        u8 u3F;
        u8 u40;
        u8 u41;
        u8 u42;
        u8 u43;
        u8 u44;
        s8 u45;
        s16 u46;
        s16 u48;
        s16 u4A;
        f32 u4C;
        f32 u50;
        f32 u54;
        V3_2C9C u58;
        V3_2C9C u64;
        V3_2C9C u70;
        f32 u7C;
        s32 u80;
        u8 pad84[4];
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        u8 pad8E[0xA];
    } sp;
    s32 a;
    s32 b;

    if (arg8 <= 0) {
        arg8 = 1;
    }
    if (arg9 <= 0) {
        arg9 = 1;
    }
    sp.u30 = 0x5203;
    sp.u45 = 0x27;
    sp.u28 = 0x200005;
    x.uA4 = argA;
    x.uA6 = argB;
    x.u9C = arg3;
    x.uA0 = arg9;
    x.uA2 = 0xFF / arg9;
    sp.u46 = arg8;
    sp.u48 = 0xFF / arg8;
    sp.u2C = 0;
    sp.u34 = 0;
    sp.u38 = 0;
    sp.u3F = 0xFF;
    sp.u40 = 0xFF;
    sp.u41 = 0xFF;
    sp.u42 = 0xFF;
    sp.u44 = 0xFF;
    sp.u50 = sp.u54 = arg5;
    sp.u32 = arg6;
    sp.u3C = argC;
    sp.u3D = argD;
    sp.u3E = argE;
    sp.u43 = arg7;
    sp.u58 = *arg0;
    sp.u64 = *arg1;
    sp.u70 = *arg2;
    sp.u4A = 1;
    sp.u7C = arg4;
    sp.u4C = 1.0f;
    if (func_150ADA20() & 1) {
        a = 0x40;
    } else {
        a = 0;
    }
    if (func_150ADA20() & 1) {
        b = 0x80;
    } else {
        b = 0;
    }
    sp.u80 = b | 7 | a | 0xD200 | 0x800000;
    sp.u88 = 7;
    sp.u89 = 2;
    sp.u8A = 0x11;
    sp.u8B = -1;
    sp.u8C = -1;
    sp.u8D = 2;
    obj = func_151308E4(&sp, 1, 0x10, argF, arg10);
    if (obj != 0) {
        memcpy(obj + 0xA8, &x, 8);
        memcpy(obj + 0xB0, &x.uA0, 8);
    }
    return 0;
}
