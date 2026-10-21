#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 (*D_8008B418[])(u8 *);
extern s32 (*D_8008B41C[])(u8 *);
u8 func_1514401C(u8, u8 *, u8 *, u8);
void func_1515C050(u8 *arg0) {
    s32 pad; // fakematch: frame pad puts the flag spill at 0x23
    u8 flag;

    flag = 0;
    if (arg0[0x11] & 1) {
        *(s16 *)(arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x14) < 0) {
            flag = 1;
        }
    }
    if (flag == 0) {
        if (((s8 *)arg0)[0x38] != -1) {
            if (D_8008B418[((s8 *)arg0)[0x38]](arg0) == 0) {
                flag = 1;
            }
        }
        if (*(s32 *)(arg0 + 0x1C) != 0) {
            flag = func_1514401C(arg0[0x10], arg0 + 0x1C, arg0 + 0x18, arg0[0x12]);
        }
    }
    if (flag != 0) {
        if (((s8 *)arg0)[0x39] != -1) {
            if (D_8008B41C[((s8 *)arg0)[0x39]](arg0) != 0) {
                func_1516972C((struct102 *)arg0);
            }
        } else {
            func_1516972C((struct102 *)arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_189860/func_1515C160.s")

s32 memcpy(u8 *, u8 **, s32);

u8 *func_1515C3C0(u8 **arg0, s32 arg1, u8 arg2, s32 arg3)
{
  u8 *temp_v0;
  u8 *sp2C;
  if ((*arg0) == 0)
  {
    return 0;
  }
  temp_v0 = func_15167A68(0x32, arg3, arg1 + 0x50, 1, (u8) ((s32) arg2), 1U);
  if (temp_v0 == 0)
  {
    return 0;
  }
  sp2C = temp_v0; // fakematch: copy of the result in its own local
  memcpy(temp_v0 + 0x18, arg0, 8);
  *((f32 *) (((u8 *) sp2C) + 0x20)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x14)));
  *((f32 *) (((u8 *) sp2C) + 0x24)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x18)));
  *((f32 *) (((u8 *) sp2C) + 0x28)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x1C)));
  *((f32 *) (((u8 *) sp2C) + 0x2C)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x14)));
  *((f32 *) (((u8 *) sp2C) + 0x30)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x18)));
  *((f32 *) (((u8 *) sp2C) + 0x34)) = (f32) (*((f32 *) (((u8 *) (*arg0)) + 0x1C)));
  *((s32 *) (((u8 *) sp2C) + 0x44)) = 0;
  *((s32 *) (((u8 *) sp2C) + 0x48)) = -1;
  *((s32 *) (((u8 *) sp2C) + 0x10)) = 1;
  *((s32 *) (((u8 *) sp2C) + 0x14)) = 0;
  *((f32 *) (((u8 *) sp2C) + 0x38)) = 0.0f;
  *((f32 *) (((u8 *) sp2C) + 0x3C)) = 0.0f;
  *((f32 *) (((u8 *) sp2C) + 0x40)) = 0.0f;
  return sp2C;
}

void func_1515C4C0(struct102 *arg0) {
    func_1514EDF0(arg0, ((s32 *)arg0)[0x18 / 4]);
    func_15169804(arg0);
}

void func_1515C4EC(struct102 *arg0) {
    func_1514EDF0(arg0, ((s32 *)arg0)[0x18 / 4]);
    func_15169824(arg0);
}

typedef struct { f32 x, y, z; } V3C518;
void func_1515C518(u8 *arg0) {
    s32 flag;
    u8 *o;
    V3C518 *cur;
    V3C518 *prev;
    V3C518 *d;

    flag = 0;
    if (arg0[0x1D] & 1) {
        *(s16 *)(arg0 + 0x1E) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x1E) < 0) {
            flag = 1;
        }
    }
    o = *(u8 **)(arg0 + 0x18);
    if (*(s32 *)o == 0 || arg0[0x1C] != o[0x3B]) {
        flag = 1;
    }
    if (flag == 0) {
        cur = (V3C518 *)(arg0 + 0x20);
        prev = (V3C518 *)(arg0 + 0x2C);
        d = (V3C518 *)(arg0 + 0x38);
        *prev = *cur;
        cur->x = ((V3C518 *)(*(u8 **)(arg0 + 0x18) + 0x14))->x;
        cur->y = ((V3C518 *)(*(u8 **)(arg0 + 0x18) + 0x14))->y;
        cur->z = ((V3C518 *)(*(u8 **)(arg0 + 0x18) + 0x14))->z;
        d->x = (prev->x - cur->x) * D_800BEDC8;
        d->y = (prev->y - cur->y) * D_800BEDC8;
        d->z = (prev->z - cur->z) * D_800BEDC8;
    }
    if (flag != 0) {
        func_1516972C((struct102 *)arg0);
    }
}

void func_1515C628(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x18), (s32)(arg0 + 0x1C), (s32)arg0);
}

s32 func_1515C668(u8 *arg0, u8 **arg1)
{
  struct_eu_link *sp1C;
  struct_eu_attached *new_var;
  do
  {
    if (arg0 == 0)
    {
      dummy_label_135635:
      ;

      ;
      goto block_4;
    }
    if (func_1514F250(*((struct_eu_link **) (((u8 *) arg0) + 0x2F4)), 0x16, &sp1C) != 0)
    {
      new_var = sp1C->unk10;
      *arg1 = (u8 *) new_var + 0x38;
      return 1;
    }
  }
  while (0);
  block_4:
  return 0;

}

void func_1515C6C8(void) {
    s32 i;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (node = D_800DD280[i][50]; node != NULL; node = node->next) {
            *(s32 *)((u8 *)node + 0x44) = 0;
            *(s32 *)((u8 *)node + 0x48) = -1;
        }
    }
}

void func_1515C710(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 t;
    t = arg0[4];
    if (t < 0xBB && t != 0xFF) {
        *arg2 = *(s16 *)(arg0 + 0xD2);
        *arg3 = *(s16 *)(arg0 + 0xD4);
        arg1[0] = *(f32 *)(arg0 + 0x14);
        arg1[1] = *(s16 *)(arg0 + 0xD6) + *(f32 *)(arg0 + 0x18);
        arg1[2] = *(f32 *)(arg0 + 0x1C);
    } else {
        *arg2 = 1.0f;
        *arg3 = 1.0f;
        arg1[0] = *(f32 *)(arg0 + 0x14);
        arg1[1] = *(f32 *)(arg0 + 0x18);
        arg1[2] = *(f32 *)(arg0 + 0x1C);
    }
}

void func_1515C7B4(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 t;
    t = arg0[4];
    if (t < 0xBB && t != 0xFF) {
        *arg2 = *(s16 *)(arg0 + 0xE4);
        *arg3 = *(s16 *)(arg0 + 0xE6);
        arg1[0] = *(f32 *)(arg0 + 0x14);
        arg1[1] = *(s16 *)(arg0 + 0xE8) + *(f32 *)(arg0 + 0x18);
        arg1[2] = *(f32 *)(arg0 + 0x1C);
    } else {
        *arg2 = 1.0f;
        *arg3 = 1.0f;
        arg1[0] = *(f32 *)(arg0 + 0x14);
        arg1[1] = *(f32 *)(arg0 + 0x18);
        arg1[2] = *(f32 *)(arg0 + 0x1C);
    }
}
