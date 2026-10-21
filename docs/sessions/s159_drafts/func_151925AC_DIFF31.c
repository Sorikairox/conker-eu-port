u8 *func_151308E4(void *, s32, s32, u8, s32);
extern u8 (*D_80090070[])(void);
extern f32 D_800A84D4;
extern f32 D_800A84D8;
typedef struct { f32 x, y, z; } V3_25AC;
typedef struct { s16 h[9]; } H12_25AC;
typedef struct {
    s32 u0;
    s32 u4;
    s16 u8;
    s16 uA;
    s32 uC;
    s32 u10;
    u8 u14[4];
    u8 u18;
    u8 u19;
    u8 u1A;
    u8 u1B;
    u8 u1C;
    u8 u1D;
    s16 u1E;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    f32 u2C;
    V3_25AC u30;
    f32 u3C;
    f32 u40;
    f32 u44;
    V3_25AC u48;
    f32 u54;
    s32 u58;
    s32 u5C;
    u8 u60;
    u8 u61;
    u8 u62;
    s8 u63;
    s8 u64;
    u8 u65;
} Blk_25AC;
typedef struct {
    f32 u0;
    u8 u4;
    u8 u5;
    u8 u6;
    u8 u7;
    f32 u8;
    f32 uC;
    f32 u10;
    H12_25AC u14;
    u8 u26;
} Tmp_25AC;

u8 *func_151925AC(V3_25AC *arg0, V3_25AC *arg1, f32 arg2, s16 arg3, u8 arg4, u8 arg5, f32 arg6, s32 arg7, f32 arg8, H12_25AC *arg9, u8 argA, u8 argB, s32 argC) {
    u8 *ret;
    s32 pad[2]; // fakematch: hole above the block
    Blk_25AC blk;
    Tmp_25AC tmp;
    s32 pad2; // fakematch: spill slot below tmp
    s32 a;

    blk.u8 = 0x4401;
    blk.u0 = 0x200005;
    blk.u4 = 0;
    blk.uC = 0;
    blk.u10 = 0;
    blk.u14[0] = 0;
    blk.u14[1] = 0;
    blk.u14[2] = 0;
    blk.u14[3] = 0xFF;
    blk.u18 = 0;
    blk.u19 = 0;
    blk.u1A = 0;
    blk.u1B = arg4;
    blk.u1C = arg5;
    blk.u30 = *arg0;
    blk.u3C = 0.0f;
    blk.u40 = 0.0f;
    blk.u44 = 0.0f;
    blk.u48 = *arg1;
    blk.u54 = arg2;
    blk.u22 = 1;
    blk.u24 = 1.0f;
    if (func_150ADA20() & 1) {
        a = 0x40;
    } else {
        a = 0;
    }
    blk.u58 = ((func_150ADA20() & 1) ? 0x80 : 0) | 0xC207 | a | 0x10000;
    blk.uA = arg3 + 0x12;
    blk.u1E = 0x12;
    blk.u20 = 0xE;
    blk.u60 = 6;
    blk.u61 = 8;
    blk.u62 = 0xF;
    blk.u63 = -1;
    blk.u64 = -1;
    blk.u65 = 3;
    tmp.u4 = func_150ADA20();
    tmp.u5 = func_150ADA20();
    blk.u1D = D_80090070[argA]();
    blk.u2C = arg6;
    blk.u28 = arg6;
    tmp.u0 = arg6;
    tmp.u6 = (func_150ADA20() % 6U) + 5;
    tmp.u7 = (func_150ADA20() % 6U) + 5;
    tmp.u8 = ((func_150ADA68() * 0.25f) + D_800A84D4) * tmp.u0;
    tmp.uC = ((func_150ADA68() * 0.25f) + D_800A84D8) * tmp.u0;
    tmp.u10 = arg8;
    tmp.u14 = *arg9;
    tmp.u26 = argA;
    ret = func_151308E4(&blk, 1, 0x28, argB, argC);
    if (ret != NULL) {
        memcpy(ret + 0xA8, &tmp, 0x28);
    }
    return ret;
}
