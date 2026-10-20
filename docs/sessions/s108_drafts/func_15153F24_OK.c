typedef struct { f32 v[3]; } V3_3f24;
typedef struct {
    V3_3f24 pos;
    f32 vel[3];
    f32 a;
    f32 b;
    u8 c[9];
    s16 d;
    u16 e;
    f32 f;
    s8 g;
    s16 h;
    s16 i;
} S_3f24;
void func_15156700(S_3f24 *, u8, s32, u8, s32);

void func_15153F24(u8 *arg0, u8 arg1) {
    S_3f24 sp;
    s32 n;
    s16 a;
    s16 b;
    f32 sb;
    f32 cb;
    f32 sa;
    f32 ca;

    n = *(s16 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 2) + 1));
    sp.pos = *(V3_3f24 *)(arg0 + 4);
    sp.c[0] = *(u8 *)(arg0 + 0x28);
    sp.c[1] = *(u8 *)(arg0 + 0x29);
    sp.c[2] = *(u8 *)(arg0 + 0x2A);
    sp.c[3] = *(u8 *)(arg0 + 0x2B);
    sp.c[4] = *(u8 *)(arg0 + 0x2C);
    sp.c[5] = *(u8 *)(arg0 + 0x2D);
    sp.c[6] = *(u8 *)(arg0 + 0x2E);
    sp.c[7] = *(u8 *)(arg0 + 0x2F);
    sp.c[8] = *(u8 *)(arg0 + 0x30);
    sp.e = *(u16 *)(arg0 + 0x36);
    sp.h = *(s16 *)(arg0 + 0x42);
    sp.i = *(s16 *)(arg0 + 0x44);
    while (n != 0) {
        a = *(s16 *)(arg0 + 0x10) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x14) + 1));
        b = *(s16 *)(arg0 + 0x12) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1));
        sb = func_151423D8(b);
        cb = func_151423D8(b - 0x40);
        sa = func_151423D8(a);
        ca = func_151423D8(a - 0x40);
        sp.vel[0] = 10.0f * sb * ca;
        sp.vel[1] = -10.0f * cb;
        sp.vel[2] = 10.0f * sb * sa;
        sp.a = *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * func_150ADA68();
        sp.b = *(f32 *)(arg0 + 0x20) + *(f32 *)(arg0 + 0x24) * func_150ADA68();
        sp.d = *(s16 *)(arg0 + 0x32) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x34) + 1));
        sp.f = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x3C) * func_150ADA68();
        sp.g = *(u8 *)(arg0 + 0x40) + (func_150ADA20() % (u32)(*(u8 *)(arg0 + 0x41) + 1));
        func_15156700(&sp, *(u8 *)(arg0 + 0x46), 0, arg1, 0);
        n--;
    }
}
