typedef struct {
    s32 u18;
    s32 u1C;
    u8 u20;
    u8 pad21[3];
    u8 *u24;
    s8 u28;
    u8 pad29[3];
    f32 u2C;
    f32 u30;
    f32 u34;
    f32 u38;
    f32 u3C;
    s16 u40;
    s8 u42;
    s8 u43;
    s8 u44;
    s8 u45;
} SpawnB874;
typedef struct {
    s32 u0;
    s8 u4;
    u8 pad5;
    s16 u6;
    f32 u8;
} ExtraB874;
u8 *func_1513418C(void *, s32, u8, s32);

u8 *func_151AB874(u8 *arg0, s32 arg1)
{
  SpawnB874 sp;
  ExtraB874 ex;
  u8 *ret;
  ex.u0 = arg1;
  ex.u6 = 0;
  ex.u4 = 1;
  sp.u20 = arg0[0x3B];
  sp.u18 = 0;
  sp.u1C = 0;
  ex.u8 = *((f32 *) (arg0 + 0x118));
  sp.u28 = 1;
  sp.u2C = 0.0f;
  sp.u30 = 0.0f;
  sp.u34 = 0.0f;
  sp.u40 = 0x12C;
  sp.u42 = 0xA;
  (&sp)->u43 = 3;
  sp.u44 = 0;
  sp.u45 = 1;
  sp.u24 = arg0;
  sp.u38 = 25.0f;
  sp.u3C = 0.26497f;
  ret = func_1513418C(&sp, 0xC, 0xFF, 0);
  if (ret != 0)
  {
    memcpy(ret + 0x58, &ex, 0xC);
  }
  return ret;
}
