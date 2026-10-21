typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 x;
    s16 y;
    s16 z;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    s8 pad13;
    s8 unk14;
    u8 unk15;
} SpawnA964;
extern s32 D_8008CE7C;
extern f32 D_800A70A8;
void func_15167AD8(SpawnA964 *, u8, u8);
void func_1516A964(u8 *arg0)
{
  s32 y;
  s32 lim;
  f32 f;
  SpawnA964 s;
  unsigned char v;
  y = *((s32 *) (arg0 + 0x14));
  lim = (*((s16 *) (arg0 + 0x2A))) + (*((s16 *) (arg0 + 0x22)));
  if (y >= lim)
  {
    func_1510F800(0);
    y = (*((s32 *) (arg0 + 0x14)) = func_1510FE58(*((s16 *) (arg0 + 0x20)), *((s16 *) (arg0 + 0x22)), *((s16 *) (arg0 + 0x24)), 0));
  }
  if (y >= lim)
  {
    *((s16 *) (arg0 + 0x38)) = 0;
    if ((lim - y) < 50)
    {
      s.unk0 = D_8008CE7C;
      s.unk4 = 0;
      s.unk6 = 0x100;
      s.x = *((s16 *) (arg0 + 0x20));
      s.y = (*((s32 *) (arg0 + 0x14))) + 10;
      s.z = *((s16 *) (arg0 + 0x24));
      v = arg0[0x3B];
      s.unk12 = 0;
      s.unk14 = 3;
      y = ((v << 12) / 5100) + 0xCC;
      s.unkE = (s.unk10 = y);
      s.unk15 = v;
      func_15167AD8(&s, arg0[0xC], arg0[1]);
    }
  }
  else
  {
    f = D_800A70A8;
    *((s16 *) (arg0 + 0x26)) = (*((s16 *) (arg0 + 0x26))) * f;
    *((s16 *) (arg0 + 0x28)) = (*((s16 *) (arg0 + 0x28))) * f;
  }
}
