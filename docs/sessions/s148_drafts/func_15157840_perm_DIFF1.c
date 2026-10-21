extern s32 (*D_8008B130[])(u8 *);
extern s32 (*D_8008B140[])(u8 *);
void func_15157840(u8 *arg0)
{
  s32 pad;
  u8 done = 0;
  s16 v;
  s32 m;
  if (arg0[0x10] & 1)
  {
    *((s16 *) (arg0 + 0x16)) -= D_800BE9E4;
    if ((*((s16 *) (arg0 + 0x16))) < 0)
    {
      done = 1;
    }
  }
  if (!done)
  {
    if ((*((s8 *) (arg0 + 0x11))) != (-1))
    {
      if (!D_8008B130[*((s8 *) (arg0 + 0x11))](arg0))
      {
        done = 1;
      }
    }
    if ((*((s8 *) (arg0 + 0x12))) != (-1))
    {
      if (!D_8008B140[*((s8 *) (arg0 + 0x12))](arg0))
      {
        done = 1;
      }
    }
  }
  if (!done)
  {
    func_1503F7A0(*((s32 *) (arg0 + 0x68)));
  }
  if ((!done) && (arg0[0x10] & 0x20))
  {
    v = *((s16 *) (arg0 + 0x16));
    if (v < (*((s16 *) (arg0 + 0x64))))
    {
      m = v * (*((s16 *) (arg0 + 0x66)));
      if (m < arg0[0x43])
      {
        if (!m)
        {
        }
        arg0[0x43] = m;
      }
    }
  }
  if (done)
  {
    func_1516972C((struct102 *) arg0);
  }
}
