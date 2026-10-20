extern f32 D_800BE9A4;
s32 func_151308E4(void *, s32, s32, u8, s32);
void func_151436B4(f32, f32, f32, f32 *);
void func_150E92DC(u8 *arg0) {
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
        f32 u64;
        f32 u68;
        f32 u6C;
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
        u8 pad98[0x10];
    } sp;
    s32 obj;
    f32 scale;
    u8 *p;
    s32 b;
    f32 r0;
    f32 r1;

    p = arg0 + 0x28;
    *(f32 *)(p + 0x14) += (*(f32 *)(p + 0xC) + func_150ADA68() * *(f32 *)(p + 0x10)) * D_800BE9A4;
    if (*(f32 *)(p + 0x14) > 1.0f) {
        s32 a;

        sp.u51 = 0x16;
        sp.u3C = 0xE01;
        sp.u34 = 0x200005;
        sp.u38 = 0;
        sp.u40 = 0;
        sp.u44 = 0;
        sp.u8C = 0x801E05;
        sp.u94 = 3;
        sp.u95 = 3;
        sp.u96 = 0x1A;
        sp.u97 = -1;
        sp.u70 = 0.0f;
        sp.u74 = 0.0f;
        sp.u78 = 0.0f;
        sp.u88 = 0.0f;
        sp.u4B = 0xFF;
        sp.u50 = 0xFF;
        sp.u52 = 0x1E;
        sp.u54 = 8;
        sp.u7C = 0.0f;
        sp.u84 = 0.0f;
        do {
            scale = 0.9701f;
            sp.u56 = sp.u3E = (func_150ADA20() & 0xF) + 0x28;
            sp.u4F = (func_150ADA20() % 119U) + 0x64;
            sp.u5C = sp.u60 = (func_150ADA68() * 59.0f) + 80.0f;
            sp.u58 = ((func_150ADA68() * 3727.0f) + 99979.0f) * 0.00001f;
            sp.u8C &= ~0xC0;
            if (func_150ADA20() & 1) {
                a = 0x80;
            } else {
                a = 0;
            }
            if (func_150ADA20() & 1) {
                b = 0x40;
            } else {
                b = 0;
            }
            sp.u8C |= (u32)(b | a); // fakematch: the u32 cast picks the or-register order
            sp.u4C = 0x44;
            sp.u4D = 0x3C;
            sp.u4E = 0x27;
            sp.u48 = 0xF;
            sp.u49 = 0x11;
            sp.u4A = 5;
            r0 = func_150ADA68();
            r1 = func_150ADA68();
            func_151436B4(r0 * 6.2831855f, r1 * 6.2831855f, func_150ADA68() * 20.0f, &sp.u64);
            sp.u64 += *(f32 *)(p + 0);
            sp.u68 += *(f32 *)(p + 4);
            sp.u6C += *(f32 *)(p + 8);
            sp.u80 = ((func_150ADA68() * 471.0f) + -1242.0f) * 0.01f;
            obj = func_151308E4(&sp, 0, 4, arg0[0xC], arg0[1]);
            if (obj != 0) {
                memcpy(obj + 0xA8, &scale, 4);
            }
            *(f32 *)(p + 0x14) -= 1.0f;
        } while (*(f32 *)(p + 0x14) > 1.0f);
    }
}
