extern void (*D_8008B6F8[])(u8 *, u8 *, u8);
void func_15161F4C(u8 *arg0, u8 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x18;
  if (arg2 == 0)
  {
    s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
    if ((*(s32 *)v == *(s32 *)arg1) || (v[4] == arg1[4])) { func_1516972C((struct102 *)arg0); }
  }
  else if (arg2 == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)v) { *(s32 *)v = *(s32 *)(arg1 + 4); v[4] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)v) { *(s32 *)v = *(s32 *)arg1; v[4] = arg1[8]; }
  }
  if (D_8008B6F8[arg0[0x1D]] != NULL) { D_8008B6F8[arg0[0x1D]](arg0, arg1, arg2); }
}
