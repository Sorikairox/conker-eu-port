#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_156A30/func_15129220.s")

extern s16 D_800898F0;
extern u8 D_800DC458[];
extern f32 D_800A39F0;

void func_15129E30(u8 *arg0, s32 arg1)
{
  if (D_800898F0 != 0)
  {
    *((s16 *) (D_800DC458 + arg0[0x23D] * 0x24 + 2)) = 0;
    *((f32 *) (D_800DC458 + arg0[0x23D] * 0x24 + 4)) = -1.0f;
    *((f32 *) (D_800DC458 + arg0[0x23D] * 0x24 + 8)) = D_800A39F0;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_156A30/func_15129EA4.s")
