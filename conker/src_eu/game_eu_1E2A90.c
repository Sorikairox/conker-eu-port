#include <ultra64.h>
#include "functions.h"
#include "variables.h"


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
} Spawn5280;
extern u8 D_800A43C6[];
s32 func_15134070(u8 *);
void func_1516962C(s32, u8 *, u8);
u8 *func_1513418C(void *, s32, u8, s32);

u8 *func_151B5280(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *ret;
    Spawn5280 sp;
    u8 flag[1];
    s32 id;

    if (arg0 == NULL) {
        return 0;
    }
    id = func_15134070(arg0);
    if (id == 0x63) {
        return 0;
    }
    if (D_800A43C6[id * 16] == 2) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x16);
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = arg0[0x3B];
    sp.u34 = 2;
    sp.u4E = 6;
    sp.u30 = arg0;
    sp.u38 = 0.0f;
    sp.u3C = -27.0f;
    sp.u40 = 16.0f;
    sp.u44 = 15.0f;
    sp.u48 = 0.448f;
    sp.u4C = func_150ADA20() % 21U + 0x28;
    sp.u4F = 8;
    sp.u50 = -1;
    sp.u51 = 7;
    if (D_800A43C6[id * 16] == 1) {
        flag[0] = 1;
    } else {
        flag[0] = 0;
    }
    ret = func_1513418C(&sp, 1, arg1, arg2);
    if (ret != NULL) {
        memcpy(ret + 0x58, flag, 1);
    }
    return ret;
}

s32 func_151B5454(f32 *, f32, f32, f32, u8, u8);
void func_151B53FC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6)
{
  f32 v[3];
  v[0] = arg0;
  v[1] = arg1;
  v[2] = arg2;
  func_151B5454(v, arg3, arg4, arg5, arg6[0x58], arg6[0xC]);
}

s32 func_151B5454(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    s32 pad; // fakematch: frame slot
    f32 v[3];

    v[0] = -arg1 * 0.20500001f;
    v[1] = -arg2 * 0.20500001f;
    v[2] = -arg3 * 0.20500001f;
    return func_151D9014(arg0, v, arg4, func_150ADA68() * 0.497f + -1.0f, func_150ADA20() % 31U + 0x14, func_150ADA20() % 101U + 0x9B, func_150ADA68() * 152.0f + 109.0f, func_150ADA20() & 1, 1.7f, 1.7f, 0, 0, 1, 0, arg5, 1);
}

u8 *func_151B5590(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: frame slot
    Spawn5280 sp;

    if (arg0 == NULL) {
        return 0;
    }
    sp.u24 = 0;
    sp.u28 = 0;
    sp.u2C = arg0[0x3B];
    sp.u34 = 2;
    sp.u30 = arg0;
    sp.u38 = 0.0f;
    sp.u3C = -27.0f;
    sp.u40 = 16.0f;
    sp.u44 = 9.8f;
    sp.u48 = 0.143f;
    sp.u4E = 2;
    sp.u4C = 0x12C;
    sp.u4F = 9;
    sp.u50 = -1;
    sp.u51 = 8;
    return func_1513418C(&sp, 0, arg1, arg2);
}

s32 func_151B56A4(f32 *, f32, f32, f32, u8);

void func_151B5654(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6)
{
  f32 new_var[2];
  f32 sp24;
  sp24 = arg0;
  new_var[0] = arg1;
  new_var[1] = arg2;
  func_151B56A4(&sp24, arg3, arg4, arg5, (s32) (*((u8 *) (((u8 *) arg6) + 0xC))));
}

s32 func_151B56A4(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4) {
    s32 pad; // fakematch: frame slot
    f32 v[3];
    u8 flag;

    v[0] = -arg1 * 0.13000001f;
    v[1] = -arg2 * 0.13000001f;
    v[2] = -arg3 * 0.13000001f;
    if (func_150ADA20() & 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    return func_151D9014(arg0, v, 0, func_150ADA68() * 0.126f + -0.702f, (func_150ADA20() & 0xF) + 0xA, func_150ADA20() % 45U + 0x89, func_150ADA68() * 202.0f + 142.0f, flag, 1.7f, 1.7f, 0, 0, 1, 0, arg4, 1);
}
