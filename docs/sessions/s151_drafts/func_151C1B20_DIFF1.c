void func_151C1B20(void *arg0)
{
  u8 **q = (u8 **) (&arg0);
  struct102 *a;
  u8 *p;
  u8 *v;
  if ((*((s32 *) ((*q) + 0x1F0))) != 0)
  {
    func_1516972C(*((struct102 **) ((*q) + 0x1F0)));
  }
  p = (*q) + 0x170;
  if ((*((struct102 **) (p + 0x84))) != 0)
  {
    func_1516972C(*((struct102 **) (p + 0x84)));
  }
  v = *((u8 **) (p + 0x88));
  if (v != 0)
  {
    s32 *w = (s32 *) ((*((u8 **) (p + 0x88))) + 0x110);
    *w = 0;
  }
  if ((*((struct102 **) (p + 0x8C))) != 0)
  {
    func_1516972C(*((struct102 **) (p + 0x8C)));
  }
  func_1000FD38(func_151C16BC, *q, 0);
}
