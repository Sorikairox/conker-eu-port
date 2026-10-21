typedef struct { f32 x; f32 y; f32 z; f32 pad[3]; } Ent_151B5128;
typedef struct { u8 pad0[0x10]; u8 flags; u8 pad11[0x37]; Ent_151B5128 e[10]; } Obj_151B5128;
extern f32 D_800AA7A8;
s32 func_151B5128(Obj_151B5128 *arg0)
{
  s32 i;
  int new_var;
  f32 f;
  f32 d;
  f = -1000.0f;
  d = D_800AA7A8;
  new_var = ~2;
  for (i = 0; i < 10; i++)
  {
    arg0->e[i].x = f;
    arg0->e[i].y = 0.0f;
    arg0->e[i].z = 0.0f;
    f += d;
  }

  arg0->flags &= new_var;
  return 1;
}
