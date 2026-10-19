#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15046F70(f32 *, s32, f32, f32 *);
extern f32 D_800A0B80;
s32 func_1504715C(f32 *, u8 *);
s32 func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
void func_150CE0C0(u8 *arg0, u8 arg1, s32 arg2)
{
  f32 sp6C[3];
  f32 sp48[9];
  if (arg0 != 0)
  {
    func_1504715C(sp48, arg0);
    sp6C[0] = *((f32 *) (((u8 *) arg0) + 0x14));
    sp6C[1] = (*((f32 *) (((u8 *) arg0) + 0x18))) + 1000.0f;
    sp6C[2] = *((f32 *) (((u8 *) arg0) + 0x1C));
    if (func_15046F70(sp6C, 0, (*((f32 *) (((u8 *) arg0) + 0x18))) - D_800A0B80, sp48) != 0)
    {
      sp6C[1] = sp48[0];
      dummy_label_506575: ; // fakematch: empty label keeps the sp6C[1] store out of the jal delay slot
      func_1514CBE8(sp6C[0], sp6C[1], sp6C[2], 251.0f, 0, 0xFF, (func_150ADA20() & 0xF) + 0x23, 0x17, 0, 0.0f, 0, arg1);
      func_1514CBE8(sp6C[0], sp6C[1], sp6C[2], 290.0f, 0, 0xFF, (func_150ADA20() % 21U) + 0x1E, 0x18, 0, 0.0f, 0, arg1);
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FB8D0/func_150CE204.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FB8D0/func_150CE420.s")
