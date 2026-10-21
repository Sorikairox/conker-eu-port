extern u8 D_800DFC00[];
extern s32 D_800DFDE8[];
extern s32 *D_800E0578[];
s32 func_1518C900(s32 arg0)
{
  s32 *p;
  u8 *cnt = &D_800DFC00[arg0];
  if ((*cnt) == 0)
  {
    p = (s32 *) func_1502B6BC(0, 0, 0, 2, 9, arg0);
    if (p == 0)
    {
      return 0;
    }
    func_1510D3E0(*p, 0, 1, 0x3E, &D_800DFDE8[arg0]);
    func_15168E54(*p, p);
 if (0) { }
    D_800E0578[arg0] = p;
  }
  else
  {
    p = D_800E0578[arg0];
  }
  if ((*cnt) != 0xFF)
  {
    (*cnt)++;
  }
  return *p;
}
