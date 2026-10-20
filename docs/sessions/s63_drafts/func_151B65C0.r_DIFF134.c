typedef struct { f32 x, y, z; } V3;

s32 func_151B65C0(u8 *arg0, u8 *arg1, f32 arg2, u8 *arg3, u8 *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, u8 argA, u8 argB, u8 argC, s32 argD) {
    struct {
        f32 u28[6];
        s32 u40;
        u8 pad44[0x8];
        f32 u4C;
        f32 u50;
        f32 u54;
        s32 u58;
        u8 pad5C[0x8];
        s32 u64;
        f32 u68;
        f32 u6C;
        s32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        s32 u80;
        s16 u84;
        s16 u86;
        s8 u88;
        u8 pad89[0x3];
        s32 u8C;
        u8 u90;
        s8 u91;
        s8 u92;
        s8 u93;
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        u8 pad99[0x1];
        s8 u9A;
        u8 pad9B[0x1];
        s32 u9C;
        s8 uA0;
        u8 padA1[0x1];
        s16 uA2;
        s16 uA4;
        u8 padA6[0x6];
        s32 uAC;
    } sp;
    s32 var_v1;

    sp.u28[1] = arg2;
    sp.u28[0] = 0.0f;
    sp.u28[5] = arg2;
    sp.u28[4] = arg2;
    sp.u28[3] = arg9;
    sp.u28[2] = 8.1f * arg2;
    *(V3 *)&sp.u40 = *(V3 *)arg3;
    sp.u4C = 1.0f;
    sp.u50 = 1.0f;
    sp.u54 = 1.0f;
    *(V3 *)&sp.u58 = *(V3 *)arg0;
    sp.u80 = 0x3900;
    sp.u7C = arg5;
    if (arg6 == -1) {
        sp.u84 = 0x12C;
        arg8 = 0x100 >> argA; // fakematch: arg8 slot reused
    } else {
        sp.u80 = 0x3980;
        arg8 = 0x100 >> argA; // fakematch: arg8 slot reused
        sp.u84 = arg6 + arg8;
    }
    if (arg1 != NULL) {
        (*(s32 *)((u8 *)(&sp.u64) + 0)) = (*(s32 *)((u8 *)arg1 + 0));
        (*(s32 *)((u8 *)(&sp.u64) + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
        (*(s32 *)((u8 *)(&sp.u64) + 8)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
        sp.u80 |= 0x20;
    } else {
        sp.u64 = 0;
        sp.u68 = 0.0f;
        sp.u6C = 0.0f;
    }
    if (arg4 != NULL) {
        (*(s32 *)((u8 *)(&sp.u70) + 0)) = (*(s32 *)((u8 *)arg4 + 0));
        (*(s32 *)((u8 *)(&sp.u70) + 4)) = (s32) (*(s32 *)((u8 *)arg4 + 4));
        (*(s32 *)((u8 *)(&sp.u70) + 8)) = (s32) (*(s32 *)((u8 *)arg4 + 8));
        sp.u80 |= 0x40;
    } else {
        sp.u70 = 0;
        sp.u74 = 0.0f;
        sp.u78 = 0.0f;
    }
    if (argB != 0) {
        sp.u80 |= 1;
    }
    sp.u86 = 3;
    sp.u88 = 0;
    sp.u8C = 0;
    sp.u91 = 6;
    sp.u92 = 0;
    sp.u93 = 6;
    sp.u94 = 0;
    sp.u95 = 0;
    sp.u96 = 0;
    sp.u97 = 0;
    sp.u98 = 2;
    sp.u9A = 0;
    sp.u9C = 0;
    sp.uA0 = 0;
    sp.uA2 = (s16) arg8;
    sp.uA4 = (s16) (0xFF / arg8);
    sp.u90 = arg7;
    var_v1 = func_15132FBC((u8 *)&sp.u28[2], 3, 0xFF, 8, (s32) argC, argD);
    if (var_v1 != 0) {
        sp.uAC = var_v1;
        memcpy(var_v1 + 0x170, &sp, 8);
        var_v1 = sp.uAC;
    }
    return var_v1;
}
