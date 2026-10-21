typedef struct { u8 b[4]; } B4_AEE4;
typedef struct { s32 w[10]; } Blk_AEE4;
typedef struct { f32 f0; f32 f4; B4_AEE4 c; Blk_AEE4 d; } Tab_AEE4;
typedef struct { B4_AEE4 c; Blk_AEE4 d; } A_AEE4;
typedef struct { u8 u0; u8 *u4; f32 u8_; f32 uC; f32 u10; f32 u14; f32 u18; f32 u1C; f32 u20; u8 u24; s8 u25; u8 u26; } B_AEE4;
extern Tab_AEE4 D_800A674C[];
struct260 *func_151A8B20(void *arg0, s16 arg1, s32 arg2, u8 arg3, s32 arg4);
void func_1515AEE4(u8 *arg0, s32 arg1) {
    B_AEE4 b;
    s32 pad[2];
    A_AEE4 a;
    Tab_AEE4 *e;
    struct260 *p;

    if (arg0[0x1F] <= 0) {
        e = &D_800A674C[arg0[0x1F]];
        b.u0 = 0xF;
        b.u24 = 0;
        b.u25 = -1;
        b.u26 = 2;
        b.u10 = 0.0f;
        b.u14 = 0.0f;
        b.u18 = 0.0f;
        b.u1C = 0.0f;
        b.u20 = 0.0f;
        b.u4 = arg0;
        b.u8_ = e->f0;
        b.uC = e->f4;
        a.c = e->c;
        a.d = e->d;
        p = func_151A8B20(&b, -1, 0x2C, 0xFF, 0);
        if (p != NULL) {
            memcpy((u8 *)p + 0x80, &a, 0x2C);
        }
    }
}
