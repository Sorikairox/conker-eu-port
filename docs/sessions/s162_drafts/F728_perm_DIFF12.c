typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3_1513F728;
typedef struct {
    V3_1513F728 vel;
    f32 g;
    f32 damp;
    f32 rot[3];
} struct_eu_1513F728_phys;
typedef struct {
    u8 pad0[0x34];
    f32 pos[3];
    f32 ang[3];
    u8 pad4C[0xC4];
    struct_eu_1513F728_phys phys;
} struct_eu_1513F728;
extern s32 D_800BE9E4;
extern f32 D_800BEDC8;

s32 func_1513F728(struct_eu_1513F728 *arg0)
{
  struct_eu_1513F728_phys *p = &arg0->phys;
  V3_1513F728 old;
  s32 i;
  f32 dx;
  f32 dy;
  f32 dz;
  old = p->vel;
  for (i = D_800BE9E4; i != 0; i--)
  {
    p->vel.x *= p->damp;
    p->vel.y *= p->damp;
    p->vel.z *= p->damp;
  }

  p->vel.y += p->g * D_800BE9A4;
  dx = (p->vel.x - old.x) * D_800BEDC8;
  dy = (p->vel.y - old.y) * D_800BEDC8;
  dz = (p->vel.z - old.z) * D_800BEDC8;
  arg0->pos[0] += (old.x + ((0.5f * dx) * D_800BE9A4)) * D_800BE9A4;
  arg0->pos[1] += (old.y + ((0.5f * dy) * D_800BE9A4)) * D_800BE9A4;
  arg0->pos[2] += (old.z + ((0.5f * dz) * D_800BE9A4)) * D_800BE9A4;
 dummy_label_423152: ;
  arg0->ang[0] += p->rot[0] * D_800BE9A4;
  arg0->ang[1] += p->rot[1] * D_800BE9A4;
  arg0->ang[2] += p->rot[2] * D_800BE9A4;
  return 1;
}
