typedef struct E909C_N { s32 id; s32 pad; f32 w; struct E909C_N *next; } E909C_N;
typedef struct { f32 pos[3]; f32 v[3]; s32 pad[2]; } E909C_S;
extern s32 D_800BEE08;

void func_150E909C(u8 *arg0)
{
  f32 *cam;
  E909C_S s;
  f32 *p;
  E909C_N *n;
  f32 r;
  f32 dx;
  f32 dy;
  f32 dz;
  u8 *o;
  cam = func_15144B34(D_800BEE08);
  p = (f32 *) (arg0 + 0x28);
  p[2] += ((p[0] + (func_150ADA68() * p[1])) * D_800BE9A4) * D_800DCD90;
  while (p[2] > 1.0f)
  {
    r = func_150ADA68() * D_800DCD90;
    n = (E909C_N *) D_800DCDC4;
    while (n->w < r)
    {
      r -= n->w;
      n = n->next;
    }

    func_1514470C(n->id, s.pos);
    dx = s.pos[0] - cam[0];
    dy = s.pos[1] - cam[1];
    dz = s.pos[2] - cam[2];
    if ((((dx * dx) + (dy * dy)) + (dz * dz)) < 3240000.0f)
    {
      s.v[0] = 0.31712f;
      s.v[1] = 1.04651f;
      s.v[2] = 0.0f;
      o = (u8 *) func_15149130((func_150ADA20() % 13U) + 5, -1, 0x34, -1, 1, 0, 0x18, arg0[0xC], arg0[1]);
      if (o != 0)
      {
        memcpy((s32) (o + 0x28), (f32 *) (&s), 0x18);
      }
 goto dummy_label_122314; dummy_label_122314: ;
    }
    p[2] -= 1.0f;
  }

}
