extern f32 D_800BE9A4;
typedef struct { f32 x, y, z; } V3_20E4;
extern V3_20E4 D_8008FE70, D_8008FE7C;
void func_15143874(s16, f32, f32 *, f32 *);
s32 func_151308E4(void *, s32, s32, u8, s32);
void func_15143794(s16, s16, f32, void *);
void func_151B20E4(u8 *arg0) {
    u8 *p;
    V3_20E4 *q;
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
    V3_20E4 b;
    V3_20E4 a;

    p = arg0 + 0x28;
    *(f32 *)(p + 8) += (697.0f + func_150ADA68() * 342.0f) * 0.001f * D_800BE9A4;
    if (*(f32 *)(p + 8) > 1.0f) {
        if (*(s32 *)(*(u8 **)p + 0x1D4) != 0) {
            V3_20E4 c = D_8008FE70;
            func_15143134(&c, &b, *(s32 *)(*(u8 **)p + 0x1D4) + 0x800);
            {
                V3_20E4 d = D_8008FE7C;
                func_15143134(&d, &a, *(s32 *)(*(u8 **)p + 0x1D4) + 0x640);
            }
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
            sp.u88 = 0.0f;
            sp.u8C = 0xE05;
            sp.u96 = 0xA;
            sp.u97 = -1;
            sp.u52 = 0x1E;
            sp.u54 = 8;
            sp.u56 = 0x32;
            sp.u58 = 1.02700007f;
            scale = 0.924f;
            do {
                s32 base;
                s16 ang;

                sp.u3E = (func_150ADA20() % 41U) + 0x1E;
                sp.u4F = (func_150ADA20() % 156U) + 0x64;
                sp.u5C = sp.u60 = (func_150ADA68() * 104.0f) + 199.0f;
                if (func_150ADA20() & 1) {
                    q = &b;
                } else {
                    q = &a;
                }
                base = ((*(u16 *)(*(u8 **)p + 0x7A) >> 8) + 0x40) & 0xFF;
                ang = ((func_150ADA20() % 100U) + base) - 0x31;
                func_15143874(ang, 36.0f, &sp.u64[0], &sp.u64[2]);
                sp.u64[1] = 0.0f;
                sp.u64[0] += q->x;
                sp.u64[1] = q->y;
                sp.u64[2] += q->z;
                func_15143874(ang, ((func_150ADA68() * 1497.0f) + 995.0f) * 0.01f, &sp.u7C[0], &sp.u7C[2]);
                sp.u7C[1] = 0.0f;
                if (!p && !p && !p) { // fakematch: basic-block boundary (remote permuter)
                }
                sp.u8C &= ~0xC0;
                if (func_150ADA20() & 1) {
                    sp.u8C |= 0x40;
                }
                if (func_150ADA20() & 1) {
                    sp.u8C |= 0x80;
                }
                obj = func_151308E4(&sp, 1, 4, arg0[0xC], arg0[1]);
                if (obj != 0) {
                    memcpy(obj + 0xA8, &scale, 4);
                }
                *(f32 *)(p + 8) -= 1.0f;
            } while (*(f32 *)(p + 8) > 1.0f);
            return;
        }
        while (*(f32 *)(p + 8) > 1.0f) {
            *(f32 *)(p + 8) -= 1.0f;
        }
    }
}
