// PERMUTER CHANGED DECL: s32func_1518403C(s32) (base: s32func_1518403C(s32arg0))
void func_1510D3E0(s32, s32, s32, s32, s32 *);
s32 func_1518403C(s32 arg0)
{
  u8 *temp_v0;
  s32 *p;
  if ((*((s32 *) (((u8 *) D_800DDE80) + (arg0 * 0x14)))) == 0)
  {
    temp_v0 = func_1502B6BC(0, 0, 0, 2, 9, arg0 + 0xAD);
    if (temp_v0 != 0)
    {
      *((u8 **) (((u8 *) D_800DDE80) + (arg0 * 0x14))) = temp_v0;
 do { *((s32 *) ((((u8 *) D_800DDE80) + (arg0 * 0x14)) + 4)) = *((s32 *) (temp_v0 + 0)); *((s32 *) ((((u8 *) D_800DDE80) + (arg0 * 0x14)) + 8)) = *((s32 *) (temp_v0 + 8)); *((s32 *) ((((u8 *) D_800DDE80) + (arg0 * 0x14)) + 0xC)) = *((s32 *) (temp_v0 + 0x18)); } while (0);
      *(p = &D_800DDF78[arg0]) = *((s32 *) (temp_v0 + 0x10));
      func_1510D3E0(*p, 0, 1, 0x3E, (s32 *) ((((u8 *) D_800DDE80) + (arg0 * 0x14)) + 0x10));
      D_800DDF68[arg0] = 1;
    }
  }
}
