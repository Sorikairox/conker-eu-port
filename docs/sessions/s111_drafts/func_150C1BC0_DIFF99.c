s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_15148310(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32);
extern f32 D_800A05C0;
extern f32 D_800A05C4;
extern f32 D_800A05C8;
extern f32 D_800A05CC;
extern f32 D_800A05D0;
s32 func_150C1BC0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE)
{
  struct { f32 u0; f32 u4; f32 u8; s16 uC; s16 uE; s32 u10; u8 u14; u8 u15; u8 pad[0xA]; } c;
  struct { f32 u0; f32 u4; f32 u8; f32 uC; f32 u10; f32 u14; u8 u18; u8 u19; u8 u1A; u8 u1B; s32 pad; } b;
  struct { s32 u0; s32 u4; s32 u8; s32 uC; s32 u10; s32 u14; s32 u18; u8 u1C; u8 u1D; } a;
  s32 n;
  s16 x;
  f32 s;
  f32 sx;
  f32 cx;
  f32 sa;
  f32 ca;
  a.u4 = 1;
  a.u8 = 0x160600;
  a.uC = 3;
  a.u10 = 0x10;
  a.u0 = 0;
  a.u14 = 0x80;
  a.u18 = 0x20;
  a.u1C = 0;
  a.u1D = 9;
  c.u10 = 1;
  c.uE = 1;
  b.u19 = 0xA;
  b.u1A = 0xFF;
  b.u18 = 0x28;
  b.u1B = 0xFF;
  c.u0 = arg2;
  c.u4 = arg3;
  c.u8 = arg4;
  n = 1;
  while (n != 0)
  {
    x = (func_150ADA20() % 13U) - 0x3F;
    sx = func_151423D8(x);
    cx = func_151423D8(x - 0x40);
    sa = func_151423D8(arg8);
    ca = func_151423D8(arg8 - 0x40);
    s = (func_150ADA68() * D_800A05C0) + 25.5f;
    c.u15 = (func_150ADA20() % 9U) + 5;
    c.uC = (func_150ADA20() & 0x3F) + 0x5A;
    b.u0 = (func_150ADA68() * D_800A05C4) + D_800A05C8;
    b.u10 = (func_150ADA68() * D_800A05CC) + D_800A05D0;
    b.u4 = s * sx * ca;
    b.u8 = -s * cx;
    b.uC = s * sx * sa;
    func_15148310(&c, &b, 0, 1, 5, 0, 0, 0, 0, 0, 0, &a, 0, argE, 0);
    n--;
  }
  return 1;
}
