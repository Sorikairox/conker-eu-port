void *memcpy(void *, const void *, s32);
extern f32 D_800A90B4;
typedef struct { f32 x, y, z; } V3_1519F0FC;

typedef struct {
    f32 u0;
    f32 u4;
    f32 u8;
    f32 uC;
    f32 u10[3];
    f32 u1C[3];
    f32 u28[3];
    V3_1519F0FC u34;
    V3_1519F0FC u40;
    f32 u4C;
    s32 u50;
    s16 u54;
    u16 u56;
    s8 u58;
    s32 u5C;
    u8 u60;
    s8 u61;
    s8 u62[6];
    s8 u68;
    s8 u6A_pad;
    s8 u6A;
    s32 u6C;
    s8 u70;
    s16 u72;
    s16 u74;
    s32 u78;
} Blk7C;

void func_1519F0FC(u8 *arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4) {
    Blk7C blk;
    u8 *tmp;
    u8 *temp_v0;

    tmp = arg0;
    blk.u0 = 1.0f;
    blk.u4 = 1.0f;
    blk.u8 = *(f32 *)(arg0 + 0x18) * D_800A90B4;
    blk.uC = *(f32 *)(arg0 + 0x1C) * D_800A90B4;
    blk.u10[0] = *(f32 *)(arg0 + 0xC);
    blk.u10[1] = *(f32 *)(arg0 + 0x10);
    blk.u10[2] = *(f32 *)(arg0 + 0x14);
    blk.u1C[0] = 1.0f;
    blk.u1C[1] = 1.0f;
    blk.u1C[2] = 1.0f;
    blk.u28[0] = *(f32 *)(arg0 + 0);
    blk.u28[1] = *(f32 *)(arg0 + 4);
    blk.u28[2] = *(f32 *)(arg0 + 8);
    blk.u34 = *(V3_1519F0FC *)D_800A5860;
    blk.u40 = *(V3_1519F0FC *)D_800A5860;
    blk.u4C = 0.0f;
    blk.u50 = 0x980;
    blk.u54 = arg2;
    blk.u56 = arg1;
    blk.u58 = 0;
    blk.u5C = 0;
    blk.u60 = 0xFF;
    blk.u61 = 0x15;
    blk.u62[0] = 0;
    blk.u62[1] = 0;
    blk.u62[2] = 0;
    blk.u62[3] = 0;
    blk.u62[4] = 0;
    blk.u62[5] = 0;
    blk.u68 = 2;
    blk.u6A = 0;
    blk.u6C = 0;
    blk.u70 = 0;
    blk.u72 = 1;
    blk.u74 = 0xFF;
    blk.u78 = 0;
    temp_v0 = func_15132BBC(&blk, 3, 0xFF, 0, 4, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x170, &tmp, 4);
    }
}
