extern u8 *D_80086F40[];
s32 func_1507F834(void)
{
  u8 *p;
  s32 type;
  u8 new_var2;
  short b;
  p = (u8 *) D_800D154C->unk31C;
  type = p[0x5C];
  p += 0x58;
  new_var2 = 0;
  if (type == new_var2)
  {
    return 1;
  }
  b = p[5] + 1;
  p[5] = b;
  new_var2 = b;
  b = D_80086F40[type][new_var2];
  if (b == 0)
  {
    p[4] = 0;
    p[5] = 0;
    return 1;
  }
  return 0;
}
