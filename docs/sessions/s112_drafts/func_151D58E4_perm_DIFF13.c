typedef struct { f32 x, y, z; } V3_58;
typedef struct { V3_58 pos; f32 a; f32 b; f32 c; } S58E4;
void func_1516547C(u8, u8, void *, u8, s32);

void func_151D58E4(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6)
{
  s32 pad;
  S58E4 s;
  s32 i;
  S58E4 *new_var2;
  S58E4 *new_var;
  new_var = new_var2;
  new_var2 = &s;
  s.pos = *((V3_58 *) arg0);
  s.a = arg1;
  s.b = arg2;
  s.c = arg3;
  for (i = 0; i < (D_80082FA0 + 1); i++)
  {
    func_1516547C(arg4, i, new_var, arg5, arg6);
  }

}
