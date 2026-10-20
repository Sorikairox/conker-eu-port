typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} Sd8a8;
s32 func_15134DAC(Sd8a8 *, s32, ...);
void func_151BD8A8(u8 *arg0, s32 arg1, s32 arg2)
{
  Sd8a8 s;
  s16 zp; // fakematch: unused pad, puts z at sp+0x20
  s16 z;
  s32 v;
  if (arg0 != 0)
  {
    s.u0 = arg0[0x3B];
    s.u4 = arg0;
    s.u8_ = 1;
    s.u24 = 0;
    s.u26 = 0x32;
    s.u28 = 0x64;
    s.u2A = 0x12C;
    s.uC = 31.0f;
    s.u2E = 4;
    s.u2F = 4;
    s.u30 = 3;
    s.u38 = 5;
    s.u39 = -1;
    z = 0;
    s.u10 = -34.0f;
    s.u14 = -117.0f;
    s.u18 = 35.0f;
    s.u1C = -24.0f;
    s.u20 = -182.0f;
    s.u34 = 0.30061f;
    v = func_15134DAC(&s, 2);
    if (v != 0)
    {
      memcpy((void *) (v + 0x80), &z, 2);
    }
    s.uC = -s.uC;
    s.u18 = -s.u18;
    v = func_15134DAC(&s, 2);
    if (v != 0)
    {
      memcpy((void *) (v + 0x80), &z, 2);
    }
  }
}
