#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15046F70(f32 *, s32, f32, f32 *);
s32 func_1504715C(f32 *, struct127 *);
#ifdef NON_MATCHING
void func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#else
s32 func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#endif
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
      func_1514CBE8(sp6C[0], sp6C[1], sp6C[2], 251.0f, 0, 0xFF, (random_int() & 0xF) + 0x23, 0x17, 0, 0.0f, 0, arg1);
      func_1514CBE8(sp6C[0], sp6C[1], sp6C[2], 290.0f, 0, 0xFF, (random_int() % 21U) + 0x1E, 0x18, 0, 0.0f, 0, arg1);
    }
  }
}

void func_15143794(s16, s16, f32, void *);
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_150CE204(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
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
    sp.u3E = (random_int() % 41U) + 0x32;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (random_int() % 101U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (random_float() * 401.0f) + 404.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    func_15143794(arg8, (s16) ((random_int() % 20U) - 0x13), ((random_float() * 150.0f) + 150.0f) * 0.1f, sp.u7C);
    sp.u8C = 0xE05;
    sp.u88 = 0.0f;
    if (random_int() & 1) {
        sp.u8C |= 0x40;
    }
    if (random_int() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 0xA;
    sp.u97 = -1;
    sp.u52 = 0x1E;
    sp.u54 = 8;
    sp.u56 = 0x46;
    sp.u58 = 1.0196f;
    scale = 0.95091f;
    obj = func_151308E4(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

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
    func_15143794(arg8, (s16) (((u32) random_int() % 41U) - 0x3D), ((random_float() * 101.0f) + 150.0f) * 0.1f, &sp.u5C);
    sp.u68 = ((random_float() * 260.0f) + -130.0f) * 0.1f;
    sp.u70 = ((random_float() * 260.0f) + -130.0f) * 0.1f;
    sp.u7C = (random_int() % 21U) + 0x32;
    sp.u74 = ((random_float() * 311.0f) + -1217.0f) * 0.001f;
    sp.u28[3] = ((random_float() * 302.0f) + 52.0f) * 0.001f;
    sp.u28[2] = sp.u28[3];
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = (random_int() % 76U) + 0xB4;
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
