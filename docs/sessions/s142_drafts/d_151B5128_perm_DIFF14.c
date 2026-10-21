typedef struct { f32 x, y, z; u8 padC[0xC]; } E5128;
volatile unsigned char func_151B5128(u8 *arg0)
{
  f32 x = -1000.0f;
  s32 i;
  i = 0;
  do
  {
    u8 *new_var;
    ((E5128 *) (arg0 + 0x48))[i].x = x;
    ((E5128 *) (arg0 + 0x48))[i].y = 0.0f;
    new_var = arg0 + 0x48;
    ((E5128 *) new_var)[i].z = 0.0f;
    x += 222.22223f;
  }
  while ((++i) < 10);
  arg0[0x10] &= ~2;
  return 1;
}
