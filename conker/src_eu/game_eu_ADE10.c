#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15080600(void)
{
  D_800D1D50 = (D_800D1D48 = (D_800D1D4C = 0));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ADE10/func_15080628.s")

#ifdef NON_MATCHING
int func_151EFDD0(void);
extern s32 D_80042B90;
extern s32 D_8009C0E0;

void func_15080748(u8 *arg0) {
    s32 sp1C;
    s32 var_v1;

    if ((D_800D1D48 != 0) && (arg0 != NULL)) {
        if (D_800D1D48 == 1) {
            if (D_80042B90 < 0x3E8) {
                (*(s8 *)((u8 *)arg0 + 0x1FF)) = 0;
            } else {
                (*(s8 *)((u8 *)arg0 + 0x1FF)) = 1;
            }
        } else if (D_80042B90 >= 0x3E9) {
            var_v1 = D_800D1D4C + 1;
            if (((*(u8 *)((u8 *)arg0 + 0x135)) - D_800BE9E4) < 0) {
                if (var_v1 >= 5) {
                    var_v1 = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x134)) = (s8) *(s32 *)((u8 *)&D_8009C0E0 + (var_v1 * 4));
                sp1C = var_v1;
                (*(u8 *)((u8 *)arg0 + 0x135)) = (u8) ((func_151EFDD0() % 7) + 4);
                D_800D1D4C = var_v1;
            }
        }
        D_80042B90 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ADE10/func_15080748.s")
#endif
s32 func_1507E8E0(u8 *, s32, s32);
s32 func_1507ED48();

void func_15080830(u8 *arg0, s32 arg1, s32 arg2)
{
  int new_var;
  s32 temp_v0;
  if (arg0 != 0)
  {
    arg2 = arg2;
    if (func_1507ED48() > 0)
    {
      new_var = 0xFFFE;
      if (arg1 == 0)
      {
        D_800D1D48 = 0;
        *((s16 *) (((u8 *) arg0) + 0x72)) = 0x14;
        func_1507E8E0(arg0, 0, 0xA);
        return;
      }
      *((s16 *) (((u8 *) arg0) + 0x72)) = new_var;
      if (arg1 == 1)
      {
        D_800D1D48 = 2;
        return;
      }
      if (arg2 != 0)
      {
        if (arg2 >= 0x15)
        {
          arg2 = 0x14;
        }
        if (arg2 <= 0)
        {
          arg2 = 1;
        }
      }
      func_1507E8E0(arg0, arg1, arg2);
      return;
    }
    temp_v0 = arg1 != 0;
    D_800D1D48 = temp_v0;
    if (temp_v0 == 0)
    {
      *((s8 *) (((u8 *) arg0) + 0x1FF)) = 0;
    }
  }
}
