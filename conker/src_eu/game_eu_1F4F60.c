#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C7750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C7B1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8448.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8880.s")

void func_151C8C24(u8 *arg0, s32 arg1) {
    s32 sp18[2];
    if (arg0 != NULL) {
        sp18[0] = (s32)arg0;
        sp18[1] = arg1;
        func_151403A8(sp18, 0x20);
    }
}

s32 func_151C8D90(s32, u8 *);
void func_151C8F4C(s32, u8 *);
void func_151C8C5C(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v;
    u8 **q = &arg0;
    switch (arg2) {
    case 0x20:
        v = (*q) + 0x110;
        if ((v[0x86] & 0x10) && (*(s32 *)(v + 0x28) == arg1[1])) {
            if (func_151C8D90(arg1[0], (*q))) {
                func_151C8F4C(arg1[0], (*q));
            }
        }
        break;
    case 0x3A:
        v = (*q) + 0x110;
        if (*(s32 *)(v + 0x28) == arg1[0]) {
            switch (((u8 *)arg1)[4]) {
            case 0: v[0x86] |= 2; break;
            case 1: v[0x86] &= ~2; break;
            case 2: func_151C8F4C(0, (*q)); break;
            }
        }
        break;
    }
}

s32 func_151C8D5C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    u8 *p;
    s16 *q;
    p = *(u8 **)(arg0 + 0x18);
    q = arg6;
    if (!(p[0x86] & 2)) {
        *q = 0;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8D90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8F4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C957C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9748.s")

void func_151C9A84(struct210 *arg0) {
    u8 *p;
    struct102 *a;
    struct210 **pa = &arg0; // fakematch: arg0 address taken keeps it in its home slot

    p = (u8 *)*pa + 0x110;
    if (*(s32 *)((u8 *)*pa + 0x13C) != 0) {
        func_1516972C(*(struct102 **)(p + 0x2C));
        func_1000FD38(func_151C8D5C, p, 0);
    }
    p = (u8 *)*pa;
    a = *(struct102 **)(p + 0x144);
    p += 0x110;
    if (a != NULL) {
        func_1516972C(a);
    }
    if (*(struct102 **)(p + 0x38) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x38));
    }
    if (*(struct102 **)(p + 0x3C) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x3C));
    }
    if (*(struct102 **)(p + 0x40) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x40));
    }
    if (*(struct102 **)(p + 0x44) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x44));
    }
    if (*(struct102 **)(p + 0x48) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x48));
    }
    if (*(struct102 **)(p + 0x4C) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x4C));
    }
    if (*(struct102 **)(p + 0x50) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x50));
    }
    func_1513CA6C(arg0);
}

void func_151C9B88(struct210 *arg0) {
    u8 *p;
    struct102 *a;
    struct210 **pa = &arg0; // fakematch: arg0 address taken keeps it in its home slot

    p = (u8 *)*pa + 0x110;
    if (*(s32 *)((u8 *)*pa + 0x13C) != 0) {
        func_1516972C(*(struct102 **)(p + 0x2C));
        func_1000FD38(func_151C8D5C, p, 0);
    }
    p = (u8 *)*pa;
    a = *(struct102 **)(p + 0x144);
    p += 0x110;
    if (a != NULL) {
        func_1516972C(a);
    }
    if (*(struct102 **)(p + 0x38) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x38));
    }
    if (*(struct102 **)(p + 0x3C) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x3C));
    }
    if (*(struct102 **)(p + 0x40) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x40));
    }
    if (*(struct102 **)(p + 0x44) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x44));
    }
    if (*(struct102 **)(p + 0x48) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x48));
    }
    if (*(struct102 **)(p + 0x4C) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x4C));
    }
    if (*(struct102 **)(p + 0x50) != NULL) {
        func_1516972C(*(struct102 **)(p + 0x50));
    }
    func_1513CAA0(arg0);
}

s32 func_151C9C8C(u8 *arg0, s32 arg1) {
    s32 *q = &arg1; // fakematch: arg1 home store
    u8 *p = *(u8 **)(arg0 + 0x170) + 0x110;
    if (p[0x86] & 2) {
        return 1;
    }
    return 0;
}

void func_151C9CBC(s32 arg0, s32 arg1) {
    s32 tmp[2];
    tmp[0] = arg1;
    *(u8 *)(tmp + 1) = arg0;
    func_151403A8(tmp, 0x3A);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9740.s")

s32 func_1504715C(s32 *, struct127 *);
void func_151AC3F0(struct17 *, s32 *, s32, u8, s32);
void func_151CA070(struct127 *arg0, u8 arg1, s32 arg2) {
    struct17 pos;
    s32 sp20[9];

    pos.unk0 = *(f32 *)((u8 *)arg0 + 0x14);
    pos.unk4 = *(f32 *)((u8 *)arg0 + 0x180) + 2.0f;
    pos.unk8 = *(f32 *)((u8 *)arg0 + 0x1C);
    func_1504715C(sp20, arg0);
    func_151AC3F0(&pos, sp20, 2, arg1, arg2);
}

s32 func_151CA0E0(u8 *arg0)
{
  u8 *new_var2;
  u8 *new_var;
  new_var = arg0;
  new_var2 = *((u8 **) (new_var + 0x18));
  if ((*((u8 *) (new_var2 + 0x6F))) == 0)
  {
    *((s8 *) ((*((u8 **) (arg0 + 0x14))) + 9)) = 0;
  }
  else
  {
    *((s8 *) ((*((u8 **) (new_var + 0x14))) + 9)) = 1;
  }
  return 1;
}

s32 func_151CA114(u8 *arg0, s8 *arg1)
{
  u8 *new_var;
  new_var = *((u8 **) (((u8 *) arg0) + 0x188)); // fakematch: pointer in a named local (permuter)
  if ((*((u8 *) (((u8 *) new_var) + 0x6F))) == 0)
  {
    *arg1 = 1;
  }
  else
  {
    *((s32 *) (((u8 *) arg0) + 0x58)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x58))) & (~2));
    *arg1 = 0;
  }
  return 1;
}
