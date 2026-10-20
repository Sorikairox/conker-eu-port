typedef struct { u8 *p; u8 b; } Bc6b4;
typedef struct { f32 v[3]; } V3c6b4;
typedef struct { V3c6b4 pos; s16 u0C; s16 u0E; s32 u10; s8 u14; s8 u15; } S2c6b4;
typedef struct { u8 *p; u8 b; V3c6b4 pos; f32 u14; f32 u18; f32 u1C; f32 u20; } B2c6b4;
typedef struct { s8 u0; s8 u1; s16 u2; s8 u4; } S3c6b4;
extern f32 D_800AAC10;
extern f32 D_800DCE54;
s32 func_15163414(S3c6b4 *, u8 *, u8 *, u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_151BC6B4(u8 *arg0, u8 arg1, s32 arg2) {
    s32 ret;
    struct_eu_EF410 s1;
    Bc6b4 b1;
    S2c6b4 s2;
    B2c6b4 b2;
    Bc6b4 b3;
    S3c6b4 s3;
    u8 *px;
    u8 *py;
    u8 *pz;
    u8 *ret2;

    if (D_80082FA0 < 2 && D_8008FD8C < 5) {
        s1.unk0 = (s32)(arg0 + 0x14);
        s1.unk4 = (s32)(arg0 + 0x18);
        s1.unk8 = (s32)(arg0 + 0x1C);
        s1.unk14 = 300;
        s1.unkC = 15.0f;
        s1.unk10 = D_800AAC10 * D_800DCE54;
        s1.unk16 = 4;
        s1.unk17 = 4;
        s1.unk18 = 1;
        s1.unk19 = 0;
        b1.p = arg0;
        b1.b = arg0[0x3B];
        ret = func_15134908(&s1, 8, arg1, arg2);
        if (ret != 0) {
            memcpy(ret + 0x40, &b1, 8);
        }
    }
    s2.u15 = 0x28;
    s2.pos.v[0] = *(f32 *)(arg0 + 0x14);
    s2.pos.v[1] = *(f32 *)(arg0 + 0x18);
    s2.u0C = 300;
    s2.u0E = 6;
    s2.u10 = 0xC;
    b2.p = arg0;
    s2.pos.v[2] = *(f32 *)(arg0 + 0x1C);
    b2.b = arg0[0x3B];
    b2.pos = s2.pos;
    b2.u14 = 0.0f;
    b2.u18 = 0.0f;
    b2.u20 = -16384.0f;
    b2.u1C = -16384.0f;
    pz = arg0 + 0x1C;
    py = arg0 + 0x18;
    px = arg0 + 0x14;
    ret2 = func_15147FF0(&s2, 0x28, 0x14, 0xA, 0xA, 0xA, 0, 0, 0, arg1, arg2);
    if (ret2 != NULL) {
        memcpy(*(s32 *)(ret2 + 0x98), &b2, 0x24);
    }
    b3.p = arg0;
    s3.u0 = 2;
    s3.u1 = 0xE;
    b3.b = arg0[0x3B];
    s3.u2 = 300;
    s3.u4 = 0x1F;
    ret = func_15163414(&s3, px, py, pz, 0, 0, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, 8, arg1, arg2);
    if (ret != 0) {
        memcpy(ret + 0x28, &b3, 8);
    }
}
