f32 func_151CC784(u8 *arg0);

s32 func_151CBF20(u8 *arg0)
{
  u8 *p;
  f32 t;
  f32 k;
  f32 lo;
  unsigned char a;
  p = arg0 + 0x70;
  k = (1.0f - ((func_151CC784(arg0) - (*((f32 *) (p + 0x18)))) * (*((f32 *) (p + 0x20))))) * 75.0f;
  if (p[0xC] & 1)
  {
    lo = 91.0f + k;
    *((f32 *) (arg0 + 0x14)) = (sinf(*((f32 *) (p + 0x10))) * ((112.0f + k) - lo)) + lo;
    *((f32 *) (p + 0x10)) += 0.505f * D_800BE9A4;
    if ((*((f32 *) (p + 0x10))) >= 3.1415927f)
    {
      *((f32 *) (arg0 + 0x14)) = lo;
      p[0xC] &= 0xFFFE;
    }
  }
  else
  {
    *((f32 *) (arg0 + 0x14)) = 91.0f + k;
  }
  if (p[0xD] == 2)
  {
    *((f32 *) (arg0 + 0x14)) -= 20.0f;
  }
  a = *((f32 *) (p + 0x14));
  if (arg0[0x20] == 0x7C)
  {
    arg0[0x2E] = 0xFF - a;
  }
  else
  {
    arg0[0x2E] = a;
  }
  t = *((f32 *) (p + 0x14));
  *((f32 *) (p + 0x14)) = t + ((255.0f - t) * 0.67600006f);
  return 1;
}
