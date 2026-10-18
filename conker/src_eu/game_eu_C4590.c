#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15096970(void) {
    bzero(D_800D31E0, 0x6C);
    D_800D2DB4 = 0;
}

s32 func_15096DB0(s32 arg0)
{
  s32 i;
  for (i = 0; i < arg0; i++) {
    if (*((u8 *)D_800D31E0 + i * 0x24) != 0) {
      return 1;
    }
  }
  return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_15096E78.s")

s32 func_15096E78(s32);

void func_15097118(void) {
    s32 var_s0;
    u8 *var_s1;

    var_s0 = 0;
    if (D_800C35EA != 1) {
        var_s1 = D_800D31E0;
loop_2:
        if (*var_s1 != 0) {
            if (func_15096E78(var_s0) == 0) {
                goto block_6;
            }
            return;
        }
block_6:
        var_s0 += 1;
        var_s1 += 0x24;
        if (var_s0 == 3) {

        } else {
            goto loop_2;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_15097188.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_150979AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C4590/func_15097BA8.s")
