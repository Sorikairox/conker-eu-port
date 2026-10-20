s32 func_151308E4(void *, s32, s32, u8, s32);
void func_15143874(s16, f32, f32 *, f32 *);
s32 func_1515C668(void *, f32 **);
extern f32 D_800BE9A4;
void func_15192F14(u8 *arg0) {
    u8 *p;
    s32 r;
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
        f32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x8];
    } sp;
    s32 obj;
    f32 scale;
    f32 *out;
    u8 a;

    p = arg0 + 0x28;
    *(f32 *)(p + 8) += (312.0f + func_150ADA68() * 599.0f) * 0.001f * D_800BE9A4;
    if (*(f32 *)(p + 8) > 1.0f) {
        if (func_1515C668(*(u8 **)p, &out) != 0) {
            sp.u51 = 0x29;
            sp.u3C = 0xE03;
            sp.u34 = 0x200005;
            sp.u4C = 0xB0;
            sp.u4D = 0xA0;
            sp.u4E = 0x2A;
            sp.u48 = 0x40;
            sp.u49 = 0xB;
            sp.u4A = 0x6A;
            sp.u38 = 0;
            sp.u40 = 0;
            sp.u44 = 0;
            sp.u4B = 0xFF;
            sp.u50 = 0xFF;
            sp.u94 = 3;
            sp.u95 = 3;
            sp.u8C = 0xE05;
            sp.u96 = 0xA;
            sp.u97 = -1;
            sp.u52 = 0x14;
            sp.u54 = 0xC;
            sp.u56 = 0x23;
            sp.u88 = 0.0f;
            sp.u58 = 1.04f;
            scale = 0.95000005f;
            do {
                a = func_150ADA20() & 1;
                sp.u3E = (func_150ADA20() % 31U) + 0x14;
                sp.u4F = (func_150ADA20() % 156U) + 0x64;
                sp.u5C = sp.u60 = (func_150ADA68() * 150.0f) + 100.0f;
                func_15143874(*(u16 *)(*(u8 **)p + 0x7A) >> 8, a ? 20.0f : -20.0f, &sp.u64[0], &sp.u64[2]);
                sp.u64[0] += *(f32 *)(*(u8 **)p + 0x14);
                sp.u64[2] += *(f32 *)(*(u8 **)p + 0x1C);
                sp.u64[1] = *(f32 *)(*(u8 **)p + 0x180) + 20.0f;
                sp.u8C &= ~0xC0;
                if (func_150ADA20() & 1) {
                    sp.u8C |= 0x40;
                }
                if (func_150ADA20() & 1) {
                    sp.u8C |= 0x80;
                }
                sp.u7C[0] = out[0] * -1.516f;
                sp.u7C[1] = out[1] * -1.516f;
                sp.u7C[2] = out[2] * -1.516f;
                obj = func_151308E4(&sp, 1, 4, arg0[0xC], arg0[1]);
                if (obj != 0) {
                    memcpy(obj + 0xA8, &scale, 4);
                }
                *(f32 *)(p + 8) -= 1.0f;
            } while (*(f32 *)(p + 8) > 1.0f);
        }
    }
}
