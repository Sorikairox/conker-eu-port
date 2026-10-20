void func_151640C0(u8 *arg0, u8 *arg1, u8 arg2)
{
  u8 **q = &arg0; // fakematch: shape C home reload
  u8 **r = &arg1; // fakematch: shape C home reload
  u8 *a;
  u8 *v;
  s32 k;
  s32 w;
  u8 b;
  u8 c;
  if (arg2 == 0x29)
  {
    a = *(u8 **)(*r + 4);
    v = *q;
    v = v + 0x18; // fakematch: split add keeps the reload in v0 (permuter)
    k = *(s32 *)a;
    w = *(s32 *)v;
    c = v[4];
    b = a[4];
    if ((w == k) || (c == b) || (b == ((u8 *)w)[0x3B]))
    {
      func_1516972C((struct102 *)*q);
    }
  }
}
