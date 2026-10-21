void func_1513E13C(struct210 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6)
{
  struct210 *p = arg0;
  f32 s = func_151423D8(arg6 - 0x40);
  f32 c = func_151423D8(arg6);
  struct210 *new_var;
  s32 y;
  ((Vtx *) (&p->unk40))[0].v.ob[0] = (arg1 + (arg4 * c)) - (arg5 * s);
  ((Vtx *) (&p->unk40))[0].v.ob[1] = (y = arg2);
  ((Vtx *) (&p->unk40))[0].v.ob[2] = (arg3 + (arg5 * c)) + (arg4 * s);
  new_var = p;
  ((Vtx *) (&new_var->unk40))[1].v.ob[1] = y;
 do { ((Vtx *) (&p->unk40))[1].v.ob[0] = (arg1 - (arg4 * c)) - (arg5 * s); do { ((Vtx *) (&p->unk40))[1].v.ob[2] = (arg3 + (arg5 * c)) - (arg4 * s); } while (0); } while (0);
  ((Vtx *) (&p->unk40))[2].v.ob[1] = y;
  ((Vtx *) (&p->unk40))[2].v.ob[0] = (arg1 - (arg4 * c)) + (arg5 * s);
  ((Vtx *) (&p->unk40))[3].v.ob[1] = y;
  ((Vtx *) (&p->unk40))[2].v.ob[2] = (arg3 - (arg5 * c)) - (arg4 * s);
  ((Vtx *) (&p->unk40))[3].v.ob[0] = (arg1 + (arg4 * c)) + (arg5 * s);
  ((Vtx *) (&p->unk40))[3].v.ob[2] = (arg3 - (arg5 * c)) + (arg4 * s);
}
