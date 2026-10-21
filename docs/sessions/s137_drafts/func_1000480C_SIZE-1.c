extern OSThread D_80035C70;
extern u8 D_8003A8D2;
extern volatile u8 D_8003A8D3;
extern u8 D_8003A8D5;

void func_1000480C(s32 devAddr, void *dramAddr, u32 size)
{
  s32 w;
  u32 i;
  u32 n;
  D_8003A8D2 = 1;
  size = (size + 1) & ~1;
  while (D_8003A8D3 != 0)
  {
  }
  n = size - 2;
  while ((*(vu32 *) 0xA4600010) & 3)
  {
  }
  devAddr |= D_80000308;
  if (devAddr & 2)
  {
    size -= 2;
    w = *(s32 *) ((devAddr - 2) | 0xA0000000);
    *(u16 *) dramAddr = ((u16 *) &w)[1];
    n = size - 2;
    for (i = 0; i < n; i += 4)
    {
      w = *(s32 *) ((devAddr + 2 + i) | 0xA0000000);
      *(u16 *) ((u8 *) dramAddr + i + 2) = w >> 16;
      *(u16 *) ((u8 *) dramAddr + i + 4) = w;
    }
    if (size & 2)
    {
      w = *(s32 *) ((devAddr + i + 2) | 0xA0000000);
      *(u16 *) ((u8 *) dramAddr + i + 2) = ((u16 *) &w)[0];
    }
  }
  else
  {
    for (i = 0; i < n; i += 4)
    {
      *(s32 *) ((u8 *) dramAddr + i) = *(s32 *) ((devAddr + i) | 0xA0000000);
    }
    if (size & 2)
    {
      w = *(s32 *) ((i + devAddr) | 0xA0000000);
      *(u16 *) ((u8 *) dramAddr + i) = ((u16 *) &w)[0];
    }
  }
  D_8003A8D2 = 0;
  if (D_8003A8D5 != 0)
  {
    osStartThread(&D_80035C70);
  }
}
