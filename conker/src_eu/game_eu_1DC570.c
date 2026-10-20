#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_15045AF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
void func_151AC3F0(struct17 *, s32 *, s32, u8, s32);
void func_10010FFC(s32, s32, s32, s32, s32, u8 *);

typedef struct {
    s32 u24;
    s32 u28;
    u8 u2C;
    u8 *u30;
    s8 u34;
    f32 u38;
    f32 u3C;
    f32 u40;
    f32 u44;
    f32 u48;
    s16 u4C;
    s8 u4E;
    s8 u4F;
    s8 u50;
    s8 u51;
} SpawnAED60;
s32 func_151AED60(u8 *arg0, f32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    s32 pad;
    SpawnAED60 sp;
    s16 *p2;

    if (arg0 == NULL) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x11);
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = arg0[0x3B];
    sp.u34 = 1;
    sp.u4E = 2;
    sp.u30 = arg0;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    if (arg0) {} // fakematch: with p2 below, puts arg2 in v0
    sp.u40 = 0.0f;
    sp.u44 = 15.400001f;
    sp.u48 = arg1;
    p2 = &arg2; // fakematch: address-taken arg2 (loaded into v0 from its home slot)
    if (*p2 != 0) {
        sp.u4C = *p2;
        sp.u4E = 6;
    } else {
        sp.u4C = 0x12C;
    }
    sp.u4F = 6;
    sp.u50 = -1;
    sp.u51 = 5;
    return func_1513418C(&sp, 0, arg3, arg4);
}

void func_151AF064(); // K&R: the ref passes the flag unmasked (definition is K&R too)
void func_151AEF34(u8 *, f32, f32, f32, u8, u8);

void func_151AEE40(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 v[3];
    f32 r;
    s32 a;
    s32 b;

    v[0] = arg0;
    v[1] = arg1;
    v[2] = arg2;
    r = func_150ADA68();
    if (!(r < 0.15f)) {
        if (r < 0.25f) {
            a = (func_150ADA68() > 0.0f) ? 1 : 0;
            func_151AF064(v, a, arg6[0xC]);
        } else {
            b = (func_150ADA68() > 0.80500007f) ? 1 : 0;
            func_151AEF34((u8 *)v, arg3, arg4, arg5, b, arg6[0xC]);
        }
    }
}

void func_151AEF34(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    s32 pad; // fakematch
    f32 v[3];

    v[0] = -arg1 * 0.10300001f;
    v[1] = -arg2 * 0.10300001f;
    v[2] = -arg3 * 0.10300001f;
    func_151D9014(arg0, v, 0, (func_150ADA68() * 0.60200006f) + -1.0450001f, ((u32)func_150ADA20() % 31) + 0x3C, ((u32)func_150ADA20() % 101) + 0x9B, (func_150ADA68() * 219.0f) + 77.0f, arg4, 1.0f, 1.0f, 0, 0, 1, 0, arg5, 1);
}

s32 func_151DA6F8(s32, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151AF064(arg0, arg1, arg2)
    s32 arg0;
    u8 arg1;
    u8 arg2;
{
  f32 sp88[4];
  u8 sp87;
  u8 sp86;
  f32 temp_f12;
  f32 sp7C;
  f32 sp78;
  f32 sp74;
  f32 sp70;
  f32 temp_f2;
  f32 sp68;
  s32 sp64;
  s32 sp60;
  f32 sp5C;
  sp87 = func_150ADA20();
  sp86 = ((func_150ADA20() & 0x7F) & 0xFFFF) - 0x3F;
  sp7C = func_151423D8(sp87);
  sp78 = func_151423D8(sp87 - 0x40);
  sp74 = func_151423D8(sp86);
  sp70 = func_151423D8(sp86 - 0x40);
  temp_f2 = ((func_150ADA68() * 80.0f) + 20.0f) * 0.1f;
  temp_f12 = temp_f2 * sp74;
  sp88[0] = temp_f12 * sp78;
  sp88[1] = (-temp_f2) * sp70;
  sp88[2] = temp_f12 * sp7C;
 dummy_label_888456: ; // fakematch: permuter label (splits the basic block before the rand() calls)
  sp5C = func_150ADA68();
  sp60 = func_150ADA20();
  sp64 = func_150ADA20();
  sp68 = func_150ADA68();
  func_151DA6F8(arg0, sp88, (sp5C * 0.40600002f) + 0.21000001f, (s16) ((((u32) sp60) % 41U) + 0x3C), (((u32) sp64) % 101U) + 0x9B, (sp68 * 4.0f) + 3.1000001f, (func_150ADA20() % 5U) + 3, (s32) arg1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, (s32) arg2, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC570/func_151AECA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC570/func_151AF820.s")

s32 func_151AF938(void *, f32, f32, f32, u8);

void func_151AF8E8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6)
{
  f32 new_var[2];
  f32 sp24;
  sp24 = arg0;
  new_var[0] = arg1;
  new_var[1] = arg2;
  func_151AF938(&sp24, arg3, arg4, arg5, (s32) (*((u8 *) (((u8 *) arg6) + 0xC))));
}

s32 func_151AF938(void *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4) {
    s32 pad; // fakematch
    f32 v[3];
    u8 flag;
    s32 pad2; // fakematch
    s32 r2;
    s32 r1;
    f32 rf;

    v[0] = -arg1 * 0.13000001f;
    v[1] = -arg2 * 0.13000001f;
    v[2] = -arg3 * 0.13000001f;
    if (func_150ADA20() & 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    rf = func_150ADA68();
    r1 = func_150ADA20();
    r2 = func_150ADA20();
    return func_151D9014(arg0, v, 0, (rf * 0.126f) + -0.702f, (r1 & 0xF) + 0xA, ((u32)r2 % 45) + 0x89, (func_150ADA68() * 202.0f) + 142.0f, flag, 1.7f, 1.7f, 0, 0, 1, 0, arg4, 1);
}
