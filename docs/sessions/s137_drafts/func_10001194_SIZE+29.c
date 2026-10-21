extern u8 D_427B0[];
extern u8 D_19EDE8[];
extern u8 D_151FA920[];
extern u8 D_80033690[];
extern u8 D_80032E90[];
extern u8 D_80043ED0[];
extern OSViMode D_8002AF20;
extern OSMesgQueue D_8003B578;
extern OSMesg D_8003BC10;
extern s32 D_80082EB0;
extern s32 D_80035858;
extern s32 *D_8003585C;
void func_10003570(s32);
void func_10003BD0(void);
void func_1000738C(void);
void func_10005BE0(void);
void func_15007830(void);
void func_10006530(void *, s32 *, u32);
void *allocate_memory(s32, s32, s32, s32);

void func_10001194(s32 arg0)
{
  u32 count;
  void *src;
  void *buf;
  u32 size;
  s32 offset;
  s32 phi_s0;
  u32 i;
  if (D_8000030C != 0)
  {
    osCreateMesgQueue(&D_8003B578, &D_8003BC10, 8);
    func_10003570(0xFE);
    osViSetMode(&D_8002AF20);
    osViBlack(1);
    osViSetEvent(&D_8003B578, NULL, 1);
  }
  func_10005218();
  if (D_8000030C == 0)
  {
    phi_s0 = 0x80400000 - (u32) D_80043ED0;
    bzero(D_80043ED0, phi_s0);
  }
  else
  {
    bzero(&D_800EA140, 0x80400000 - (u32) &D_800EA140);
    phi_s0 = 0x80400000 - (u32) D_80043ED0;
  }
  osInvalICache(D_80043ED0, phi_s0);
  osInvalDCache(D_80043ED0, phi_s0);
  func_10003920();
  func_10003930();
  func_10003BD0();
  func_1000738C();
  D_8002AAE8[0] = func_10003C6C(0x1ECC0, 0xFF, 3, 1, 0);
  D_8002AAE8[1] = func_10003C6C(0x1ECC0, 0xFF, 3, 1, 0);
  if (D_8000030C == 0)
  {
    osCreateMesgQueue(&D_8003B578, &D_8003BC10, 8);
    func_10003570(0xFE);
    osViSetMode(&D_8002AF20);
    osViBlack(1);
    osViSetEvent(&D_8003B578, NULL, 1);
  }
  offset = (s32) D_427B0;
  func_10004514(offset, &D_80082EB0, 0x10, 1);
  src = (void *) (D_80082EB0 + offset);
  size = (s32) D_19EDE8 - (s32) src;
  buf = allocate_memory(size, 1, 2, 0);
  func_10004514((s32) src, buf, size, 1);
  func_10006530(buf, &D_80082EB0, D_8003809C);
  func_10004074(buf);
  count = (((u32) (D_151FA920 - (u8 *) func_15000000) + 0xFFF) >> 12) + 1;
  D_80035858 = (s32) (D_80033690 + 0xF) & ~0xF;
  D_8003585C = (s32 *) ((s32) (D_80032E90 + 0xF) & ~0xF);
  func_10004514(offset + 4, D_8003585C, ((((count + 1) * 4) + 0xF) | 0xF) ^ 0xF, 1);
  for (i = 0; i < count; i++)
  {
    D_8003585C[i] = (D_8003585C[i] ^ 0x8039CCCA) + offset;
  }
  D_8003BE74 = 0;
  func_10005B04(0xEB);
  func_10001420();
  func_10005BE0();
  func_15007830();
}
