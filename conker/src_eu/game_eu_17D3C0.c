#include <ultra64.h>
#include "functions.h"
#include "variables.h"


f32 func_15144A74(u8 *, u8 *);
s32 func_15144E80(u8 *, u8 *, u8 *, u8 *);

void func_1514FBB0(u8 *arg0, u8 *arg1) {
    arg1[0] = 2;
    *(f32 *)(arg1 + 0x28) = *(f32 *)(arg0 + 0x20);
    if ((func_15144E80(arg0 + 0xC, arg1 + 0x10, arg1 + 0x1C, arg1 + 4) != 0) && (func_15144A74(arg1 + 4, arg0) < 0.0f)) {
        *(f32 *)(arg1 + 4) = -*(f32 *)(arg1 + 4);
        *(f32 *)(arg1 + 8) = -*(f32 *)(arg1 + 8);
        *(f32 *)(arg1 + 0xC) = -*(f32 *)(arg1 + 0xC);
    }
}

s32 func_15145128(u8 *, u8 *, void *, void *);
s32 func_15146078(u8 *, s32 *, s32 *);
s32 func_1514FC58(u8 *arg0) {
    s32 f;
    f = arg0[0];
    if (!(f & 1)) {
        if (func_15145128(arg0 + 4, arg0 + 4, 0, 0) == 0) {
            return 0;
        }
        *(f32 *)(arg0 + 4) *= 1000.0f;
        f = arg0[0] |= 1;
        *(f32 *)(arg0 + 8) *= 1000.0f;
        *(f32 *)(arg0 + 0xC) *= 1000.0f;
    }
    if (!(f & 2)) {
        if (func_15146078(arg0 + 4, (s32 *)(arg0 + 0x10), (s32 *)(arg0 + 0x1C)) == 0) {
            return 0;
        }
        f = arg0[0] |= 6;
    }
    if (!(f & 4)) {
        if (func_15145128(arg0 + 0x10, arg0 + 0x10, 0, 0) == 0) {
            return 0;
        }
        if (func_15145128(arg0 + 0x1C, arg0 + 0x1C, 0, 0) == 0) {
            return 0;
        }
        arg0[0] |= 4;
    }
    return 1;
}

s32 func_15143874(s16, f32, f32 *, f32 *);

f32 *func_1514FD78(f32 *arg0, f32 arg1, f32 *arg2) {
    f32 s;
    f32 c;

    func_15143874(func_150ADA20() & 0xFF, arg0[10] * func_150ADA68(), &c, &s);
    arg2[0] = (arg0[1] + (arg0[7] * s + arg0[4] * c)) * arg1;
    arg2[1] = (arg0[2] + (arg0[8] * s + arg0[5] * c)) * arg1;
    arg2[2] = (arg0[3] + (arg0[9] * s + arg0[6] * c)) * arg1;
    return arg2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1514FE68.s")

s32 func_15146078(u8 *, s32 *, s32 *);
s32 func_1514FE68(u8 *, u8 *, s32 *, s32 *, f32, s32, s32);
void func_15150108(u8 *arg0, u8 arg1, s32 arg2) {
    s32 sp34[3];
    s32 sp28[3];
    if (func_15146078(arg0, sp34, sp28) != 0) {
        func_1514FE68(arg0 + 0x10, arg0, sp34, sp28, (*(f32 *)((u8 *)arg0 + 0xC)), (s32) arg1, arg2);
    }
}

s32 func_15145128(u8 *, u8 *, void *, void *);
void func_1515016C(u8 *arg0, u8 arg1, s32 arg2) {
    f32 a[3];
    s32 a1;
    s32 a2;
    f32 b[3];
    s32 b1;
    s32 b2;
    f32 c[3];
    s32 c1;
    s32 c2;
    if (func_15144E80(arg0 + 0xC, (u8 *)a, (u8 *)b, (u8 *)c) != 0) {
        func_15145128((u8 *)a, (u8 *)a, &a1, &a2);
        func_15145128((u8 *)b, (u8 *)b, &b1, &b2);
        func_15145128((u8 *)c, (u8 *)c, &c1, &c2);
        if (func_15144A74((u8 *)c, arg0) < 0.0f) {
            c[0] = -c[0];
            c[1] = -c[1];
            c[2] = -c[2];
        }
        func_1514FE68(arg0 + 0x24, (u8 *)c, (s32 *)a, (s32 *)b, *(f32 *)(arg0 + 0x20), arg1, arg2);
    }
}

s32 func_151A2FC4(u8 *, s16, s16, f32, f32, f32, s32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
void func_15150258(u8 *arg0, u8 arg1, s32 arg2) {
    s32 n;
    n = *(s32 *)(arg0 + 8) + (func_150ADA20() % (u32)(*(s32 *)(arg0 + 0xC) + 1));
    while (n != 0) {
        func_151A2FC4(arg0 + 0x10,
            *(s16 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 2) + 1)),
            *(s16 *)(arg0 + 4) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 6) + 1)),
            *(f32 *)(arg0 + 0x1C) + *(f32 *)(arg0 + 0x20) * func_150ADA68(),
            *(f32 *)(arg0 + 0x24) + *(f32 *)(arg0 + 0x28) * func_150ADA68(),
            *(f32 *)(arg0 + 0x2C) + *(f32 *)(arg0 + 0x30) * func_150ADA68(),
            *(s32 *)(arg0 + 0x34) + (func_150ADA20() % (u32)(*(s32 *)(arg0 + 0x38) + 1)),
            *(f32 *)(arg0 + 0x3C), *(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0x44), *(f32 *)(arg0 + 0x48),
            *(s16 *)(arg0 + 0x4C), *(s16 *)(arg0 + 0x4E), *(s16 *)(arg0 + 0x50), *(s16 *)(arg0 + 0x52),
            *(s16 *)(arg0 + 0x54), *(s16 *)(arg0 + 0x56), *(s8 *)(arg0 + 0x58), arg1, arg2);
        n--;
    }
}

void func_1514FBB0();
void func_151504B4();

void func_1515046C(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    func_1514FBB0(arg0, sp24);
    func_151504B4(sp24, arg1, arg2, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151504B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151506E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15150970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15150D7C.s")

void func_15143794(s16, s16, f32, void *);
s32 func_150ACEA0(f32, f32, s32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
s32 func_15145C90(s32);

void func_1515128C(u8 *arg0, u8 arg1, s32 arg2) {
    s32 n;
    f32 spC0[3];
    u8 spAC[0x14];
    f32 spA0[3];
    f32 sp9C;
    s32 sp98;
    u8 *hit;

    n = *(s32 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s32 *)(arg0 + 4) + 1));
    while (n != 0) {
        func_15143794(*(s16 *)(arg0 + 0x14) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1)),
            *(s16 *)(arg0 + 0x18) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1A) + 1)), 100.0f, spC0);
        hit = spAC; // fakematch: named pointer to spAC (permuter), both calls use it
        if (func_150ACEA0(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0xC), *(s32 *)(arg0 + 0x10), spC0[0], spC0[1], spC0[2], 0,
                hit, &spA0[0], &spA0[1], &spA0[2], &sp9C, &sp98, 0, 0.0f) != 0) {
            if (func_15145C90(sp98) != 0) {
                if (sp9C < *(f32 *)(arg0 + 0x1C)) {
                    func_151D9B8C(*(u8 *)(arg0 + 0x2C), *(f32 *)(arg0 + 0x20) + *(f32 *)(arg0 + 0x24) * func_150ADA68(),
                        (func_150ADA20() % 156U) + 100, (s32)hit, (struct17 *)spA0,
                        *(s16 *)(arg0 + 0x28) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x2A) + 1)),
                        1, 1, 1, arg1, arg2);
                }
            }
        }
        n--;
    }
}

void func_15143794(s16, s16, f32, void *);
s32 func_1518A930(u8 *, f32 *, f32, f32 *, f32 *, f32, f32, u8, s32, u8, s32, u8, s32);

void func_15151500(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    f32 spBC[3];
    f32 d;
    s32 n;
    f32 spA8[3];
    f32 sp9C[3];

    d = 2.0f * *(f32 *)(arg0 + 0x2C);
    spBC[1] = 0.0f;
    n = func_150ADA20();
    n = *(s32 *)(arg0 + 0) + (n % (u32)(*(s32 *)(arg0 + 4) + 1));
    while (n != 0) {
        spA8[0] = func_150ADA68() * 360.0f;
        spA8[1] = func_150ADA68() * 360.0f;
        spA8[2] = func_150ADA68() * 360.0f;
        func_15143794(*(s16 *)(arg0 + 0x1C) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1E) + 1)),
            *(s16 *)(arg0 + 0x20) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x22) + 1)),
            *(f32 *)(arg0 + 0x24) + *(f32 *)(arg0 + 0x28) * func_150ADA68(), sp9C);
        spBC[0] = func_150ADA68() * d - *(f32 *)(arg0 + 0x2C);
        spBC[2] = func_150ADA68() * d - *(f32 *)(arg0 + 0x2C);
        func_1518A930(arg0 + 8, spA8, *(f32 *)(arg0 + 0x14) + *(f32 *)(arg0 + 0x18) * func_150ADA68(), sp9C, spBC,
            *(f32 *)(arg0 + 0x30) + *(f32 *)(arg0 + 0x34) * func_150ADA68(), *(f32 *)(arg0 + 0x38),
            *(u8 *)(arg0 + 0x3C), *(s16 *)(arg0 + 0x3E) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x40) + 1)),
            arg1, 0, arg2, arg3);
        n--;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515176C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151FA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151522DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152A90.s")

void func_15143794(s16, s16, f32, void *);
void func_150CD3C0(void *, u8, u8);
extern void (*D_8008B000[])(u8 *);
typedef struct { f32 v[3]; } V3_2de4;
typedef struct {
    V3_2de4 v;
    f32 p[3];
    f32 a;
    f32 b;
    u8 c[4];
    s32 n;
    f32 x;
    f32 y;
    f32 z;
} S_2de4;

void func_15152DE4(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused slot above the struct (frame size)
    S_2de4 sp;
    s32 n;
    s8 i;

    n = func_150ADA20();
    n = *(s32 *)(arg0 + 0) + (n % (u32)(*(s32 *)(arg0 + 4) + 1));
    sp.v = *(V3_2de4 *)(arg0 + 8);
    sp.a = *(f32 *)(arg0 + 0x24);
    sp.z = *(f32 *)(arg0 + 0x48);
    while (n != 0) {
        func_15143794(*(s16 *)(arg0 + 0x14) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1)),
            *(s16 *)(arg0 + 0x18) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x1A) + 1)),
            *(f32 *)(arg0 + 0x1C) + *(f32 *)(arg0 + 0x20) * func_150ADA68(), sp.p);
        sp.b = *(f32 *)(arg0 + 0x28) + *(f32 *)(arg0 + 0x2C) * func_150ADA68();
        sp.n = *(s16 *)(arg0 + 0x32) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x34) + 1));
        sp.x = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x40) * func_150ADA68();
        sp.y = *(f32 *)(arg0 + 0x3C) + *(f32 *)(arg0 + 0x44) * func_150ADA68();
        i = *(s8 *)(arg0 + 0x30);
        if (i != 0xFFFFFFFF) { // unsigned compare: "!= -1" gives beq v0,fp (permuter found -1U)
            D_8008B000[i](sp.c);
        } else {
            sp.c[0] = 0xFF;
            sp.c[1] = 0xFF;
            sp.c[2] = 0xFF;
            sp.c[3] = 0xFF;
        }
        func_150CD3C0(&sp, arg1, (u8)arg2);
        n--;
    }
}

extern u8 D_800A63C0[][3];

void func_1515302C(u8 *arg0) {
    u8 i = func_150ADA20() % 5U;
    u8 *e = D_800A63C0[i];

    arg0[3] = func_150ADA20() % 101U + 0x9B;
    arg0[0] = e[0];
    arg0[1] = e[1];
    arg0[2] = e[2];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151530A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151534E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15153808.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15153BA4.s")

typedef struct { f32 v[3]; } V3_3f24;
typedef struct {
    V3_3f24 pos;
    f32 vel[3];
    f32 a;
    f32 b;
    u8 c[9];
    s16 d;
    u16 e;
    f32 f;
    s8 g;
    s16 h;
    s16 i;
} S_3f24;
#ifdef NON_MATCHING
s32 func_15156700(S_3f24 *, u8, s32, u8, s32);
#else
void func_15156700(S_3f24 *, u8, s32, u8, s32);
#endif

void func_15153F24(u8 *arg0, u8 arg1) {
    S_3f24 sp;
    s32 n;
    s16 a;
    s16 b;
    f32 sb;
    f32 cb;
    f32 sa;
    f32 ca;

    n = *(s16 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 2) + 1));
    sp.pos = *(V3_3f24 *)(arg0 + 4);
    sp.c[0] = *(u8 *)(arg0 + 0x28);
    sp.c[1] = *(u8 *)(arg0 + 0x29);
    sp.c[2] = *(u8 *)(arg0 + 0x2A);
    sp.c[3] = *(u8 *)(arg0 + 0x2B);
    sp.c[4] = *(u8 *)(arg0 + 0x2C);
    sp.c[5] = *(u8 *)(arg0 + 0x2D);
    sp.c[6] = *(u8 *)(arg0 + 0x2E);
    sp.c[7] = *(u8 *)(arg0 + 0x2F);
    sp.c[8] = *(u8 *)(arg0 + 0x30);
    sp.e = *(u16 *)(arg0 + 0x36);
    sp.h = *(s16 *)(arg0 + 0x42);
    sp.i = *(s16 *)(arg0 + 0x44);
    while (n != 0) {
        a = *(s16 *)(arg0 + 0x10) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x14) + 1));
        b = *(s16 *)(arg0 + 0x12) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x16) + 1));
        sb = func_151423D8(b);
        cb = func_151423D8(b - 0x40);
        sa = func_151423D8(a);
        ca = func_151423D8(a - 0x40);
        sp.vel[0] = 10.0f * sb * ca;
        sp.vel[1] = -10.0f * cb;
        sp.vel[2] = 10.0f * sb * sa;
        sp.a = *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * func_150ADA68();
        sp.b = *(f32 *)(arg0 + 0x20) + *(f32 *)(arg0 + 0x24) * func_150ADA68();
        sp.d = *(s16 *)(arg0 + 0x32) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x34) + 1));
        sp.f = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x3C) * func_150ADA68();
        sp.g = *(u8 *)(arg0 + 0x40) + (func_150ADA20() % (u32)(*(u8 *)(arg0 + 0x41) + 1));
        func_15156700(&sp, *(u8 *)(arg0 + 0x46), 0, arg1, 0);
        n--;
    }
}

void func_1515423C(u8 *, s32, s32, u8, s32);

void func_151541F4(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    func_1514FBB0(arg0, sp24);
    func_1515423C(sp24, arg1, arg2, arg3, arg4);
}

s32 func_151DA6F8(struct17 *, s32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_1515423C(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 n;
    f32 spA8[3];

    if (func_1514FC58(arg0) != 0) {
        n = func_150ADA20();
        n = *(s16 *)((u8 *)arg1 + 0x24) + (n % (u32)(*(s16 *)((u8 *)arg1 + 0x26) + 1));
        while (n != 0) {
            func_1514FD78((f32 *)arg0, *(f32 *)((u8 *)arg1 + 0x1C) + *(f32 *)((u8 *)arg1 + 0x20) * func_150ADA68(), spA8);
            func_151DA6F8((struct17 *)arg1, (s32 *)spA8,
                *(f32 *)((u8 *)arg1 + 0x14) + *(f32 *)((u8 *)arg1 + 0x18) * func_150ADA68(),
                *(s16 *)((u8 *)arg1 + 0x2C) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2E) + 1)),
                *(s16 *)((u8 *)arg1 + 0x30) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x32) + 1)),
                *(f32 *)((u8 *)arg1 + 0xC) + *(f32 *)((u8 *)arg1 + 0x10) * func_150ADA68(),
                *(s16 *)((u8 *)arg1 + 0x28) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2A) + 1)),
                func_150ADA68() < *(f32 *)((u8 *)arg1 + 0x38),
                1.7f, 1.7f, 1, *(u8 *)((u8 *)arg1 + 0x34), arg2,
                *(s16 *)((u8 *)arg1 + 0x3C), *(s16 *)((u8 *)arg1 + 0x3E), *(s32 *)((u8 *)arg1 + 0x40), arg3, arg4);
            n--;
        }
    }
}

void func_15143794(s16, s16, f32, void *);
s32 func_151DA6F8(struct17 *, s32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_15154488(struct_eu_15154488 *arg0, struct17 *arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 n;
    s32 spA8[3];

    n = *(s16 *)((u8 *)arg1 + 0x24) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x26) + 1));
    while (n != 0) {
        func_15143794(arg0->unk0 + (func_150ADA20() % (u32)(arg0->unk2 + 1)),
            arg0->unk4 + (func_150ADA20() % (u32)(arg0->unk6 + 1)),
            *(f32 *)((u8 *)arg1 + 0x1C) + *(f32 *)((u8 *)arg1 + 0x20) * func_150ADA68(), spA8);
        func_151DA6F8(arg1, spA8,
            *(f32 *)((u8 *)arg1 + 0x14) + *(f32 *)((u8 *)arg1 + 0x18) * func_150ADA68(),
            *(s16 *)((u8 *)arg1 + 0x2C) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2E) + 1)),
            *(s16 *)((u8 *)arg1 + 0x30) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x32) + 1)),
            *(f32 *)((u8 *)arg1 + 0xC) + *(f32 *)((u8 *)arg1 + 0x10) * func_150ADA68(),
            *(s16 *)((u8 *)arg1 + 0x28) + (func_150ADA20() % (u32)(*(s16 *)((u8 *)arg1 + 0x2A) + 1)),
            func_150ADA68() < *(f32 *)((u8 *)arg1 + 0x38),
            1.7f, 1.7f, 1, *(u8 *)((u8 *)arg1 + 0x34), arg2,
            *(s16 *)((u8 *)arg1 + 0x3C), *(s16 *)((u8 *)arg1 + 0x3E), *(s32 *)((u8 *)arg1 + 0x40), arg3, arg4);
        n--;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154728.s")

s32 func_15154A9C(u8 *arg0) {
    f32 *p;
    f32 s;
    f32 t;
    p = (f32 *)(arg0 + 0x170);
    s = *(f32 *)(arg0 + 0x178) * sqrtf(p[0]);
    *(f32 *)(arg0 + 0x18) = s;
    if (!(*(u8 *)(arg0 + 0x184) & 1)) {
        *(f32 *)(arg0 + 0x1C) = s;
    }
    do { t = p[0]; *(s8 *)(arg0 + 0x70) = (s8)(u32)(p[3] - p[4] * t * t); } while (0); // fakematch: same-line do-while(0) (permuter) keeps &D_800BE9A4 in v1 from the start
    p[0] += D_800BE9A4;
    if (p[1] < p[0]) {
        return 0;
    }
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}

void func_15143794(s16, s16, f32, void *);
void func_151C64F4(s32, void *, f32, s32, s32, s32, f32, s32, s32, u8, s32);
void func_15154BF4(u8 *arg0, u8 arg1, s32 arg2) {
    s32 sp80[4];
    s32 n;
    n = *(s16 *)(arg0 + 0) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 2) + 1));
    if (n > 0) {
        do {
            func_15143794(func_150ADA20() & 0xFF, *(s16 *)(arg0 + 0xA) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0xE) + 1)),
                *(f32 *)(arg0 + 0x10) + *(f32 *)(arg0 + 0x14) * func_150ADA68(), sp80);
            func_151C64F4(*(s32 *)(arg0 + 4), sp80, *(f32 *)(arg0 + 0x18) + *(f32 *)(arg0 + 0x1C) * func_150ADA68(),
                *(s32 *)(arg0 + 0x20),
                *(u8 *)(arg0 + 0x24) + (func_150ADA20() % (u32)(*(u8 *)(arg0 + 0x25) + 1)),
                *(s16 *)(arg0 + 0x26) + (func_150ADA20() % (u32)(*(s16 *)(arg0 + 0x28) + 1)),
                *(f32 *)(arg0 + 0x2C) + *(f32 *)(arg0 + 0x30) * func_150ADA68(),
                func_150ADA68() < *(f32 *)(arg0 + 0x34), *(s32 *)(arg0 + 0x38), arg1, arg2);
            n--;
        } while (n > 0);
    }
}

typedef struct { f32 x, y, z; } V3;

s32 func_15154DF4(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, s32 arg5)
{
  s32 obj;
  struct 
  {
    f32 u2C[15];
    s32 u68;
    u8 pad6C[0x8];
    f32 u74;
    f32 u78;
    f32 u7C;
    f32 u80;
    f32 u84;
    f32 u88;
    f32 u8C;
    s32 u90;
    s16 u94;
    s16 u96;
    s8 u98;
    u8 pad99[0x3];
    s32 u9C;
    u8 uA0;
    s8 uA1;
    s8 uA2;
    s8 uA3;
    s8 uA4;
    s8 uA5;
    s8 uA6;
    s8 uA7;
    s8 uA8;
    u8 padA9[0x1];
    s8 uAA;
    u8 padAB[0x1];
    s32 uAC;
    s8 uB0;
    u8 padB1[0x1];
    s16 uB2;
    s16 uB4;
    u8 padB6[0x6];
  } sp;
  f32 temp_f0;
  if (arg1 <= 0.0f)
  {
    return 0;
  }
  sp.u2C[0] = arg1;
  sp.u2C[1] = arg2;
  sp.u2C[3] = 0.0f;
  sp.u2C[7] = 0.0f;
  sp.u2C[8] = 0.0f;
  sp.u2C[5] = 1.0f;
  sp.u2C[6] = 1.0f;
  sp.u2C[2] = arg3;
  sp.u2C[4] = 3.1415927f / arg1;
  sp.u2C[9] = func_150ADA68() * 360.0f;
  sp.u2C[10] = func_150ADA68() * 360.0f;
  temp_f0 = func_150ADA68();
  sp.u2C[12] = 1.0f;
  sp.u2C[13] = 1.0f;
  sp.u2C[14] = 1.0f;
  sp.u2C[11] = temp_f0 * 360.0f;
  *((V3 *) (&sp.u68)) = *((V3 *) arg0);
  sp.u74 = 0.0f;
  sp.u78 = 0.0f;
  sp.u7C = 0.0f;
  temp_f0 = func_150ADA68();
  sp.u84 = 0.0f;
  sp.u80 = (temp_f0 * 26.296001f) + (-13.148001f);
  sp.u88 = (func_150ADA68() * 26.296001f) + (-13.148001f);
  sp.u8C = 0.0f;
  sp.u90 = 0x140;
  sp.u96 = 0x55;
  sp.u98 = 0;
  sp.u9C = 0;
  sp.uA0 = 0xFF;
  sp.uA1 = 0x12;
  sp.uA2 = 0;
  sp.uA3 = 0;
  sp.uA4 = 0;
  sp.uA5 = 0;
  sp.uA6 = 0;
  sp.uA7 = 0;
  sp.uA8 = 2;
  sp.uAA = 0;
  sp.uAC = 0;
  sp.uB0 = 0;
  sp.uB2 = 1;
  sp.uB4 = 0xFF;
  sp.u94 = 0x12C;
  obj = func_15132FBC((u8 *) (&sp.u2C[5]), 0, 0, 0x14, arg4, arg5);
  if (obj != 0)
  {
    memcpy(obj + 0x170, &sp, 0x14);
  }
  return obj;
}

s32 func_15154FF8(u8 *arg0) {
    f32 *p;
    f32 s;

    p = (f32 *)(arg0 + 0x170);
    s = sinf(p[3]);
    *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x1C) = p[1] * s;
    *(s8 *)(arg0 + 0x70) = (s8)(u32)(((u32)p[2] & 0xFF) * s);
    p[0] -= D_800BE9A4;
    if (p[0] <= 0.0f) {
        return 0;
    }
    p[3] += p[4] * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}
