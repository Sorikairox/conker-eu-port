#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CF650.s")

void func_150CF994(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || v[4] == arg1[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        }
    }
}

void func_151CFE48(struct127 *, f32, s32);

void func_150CFA40(s32 arg0) {
    func_151CFE48(D_800CC2D0, D_800CC2D0->y_position + 300.0f, 0xC61C4000);
}

extern s32 D_80088C30;
extern s32 D_80088C34;
extern s32 D_80088C38;
void func_150CFA88(s32 arg0) {
    s32 temp_v1;
    D_80088C30 += D_800BE9E4 * 0x1A;
    temp_v1 = D_800BE9E4 * 0x1C;
    D_80088C34 -= temp_v1;
    D_80088C38 -= temp_v1;
}

extern s32 D_80088C30;
extern s32 D_80088C34;
extern s32 D_80088C38;
extern s32 D_80088C3C;

Gfx *func_150CFAF8(Gfx *gdl) {
    gDPSetTileSize(gdl++, 0, D_80088C30 >> 7, D_80088C34 >> 7, 0x47E, 0x47E);
    gDPSetTileSize(gdl++, 1, D_80088C38 >> 7, D_80088C3C >> 7, 0x47E, 0x47E);
    return gdl;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CFB90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CFD10.s")

void func_150D00FC(u8 *arg0, f32 *arg1, u8 arg2) {
    u8 *temp_v0 = arg0 + 0x70;
    if (arg2 == 0x52) {
        temp_v0[0] |= 1;
        *(f32 *)(temp_v0 + 4) = 0.0f;
        *(f32 *)(temp_v0 + 8) = *(f32 *)(arg0 + 0x10);
        *(f32 *)(temp_v0 + 0xC) = *arg1 - *(f32 *)(arg0 + 0x10);
    }
}

void func_150D0148(f32 arg0) {
    f32 sp1C = arg0;
    func_15155C9C(&sp1C, 0x52);
}

s32 func_150D0170(u8 *arg0) {
    f32 *v = (f32 *)(arg0 + 0x70);

    *(f32 *)(arg0 + 0x10) += v[0] * D_800BE9A4;
    *(f32 *)(arg0 + 0x14) += v[1] * D_800BE9A4 + 0.5f * v[2] * D_800BE9A4 * D_800BE9A4;
    v[1] += v[2] * D_800BE9A4;
    if (v[3] < *(f32 *)(arg0 + 0x14)) {
        *(f32 *)(arg0 + 0x14) = v[3];
        v[0] *= 0.3f;
        v[1] = fabsf(v[1]) * -0.15f;
    }
    return 1;
}

u8 *func_150D0230(u8 *arg0) {
    while ((*arg0 != 0xBD) && (*arg0 != 0)) {
        arg0++;
    }
    return arg0;
}

u8 *func_150D026C(u8 *arg0) {
    while (*arg0 != 0) {
        arg0++;
    }
    return arg0;
}

s32 func_150D0294(u8 *arg0, u8 **arg1) {
    u8 *temp_v0 = func_150D0230(arg0);
    *arg1 = temp_v0;
    return temp_v0 - arg0;
}

s32 func_150D02C8(u8 *arg0)
{
  u8 *end;
  s32 best = 0;
  u8 *next;
  end = func_150D026C(arg0);
  while (arg0 < end) {
    s32 v;
    v = func_150D0294(arg0, &next);
    if (best < v) {
      best = v;
    }
    arg0 = next + 1;
  }
  return best;
}

s32 memcpy(s32, void *, s32);
void func_150D034C(u8 *arg0)
{
  u8 *p = arg0;
  u8 *q;
  memcpy(*((s32 *) ((p + ((*((u8 *) (p + 0x3D))) << 2)) + ((0, 0x40)))), *((void **) (p + 0x34)), *((u8 *) (p + 0x3C)));
  q = p + 0x28;
  p = q;
  *((*((u8 **) ((p + ((*((u8 *) (p + 0x15))) << 2)) + 0x18))) + (*((u8 *) (p + 0x14)))) = 0;
}

void func_150D03A8(u8 *arg0) {
    u8 *v = arg0 + 0x28;

    if (**(u8 **)(arg0 + 0x38) != 0) {
        *(u8 **)(v + 0xC) = *(u8 **)(v + 0x10) + 1;
        *(u8 *)(v + 0x14) = func_150D0294(*(u8 **)(v + 0xC), (u8 **)(v + 0x10));
        *(u8 *)(v + 0x15) = *(u8 *)(v + 0x15) ^ 1;
        func_150D034C(arg0);
        *(u8 *)(v + 8) = *(u8 *)(v + 8) | 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150D0420.s")

extern s32 D_80088C40[];

s32 func_150D0544(s32 arg0, u8 *arg1, s32 arg2) {
    u8 *v = arg1 + 0x28;

    if ((*(s8 *)(arg1 + 0x4C) != -1) && (((s32 (**)(u8 *))D_80088C40)[*(volatile s8 *)(arg1 + 0x4C)](arg1) == 0)) { // fakematch: volatile forces the second lb of the index, v defined first so addiu is rematerialised
        *(s16 *)(arg1 + 0xE) = -1;
        return arg0;
    }
    *(u8 *)(v + 8) &= 0xFFFE;
    return arg0;
}

extern void (*D_80088C50[])(u8 *, u8 *, u8);
void func_150D03A8(u8 *);
void func_150D05D0(u8 *arg0, u8 *arg1, u8 arg2) {
    void (*f)(u8 *, u8 *, u8);
    if (arg2 == 0x51) {
        if (arg0[0x28] == arg1[0]) {
            func_150D03A8(arg0);
        }
    } else {
        f = D_80088C50[arg0[0x4D]];
        if (f != NULL) {
            f(arg0, arg1, arg2);
        }
    }
}

u8 *func_150D0420(u8, s32, s16, s32, s32, s32, u8, s32);
s32 memcpy(s32, void *, s32);
void func_150D0644(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    s32 sfpad;
    s8 sp30[4];
    u8 *temp_v0;
    sp30[0] = 0;
    temp_v0 = func_150D0420(arg0, arg1, arg2, 8, 0, 0, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0 + 0x48)), sp30, 1);
    }
}
