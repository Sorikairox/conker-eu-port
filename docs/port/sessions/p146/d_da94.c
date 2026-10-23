extern f32 D_800A2310;
extern f32 D_800A2314;
extern f32 D_800A2318;
extern f32 D_800A231C;
extern f32 D_800A2320;
extern f32 D_800A2324;
extern f32 D_800A2328;
extern f32 D_800A232C;
extern f32 D_800A2330;
extern f32 D_800A2334;
extern f32 D_800A2338;
void func_1502ED88(u8 *, s32, s32, s32, s32, s32, s32);
void func_151080F8(u8 *, s16, s16, u8, s32);
void func_151D58E4(u8 *, f32, f32, f32, u8, u8, s32);
void func_150E856C(f32, u8, s32, u8 *, s16, u8, u8, u8, u8, u8, u8, s32);
void func_150E892C(f32 *, s16, u8, s32);
// bound_cloud_update: update handler (D_8008A100 slot 43) of a cloud effect that can be bound to an object. The
// state block at +0x110 holds the object (+0x110, valid while its +0 is set and its id +0x3B equals +0x114), the
// peak alpha scale (+0x118), the remaining life (+0x11C), a pulse phase (+0x120), two wobble phases (+0x12C,
// +0x130) with their outputs (+0x124, +0x128), a linked effect (+0x138), a spawn accumulator (+0x13C), a height
// (+0x140), a sound block (+0x144), a "burst done" byte (+0x168) and flags (+0x169). A bound object is tinted
// and gets random particles (func_151080F8) at a random rate; the effect follows its x/z. The scale fades in
// over life 50..20, holds to 10, then fades out; at life 10 the burst fires once (object animation 0x16 and a
// sound, two shock waves, and with flag 1 a smoke puff + flash). Alpha +0x5C pulses (sin), the linked effect
// copies scale / alpha / x / z. Returns 0 once the life drops below 0.
s32 func_150FDA94(u8 *fx) {
    u8 *st = fx + 0x110;
    u8 *obj = *(u8 **)st;
    u8 *link;
    f32 x;
    f32 z;
    f32 pos[3];
    f32 life;
    f32 scale;
    f32 size;
    s32 r0;
    s32 r1;

    if (obj != NULL) {
        if (*(s32 *)obj == 0 || st[4] != obj[0x3B]) {
            *(u8 **)st = NULL;
            obj = NULL;
        }
        /* as the original: reads through obj even after clearing it */
        x = *(f32 *)(obj + 0x14);
        z = *(f32 *)(obj + 0x1C);
    } else {
        x = *(f32 *)(fx + 0x34);
        z = *(f32 *)(fx + 0x3C);
    }
    if (obj != NULL) {
        func_1502ED88(obj, 0xFF, 0, 0, 0xFF, 0, 4);
        *(f32 *)(st + 0x2C) += (D_800A2310 + func_150ADA68() * D_800A2314) * D_800BE9A4;
        while (*(f32 *)(st + 0x2C) > 1.0f) {
            r0 = func_150ADA20();
            r1 = func_150ADA20();
            func_151080F8(obj, (s16)(r0 & 0xFF), (s16)((u32)r1 % 101 - 63), fx[0xC], fx[1]);
            *(f32 *)(st + 0x2C) -= 1.0f;
        }
    }
    life = *(f32 *)(st + 0xC);
    if (life > 20.0f) {
        *(f32 *)(fx + 0x2C) = (50.0f - life) * D_800A2318 * *(f32 *)(st + 0x8);
    } else if (life > 10.0f) {
        *(f32 *)(fx + 0x2C) = *(f32 *)(st + 0x8);
    } else {
        *(f32 *)(fx + 0x2C) = life * D_800A231C * *(f32 *)(st + 0x8);
        if (st[0x58] == 0) {
            if (obj != NULL) {
                func_1505D024((struct127 *)obj, 0x16, *(u16 *)(obj + 0x7A), -1);
                func_10010F88(0x69D, 0x7D00, 0, 0, 0, (s16)(s32) * (f32 *)(fx + 0x34),
                              (s16)(s32) * (f32 *)(fx + 0x38), (s16)(s32) * (f32 *)(fx + 0x3C), 500, 3000);
            }
            st[0x58] = 1;
            func_151D5404((struct17 *)(fx + 0x34), 506.0f, 1013.0f, 0.0009871669f, 15, 20, fx[0xC], fx[1]);
            func_151D58E4(fx + 0x34, 506.0f, 1013.0f, 0.0009871669f, 5, fx[0xC], fx[1]);
            if (st[0x59] & 1) {
                pos[0] = *(f32 *)(fx + 0x34);
                pos[1] = *(f32 *)(st + 0x30);
                pos[2] = *(f32 *)(fx + 0x3C);
                size = func_150ADA68();
                r0 = func_150ADA20();
                r1 = func_150ADA20();
                func_150E856C(size * 78.0f + 125.0f, ((u32)r0 % 76 + 180) & 0xFF, (s32)(st + 0x34), (u8 *)pos,
                              (u32)r1 % 207 + 302, 0, 1, 0, 0, 0, fx[0xC], 0);
                func_150E892C(pos, (s16)((u32)func_150ADA20() % 80 + 243), fx[0xC], fx[1]);
            }
        }
    }
    fx[0x5C] = (u32)(sinf(*(f32 *)(st + 0x10)) * 57.0f + 198.0f);
    *(f32 *)(st + 0x10) += D_800A2320 * D_800BE9A4;
    *(f32 *)(st + 0x10) = func_15144B68(*(f32 *)(st + 0x10));
    *(f32 *)(st + 0x1C) += D_800A2324 * D_800BE9A4;
    *(f32 *)(st + 0x20) += D_800A2328 * D_800BE9A4;
    *(f32 *)(st + 0x1C) = func_15144B68(*(f32 *)(st + 0x1C));
    *(f32 *)(st + 0x20) = func_15144B68(*(f32 *)(st + 0x20));
    *(f32 *)(st + 0x14) = func_150AD78C(*(f32 *)(st + 0x1C)) * D_800A232C + D_800A2330;
    *(f32 *)(st + 0x18) = func_150AD78C(*(f32 *)(st + 0x20)) * 1192.0f + D_800A2334;
    link = *(u8 **)(st + 0x28);
    if (link != NULL) {
        scale = *(f32 *)(fx + 0x2C) * D_800A2338;
        *(f32 *)(link + 0x30) = scale;
        *(f32 *)(*(u8 **)(st + 0x28) + 0x2C) = scale;
        (*(u8 **)(st + 0x28))[0x5C] = fx[0x5C];
        *(f32 *)(*(u8 **)(st + 0x28) + 0x34) = x;
        *(f32 *)(*(u8 **)(st + 0x28) + 0x3C) = z;
    }
    *(f32 *)(fx + 0x34) = x;
    *(f32 *)(fx + 0x3C) = z;
    *(f32 *)(st + 0xC) -= D_800BE9A4;
    if (*(f32 *)(st + 0xC) < 0.0f) {
        return 0;
    }
    return 1;
}
