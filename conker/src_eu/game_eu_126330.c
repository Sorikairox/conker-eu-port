#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_150F8DFC
void func_150F8EAC(u8 *arg0);

typedef struct { s32 x, y, z; } V3i;
s32 func_151530A8(s32 *, s32, s32);

void func_150F8B20(s32 arg0, u8 *arg1, s32 arg2) {

    f32 pos[3];
    Header header;
    Header2 header2;
    struct {
        s32 u3C;
        s32 u40;
        s32 u44;
        u8 pad48[0x8];
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s32 u70;
        s32 u74;
        s16 u78;
        s16 u7A;
        s16 u7C;
        s8 u7E;
        s8 u7F;
        s8 u80;
        u8 u81;
        u8 u82;
        u8 u83;
        u8 u84;
        s8 u85;
        s8 u86;
        s8 u87;
        s8 u88;
        u8 u89;
        u8 u8A;
        u8 u8B;
        u8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 u91;
        s8 u92;
        s8 u93;
        s8 u94;
        u8 pad95[0x3];
        s32 u98;
        s32 u9C;
        s16 uA0;
        s16 uA2;
        s16 uA4;
        s8 uA6;
        u8 padA7[0x1];
        f32 uA8;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
    } sp;

    pos[0] = (*(f32 *)((u8 *)arg1 + 0x14));
    pos[1] = (*(f32 *)((u8 *)arg1 + 0x18)) + 50.0f;
    pos[2] = (*(f32 *)((u8 *)arg1 + 0x1C));
    if ((arg1 && arg1) && arg1) {
    } // fakematch: scheduling barrier (pos stores before header stores)
    header.unk0 = 3;
    if ((arg1 && arg1) && arg1) {
    } // fakematch
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 9U) + 5;
    header.unk4 = 0;
    header2.unk0 = pos[0];
    header2.unk4 = pos[1];
    header2.unk8 = pos[2];
    func_151602C0(&header, &header2, (func_150ADA20() % 31U) + 0x5A, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
    sp.u3C = 8;
    sp.u40 = 0xC;
    *(V3i *) &sp.u44 = *(V3i *) pos;
    sp.u50 = 3.07f;
    sp.u54 = 6.2f;
    sp.u58 = -0.96900004f;
    sp.u5C = 0.71800005f;
    sp.u60 = 15.0f;
    sp.u64 = 30.0f;
    sp.u68 = 0;
    sp.u6A = 0xFF;
    sp.u6C = -0x40;
    sp.u6E = 0x50;
    sp.u70 = 3;
    sp.u74 = 1;
    sp.u78 = 0x14;
    sp.u7A = 0xF;
    sp.u7C = 1;
    sp.u7E = 4;
    sp.u7F = 2;
    sp.u80 = 3;
    sp.u81 = 0xFF;
    sp.u82 = 0xFF;
    sp.u83 = 0xFF;
    sp.u84 = 0xFF;
    sp.u85 = 0;
    sp.u86 = 0;
    sp.u87 = 0;
    sp.u88 = 0;
    sp.u89 = 0xFF;
    sp.u8A = 0xFF;
    sp.u8B = 0xFF;
    sp.u8C = 0xFF;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u91 = 0xFF;
    sp.u92 = 0;
    sp.u93 = 3;
    sp.u94 = 0x24;
    sp.u98 = 0x200005;
    sp.u9C = 0x60600;
    sp.uA0 = 8;
    sp.uA2 = 0x1F;
    sp.uA4 = 1;
    sp.uA6 = 0;
    sp.uA8 = 1.0f;
    sp.uAC = -1;
    sp.uAD = 0;
    sp.uAE = -1;
    sp.uAF = -1;
    func_151530A8(&sp.u3C, 0xFF, 1);
}

void func_150F8DCC(s32 arg0, s32 arg1) {
    s32 tmp[2];
    tmp[0] = arg1;
    func_151494E0(tmp, 0x3F);
}

void func_150F8DFC(struct102 *arg0, u8 *arg1, u8 arg2)
{
  u8 *w = (u8 *) arg0;
  u8 *v = w + 0x28;
  u8 i;
  if (arg2 == 0x42)
  {
    s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
    if (arg1[4] == v[4])
    {
      unsigned int blk_t; // fakematch: unsigned index temp (permuter)
      for (i = 0; i < 7; i++)
      {
        blk_t = i;
        (*((u8 **) ((v + 0xC) + (blk_t * 4))))[0x6E] = 1;
      }

      (*((u8 **) (v + 0x28)))[0x6E] = 0;
      v[8] = 7;
    }
  }
  else
    if ((arg2 ^ 0) == 0x3F) // fakematch: ^ 0 (permuter)
  {
    if ((*((s32 *) arg1)) == (*((s32 *) (w + 0x28))))
    {
      func_150F8EAC(arg0);
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F8EAC.s")

extern u8 D_800A2010[][2];

void func_150F9CA0(u8 arg0) {
    struct {
        s32 unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = 0;
    tmp.unk4 = D_800A2010[arg0][0];
    func_151494E0(&tmp, 0x42);
    tmp.unk4 = D_800A2010[arg0][1];
    func_151494E0(&tmp, 0x42);
}

void func_150F9D08(s32 arg0) {
}

void func_150F9D14(struct260 *arg0) {
    func_150F9D08(arg0);
    func_1514933C(arg0);
}

void func_150F9D40(struct260 *arg0) {
    func_150F9D08(arg0);
    func_15149368(arg0);
}

s32 func_151030B8(u8 *, u8, f32 *, f32 *, f32 *, s32, s32, f32, s32 *, s32, s32, s32, s32, s32);
s32 func_15145EA4(f32 **, s32 **, s32, s32);
extern u8 D_80088EF0;
extern f32 D_800A2018[];
extern f32 D_800A2024[];

void func_150F9D6C(u8 *arg0, u8 arg1, s32 arg2)
{
  s32 sp64[3];
  f32 sp58[3];
  f32 *sp54;
  s32 *sp50;
  s32 m;
  if (*(s32 *)(arg0 + 0x1D4) == 0)
  {
    return;
  }
  sp54 = D_800A2018;
  sp50 = sp64;
  m = *(s32 *)(arg0 + 0x1D4) + (D_80088EF0 << 6);
  func_15145EA4((0, &sp54), &sp50, (0, m), 1); // fakematch: permuter comma operands fix the 0x48/0x4C spill slot
  sp58[1] = (func_150ADA68() * 1) + 2.0f; // fakematch: int * 1 keeps the result scheduling
  sp58[0] = (func_150ADA68() * 14.0f) + 28.0f;
  func_151030B8(arg0, D_80088EF0, D_800A2018, D_800A2024, sp58, (func_150ADA20() % 3U) + 4, (func_150ADA20() % 156U) + 0x64, (func_150ADA68() * 300.0f) + 400.0f, sp64, 0xFF, 0, -1, arg1, arg2);
}

u8 *func_150FF808(u8 *);
s32 func_150FF9F4(s32 *, s32 *, u8, s32);
s32 func_150FFC60(s32 *, s32 *, s32 *, s32 *, s32 *, u8 *, u8 *);
s32 func_151D44C4(s32 *, u8, s32);
s32 func_151D49B8(s32 *, s32 *, s32, u8 *, f32, s32, s32);

void func_150F9ED0(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad[15]; // fakematch: frame is 0xA8, pad first keeps the vectors at 0x30-0x60
    s32 sp60[3];
    s32 sp54[3];
    s32 sp48[3];
    s32 sp3C[3];
    s32 sp30[3];
    u8 *temp_v0;
    u8 *sp2C;

    temp_v0 = func_150FF808(arg0);
    if (temp_v0 != NULL) {
        sp2C = temp_v0;
        if (func_150FFC60(sp60, sp54, sp48, sp3C, sp30, arg0, temp_v0) != 0) {
            func_151D44C4(sp54, arg1, arg2);
            func_151D49B8(sp48, sp3C, (*(u8 *)(sp2C + 2) << 6) + *(s32 *)(arg0 + 0x1D4), arg0, 1.0f, arg1, arg2);
            func_150FF9F4(sp54, sp60, arg1, arg2);
        }
    }
}
