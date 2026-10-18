#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501BB20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501BBB8.s")

extern f32 D_80096D10;
void func_1501C0D0(u8, f32, f32);
void func_1501BFF0(u8 arg0, u8 arg1)
{
  f32 t;
  f32 a;
  f32 b;
  if (arg1 >= 9) {
    arg1 = 8;
  }
  if (arg1 == 8) {
    a = 20.0f;
    b = 0.0f;
  } else if (arg1 == 0) {
    a = 0.0f;
    b = 99.0f;
  } else {
    t = ((f32)(u32)arg1 - 1) * D_80096D10 * 5.0f;
    a = t + 2.0f;
    b = 7.0f - t;
  }
  func_1501C0D0(arg0, a, b);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C0D0.s")

void func_1501C15C(u8 arg0) {
    s32 temp_v0 = D_800843F0[arg0];

    if (temp_v0 < 4) {
        D_800BED5C[temp_v0] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C1B0.s")

void func_1501C51C(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        func_1501C15C(i);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C55C.s")
