// PERMUTER CHANGED DECL: voidfunc_15106B90(struct102*) (base: voidfunc_15106B90(struct102*arg0))
void func_15143874(s16, f32, f32 *, f32 *);

void func_15106B90(struct102 *arg0)
{
  s32 i;
  u8 *src;
  V3_133A70 *d;
  V3_133A70 *dst;
  u8 *q;
  src = (u8 *) func_15106760((s32) arg0);
  d = (V3_133A70 *) func_1510676C((struct_eu_133A70 *) arg0);
  d[0] = *((V3_133A70 *) (((u8 *) arg0) + 0x14));
  d[(*((s32 *) (((u8 *) arg0) + 0x48))) + 1] = *((V3_133A70 *) (((u8 *) arg0) + 0x38));
  for (i = 1; i < ((*((s32 *) (((u8 *) arg0) + 0x48))) + 1); i++)
  {
    s32 pad; // fakematch: frame slot below s, c
    f32 s;
    f32 c;
    dst = &d[i];
    q = src + ((i - 1) * 0x34);
    if (!arg0) { // fakematch: permuter (s-register order of i / dst / src)
    }
    func_15143874(func_150ADA20() & 0xFF, (*((f32 *) (((u8 *) arg0) + 0x4C))) * func_150ADA68(), &c, &s);
    dst->x = (*((f32 *) (q + 4))) + (((*((f32 *) (q + 0x28))) * s) + ((*((f32 *) (q + 0x1C))) * c));
    dst->y = (*((f32 *) (q + 8))) + (((*((f32 *) (q + 0x2C))) * s) + ((*((f32 *) (q + 0x20))) * c));
    dst->z = (*((f32 *) (q + 0xC))) + (((*((f32 *) (q + 0x30))) * s) + ((*((f32 *) (q + 0x24))) * c));
  }

}
