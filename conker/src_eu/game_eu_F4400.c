#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_150C7290();
void func_150C6BF0(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x6C) != 0) {
        u8 *p = *(u8 **)(arg0 + 0x6C);
        p += 0xB0;
        p[4] = 1;
    } else {
    *(s32 *)(arg0 + 0x6C) = func_150C7290();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6C3C.s")

s32 func_1513F6C0(u8 *, s32, s32);
s32 func_150C6D2C(u8 *arg0)
{
  u8 *p;
  p = *((u8 **) (arg0 + 0xB0));
  p += 0x59;  // fakematch: keeps the dead addiu (p += K+1; p--;)
  p--;  // fakematch: pairs with p += K+1
  *((s32 *) (p + 0x14)) = 0;
  *((s32 *) (arg0 + 0xB0)) = 0;
  *((s32 *) (arg0 + 0x18)) = (*((s32 *) (arg0 + 0x18))) | 2;
  func_1513F6C0(arg0, 0, 0);
  return 0;
}

s32 func_150C6DC4(s32, u8 *, s32);

void func_150C6D70(u8 *arg0)
{
  u8 *new_var4;
  u8 *new_var;
  s32 *new_var3;
  u8 *new_var2;
  s32 temp_a2;
  do
  {
    new_var2 = arg0;
    temp_a2 = *((s32 *) (((u8 *) new_var2) + 0x18));
    new_var = ((u8 *) new_var2) + 0x70;
    if (((*((s32 *) new_var)) != 0) ^ 0)
    {
      temp_a2++;
      temp_a2--;
      new_var3 = (s32 *) new_var;
      new_var4 = (u8 *) ((*new_var3) + 0x58);
      new_var2 = new_var4 + 4;
      *((s8 *) new_var2) = 1;
      goto dummy_label_302949;
      dummy_label_302949:
      ;

      ;
      ;
      return;
    }
  }
  while (0);
  *((s32 *) new_var) = func_150C6DC4(temp_a2, new_var2, *((s32 *) (((u8 *) new_var2) + 0x18)));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6DC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C6F08.s")

s32 func_150C721C(u8 *arg0) {
    s32 ret = 1;
    if (arg0[0x5C] == 0) {
        ret = 0;
    }
    arg0[0x5C] = 0;
    return ret;
}

void func_150C7240(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    func_151346EC(arg0);
}

void func_150C7268(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    func_1513470C(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F4400/func_150C7290.s")
