typedef struct { s16 x; s16 y; s16 z; u8 pad6[0xF]; u8 unk15; u8 pad16; s8 unk17; s32 unk18; s32 unk1C; u8 pad20[4]; f32 unk24; f32 unk28; f32 unk2C; f32 unk30; } Ent34;
s32 func_150A332C(Ent34 *arg0, f32 arg1, f32 arg2, f32 arg3)
{
  float new_var;
  arg1 -= arg0->x;
  new_var = arg0->z;
  arg2 -= arg0->y;
  arg3 = arg2 - new_var;
  arg3 = arg2 - arg0->z;
  new_var = (((arg3 * arg0->unk30) + (arg1 * arg0->unk2C)) * arg0->unk28) - (arg2 * arg0->unk24);
  if (new_var <= 0.0f)
  {
    return 1;
  }
  return 0;
}
