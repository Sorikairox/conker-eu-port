#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_15108850.s")

s32 func_15109100(u8 *);
s32 func_15109140(u8 *);

s32 func_15109034(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *new_var;

    // permuter: the offset is read through a pointer local and added with +=
    temp_s0_2 = arg0 + 0x50;
    temp_s0 = arg0;
    temp_s0 += *(s32 *)temp_s0_2;
    temp_s0_2 = temp_s0 + 0xF8;
    *(f32 *)(temp_s0_2 + 8) = *(f32 *)(temp_s0 + 0x100) + (0.0857f * D_800BE9A4);
    *(f32 *)(temp_s0_2 + 0xC) = *(f32 *)(temp_s0_2 + 0xC) + (0.0783f * D_800BE9A4);
    temp_s0 = temp_s0_2;
    *(f32 *)(temp_s0 + 8) = func_15144B68(*(f32 *)(temp_s0 + 8));
    *(f32 *)(temp_s0 + 0xC) = func_15144B68(*(f32 *)(temp_s0 + 0xC));
    *(f32 *)(temp_s0 + 0) = sinf(*(f32 *)(temp_s0 + 8)) * 7.1050005f;
    new_var = temp_s0;
    *(f32 *)(temp_s0 + 4) = sinf(*(f32 *)(new_var + 0xC)) * 7.1050005f;
    func_15109100(arg0);
    func_15109140(arg0);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_15109100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_15109140.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_151091B8.s")

s32 func_151092A4(u8 *arg0, s32 arg1) {
    f32 mf[4][4];
    u8 *q;

    q = arg0; q += *(s32 *)(arg0 + 0x50); q += 0xF8;
    func_150A8050(mf, *(f32 *)q, 0.0f, *(f32 *)(q + 4));
    mf[3][1] = *(f32 *)(q + 0x10);
    mf[0][0] *= 0.157f;
    mf[0][1] *= 0.157f;
    mf[0][2] *= 0.157f;
    mf[1][0] *= 0.157f;
    mf[1][1] *= 0.157f;
    mf[1][2] *= 0.157f;
    mf[2][0] *= 0.157f;
    mf[2][1] *= 0.157f;
    mf[2][2] *= 0.157f;
    guMtxF2L(mf, &((Mtx *)(arg0 + 0x78))[D_800BE9C0]);
    return 1;
}

s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, s32, f32 *, f32 *, f32 *, s32, s32, s32, f32);
typedef struct { f32 x, y, z; } V3_09390;

s32 func_15109390(u8 *arg0)
{
  u8 *base;
  u8 *p;
  float new_var;
  V3_09390 out;
  f32 mf[4][4];
  s32 pad2[3]; // frame padding
  V3_09390 hit;
  base = *((u8 **) (arg0 + 0x18));
  p = base;
  p += *((s32 *) (base + 0x50));
  p += 0xF8;
  func_150A8050(mf, *((f32 *) (p + 0)), 0.0f, *((f32 *) (p + 4)));
  mf[3][1] = *((f32 *) (p + 0x10));
  mf[0][0] *= 0.157f;
  mf[0][1] *= 0.157f;
  mf[0][2] *= 0.157f;
  mf[1][0] *= 0.157f;
  mf[1][1] *= 0.157f;
  mf[1][2] *= 0.157f;
  mf[2][0] *= 0.157f;
  mf[2][1] *= 0.157f;
  mf[2][2] *= 0.157f;
  func_150A7E40(mf, 0.0f, -1108.0f, 0.0f, &out.x, &out.y, &out.z);
  if ((arg0 && arg0) && arg0) // fakematch: permuter, scheduling
  {
  }
  new_var = out.y - (*((f32 *) (p + 0x10)));
  if (func_150ACEA0(0.0f, *((f32 *) (p + 0x10)), 0.0f, out.x, new_var, out.z, 0, 0, &hit.x, &hit.y, &hit.z, 0, 0, 0, 0.0f) == 0)
  {
    hit = out;
  }
  *((s16 *) ((*((u8 **) (arg0 + 0x14))) + 0xE)) = hit.x;
  *((s16 *) ((*((u8 **) (arg0 + 0x14))) + 0x10)) = hit.y;
  *((s16 *) ((*((u8 **) (arg0 + 0x14))) + 0x12)) = hit.z;
  if (p[0x20] != 0)
  {
    *((*((u8 **) (arg0 + 0x14))) + 9) = 0;
  }
  else
  {
    *((*((u8 **) (arg0 + 0x14))) + 9) = 1;
  }
  return 1;
}

void func_1510957C(s32 arg0, s32 arg1, u8 arg2) {
    struct {
        s32 unk0;
        s32 unk4;
        u8 unk8;
    } sp24;
    s32 sp1C[2] = {0x38, 0x54};

    sp24.unk0 = arg0;
    sp24.unk4 = arg1;
    sp24.unk8 = arg2;
    func_15169260(sp1C, 2, (s32)&sp24, 0x1D);
}

void func_151095E4(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *p = arg0;
  p += *(s32 *)(arg0 + 0x50);
  p += 0xF8;
  switch (arg2) {
  case 0x1D:
    {
      s32 t; // fakematch: block-local declaration = basic-block boundary (unfilled jr ra delay slot, s69)
      *(s32 *)(p + 0x14) = ((s32 *)arg1)[0];
      p[0x18] = ((u8 *)arg1)[8];
      *(s32 *)(p + 0x1C) = ((s32 *)arg1)[1];
    }
    break;
  case 0x1E:
    if (p[0x20] != 0) {
      p[0x20] = 0;
    } else {
      p[0x20] = 1;
    }
    break;
  }
}

void func_1510965C(void) {
    s32 sp18[2] = {0x38, 0x54};

    func_15169260(sp18, 2, 0, 0x1E);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1365E0/func_151096A0.s")
