#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_151201D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_151206C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_15121A00.s")

void func_15121C68(u8 *arg0) {
    if (arg0[0x23E] != 0) {
        if (arg0[0x23E] == 0x34) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 80.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 350.0f;
            return;
        }
        if ((arg0[0x23E] == 0x3B) && ((D_800BE9F0 == 0x41) || (D_800BE9F0 == 0x3C))) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = -12.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = -28.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 106.0f;
            return;
        }
        if ((arg0[0x23E] == 2) || (arg0[0x23E] == 0xA) || (arg0[0x23E] == 0x13)) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 135.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x80);
            return;
        }
        if ((arg0[0x23E] == 0x12) && (D_800BE9F0 == 0x3C)) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 180.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0xF) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 480.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0x38) {
            (*(f32 *)((u8 *)arg0 + 0x784)) = 110.0f;
            (*(f32 *)((u8 *)arg0 + 0x190)) = 5.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0x15) {
            (*(f32 *)((u8 *)arg0 + 0x784)) = 110.0f;
            (*(f32 *)((u8 *)arg0 + 0x190)) = 25.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        (*(f32 *)((u8 *)arg0 + 0x190)) = 5.0f;
        (*(f32 *)((u8 *)arg0 + 0x784)) = 75.0f;
        (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
        return;
    }
    (*(f32 *)((u8 *)arg0 + 0x784)) = 90.0f;
    (*(f32 *)((u8 *)arg0 + 0x190)) = 25.0f;
    (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
}

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
