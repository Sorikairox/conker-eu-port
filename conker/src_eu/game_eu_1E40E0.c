#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B68D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B69D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B6B84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B6ED8.s")

void func_151B7664(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 *p;
  s32 id;
  s32 t;
  p = *((s32 **) (arg0 + 0x98));
  id = p[0];
  t = id;
  if (arg2 == 0)
  {
    if (t == arg1[0])
    {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (unfilled jr ra delay slot, s69)
      arg0[0x30] = 0;
      *((u16 *) (arg0 + 0x1E)) |= 8;
    }
  }
  else
    if (arg2 == 0x2D)
  {
    t = arg1[0];
    if (t == *p)
    {
      p[0] = arg1[1];
      ((u8 *) p)[4] = ((u8 *) arg1)[9];
      return;
    }
    if (arg1[1] == *p)
    {
      p[0] = t;
      ((u8 *) p)[4] = ((u8 *) arg1)[8];
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B76F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B78D8.s")

s32 func_151B7C28(u8 *arg0, u8 *arg1)
{
  u8 *temp_a2;
  u8 *new_var;
  u8 *temp_v1;
  new_var = *((u8 **) (arg0 + 0x98)); temp_v1 = *((u8 **) (new_var + 4)); temp_a2 = *((u8 **) temp_v1);
  if (*((s32 *) temp_a2) == 0) goto ret0;
  if (temp_v1[4] != temp_a2[0x3B]) { ret0: return 0; }
  *((f32 *) (arg1 + 0)) = *((f32 *) (temp_a2 + 0x14));
  *((f32 *) (arg1 + 4)) = *((f32 *) (temp_a2 + 0x18));
  *((f32 *) (arg1 + 8)) = *((f32 *) (temp_a2 + 0x1C));
  return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7C7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7DA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B7F48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E40E0/func_151B81E8.s")

void func_151B887C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    void (*temp_v1)(u8 *, s32, u8) = D_8008FF38[temp_v0[8]];

    if (temp_v1 != NULL) {
        temp_v1(arg0, arg1, arg2);
    }
}

void func_151B88C8(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *q = *(u8 **)(arg0 + 0x98);
    u8 *p = *(u8 **)(q + 4);
    s32 id;
    if (arg2 == 0) {
        id = arg1[0];
        if (id == *(s32 *)p || p[4] == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    }
}

void func_151B8920(u8 *arg0) {
    struct102 **temp_v0 = *(struct102 ***)(arg0 + 0x98);
    struct102 *temp_a1 = *temp_v0;

    if (temp_a1 != NULL) {
        func_1516972C(temp_a1);
    }
}

void func_151B8950(s32 arg0) {
    func_151B8920(arg0);
    func_15147E64(arg0);
}

void func_151B897C(s32 arg0) {
    func_151B8920(arg0);
    func_15147E98(arg0);
}
