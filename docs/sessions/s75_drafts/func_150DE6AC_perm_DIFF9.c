s32 func_150DE6AC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5)
{
  u8 *sp8C;
  struct 
  {
    s32 u50;
    s32 u54;
    u8 pad58[0x4];
    f32 u5C;
    s32 u60;
    s16 u64;
    s8 u66;
    u8 pad67[0x1];
    s32 u68;
    s32 u6C;
    u8 u70;
    u8 u71;
    s8 u72;
    s8 u73;
    s8 u74;
    u8 u75;
    u8 pad76[0x2];
    s32 u78;
    u8 pad7C[0xC];
    s32 u88;
  } sp;
  sp8C = *((u8 **) (((u8 *) arg0) + 0x98));
  sp.u88 = *((s32 *) (((u8 *) arg0) + 0x94));
  sp.u5C = (func_150ADA68() * 10.0f) + 10.0f;
  *((s8 *) (((u8 *) sp8C) + 0x20)) = 4;
  switch (func_150ADA20() & 1)
  {
    case 0:
      sp.u66 = 0x1B;
      break;

    case 1:
      sp.u66 = 0x1C;
      break;

  }

  sp.u68 = 0;
  sp.u6C = 0;
  sp.u60 = 0x11;
  sp.u64 = 0x64;
  sp.u70 = 0xFF;
  sp.u71 = 0xFF;
  sp.u72 = 0;
  sp.u73 = 0;
  sp.u74 = 0;
  sp.u75 = 0xAA;
  sp.u78 = 0x30002;
  sp.u50 = func_150ADA20();
  sp.u54 = func_150ADA20();
  func_1513C73C((s32) (&sp.u60), 5U, 0U, arg5, ((f32 *) (sp.u88 + ((*((s8 *) (arg0 + 0x2D))) * 0x14)))[0], arg4, ((f32 *) (sp.u88 + ((*((s8 *) (arg0 + 0x2D))) * 0x14)))[2], sp.u5C, sp.u5C, (u8) (sp.u50 & 0xFF), (u8) ((func_150ADA20() & 1) + (sp.u54 & 1)), 0, (u8) ((s32) (*((u8 *) (((u8 *) arg0) + 0xC)))), (s32) ((*((u8 *) (((u8 *) arg0) + 1))) & 0xFFu));
  return 1;
}
