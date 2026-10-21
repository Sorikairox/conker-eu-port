typedef struct { f32 x, y, z; } V368D0;
typedef struct { V368D0 pos; s16 u80; s16 u82; s32 u84; u8 pad88; s8 u89; u8 pad8A[2]; s32 pad8C; } SA68D0;
typedef struct { u8 *u44; u8 u48; u8 pad49[3]; V368D0 pos; f32 u58, u5C, u60, u64, u68, u6C; } SB68D0;
void *memcpy(void *, const void *, u32);
void func_151B68D0(u8 *arg0, u8 arg1, s32 arg2) {
    SA68D0 a;
    s32 pad;
    SB68D0 b;
    u8 *r;

    a.u89 = 10;
    a.pos.x = *(f32 *)(arg0 + 0x14);
    a.pos.y = *(f32 *)(arg0 + 0x18);
    a.u80 = 300;
    a.u82 = 6;
    b.u44 = arg0;
    a.pos.z = *(f32 *)(arg0 + 0x1C);
    b.u48 = arg0[0x3B];
    b.pos = a.pos;
    b.u58 = 0.0f;
    b.u5C = 0.0f;
    b.u64 = -16384.0f;
    b.u60 = -16384.0f;
    b.u68 = 0.0f;
    a.u84 = 0xD;
    r = func_15147FF0(&a, 0x30, 0x1C, 0xB, 0xB, 0xB, 0, 0, 0, arg1, arg2);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, sizeof(b));
    }
}
