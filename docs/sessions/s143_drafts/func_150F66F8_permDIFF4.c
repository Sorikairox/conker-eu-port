s32 func_15145EA4(s32 **, struct17 **, s32, s32);
extern s32 D_800A1EE8;
extern s32 D_800A1EF4;
typedef struct {
    u8 pad0[0x48];
    f32 unk48;
    f32 unk4C;
    u8 pad50[8];
    u8 pad58;
} Sub110;
typedef struct {
    u8 *obj;
    u8 unk4;
    u8 pad5[3];
    u8 *unk8;
    u8 *unkC;
} Sub28;

void func_150F66F8(u8 *arg0)
{
  Sub28 *sub;
  u8 *obj;
  struct17 a;
  struct17 b;
  s32 *tbl[2];
  struct17 *out[2];
  int new_var;
  s32 pad[4];
  u8 *v;
  u8 *p;
  sub = (Sub28 *) (arg0 + 0x28);
  obj = sub->obj;
  if (((*((s32 *) obj)) == 0) || (sub->unk4 != obj[0x3B]))
  {
    *((s16 *) (arg0 + 0xE)) = -1;
    return;
  }
  new_var = 0x110;
  if (((*((s32 *) (obj + 0x1D4))) != 0) && (!((*((s32 *) (obj + 0x94))) & 2)))
  {
    tbl[0] = &D_800A1EE8;
    tbl[1] = &D_800A1EF4;
    out[0] = &a;
    out[1] = &b;
    func_15145EA4(tbl, out, *((s32 *) (obj + 0x1D4)), 2);
    v = sub->unk8;
    if (v != 0)
    {
      v[0x168] = v[0x168] | 1;
      *((struct17 *) (v + 0x34)) = a;
      *((struct17 *) (v + 0x40)) = b;
    }
    v = sub->unkC;
    if (v != 0)
    {
      p = *((u8 **) (v + 0x14));
      p[9] = 0;
      *((s16 *) (p + 0xE)) = a.unk0;
      *((s16 *) (p + 0x10)) = a.unk4;
      *((s16 *) (p + 0x12)) = a.unk8;
    }
 dummy_label_890930: ;
  }
  else
  {
    v = sub->unk8;
    if (v != 0)
    {
      ((Sub110 *) (v + new_var))->pad58 &= 0xFFFE;
    }
    v = sub->unkC;
    if (v != 0)
    {
      (*((u8 **) (v + 0x14)))[9] = 1;
    }
  }
  v = sub->unk8;
  if (v != 0)
  {
    ((Sub110 *) (v + new_var))->unk48 = 4.0f;
    ((Sub110 *) (v + new_var))->unk4C = 8.0f;
  }
}
