#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EF370/func_150C1B60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EF370/func_150C1BC0.s")

s32 func_150C1E78(u8 *arg0)
{
  s32 t;
  s32 v;
  u8 *q;
  q = *((u8 **) (arg0 + 0x98));
  v = *((s16 *) (arg0 + 0x1C));
  t = (v * 8) & 0xFFFFFFFFFFFFFFFF; // fakematch: 64-bit mask keeps t in a temp register
  v = t;
  if (t >= 0x100)
  {
    v = 0xFF;
  }
  q[0x1B] = v;
  if ((v & 0xFF) < 0)
  {
    return 0;
  }
  return 1;
}
