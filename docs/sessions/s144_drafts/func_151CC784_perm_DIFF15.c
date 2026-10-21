typedef struct { u8 *unk0; u8 pad4[8]; u8 unkC; u8 padD[0xB]; f32 unk18; f32 unk1C; u8 pad20[0x34]; s8 unk54; } SubC784;
extern f32 D_800AB2A0;
f32 func_151CC784(u8 *arg0)
{
  SubC784 *v;
  f32 r;
  v = (SubC784 *) (arg0 + 0x70);
  if (v->unkC & 4)
  {
    f32 t;
    t = D_800C3958[v->unk54].unk28 * D_800AB2A0;
    r = v->unk18 + ((v->unk1C - v->unk18) * t);
  }
  else
  {
    r = *((f32 *) (v->unk0 + 0x19C));
    r = (((0, *((f32 *) (v->unk0 + 0x1A0)))) + r) * 0.5f;
  }
  if (r < v->unk18)
  {
    return v->unk18;
  }
  if (v->unk1C < r)
  {
    return v->unk1C;
  }
  return r;
}
