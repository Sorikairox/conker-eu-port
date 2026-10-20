extern s32 D_80088F70[];
typedef struct {
    s32 x[3];
} V3i_151037D4;
s32 func_151308E4(void *, s32, s32, u8, s32);
void func_151037D4(s16 arg0, u8 arg1, f32 arg2, u8 *arg3, u8 arg4, u8 arg5, s32 arg6) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        u8 u48;
        u8 u49;
        u8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        u8 u4E;
        u8 u4F;
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
        u8 u9A;
        u8 pad9B[0xD];
    } sp;
    s32 b;
    s32 a;

    sp.u51 = D_80088F70[func_150ADA20() & 3];
    sp.u38 = 0x20000;
    sp.u48 = 0xFF;
    sp.u3C = 0x2203;
    sp.u34 = 0x200005;
    sp.u3E = arg0 + 1;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u49 = 0xFF;
    sp.u4A = 0xFF;
    sp.u4B = 0xFF;
    sp.u4C = 0xFF;
    sp.u4D = 0xFF;
    sp.u4E = 0xFF;
    sp.u50 = 0xFF;
    sp.u60 = arg2;
    sp.u5C = arg2;
    sp.u4F = arg1;
    *(V3i_151037D4 *)sp.u64 = *(V3i_151037D4 *)arg3;
    sp.u52 = 3;
    sp.u54 = 0x55;
    sp.u56 = 1;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    sp.u7C = 0.0f;
    sp.u80 = 0.0f;
    sp.u84 = 0.0f;
    sp.u88 = 0.0f;
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
    sp.u8C = b | 1 | a | 0xC200 | 0x40000 | 0x800000;
    sp.u94 = 6;
    sp.u95 = 8;
    sp.u96 = -1;
    sp.u97 = -1;
    sp.u98 = -1;
    sp.u99 = 0;
    sp.u9A = arg4;
    func_151308E4(&sp, 1, 0, arg5, arg6);
}
