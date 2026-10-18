#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D658.s")

void func_1503D728(s32 *arg0, s32 arg1) {
    s32 temp_v0 = *arg0;
    if ((temp_v0 != 0) && !(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}

void func_1503D74C(s32 *arg0, s32 arg1) {
    while (*arg0 != 0) {
        *arg0 += arg1;
        arg0 += 2;
    }
}

void func_1503D774(u8 *arg0, s32 arg1)
{
  u8 *start = arg0;
  while (*(u16 *)arg0 != 0x3E7) {
    if (*(s32 *)(arg0 + 4) != 0) {
      func_1503D728(arg0 + 4, start);
    }
    arg0 += 8;
  }
  D_800C5A90[arg1] = (arg0 - start) >> 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D800.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D8E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503D950.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DA64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DAF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DC74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DD2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DD8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503DF2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6AA20/func_1503E00C.s")
