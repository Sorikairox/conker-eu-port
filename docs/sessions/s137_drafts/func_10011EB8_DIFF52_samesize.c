s32 func_1510FE4C(s32);
u16 func_1000F568(u16, u16, s32, s32);
typedef struct { u16 a; u16 b; } SndPair;
extern SndPair D_8002C5A0[][5];

u16 func_10011EB8(s32 arg0, s16 *arg1, s32 arg2)
{
  u16 v;
  s32 idx;
  s32 t;
  t = arg0;
  idx = func_1510FE4C(t);
  t = idx;
  if (arg1 != 0)
  {
    if (D_80082FA0 != 0)
    {
      *arg1 = 0x7FFF / (D_80082FA0 + 1);
    }
    else
    {
      *arg1 = 0x7FFF;
    }
  }
  v = D_8002C5A0[idx][arg2].a;
  if (D_8002C5A0[idx][arg2].b >= 2)
  {
    v = func_1000F568(v, D_8002C5A0[idx][arg2].b, arg2, t);
  }
  return v;
}
