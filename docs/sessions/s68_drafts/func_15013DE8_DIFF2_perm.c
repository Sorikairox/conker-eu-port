s32 func_15149AC0(f32 *, s32, s32, s32, s32, s32);
extern f32 D_80096A04, D_80096A08, D_80096A0C, D_80096A10, D_80096A14, D_80096A18, D_80096A1C, D_80096A20, D_80096A24, D_80096A28;

s32 func_15013DE8(u8 *arg0)
{
  struct 
  {
    f32 u30;
    f32 u34;
    f32 u38;
    f32 u3C;
    f32 u40;
    f32 u44;
    f32 u48;
    f32 u4C;
    s16 u50;
    s16 u52;
    s16 u54;
    u8 u56;
    u8 u57;
    u8 u58;
    u8 u59;
    s16 u5A;
    u8 u5C;
    u8 u5D;
    u8 u5E;
    u8 u5F;
    s32 u60;
    u8 u64;
    u8 pad65[3];
    f32 u68;
    f32 u6C;
    f32 u70;
    f32 u74;
  } sp;
  f32 b;
  f32 c;
  arg0[0x16] |= 4;
  b = (*((s16 *) (arg0 + 6))) * D_80096A04;
  c = (*((s16 *) (arg0 + 8))) * D_80096A08;
  sp.u50 = 0x6231;
  sp.u52 = 0x1A4D;
  sp.u56 = 0;
  sp.u57 = 0;
  sp.u58 = 0;
  sp.u59 = 0xFF;
  sp.u5A = 0;
  sp.u5D = 0xFF;
  sp.u60 = 0;
  sp.u5E = 0;
  sp.u5F = 0;
  sp.u64 = 0;
  sp.u6C = D_80096A0C;
  sp.u30 = *((s16 *) (arg0 + 0));
  sp.u34 = *((s16 *) (arg0 + 2));
  sp.u38 = *((s16 *) (arg0 + 4));
  sp.u54 = 0x12C;
  sp.u68 = 0.0f;
  sp.u70 = D_80096A10;
  sp.u74 = D_80096A14;
  sp.u5C = (func_150ADA20() % 56U) + 0xC8;
  sp.u3C = b;
  sp.u3C = D_80096A18 * sp.u3C;
  sp.u44 = D_80096A1C * b;
 sp.u40 = D_80096A20 * c; sp.u48 = D_80096A24 * c; sp.u4C = D_80096A28 * c; func_15149AC0(&sp.u30, 0xA, 1, (u8) (((*((s32 *) (arg0 + 0x18))) != 0) ? (2) : (1)), 0xFF, 1); return 1;
}
