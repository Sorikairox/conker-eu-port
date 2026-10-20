s32 func_15047274(u8 *, u16, f32, u8 *);
s32 func_1514672C(u8 *);
s32 func_151925AC(s32 *, f32 *, f32, s16, s32, s32, f32, s32, f32, u8 *, s32, s32, s32);

void func_151922C4(u8 *arg0)
{
  u8 *temp_s0;
  u8 *temp_s1;
  s32 spB4[3];
  s32 var_s1;
  f32 spA4[3];
  f32 temp_f20;
  f32 temp_f2;
  f32 var_f26;
  s32 temp_s2;
  s32 temp_s3;
  s32 temp_v0;
  temp_s1 = *((u8 **) (((u8 *) arg0) + 0x28));
  temp_s0 = arg0 + 0x28;
  if (((*((s32 *) (((u8 *) temp_s1) + 0))) == 0) || ((*((u8 *) (((u8 *) temp_s0) + 4))) != (*((u8 *) (((u8 *) temp_s1) + 0x3B)))))
  {
    *((s16 *) (((u8 *) arg0) + 0xE)) = -1;
    return;
  }
  *((f32 *) (((u8 *) temp_s0) + 0x18)) = (f32) ((((*((f32 *) (((u8 *) temp_s0) + 0x1C))) + (func_150ADA68() * (*((f32 *) (((u8 *) temp_s0) + 0x20))))) * D_800BE9A4) + (*((f32 *) (((u8 *) temp_s0) + 0x18))));
  temp_f2 = *((f32 *) (((u8 *) temp_s0) + 0x18));
  if (temp_f2 > 1.0f)
  {
    temp_v0 = *((s32 *) (((u8 *) temp_s1) + 0x1D4));
    if (temp_v0 != 0)
    {
      func_15143134(temp_s0 + 8, spB4, temp_v0 + (*((s32 *) (((u8 *) temp_s0) + 0x14))));
      temp_f20 = -9500.0f;
      if ((*((f32 *) (((u8 *) temp_s0) + 0x60))) > 0.0f)
      {
        if (func_1514672C((u8 *) spB4) == 0)
        {
          var_f26 = -9500.0f;
        }
        else
          if (func_15047274((u8 *) spB4, 0, temp_f20, temp_s0 + 0x24) != 0)
        {
          var_f26 = *((f32 *) (((u8 *) temp_s0) + 0x24));
        }
        else
        {
          var_f26 = temp_f20;
        }
      }
      else
      {
        var_f26 = -9500.0f;
      }
      do
      {
        var_s1 = (func_150ADA68() < (*((f32 *) (((u8 *) temp_s0) + 0x60)))) ? (1) : (0);
        spA4[0] = 0.0f;
        spA4[1] = 0.0f;
        spA4[2] = 0.0f;
        temp_f20 = func_150ADA68();
        temp_s2 = func_150ADA20();
        temp_s3 = func_150ADA20();
        func_151925AC(spB4, spA4, (*((f32 *) (((u8 *) temp_s0) + 0x48))) + (temp_f20 * (*((f32 *) (((u8 *) temp_s0) + 0x4C)))), (s16) ((*((s16 *) (((u8 *) temp_s0) + 0x50))) + (((u32) temp_s2) % ((u32) ((*((s16 *) (((u8 *) temp_s0) + 0x52))) + 1)))), (*((u8 *) (((u8 *) temp_s0) + 0x54))) + (((u32) temp_s3) % ((u32) ((*((u8 *) (((u8 *) temp_s0) + 0x55))) + 1))), 0xFF, (func_150ADA68() * (*((f32 *) (((u8 *) temp_s0) + 0x5C)))) + (temp_f20 = *((f32 *) (((u8 *) temp_s0) + 0x58))), var_s1, var_f26, temp_s0 + 0x28, (s32) (*((u8 *) (((u8 *) temp_s0) + 0x64))), (s32) (*((u8 *) (((u8 *) arg0) + 0xC))), (s32) (*((u8 *) (((u8 *) arg0) + 1))));
        *((f32 *) (((u8 *) temp_s0) + 0x18)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0x18))) - 1.0f);
      }
      while ((*((f32 *) (((u8 *) temp_s0) + 0x18))) > 1.0f);
      return;
    }
    if ((*((f32 *) (((u8 *) temp_s0) + 0x18))) > 1.0f)
    {
      do
      {
        *((f32 *) (((u8 *) temp_s0) + 0x18)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0x18))) - 1.0f);
      }
      while ((*((f32 *) (((u8 *) temp_s0) + 0x18))) > 1.0f);
    }
  }
}
