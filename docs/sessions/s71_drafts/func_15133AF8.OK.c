void func_151B9C10(void *);
extern void (*D_80089D98[])(u8 *, u8 *, u8);
void func_15133AF8(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 idx;
  s32 sel = arg2;
  s32 t;
  s32 k; // fakematch: unused local fixes the arg2-copy spill slot
  if ((arg2 == 0x1B) && (*(u16 *)(arg0 + 0x66) == 0x22))
  {
    func_151B9C10(arg0);
  }
  if (sel == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)(arg0 + 0x7C)) { *(s32 *)(arg0 + 0x7C) = *(s32 *)(arg1 + 4); arg0[0x80] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(arg0 + 0x7C)) {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(arg0 + 0x7C) = *(s32 *)arg1; arg0[0x80] = arg1[8]; }
  }
  else if (sel == 0)
  {
    t = *(s32 *)arg1;
    if ((t == *(s32 *)(arg0 + 0x7C)) || (arg0[0x80] == arg1[4])) { *(s32 *)(arg0 + 0x7C) = 0; arg0[0x80] = 0; }
  }
  if (*(s32 *)(arg0 + 0x60) & 0x100) { idx = arg0[0x68]; } else { idx = 0; }
  if (D_80089D98[idx] != NULL) { D_80089D98[idx](arg0, arg1, arg2); }
}
