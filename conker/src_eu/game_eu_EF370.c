#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* s32 slots as in game_eu_EF6D0: the caller masks the tag itself (andi), IDO would skip the mask for a u8 parameter */
s32 func_1514C860(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

/* spawn_ring_kind2_small: P238: emits 25 points of spawn handler kind 2 (D_8008ADA0) on a radius-80 ring around
 * (x, y, z), starting at byte angle 0 and stepping by 3, with arg8 / arg9 / argA 0 and the byte `tag` as argB
 * (func_1514C860, spawn_ring_emit). Its only caller (func_150C3994, asm) passes 0xFF and ignores v0; the asm leaves
 * func_1514C860's v0 in place, so it is returned. */
s32 func_150C1B60(f32 x, f32 y, f32 z, s32 tag) {
    return func_1514C860(x, y, z, 80.0f, 0, 3, 0x19, 2, 0, 0.0f, 0, tag & 0xFF);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EF370/func_150C1B60.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EF370/func_150C1BC0.s")

s32 func_150C1E78(u8 *arg0)
{
  s32 t;
  s32 v;
  u8 *q;
  q = *((u8 **) (arg0 + 0x98));
  v = *((s16 *) (arg0 + 0x1C));
  t = (v * 8) & 0xFFFFFFFFFFFFFFFF; // fakematch: 64-bit mask keeps t in a temp register
  v = t;
  if (t >= 0x100)
  {
    v = 0xFF;
  }
  q[0x1B] = v;
  if ((v & 0xFF) < 0)
  {
    return 0;
  }
  return 1;
}
