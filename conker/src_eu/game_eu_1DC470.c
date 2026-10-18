#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AEC60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AED60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AEE40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AEF34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AF064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AECA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AF820.s")

s32 func_151AF938(f32 *, s32, s32, s32, s32);

void func_151AF8E8(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6)
{
  f32 new_var[2];
  f32 sp24;
  sp24 = arg0;
  new_var[0] = arg1;
  new_var[1] = arg2;
  func_151AF938(&sp24, arg3, arg4, arg5, (s32) (*((u8 *) (((u8 *) arg6) + 0xC))));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AF938.s")
