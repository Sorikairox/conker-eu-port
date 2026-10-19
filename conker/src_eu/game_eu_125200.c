#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F79F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F7E34.s")

extern f32 D_800A1FA8;
s32 func_150F83A0(u8 *arg0)
{
  u8 *v = arg0 + 0x110;
  f32 f;
  *((s8 *) (arg0 + 0x5C)) = (s8) ((u32) ((*((f32 *) (arg0 + 0x128))) * D_800A1FA8));
  f = (*((f32 *) (v + 0x24))) + ((*((f32 *) (v + 0x28))) * sinf(*((f32 *) (arg0 + 0x12C))));
  *((f32 *) (arg0 + 0x30)) = f;
  *((f32 *) (arg0 + 0x2C)) = f;
  *((f32 *) (v + 0x1C)) = func_15144B68(((*((f32 *) (v + 0x20))) * D_800BE9A4) + (*((f32 *) (v + 0x1C))));
  *((f32 *) (v + 0x18)) = (*((f32 *) (v + 0x18))) - D_800BE9A4;
  if ((*((f32 *) (v + 0x18))) < 0.0f)
  {
    return 0;
  }
  return 1;
}

void func_150F84D8(u8 *arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x110, arg0 + 0x11C, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F850C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F85AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F873C.s")
