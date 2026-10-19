#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6D300/func_1503FAF0.s")

s32 func_1503FAF0(u8 *, s16, s16, s32, s32);

void func_1503FBF4(u8 *arg0, s32 arg1, s32 arg2) {
    func_1503FAF0(arg0 + 0x320, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x1C)), arg1, 1);
}

void func_1503FC54(void)
{
  int new_var; // fakematch: permuter temp for start + 1
  s32 i;
  s32 start;
  if (0 != D_800C67F0)
  {
    start = D_800C67F1;
    new_var = start + 1;
    i = new_var;
    if (i >= 0x19)
    {
      i = 0;
    }
    while (i != start)
    {
      if (D_800CC2D0[i].unkF8 & 0x800000)
      {
        D_800C67F1 = i;
        return;
      }
      i++;
      if (i >= 0x19)
      {
        i = 0;
      }
    }

  }
}
