struct Unk15140190 {
    u8 pad0[0x2C];
    f32 w;
    f32 h;
    f32 pos[3];
    f32 rot[3];
    u8 pad4C[0x74];
    u8 blk[0x40];
    u8 *tbl[1];
};
s32 func_151D6310(void *, s16, s32, s16 **, u8 *);
s16 *func_1513EE14(struct Unk15140190 *arg0, s16 arg1)
{
  s16 *p;
  s16 *ret;
  f32 mtx[4][4];
  f32 v[4][2];
  f32 o[4][3];
  u8 flag;
  s16 *q;
  func_151D6310(arg0->tbl, arg1, 0x40, &p, &flag);
  ret = p;
  if (p != 0)
  {
    if (flag != 0)
    {
      memcpy(arg0->tbl[arg1], arg0->blk, 0x40);
      memcpy(arg0->tbl[arg1] + 0x40, arg0->blk, 0x40);
    }
  }
  else
  {
    return 0;
  }
  func_150A8050(mtx, arg0->rot[0], arg0->rot[1], arg0->rot[2]);
  mtx[3][0] = arg0->pos[0];
  mtx[3][1] = arg0->pos[1];
  mtx[3][2] = arg0->pos[2];
  v[0][0] = arg0->w;
  v[0][1] = arg0->h;
  v[1][0] = -arg0->w;
  v[1][1] = arg0->h;
  v[2][0] = -arg0->w;
  v[2][1] = -arg0->h;
  v[3][0] = arg0->w;
  v[3][1] = -arg0->h;
  func_150A7E40(mtx, v[0][0], v[0][1], 0.0f, &o[0][0], &o[0][1], &o[0][2]);
  func_150A7E40(mtx, v[1][0], v[1][1], 0.0f, &o[1][0], &o[1][1], &o[1][2]);
 do { func_150A7E40(mtx, v[2][0], v[2][1], 0.0f, &o[2][0], &o[2][1], &o[2][2]); func_150A7E40(mtx, v[3][0], v[3][1], 0.0f, &o[3][0], &o[3][1], &o[3][2]); p[0] = o[0][0]; p[1] = o[0][1]; p[2] = o[0][2]; p[3] = 0; p += 8; q = p; } while (0);
  q[0] = o[1][0];
  q[1] = o[1][1];
  q[2] = o[1][2];
  q[3] = 0;
  p = q + 8;
  q = p;
  q[0] = o[2][0];
  q[1] = o[2][1];
  q[2] = o[2][2];
  q[3] = 0;
  p = q + 8;
  q = p;
  q[0] = o[3][0];
  q[1] = o[3][1];
  q[2] = o[3][2];
  q[3] = 0;
  p = q + 8;
  return ret;
}
