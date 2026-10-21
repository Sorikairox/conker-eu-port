Gfx *func_1513F4E4(Gfx *arg0, u8 arg1, u8 *arg2)
{
  s32 mode = func_15143044(arg1, 0);
  if (mode != D_800DD5EE)
  {
    if ((*arg2) == 1)
    {
      {
        Gfx *_g = (Gfx *) (arg0++);
        _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24);
        _g->words.w1 = 0;
      }
      ;
      *arg2 = 0;
    }
 do { { Gfx *_g = (Gfx *) (arg0++); _g->words.w0 = ((unsigned int) ((((unsigned int) 0xfc) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((((unsigned int) ((((unsigned int) D_800A4F88[arg1][0]) & ((0x01 << 4) - 1)) << 20)) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][2]) & ((0x01 << 5) - 1)) << 15))) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][4]) & ((0x01 << 3) - 1)) << 12))) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][6]) & ((0x01 << 3) - 1)) << 9))) | (((unsigned int) ((((unsigned int) D_800A4F88[arg1][8]) & ((0x01 << 4) - 1)) << 5)) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][10]) & ((0x01 << 5) - 1)) << 0))))) & ((0x01 << 24) - 1)) << 0)); _g->words.w1 = (unsigned int) ((((((unsigned int) ((((unsigned int) D_800A4F88[arg1][1]) & ((0x01 << 4) - 1)) << 28)) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][3]) & ((0x01 << 3) - 1)) << 15))) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][5]) & ((0x01 << 3) - 1)) << 12))) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][7]) & ((0x01 << 3) - 1)) << 9))) | (((((((unsigned int) ((((unsigned int) D_800A4F88[arg1][9]) & ((0x01 << 4) - 1)) << 24)) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][12]) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][14]) & ((0x01 << 3) - 1)) << 18))) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][11]) & ((0x01 << 3) - 1)) << 6))) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][13]) & ((0x01 << 3) - 1)) << 3))) | ((unsigned int) ((((unsigned int) D_800A4F88[arg1][15]) & ((0x01 << 3) - 1)) << 0)))); } } while (0);
    D_800DD5EE = mode;
  }
  return arg0;
}
