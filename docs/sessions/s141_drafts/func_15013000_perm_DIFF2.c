void func_15013000(void)
{
  s32 off;
  int new_var2;
  u32 i;
  int new_var;
  void (*fn)(u8 *);
  D_800DCDC4 = 0;
  D_800DCD90 = 0.0f;
  if (((!off) && (!off)) && (!off))
  {
  }
  new_var = 0x15;
  off = (i = 0);
  if (D_800D3094 != 0)
  {
    do
    {
      new_var2 = (D_800D34B8[off + new_var] >> ((0, 2))) & 0xFF;
      fn = D_800831C0[new_var2];
      if (fn != 0)
      {
        fn(D_800D34B8 + (off ^ 0));
      }
      i += 1;
      off += 0x34;
    }
    while (i < ((u32) D_800D3094));
  }
}
