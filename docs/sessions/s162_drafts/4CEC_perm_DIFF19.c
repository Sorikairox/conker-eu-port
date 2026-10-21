typedef struct {
    u8 pad0[0xC];
    f32 uC;
    f32 u10;
    u8 pad14[0x20];
    f32 u34;
    f32 u38;
    u8 pad3C[0x144];
} struct_eu_15144CEC;
extern f32 D_800DA130[][4][4];
extern f32 D_800D9F40;
void func_150A7EE0(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
s32 func_15144CEC(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, u8 arg5)
{
  f32 sp44;
  f32 sp40;
  f32 sp3C;
  f32 d;
  f32 x;
  f32 y;
  if (arg2 == 0)
  {
    arg2 = &sp44;
  }
  if (arg3 == 0)
  {
    arg3 = &sp40;
  }
  if (arg4 == 0)
  {
    arg4 = &sp3C;
  }
  func_150A7EE0(D_800DA130[arg5], arg0[0], arg0[1], arg0[2], &arg1[0], &arg1[1], arg2, arg3);
  d = *arg3;
  if ((d >= 6000.0f) || (d <= D_800D9F40))
  {
    return 0;
  }
  if (d != 0.0f)
  {
    *arg4 = 1.0f / d;
  }
  else
  {
    return 0;
  }
  x = (((struct_eu_15144CEC *) D_800BE628)[arg5].uC + 5.0f) * arg1[0];
  d = ((*arg4) * x) + ((struct_eu_15144CEC *) D_800BE628)[arg5].u34;
  y = (((struct_eu_15144CEC *) D_800BE628)[arg5].u10 + 5.0f) * arg1[1];
  arg1[0] = d;
  arg1[1] = ((struct_eu_15144CEC *) D_800BE628)[arg5].u38 - ((*arg4) * y);
  return 1;
}
