typedef struct Node8D80 { u8 u0; u8 u1; u8 u2; u8 u3; u8 u4; s16 u6; void *u8_; struct Node8D80 *uC; u8 *u10; s32 u14; } Node8D80;
void *allocate_memory(s32, s32, s32, s32);
s32 func_10004074(u8 *);
void func_15188FC8();
s32 func_1502DE10(u8);
void func_15188D80(u8 *arg0, s32 arg1, s32 arg2)
{
  Node8D80 *n;
  void *buf;
  s32 cnt;
  u32 size;
  s32 pad;
  for (n = *((Node8D80 **) D_800DF7C8); n != 0; n = n->uC)
  {
    if (arg0 == n->u10)
    {
      if (n->u6 < arg1)
      {
        n->u6 = arg1;
      }
      n->u4 = arg2;
      return;
    }
  }

  n = allocate_memory(0x18, 1, 0, 0);
  if (n == 0)
  {
    return;
  }
  cnt = func_1502DE10(arg0[4] ^ 0);
  if (cnt == 0)
  {
    func_10004074((u8 *) n);
    return;
  }
  size = cnt * 0x180;
  buf = allocate_memory(size, 1, 1, 1);
  if (buf == 0)
  {
    func_10004074((u8 *) n);
    return;
  }
  n->u0 = 0;
  n->u1 = 3;
  n->u2 = 0;
  n->u3 = 0x14;
  n->u4 = arg2;
  n->u6 = arg1;
  n->u8_ = buf;
  n->u10 = arg0;
  n->u14 = 0;
  bzero(buf, size);
  func_15188FC8(n, D_800DF7C8);
}
