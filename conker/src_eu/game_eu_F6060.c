#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C8850.s")

void func_150C89F4(s32 arg0) {
    if (arg0 == 0) {
        func_150C8850();
    }
}

typedef struct { u8 u0; u8 pad1[3]; s16 u4; u8 pad6[4]; } E10;
extern E10 *D_eu_800BE900;
s32 func_150CE07C(s32);
void func_150C851C(s32 arg0) {
    s32 i;
    s32 v;
    s32 lo;
    s32 range;

    if (D_eu_800BE900 != NULL) {
        func_150CE07C(arg0);
        range = ((arg0 * 50) >> 8) + 50;
        lo = (arg0 * 300) >> 8;
        for (i = 0; i < 10; i++) {
            v = lo;
            v += func_150ADA20() % (u32)range;
            *(s16 *)&D_eu_800BE900[i].pad6[2] = v;
        }
    }
}

typedef struct { s32 *a[2]; } P2;
extern P2 D_eu_80088BB0;
s32 func_1510D66C(s32, s32 *, s32, s32);
Gfx *func_150C8B00(Gfx *gfx) {
    s32 i;
    s32 buf[3];
    s32 lvl;
    P2 tabs = D_eu_80088BB0;

    for (i = 0; i < 10; i++) {
        lvl = D_eu_800BE900[i].u4 >> 8;
        if (lvl < 0) {
            lvl = 0;
        } else if (lvl >= 5) {
            lvl = 4;
        }
        if (D_eu_800BE900[i].u0 >= 2) {
            D_eu_800BE900[i].u0 = 0;
        }
        lvl = func_1510D66C(tabs.a[D_eu_800BE900[i].u0][lvl], buf, 3, 0);
        gSPSegment(gfx++, i + 1, lvl);
    }
    return gfx;
}

u8 *func_15073118(struct127 *, s32, s32, f32, f32, f32, f32, f32, f32, f32, s32);
void func_1503E5F8(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern f32 D_800A08C0;
extern f32 D_800A08C4;
extern f32 D_800A08C8;
extern f32 D_800A08CC;
s32 func_150C8C30(u8 *arg0, struct127 *arg1) {
    u8 *v;
    u8 *e;
    u8 i;
    u8 *p;
    s16 t;
    s32 pad[2]; // fakematch: frame 8 bytes (unknown named locals)
    f32 m[4][4];
    f32 x;
    f32 y;
    f32 z;
    f32 u0;
    f32 u1;
    f32 u2;
    f32 r0;
    f32 r1;
    f32 r2;

    v = *(u8 **)((u8 *)arg1 + 0x2D0);
    if (v == NULL) {
        return 0;
    }
    if ((*(u16 *)((u8 *)arg1 + 0x84) == 0x14 && 10.0f < *(f32 *)(v + 8)) || *(u16 *)((u8 *)arg1 + 0x84) == 0x23) {
        i = D_800BE9C0;
        p = *(u8 **)(arg0 + 0x34);
        p += (i == 0) << 6;
        guMtxL2F(m, (Mtx *)p);
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        m[3][3] = 1.0f;
        func_1503E5F8((f32 *)m, &x, &y, &z, &r0, &r1, &r2, &u0, &u1, &u2);
        e = func_15073118(arg1, -1, 0x4E, 0.0f, 0.0f, 0.0f, 0.0f, D_800A08C0, D_800A08C4, D_800A08C8, 0xC8);
        *(f32 *)(e + 0x14) = x;
        *(f32 *)(e + 0x18) = y;
        *(f32 *)(e + 0x1C) = z;
        *(f32 *)(e + 0xB8) = r0;
        *(f32 *)(e + 0x40) = r1;
        *(f32 *)(e + 0xC4) = r2;
        t = (*(f32 *)(e + 0x40) - 90.0f) * D_800A08CC;
        *(s16 *)(e + 0x76) = t;
        *(s16 *)(e + 0x7A) = t;
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C8DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C8F68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C92B8.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CA0DC.s")

#ifdef NON_MATCHING
extern f32 D_800A0950;
extern f32 D_800A0954;
extern f32 D_800A0958;
extern f32 D_800A0960;
extern f32 D_800A0964;
extern f32 D_800A0968;

void func_150CA2C4(u8 *arg0, u8 *arg1, u8 arg2, s32 arg3) {
    struct {
        s32 u28;
        s32 u2C;
        s32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        s32 u5C;
        u8 pad60[0x8];
        s32 u68;
        u8 pad6C[0x8];
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s32 u84;
        s16 u88;
        s16 u8A;
        s8 u8C;
        u8 pad8D[0x3];
        s32 u90;
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        s8 u99;
        s8 u9A;
        s8 u9B;
        s8 u9C;
        u8 pad9D[0x1];
        s8 u9E;
        u8 pad9F[0x1];
        s32 uA0;
        s8 uA4;
        u8 padA5[0x1];
        s16 uA6;
        s16 uA8;
    } sp;
    s32 sp20;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f4;

    func_150CD2A0(arg0, &sp.u30, &sp.u2C, &sp.u28);
    (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)arg1 + 0));
    (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
    (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
    sp.u50 = 1.0f;
    sp.u54 = 1.0f;
    sp.u58 = 1.0f;
    sp.u84 = 0x29E8;
    sp.u44 = func_150ADA68() * 360.0f;
    sp.u48 = func_150ADA68() * 360.0f;
    temp_f18 = func_150ADA68() * 360.0f;
    sp.u8A = 0x20;
    sp.u38 = D_800A0950;
    sp.u4C = temp_f18;
    sp.u78 = 0.0f;
    sp.u34 = 1.0f;
    sp20 = func_150ADA20();
    func_15143794((s16) arg2, (s16) (((u32) sp20 % 26U) - 0x2D), ((func_150ADA68() * 81.0f) + 60.0f) * (*(f32 *)((u8 *)arg0 + 0x20)) * D_800A0954, &sp.u68);
    sp.u74 = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A0958;
    sp.u7C = ((func_150ADA68() * 260.0f) + -130.0f) * D_800A0958;
    sp.u88 = (func_150ADA20() % 41U) + 0x28;
    sp.u80 = ((func_150ADA68() * D_800A0960) + D_800A0964) * D_800A0968;
    temp_f4 = func_150ADA68() * 400.0f;
    sp.u8C = 0;
    sp.u90 = 0;
    temp_f2 = (temp_f4 + 199.0f) * D_800A0968;
    sp.u3C = temp_f2;
    sp.u40 = temp_f2;
    sp.u94 = (func_150ADA20() % 101U) + 0x9B;
    sp.u95 = 7;
    sp.u96 = 0;
    sp.u97 = 0;
    sp.u98 = 0;
    sp.u99 = 0;
    sp.u9A = 0;
    sp.u9B = 0;
    sp.u9C = 0;
    sp.u9E = 2;
    sp.uA0 = 0;
    sp.uA4 = 0;
    sp.uA6 = 0x20;
    sp.uA8 = 7;
    func_15132FBC(&sp.u34, 3, 0xFF, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CA2C4.s")
#endif
s32 func_150CA57C(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * D_800BE9A4) + (*(f32 *)(arg0 + 0x5C) * D_800BE9A4 * D_800BE9A4 * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CA150.s")

#ifdef NON_MATCHING
void func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#else
s32 func_1514CBE8(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#endif

void func_150CAE30(u8 *arg0) {
    s16 sp3E;

    sp3E = (func_150ADA20() % 21U) + 0xA;
#ifdef NON_MATCHING
    func_1514CBE8((*(f32 *)arg0), (*(f32 *)((u8 *)arg0 + 4)), (*(f32 *)((u8 *)arg0 + 8)), (func_150ADA68() * 59.0f) + 170.0f, 0, 0xFF, (s32) sp3E, 0x13, 0, 0.0f, 0, 0xFF);
#else
    func_1514CBE8((*(f32 *)arg0), (*(f32 *)((u8 *)arg0 + 4)), (*(s32 *)((u8 *)arg0 + 8)), (func_150ADA68() * 59.0f) + 170.0f, 0, 0xFF, (s32) sp3E, 0x13, 0, 0.0f, 0, 0xFF);
#endif
}

s32 func_150CAED0(u8 *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x1C));
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) (*(u8 *)((u8 *)arg0 + 0x28))) {
            (*(u8 *)((u8 *)arg0 + 0x28)) = (u8) temp_v1;
        }
    }
    return 1;
}

void func_15143794(s16, s16, f32, void *);
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_150CAF04(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
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
        s32 u7C[3];
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

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() % 26U) + 0x19;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 156U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (func_150ADA68() * 401.0f) + 800.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    func_15143794(arg8, (s16) ((func_150ADA20() % 12U) - 0x15), ((func_150ADA68() * 300.0f) + 498.0f) * 0.1f, sp.u7C);
    sp.u8C = 0xE05;
    sp.u88 = 0.0f;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 9;
    sp.u97 = -1;
    sp.u52 = 0x19;
    sp.u54 = 0xA;
    sp.u56 = 0x20;
    sp.u58 = 1.04f;
    scale = 0.95100003f;
    obj = func_151308E4(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

s32 func_150CB128(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

void func_15143794(s16, s16, f32, void *);

s32 func_150CB2D0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        f32 u28[13];
        s32 u5C;
        u8 pad60[0x8];
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
        s8 u88;
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

    sp.u28[10] = arg2;
    sp.u28[11] = arg3;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u78 = 0x29E8;
    sp.u28[4] = 0.0f;
    sp.u28[5] = 0.0f;
    sp.u28[6] = 0.0f;
    sp.u6C = 0.0f;
    sp.u28[0] = 1.0f;
    sp.u7E = 0x20;
    sp.u28[12] = arg4;
    sp.u28[1] = 0.2f;
    func_15143794(arg8, (s16) (((u32) func_150ADA20() % 21U) - 0x28), ((func_150ADA68() * 204.0f) + 500.0f) * 0.1f, &sp.u5C);
    sp.u68 = ((func_150ADA68() * 260.0f) + -130.0f) * 0.1f;
    sp.u70 = ((func_150ADA68() * 260.0f) + -130.0f) * 0.1f;
    sp.u7C = (func_150ADA20() % 51U) + 0x32;
    sp.u74 = ((func_150ADA68() * 1008.0f) + -3085.0f) * 0.001f;
    sp.u28[3] = ((func_150ADA68() * 601.0f) + 200.0f) * 0.001f;
    sp.u28[2] = sp.u28[3];
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = (func_150ADA20() % 76U) + 0xB4;
    sp.u89 = 4;
    sp.u8A = 0;
    sp.u8B = 0;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u92 = 2;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 0x20;
    sp.u9C = 7;
    func_15132FBC(&sp, 3, 0xFF, 0, (s32) argE, 0);
    return 1;
}

s32 func_150CB508(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * D_800BE9A4) + (*(f32 *)(arg0 + 0x5C) * D_800BE9A4 * D_800BE9A4 * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}
