typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
} DCA8Draw;
typedef struct {
    u8 pad0[0xE];
    s16 hE;
    s16 h10;
    s16 h12;
    s16 h14;
    s16 h16;
    u8 pad18[2];
    u8 b1A;
    u8 b1B;
    u8 b1C;
    u8 b1D;
    u8 b1E;
    u8 b1F;
    u8 r;
    u8 g;
    u8 b;
} DCA8Obj;
extern u8 *D_8008CDEC[];
extern s16 D_800DD5EC;
extern s32 D_800D30BC;
extern u8 D_800D31C8;
extern u8 D_800D31C9;
extern u8 D_800D31CA;
Gfx *func_15095B70(Gfx *, DCA8Draw *);
Gfx *func_1516DCA8(Gfx *gfx, DCA8Obj *arg1, s32 arg2)
{
  u8 new_var2;
  DCA8Draw d;
  u8 *tex;
  s32 flag;
  s16 new_var;
  s32 om[7];
  s32 mode;
  int new_var3;
  s32 r;
  s32 g;
  s32 b;
  flag = 0;
  D_800D31CB = 0;
  tex = D_8008CDEC[arg1->b1A];
  new_var2 = arg1->b1B;
 do { gfx = (Gfx *) func_15142E24((s32) gfx, (s32) tex, new_var2 << 8, 2, 0x100, 0x100, 0, 6, (s32) (&d), (u8 *) (&flag), 3); } while (0);
  if (tex[0xA] == 5)
  {
    mode = 2;
  }
  else
  {
    mode = 1;
  }
  if (mode != D_800DD5EC)
  {
    if (flag == 0)
    {
      {
        Gfx *_g = (Gfx *) (gfx++);
        _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24);
        _g->words.w1 = 0;
      }
      ;
      flag = 1;
    }
    D_800DD5EC = mode;
    if (mode == 1)
    {
      om[0] = 0;
      {
        Gfx *_g = gfx++;
        _g->words.w0 = 0xFC30B261;
        _g->words.w1 = 0x5566FF7F;
      }
    }
    else
    {
      om[0] = 0x100000;
      {
        Gfx *_g = gfx++;
        _g->words.w0 = 0xFC30B5FF;
        _g->words.w1 = 0x5FFEFE38;
      }
    }
  }
  gfx = func_15142FBC(gfx, (om[0] | D_800D30BC) | 0x2C00, 0x5049DC, (u8 *) (&flag));
  d.h0 = arg1->hE;
  d.h2 = arg1->h10;
  d.h4 = arg1->h12;
  d.h6 = arg1->h14;
  new_var = arg1->h16;
  d.h8 = new_var;
  d.bD = 0;
  d.bA = arg1->b1F;
  D_800D31C8 = arg1->b1C;
  D_800D31C9 = arg1->b1D;
  D_800D31CA = arg1->b1E;
  r = arg1->r;
  g = arg1->g;
  b = arg1->b;
  if (((r != D_800DD5F8) || (g != D_800DD5FA)) || (b != D_800DD5FC))
  {
    D_800DD5F8 = r;
    D_800DD5FA = g;
    new_var3 = flag == 0;
    D_800DD5FC = b;
    if (new_var3)
    {
      {
        Gfx *_g = (Gfx *) (gfx++);
        _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24);
        _g->words.w1 = 0;
      }
      ;
    }
    {
      Gfx *_g = (Gfx *) (gfx++);
      _g->words.w0 = (unsigned int) ((((unsigned int) 0xfb) & ((0x01 << 8) - 1)) << 24);
      _g->words.w1 = (unsigned int) (((((unsigned int) ((((unsigned int) r) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) g) & ((0x01 << 8) - 1)) << 16))) | ((unsigned int) ((((unsigned int) b) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 8) - 1)) << 0)));
    }
    ;
  }
  return func_15095B70(gfx, &d);
}
