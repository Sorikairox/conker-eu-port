s32 func_151308E4(void *, s32, s32, u8, s32);
typedef struct {
    s32 x[3];
} V3i_B8AA0;
void func_15143794(s16, s16, f32, void *);
void func_150C9EB4(u8 *arg0, f32 *arg1, u8 arg2, s32 arg3) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        s8 u4C;
        s8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64[3];
        f32 u70;
        f32 u74;
        f32 u78;
        s32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        s8 u99;
        u8 pad9A[10];
    } sp;
    s32 b;
    s16 r;
    f32 f;
    s32 a;

    sp.u51 = 0x26;
    sp.u3C = 0xC01;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() % 81U) + 0x19;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u94 = 5;
    sp.u95 = 5;
    sp.u48 = 0;
    sp.u49 = 0;
    sp.u4A = 0;
    sp.u4B = 0xFF;
    sp.u4C = 0;
    sp.u4D = 0;
    sp.u4E = 0;
    sp.u4F = (func_150ADA20() % 156U) + 0x64;
    sp.u50 = 0xFF;
    sp.u5C = sp.u60 = (func_150ADA68() * 500.0f) + 500.0f;
    *(V3i_B8AA0 *)sp.u64 = *(V3i_B8AA0 *)arg1;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u88 = ((func_150ADA68() * 550.0f) + -1416.0f) * 0.001f;
    sp.u52 = 0x14;
    sp.u54 = 0xC;
    sp.u56 = 0;
    sp.u58 = 1.0f;
    if (func_150ADA20() & 1) {
        a = 0x40;
    } else {
        a = 0;
    }
    if (func_150ADA20() & 1) {
        b = 0x80;
    } else {
        b = 0;
    }
    sp.u8C = b | 7 | a | 0x200;
    sp.u96 = -1;
    sp.u97 = -1;
    r = (func_150ADA20() % 11U) - 0x12;
    f = (*(f32 *)(arg0 + 0x20) * 0.961f) + ((*(f32 *)(arg0 + 0x20) * 0.24300002f) * func_150ADA68());
    func_15143794(arg2, r, f, sp.u7C);
    func_151308E4(&sp, 1, 0, arg0[0xC], arg0[1]);
}
