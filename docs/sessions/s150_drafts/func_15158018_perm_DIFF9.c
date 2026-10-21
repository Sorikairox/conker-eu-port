typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3_15158018;

s32 func_15158018(u8 *arg0)
{
  f32 new_var;
  u8 *p = arg0 + 0x120;
  V3_15158018 old;
  s32 i;
  f32 g;
  f32 dx;
  f32 dz;
  if (p[0x30] & 1)
  {
    old = *((V3_15158018 *) (p + 0x10));
    if (p[0x30] & 8)
    {
      for (i = D_800BE9E4; i != 0; i--)
      {
        *((f32 *) (p + 0x10)) *= *((f32 *) (p + 0x2C));
        *((f32 *) (p + 0x18)) *= *((f32 *) (p + 0x2C));
      }

    }
    if (p[0x30] & 4)
    {
      new_var = *((f32 *) (p + 0x28));
      g = new_var;
      *((f32 *) (p + 0x14)) += g * D_800BE9A4;
    }
    else
    {
      g = 0.0f;
    }
    dx = ((*((f32 *) (p + 0x10))) - old.x) * D_800BEDC8;
    dz = ((*((f32 *) (p + 0x18))) - old.z) * D_800BEDC8;
    *((f32 *) (arg0 + 0x54)) += (old.x + ((0.5f * dx) * D_800BE9A4)) * D_800BE9A4;
    *((f32 *) (arg0 + 0x58)) += (old.y + ((0.5f * g) * D_800BE9A4)) * D_800BE9A4;
    *((f32 *) (arg0 + 0x5C)) += (old.z + ((0.5f * dz) * D_800BE9A4)) * D_800BE9A4;
  }
  if (p[0x30] & 2)
  {
    *((f32 *) (p + 0x0)) += (*((f32 *) (p + 0x1C))) * D_800BE9A4;
    *((f32 *) (p + 0x4)) += (*((f32 *) (p + 0x20))) * D_800BE9A4;
    *((f32 *) (p + 0x8)) += (*((f32 *) (p + 0x24))) * D_800BE9A4;
  }
  return 1;
}
