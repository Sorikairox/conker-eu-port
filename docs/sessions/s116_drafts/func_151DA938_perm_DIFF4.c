typedef struct { f32 x, y, z; s32 a, b; } Node14;
extern f32 D_800AB87C;
s32 func_151DAB58(u8, f32, u8, f32 *, s32, s32, s32);
s32 func_151DA938(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5)
{
  u8 *tbl;
  u8 *obj;
  f32 pos[3];
  u8 *p;
  s32 pad;
  pad = 0x48;
  tbl = *((u8 **) (arg0 + 0x94));
  obj = *((u8 **) (arg0 + 0x98));
  pos[0] = ((Node14 *) tbl)[*((s8 *) (arg0 + 0x2D))].x;
  pos[1] = arg4 + 2.0f;
  pos[2] = ((Node14 *) tbl)[*((s8 *) (arg0 + 0x2D))].z;
  if (func_150ADA20() & 1)
  {
    p = obj + pad;
    func_151D9B8C(*((u8 *) (p + 8)), ((*((f32 *) (obj + 0))) * 3.0f) * (*((f32 *) p)), *((u8 *) (obj + 0x1B)), arg5, (struct17 *) pos, 0x64, 0, 1, 0, *((u8 *) (arg0 + 0xC)), *((u8 *) (arg0 + 1)));
  }
  else
  {
    p = obj + pad;
    func_151DAB58(*((u8 *) (p + 8)), ((*((f32 *) (obj + 0))) * D_800AB87C) * (*((f32 *) p)), *((u8 *) (obj + 0x1B)), pos, 1, *((u8 *) (arg0 + 0xC)), *((u8 *) (arg0 + 1)));
  }
  *((s8 *) (obj + 0x20)) = 4;
  return 1;
}
