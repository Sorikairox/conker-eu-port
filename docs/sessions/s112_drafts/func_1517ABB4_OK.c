s32 func_1510EDAC(s32, s32, f32 *, s32, s32, s32, f32, f32, f32, f32, s32, s32);

void func_1517ABB4(f32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4)
{
  u8 *obj;
  s32 n;
  f32 d;
  s32 h;
  s32 pad;
  n = arg0;
  if (n != 0)
  {
    obj = func_15167A68(9, 0, 0xB8, 1, 0xFF, 1);
    if (obj)
    {
      func_1510EDAC(0, 0, &d, 0, 0, 0, arg2, arg3, arg4, arg3, 0, 0);
 if (0) {} // fakematch: block boundary, puts the shared s16 store value in v0
      *((s16 *) (obj + 0x92)) = (*((s16 *) (obj + 0xB0)) = d + 3.0f);
      *((s16 *) (obj + 0x90)) = arg2;
      *((s16 *) (obj + 0x94)) = arg4;
      *((s16 *) (obj + 0x96)) = 0x5A;
      *((s16 *) (obj + 0x98)) = func_150ADA20() % 360U;
      *((s16 *) (obj + 0x9A)) = 0;
      *((s16 *) (obj + 0xA0)) = 0;
      *((s16 *) (obj + 0xA4)) = 0;
      *((u8 *) (obj + 0x9F)) = arg1;
      *((f32 *) (obj + 0xA8)) = ((s32) ((func_150ADA20() % 80U) + 0x64)) * 0.01f;
      *((s16 *) (obj + 0xA2)) = arg0 * 0.4f;
      h = arg0 * 0.5f;
      *((s8 *) (obj + 0x9C)) = (func_150ADA20() % ((u32) n)) - h;
      *((s8 *) (obj + 0x9D)) = (func_150ADA20() % ((u32) n)) - h;
      *((s8 *) (obj + 0x9E)) = (func_150ADA20() % ((u32) n)) - h;
      *((s16 *) (obj + 0xA6)) = 0;
      *((u8 *) (obj + 0xB3)) = 0xFF;
    }
  }
}
