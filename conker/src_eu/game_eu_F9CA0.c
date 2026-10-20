#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F9CA0/func_150CBF80.s")

s32 func_150CCB48(u8 *arg0)
{
  f32 temp_f0;
  s32 temp_v1;
  u8 *p;
  p = arg0 + 0x128;
  if ((*((s32 *) (((u8 *) arg0) + 0x58))) & 1)
  {
    temp_v1 = *((s16 *) (((u8 *) arg0) + 0x1C));
    if (temp_v1 < 0x20)
    {
      if ((temp_v1 * 8) < ((s32) (*((u8 *) (((u8 *) arg0) + 0x5C)))))
      {
        *((u8 *) (((u8 *) arg0) + 0x5C)) = (u8) (temp_v1 * 8);
      }
    }
    temp_v1 = *((s16 *) (((u8 *) arg0) + 0x1C));
    temp_f0 = temp_f0;
    if ((*((s16 *) p)) < temp_v1)
    {
      temp_f0 = (*((f32 *) (p + 4))) * D_800BE9A4;
      *((f32 *) (((u8 *) arg0) + 0x2C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x2C))) + temp_f0);
      *((f32 *) (((u8 *) arg0) + 0x30)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x30))) + temp_f0);
    }
  }
  return 1;
}

void func_15143794(s16, s16, f32, void *);
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_150CCBC8(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0xC];
        s32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x10];
    } sp;
    s32 obj;
    f32 scale;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() & 0xF) + 0x14;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 156U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (func_150ADA68() * 401.0f) + 300.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    func_15143794(arg8, (s16) ((func_150ADA20() % 21U) - 0x19), ((func_150ADA68() * 200.0f) + 350.0f) * 0.1f, sp.u7C);
    sp.u8C = 0xE05;
    sp.u88 = 0.0f;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 8;
    sp.u97 = -1;
    sp.u52 = 0xA;
    sp.u54 = 0x19;
    sp.u56 = 0x1B;
    sp.u58 = 1.04f;
    scale = 0.901f;
    obj = func_151308E4(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

s32 func_150CCDE4(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

void func_15143794(s16, s16, f32, void *);

s32 func_150CCF8C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        f32 u28[13];
        s32 u5C;
        u8 pad60[0x8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 pad91[0x1];
        s8 u92;
        u8 pad93[0x1];
        s32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        u8 padA0[0x8];
    } sp;

    sp.u28[10] = arg2;
    sp.u28[11] = arg3;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u78 = 0x29E8;
    sp.u28[4] = 0.0f;
    sp.u28[5] = 0.0f;
    sp.u28[6] = 0.0f;
    sp.u6C = 0.0f;
    sp.u28[0] = 1.0f;
    sp.u7E = 0x20;
    sp.u28[12] = arg4;
    sp.u28[1] = 0.2f;
    func_15143794(arg8, (s16) (((u32) func_150ADA20() % 44U) - 0x3F), ((func_150ADA68() * 200.0f) + 300.0f) * 0.1f, &sp.u5C);
    sp.u68 = ((func_150ADA68() * 260.0f) + -130.0f) * 0.1f;
    sp.u70 = ((func_150ADA68() * 260.0f) + -130.0f) * 0.1f;
    sp.u7C = (func_150ADA20() % 51U) + 0x32;
    sp.u74 = ((func_150ADA68() * 1500.0f) + -3500.0f) * 0.001f;
    sp.u28[3] = ((func_150ADA68() * 500.0f) + 100.0f) * 0.001f;
    sp.u28[2] = sp.u28[3];
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = (func_150ADA20() % 101U) + 0x9B;
    sp.u89 = 3;
    sp.u8A = 0;
    sp.u8B = 0;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u92 = 2;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 0x20;
    sp.u9C = 7;
    func_15132FBC(&sp, 3, 0xFF, 0, (s32) argE, 0);
    return 1;
}

s32 func_150CD1C4(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * D_800BE9A4) + (*(f32 *)(arg0 + 0x5C) * D_800BE9A4 * D_800BE9A4 * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}
