extern f32 D_800BE9A4;
extern s32 D_80082FA0;
extern f32 D_800A13B4[][3];
extern f32 D_800A13CC[][3];
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_15145CD0(s32, void *, void *, s32);
void func_150E16CC(u8 *arg0) {
    s32 obj;
    u8 *p;
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
        s8 u98;
        s8 u99;
        u8 pad9A[0xE];
    } sp;
    f32 scale;
    f32 v[3];
    f32 *tbl[2];
    f32 *outs[2];
    s32 a;
    s32 b;
    s32 i;
    s16 mask;
    f32 f;

    p = arg0 + 0x28;
    *(f32 *)(p + 0xC) += (204.0f + func_150ADA68() * 159.0f) * 0.001f * D_800BE9A4;
    if (*(f32 *)(p + 0xC) > 1.0f) {
        i = 0;
        mask = 0;
        for (; i <= D_80082FA0; i++) {
            mask |= 1 << i;
        }
        if (!(*(s16 *)(*(u8 **)(p + 8) + 2) & mask)) {
            do {
                *(f32 *)(p + 0xC) -= 1.0f;
            } while (*(f32 *)(p + 0xC) > 1.0f);
            return;
        }
        sp.u51 = 0x29;
        sp.u3C = 0x4403;
        sp.u34 = 0x200005;
        sp.u38 = 0;
        sp.u40 = 0;
        sp.u44 = 0;
        sp.u52 = 0x21;
        sp.u54 = 7;
        sp.u8C = 0x1CE05;
        sp.u94 = 6;
        sp.u95 = 8;
        sp.u96 = 0x10;
        sp.u97 = -1;
        sp.u88 = 0.0f;
        sp.u98 = -1;
        sp.u99 = 0;
        sp.u56 = 0x27;
        sp.u48 = 0xDD;
        sp.u49 = 0xD3;
        sp.u4A = 0xCD;
        sp.u4B = 0xFF;
        sp.u4C = 0x57;
        sp.u4D = 0x55;
        sp.u4E = 0x5A;
        sp.u50 = 0xFF;
        scale = 0.962339f;
        sp.u58 = 1.011462f;
        tbl[0] = D_800A13B4[p[0]];
        tbl[1] = D_800A13CC[p[0]];
        outs[0] = &sp.u64;
        outs[1] = v;
        func_15145CD0(*(s32 *)(p + 4), tbl, outs, 2);
        v[0] -= sp.u64;
        v[1] -= sp.u68;
        if ((p && p) && p) { } // fakematch: scheduling barrier (permuter)
        v[2] -= sp.u6C;
        do {
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
            sp.u70 = 0.0f;
            sp.u74 = 0.0f;
            sp.u78 = 0.0f;
            sp.u4F = 0xFF;
            sp.u3E = (func_150ADA20() % 17U) + 0x32;
            sp.u5C = sp.u60 = (func_150ADA68() * 165.0f) + 357.0f;
            f = ((func_150ADA68() * 195.0f) + 356.0f) * 0.001f;
            sp.u7C = v[0] * f;
            sp.u80 = v[1] * f;
            sp.u84 = v[2] * f;
            obj = func_151308E4(&sp, 1, 4, arg0[0xC], arg0[1]);
            if (obj != 0) {
                memcpy(obj + 0xA8, &scale, 4);
            }
            *(f32 *)(p + 0xC) -= 1.0f;
        } while (*(f32 *)(p + 0xC) > 1.0f);
    }
}
