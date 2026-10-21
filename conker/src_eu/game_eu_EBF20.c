#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_15116A8C(u8 *, s32, s32, s32);

void func_150BE710(u8 *arg0)
{
  u8 temp_t2;
  u8 *new_var2;
  int new_var3;
  u8 *new_var;
  new_var2 = arg0;
  if (((*((u8 *) (((u8 *) arg0) + 0x73))) & 3) != 3)
  {
    func_15116A8C(arg0, 1, 0x62C, 0x43FA0000);
    if ((*((u8 *) (((u8 *) arg0) + 0x4F))) & 4)
    {
      new_var3 = 0x64;
      *((f32 *) (((u8 *) arg0) + 0x84)) = (f32) ((*((f32 *) (((u8 *) arg0) + new_var3))) + (*((f32 *) (((u8 *) arg0) + 0x84))));
    }
    else
      if ((*((f32 *) (((u8 *) arg0) + 0x84))) > 270.0f)
    {
      *((f32 *) (((u8 *) arg0) + 0x84)) = 270.0f;
    }
    if ((*((f32 *) (((u8 *) arg0) + 0x84))) > 360.0f)
    {
      temp_t2 = 0xFFFC;
      temp_t2 = (*((u8 *) (((u8 *) new_var2) + 0x73))) & temp_t2;
      new_var = (u8 *) arg0;
      *((u8 *) (new_var + 0x73)) = (*((u8 *) (new_var + 0x73))) & 0xFFFC;
      *((u8 *) (new_var + 0x73)) = (u8) ((*((u8 *) (new_var + 0x73))) | 3);
      *((f32 *) (new_var + 0x64)) = 0.0f;
      func_100111C8(*((u16 *) (new_var + 0x74)));
      *((u16 *) (new_var + 0x74)) = 0U;
    }
  }
}

#ifdef NON_MATCHING
void func_150BE7E8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    f32 var_f22;

    temp_f12 = (f32) (*(s16 *)((u8 *)arg0 + 0x80));
    temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 0x7E));
    temp_f0 = (f32) (*(s16 *)((u8 *)arg0 + 0x7C));
    temp_f20 = (f32) (*(s16 *)((u8 *)arg0 + 0x3C)) * 0.000061035156f;
    temp_f20_2 = temp_f20 - (temp_f20 * 0.128f);
    var_f22 = ((f32) (*(s16 *)((u8 *)arg0 + 0x3E)) * 0.000061035156f) + (temp_f20_2 * (f32) D_800BE9E4);
    (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)arg0 + 0x82)) - temp_f0) * var_f22) + temp_f0);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)arg0 + 0x84)) - temp_f2) * var_f22) + temp_f2);
    (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)arg0 + 0x86)) - temp_f12) * var_f22) + temp_f12);
    if (var_f22 > 1.0f) {
        var_f22 = 1.0f;
    }
    (*(s16 *)((u8 *)arg0 + 0x3C)) = (s16) (s32) (temp_f20_2 * 16384.0f);
    (*(s16 *)((u8 *)arg0 + 0x3E)) = (s16) (s32) (var_f22 * 16384.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBF20/func_150BE7E8.s")
#endif
s16 *func_150BE938(s16 *arg0, s32 arg1) {
    u8 *p = (u8 *)&D_800CC2D0[arg1];

    arg0[0] = 0x68;
    arg0[1] = *(s32 *)(p + 0x2E8);
    arg0[2] = 0xE;
    arg0[3] = *(s32 *)(p + 0x2E4);
    return arg0 + 4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBF20/func_150BE994.s")
