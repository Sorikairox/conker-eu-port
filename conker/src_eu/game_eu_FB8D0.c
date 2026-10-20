#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15046F70(f32 *, s32, f32, f32 *);
s32 func_1504715C(f32 *, struct127 *);
s32 func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
void func_150CE0C0(u8 *arg0, u8 arg1, s32 arg2)
{
  f32 sp6C[3];
  f32 sp48[9];
  if (arg0 != 0)
  {
    func_1504715C(sp48, arg0);
    sp6C[0] = *((f32 *) (((u8 *) arg0) + 0x14));
    sp6C[1] = (*((f32 *) (((u8 *) arg0) + 0x18))) + 1000.0f;
    sp6C[2] = *((f32 *) (((u8 *) arg0) + 0x1C));
    if (func_15046F70(sp6C, 0, (*((f32 *) (((u8 *) arg0) + 0x18))) - 3000.0f, sp48) != 0)
    {
      sp6C[1] = sp48[0];
      dummy_label_506575: ; // fakematch: empty label keeps the sp6C[1] store out of the jal delay slot
      func_1514CBE8(sp6C[0], sp6C[1], sp6C[2], 251.0f, 0, 0xFF, (func_150ADA20() & 0xF) + 0x23, 0x17, 0, 0.0f, 0, arg1);
      func_1514CBE8(sp6C[0], sp6C[1], sp6C[2], 290.0f, 0, 0xFF, (func_150ADA20() % 21U) + 0x1E, 0x18, 0, 0.0f, 0, arg1);
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FB8D0/func_150CE204.s")

void func_15143794(s16, s16, f32, void *);

s32 func_150CE420(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
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
    func_15143794(arg8, (s16) (((u32) func_150ADA20() % 41U) - 0x3D), ((func_150ADA68() * 101.0f) + 150.0f) * 0.1f, &sp.u5C);
    sp.u68 = ((func_150ADA68() * 260.0f) + -130.0f) * 0.1f;
    sp.u70 = ((func_150ADA68() * 260.0f) + -130.0f) * 0.1f;
    sp.u7C = (func_150ADA20() % 21U) + 0x32;
    sp.u74 = ((func_150ADA68() * 311.0f) + -1217.0f) * 0.001f;
    sp.u28[3] = ((func_150ADA68() * 302.0f) + 52.0f) * 0.001f;
    sp.u28[2] = sp.u28[3];
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = (func_150ADA20() % 76U) + 0xB4;
    sp.u89 = 8;
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
