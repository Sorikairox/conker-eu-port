typedef struct MemBlk {
  struct MemBlk *next;
  struct MemBlk *prev;
  u32 info;
  struct MemBlk *fnext;
  struct MemBlk *fprev;
} MemBlk;
extern struct54 *D_8003841C;

void func_10004074(void *arg0)
{
  MemBlk *b;
  MemBlk *o;
  MemBlk *n;
  MemBlk *t;
  u32 info;
  s32 merged;
  OSIntMask mask;
  o = (MemBlk *) ((u8 *) arg0 - 0xC);
  if (arg0 != NULL)
  {
    b = o;
    merged = 0;
    mask = osSetIntMask(1);
    ((u8 *) o)[8] = 0;
    n = o->prev;
    if (n != NULL)
    {
      info = n->info;
      if ((info >> 24) == 0)
      {
        t = o->next;
        b = n;
        merged = 1;
        n->next = t;
        n->info = info + o->info + 0xC;
        if (t != NULL)
        {
          t->prev = n;
        }
      }
    }
    n = b->next;
    if ((n != NULL) && ((n->info >> 24) == 0))
    {
      t = n->next;
      b->next = t;
      merged = 1;
      b->info = b->info + n->info + 0xC;
      if (t != NULL)
      {
        t->prev = b;
      }
      t = n->fnext;
      b->fnext = t;
      if (t != NULL)
      {
        t->fprev = b;
      }
      t = n->fprev;
      if (t == NULL)
      {
        *(MemBlk **) &D_800380B8 = b;
        b->fprev = NULL;
      }
      else if (t != b)
      {
        b->fprev = t;
        if (t != NULL)
        {
          t->fnext = b;
        }
      }
    }
    if (merged == 0)
    {
      n = (MemBlk *) D_800380B8;
      if (n == NULL)
      {
        b->fnext = NULL;
        b->fprev = NULL;
        *(MemBlk **) &D_800380B8 = b;
      }
      else if ((u32) b < (u32) n)
      {
        b->fnext = n;
        b->fprev = NULL;
        n->fprev = b;
        *(MemBlk **) &D_800380B8 = b;
      }
      else
      {
      loop:
        t = n->fnext;
        if (t == NULL)
        {
          b->fnext = NULL;
          b->fprev = n;
          n->fnext = b;
        }
        else if ((u32) b < (u32) t)
        {
          b->fnext = t;
          b->fprev = n;
          t->fprev = b;
          n->fnext = b;
        }
        else
        {
          n = t;
          goto loop;
        }
      }
    }
    if (b->fnext == NULL)
    {
      *(MemBlk **) &D_8003841C = b;
    }
    info = b->info;
    if ((u32) D_8002AC30 < info)
    {
      D_8002AC30 = info;
      *(MemBlk **) &D_800380B0 = b;
    }
    osSetIntMask(mask);
  }
}
