#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15192E90(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    if (arg0 == NULL) {
        return;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_151491F4(0x23, -1, 0x14, 1, 0x10, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C06A0/func_15192F14.s")

struct260 *func_151932B8(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[3];
        f32 unk8;
    } tmp;

    if (arg0 == NULL) {
        return NULL;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_151491F4(arg1, -1, 0x18, 1, 0x16, 0xC, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C06A0/func_15193360.s")

void func_151937A4(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied lw ra
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)(arg1 + 0);
        if (temp_v1 == *(s32 *)(temp_v0 + 0) || *(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4)) {
            func_1516972C(arg0);
        }
    }
}

void func_15193850(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 new_var;
  u8 *v = arg0 + 0x28;
  if (arg2 == 0x2D)
  {
    if (arg1[0] == (*((s32 *) v)))
    {
      *((s32 *) v) = arg1[1];
      v[4] = ((u8 *) arg1)[9];
    }
    else
    {
      if (arg1[1] == (*((s32 *) v)))
      {
        *((s32 *) v) = arg1[0];
        v[4] = ((u8 *) arg1)[8];
 } dummy_label_982087: ; // fakematch: unused label
      ;
    }
  }
  else
    if (arg2 == 0)
  {
    new_var = arg1[0]; // fakematch: new_var pins the load order
    if (((*((s32 *) v)) == new_var) || ((v[4] ^ 0) == ((u8 *) arg1)[4])) // fakematch: ^ 0 operand order
    {
      func_1516972C(arg0);
    }
  }
}
