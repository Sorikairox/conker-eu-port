#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15046F70(f32 *, s32, f32, s32);
s32 func_1504715C(s32, struct127 *);
s32 func_15142314(s32, s32, f32 *, u8);

s32 func_15146E00(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 var_a1;

    if ((arg3 != 1) && ((u32)arg3 != 2)) { // fakematch: unsigned cast keeps the compare on a3 (permuter)
        return 0;
    }
    var_a1 = (arg3 == 1) ? 0x13 : 0x17;
    func_15142314(*(s32 *)(arg1 + 0x1D4), var_a1, arg0, arg3);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 10.0f;
    sp2C[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046F70(sp2C, 0, arg0[1] - 50.0f, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15146EE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15147008.s")

void func_15147128(s32 arg0, s32 arg1, s32 arg2) {
    func_15147168(arg0, arg1, arg2, 0);
}

void func_15147148(s32 arg0, s32 arg1, s32 arg2) {
    func_15147168(arg0, arg1, arg2, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15147168.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_151472D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_151473F4.s")

s32 func_15146E00(f32 *, u8 *, s32, u8);
s32 func_1514CBE8(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
void func_151475B0(u8 *arg0, volatile u8 arg1, s32 arg2) {
    f32 sp44[3];
    s16 sp42;
    u8 **q = &arg0; // fakematch: arg0 reloaded from its home slot
    if (*(s32 *)(*q + 0x1D4) != 0) {
        do {} while (0); // fakematch: permuter
        func_15146E00(sp44, *q, 0, arg1);
        sp42 = (func_150ADA20() % 11U) + 5;
        func_1514CBE8(sp44[0], sp44[1], *(s32 *)&sp44[2], func_150ADA68() * 11.0f, 0, 0xFF, sp42, 0x16, 0, 0.0f, 0, 0xFF);
    }
}

void func_15143794(s16, s16, f32, void *);
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_1514766C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
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
        u8 pad98[0xC];
    } sp;
    s32 obj;
    f32 scale;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() & 0xF) + 0x14;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 101U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (func_150ADA68() * 95.0f) + 101.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    func_15143794(arg8, (s16) ((func_150ADA20() % 11U) - 0xB), ((func_150ADA68() * 396.0f) + 202.0f) * 0.01f, sp.u7C);
    sp.u8C = 0xE05;
    sp.u88 = 0.0f;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 0xA;
    sp.u97 = -1;
    sp.u52 = 0x14;
    sp.u54 = 0xC;
    sp.u56 = 0x1B;
    sp.u58 = 1.02f;
    scale = 0.94000006f;
    obj = func_151308E4(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15147888.s")

void func_15141F78(u8, s32 *, f32, s32, f32 *, u8);
void func_15142180(u8, f32 *, s32, f32, f32);
extern u8 (*D_800900BC)(void);
void func_151479E8(u8 *arg0, int arg1, s32 arg2)
{
  f32 sp4C[3];
  s32 sp28[9];
  if (*((s32 *) (arg0 + 0x1D4)))
  {
    if (0) // fakematch: empty if keeps the arg0 reload schedule (DIFF2 without)
    {
    }
    if (func_15146E00(sp4C, arg0, (s32) sp28, arg1) != 0)
    {
      func_15141F78(D_800900BC(), sp28, arg2 * 0.0076923077f, (u8) ((*((f32 *) (arg0 + 0x40))) * 0.7111111f), sp4C, arg1);
      if (arg2 >= 0x73)
      {
        func_15142180(6, sp4C, sp28[6], 1.0f, 1.0f);
      }
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_174610/func_15147B48.s")
