void func_15168B44(u8 *arg0)
{
  int new_var;
  s32 w = *((s32 *) (arg0 + 0x14));
  s32 lo = ((((((((((((w & (0xFFFF ^ 0)) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu;
  if (lo != 0)
  {
    *((volatile s32 *) (arg0 + 0x14)) = w & 0xFFFF0000;
    *((s16 *) (arg0 + 0x38)) = 0x1E;
    lo = w;
    new_var = (lo & 0xFFFF0000) | ((lo - 1) & 0xFFFF);
    *((s32 *) (arg0 + 0x14)) = new_var;
    return;
  }
  if (((lo >> (((((((16 & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF)) & 0xFFFF) < arg0[0x3F])
  {
    arg0[0x3F] -= (lo >> 16) & 0xFFFF;
    *((s16 *) (arg0 + 0x38)) = 0x1E & 0xFFFFu;
    return;
  }
  {
    s32 t;
    *((s16 *) (arg0 + 0x38)) = 0;
  }
}
