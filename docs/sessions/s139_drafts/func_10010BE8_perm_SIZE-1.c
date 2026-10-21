s32 func_10017438(s32, s16, u16, u8, f32, s32, s32, struct31 **);
extern s32 D_8003E708;
extern u16 D_80042984;

u16 func_10010BE8(u16 arg0, s32 arg1, u16 arg2, u8 arg3, s16 arg4, u8 arg5, u8 arg6)
{
  u32 var_s1;
  struct120 *temp_s0;
  u16 id;
  s32 t;
  u8 vol;
  if (!D_80042984)
  {
  }
  var_s1 = arg0 & 0xF;
  temp_s0 = &D_800425E0[var_s1];
  if ((temp_s0->unk0 == arg0) && (arg0 != 0))
  {
    if ((temp_s0->unk8 != 0) && (func_100173C4(&temp_s0->unk8) != 0))
    {
      func_10017594(temp_s0->unk8);
      temp_s0->unk8 = 0;
    }
  }
  else
    if ((((temp_s0->unk8 != 0) && (func_100173C4(&temp_s0->unk8) != 0)) || (temp_s0->unk4 & 0x8000)) && ((((var_s1 = 0, ((s32 *) (&D_80042984))[1] != 0)) && (func_100173C4((struct31 **) D_80042988) != 0)) || (D_80042984 & 0x8000)))
  {
    loop_11:
    var_s1 += 1;

    if (var_s1 < 0x10U)
    {
      temp_s0 = &D_800425E0[var_s1];
      if (((temp_s0->unk8 != 0) && (func_100173C4(&temp_s0->unk8) != 0)) || (temp_s0->unk4 & 0x8000))
      {
        goto loop_11;
      }
    }
  }
  if (arg2 < 100)
  {
    return 0;
  }
  if (var_s1 >= 0x10)
  {
    id = 0;
  }
  else
  {
    if (arg1 == 0)
    {
      return 0;
    }
    t = arg1 & 0x7FFF;
    if (t >= 0x6E3)
    {
      return 0;
    }
    temp_s0 = &D_800425E0[var_s1];
    id = temp_s0->unk2;
    temp_s0->unk0 = id;
    arg0 = id + 0x10;
    if (arg0 < 0x10)
    {
      arg0 += 0x10;
    }
    temp_s0->unk2 = arg0;
    temp_s0->unk4 = arg1;
    if (temp_s0->unk8 != 0)
    {
      temp_s0->unk8->unk54 = 5;
    }
    if (((arg5 & 0x7F) + ((u8) D_80041FD8)) < 0x80)
    {
      vol = arg5 + ((u8) D_80041FD8);
    }
    else
    {
      vol = arg5 | 0x7F;
    }
    func_10017438(D_8003E708, t, arg2, arg3, alCents2Ratio(arg4), vol, arg6, &temp_s0->unk8);
  }
  return id;
}
