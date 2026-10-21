s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
void func_15133CD0(u8 *, u8 *);
typedef struct { u8 v[3]; } Tbl3_F490;
extern Tbl3_F490 D_8008FF60;
typedef struct { f32 x, y, z; } V3_F490;
typedef struct {
    f32 u0;
    f32 u4;
    f32 u8;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    f32 u24;
    V3_F490 u28;
    f32 u34[7];
    s32 u50;
    s16 u54;
    s16 u56;
    u8 u58;
    s32 u5C;
    u8 u60;
    u8 u61;
    u8 u62[6];
    u8 u68;
    u8 u69;
    u8 u6A;
    s32 u6C;
    u8 u70;
    s16 u72;
    s16 u74;
    s32 u78;
} Blk78_F490;

u8 *func_151BF490(f32 arg0, V3_F490 *arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8)
{
  s32 pad;
  Tbl3_F490 tbl = D_8008FF60;
  Blk78_F490 blk;
  u8 *ret;
  s32 i;
  if (arg4 >= 3)
  {
    return 0;
  }
  blk.u0 = 1.0f;
  blk.u4 = 1.0f;
  blk.uC = 0.923f;
  blk.u8 = 0.923f;
  blk.u10 = 0.0f;
  if ((arg4 && arg4) && arg4)
  {
  }
  blk.u14 = arg0;
  blk.u18 = 0.0f;
  blk.u1C = 1.0f;
  blk.u20 = 1.0f;
  blk.u24 = 1.0f;
  blk.u28 = *arg1;
  blk.u34[0] = 0.0f;
  blk.u34[1] = 0.0f;
  blk.u34[2] = 0.0f;
  blk.u34[3] = 0.0f;
  blk.u34[4] = 0.0f;
  blk.u34[5] = 0.0f;
  blk.u34[6] = 0.0f;
  blk.u50 = ((((arg5 != 0) ? (0x4000) : (0)) | 0x1D00) | 0x80000) | 0x40000;
  blk.u54 = 0x12C;
  blk.u56 = 0x26;
  blk.u58 = tbl.v[arg4];
  blk.u5C = arg6;
  blk.u60 = 0xFF;
  if (D_800BE9F0 == 7)
  {
    blk.u61 = 0x18;
  }
  else
  {
    blk.u61 = 0;
  }
  blk.u62[0] = 0;
  blk.u62[1] = 0;
  blk.u62[2] = 0;
  blk.u62[3] = 0;
  blk.u62[4] = 0;
  blk.u62[5] = 0;
  blk.u68 = 2;
  blk.u6A = 0;
  blk.u6C = 0;
  blk.u70 = 0;
  blk.u72 = 1;
  blk.u74 = 0xFF;
  ret = (u8 *) func_15132FBC(&blk, arg2, arg3, 0, arg7, arg8);
  if (ret != 0)
  {
    for (i = 0; i < 2; i++)
    {
      func_15133CD0((ret + 0x90) + (i * 0x40), ret);
    }

  }
  return ret;
}
