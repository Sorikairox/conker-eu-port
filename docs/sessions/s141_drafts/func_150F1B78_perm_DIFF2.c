void func_150F1B78(u8 *arg0, u8 * volatile arg1, volatile u8 arg2)
{
  u8 **q = &arg0;
  u8 *p;
  u8 *t;
  s32 a;
  if (arg2 == 0x43)
  {
 if (1) { }
    a = *((s32 *) arg1);
    p = (*q) + 0x28;
    t = arg1;
    if ((a == (*((s32 *) p))) || (p[4] == (t[4] & 0xFFFFu)))
    {
      func_1516972C(*q);
    }
  }
  else
  {
    p = (*q) + 0x28;
    func_15149514(arg1, arg2, p, p + 4, *q);
  }
}
