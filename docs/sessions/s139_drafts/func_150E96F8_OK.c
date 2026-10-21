typedef struct E96F8_N { s32 id; s32 pad; f32 w; struct E96F8_N *next; } E96F8_N;
extern s32 D_800BEE08;
typedef struct { f32 pos[3]; f32 v[4]; u8 pad1C[0x14]; s32 u30; u8 u34; u8 u35; s32 u38; } E96F8_S;

void func_150E96F8(u8 *arg0)
{
  f32 *cam;
  f32 r;
  f32 *p;
  E96F8_N *n;
  E96F8_S s;
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
    n = (E96F8_N *) D_800DCDC4;
    while (n->w < r)
    {
      r -= n->w;
      n = n->next;
    }

    func_1514470C(n->id, s.pos);
    dx = s.pos[0] - cam[0];
    dy = s.pos[1] - cam[1];
    dz = s.pos[2] - cam[2];
    if ((((dx * dx) + (dy * dy)) + (dz * dz)) < 1960000.0f)
    {
      s.v[0] = 0.19324f;
      s.v[1] = 0.31401f;
      s.v[2] = 0.0f;
      s.v[3] = 99999.9f;
      s.u30 = 0;
      s.u34 = 0;
      s.u35 = 0;
      s.u38 = 0;
      o = (u8 *) func_15149130((func_150ADA20() % 13U) + 5, -1, 0x37, -1, 1, 0, 0x3C, arg0[0xC], arg0[1]);
      if (o != 0)
      {
        memcpy((s32) (o + 0x28), (f32 *) (&s), 0x3C);
      }
      goto dummy_label_122314; // fakematch: permuter label, fixes the s-reg order
      dummy_label_122314:
      ;
      ;
    }
    p[2] -= 1.0f;
  }

}
