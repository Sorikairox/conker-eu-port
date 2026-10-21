extern u8 (*D_80090070[])(void);
extern u8 D_800AB710[];
extern f32 D_800AB880;
extern f32 D_800AB884;
extern f32 D_800AB888;
extern f32 D_800AB88C;
typedef struct { f32 x, y, z; } V3_AB58;
typedef struct {
    u8 u0;
    s8 u1;
    s16 u2;
    s16 u4;
    s16 pad6;
    s32 u8;
    s32 uC;
    u8 u10[4];
    f32 u14;
    f32 u18;
    V3_AB58 u1C;
    f32 u28[3];
    f32 u34[3];
    s32 u40;
    u8 u44;
    u8 u45;
    s8 u46;
    s8 u47;
    s32 u48;
    u8 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
} Blk58_AB58;
typedef struct { u8 a; u8 b; f32 c; f32 d; } Tmp_AB58;

s32 func_151DAB58(u8 arg0, f32 arg1, u8 arg2, f32 *arg3, u8 arg4, u8 arg5, s32 arg6) {
    Blk58_AB58 blk;
    Tmp_AB58 tmp;
    s32 flag;
    u8 *temp_v0;

    blk.u0 = D_80090070[arg0]();
    blk.u2 = ((arg4 != 0 ? 0x3B : 0x22) << 8) + 3;
    blk.u4 = 0x64;
    blk.u8 = 0;
    blk.uC = 0;
    blk.u10[0] = 0;
    blk.u10[1] = 0;
    blk.u10[2] = 0;
    blk.u10[3] = 0xFF;
    blk.u14 = arg1;
    blk.u18 = arg1;
    blk.u1C = *(V3_AB58 *)arg3;
    flag = 0;
    if (D_800AB710[arg0] != 0) {
        flag = 0x40000000;
    }
    blk.u40 = flag | 0x0CDC0009;
    blk.u28[0] = 0.0f;
    blk.u28[1] = 0.0f;
    blk.u28[2] = 0.0f;
    blk.u34[0] = 1.0f;
    blk.u34[1] = 1.0f;
    blk.u34[2] = 1.0f;
    blk.u44 = arg2;
    blk.u45 = 0xFF;
    blk.u46 = 0;
    blk.u47 = 7;
    tmp.a = 0;
    tmp.b = (func_150ADA20() % 3U) + 6;
    tmp.c = (func_150ADA68() * D_800AB880) + D_800AB884;
    tmp.d = (func_150ADA68() * D_800AB888) + D_800AB88C;
    blk.u1 = 0;
    blk.u48 = 0;
    blk.u4C = 0xFF;
    blk.u50 = 0;
    blk.u54 = 0x20;
    blk.u56 = 7;
    temp_v0 = func_1513D2F0(&blk, (s32)&D_800A4AA0, 0, 0x14, 0, 0xE, (func_150ADA20() & 1 ? 1 : 0) | 2, arg4 != 0 ? 3 : 0, arg4 != 0 ? 0xFF : 0, 0xC, arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x110, &tmp, 0xC);
    }
}
