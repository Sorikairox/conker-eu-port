typedef struct {
    s8 cmd;
    u8 b1;
    u8 b2;
    u8 b3;
    s32 w1;
} G8F08;

void func_15168F08(G8F08 *gfx, s32 base)
{
  s32 i;
  s32 c;
  G8F08 *g;
  i = 0;
  g = gfx;
  if (g->cmd != (-0x21))
  {
    ;
    do
    {
      i++;
      if ((g->cmd == 1) || ((g->cmd == (-0x24)) && (g->b3 == 0xE)))
      {
        g->w1 &= 0xFFFFFF;
        g->w1 += base;
      }
      g = &gfx[i];
      gfx++; // fakematch
      gfx--;
    }
    while (g->cmd != (-0x21));
  }
}
