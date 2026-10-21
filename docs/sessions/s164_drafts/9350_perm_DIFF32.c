s32 func_15149350(u8 *arg0)
{
  u16 a;
  u16 step;
  s32 i;
  u8 *v;
  Part9064 *base;
  if ((*((s8 *) (arg0 + 0x2C))) >= 3)
  {
    (*((s8 *) (arg0 + 0x2C)))--;
    v = *((u8 **) (arg0 + 0x98));
    base = *((Part9064 **) (arg0 + 0x94));
    step = 0x1000 / (*((s8 *) (arg0 + 0x2C)));
    i = *((s8 *) (arg0 + 0x2D));
    if (v[0x18] & 0x20)
    {
      a = 0x1000;
    }
    else
    {
      a = 0;
    }
    (*((s8 *) (arg0 + 0x2E)))--;
    if ((*((s8 *) (arg0 + 0x2E))) < 0)
    {
      *((s8 *) (arg0 + 0x2E)) = (*((u8 *) (arg0 + 0x25))) - 1;
    }
    while (i != (*((s8 *) (arg0 + 0x2E))))
    {
      base[i].a = 0;
      if (v[0x18] & 0x20)
      {
        a -= step;
      }
      else
      {
        a += step;
      }
      i++;
      if (i == (*((u8 *) (arg0 + 0x25))))
      {
        i = 0;
      }
    }

    return 1;
  }
  return 0;
}
