s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);
extern f32 D_800A03D0;
extern f32 D_800A03D4;
void func_150BE40C(u8 *arg0)
{
  struct { u8 *p; s16 t; } *q;
  struct
  {
    f32 u0;
    f32 u4;
    f32 u8;
    f32 uC;
    u8 u10;
    s16 u12;
    s16 u14;
    s16 u16;
    s16 u18;
    u8 u1A;
    u8 u1B;
    u8 u1C;
    u8 u1D;
    u8 u1E;
    u8 u1F;
    u8 u20;
    u8 u21;
    u8 u22;
    u8 u23;
    s32 u24;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s32 u38;
    s32 u3C;
    u8 u40;
    u8 u41;
    u8 pad42[2];
    u8 u44;
    f32 u48;
    f32 u4C;
    f32 u50;
    f32 u54;
  } a;
  struct
  {
    struct { u8 *p; s16 t; } *q;
    u8 *p;
    s32 u4;
    s32 u8;
    s8 uC;
    s8 uD;
    f32 u10;
    u8 pad[0x48];
  } b;
  s32 r;
  *(s16 *)(arg0 + 0x2C) -= D_800BE9E4;
  if (*(s16 *)(arg0 + 0x2C) < 0)
  {
    a.u0 = (func_150ADA68() * 270.0f) + -135.0f;
    a.u4 = -120.0f;
    a.u8 = (func_150ADA68() * 10.0f) + 3.0f;
    a.uC = (func_150ADA68() * 17.0f) + 9.0f;
    a.u10 = 0xAB;
    a.u12 = 0x3E8;
    a.u14 = 0x31;
    a.u16 = 1;
    a.u18 = 0xFF;
    a.u1A = 7;
    a.u1B = 0xFF;
    a.u1C = 0xFF;
    a.u1D = 0xFF;
    a.u1E = (func_150ADA20() % 156U) + 0x64;
    a.u1F = 0xFF;
    a.u20 = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u30 = 3;
    a.u34 = 0x22;
    a.u38 = 0x80;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 7;
    q = (void *)(arg0 + 0x28);
    a.u48 = 1.0f;
    a.u4C = 1.0f;
    a.u44 = q->p[0x23D];
    a.u50 = 0.0f;
    a.u54 = 0.0f;
    b.uD = 0;
    b.uC = 0;
    b.p = q->p;
    b.q = q;
    b.u10 = (func_150ADA68() * D_800A03D0) + D_800A03D4;
    r = func_151559FC(&a, 0xA, 0, 0, 0x58, arg0[0xC], 0);
    if (r != 0)
    {
      memcpy((u8 *)r + 0x70, &b.p, 0x58);
    }
    b.q->t = (func_150ADA20() % 151U) + 0x19;
  }
}
