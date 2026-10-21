#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15034B50.s")

extern s16 D_800C4310;

void func_150351A4(u8 *arg0, s32 arg1, s32 arg2)
{
  f32 temp_f0;
  s32 temp_v1;
  u8 *temp_a2;
  s32 new_var;
  if (D_800C4310 != 0)
  {
    u8 *temp_v0;
    temp_v1 = (new_var = /* fakematch: permuter chain */ *((s32 *) (((u8 *) arg0) + 0x1D4)));
    temp_a2 = (arg1 << 6) + temp_v1;
    temp_v0 = (arg2 << 6) + new_var;
    temp_v1 = D_800C4310;
    temp_f0 = ((f32) temp_v1) * 0.00076296274f;
    temp_f0 *= *((f32 *) (((u8 *) arg0) + 0x14C));
    *((f32 *) (((u8 *) temp_a2) + 0x34)) = (f32) ((*((f32 *) (((u8 *) temp_a2) + 0x34))) - temp_f0);
    if (((0, arg2)) != (-1)) // fakematch: permuter comma
    {
      *((f32 *) (((u8 *) ((arg2 << 6) + new_var)) + 0x34)) = (f32) ((*((f32 *) (((u8 *) temp_v0) + 0x34))) - temp_f0);
    }
  }
}

void func_15035210(void) {
    D_800C4320 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15035220.s")

struct_eu_size0C *func_150359B8(void) {
    if (D_800C4320 == 15) {
        return NULL;
    }
    D_800C4320++;
    return &D_800C4328[D_800C4320 - 1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15035A04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15035AF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_1503605C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_150362D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_62360/func_15036438.s")
