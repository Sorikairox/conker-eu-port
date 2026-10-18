#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3870.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3F78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D44E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4ED0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4FF0.s")

void func_150D50E4(s32 arg0) {
    func_150D513C(arg0);
    func_15147E64(arg0);
}

void func_150D5110(s32 arg0) {
    func_150D513C(arg0);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D513C.s")

extern f32 D_800A0DE4;
extern u8 D_800A0D90[];
s32 func_150D51D4(u8 *arg0)
{
  u8 *temp_v1;
  *(s16 *)(arg0 + 0x170) -= D_800BE9E4;
  temp_v1 = arg0 + 0x110;
  if (*(s16 *)(arg0 + 0x170) < 0) {
    arg0[0x18] = *(s32 *)&D_800A0D90[(func_150ADA20() & 3) * 4];
    *(s16 *)(arg0 + 0x170) = (func_150ADA20() & 7) + 3;
  }
  *(f32 *)(temp_v1 + 0x48) += (*(f32 *)(arg0 + 0x174) - *(f32 *)(temp_v1 + 0x48)) * D_800A0DE4;
  return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5268.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5634.s")
