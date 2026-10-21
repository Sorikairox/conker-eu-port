s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
void *memcpy(void *, const void *, s32);
extern f32 D_800AA810;
typedef struct { f32 x, y, z; } V3_61A0;
typedef struct {
    f32 u0;
    f32 u4;
    f32 u8;
    f32 uC;
    V3_61A0 u10;
    f32 u1C[3];
    V3_61A0 u28;
    V3_61A0 u34;
    V3_61A0 u40;
    f32 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
    u8 u58;
    s32 u5C;
    u8 u60;
    u8 u61;
    u8 u62;
    u8 u63;
    u8 u64;
    u8 u65;
    u8 u66;
    u8 u67;
    u8 u68;
    u8 u6A;
    s32 u6C;
    u8 u70;
    s16 u72;
    s16 u74;
    s32 u78;
} Blk78_61A0;

u8 *func_151B61A0(V3_61A0 *arg0, V3_61A0 *arg1, f32 arg2, V3_61A0 *arg3, V3_61A0 *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, u8 argA, u8 argB, u8 argC, s32 argD) {
    u8 *ret;
    Blk78_61A0 blk;
    f32 tmp[2];
    s32 sh;
    s32 sum;
    s32 *p;

    tmp[0] = 0.0f;
    tmp[1] = arg2;
    blk.u0 = D_800AA810 * arg2;
    blk.u4 = arg9;
    blk.u8 = arg2;
    blk.uC = arg2;
    blk.u10 = *arg3;
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.u28 = *arg0;
    blk.u4C = arg5;
    blk.u50 = 0xB908;
    if (arg6 == -1) {
        blk.u54 = 0x12C;
        sh = 0x100 >> argA;
    } else {
        blk.u50 = 0xB988;
        sh = 0x100 >> argA;
        blk.u54 = arg6 + sh;
    }
    if (arg1 != NULL) {
        blk.u34 = *arg1;
        blk.u50 |= 0x20;
    } else {
        blk.u34.x = 0.0f;
        blk.u34.y = 0.0f;
        blk.u34.z = 0.0f;
    }
    sum = 0;
    for (p = (s32 *)func_15002FB4; p < (s32 *)func_1500310C; p++) {
        sum = (sum + *p) * 2;
    }
    if (sum != 0x648AD760) {
        D_8008FDA8 = -1;
    }
    if (arg4 != NULL) {
        blk.u40 = *arg4;
        blk.u50 |= 0x40;
    } else {
        blk.u40.x = 0.0f;
        blk.u40.y = 0.0f;
        blk.u40.z = 0.0f;
    }
    if (argB != 0) {
        blk.u50 |= 1;
    }
    blk.u56 = 2;
    blk.u58 = 0;
    blk.u5C = 0;
    blk.u60 = arg7;
    blk.u61 = 5;
    blk.u62 = 0;
    blk.u63 = 6;
    blk.u64 = 0;
    blk.u65 = 0;
    blk.u66 = 2;
    blk.u67 = 0;
    blk.u68 = 2;
    blk.u6A = 0;
    blk.u6C = 0;
    blk.u70 = 0;
    blk.u72 = sh;
    blk.u74 = 0xFF / sh;
    ret = (u8 *)func_15132FBC(&blk, 3, 0xFF, 8, argC, argD);
    if (ret != NULL) {
        memcpy(ret + 0x170, tmp, 8);
    }
    return ret;
}
