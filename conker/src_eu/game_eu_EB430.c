#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A0370[];
extern u8 D_800A0340[];
#endif

#ifdef NON_MATCHING
void func_150BDC20(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        u8 padA4[0x4];
        s32 uA8;
        u8 padAC[0x14];
        s32 uC0;
        s32 uC4;
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        u8 padDC[0x14];
        s32 uF0;
        s32 uF4;
        s32 uF8;
        s32 uFC;
        s32 u100;
        s32 u104;
        f32 u108;
        f32 u10C;
        f32 u110;
        u8 pad114[0xC];
        s32 u120;
        s32 u124;
        s32 u128;
        s32 u12C;
        s32 u130;
        s32 u134;
    } sp;
    s32 *var_s0;
    s32 *var_s3;
    s32 *var_s4;
    s32 *var_s5;
    f32 *var_s1;
    f32 *var_s2;

    if (arg0 != NULL) {
        var_s1 = &D_800A0310;
        var_s2 = &sp.u108;
        if ((*(u8 **)((u8 *)arg0 + 0x1D4)) != NULL) {
            var_s5 = ((u8 *)&D_800A0370);
            var_s3 = ((u8 *)&D_800A0340);
            var_s4 = &sp.uD8;
            var_s0 = &sp.uA8;
            do {
                func_15143134(var_s1, var_s2, (*(u8 **)((u8 *)arg0 + 0x1D4)));
                func_15143134(var_s3, var_s4, (*(u8 **)((u8 *)arg0 + 0x1D4)));
                func_15143134(var_s5, var_s0, (*(u8 **)((u8 *)arg0 + 0x1D4)));
                var_s0 = (s32 *)((u8 *)var_s0 + (0xC));
                var_s1 = (f32 *)((u8 *)var_s1 + (0xC));
                var_s2 = (f32 *)((u8 *)var_s2 + (0xC));
                var_s3 = (s32 *)((u8 *)var_s3 + (0xC));
                var_s4 = (s32 *)((u8 *)var_s4 + (0xC));
                var_s5 = (s32 *)((u8 *)var_s5 + (0xC));
            } while (var_s0 != &sp.uD8);
            sp.u8C = sp.uC0 - sp.uF0;
            sp.u90 = sp.uC4 - sp.uF4;
            sp.u94 = sp.uC8 - sp.uF8;
            func_1514C9E0(sp.u120, sp.u124, sp.u128, sp.u12C, sp.u130, sp.u134, (func_150ADA68() * 6.0f) + 14.0f, 0xDU, 0, 0.0f, (s32) &sp.u8C, (u8) (s32) arg1);
            sp.u98 = sp.uCC - sp.uFC;
            sp.u9C = sp.uD0 - sp.u100;
            sp.uA0 = sp.uD4 - sp.u104;
            func_1514C9E0(sp.u12C, sp.u130, sp.u134, sp.u108, sp.u10C, sp.u110, (func_150ADA68() * 6.0f) + 14.0f, 0xDU, 0, 0.0f, (s32) &sp.u98, (u8) (s32) arg1);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EB430/func_150BDC20.s")
#endif
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
