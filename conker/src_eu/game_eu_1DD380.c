#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15046F70(f32 *, s32, f32, s32);
s32 func_1504715C(s32, struct127 *);
extern u8 D_800AA4D0[];
extern u8 D_800AA4DC[];
s32 func_151AFB70(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    func_15143134((arg3 == 1) ? D_800AA4DC : D_800AA4D0, arg0, (arg3 == 1) ? *(u8 **)(arg1 + 0x1D4) + 0x800 : *(u8 **)(arg1 + 0x1D4) + 0x640);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 100.0f;
    sp2C[2] = arg0[2];
    func_1504715C(arg2, (struct127 *) arg1);
    return func_15046F70(sp2C, 0, arg0[1] - 500.0f, arg2);
}

s32 func_151AFC70(s32 arg0, s32 arg1) {
    return 0xC;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DD380/func_151AFC84.s")

s32 func_151B0184(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    s32 temp_v1;

    if (temp_v0 < 32) {
        temp_v1 = temp_v0 << 3;
        if (temp_v1 < arg0[0x28]) {
            arg0[0x28] = temp_v1;
        }
    }
    return 1;
}

s32 func_eu_151B01B8(u8 *arg0)
{
  f32 temp_f0;
  s32 temp_v1;
  u8 *p;
  p = arg0 + 0x128;
  if ((*((s32 *) (((u8 *) arg0) + 0x58))) & 1)
  {
    temp_v1 = *((s16 *) (((u8 *) arg0) + 0x1C));
    if (temp_v1 < 0x20)
    {
      if ((temp_v1 * 8) < ((s32) (*((u8 *) (((u8 *) arg0) + 0x5C)))))
      {
        *((u8 *) (((u8 *) arg0) + 0x5C)) = (u8) (temp_v1 * 8);
      }
    }
    temp_v1 = *((s16 *) (((u8 *) arg0) + 0x1C));
    temp_f0 = temp_f0;
    if ((*((s16 *) p)) < temp_v1)
    {
      temp_f0 = (*((f32 *) (p + 4))) * D_800BE9A4;
      *((f32 *) (((u8 *) arg0) + 0x2C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x2C))) + temp_f0);
      *((f32 *) (((u8 *) arg0) + 0x30)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x30))) + temp_f0);
    }
  }
  return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DD380/func_151B0238.s")

s32 func_151B0454(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}
