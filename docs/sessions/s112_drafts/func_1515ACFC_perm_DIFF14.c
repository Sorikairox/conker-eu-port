s32 func_15046EF0(u8 *, u16, f32, u8 *);
s32 func_1514672C(u8 *);
s32 func_1515AB7C(u8 *, u8 *);
u8 func_151D8E20(void);

u8 func_1515ACFC(u8 *arg0, u8 *arg1)
{
  u8 flag;
  u8 new_var2;
  u8 *new_var;
  f32 v[3];
  f32 *p;
  f32 f;
  flag = 1;
  func_1515AB7C(arg0, arg1);
  new_var = arg1;
  if ((*((f32 *) (arg0 + 0x5C))) < 0.0f)
  {
    return 1;
  }
  v[0] = (*((f32 *) (arg0 + 0x4C))) + (*((f32 *) (arg0 + 0x40)));
  v[1] = *((f32 *) (new_var + 4));
  p = (f32 *) (arg0 + 0xA8);
  v[2] = (*((f32 *) (arg0 + 0x54))) + (*((f32 *) (arg0 + 0x48)));
  if (1)
  {
    f = p[8];
  }
  if ((-99999.9f) == f)
  {
    if (func_1514672C((u8 *) v) == 0)
    {
      return 0;
    }
    if (func_15046EF0((u8 *) v, 0, *((f32 *) (arg0 + 0x44)), arg0 + 0x80) != 0)
    {
      flag = 0;
      v[1] = *((f32 *) (arg0 + 0x80));
    }
  }
  else
    if (f <= (*((f32 *) (arg0 + 0x44))))
  {
    v[1] = f;
    flag = 0;
  }
  if (((flag == 0) && (func_150ADA68() < 0.2f)) && (arg0[0x9D] == 3))
  {
    new_var2 = func_151D8E20();
    func_151DBCBC(new_var2, (*p) * 0.2f, arg0[0x2B], (s32) (arg0 + 0x84), v, arg0[0xC], arg0[1]);
  }
  return flag;
}
