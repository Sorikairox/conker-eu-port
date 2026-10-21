typedef struct { f32 x, y, z; s16 u0C; s16 u0E; s32 u10; s8 u14; s8 u15; u8 pad16[2]; s32 u18; } SADA70;
typedef struct { f32 f[18]; s32 u48; u8 u4C; u8 pad4D[3]; } SBDA70;
s32 func_151CDA70(s32 arg0, u8 arg1, s32 arg2, u8 arg3, u8 arg4) {
    u8 *r;
    SADA70 a;
    SBDA70 b;

    a.u15 = 0x23;
    a.x = b.f[6] = ((s16 *)arg0)[0];
    a.y = ((s16 *)arg0)[1] + ((s16 *)arg0)[4];
    a.u0C = 0x12C;
    a.u0E = 0x34;
    a.u10 = 0xB;
    a.z = b.f[7] = ((s16 *)arg0)[2];
    b.f[13] = b.f[9] = ((s16 *)arg0)[3] * 0.875f;
    b.f[4] = 0.030000001f;
    b.f[0] = b.f[1] = ((s16 *)arg0)[3] * 0.125f;
    b.f[5] = 0.040000003f;
    b.f[2] = 0.0f;
    b.f[17] = ((s16 *)arg0)[1];
    b.f[3] = 0.0f;
    b.f[10] = ((s16 *)arg0)[3] * 0.0625f;
    b.f[11] = 0.0f;
    b.f[12] = 0.055000003f;
    b.f[16] = 0.0f;
    b.u48 = arg2;
    b.f[14] = -16384.0f;
    b.f[15] = -16384.0f;
    b.f[8] = 0.0f;
    b.u4C = arg1;
    a.u18 = 0;
    a.u14 = 7;
    r = func_15147FF0(&a, 0x50, 0x1C, 9, 9, 9, 0, 0, 0, arg3, arg4);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, 0x50);
    }
    return (s32)r;
}
