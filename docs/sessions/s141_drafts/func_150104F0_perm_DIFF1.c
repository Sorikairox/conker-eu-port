u8 *func_151149AC(s32);
extern s32 D_800D9D70;
void func_150104F0(void)
{
  unsigned char new_var;
  s8 *p = (s8 *) (&D_800D9D70);
  new_var = (new_var = (p[1] = 0));
  p[2] = 0;
  *p = new_var;
  p[2] = 0;
  p++;
  p--;
  *((f32 *) (func_151149AC(0xF6) + 0x7C)) = 2.0f;
  if (p)
  {
  }
  D_80088D20 = 0;
}
