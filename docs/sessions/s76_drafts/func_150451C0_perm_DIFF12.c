// PERMUTER CHANGED DECL: s32func_150451C0(f32*,f32,Unk45674*) (base: s32func_150451C0(f32*arg0,f32arg1,Unk45674*arg2))
extern s32 D_800DC26C;
s32 func_150A3F50(s32, s32);
s32 func_150451C0(f32 *arg0, f32 arg1, Unk45674 *arg2)
{
  Unk45674 *out;
  s32 best;
  s32 n;
  int new_var;
  s32 i;
  f32 d;
  s32 j;
  s32 *q;
  s32 off;
  if (arg1 < arg0[0, 1])
  {
    arg2->unk1C &= ~2;
    return 0;
  }
  arg2->unk0 = D_800990F8;
  best = -1;
  func_1510F800(0);
  n = func_150A3F50((s32) arg0[0], (s32) arg0[2]);
  for (i = 0; i < n; i++)
  {
    d = D_800D3720[i].unk0 * 0.00390625f;
    if ((arg0[1] <= d) && (d < arg2->unk0))
    {
      best = i;
      arg2->unk0 = d;
    }
  }

  if (best != (-1))
  {
    q = D_800D3720[best].unk4;
    out = arg2;
    off = D_800D3720[best].unk8;
    for (j = 0; j < 3; j++)
    {
      s16 *p;
      p = (s16 *) (q[j] + (off * 0x10));
      out->unk4[j][0] = p[0];
      out->unk4[j][1] = p[1];
      out->unk4[j][2] = p[2];
    }

    new_var = (((s32) D_800D3720[best].unk4) - D_800DC26C) / 12;
    out->unk18 = ((s32 *) D_800DBE5C)[new_var];
    out->unk1C |= 5;
    out->unk1D = 1;
    out->unk20 = 0;
    if (out->unk0 <= arg1)
    {
      arg2->unk1C |= 2;
      return 1;
    }
    return 0;
  }
  arg2->unk1C &= ~2;
  return 0;
}
