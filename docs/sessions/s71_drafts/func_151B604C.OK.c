void func_151B604C(u8 *arg0, u8 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x28;
  if (arg2 == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)(v + 0x580)) { *(s32 *)(v + 0x580) = *(s32 *)(arg1 + 4); v[0x584] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x580)) { *(s32 *)(v + 0x580) = *(s32 *)arg1; v[0x584] = arg1[8]; }
    if (*(s32 *)arg1 == *(s32 *)(v + 0x588)) { *(s32 *)(v + 0x588) = *(s32 *)(arg1 + 4); v[0x58C] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x588)) {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(v + 0x588) = *(s32 *)arg1; v[0x58C] = arg1[8]; }
  }
  else if (arg2 == 0)
  {
    s32 k = *(s32 *)arg1;
    if ((k == *(s32 *)(v + 0x580)) || (k == *(s32 *)(v + 0x588)) || (v[0x584] == arg1[4]) || (v[0x58C] == arg1[4])) { func_1516972C((struct102 *)arg0); }
  }
}
