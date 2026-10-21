void func_151A7E2C(u8 *arg0)
{
  s16 new_var;
  s16 temp_v1;
  s32 temp_lo;
  unsigned char temp_lo_2;
  u8 *temp_v0;
  temp_v0 = arg0 + 0x50;
  temp_v1 = *((s16 *) (((u8 *) arg0) + 0x38));
  if (temp_v1 < (*((s16 *) (((u8 *) arg0) + 0x54))))
  {
    *((s8 *) (((u8 *) arg0) + 0x3F)) = (s8) ((*((s16 *) (((u8 *) arg0) + 0x56))) * (0, temp_v1));
  }
  if (temp_v1 < (*((s16 *) (((u8 *) temp_v0) + 8))))
  {
    temp_v1 = (*((s16 *) (((u8 *) temp_v0) + 0xA))) * D_800BE9E4;
    temp_lo = temp_v1;
    *((s16 *) (((u8 *) arg0) + 0x34)) = (s16) ((*((s16 *) (((u8 *) arg0) + 0x34))) + temp_lo);
    *((s16 *) (((u8 *) arg0) + 0x36)) = (s16) ((*((s16 *) (((u8 *) arg0) + 0x36))) + temp_lo);
  }
  temp_lo_2 = (*((s16 *) (((u8 *) temp_v0) + 2))) * (0, new_var = *((s16 *) (((u8 *) arg0) + 0x38)));
  *((s8 *) (((u8 *) arg0) + 0x42)) = temp_lo_2;
  *((s8 *) (((u8 *) arg0) + 0x41)) = temp_lo_2;
  *((s8 *) (((u8 *) arg0) + 0x40)) = temp_lo_2;
}
