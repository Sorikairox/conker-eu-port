s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern s32 D_800A234C;

void func_150FE638(struct127 *arg0, s32 arg1, u8 arg2, s32 arg3)
{
  f32 sp60[2];
  u8 sp5F;
  struct108 *temp_v0_2;
  struct126 *temp_v0;
  u32 new_var;
  if ((arg0->unk1D4 != 0) && ((arg0->unk74 & 0xF) != 0xF))
  {
    sp60[1] = (func_150ADA68() * 1.5f) + 2.0f;
    sp60[0] = (func_150ADA68() * 10.1f) + 2.06f;
    temp_v0 = arg0->unk31C;
    if (((temp_v0 != 0) && (temp_v0->unk197 != 0)) && ((temp_v0_2 = arg0->camera, temp_v0_2 != 0)))
    {
      sp5F = (~(1 << temp_v0_2->unk23D)) & 0xFFFFu;
    }
    else
    {
      sp5F = 0xFF;
    }
    new_var = (u32) func_150ADA20();
    func_151030B8(arg0, D_80088F20, D_800A2340, &D_800A234C, sp60, (new_var % 5U) + 6, (((u32) func_150ADA20()) % 101U) + 0x9B, (func_150ADA68() * 199.0f) + 501.0f, arg1, (s32) sp5F, 0, -1, (s32) arg2, arg3);
  }
}
