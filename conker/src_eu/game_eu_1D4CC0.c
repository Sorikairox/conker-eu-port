#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D4CC0/func_151A74B0.s")

s32 func_151A799C(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x170;
    if (*(s16 *)(arg0 + 0x64) < 0x20) {
        if (*(struct102 **)(temp_v0 + 4) != NULL) {
            func_1516972C(*(struct102 **)(temp_v0 + 4));
            *(struct102 **)(temp_v0 + 4) = NULL;
        }
    }
    return 1;
}

#ifdef NON_MATCHING
void func_1514B0CC(f32, f32, f32, f32, s16, f32, f32, f32, f32, s16, s16, u8);
#else
s32 func_1514B0CC(f32, f32, s32, f32, s32, f32, f32, f32, f32, s32, s32, u8);
#endif
s32 func_151A79EC(u8 *arg0, f32 arg1, s32 arg2, s32 arg3, f32 arg4)
{
  u8 *p;
  u8 b;
  p = arg0 + 0x170;
  *((f32 *) (arg0 + 0x3C)) = (*((f32 *) (arg0 + 0x10))) + arg4;
  if ((*((s32 *) (arg0 + 0x174))) != 0)
  {
    func_1516972C(*((struct102 **) (p + 4)));
    *((struct102 **) (p + 4)) = 0;
  }
  if ((*((f32 *) p)) < (*((f32 *) (arg0 + 0x48))))
  {
    *((s32 *) (arg0 + 0x60)) &= ~7;
    *((s32 *) (arg0 + 0x60)) &= ~8;
    *((s32 *) (arg0 + 0x60)) &= ~0x40;
    *((s32 *) (arg0 + 0x60)) &= ~0x20;
    *((f32 *) (arg0 + 0x44)) = 0.0f;
    *((f32 *) (arg0 + 0x48)) = 0.0f;
    *((f32 *) (arg0 + 0x4C)) = 0.0f;
    if ((*((s16 *) (arg0 + 0x64))) > 0x20)
    {
      *((s16 *) (arg0 + 0x64)) = 0x20;
    }
    if (p[8] != 0)
    {
      b = 0;
      if (p[9] != 0)
      {
        b = 1;
      }
#ifdef NON_MATCHING
      /* arg3 holds f32 bits */
      func_1514B0CC(arg1, arg4, *(f32 *) &arg3, (*((f32 *) (arg0 + 0x18))) * 35.0f, (func_150ADA20() % 3U) + 2, *((f32 *) (arg0 + 0x18)), (*((f32 *) (arg0 + 0x18))) * 0.5f, *((f32 *) (arg0 + 0x18)), (*((f32 *) (arg0 + 0x18))) * 0.5f, *((s16 *) (p + 0xA)), *((s16 *) (p + 0xC)), b);
#else
      func_1514B0CC(arg1, arg4, arg3, (*((f32 *) (arg0 + 0x18))) * 35.0f, (func_150ADA20() % 3U) + 2, *((f32 *) (arg0 + 0x18)), (*((f32 *) (arg0 + 0x18))) * 0.5f, *((f32 *) (arg0 + 0x18)), (*((f32 *) (arg0 + 0x18))) * 0.5f, *((s16 *) (p + 0xA)), *((s16 *) (p + 0xC)), b);
#endif
    }
  }
  else
  {
    *((f32 *) (arg0 + 0x44)) *= *((f32 *) (arg0 + 0x14));
    *((f32 *) (arg0 + 0x48)) = (*((f32 *) (arg0 + 0x14))) * (-(*((f32 *) (arg0 + 0x48))));
    *((f32 *) (arg0 + 0x4C)) *= *((f32 *) (arg0 + 0x14));
    *((f32 *) (arg0 + 0x50)) *= *((f32 *) (arg0 + 0x14));
    *((f32 *) (arg0 + 0x54)) *= *((f32 *) (arg0 + 0x14));
    *((f32 *) (arg0 + 0x58)) *= *((f32 *) (arg0 + 0x14));
  }
  return 1;
}

s32 func_151A2C9C(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_151A7BC0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6);
void func_151A7D70(u8 *arg0);
void func_151A7E2C(u8 *arg0);
void func_151A7EB8(u8 *arg0);

s32 func_151A2C9C(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151A7BC0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp74[9];
    f32 temp_f18;
    f32 sp6C;
    f32 temp_f2;

    sp6C = (*(f32 *)((u8 *)arg6 + 0x40));
    sp74[6] = arg0;
    sp74[7] = arg1;
    sp74[8] = arg2;
    temp_f18 = (func_150ADA68() * 166.0f) + 160.0f;
    sp74[0] = 0.0f;
    sp74[1] = 0.0f;
    sp74[2] = 0.0f;
    temp_f2 = temp_f18 * 0.001f;
    sp74[3] = -arg3 * D_800BEDC8 * temp_f2;
    sp74[4] = -arg4 * D_800BEDC8 * temp_f2;
    sp74[5] = -arg5 * D_800BEDC8 * temp_f2;
    func_151A2C9C(&sp74[6], sp74, &sp74[3], 0x3F800000, ((func_150ADA68() * 591.0f) + -600.0f) * 0.001f, ((func_150ADA68() * 500.0f) + 400.0f) * sp6C, ((u32) func_150ADA20() % 21U) + 0xF, (func_150ADA20() % 101U) + 0x64, 0xF, 0x14, 0, -1, 0x56, 0x27, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1)));
}

void func_151A7D70(u8 *arg0)
{
  u8 *p = arg0 + 0x50;
  unsigned char t;
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (arg0 + 0x54))))
  {
    *((s8 *) (arg0 + 0x3F)) = (*((s16 *) (arg0 + 0x56))) * (*((s16 *) (arg0 + 0x38)));
  }
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (p + 8))))
  {
    short d;
    d = (*((s16 *) (p + 0xA))) * D_800BE9E4;
    *((s16 *) (arg0 + 0x34)) += d;
    *((s16 *) (arg0 + 0x36)) += d;
  }
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (p + 0))))
  {
    *((s8 *) (arg0 + 0x2F)) = 0x15;
    *((u16 *) (arg0 + 0x44)) |= 0x201;
    t = (*((s16 *) (p + 2))) * (0, (*((s16 *) (arg0 + 0x38)))); // fakematch: comma puts arg0->0x38 in fs of multu (s142 recipe 1)
    *((s32 *) (arg0 + 0x14)) = 0xC000F;
    *((s8 *) (arg0 + 0x42)) = t;
    *((s8 *) (arg0 + 0x41)) = t;
    *((s8 *) (arg0 + 0x40)) = t;
  }
}

#define S(o) (*(s16 *)(arg0 + (o)))
#define S2(o) (*(s16 *)(p + (o)))
void func_151A7E2C(u8 *arg0)
{
  u8 *p = arg0 + 0x50;
  unsigned char t;
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (arg0 + 0x54))))
  {
    *((s8 *) (arg0 + 0x3F)) = (*((s16 *) (arg0 + 0x56))) * (*((s16 *) (arg0 + 0x38)));
  }
  if ((*((s16 *) (arg0 + 0x38))) < (*((s16 *) (p + 8))))
  {
    short d;
    d = (*((s16 *) (p + 0xA))) * D_800BE9E4;
    *((s16 *) (arg0 + 0x34)) += d;
    *((s16 *) (arg0 + 0x36)) += d;
  }
  t = (*((s16 *) (p + 2))) * (0, (*((s16 *) (arg0 + 0x38)))); // fakematch: comma puts arg0->0x38 in fs of multu (s142 recipe 1)
  *((s8 *) (arg0 + 0x42)) = t;
  *((s8 *) (arg0 + 0x41)) = t;
  *((s8 *) (arg0 + 0x40)) = t;
}

void func_151A7EB8(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x170;
    if (*(s32 *)(arg0 + 0x174) != 0) {
        func_1516972C(*(struct102 **)(temp_v0 + 4));
        *(struct102 **)(temp_v0 + 4) = NULL;
    }
}
