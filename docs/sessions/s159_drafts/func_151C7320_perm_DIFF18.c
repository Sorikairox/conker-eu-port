s32 func_151030B8(s32, u8, u8 *, u8 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern u32 D_800AAEE0[];
extern u8 D_800AAEE8[];
extern u8 D_800AAF00[];
extern f32 D_800AAFF0;
extern f32 D_800AAFF4;
extern f32 D_800AAFF8;
extern f32 D_800AAFFC;
extern f32 D_800AB000;

void func_151C7320(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5)
{
  f32 v[2];
  volatile unsigned int r1;
  s32 new_var;
  s32 r0;
  v[1] = (func_150ADA68() * D_800AAFF0) + D_800AAFF4;
  v[0] = (func_150ADA68() * D_800AAFF8) + D_800AAFFC;
  r0 = func_150ADA20();
  r1 = func_150ADA20();
  func_151030B8(new_var = arg0, D_800AAEE0[arg1] >> 6, D_800AAEE8 + (arg1 * 12), D_800AAF00 + (arg1 * 12), v, (r0 & 3) + 6, 0xFF, (func_150ADA68() * 270.0f) + D_800AB000, arg2, 0xFF, 0, arg3, arg4, arg5);
}
