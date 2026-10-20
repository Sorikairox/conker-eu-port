typedef struct { f32 f0; u8 pad4[0x14]; s32 u18; s8 u1C; s8 u1D; u8 pad1E[2]; s32 u20; } S5C;
extern f32 D_800A1F44, D_800A1F48, D_800A1F4C;
void func_15137F30(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC);
s32 func_1504715C(S5C *, s32);
void func_150F6EDC(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, u8 *arg5)
{
  f32 spA4[3];
  f32 sp98[3];
  f32 sp8C[3];
  f32 sp88;
  s16 sp86;
  u8 sp85;
  f32 sp80;
  S5C s;
  u8 a;
  s32 b;
  func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, spA4, sp98, sp8C, &sp88, &sp86, &sp85, &sp80);
  sp80 *= 1.0f + (2.0f * func_150ADA68());
  b = func_150ADA68() < D_800A1F44;
  a = b;
  if ((u8) b)
  {
    func_1504715C(&s, *((s32 *) (arg5 + 0x1C)));
  }
  else
  {
    s.u18 = 0;
    s.u1C = 0;
    s.u1D = 0;
    s.u20 = 0;
    s.f0 = D_800A1F48;
  }
  b = b * 0;
  if (a)
  {
    b = (func_150ADA68() < 0.5f) ? (1) : (0);
  }
  func_151D9014(spA4, sp8C, 1, sp88, sp86, sp85, sp80, a, D_800A1F4C, D_800A1F4C, 1, (s32) (&s), 1, b, arg5[0xC], arg5[1]);
}
