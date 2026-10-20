#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EB430/func_150BDC20.s")

s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_15148310(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32);
extern f32 D_800A03A0;
extern f32 D_800A03A4;
extern f32 D_800A03A8;
extern f32 D_800A03AC;
extern f32 D_800A03B0;
extern f32 D_800A03B4;
s32 func_150BDE34(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, f32 *argD, u8 argE)
{
  struct { f32 u0; f32 u4; f32 u8; s16 uC; s16 uE; s32 u10; u8 u14; u8 u15; u8 pad[0xA]; } c;
  struct { f32 u0; f32 u4; f32 u8; f32 uC; f32 u10; f32 u14; u8 u18; u8 u19; u8 u1A; u8 u1B; s32 pad; } b;
  struct { s32 u0; s32 u4; s32 u8; s32 uC; s32 u10; s32 u14; s32 u18; u8 u1C; u8 u1D; s32 pad; } a;
  f32 t;
  a.u4 = 1;
  a.u8 = 0x160600;
  a.u0 = 0;
  a.uC = 3;
  a.u10 = 0x10;
  a.u14 = 0x80;
  a.u18 = 0x20;
  a.u1C = 0;
  a.u1D = 9;
  c.u10 = 1;
  c.uE = 1;
  c.u0 = arg2;
  c.u4 = arg3;
  b.u14 = arg3;
  b.u19 = 9;
  b.u1A = 0xFF;
  b.u18 = 8;
  c.u8 = arg4;
  t = ((func_150ADA68() * 127.0f) + 85.0f) * D_800A03A0;
  b.u4 = argD[0] * t;
  b.u8 = argD[1] * t;
  b.uC = argD[2] * t;
  b.u1B = (func_150ADA20() % 86U) + 0xB4;
  c.u15 = (func_150ADA20() & 3) + 3;
  c.uC = (func_150ADA20() % 31U) + 0x27;
  b.u0 = ((func_150ADA68() * D_800A03A4) + D_800A03A8) * D_800A03AC;
  b.u10 = ((func_150ADA68() * 356.0f) + D_800A03B0) * D_800A03B4;
  func_15148310(&c, &b, 0, 1, 0xB, 0, 0, 0, 0, 0, 0, &a, 0, argE, 1);
  return 1;
}

s32 func_150BE01C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    if ((*(s16 *)(arg0 + 0x1C) << 3) < temp_v0[0x1B]) {
        temp_v0[0x1B] = *(s16 *)(arg0 + 0x1C) << 3;
    }
    return 1;
}
