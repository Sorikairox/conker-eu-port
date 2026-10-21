u16 func_1000FA64(u16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s16 arg6, s32 arg7, void *arg8, s32 arg9, s32 argA, s32 argB)
{
  s32 idx;
  s32 count;
  idx = D_80042B00;
  if (idx < 0x20)
  {
    D_80042B00++;
  }
  else
  {
    return 0;
  }
  if (arg7 != 0)
  {
        ((SfxEnt *) D_80041FE0)[idx].unk10 = argA | 0x12;
  }
  else
  {
        ((SfxEnt *) D_80041FE0)[idx].unk10 = (argA & 0x108) | 2;
  }
  if (argA & 0x40)
  {
    arg2 = func_15083E0C(arg1);
    if (arg2 == -1)
    {
      return 0;
    }
  }
  ((SfxEnt *) D_80041FE0)[idx].unk24 = 0;
  ((SfxEnt *) D_80041FE0)[idx].unk23 = 0;
  ((SfxEnt *) D_80041FE0)[idx].unk22 = 0;
  ((SfxEnt *) D_80041FE0)[idx].unk0 = arg0;
  ((SfxEnt *) D_80041FE0)[idx].unk2 = arg1;
  ((SfxEnt *) D_80041FE0)[idx].unk4 = arg2;
  ((SfxEnt *) D_80041FE0)[idx].unk6 = arg3;
  ((SfxEnt *) D_80041FE0)[idx].unk8 = arg5;
  ((SfxEnt *) D_80041FE0)[idx].unkA = arg6;
  ((SfxEnt *) D_80041FE0)[idx].unkC = arg4;
  ((SfxEnt *) D_80041FE0)[idx].unk14 = (void *) arg7;
  ((SfxEnt *) D_80041FE0)[idx].unk18 = (s32) arg8;
  ((SfxEnt *) D_80041FE0)[idx].unk1C = arg9;
  ((SfxEnt *) D_80041FE0)[idx].unk2C = alCents2Ratio(argB);
  ((SfxEnt *) D_80041FE0)[idx].unk26 = 0;
  ((SfxEnt *) D_80041FE0)[idx].unk28 = 0;
  ((SfxEnt *) D_80041FE0)[idx].unk20 = argB;
  count = D_80042B00;
  func_10011624(D_80041FE0, &D_80042B00, idx, idx + 1);
  if (count != D_80042B00)
  {
    return 0;
  }
  ((SfxEnt *) D_80041FE0)[idx].unk10 |= 0x1000;
  return ((SfxEnt *) D_80041FE0)[idx].unk24;
}
