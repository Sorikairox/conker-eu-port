void func_15168B44(u8 *arg0)
{
  s32 w = *(s32 *)(arg0 + 0x14);
  s32 lo = w & 0xFFFF;
  if (lo != 0) {
    *(volatile s32 *)(arg0 + 0x14) = w & 0xFFFF0000;
    *(s16 *)(arg0 + 0x38) = 0x1E;
    *(s32 *)(arg0 + 0x14) = (w & 0xFFFF0000) | ((lo - 1) & 0xFFFF);
    return;
  }
  if (((w >> 16) & 0xFFFF) < arg0[0x3F]) {
    arg0[0x3F] -= (w >> 16) & 0xFFFF;
    *(s16 *)(arg0 + 0x38) = 0x1E;
    return;
  }
  {
    s32 t;
    *(s16 *)(arg0 + 0x38) = 0;
  }
}
