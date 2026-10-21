s32 func_1000EE70(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, void *arg5)
{
  struct_eu_sfx *sfx = arg0;
  SfxObj *obj = (SfxObj *) sfx->unk18;
  unsigned short id;
  if ((obj != 0) && ((*((s32 *) arg2)) != 0))
  {
    id = sfx->unk1C & 0xFF;
    if ((obj->unk0 != 0) && (((u8 *) obj)[0x3B] == id))
    {
      *((s32 *) arg5) = ((obj->unk184 >> 3) & 0x30) * 2;
      sfx->unk2 = obj->unk14;
      sfx->unk4 = obj->unk18;
      sfx->unk6 = obj->unk1C;
      return 0;
    }
    if (func_1000F44C(sfx->unk24) == 0)
    {
      return 0;
    }
  }
  return 1;
}
