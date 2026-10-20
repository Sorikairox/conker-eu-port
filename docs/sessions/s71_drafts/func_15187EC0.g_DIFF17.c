s32 func_15187EC0(s32 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7)
{
  s32 *q = &arg0; // fakematch: shape C home reload
  u8 *e;
  if (D_800DFBE4 < 5)
  {
    e = (u8 *)&D_800DFB30[D_800DFBE4];
    *(f32 *)(e + 0x14) = arg1; e[6] = e[0] = arg2; e[7] = e[1] = arg3; e[8] = e[2] = arg4; *(s32 *)(e + 0x10) = *q; e[3] = arg5; e[4] = arg6; e[5] = arg7;
    bzero(e + 0x18, 0xC);
    D_800DFBE4++; return D_800DFBE4 - 1;
  }
  return -1;
}
