typedef struct { f32 x, y, z; } V3_151DD390;
typedef struct {
    s32 a;
    s32 b;
    V3_151DD390 pos;
    s16 x14;
    s16 x16;
    s16 x18;
    s16 x1A;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    s16 x2C;
    s16 x2E;
    f32 x30;
    f32 x34;
    f32 x38;
} Sp_151DD390;
extern u8 D_800AB930[];
extern u8 D_800AB934[];
extern f32 D_800AB938;
extern f32 D_800AB93C;
extern f32 D_800AB940;
extern f32 D_800AB944;

void func_151DD390(V3_151DD390 *arg0, u8 arg1, s32 arg2)
{
  Sp_151DD390 s;
  f32 sc = D_800AB938;
 dummy_label_356333: ;
  s.a = 12;
  s.b = 5;
  s.pos = *arg0;
  s.x14 = 0;
  s.x16 = 0xFF;
  s.x18 = -0x40;
  s.x1A = 0x31;
  s.x2C = 0x19;
  s.x2E = 0x14;
  s.x30 = sc;
  s.x34 = sc;
  s.x1C = 3.0f;
  s.x20 = 9.0f;
  s.x24 = D_800AB93C;
  s.x28 = D_800AB940;
  s.x38 = D_800AB944;
  func_15152700(&s, D_800AB930, D_800AB934, 1, 26.0f, 0, arg1, arg2);
}
