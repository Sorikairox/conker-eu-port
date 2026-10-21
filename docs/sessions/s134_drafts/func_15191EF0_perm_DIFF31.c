void func_15191EF0(struct102 *arg0, u8 * volatile arg1, u8 arg2)
{
  u8 *new_var2;
  s32 new_var3;
  if (arg2 == 0xD)
  {
    s32 new_var;
    new_var = *((s32 *) (arg1 + 0));
    if (((*((s32 *) (((u8 *) arg0) + 0x10))) == new_var) || (arg0->unk14 == (*((u8 *) (arg1 + 4)))))
    {
      arg0->unk18 |= 1;
      new_var2 = ((u8 *) arg0) + 0x16;
      *((s16 *) new_var2) = 0x64;
    }
  }
  else
    if (((arg2 == 0xC) || (arg2 == 0x50)) || (arg2 == 0xE))
  {
    if (((*((s32 *) (((u8 *) arg0) + 0x10))) == (*((s32 *) (arg1 + 0)))) || (arg0->unk14 == (*((u8 *) (arg1 + 4)))))
    {
      func_1516972C(arg0);
    }
  }
  else
  {
    new_var3 = (s32) arg1;
    if (arg2 == 0x4E)
    {
      func_1516972C(arg0);
    }
    else
    {
      func_15169850(new_var3, (&arg2)[0], (s32) (&arg0->unk10), (s32) (&arg0->unk14), (s32) arg0);
    }
  }
}
