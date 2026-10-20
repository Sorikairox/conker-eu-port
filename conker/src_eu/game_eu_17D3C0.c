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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515128C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515176C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15151FA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_151522DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152A90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15152DE4.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15153F24.s")

void func_1515423C();

void func_151541F4(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x2C];
    func_1514FBB0(arg0, sp24);
    func_1515423C(sp24, arg1, arg2, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_1515423C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154488.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17D3C0/func_15154FF8.s")
