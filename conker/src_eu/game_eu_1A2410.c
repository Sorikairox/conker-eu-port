#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2410/func_15174690.s")

void func_15174E90(u8 *arg0)
{
  s32 v;
  s32 temp_v1;
  v = arg0[0x3F];
  if (v >= 0xC9)
  {
    v = 0xC8;
  }
  v -= D_800BE9E4 * (*((s32 *) (arg0 + 0x18)));
  if (v < 0)
  {
    *((s16 *) (arg0 + 0x38)) = 0;
    return;
  }
  temp_v1 = *((s32 *) (arg0 + 0x14));
  arg0[0x3F] = v;
  *((s16 *) (arg0 + 0x34)) = (*((s16 *) (arg0 + 0x34))) + temp_v1;
  *((s16 *) (arg0 + 0x36)) = (*((s16 *) (arg0 + 0x36))) + ((temp_v1 * 8) / 7);
}
