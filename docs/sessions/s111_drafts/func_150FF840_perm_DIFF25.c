s32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151D56F8(u8 *);
void func_151D44C4(f32 *, u8, s32);
s32 func_15100304(f32 *, f32 *, u8, s32);
s32 func_151030B8(u8 *, u8, u8 *, u8 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
s32 func_15081A90(u8 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
s32 func_15082278(u8 *, u8 *, s32);
void func_151000EC();
void func_151001BC(u8 *);
void func_15100248();
extern s32 D_800A2500;
extern s32 D_800A250C;
extern f32 D_800A2540;
extern f32 D_800A2544;
extern f32 D_800A2548;
extern f32 D_800A254C;
extern f32 D_800A2550;
extern f32 D_800A2554;
extern f32 D_800A2558;
void func_150FF840(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4)
{
  f32 pos[3];
  f32 dir[3];
  s32 a[3];
  s32 b[3];
  f32 v[2];
  f32 p2[3];
  f32 p1[3];
  f32 p0[3];
  u8 buf[0x64];
  u8 *ptr;
  u8 *t;
  s32 r[2];
  func_15100248(arg0, pos, dir, a, b);
  func_151D56F8(arg0);
  if (((*((s32 *) (arg0 + 0x1D4))) != 0) && ((arg0[0x74] & 0xF) != 0xF))
  {
    func_151D44C4(pos, arg3, arg4);
    v[1] = ((func_150ADA68() * D_800A2540) + 4800.0f) * D_800A2544;
    v[0] = ((func_150ADA68() * 220.0f) + 320.0f) * D_800A2548;
    r[0] = func_150ADA20();
    r[1] = func_150ADA20();
    func_151030B8(arg0, D_80088BB0, (u8 *) (&D_800A2500), (u8 *) (&D_800A250C), v, (((u32) r[0]) % 3) + 4, (r[1] & 0x7F) + 0x80, (func_150ADA68() * 450.0f) + 780.0f, pos, 0xFF, 0, -1, arg3, arg4);
    func_15100304(pos, dir, arg3, arg4);
  }
  if (arg1 != 0)
  {
 dummy_label_712961: ;
    p0[0] = pos[0] + (dir[0] * D_800A254C);
    p0[1] = pos[1] + (dir[1] * D_800A254C);
    p0[2] = pos[2] + (dir[2] * D_800A254C);
    p1[0] = pos[0] + (dir[0] * D_800A2550);
    p1[1] = pos[1] + (dir[1] * D_800A2550);
    p1[2] = pos[2] + (dir[2] * D_800A2550);
    p2[0] = pos[0] + (dir[0] * D_800A2554);
    p2[1] = pos[1] + (dir[1] * D_800A2554);
    p2[2] = pos[2] + (dir[2] * D_800A2554);
    func_151000EC(p0, pos, arg0, 0x32);
    func_151000EC(p1, pos, arg0, 0x30);
    func_151000EC(p2, pos, arg0, 0x31);
  }
  if (arg2 != 0)
  {
    t = *((u8 **) (arg0 + 0x31C));
    if (t != 0)
    {
      ptr = t + 0xB0;
    }
    else
    {
      ptr = buf;
    }
    func_15081A90(arg0, pos[0], pos[1], pos[2], dir[0] * D_800A2558, dir[1] * D_800A2558, dir[2] * D_800A2558, ptr, 2000.0f, 0, 0, 0, -1, 0, 0);
    func_15082278(arg0, ptr, 0x10);
  }
  func_151001BC(arg0);
}
