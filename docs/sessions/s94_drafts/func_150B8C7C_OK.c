s32 func_151308E4(void *, s32, s32, u8, s32);
void func_15143874(s16, f32, void *, void *);
s32 func_150B8C7C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    f32 scale;
    s32 pad;
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
        u8 u4C;
        u8 u4D;
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
        f32 u7C;
        f32 u80;
        f32 u84;
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
    s32 obj;
    s32 b;
    s32 a;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    scale = 0.917241f;
    sp.u3E = (func_150ADA20() & 0xF) + 0x19;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 71U) + 0x3C;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = ((func_150ADA68() * 15738.0f) + 24699.0f) * 0.01f;
    sp.u64[0] = arg2;
    sp.u64[1] = arg3;
    sp.u64[2] = arg4;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    func_15143874(arg8, ((func_150ADA68() * 154.0f) + 205.0f) * 0.1f, &sp.u7C, &sp.u84);
    sp.u80 = 0.0f;
    sp.u88 = 0.0f;
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
    sp.u8C = b | 0xE05 | a | 0x8000 | 0x4000;
    sp.u96 = 0xA;
    sp.u97 = -1;
    sp.u52 = 0x1C;
    sp.u54 = 9;
    sp.u56 = 0x19;
    sp.u98 = -1;
    sp.u99 = 0;
    sp.u58 = 1.033333f;
    obj = func_151308E4(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}
