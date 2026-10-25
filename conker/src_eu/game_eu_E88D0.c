#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8  pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u8  pad1E[0xA];
    /* 0x28 */ u8  unk28;
    /* 0x29 */ u8  pad29[0x81 - 0x29];
    /* 0x81 */ u8  unk81;
    /* 0x82 */ u8  pad82[0xB0 - 0x82];
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
} struct_eu_E88D0;

void func_1513F6C0();


#ifdef NON_MATCHING
void func_15142314(void *, s32, void *);
s32 func_15143E94(s32, s32);
void func_151664F0(s32, s32, s32, s32, s32, s32, s32, u8, s32);
void func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
void func_1504715C(void *, u8 *);
s32 func_15046F70(f32 *, s32, f32, f32 *);
struct210 *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD);
s32 func_1518B140(u8 *arg0, s32 arg1, u8 arg2);
void func_1516972C(struct102 *arg0);
/* the .s's late_rodata D_800A0240 / D_800A0244 / D_800A0248 (0.7111111, 1.02, 0.95) is gone in the NM link */
static const f32 D_800A0240[1] = { 0.711111128f }; /* 0x3F360B61 (arrays: IDO puts scalar float statics in .data) */
static const f32 D_800A0244_[1] = { 1.01999998f }; /* 0x3F828F5C, read by func_150BB4CC */
#define D_800A0244 D_800A0244_[0]
static const f32 D_800A0248_[1] = { 0.949999988f }; /* 0x3F733333, read by func_150BB4CC */
#define D_800A0248 D_800A0248_[0]

// foot_splash_effect: water / dust splash at foot bone 0x11 (kind 0) or 0x1A (kind 1) of object `obj` (skipped for a
// missing object, state 0 or 8, or no model at +0x1D4), at the object's own height +0x180: sound 0x4022, a ring
// func_151664F0, a spray func_1514CBE8 (heading = current camera's +0x380 * 0.7111 +- 60). When the ground probe
// (func_15046F70, 100 above to 100 below) hits, also a ripple sprite (func_1513C73C, template 0x7340) that is added
// to list D_80088750 or freed; then a second smaller spray. `alpha` is passed on to every spawn.
void func_150BABE0(u8 *obj, u8 kind, u8 alpha) {
    struct {
        s32 tex;
        s16 life;
        u8 type;
        u8 pad7;
        s32 unk8;
        s32 rot;
        u8 col[8];
        s32 flags;
        s32 unk1C;
        u8 unk20;
    } spr;
    f32 hit[9];
    f32 probe[3];
    f32 pos[3];
    u8 *cam = (u8 *) D_800DBFF0 + D_80082FA4 * 0x9A0;
    s32 heading = (s32) (*(f32 *) (cam + 0x380) * D_800A0240[0]);
    s16 left, right;
    f32 size;
    s32 r1, r2, r3;
    struct210 *p;

    if (obj == NULL) {
        return;
    }
    if (*(s32 *) obj == 0 || *(s32 *) obj == 8) {
        return;
    }
    if (*(u8 **) (obj + 0x1D4) == NULL) {
        return;
    }
    /* callers pass kind 0 or 1; the asm leaves the bone uninitialised for other values */
    func_15142314(*(u8 **) (obj + 0x1D4), kind == 0 ? 0x11 : 0x1A, pos);
    pos[1] = *(f32 *) (obj + 0x180);
    func_15143E94(5, 0x4022);
    func_151664F0(-1, (s32) pos[0], (s32) (pos[1] + 6.0f), (s32) pos[2], 0x19, 0x12, 0, alpha, 1);
    size = func_150ADA68();
    r1 = func_150ADA20();
    right = heading + 0x3C;
    left = heading - 0x3C;
    func_1514CBE8(pos[0], pos[1], pos[2], size * 50.0f + 40.0f, right, left, (u32) r1 % 11 + 30, 5, 0, 0.0f, 0, alpha);
    func_1504715C(hit, obj);
    probe[0] = pos[0];
    probe[1] = pos[1] + 100.0f;
    probe[2] = pos[2];
    if (func_15046F70(probe, 0, pos[1] - 100.0f, hit)) {
        size = func_150ADA68() * 200.0f + 200.0f;
        spr.type = 0x2A;
        spr.pad7 = 0;
        spr.tex = 0x7340;
        spr.life = 300;
        spr.unk8 = 0;
        spr.rot = (u32) func_150ADA20() % 2001 + 2000;
        spr.col[0] = 0xFF;
        spr.col[1] = 0xFF;
        spr.col[2] = 0;
        spr.col[3] = 0;
        spr.col[4] = 0;
        spr.col[5] = 0xFF;
        spr.col[6] = 0;
        spr.col[7] = 0xD;
        spr.unk20 = 0xFF;
        spr.unk1C = 0;
        spr.flags = 0x170002;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        r3 = func_150ADA20();
        p = func_1513C73C((s32) &spr, 0, 0, (s32) &hit[1], pos[0], hit[0], pos[2], size, size, r1 & 0xFF,
                          (r3 & 1) + (r2 & 1) * 2, 4, alpha, 0);
        if (p != NULL && func_1518B140((u8 *) D_80088750, (s32) p, 1) == 0) {
            func_1516972C((struct102 *) p);
        }
    }
    size = func_150ADA68();
    r1 = func_150ADA20();
    func_1514CBE8(pos[0], pos[1], pos[2], size * 40.0f + 60.0f, right, left, (u32) r1 % 7 + 6, 6, 0, 0.0f, 0, alpha);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E88D0/func_150BABE0.s")
#endif

#ifndef NON_MATCHING
extern f32 D_800A0244;
extern f32 D_800A0248;
#endif
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_150BB4CC(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
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
        u8 pad70[0xC];
        f32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0xC];
    } sp;
    s32 obj;
    f32 scale;
    s16 spBE;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 temp_f2;

    spB8 = func_151423D8(arg8 - 0x40);
    spB4 = func_151423D8(arg8);
    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() % 36U) + 0x46;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 52U) + 0x5A;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (func_150ADA68() * 165.0f) + 800.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    spBE = (func_150ADA20() % 11U) - 0xC;
    spB0 = func_151423D8(spBE - 0x40);
    spAC = func_151423D8(spBE);
    temp_f2 = (func_150ADA68() * 11.0f) + 15.0f;
    sp.u7C[0] = temp_f2 * spAC * spB8;
    sp.u7C[1] = -temp_f2 * spB0;
    sp.u7C[2] = temp_f2 * spAC * spB4;
    sp.u88 = 0.0f;
    sp.u8C = 0xE05;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 2;
    sp.u97 = -1;
    sp.u52 = 0x16;
    sp.u54 = 0xB;
    sp.u56 = 1;
    sp.u58 = D_800A0244;
    scale = D_800A0248;
    obj = func_151308E4(&sp, 0, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

s32 func_150BB740(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

void func_150BB8E8(struct_eu_E88D0 *arg0) {
    arg0->unk18 |= 1;
    arg0->unk1C = 50;
    arg0->unkB0 = arg0->unk1C;
    arg0->unkB2 = 5;
    func_1513F6C0(arg0, 6, arg0->unk81);
}

s32 func_150BB930(struct_eu_E88D0 *arg0) {
    if (arg0->unk1C < arg0->unkB0) {
        s16 temp_lo = arg0->unk1C * arg0->unkB2;
        if (temp_lo < arg0->unk28) {
            arg0->unk28 = temp_lo;
        }
    }
    return 1;
}

s32 func_150BB978(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    s16 spBE;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    struct {
        f32 u28[13];
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        u8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 pad91[0x1];
        s8 u92;
        u8 pad93[0x1];
        s32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        u8 padA0[0x8];
    } sp;
    f32 temp_f2;

    spB8 = func_151423D8(arg8 - 0x40);
    spB4 = func_151423D8(arg8);
    sp.u28[4] = 0.0f;
    sp.u28[5] = 0.0f;
    sp.u28[6] = 0.0f;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u78 = 0x9E8;
    sp.u28[10] = arg2;
    sp.u28[11] = arg3;
    sp.u28[12] = arg4;
    sp.u28[1] = 0.2f;
    spBE = (func_150ADA20() % 13U) - 0x34;
    spB0 = func_151423D8(spBE - 0x40);
    spAC = func_151423D8(spBE);
    temp_f2 = (func_150ADA68() * 9.0f) + 3.0f;
    sp.u5C = temp_f2 * spAC * spB8;
    sp.u60 = -temp_f2 * spB0;
    sp.u64 = temp_f2 * spAC * spB4;
    sp.u68 = (func_150ADA68() * 50.0f) + -25.0f;
    sp.u6C = 0.0f;
    sp.u70 = (func_150ADA68() * 50.0f) + -25.0f;
    sp.u7C = (func_150ADA20() % 68U) + 0x26;
    sp.u74 = (func_150ADA68() * -0.1f) + -0.3f;
    sp.u28[0] = 1.0f;
    sp.u28[3] = (func_150ADA68() * 18.800001f) + 5.6f;
    sp.u28[2] = sp.u28[3];
    sp.u7E = 0x1F;
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = 0xFF;
    sp.u89 = 1;
    sp.u8A = 0;
    sp.u8B = 0;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u92 = 0;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 1;
    sp.u9C = 0xFF;
    func_15132FBC(&sp, 3, 0xFF, 0, argE, 0);
    return 1;
}
