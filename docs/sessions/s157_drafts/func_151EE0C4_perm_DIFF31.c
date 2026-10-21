void *allocate_memory(s32, s32, s32, s32);
void func_10004074(void *);
void func_1503F8A8(void *, s32, s32, s32, f32, s32);
s32 func_1503F91C(s32, s32, void *, void *, void *, void *, void *);
extern void guMtxIdentF(float mf[4][4]);

typedef struct {
    u8 pad[0x3E0];
    void *m0;
    void *m1;
} DlObj3E0;

typedef struct {
    Gfx **dls;
    Gfx *copy[4];
    u8 count;
    u8 flag;
    u8 pad16[6];
    s32 u1C;
    s32 u20;
    DlObj3E0 *obj;
    f32 m0[4][4];
    f32 m1[4][4];
} DlCopy;

DlCopy *func_151EE0C4(s32 arg0, s32 arg1, s32 arg2, volatile unsigned int arg3)
{
  DlCopy *s;
  s32 i;
  s32 j;
  Gfx *src;
  Gfx **new_var;
  Gfx *dst;
  u32 w;
  u32 cmd;
  s = allocate_memory(0xA8, 1, 0, 1);
  if (s == 0)
  {
    return 0;
  }
  s->flag = 1;
  if (func_1503F91C(arg0, arg1, s, &s->count, &s->u1C, &s->u20, &s->obj) != 0)
  {
    func_10004074(s);
    return 0;
  }
  guMtxIdentF(s->m0);
  guMtxIdentF(s->m1);
  s->obj->m0 = s->m0;
  s->obj->m1 = s->m1;
  func_1503F8A8(s->obj, 1, arg2, arg3, 0.0f, 0);
  for (i = 0; (i + 1) <= s->count; i++)
  {
    j = 0;
    src = (new_var = s->dls)[i];
    do
    {
      w = src->words.w0;
      src++;
      j = j + 8;
    }
    while (((w >> 24) & 0xFF) != 0xDF);
    if ((s->copy[i] = allocate_memory(j, 1, 1, 1)) == 0)
    {
      for (j = 0; j < i; j++)
      {
        func_10004074(s->copy[j]);
      }

      func_10004074(s);
      return 0;
    }
  }

  for (i = 0; i < s->count; i++)
  {
    dst = s->copy[i];
    src = s->dls[i];
    do
    {
      w = src->words.w0;
      src++;
      dst->words.w0 = w;
      dst->words.w1 = src[-1].words.w1;
      cmd = (w >> 24) & 0xFF;
      if (cmd == 0xEF)
      {
        dst->words.w0 = w & 0xFFFEFFFF;
        dst->words.w1 = 0x5041C8;
      }
      if (cmd == 0xFC)
      {
        dst->words.w0 = 0;
      }
      dst++;
    }
    while (cmd != 0xDF);
  }

  return s;
}
