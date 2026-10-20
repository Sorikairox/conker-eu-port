void func_1000FD38(void *, u8 *, s32);
void func_15104FF8(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *p = arg0 + 0x28;
  u8 *o;
  if (arg2 == 0x38)
  {
    o = *(u8 **)p; if (o[0x14] == 1) { *(s16 *)(p + 8) = 0xFA; func_1000FD38(func_1000EF40, o, 0); func_1000FA64(0x236, (*(s16 **)p)[0], (*(s16 **)p)[1], (*(s16 **)p)[2], 0x4000, 0x5DC, 0x3E8, (s32)func_1000EF40, *(u8 **)p, 0, 8, 0); }
  }
}
