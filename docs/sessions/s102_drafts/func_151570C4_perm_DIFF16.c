extern f32 D_800DCE60[3][10][4];
s32 func_15157294(f32 *, u8, f32 (*)[4]);

void func_151570C4(u8 *arg0)
{
  u32 j;
  u32 i;
  f32 (*row)[4];
  Header h;
  Header2 h2;
  *((s16 *) (arg0 + 0x2C)) -= D_800BE9E4;
  if ((*((s16 *) (arg0 + 0x2C))) < 0)
  {
    i = func_150ADA20() % 3U;
    j = func_150ADA20() % 10U;
    row = D_800DCE60[i];
    if (((row[j][0] != 0.0f) && (row[j][1] != 0.0f)) && (row[j][2] != 0.0f))
    {
      func_15157294(row[j], ((0, arg0))[0xC], row);
      h.unk0 = 3;
      h.unk1 = -1;
      h.unk2 = (func_150ADA20() % 11U) + 5;
      h.unk4 = 0;
      row = D_800DCE60[i];
      h2.unk0 = row[j][0];
      h2.unk4 = row[j][1];
      h2.unk8 = row[j][2];
      func_151602C0(&h, &h2, (func_150ADA20() % 156U) + 0x64, 0xFF, 0xFF, 0xFF, 0xFFU, 0U, 0, arg0[0xC], arg0[1]);
    }
    ((s16 *) (arg0 + 0x28))[2] = (func_150ADA20() % ((u32) (((s16 *) (arg0 + 0x28))[1] + 1))) + ((s16 *) (arg0 + 0x28))[0];
  }
}
