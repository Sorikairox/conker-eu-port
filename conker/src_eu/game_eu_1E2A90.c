#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E2A90/func_151B5280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E2A90/func_151B53FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E2A90/func_151B5454.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E2A90/func_151B5590.s")

s32 func_151B56A4(f32 *, s32, s32, s32, s32);

void func_151B5654(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6)
{
  f32 new_var[2];
  f32 sp24;
  sp24 = arg0;
  new_var[0] = arg1;
  new_var[1] = arg2;
  func_151B56A4(&sp24, arg3, arg4, arg5, (s32) (*((u8 *) (((u8 *) arg6) + 0xC))));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E2A90/func_151B56A4.s")
