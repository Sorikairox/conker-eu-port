s32 func_15149AC0(f32 *, s32, s32, s32, s32, s32);
extern f32 D_800A5BAC;
extern f32 D_800A5BB0;
extern f32 D_800A5BB4;
extern f32 D_800A5BB8;
extern f32 D_800A5BBC;
extern f32 D_800A5BC0;
extern f32 D_800A5BC4;
extern f32 D_800A5BC8;
extern f32 D_800A5BCC;
extern f32 D_800A5BD0;
extern f32 D_800A5BD4;
extern f32 D_800A5BD8;
extern f32 D_800A5BDC;
extern f32 D_800A5BE0;
extern f32 D_800A5BE4;

void func_1514B30C(f32 *arg0, u8 arg1, s32 arg2) {
    struct {
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s16 u50;
        s16 u52;
        s16 u54;
        u8 u56;
        u8 u57;
        u8 u58;
        u8 u59;
        s16 u5A;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        s32 u60;
        u8 u64;
        u8 pad65[3];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
    } sp;
    f32 a;
    f32 b;
    s32 pad[2]; // fakematch: frame

    do { sp.u50 = 0x6231; sp.u52 = 0x1A4D; } while (0); // fakematch: block boundary flips the two sh stores (permuter)
    *(V3A434 *)&sp.u30 = *(V3A434 *)arg0;
    sp.u56 = 0;
    sp.u57 = 0;
    sp.u58 = 0;
    sp.u59 = 0xFF;
    sp.u5D = 0xFF;
    sp.u5E = 0;
    sp.u5F = 1;
    sp.u60 = 0;
    sp.u5A = 1;
    sp.u64 = 0x1C;
    sp.u6C = 0.0f;
    sp.u70 = D_800A5BAC;
    sp.u74 = D_800A5BB0;
    a = (func_150ADA68() * D_800A5BB4 + D_800A5BB8) * D_800A5BBC;
    b = func_150ADA68();
    sp.u3C = D_800A5BC0 * a;
    sp.u44 = D_800A5BC4 * a;
    b = (b * D_800A5BC8 + D_800A5BCC) * D_800A5BD0;
    sp.u40 = D_800A5BD4 * b;
    sp.u48 = D_800A5BD8 * b;
    sp.u4C = D_800A5BDC * b;
    sp.u54 = func_150ADA20() % 17U + 16;
    sp.u68 = (func_150ADA68() * D_800A5BE0 + 50.0f) * D_800A5BE4;
    sp.u5C = func_150ADA20() % 156U + 100;
    func_15149AC0(&sp.u30, 0xA, 0, 0, arg1, arg2);
}
