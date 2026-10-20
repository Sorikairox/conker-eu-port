typedef struct { s32 u0; s16 u4; u8 u6; u8 u7; s32 u8; s32 uC; u8 u10, u11, u12, u13, u14, u15, u16, u17; s32 u18; s32 u1C; s16 u20; s16 u22; s16 u24; s16 u26; } E8_S;
s32 func_150ADA20(void);
struct210 *func_1513C650(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF);
void func_150E856C(f32 arg0, s32 arg1, s32 arg2, f32 *arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, s32 argB)
{
  E8_S s;
  f32 new_var;
  s32 k;
  s32 m;
  s32 c;
  s32 b;
  s32 a;
  s.u22 = 0x14;
  s.u24 = 0xC;
  new_var = arg0;
  s.u6 = 0x4F ^ 0;
  s.u7 = 0;
  if (arg4 == (-1))
  {
    b = 0;
  }
  else
  {
    b = 1;
  }
  if (arg5)
  {
    c = 0x400;
  }
  else
  {
    c = 0;
  }
  s.u0 = ((c | b) | 0x9300) | 0x40000;
  if (arg4 == (-1))
  {
    s.u4 = 0x12C;
  }
  else
  {
    s.u4 = arg4 + 0x14;
    if (1)
    {
    }
  }
  s.u8 = 0;
  s.uC = 0;
  s.u11 = 0xFF;
  s.u10 = arg1;
  s.u12 = arg7;
  s.u13 = arg8;
  s.u14 = arg9;
  s.u15 = 0xFF;
  if (arg6 != 0)
  {
    c = 2;
  }
  else
  {
    c = 1;
  }
  s.u18 = c + 0x480000;
  s.u16 = 0;
  s.u17 = 6;
  if (arg5 != 0)
  {
    k = 3;
    m = 0xFF;
  }
  else
  {
    arg9 += 0;
    k = 0;
    m = 0;
  }
  a = func_150ADA20();
  b = func_150ADA20();
  c = func_150ADA20();
  func_1513C650((s32) (&s), 0, 0, arg2, arg3[0], arg3[1], arg3[2], arg0, new_var, a & 0xFF, (u8) ((b & 1) + ((c & 1) * 2)), k, m, 0, argA, argB);
}
