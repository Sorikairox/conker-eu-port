void func_151CD444(u8 *arg0);
s32 func_151CA398(u8 *, s32, s32, s32, s32);
s32 func_151CA484(u8 *);
s32 func_151CA4E8(u8 *, s32, s32, s32, s32);
s32 func_151CAC50(u8 *, s32);
s32 func_151CB128(u8 *, s32);
s32 func_151CB2D8(u8 *, s32);
s32 func_151CBBAC(u8 *, s32, s32, s32, s32);
s32 func_151CCAD4(u8 *, s32, s32, s32, s32, s32);
s32 func_151CCDF0(u8 *, s32, s32, s32, s32, s32);
s32 func_151CD2CC(u8 *, s32, s32, s32);
extern u8 D_800CC3C8[];

void func_151CA150(u8 *arg0, s32 arg1)
{
  s32 var_a0;
  u8 temp_v0;
  u8 temp_v1;
  s32 new_var;
  u8 new_var2;
  func_151CA484(arg0);
  new_var2 = *((u8 *) (((u8 *) (*((u8 **) (((u8 *) arg0) + 0x3D0)))) + 0x65));
  var_a0 = arg1;
  temp_v0 = new_var2;
  if ((temp_v0 != 0) && (((temp_v1 = D_800CC3C8[temp_v0 * 0x32C], temp_v1 == 0x23)) || (D_800CC3C8[temp_v0 * 0x32C] == 0x8A)))
  {
    var_a0 = 0x1B;
  }
  new_var = var_a0;
  switch (new_var)
  {
    case 0x23:
      func_151CA4E8(arg0, 1, 1, -1, 0xFF);
      func_151CAC50(arg0, 0);
      return;

    case 0x1F:

    case 0x29:
      func_151CA4E8(arg0, 2, 1, -1, 0xFF);
      func_151CB2D8(arg0, 0);
      if (1)
    {
    }
      return;

    case 0xC:

    case 0x16:
      func_151CB2D8(arg0, 0);
      func_151CD444(arg0);
      return;

    case 0x1B:
      if (D_800BE9F0 == 0x27)
    {
      func_151CA398(arg0, 1, -1, 0xFF, 1);
      return;
    }
      if (D_80082FA0 == 0)
    {
      func_151CCAD4(arg0, 0xFF, 0, 0, 1, 0xFF);
      func_151CCDF0(arg0, 0xFF, 0, 0, 1, 0xFF);
    }
    else
    {
      func_151CD2CC(arg0, 0xFF, 0, 0);
    }
      func_151CA4E8(arg0, 3, 1, -1, 0xFF);
      func_151CBBAC(arg0, 1, 1, -1, 0xFF);
      return;

    case 0x24:
      func_151CA4E8(arg0, 0, 1, -1, 0xFF);
      func_151CAC50(arg0, 0);
      return;

    case 0x12:

    case 0x18:

    case 0x38:

    case 0x3B:
      break;

    case 9:

    default:
      func_151CB128(arg0, 0);
      break;

  }

}
