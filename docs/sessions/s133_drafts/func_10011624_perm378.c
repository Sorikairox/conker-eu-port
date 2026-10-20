void func_10011624(struct15 *arg0, s32 *arg1, s32 arg2, s32 arg3)
{
  s32 i;
  s32 flags;
  s32 vol;
  s32 mode;
  u32 dist;
  s32 r;
  u32 delay;
  s32 pitch;
  u16 snd;
  s32 pan;
  f32 ratio;
  SfxEnt *s;
  s32 temp;
  u16 id;
  s32 pp;
  s32 *pv;
  f32 f;
  s32 d;
  s32 old;
  for (i = arg2; (i < (*arg1)) && (i < arg3); i++)
  {
    temp = (flags = ((SfxEnt *) arg0)[i].unk10);
    if (temp & 0x80)
    {
      continue;
    }
    if (temp & 0x1000)
    {
      ((SfxEnt *) arg0)[i].unk10 = temp & (~0x1000);
      continue;
    }
    id = ((SfxEnt *) arg0)[i].unk24;
    if (((flags & 1) && (id != 0)) && (func_1000F3D0(id) == 0))
    {
      flags &= ~1;
      id = 0;
      if (!(flags & 8))
      {
        flags |= 0x80;
        ((SfxEnt *) arg0)[i].unk0 = 0;
      }
      ((SfxEnt *) arg0)[i].unk26 = 0;
      ((SfxEnt *) arg0)[i].unk22 = 0;
      ((SfxEnt *) arg0)[i].unk24 = 0;
      ((SfxEnt *) arg0)[i].unk10 = flags;
      ((SfxEnt *) arg0)[i].unk2C = 1.0f;
    }
    if ((flags & 2) || (id == 0))
    {
      if (flags & 0x100)
      {
        vol = 0x40;
        pv = 0;
      }
      else
      {
        pv = &vol;
      }
      if (flags & 0x40)
      {
        r = func_1000A750(((SfxEnt *) arg0)[i].unk4, D_80042308[0].ex, D_80042308[0].ey, D_80042308[0].ez, D_80042308[0].f, D_80042308[0].x, D_80042308[0].y, D_80042308[0].z, ((SfxEnt *) arg0)[i].unk8, ((SfxEnt *) arg0)[i].unkA, &vol, &dist, &delay);
        dist = (((SfxEnt *) arg0)[i].unkC * dist) >> 15;
      }
      else
      {
        r = func_100114D0(((SfxEnt *) arg0)[i].unk2, ((SfxEnt *) arg0)[i].unk4, ((SfxEnt *) arg0)[i].unk6, ((SfxEnt *) arg0)[i].unkC, ((SfxEnt *) arg0)[i].unk8, ((SfxEnt *) arg0)[i].unkA, pv, &dist, &delay);
      }
      if (D_800BEA35 != 0)
      {
        dist = 0;
      }
      pitch = ((SfxEnt *) arg0)[i].unk20;
      pan = ((SfxEnt *) arg0)[i].unk23;
      snd = ((SfxEnt *) arg0)[i].unk0;
      if ((flags & 0x10) && (((SfxEnt *) arg0)[i].unk14 != 0))
      {
        ((SfxEnt *) arg0)[i].unk10 = flags;
        if (((SfxEnt *) arg0)[i].unk14(&arg0[i], &r, &dist, &vol, &pitch, &pan, &snd) != 0)
        {
          func_1000FE88(arg0, i, arg1);
          continue;
        }
        id = ((SfxEnt *) arg0)[i].unk24;
        flags = ((SfxEnt *) arg0)[i].unk10;
      }
      if (snd != 0)
      {
        if (dist != 0)
        {
          pp = (vol & 0x80) | pan;
          vol &= 0x7F;
          if (flags & 0x200)
          {
            vol = 0x80 - vol;
            if (vol == 0x80)
            {
              vol = 0x7F;
            }
            pp ^= 0x80;
          }
          old = id;
          ratio = alCents2Ratio(pitch);
          if (old == 0)
          {
            mode = flags & 0xC00;
            if (mode != 0)
            {
              if (mode == 0x400)
              {
                mode = 0;
              }
              else
              {
                mode = 1;
              }
            }
            else
            {
              mode = D_80041FD9;
            }
            id = func_10010BE8(0, snd, dist, vol, pitch, pp, mode);
            if (id != 0)
            {
              flags |= 1;
              ((SfxEnt *) arg0)[i].unk0 = snd;
            }
          }
          else
          {
            if (dist != ((SfxEnt *) arg0)[i].unk26)
            {
              func_1000F85C(id, 8, dist);
            }
            if (vol != (((SfxEnt *) arg0)[i].unk22 & 0x7F))
            {
              func_1000F85C(id, 4, vol);
            }
            if (pp != (((SfxEnt *) arg0)[i].unk23 | (((SfxEnt *) arg0)[i].unk22 & 0x80)))
            {
              func_1000F85C(id, 0x100, pp);
            }
            if (flags & 4)
            {
              d = ((s32) ((((SfxEnt *) arg0)[i].unk28 - delay) * D_800BE9E4)) / 3;
              if (d >= 0x16F)
              {
                f = 2.0f;
              }
              else
              {
                f = 367.0f / (0x16F - d);
                if (f > 2.0f)
                {
                  f = 2.0f;
                }
                else
                  if (f < 0.5f)
                {
                  f = 0.5f;
                }
              }
              ratio *= f;
              ratio = ((ratio - ((SfxEnt *) arg0)[i].unk2C) * 0.3f) + ((SfxEnt *) arg0)[i].unk2C;
            }
            if (ratio != ((SfxEnt *) arg0)[i].unk2C)
            {
              func_1000F85C(id, 0x11, *((s32 *) (&ratio)));
            }
          }
          ((SfxEnt *) arg0)[i].unk28 = delay;
          ((SfxEnt *) arg0)[i].unk26 = dist;
          ((SfxEnt *) arg0)[i].unk22 = vol | pp;
          ((SfxEnt *) arg0)[i].unk23 = pan;
          ((SfxEnt *) arg0)[i].unk2C = ratio;
 dummy_label_22270: ;
        }
        else
          if (flags & 8)
        {
          if (id != 0)
          {
            func_100111C8(id);
          }
          id = 0;
          flags &= ~1;
        }
        else
        {
          func_1000FE88(arg0, i, arg1);
          continue;
        }
      }
    }
    ((SfxEnt *) arg0)[i].unk24 = id;
    ((SfxEnt *) arg0)[i].unk10 = flags;
  }

}
