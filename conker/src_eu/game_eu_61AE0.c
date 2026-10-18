#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_150342D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_150344AC.s")

s16 *func_15034630(s16 *arg0, s32 arg1)
{
  struct127 *temp_v0;
  temp_v0 = &D_800CC2D0[arg1];
  if (temp_v0->unk1D1 != 0)
  {
    *arg0 = 6;
    arg0 += 2;
    arg0[-1] = (s16) (temp_v0->unk1D1 * 0xC8);
  }
  return arg0;
}

s16 *func_150346A0(s16 *arg0, s32 arg1)
{
  struct127 *temp_v0;
  temp_v0 = &D_800CC2D0[arg1];
  if (temp_v0->unk1D1 != 0)
  {
    *arg0 = 6;
    arg0 += 2;
    arg0[-1] = (s16) (temp_v0->unk1D1 * 0xC8);
  }
  return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_15034710.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_15034790.s")

s32 func_1503BCAC();

void func_1503482C(s32 arg0) {
    switch (D_800CC2D4[arg0 * 0x32C]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 0x80:
    case 0xB0:
        func_1503BCAC();
        break;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_150348D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_15034A18.s")

void func_15034AD8(void) {
    struct127 *var_s0;
    var_s0 = D_800CC2D0;
    if (D_800BEAC0 == 0) {
        do {
            if ((var_s0->interaction_state != 0) && (var_s0->unk9C != 0)) {
                func_15034A18(var_s0);
            }
            var_s0++;
        } while (var_s0 != (struct127 *)&D_800D121C);
    }
}
