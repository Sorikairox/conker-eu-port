s32 func_15145128(f32 *, f32 *, s32, s32);
f32 func_15143E64(f32 *);

s32 func_15082020(f32 *arg0, f32 *arg1, struct127 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6)
{
  f32 pos[3];
  f32 a[3];
  f32 b[3];
  f32 c[3];
  f32 dc;
  f32 e0;
  f32 d[3];
  pos[0] = arg2->x_position;
  pos[1] = arg2->y_position + arg2->unkD6;
  pos[2] = arg2->z_position;
  dc = arg2->unkDC;
  lbl:
  e0 = arg2->unkE0;

  a[0] = arg0[0];
  a[1] = arg0[1] * dc;
  a[2] = arg0[2];
  b[0] = arg1[0];
  b[1] = arg1[1] * dc;
  b[2] = arg1[2];
  if (func_15145128(b, b, 0, 0) == 0)
  {
    return 0;
  }
  c[0] = pos[0];
  c[1] = pos[1] * dc;
  c[2] = pos[2];
  if (func_151452C4((struct17 *) a, (struct17 *) b, (struct17 *) c, arg2->unkD2, (s32) arg3, (s32) arg4, arg5, arg6) == 0)
  {
    return 0;
  }
  arg3[1] *= e0;
  arg4[1] *= e0;
  if (((!d) && (!d)) && (!d))
  {
  }
  d[0] = arg3[0] - arg0[0];
  d[1] = arg3[1] - arg0[1];
  d[2] = arg3[2] - arg0[2];
  *arg5 = func_15143E64(d);
  d[0] = arg4[0] - arg0[0];
  d[1] = arg4[1] - arg0[1];
  d[2] = arg4[2] - arg0[2];
  *arg6 = func_15143E64(d);
  return 1;
}
