// PERMUTER CHANGED DECL: s32func_150B6314(u8*,u8,s32) (base: s32func_150B6314(u8*arg0,u8arg1,s32arg2))
s32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_151307F0(void *, u8, s32, s32, u8, s32);
typedef struct { s32 w[3]; } Vec3w;
s32 func_150B6314(u8 *arg0, u8 arg1, s32 arg2)
{
  struct 
  {
    s32 u34;
    s32 u38;
    s16 u3C;
    s16 u3E;
    s32 u40;
    s32 u44;
    u8 u48;
    u8 u49;
    u8 u4A;
    u8 u4B;
    u8 u4C;
    u8 u4D;
    u8 u4E;
    u8 u4F;
    u8 u50;
    u8 u51;
    s16 u52;
    s16 u54;
    s16 u56;
    f32 u58;
    f32 u5C;
    f32 u60;
    f32 u64;
    f32 u68;
    f32 u6C;
    f32 pad70f[3];
    f32 u7Cf[3];
    f32 u88;
    s32 u8C;
    u8 pad90[4];
    s8 u94;
    s8 u95;
    s8 u96;
    s8 u97;
    s8 u98;
    s8 u99;
    u8 pad9A[0xA];
  } sp;
  s32 g;
  s32 f;
  sp.u51 = 0x2B;
  sp.u3C = 0x4403;
  sp.u34 = 0x200005;
  sp.u38 = 0x20000;
  sp.u3E = (func_150ADA20() % 7U) + 4;
  sp.u40 = 0;
  sp.u44 = 0;
  sp.u48 = 0xFF;
  sp.u49 = 0xFF;
  sp.u4A = 0xFF;
  sp.u4B = 0xFF;
  sp.u4C = 0xFF;
  sp.u4D = 0xFF;
  sp.u4E = 0xFF;
  sp.u4F = 0xFF;
  sp.u50 = 0xFF;
  sp.u5C = (sp.u60 = (func_150ADA68() * 500.0f) + 500.0f);
  *((Vec3w *) (&sp.u64)) = *((Vec3w *) arg0);
  sp.u52 = 3;
  sp.u54 = 0x55;
  sp.u56 = 1;
  sp.pad70f[0] = 0.0f;
  sp.pad70f[1] = 0.0f;
  sp.pad70f[2] = 0.0f;
  sp.u7Cf[0] = 0.0f;
  sp.u7Cf[1] = 0.0f;
  sp.u7Cf[2] = 0.0f;
  sp.u88 = 0.0f;
  sp.u58 = 1.0f;
  if (func_150ADA20() & 1)
  {
    f = 0x40;
  }
  else
  {
    f = 0;
  }
  if (((((((((((((func_150ADA20() & 1) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu)
  {
    g = 0x80;
  }
  else
  {
    g = 0;
  }
  sp.u8C = ((g | 1) | f) | 0xC200;
  sp.u94 = 6;
  sp.u95 = 6;
  sp.u96 = -1;
  sp.u97 = -1;
  sp.u98 = -1;
  sp.u99 = 4;
  return func_151307F0(&sp, 1, 0, 0, arg1, arg2);
}
