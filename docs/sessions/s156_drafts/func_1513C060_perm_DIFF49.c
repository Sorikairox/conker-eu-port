typedef struct {
    u8 pad0[0x10];
    s32 flags10;
    u8 pad14[4];
    s32 flags18;
    s16 t1C;
    u8 b1E;
    u8 pad1F;
    s32 pos20;
    s32 vel24;
    u8 b28;
    u8 pad29[4];
    s8 b2D;
    u8 pad2E[0xC];
    s16 h3A;
    s16 h3C;
    u8 pad3E[0x42];
    u8 b80;
    u8 b81;
} C060Obj;
extern s32 (*D_8008A010[])(void);
extern s32 (*D_8008A048[])(void);
void func_1513C060(C060Obj *arg0)
{
  s32 pad;
  s8 done;
  s32 v;
  C060Obj *new_var2;
  C060Obj *new_var;
  s32 vel;
  s32 max;
  s32 pos;
  s32 *new_var3;
  if (arg0->flags10 & 1)
  {
    done = 0;
    if (arg0->flags18 & 1)
    {
      arg0->t1C -= D_800BE9E4;
      if (arg0->t1C < 0)
      {
        done = 1;
      }
    }
    if (arg0->b80 != 0)
    {
      if (D_8008A010[arg0->b80]() == 0)
      {
        done = 1;
      }
    }
    new_var2 = arg0;
    if (((new_var2->flags18 & 0x8000) && (!done)) && (new_var2->t1C < new_var2->h3A))
    {
      v = new_var2->t1C * new_var2->h3C;
      if (v < new_var2->b28)
      {
        new_var2->b28 = v;
      }
    }
    if (((new_var2->flags18 & 0x10000) && (!done)) && (new_var2->t1C < new_var2->h3A))
    {
      v = new_var2->t1C * new_var2->h3C;
      if (v < new_var2->b28)
      {
        new_var2->b2D = v;
      }
    }
    if (!done)
    {
      vel = new_var2->vel24;
      if (vel != 0)
      {
        new_var = new_var2;
        max = (D_80090F14[new_var2->b1E][0] << 16) - 1;
        new_var3 = &new_var2->flags18;
        new_var2->pos20 += vel * D_800BE9E4;
        pos = new_var2->pos20;
        if (max < pos)
        {
          if ((*new_var3) & 2)
          {
            done = 1;
          }
          else
            if ((*new_var3) & 0x40)
          {
            new_var2->vel24 = 0;
            new_var2->pos20 = max;
          }
          else
            if ((*new_var3) & 4)
          {
            new_var2->pos20 = max - (pos % max);
            new_var2->vel24 = -vel;
          }
          else
          {
            do
            {
              pos = (new_var2->pos20 = pos - max);
              if ((!new_var2) && (!new_var2))
              {
              }
            }
            while (max < pos);
          }
        }
        else
          if (pos < 0)
        {
          if ((*new_var3) & 8)
          {
            done = 1;
          }
          else
            if ((*new_var3) & 0x80)
          {
            new_var2->vel24 = 0;
            new_var2->pos20 = 0;
          }
          else
            if ((*new_var3) & 4)
          {
            new_var->pos20 = (-pos) % max;
            new_var2->vel24 = -vel;
          }
          else
          {
            do
            {
              pos = (new_var2->pos20 = pos + max);
            }
            while (pos < 0);
          }
        }
      }
    }
    if (done)
    {
      if (new_var2->b81 != 0)
      {
        if (D_8008A048[new_var2->b81]() != 0)
        {
          func_1516972C((struct102 *) new_var2);
        }
      }
      else
      {
        func_1516972C((struct102 *) new_var2);
      }
    }
  }
}
