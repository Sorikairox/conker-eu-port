typedef struct { s32 w[7]; u8 b1C; u8 pad1D[7]; } Blk7FF0;
typedef struct {
    u8 pad0[0x10];
    u8 u10[0x1C];
    u8 u2C; u8 u2D; u8 u2E; u8 u2F; u8 u30; u8 u31; u8 pad32[2];
    s32 u34;
    u8 u38; u8 pad39[3];
    s32 u3C[4];
    s32 u4C;
    s32 u50;
    f32 u54; f32 u58; f32 u5C;
    Blk7FF0 u60;
    u8 u84[0x10];
    u8 *u94;
    u8 *u98;
    u8 pad9C[4];
    u8 uA0[1];
} Obj7FF0;
s32 func_1515D9F0(s32);
s32 func_1515D9B0(void);
void *func_15147FF0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9, s32 argA)
{
  Obj7FF0 *p;
  s32 i;
  s32 type;
  int new_var;
  new_var = arg1 + (((u8 *) arg0)[0x15] * arg2);
  type = ((*((u16 *) (((u8 *) arg0) + 0xE))) & 0x40) ? (0x4D) : (0x22);
  p = func_15167A68(type, argA, new_var + 0xA0, 1, arg9, 1);
  if (p == 0)
  {
    return 0;
  }
  p->u98 = p->uA0;
  p->u94 = p->uA0;
  p->u94 = p->u94 + arg1;
  memcpy(p->u10, arg0, 0x1C);
  p->u2C = 0;
  p->u2D = 0;
  p->u2E = 0;
  p->u2F = arg3;
  p->u30 = arg4;
  p->u31 = arg5;
  if (((Blk7FF0 *) arg8) != 0)
  {
    p->u60 = *((Blk7FF0 *) arg8);
  }
  else
  {
    p->u60.b1C = 0;
  }
  p->u34 = arg6;
  p->u38 = 0;
  p->u50 = arg7;
  for (i = 0; i < 4; i++)
  {
    p->u3C[i] = 0;
  }

  p->u4C = 0;
  if (arg6 != 0)
  {
    for (i = 0; i <= D_80082FA0; i++)
    {
      p->u3C[i] = func_1515D9F0(arg6);
    }

    p->u4C = func_1515D9B0();
  }
  p->u54 = 0.0f;
  p->u58 = 0.0f;
  p->u5C = 0.0f;
  bzero(p->u84, 0x10);
  return p;
}
