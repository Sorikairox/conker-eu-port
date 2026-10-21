void func_1501C15C(u8);
extern void (*D_80090060[])(u8 *);

void func_eu_151D8FD4(u8 *arg0)
{
  s32 pad;
  u8 done = 0;
  s32 i;
  s32 v;
  if (arg0[0xE] & 1)
  {
    *((s16 *) (arg0 + 0x10)) -= D_800BE9E4;
    if ((*((s16 *) (arg0 + 0x10))) < 0)
    {
      done = 1;
    }
  }
  if (((s8) arg0[0x14]) != (-1))
  {
    D_80090060[(s8) arg0[0x14]](arg0);
  }
  i = 0;
  v = 0;
  if (arg0[0x12] != arg0[0x16])
  {
    do
    {
      if (arg0[0x13] & (1 << v))
      {
        func_1501C15C(i);
        func_1501BFF0(i & 0xFF, arg0[0x12]);
      }
 do { i++; v = i & 0xFF; } while (0);
      i = v;
    }
    while (v < 4);
    arg0[0x16] = arg0[0x12];
  }
  if (done)
  {
    func_1516972C((struct102 *) arg0);
  }
}
