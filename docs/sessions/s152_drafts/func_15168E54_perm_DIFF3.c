void func_15168E54(struct_eu_gfxcmd *arg0, s32 arg1)
{
  s32 i = 0;
  struct_eu_gfxcmd *gfx = arg0;
  s32 cmd = gfx->cmd;
  int new_var;
  s8 new_var2;
  new_var2 = gfx->cmd;
  while (cmd != (-0x21))
  {
    new_var = (((((((0x24 & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF;
    cmd = new_var2;
    gfx = &arg0[i];
    cmd = gfx->cmd;
    if ((cmd == 1) || ((cmd == (-new_var)) && (gfx->b3 == 0xE)))
    {
      func_15168E34(&gfx->w1, arg1);
    }
    i++;
    gfx = &arg0[i];
    cmd = gfx->cmd;
  }

}
