#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8790/func_1518AF80.s")

u8 *func_1518AADC(s32 arg0, s16 arg1, u8 arg2)
{
  u8 *t;
  t = func_15167A68(0x1D, 0, 0x28, 1, 0xFFU, 1U);
  if (t == 0)
  {
    return 0;
  }
  *((s32 *) (t + 0x1C)) = 0;
  *((s32 *) (t + 0x18)) = arg0;
  *((s16 *) (t + 0x22)) = arg1;
  *((s16 *) (t + 0x20)) = arg1;
  *((s32 *) (t + 0x10)) = 0;
  *((s32 *) (t + 0x14)) = 0;
  *((u8 *) (t + 0x24)) = arg2;
  return t;
}

u8 *func_1518B0D0(s32 arg0, u8 arg1)
{
  u8 *temp_v0;
  temp_v0 = func_15167A68(0x1E, 0, 0x20, 1, 0xFFU, 1U);
  if (temp_v0 == 0)
  {
    return 0;
  }
  *((s32 *) (((u8 *) temp_v0) + 0x10)) = arg0;
  *((u8 *) (((u8 *) temp_v0) + 0x1C)) = arg1;
  *((s32 *) (((u8 *) temp_v0) + 0x14)) = 0;
  *((s32 *) (((u8 *) temp_v0) + 0x18)) = 0;
  return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8790/func_1518B140.s")
