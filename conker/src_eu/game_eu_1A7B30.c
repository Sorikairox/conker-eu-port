#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517A320.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517A550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517A75C.s")

s32 func_1517A904(s32 arg0) {
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517A910.s")

s32 func_1510EDAC(s32, s32, f32 *, s32, s32, s32, f32, f32, f32, f32, s32, s32);

void func_1517ABB4(f32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4)
{
  u8 *obj;
  s32 n;
  f32 d;
  s32 h;
  s32 pad;
  n = arg0;
  if (n != 0)
  {
    obj = func_15167A68(9, 0, 0xB8, 1, 0xFF, 1);
    if (obj)
    {
      func_1510EDAC(0, 0, &d, 0, 0, 0, arg2, arg3, arg4, arg3, 0, 0);
 if (0) {} // fakematch: block boundary, puts the shared s16 store value in v0
      *((s16 *) (obj + 0x92)) = (*((s16 *) (obj + 0xB0)) = d + 3.0f);
      *((s16 *) (obj + 0x90)) = arg2;
      *((s16 *) (obj + 0x94)) = arg4;
      *((s16 *) (obj + 0x96)) = 0x5A;
      *((s16 *) (obj + 0x98)) = func_150ADA20() % 360U;
      *((s16 *) (obj + 0x9A)) = 0;
      *((s16 *) (obj + 0xA0)) = 0;
      *((s16 *) (obj + 0xA4)) = 0;
      *((u8 *) (obj + 0x9F)) = arg1;
      *((f32 *) (obj + 0xA8)) = ((s32) ((func_150ADA20() % 80U) + 0x64)) * 0.01f;
      *((s16 *) (obj + 0xA2)) = arg0 * 0.4f;
      h = arg0 * 0.5f;
      *((s8 *) (obj + 0x9C)) = (func_150ADA20() % ((u32) n)) - h;
      *((s8 *) (obj + 0x9D)) = (func_150ADA20() % ((u32) n)) - h;
      *((s8 *) (obj + 0x9E)) = (func_150ADA20() % ((u32) n)) - h;
      *((s16 *) (obj + 0xA6)) = 0;
      *((u8 *) (obj + 0xB3)) = 0xFF;
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A7B30/func_1517ADBC.s")

s32 func_1517AEC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD880 = -1;
    if ((arg1 == 0xC) || (arg1 == 0x59)) {
        arg0 = func_1517A904(arg0);
    }
    return arg0;
}

extern s32 D_800DD5E0;
extern u8 D_800909C4[];
s32 func_1517AF18(s32 arg0, s32 arg1) {
    s32 sp30[6]; // fakematch: stack layout guess (frame 0x48, &sp30[1] at 0x34)
    if (arg1 != D_800DD5E0) {
        arg0 = func_15095380(arg0, D_800909C4, (u32)arg1 << 8, &sp30[1], 0, 0, 0, 2, 3);
        D_800DD5E0 = arg1;
    }
    return arg0;
}

void func_1517ABB4(f32, u8, s16, s16, s16);

void func_1517AF90(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s32 i;
  s32 x;
  s32 z;
  s32 m;
  f32 h;
  f32 f;
  if (arg0 < 12.0f)
  {
    return;
  }
  m = arg0 * 8.0f;
  arg0 *= 0.5f;
  for (i = 0; i < arg4; i++)
  {
    x = func_150ADA20() & 0x3F;
    z = func_150ADA20() & 0x3F;
    x -= 0x20;
    z -= 0x20;
    f = ((((u32) func_150ADA20()) % m) >> 4) + arg0;
    func_1517ABB4(f, func_150ADA20() & 1, arg1 + x, arg2, arg3 + z);
  }

}

void func_1517B0EC(s32 arg0, s32 arg1, s16 arg2) {
    func_1510BD34(arg0, arg2);
}
