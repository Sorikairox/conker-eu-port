s32 func_150ADA20(void);
s32 func_151EFDD0();
void func_1516FDD4(u8 *arg0);

s32 func_15170D50(u8 *arg0)
{
  s32 a;
  s32 v;
  s32 b;
  s8 hi;
  u8 lo;
  v = arg0[0x1F];
  if (arg0[0x24] != 0)
  {
    if (v == 0)
    {
      arg0[0x24] = (func_150ADA20() % 25U) + 0xC8;
    }
    if (v != 0xFE)
    {
      v += D_800BE9E4 << 6;
      if (v >= 0xFF)
      {
        v = 0xFE;
      }
      arg0[0x1F] = v;
    }
  }
  else
    if (v != 0)
  {
    v -= D_800BE9E4 * 0x10;
    if (v < 0)
    {
      v = 0;
    }
    arg0[0x1F] = v;
  }
  if ((arg0[0x24] == 0) && (v == 0))
  {
    return 1;
  }
  func_1516FDD4(arg0);
  if (arg0[0x2F] != 0)
  {
    func_1516FE5C((s32) arg0, (func_151EFDD0() % 32) + 0xE6);
    func_1516FE8C((s32) arg0, (func_151EFDD0() % 32) + 0xE6);
  }
  else
  {
    hi = ((s8 *) arg0)[0x26];
    lo = arg0[0x27];
    a = (hi << 8) + ((((((((lo & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF);
    b = (hi * 256) + lo;
    if (((a * a) + (b * b)) > 0x7D0)
    {
      func_1516FE5C((s32) arg0, (func_151EFDD0(hi, lo) % 32) + 0xDC);
      func_1516FE8C((s32) arg0, (func_151EFDD0() % 32) + 0xDC);
    }
  }
  *((s16 *) (arg0 + 0x18)) = 0;
  return 0;
}
