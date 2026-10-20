extern u32 D_80043ED0[];
void func_10001420(void)
{
  u32 *p;
  int new_var;
  new_var = 0x3F8;
  for (p = D_80043ED0; p < (D_80043ED0 + new_var); p++)
  {
    *p = 0;
  }

}
