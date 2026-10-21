typedef struct { u16 id; u8 timer; u8 slot; } SfxPend;
#define PEND ((SfxPend *)D_80041F10)

void func_10011310(void)
{
  int new_var;
  s32 removed;
  s32 j;
  s32 n;
  s32 i;
  struct120 *e;
  removed = 0;
  j = 0;
  n = D_80041F50;
  for (i = 0; i < ((s32) D_80041F50); i++)
  {
    if (((SfxPend *) D_80041F10)[i].timer > 0)
    {
      ((SfxPend *) D_80041F10)[i].timer--;
    }
    else
    {
      removed = 1;
      new_var = ((SfxPend *) D_80041F10)[i].slot;
      ;
      if ((&D_800425E0[new_var])->unk0 == ((SfxPend *) D_80041F10)[i].id)
      {
        (&D_800425E0[new_var])->unk0 = 0;
        (&D_800425E0[new_var])->unk4 = 0;
        if ((&D_800425E0[new_var])->unk8 != 0)
        {
          func_10017594((&D_800425E0[new_var])->unk8);
        }
        (&D_800425E0[new_var])->unk8 = 0;
      }
      n--;
    }
    if (j != i)
    {
      ((SfxPend *) D_80041F10)[j] = ((SfxPend *) D_80041F10)[i];
    }
    if (removed)
    {
      j++;
    }
    else
    {
      removed = 0;
    }
  }

  D_80041F50 = n;
}
