void func_10010630(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4)
{
  u16 new_var;
  if ((arg2 && arg2) && arg2)
  {
  }
  if (arg1->interaction_state != 0)
  {
    if (arg1->camera != 0)
    {
      new_var = arg0;
      func_10010F30(new_var, arg2, 0x40, 0, ((((u32) arg1->unk184) >> 3) & 0x30) * 2);
    }
    else
    {
      func_1000FA64(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, (s32) func_1000EE70, arg1, arg1->unique_id, 0, 0);
    }
  }
}
