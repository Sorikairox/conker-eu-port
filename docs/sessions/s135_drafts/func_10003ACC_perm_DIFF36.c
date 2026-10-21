// PERMUTER CHANGED DECL: voidfunc_10003ACC(s32arg0,s32arg1,s32arg2) (base: voidfunc_10003ACC(s32r,s32g,s32b))
void func_10003ACC(s32 r, s32 g, s32 b)
{
  u16 *fb2;
  s32 i;
  s32 n;
  u16 *fb;
  unsigned int new_var2;
  s32 new_var;
  fb = (u16 *) D_8002AAE8[0];
  new_var = (s32) ((D_800BE620 * D_800BE624) * 2);
  i = 0;
  n = new_var >> 1;
  new_var2 = 2;
  if (fb != 0)
  {
    while (i < n)
    {
      *(fb++) = ((((r << 8) & 0xf800) | ((g << 3) & 0x7c0)) | ((b >> new_var2) & 0x3e)) | (1 & 0x1);
      i++;
    }

    fb2 = (u16 *) D_8002AAE8[1];
    for (i = 0; i < n; i++)
    {
      fb2[i] = ((((r << 8) & 0xf800) | ((g << 3) & 0x7c0)) | ((b >> new_var2) & 0x3e)) | (1 & 0x1);
    }

  }
}
