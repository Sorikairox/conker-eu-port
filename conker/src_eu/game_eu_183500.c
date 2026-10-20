#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct_eu_node *func_15156544(s32 arg0);


s32 func_1518C900(s32);
struct_eu_node *func_15155CF0(s32 arg0, s32 arg1)
{
  struct_eu_node *temp_v0;
  temp_v0 = func_15167A68(0x50, 0, 0xA0, 1, (u8) arg1, 1U);
  if (temp_v0 == 0)
  {
    return temp_v0;
  }
  *((s8 *) (((u8 *) temp_v0) + 0x10)) = (s8) arg0;
  *((s8 *) (((u8 *) temp_v0) + 0x11)) = 0;
  *((s32 *) (((u8 *) temp_v0) + 0x14)) = 0;
  *((f32 *) (((u8 *) temp_v0) + 0x98)) = 0.0f;
  func_1518C900(0xA6);
  return temp_v0;
}

struct_eu_node *func_15155CF0(s32, s32);

void func_15155D6C(s32 arg0, s32 arg1, f32 arg2) {
    struct_eu_node *var_v0;

    var_v0 = func_15156544(arg0);
    if (var_v0 == NULL) {
        var_v0 = func_15155CF0(arg0, 0xFF);
    }
    if (var_v0 != NULL) {
        (*(f32 *)((u8 *)var_v0 + 0x98)) = arg2;
        if (*(&D_800CC37D + (arg0 * 0x32C)) != 0) {
            (*(s16 *)((u8 *)var_v0 + 0xE)) = 0;
            (*(s8 *)((u8 *)var_v0 + 0x11)) = 0;
            return;
        }
        (*(s8 *)((u8 *)var_v0 + 0x11)) = 3;
        (*(s16 *)((u8 *)var_v0 + 0xE)) = (s16) arg1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_15155E0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_1515626C.s")

void func_1515F10C(s32);
s32 func_1518CF74(s32);
void func_15156468(struct102 *arg0)
{
  u8 *p = (u8 *) arg0;
  s32 temp_a2;
  temp_a2 = *((s32 *) (p + 0x14));
  if (temp_a2 != 0)
  {
    func_1515F10C(temp_a2);
  }
  if (((!arg0) && (!arg0)) && (!arg0)) // fakematch: dead test from the permuter
  {
  }
  func_15169804(p);
  func_1518CF74(0xA6);
}

void func_151564AC(void) {
    u8 *temp_v0 = (u8 *)func_15156544(D_800C3E78);

    if (temp_v0 != NULL) {
        if (temp_v0[0x11] == 2) {
            temp_v0[0x11] = 0;
        } else if (temp_v0[0x11] == 3) {
            temp_v0[0x11] = 2;
        }
    }
}

void func_15156500(void) {
    u8 *temp_v0 = (u8 *)func_15156544(D_800C3E78);

    if ((temp_v0 != NULL) && (temp_v0[0x11] == 3)) {
        temp_v0[0x11] = 1;
    }
}

struct_eu_node *func_15156544(s32 arg0) {
    s32 i;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (node = D_800DD280[i][80]; node != NULL; node = node->next) {
            if (arg0 == ((u8 *)node)[0x10]) {
                return node;
            }
        }
    }
    return NULL;
}

void func_15156598(u8 *arg0, struct127 **arg1, u8 arg2) {
    if (arg2 == 0) {
        s32 a;
        a = arg1[0] - D_800CC2D0;
        if ((a >= 0) && (a < 25) && (a == arg0[0x10])) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        s32 a;
        s32 b;
        a = arg1[0] - D_800CC2D0;
        b = arg1[1] - D_800CC2D0;
        if ((a >= 0) && (a < 25) && (b >= 0) && (b < 25)) {
            if (a == arg0[0x10]) { arg0[0x10] = b; }
            else if (b == arg0[0x10]) { arg0[0x10] = a; }
        }
    }
}
