#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15179420(void) {
    D_800DD864 = 0;
    D_800DD876 = 0;
    D_800DD444 = 600;
    D_800DD862 = 0xF0;
    D_800DD863 = 0x14;
    D_800DD866 = 0;
    D_800DD870 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_1517946C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179008.s")

extern s32 D_800DD868[];
void func_15179A38(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 pad; // fakematch: frame slot 0x30 (unknown named local)
    f32 vy;
    f32 vz;
    f32 s;
    f32 a;
    f32 c;
    f32 vx;
    s16 *p;

    x = D_800DBFF0->unk2F8;
    y = D_800DBFF0->unk2FC;
    z = D_800DBFF0->unk300;
    a = D_800DBFF0->unk398;
    s = func_150AD78C(a);
    c = func_150AD780(a);
    vy = 500.0f * s;
    vz = -500.0f * c;
    vx = 0.0f;
    a = D_800DBFF0->unk3A0;
    s = func_150AD78C(a);
    c = func_150AD780(a);
    x += (vx + (vz * s));
    z += ((vz * c) - vx);
    y += vy;
    p = (s16 *)D_800DD868;
    p[0] = x;
    p[2] = z;
    p[1] = y;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179D20.s")

int func_1517A028(void)
{
  s32 temp_v0;
  s32 var_v1;
  u8 **var_a0;
  s32 temp_a1;
  u8 *temp_v0_2;
  int new_var;
  new_var = D_800DD866 - 1;
  temp_v0 = new_var;
  if (temp_v0 >= 0)
  {
    var_v1 = temp_v0 * 4;
    var_a0 = D_800DD870 + var_v1;
    loop_2:
    temp_v0_2 = *var_a0;

    var_v1 -= 4;
    if (temp_v0_2 != 0)
    {
      if (((*((s32 *) (((u8 *) temp_v0_2) + 0x90))) & 2) == 0)
      {
        *((s32 *) (((u8 *) temp_v0_2) + 0x90)) |= 2;
        return;
      }
    }
    var_a0 -= 1; // fakematch: dead pointer decrement
    if (var_v1 < 0)
    {
    }
    else
    {
      goto loop_2;
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_1517A084.s")

void func_1517A220(u8 *arg0) {
    f32 temp_f12;
    f32 temp_f2;
    f32 dist;

    temp_f2 = (f32) *(s16 *)(arg0 + 0xA0) - D_800DBFF0->unk300;
    temp_f12 = (f32) *(s16 *)(arg0 + 0x9C) - D_800DBFF0->unk2F8;
    dist = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
    *(u8 *)(arg0 + 0xB4) = (s8)(u32)(255.0f - ((160.0f * dist) / 1000.0f));
}
