s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_151307F0(s32, u8, s32, s32, u8, s32);
typedef struct { s32 w[3]; } VecF0BEC;
void func_150F0BEC(u8 *arg0)
{
  struct 
  {
    s32 u0;
    s32 u4;
    s16 u8;
    s16 uA;
    s32 uC;
    s32 u10;
    u8 u14;
    u8 u15;
    u8 u16;
    u8 u17;
    u8 u18;
    u8 u19;
    u8 u1A;
    u8 u1B;
    u8 u1C;
    u8 u1D;
    s16 u1E;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    f32 u2C;
    f32 u30[3];
    VecF0BEC u3C;
    VecF0BEC u48;
    f32 u54;
    s32 u58;
    s32 u5C;
    s8 u60;
    s8 u61;
    s8 u62;
    s8 u63;
    s8 u64;
    s8 u65;
    u8 u66;
    s16 u68;
    f32 u6C;
  } sp;
  struct 
  {
    u8 *p;
    u8 b;
    f32 a[3];
  } t;
  s32 g;
  s32 r;
  s32 f;
  sp.u1D = 0x2B;
  sp.u8 = 0x4403;
  sp.u0 = 0x200005;
  sp.u4 = 0x70600;
  sp.uA = 0x12C;
  sp.uC = 0;
  sp.u10 = 0;
  sp.u14 = 0xFF;
  sp.u15 = 0xFF;
  sp.u16 = 0xFF;
  sp.u17 = 0xFF;
  sp.u18 = 0xFF;
  sp.u19 = 0xD9;
  sp.u1A = 0xA0;
  sp.u1B = 0xFF;
  sp.u1C = 0xFF;
  sp.u28 = (sp.u2C = 250.0f);
  sp.u30[0] = *((f32 *) (arg0 + 0x14));
  sp.u30[1] = *((f32 *) (arg0 + 0x18));
  sp.u30[2] = *((f32 *) (arg0 + 0x1C));
  sp.u3C = *((VecF0BEC *) D_800A5860);
  sp.u48 = *((VecF0BEC *) D_800A5860);
  sp.u1E = 1;
  sp.u20 = 0xFF;
  sp.u22 = 1;
  sp.u54 = 0.0f;
  sp.u24 = 1.0f;
  if (func_150ADA20() & 1) f = 0x40; else f = 0;
  if ((u8)(func_150ADA20() & 1)) g = 0x80; else g = 0;
  sp.u58 = ((g | f) | 0xC000) | 0x40000;
  sp.u60 = 6;
  sp.u61 = 6;
  sp.u62 = 0x25;
  sp.u63 = -1;
  sp.u64 = -1;
  sp.u65 = 0xA;
  sp.u5C = 0;
  sp.u66 = 0xFF;
  sp.u68 = 0;
  t.p = arg0;
  sp.u6C = 10000.0f;
  t.b = arg0[0x3B];
  t.a[0] = (func_150ADA68() * 2.0f) * 3.1415927f;
  t.a[1] = (func_150ADA68() * 2.0f) * 3.1415927f;
  t.a[2] = (func_150ADA68() * 2.0f) * 3.1415927f;
  r = func_151307F0((s32) (&sp), 1, 0, 0x14, 0xFF, 1);
  if (r != 0)
  {
    memcpy(((u8 *) r) + 0xA8, &t, 0x14);
  }
}
