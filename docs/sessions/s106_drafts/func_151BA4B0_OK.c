typedef struct {
    s8 u0;
    s8 u1;
    s8 u2;
    s16 u4;
    s32 u8_;
    s32 uC;
    s32 u10;
    s32 u14;
    s32 u18;
    s32 u1C;
    s32 u20;
    s8 u24;
    s8 u25;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s8 u38;
    u8 u39;
} Sa4b0;
typedef struct {
    u8 *p;
    u8 b;
} Ba4b0;
extern s8 D_800E0FFE[];
u8 *func_1513B5E0(Sa4b0 *, s32, s32, u8, s32);
u8 *func_151BA4B0(u8 *arg0, u8 arg1, s32 arg2)
{
  u8 *ret;
  Sa4b0 s;
  Ba4b0 b;
  s32 idx;
  if (arg0 == 0)
  {
    return 0;
  }
  b.p = arg0;
  b.b = arg0[0x3B];
  s.u0 = 2;
  s.u1 = -1;
  s.u2 = 3;
  s.u4 = 300;
  s.u30 = 9;
  s.u34 = 0x1AD;
  s.u39 = 0xFF;
  idx = (arg0 - ((u8 *) D_800CC2D0)) / 812;
  goto dummy_label_283214; // fakematch: label barrier (permuter) puts sw a0 (b.p) before the arg0[0x3B] load
  dummy_label_283214:
  ;
  if ((idx < 2) && (D_800E0FFE[idx] != 0))
  {
    if (D_80090130 == 2)
    {
      s.u39 = 0xFD;
    }
    else
      if (D_80090130 == 4)
    {
      if (idx == 0)
      {
        s.u39 = 0xFB;
      }
      else
      {
        s.u39 = 0xF7;
      }
    }
  }
  s.u8_ = 1;
  s.uC = 0x200205;
  s.u10 = 0x60600;
  s.u24 = 0;
  s.u25 = 0;
  s.u14 = 1;
  s.u18 = 0x36;
  s.u1C = 0x80;
  s.u20 = 0x20;
  s.u38 = 2;
  ret = func_1513B5E0(&s, 1, 8, arg1, arg2);
  if (ret != 0)
  {
    memcpy((ret + (*((s32 *) (ret + 0x50)))) + ((0, 0xF8)), &b, 8); // fakematch: comma expression (permuter) gives addu a0,v0,t9
  }
  return ret;
}
