void func_1511F30C(u8 *arg0)
{
  f32 temp_f0;
  f32 temp_f12;
  f32 temp_f12_2;
  f32 temp_f12_3;
  float new_var;
  f32 temp_f12_4;
  f32 temp_f2;
  s32 temp_v0;
  if ((*((s32 *) (((u8 *) arg0) + 0x7C))) == 0)
  {
    *((f32 *) (((u8 *) arg0) + 0x84)) = (f32) (*((s16 *) (((u8 *) arg0) + 0x14)));
  }
  new_var = ((f32) D_800BE9E4) * 4.0f;
  temp_v0 = 1 - ((*((u8 *) (((u8 *) arg0) + 0x72))) & 1);
  temp_f0 = (f32) (*((s16 *) (((u8 *) arg0) + 0x14)));
  temp_f2 = new_var;
  if ((*((s32 *) (((u8 *) arg0) + 0x80))) != 0)
  {
    if (temp_v0 & 1)
    {
      temp_f12 = *((f32 *) (((u8 *) arg0) + 0x84));
      *((s16 *) (((u8 *) arg0) + 0x14)) = (s16) ((s32) (temp_f0 + temp_f2));
      if (temp_f12 < ((f32) (*((s16 *) (((u8 *) arg0) + 0x14)))))
      {
        *((s16 *) (((u8 *) arg0) + 0x14)) = (s16) ((s32) temp_f12);
      }
    }
    else
    {
      temp_f12_2 = *((f32 *) (((u8 *) arg0) + 0x84));
      *((s16 *) (((u8 *) arg0) + 0x14)) = (s16) ((s32) (temp_f0 - temp_f2));
      if (((f32) (*((s16 *) (((u8 *) arg0) + 0x14)))) < temp_f12_2)
      {
        *((s16 *) (((u8 *) arg0) + 0x14)) = (s16) ((s32) temp_f12_2);
      }
    }
  }
  else
    if (temp_v0 & 1)
  {
    *((s16 *) (((u8 *) arg0) + 0x14)) = (s16) ((s32) (temp_f0 - temp_f2));
    temp_f12_3 = (*((f32 *) (((u8 *) arg0) + 0x84))) - 350.0f;
    if (((f32) (*((s16 *) (((u8 *) arg0) + 0x14)))) < temp_f12_3)
    {
      *((s16 *) (((u8 *) arg0) + 0x14)) = (s16) ((s32) temp_f12_3);
    }
  }
  else
  {
    temp_f12_4 = (*((f32 *) (((u8 *) arg0) + 0x84))) + 350.0f;
    *((s16 *) (((u8 *) arg0) + 0x14)) = (s16) ((s32) (temp_f0 + temp_f2));
    if (temp_f12_4 < ((f32) (*((s16 *) (((u8 *) arg0) + 0x14)))))
    {
      *((s16 *) (((u8 *) arg0) + 0x14)) = (s16) ((s32) temp_f12_4);
    }
  }
  *((s32 *) (((u8 *) arg0) + 0x7C)) = 1;
}
