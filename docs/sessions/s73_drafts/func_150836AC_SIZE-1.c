u8 *func_1515D9F0(s32);
s32 func_1515D9B0(void);
void func_150836AC(u8 *arg0)
{
  u8 *t;
  s32 i;
  s32 sel;
  s32 tmp;
  u8 *p;
  t = *(u8 **)(arg0 + 0x144);
  if (t != 0)
  {
    tmp = t[0x2F]; sel = tmp;
    p = arg0;
    if (tmp == 0) { if (arg0[0x127] != 0) sel = 3; else sel = 5; }
    for (i = 0; i <= D_80082FA0; i++) { *(s32 *)(p + 0x304) = (s32)func_1515D9F0(sel); p += 4; }
    if (*(s32 *)(arg0 + i * 4 + 0x300) != 0)
    {
      arg0[0x301] = sel;
    }
    *(s32 *)(arg0 + 0x314) = func_1515D9B0();
  }
}
