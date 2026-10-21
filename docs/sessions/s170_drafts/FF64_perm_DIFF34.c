// PERMUTER CHANGED DECL: s32func_1517F470(arg0) (base: s32func_1517F470())
Gfx *func_1517FF64(Gfx *gfx, s32 x0, s32 y0, s32 x1, s32 y1, s32 i)
{
  s32 t;
  s32 l;
  s32 u;
  s32 r;
  s32 d;
  if (x1 < x0)
  {
    t = x0;
    x0 = x1;
    x1 = t;
  }
  if (y1 < y0)
  {
    t = y0;
    y0 = y1;
    y1 = t;
  }
  l = *((f32 *) ((((u8 *) D_800BE628) + (i * 0x180)) + 0x2C));
  u = *((f32 *) ((((u8 *) D_800BE628) + (i * 0x180)) + 0x24));
  r = *((f32 *) ((((u8 *) D_800BE628) + (i * 0x180)) + 0x30));
  d = *((f32 *) ((((u8 *) D_800BE628) + (i * 0x180)) + 0x28));
  if ((((d <= y0) || (y1 <= u)) || (r <= x0)) || (x1 <= l))
  {
    return gfx;
  }
  {
    s32 a;
    s32 b;
    s32 c;
    s32 e;
    a = ((x0 < l) ? (l) : ((r < x0) ? (r) : (x0))) ^ 0;
    b = (y0 < u) ? (u) : ((d < y0) ? (d) : (y0));
    c = (x1 < l) ? (l) : ((r < x1) ? (r) : (x1));
    e = (y1 < u) ? (u) : ((d < y1) ? (d) : (y1));
    {
      Gfx *_g = (Gfx *) (gfx++);
      _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf6) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) c) & ((0x01 << 10) - 1)) << 14))) | ((unsigned int) ((((unsigned int) e) & ((0x01 << 10) - 1)) << 2));
      _g->words.w1 = ((unsigned int) ((((unsigned int) a) & ((0x01 << 10) - 1)) << 14)) | ((unsigned int) ((((unsigned int) b) & ((0x01 << 10) - 1)) << 2));
    }
    ;
  }
  return gfx;
}
