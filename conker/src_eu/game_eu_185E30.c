#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15158F90(u8 *arg0);


s32 func_1515D9B0(void);
s32 func_1515D9F0(s32);
void *memcpy(void *, const void *, u32);

s32 func_15158620(s32 src, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    u8 *p;
    s32 i;

    p = func_15167A68(arg3 ? 0x55 : 0x37, arg6, arg4 + 0xF8, 1, arg5, 1);
    if (p == NULL) {
        return 0;
    }
    memcpy(p + 0x10, (void *)src, 0x44);
    *(s32 *)(p + 0xD8) = arg1;
    *(s32 *)(p + 0xF4) = arg2;
    p[0xDC] = 0;
    for (i = 0; i < 4; i++) {
        ((s32 *)(p + 0xE0))[i] = 0;
    }
    *(s32 *)(p + 0xF0) = 0;
    if (arg1 != 0) {
        for (i = 0; i <= D_80082FA0; i++) {
            ((s32 *)(p + 0xE0))[i] = func_1515D9F0(arg1);
        }
        *(s32 *)(p + 0xF0) = func_1515D9B0();
    }
    return (s32)p;
}

s32 func_15158620(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);

void func_15158748(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    func_15158620(arg0, 0, 0, arg1, arg2, arg3, arg4);
}

extern s32 (*D_8008B1A0[])(void);
void func_15158794(u8 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0[0x10] & 1) != 0) {
        *(s16 *)(arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x14) < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (*(s8 *)(arg0 + 0x12) != -1) && (D_8008B1A0[*(s8 *)(arg0 + 0x12)]() == 0)) {
        ret = 1;
    }
    if (ret) {
        func_1516972C(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158838.s")

s32 func_15158AFC(Mtx *arg0, u8 *arg1) {
    f32 *r;
    f32 mf[4][4];

    r = (f32 *)(arg1 + 0xF8);
    func_150A8050(mf, r[0], r[1], r[2]);
    mf[3][0] = *(f32 *)(arg1 + 0x48);
    mf[3][1] = *(f32 *)(arg1 + 0x4C);
    mf[3][2] = *(f32 *)(arg1 + 0x50);
    mf[0][0] *= r[3];
    mf[0][1] *= r[3];
    mf[0][2] *= r[3];
    mf[1][0] *= r[3];
    mf[1][1] *= r[3];
    mf[1][2] *= r[3];
    mf[2][0] *= r[3];
    mf[2][1] *= r[3];
    mf[2][2] *= r[3];
    guMtxF2L(mf, arg0);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158BF4.s")

typedef struct { f32 m[4][4]; } MtxF_s82;
extern MtxF_s82 D_8008B1B8;

s32 func_15158E90(Mtx *arg0, u8 *arg1) {
    f32 s;
    u8 *p;
    MtxF_s82 mf;

    p = arg1;
    mf = D_8008B1B8;
    s = *(f32 *)(p + 0xF8) * 0.003921569f;
    mf.m[3][0] = *(f32 *)(p + 0x48);
    mf.m[3][1] = *(f32 *)(p + 0x4C);
    mf.m[3][2] = *(f32 *)(p + 0x50);
    mf.m[0][0] *= s;
    mf.m[0][1] *= s;
    mf.m[0][2] *= s;
    mf.m[1][0] *= s;
    mf.m[1][1] *= s;
    mf.m[1][2] *= s;
    mf.m[2][0] *= s;
    mf.m[2][1] *= s;
    mf.m[2][2] *= s;
    guMtxF2L(mf.m, arg0);
    return 1;
}

void func_15158F90(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0xE0))[i]) {
            func_100043B4(((s32 *)(arg0 + 0xE0))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0xF0) != 0) {
        func_100043B4(*(s32 *)(arg0 + 0xF0), 4);
    }
}

void func_15159014(void *arg0) {
    func_15158F90(arg0);
    func_15169804(arg0);
}

void func_15159040(void *arg0) {
    func_15158F90(arg0);
    func_15169824(arg0);
}

s32 func_1515906C(u8 *arg0) {
    s32 temp_v1;
    if (*(s16 *)(arg0 + 0x14) < *(s16 *)(arg0 + 0xF8)) {
        temp_v1 = *(s32 *)(arg0 + 0xFC) * *(s16 *)(arg0 + 0x14);
        if (temp_v1 < arg0[0x3B]) {
            arg0[0x3B] = temp_v1;
        }
    }
    return 1;
}

void func_151590AC(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 a;
  if (arg2 == 0x2D) {
    a = arg1[0];
    if (a == *(s32 *)(arg0 + 0x40)) {
      *(s32 *)(arg0 + 0x40) = arg1[1];
      arg0[0x44] = ((u8 *)arg1)[9];
      return;
    }
    if (arg1[1] == *(s32 *)(arg0 + 0x40)) {
      s32 *p = (s32 *)(arg0 + 0x40); // a declaration in the arm = basic-block boundary (unfilled jr ra delay slot, s69)
      *p = a;
      arg0[0x44] = ((u8 *)arg1)[8];
    }
    return;
  }
  if (arg2 == 0) {
    a = arg1[0];
    if (a == *(s32 *)(arg0 + 0x40) || arg0[0x44] == ((u8 *)arg1)[4]) {
      *(s32 *)(arg0 + 0x40) = 0;
      arg0[0x44] = 0;
    }
  }
}

s32 func_151598E0(u8 *, u8 *, u8 *);

u8 *func_15159140(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *p;

    if (arg0 == NULL) {
        return NULL;
    }
    p = func_15167A68(0x2E, 0, arg2 + 0x58, 1, 0xFF, 1);
    if (p == NULL) {
        return NULL;
    }
    *(u8 **)(p + 0x18) = arg0;
    p[0x1C] = arg0[0x3B];
    p[0x2C] = 2;
    p[0x2D] = 2;
    p[0x2E] = 2;
    p[0x2F] = 3;
    p[0x30] = 0;
    *(f32 *)(p + 0x20) = *(f32 *)(arg0 + 0x14);
    *(f32 *)(p + 0x24) = *(f32 *)(arg0 + 0x18);
    *(f32 *)(p + 0x28) = *(f32 *)(arg0 + 0x1C);
    p[0x31] = 0;
    if (arg1 != 0) {
        p[0x31] |= 1;
    }
    *(s32 *)(p + 0x10) = 1;
    *(s32 *)(p + 0x14) = 0;
    if (func_151598E0(arg0, p + 0x1D, p) == 0) {
        func_1516979C((struct102 *)p);
        return NULL;
    }
    p[0x50] = 0;
    return p;
}

void func_15159244(void **arg0) {
    func_1514EDF0(arg0, arg0[0x18 / 4]);
    func_15169804(arg0);
}
