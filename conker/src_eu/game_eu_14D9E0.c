#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_151201D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_151206C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_15121A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_15121C68.s")

s32 func_151CA484(u8 *);

void func_15121E34(u8 *arg0)
{
  u8 *new_var;
  u8 *temp_v0;
  new_var = arg0 + 0x740;
  if (!((*(*((u16 **) (((u8 *) arg0) + 0x36C)))) & 0x10))
  {
    if ((*((s32 *) (((u8 *) arg0) + 0x34))) == 0x40)
    {
      if ((*((s32 *) (((u8 *) arg0) + 0x6FC))) == 0xF)
      {
        *((f32 *) (((u8 *) arg0) + 0x898)) = 0.0f;
        *((f32 *) (((u8 *) arg0) + 0x89C)) = 0.0f;
      }
      *((s8 *) (((u8 *) (*((u8 **) (((u8 *) arg0) + 0x3D4)))) + 0x198)) = 0;
      *((s16 *) (((u8 *) arg0) + 0x73C)) = 0;
      *((s16 *) (((u8 *) arg0) + 0x84A)) = 0x32;
    }
    else
    {
      *((s16 *) (((u8 *) arg0) + 0x84A)) = 0x32;
      if (1)
      {
        *((s16 *) (((u8 *) arg0) + 0x73C)) = 3;
      }
    }
    temp_v0 = new_var;
    *((f32 *) (((u8 *) arg0) + 0x374)) = 200.0f;
    *((f32 *) (((u8 *) arg0) + 0x348)) = 100.0f;
    *((s32 *) (((u8 *) arg0) + 0x134)) = (s32) (*((f32 *) (((u8 *) temp_v0) + 0x2C)));
    *((s8 *) (((u8 *) temp_v0) + 0x4C)) = 0;
    *((f32 *) (((u8 *) arg0) + 0x190)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x99C)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x198)) = 0.0f;
    func_1506160C(*((struct127 **) (((u8 *) arg0) + 0x3D0)), 2U, 0xFFU, 0x20U, (s32) (*((u8 *) (((u8 *) arg0) + 0x23D))));
    if ((*((u8 *) (((u8 *) arg0) + 0x84C))) != 0)
    {
      func_151CA484(arg0);
      *((u8 *) (((u8 *) arg0) + 0x84C)) = 0U;
    }
  }
}
