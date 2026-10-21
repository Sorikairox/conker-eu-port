#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 (*D_8008B068[])(u8 *);

void func_15155200(u8 *arg0)
{
  s32 pad; // fakematch: puts done at sp+0x1B
  s8 done = 0;
  u8 *p;
  u8 *q;
  s16 v;
  p = arg0;
  if ((*((u16 *) (p + 0x24))) & 1)
  {
    *((s16 *) (p + 0x22)) -= D_800BE9E4;
    if ((*((s16 *) (p + 0x22))) < 0)
    {
      done = 1;
    }
  }
  if ((p[0x68] & 0xF) && (!done))
  {
    if (D_8008B068[p[0x68] & 0xF](p) == 0)
    {
      done = 1;
    }
  }
  if ((*((u16 *) (p + 0x24))) & 8)
  {
    if ((*((s16 *) (p + 0x22))) < (*((s16 *) (p + 0x26))))
    {
    q = p; // fakematch: second name for the 0x22 reload
      v = (*((s16 *) (p + 0x28))) * (*((s16 *) (q + 0x22)));
      if (v < p[0x2E])
      {
        arg0[0x2E] = v;
      }
    }
  }
  if (done)
  {
    func_1516972C((struct102 *) p);
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_182A10/func_151552F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_182A10/func_151559FC.s")

void func_15155AD4(u8 *arg0, s32 arg1, u8 arg2) {
    void (*fp)(void *, s32, u8) = D_8008B0A4[arg0[0x2A]];
    if (fp != NULL) {
        fp(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_182A10/func_15155B1C.s")

void func_15155C9C(void *arg0, u8 arg1) {
    const s32 sp18[2] = {0x5D, 0x57};

    func_15169260(sp18, 0x2, (s32)arg0, arg1);
}
