#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_151B90F0(f32 *arg0) {
    arg0[0x3C / 4] = arg0[0x48 / 4] + (arg0[0x5C / 4] * sinf(arg0[0x44 / 4]));
    arg0[0x44 / 4] += arg0[0x4C / 4] * D_800BE9A4;
    arg0[0x44 / 4] = func_15144B68(arg0[0x44 / 4]);
    arg0[0x20 / 4] += arg0[0x50 / 4] * D_800BE9A4;
    arg0[0x28 / 4] += arg0[0x58 / 4] * D_800BE9A4;
    return 1;
}

void func_151B9190(f32 *arg0, s32 arg1)
{
  arg0[0x44 / 4] = arg0[0x5C / 4] + (arg0[0x64 / 4] * sinf(arg0[0x58 / 4]));
  arg0[0x58 / 4] += arg0[0x60 / 4] * D_800BE9A4;
  arg0[0x58 / 4] = func_15144B68(arg0[0x58 / 4]);
  func_151D9450(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6900/func_151B9204.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6900/func_151B92AC.s")
