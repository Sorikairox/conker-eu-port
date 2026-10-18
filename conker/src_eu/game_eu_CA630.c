#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1509CE20(s32 arg0) {
    return D_800877D0[arg0].unk0;
}

u16 func_1509CE40(s32 arg0) {
    return D_800877D0[arg0].unk8;
}

s32 func_1509CE60(s32 arg0) {
    return *(u16 *)((u8 *)&D_800877D0[arg0] + 0xA) & 0xFFF;
}

s32 func_1509CE88(s32 arg0) {
    return D_800877D0[arg0].unk4;
}

s32 func_1509CEA8(s32 arg0)
{
  s32 var_v1;
  struct_eu_800877D0 *var_v0;
  var_v1 = 0;
 var_v0 = D_800877D0; loop_1: if ((var_v0->unk0 != 0) && (arg0 == ((var_v0->unk4 & 0x1FFFFFFF) + 1))) { return var_v1;
  }

  if (((*((s32 *) (((u8 *) var_v0) + 0x14))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x18))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 1;
  }
  if (((*((s32 *) (((u8 *) var_v0) + 0x28))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x2C))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 2;
  }
  if (((*((s32 *) (((u8 *) var_v0) + 0x3C))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x40))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 3;
  }
  var_v1 += 4;
  var_v0 += 4;
  if (var_v1 == 0xCC)
  {
    return 0xCC;
  }
  goto loop_1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509CF78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509CBD4.s")

void func_1509D0C4(s32 arg0);

void func_1509D0A4(s32 arg0) {
    func_1509D0C4(arg0);
}

s32 func_1509D274(s32, void (*)(s32), s32);
extern s32 D_800877DC;

void func_1509D0C4(s32 arg0) {
    func_1509D274(*(s32 *)((u8 *)&D_800877DC + (arg0 * 0x14)), func_1509D0C4, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D104.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D1EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D274.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D338.s")

s32 func_10004074(s32);
void func_1509D464(void) {
    s32 r;
    if (D_800D33D0 != 0) {
        r = D_800D33D0;
        func_10004074(r);
        D_800D33D0 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D49C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509D590.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DB90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DD0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA630/func_1509DFCC.s")
