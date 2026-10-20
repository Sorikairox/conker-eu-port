s32 func_151308E4(void *, s32, s32, u8, s32);
extern u8 (*D_80090070[])(void);
typedef struct {
    f32 x, y, z;
} V3_25AC;
typedef struct {
    s16 v[9];
} S18_25AC;
s32 func_151925AC(V3_25AC *arg0, V3_25AC *arg1, f32 arg2, s16 arg3, u8 arg4, u8 arg5, f32 arg6, s32 arg7, f32 arg8, S18_25AC *arg9, u8 argA, u8 argB, s32 argC) {
    s32 obj;
    struct {
        s32 u54;
        s32 u58;
        s16 u5C;
        s16 u5E;
        s32 u60;
        s32 u64;
        u8 u68;
        u8 u69;
        u8 u6A;
        u8 u6B;
        u8 u6C;
        u8 u6D;
        u8 u6E;
        u8 u6F;
        u8 u70;
        u8 u71;
        s16 u72;
        s16 u74;
        s16 u76;
        f32 u78;
        f32 u7C;
        f32 u80;
        V3_25AC u84;
        f32 u90[3];
        V3_25AC u9C;
        f32 uA8;
        s32 uAC;
        u8 padB0[4];
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        u8 padBA[0xA];
    } sp;
    struct {
        f32 u2C;
        u8 u30;
        u8 u31;
        u8 u32;
        u8 u33;
        f32 u34;
        f32 u38;
        f32 u3C;
        S18_25AC u40;
        u8 u52;
    } info;
    s32 pad; // fakematch: spill slot
    s32 a;
    s32 b;

    sp.u5C = 0x4401;
    sp.u54 = 0x200005;
    sp.u58 = 0;
    sp.u60 = 0;
    sp.u64 = 0;
    sp.u68 = 0;
    sp.u69 = 0;
    sp.u6A = 0;
    sp.u6B = 0xFF;
    sp.u6C = 0;
    sp.u6D = 0;
    sp.u6E = 0;
    sp.u6F = arg4;
    sp.u70 = arg5;
    sp.u84 = *arg0;
    sp.u90[0] = 0.0f;
    sp.u90[1] = 0.0f;
    sp.u90[2] = 0.0f;
    sp.u9C = *arg1;
    sp.uA8 = arg2;
    sp.u76 = 1;
    sp.u78 = 1.0f;
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
    sp.uAC = b | 0xC207 | a | 0x10000;
    sp.u5E = arg3 + 0x12;
    sp.u72 = 0x12;
    sp.u74 = 0xE;
    sp.uB4 = 6;
    sp.uB5 = 8;
    sp.uB6 = 0xF;
    sp.uB7 = -1;
    sp.uB8 = -1;
    sp.uB9 = 3;
    info.u30 = func_150ADA20();
    info.u31 = func_150ADA20();
    sp.u71 = D_80090070[(u64)argA]();
    info.u2C = sp.u7C = sp.u80 = arg6;
    info.u32 = (func_150ADA20() % 6U) + 5;
    info.u33 = (func_150ADA20() % 6U) + 5;
    info.u34 = ((func_150ADA68() * 0.25f) + 0.2f) * info.u2C;
    info.u38 = ((func_150ADA68() * 0.25f) + 0.2f) * info.u2C;
    info.u3C = arg8;
    info.u40 = *arg9;
    info.u52 = argA;
    obj = func_151308E4(&sp, 1, 0x28, argB, argC);
    if (obj != 0) {
        memcpy(obj + 0xA8, &info, 0x28);
    }
    return obj;
}
