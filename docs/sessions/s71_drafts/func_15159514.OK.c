void func_15159514(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 t;
  s32 *key = (s32 *)(arg0 + 0x18);
  if (arg2 == 0)
  {
    if ((*key == *(s32 *)arg1) || (arg0[0x1C] == arg1[4]))
    {
      func_1516972C((struct102 *)arg0);
    }
  }
  else if (arg2 == 0x2D)
  {
    t = *(s32 *)arg1;
    if (t == *key)
    {
      *(s32 *)(arg0 + 0x18) = *(s32 *)(arg1 + 4);
      arg0[0x1C] = arg1[9];
    }
    else if (*(s32 *)(arg1 + 4) == *key)
    {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(arg0 + 0x18) = t;
      arg0[0x1C] = arg1[8];
    }
  }
  else if (arg2 == 4)
  {
    if ((*key == *(s32 *)arg1) || (arg0[0x1C] == arg1[4]))
    {
      func_1519F970(arg0);
    }
  }
}
