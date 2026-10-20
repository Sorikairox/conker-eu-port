#include <ultra64.h>
#include "functions.h"
#include "variables.h"

const char rodata_pre_193D00[] = "\xff"; // fakematch: unreferenced leading rodata word


void func_151664F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8)
{
  s32 i;
  u8 *temp_v0;
  temp_v0 = func_15167A68(4, arg8, 0xA8, 1, (u8) ((s32) arg7), 1U);
  if (temp_v0 != 0)
  {
    if (arg0 == (-1))
    {
      for (i = 0; i != 2; i++)
      {
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x12)) = arg2;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x22)) = arg2;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x32)) = arg2;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x42)) = arg2;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x16)) = 0;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x26)) = 0;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x36)) = 0;
        *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x46)) = 0;
      }

      *((s8 *) (((u8 *) temp_v0) + 0x95)) = 0;
    }
    else
    {
      *((s8 *) (((u8 *) temp_v0) + 0x91)) = (s8) ((s32) (sinf(((f32) arg0) * 0.017453292f) * 127.0f));
      i = (s32) ((-cosf(((f32) arg0) * 0.017453292f)) * 127.0f);
      *((s8 *) (((u8 *) temp_v0) + 0x90)) = (s8) i;
      *((s8 *) (((u8 *) temp_v0) + 0x95)) = 1;
    }
    for (i = 0; i != 2; i++)
    {
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x18)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x1A)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x28)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x2A)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x38)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x3A)) = 0x2800;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x48)) = 0x2000;
      *((s16 *) ((((u8 *) temp_v0) + (i * 0x40)) + 0x4A)) = 0x2800;
    }

    *((s16 *) (((u8 *) temp_v0) + 0x9A)) = arg2;
    *((s16 *) (((u8 *) temp_v0) + 0x9E)) = 1;
    *((s8 *) (((u8 *) temp_v0) + 0x92)) = (s8) arg5;
    *((s8 *) (((u8 *) temp_v0) + 0x93)) = (s8) arg5;
    *((s16 *) (((u8 *) temp_v0) + 0x98)) = (s16) arg1;
    *((s16 *) (((u8 *) temp_v0) + 0x9C)) = (s16) arg3;
    *((s16 *) (((u8 *) temp_v0) + 0x96)) = (s16) arg4;
    *((s8 *) (((u8 *) temp_v0) + 0x94)) = (s8) arg6;
    func_1517E5CC(arg1, arg2, arg3, temp_v0);
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_193D00/func_15166688.s")

void func_15166774(struct102 *arg0) {
    s32 temp_v0;

    *(s16 *)((u8 *)arg0 + 0x9E) += *(s16 *)((u8 *)arg0 + 0x96) * D_800BE9E4;
    temp_v0 = *(u8 *)((u8 *)arg0 + 0x92);
    temp_v0 -= D_800BE9E4;
    if (temp_v0 <= 0) {
        func_1516972C(arg0);
        return;
    }
    *(u8 *)((u8 *)arg0 + 0x92) = temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_193D00/func_151667D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_193D00/func_15166E28.s")
