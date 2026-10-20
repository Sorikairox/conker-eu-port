#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_117620/func_150E9E10.s")

void func_15143794(s16, s16, f32, void *);
s32 func_150E9E10(s32 *, s32 *, f32, u8, s32);
s32 func_1514470C(s32, s32 *);

void func_150EA3B4(u8 *arg0)
{
  f32 temp_f20;
  s32 sp80[3];
  s32 sp74[3];
  u8 *temp_s0;
  temp_s0 = arg0 + 0x28;
  ;
  *((f32 *) (((u8 *) temp_s0) + 0x14)) = (f32) ((((*((f32 *) (((u8 *) temp_s0) + 4))) + (func_150ADA68() * (*((f32 *) (((u8 *) temp_s0) + 8))))) * D_800BE9A4) + (*((f32 *) (((u8 *) temp_s0) + 0x14))));
  if ((*((f32 *) (((u8 *) temp_s0) + 0x14))) > 1.0f)
  {
    do
    {
      temp_f20 = (*((f32 *) (((u8 *) temp_s0) + 0xC))) + ((*((f32 *) (((u8 *) temp_s0) + 0x10))) * func_150ADA68());
      func_1514470C(*((s32 *) (((u8 *) temp_s0) + 0)), sp80);
      func_15143794((s16) (func_150ADA20() & 0xFF), (s16) (0x40 - (((u32) func_150ADA20()) % 129U)), (func_150ADA68() * 600.0f) * 0.01f, sp74);
      func_150E9E10(sp80, sp74, temp_f20, *((u8 *) (((u8 *) arg0) + 0xC)), (s32) (*((u8 *) (((u8 *) arg0) + 1))));
      *((f32 *) (((u8 *) temp_s0) + 0x14)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0x14))) - 1.0f);
    }
    while ((*((f32 *) (((u8 *) temp_s0) + 0x14))) > 1.0f);
  }
}
