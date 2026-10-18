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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBF20/func_150BE7E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBF20/func_150BE938.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBF20/func_150BE994.s")
