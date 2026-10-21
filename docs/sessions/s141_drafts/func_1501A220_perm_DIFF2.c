s32 allocate_memory(s32, s32, s32, s32);
s32 func_150006E0(s32);
s32 func_1501A8C0(s32, s32, s32, s32);
s32 func_1510B5F0(s32);
extern s8 D_800BEA34;
extern s8 D_800BEA37;
extern s32 D_800BEA4C;
extern s8 D_800BEA55;
extern s32 D_800BEA5C;
extern f32 D_800BEAD8;

void func_1501A220(s32 arg0, s32 arg1)
{
  f32 temp_f0;
  s32 temp_f16;
  s32 temp_s1;
  s32 var_s0;
  s32 var_s0_2;
  temp_s1 = (D_80082FA0 = arg0);
  if (temp_s1 == 0)
  {
    var_s0 = 1;
  }
  else
  {
    var_s0 = temp_s1 + 2;
  }
  D_800BE628 = allocate_memory(var_s0 * 0x180, 1, 1, 0);
  D_800BEA4C = allocate_memory(var_s0 * 0x10, 1, 1, 0);
  if (D_80082FA0 == 1)
  {
    temp_f0 = ((f32) D_800BEA5C) - 2.0f;
    temp_f0 = temp_f0 * 0.8f;
    temp_f16 = (s32) temp_f0;
    D_800BEAD8 = ((f32) (temp_f16 - (temp_f16 % 4))) / temp_f0;
  }
  func_150006E0(D_800BE9F0);
  temp_s1 = D_80082FA0;
  var_s0_2 = 0;
  if (temp_s1 >= 0)
  {
    do
    {
      func_1501A8C0(var_s0_2, temp_s1, (double) 0x3FF, 0);
      temp_s1 = D_80082FA0;
      var_s0_2 += 1;
    }
    while (D_80082FA0 >= var_s0_2);
  }
  if (temp_s1 != 0)
  {
    func_1501A8C0(var_s0_2, 0, 0x3FF, 0);
  }
  D_800BEA37 = 1;
  D_800BEA34 = 1;
  D_800BEA55 = 0;
  func_1510B5F0(arg1);
}
