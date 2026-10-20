void func_15135480(struct161520 *arg0, struct161520_msg *arg1, u8 arg2)
{
  s32 t;
  s32 k;
  if (arg2 == 0x2D)
  {
    if (arg0->unk1C == arg1->unk0)
    {
      arg0->unk1C = arg1->unk4.w;
      arg0->unk18 = arg1->unk9;
    }
    else
      if (arg0->unk1C == arg1->unk4.w)
    {
      t = arg1->unk0;
      arg0->unk1C = t;
      arg0->unk18 = arg1->unk8;
    }
  }
  switch (arg0->unk50)
  {
    case 1:
      func_151355B8(arg0, arg1, arg2);
      break;

    case 2:
      func_1513555C(arg0, arg1, arg2);
      break;

    default:
      if (arg2 == 0)
    {
      k = arg0->unk1C;
      if (((k ^ 0) == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) // fakematch: (k ^ 0) keeps the key in v0 (s71/s72)
      {
        func_1516972C((struct102 *) arg0);
      }
    }
      break;

  }

}
