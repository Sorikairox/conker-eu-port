s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_15143E94(s32, s32);
s32 func_1514CBE8(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
void func_151664F0(s32, s32, s32, s32, s32, s32, s32, u8, s32);
extern f32 D_800A0234;
void func_150BAEF4(u8 *volatile arg0, u8 arg1, s32 arg2)
{
  f32 pos[3];
  s32 sp48[9];
  s32 a;
  u8 ok;
  if (*(s32 *)(arg0 + 0x1D4) != 0)
  {
    ok = func_150BAE10(pos, arg0, (s32) sp48, arg1);
    func_151D5404((struct17 *) pos, 1307.0f, 2000.0f, 0.0005f, 0xC, 0xF, 0xFF, 0);
    func_15143E94(5, 0x4022);
    if (ok != 0)
    {
      a = (s32) (D_800DBFF0[D_80082FA4].unk380 * D_800A0234);
      func_151664F0(-1, (s32) pos[0], (s32) (pos[1] + 6.0f), (s32) pos[2], 0x19, 0x12, 0, 0xFF, 1);
      func_1514CBE8(pos[0], pos[1], *(s32 *)&pos[2], (func_150ADA68() * 50.0f) + 40.0f, a + 0x3C, a - 0x3C, (func_150ADA20() % 11U) + 0x1E, 5, 0, 0.0f, 0, 0xFF);
    }
  }
}
