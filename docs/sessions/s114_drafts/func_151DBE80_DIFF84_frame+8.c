typedef struct { f32 x, y, z; } V3DBE80;
typedef struct {
    u8 u0;
    u8 u1;
    s16 u2;
    s16 u4;
    s32 u8_;
    s32 uC;
    u8 u10[4];
    f32 u14;
    f32 u18;
    V3DBE80 u1C;
    f32 u28;
    f32 u2C;
    f32 u30;
    f32 u34;
    f32 u38;
    f32 u3C;
    s32 u40;
    u8 u44;
    u8 u45;
    u8 u46;
    u8 u47;
    s32 u48;
    u8 u4C;
    s32 u50;
    s16 u54;
    s16 u56;
} SpawnDBE80;
extern u8 D_800AB7F4[][3];
void func_1513D668(s32, s32, u8, u8, u8, u8, s16, f32, f32, s32, s32, u8, s32, u8, s32);
void func_151DBE80(u8 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8, s32 arg9) {
    SpawnDBE80 sp;
    s32 v;

    sp.u0 = 0x38;
    if (arg7 != 0) {
        v = 2;
    } else {
        v = 1;
    }
    sp.u2 = v + 0x440000;
    sp.u4 = arg3;
    sp.u8_ = 0;
    sp.uC = 0x4000;
    sp.u10[3] = 0xFF;
    sp.u10[0] = D_800AB7F4[arg0][0];
    sp.u14 = 1.0f;
    sp.u18 = 1.0f;
    sp.u10[1] = D_800AB7F4[arg0][1];
    sp.u10[2] = D_800AB7F4[arg0][2];
    sp.u1C = *(V3DBE80 *)arg4;
    sp.u34 = arg2;
    sp.u40 = 0x466C0001;
    sp.u45 = 0xFF;
    sp.u1 = 0;
    sp.u46 = 0;
    sp.u47 = 6;
    sp.u48 = 0;
    sp.u4C = 0xFF;
    sp.u50 = 0;
    sp.u54 = 1;
    sp.u56 = 0xFF;
    sp.u38 = 1.0f;
    sp.u3C = 1.0f;
    sp.u28 = 0.0f;
    sp.u2C = 0.0f;
    sp.u30 = 0.0f;
    sp.u44 = arg6;
    func_1513D668((s32)&sp, 0, 0xB, 0x11, 0, (func_150ADA20() & 1) + (func_150ADA20() & 1), func_150ADA20() & 0xFF, arg1, arg1, 0, arg5, 0, 0, arg8, arg9);
}
