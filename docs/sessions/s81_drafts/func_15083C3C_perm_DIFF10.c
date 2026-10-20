s32 func_15085170(struct127 *);
u8 *func_1502B020(s32 *arg0, s32 arg1, ...);

void func_15083C3C(s32 arg0, s32 arg1, s32 arg2)
{
  struct127 *s = &D_800CC2D0[arg0];
  s32 v;
  u8 *p;
  int new_var;
  *(((u8 *) s) + 4) = arg1;
  if (arg1 == 0xFF)
  {
    *((f32 *) (((u8 *) s) + 0xC8)) = 0.0f;
    *((s16 *) (((u8 *) s) + 0xE4)) = 0;
    *((s16 *) (((u8 *) s) + 0xE6)) = 0;
    *((s16 *) (((u8 *) s) + 0xE8)) = 0;
    *((s16 *) (((u8 *) s) + 0xD2)) = 70;
    new_var = 0xD6;
    *((s16 *) (((u8 *) s) + 0xD4)) = 70;
    *((s16 *) (((u8 *) s) + new_var)) = 0;
    *((s16 *) (((u8 *) s) + 0x160)) = 0;
  }
  else
  {
    *((f32 *) (((u8 *) s) + 0xC8)) = *((s16 *) (((u8 *) D_800D1C90[arg1]) + 6));
    func_15062BDC(s, *((f32 *) (((u8 *) s) + 0x14C)), *((f32 *) (((u8 *) s) + 0x150)));
    p = (u8 *) D_800D1C90[arg1];
    *(((u8 *) s) + 5) = p[0x12];
  }
  v = func_15085170(s);
  new_var = (u8) v;
  if (1)
  {
    *(((u8 *) s) + 6) = v;
  }
  if (((u16 *) D_800C5A90)[new_var] != 0)
  {
    new_var = 0;
    *((s32 *) (((u8 *) s) + 0x58)) = (s32) func_1502B020(new_var, 2, 2, new_var);
  }
}
