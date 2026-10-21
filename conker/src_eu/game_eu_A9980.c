#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_A9980/func_1507C170.s")

s32 func_15022A8C(struct127 *);
s32 func_1507C170(struct197 *, f32, struct127 *, s32);
extern u8 D_800C3A78;

void func_1507C608(s32 arg0)
{
  struct127 *var_s0;
  struct197 *temp_a0;
  s32 *new_var;
  var_s0 = D_800CC2D0; ; do { // fakematch: permuter empty statement before the loop
    if ((((var_s0->interaction_state != 0) && (!(var_s0->unk25C & 0x200))) && ((arg0 == 0) || (var_s0->unk5 == 4))) && (((D_800C3638 == 0) || (D_800C3A78 != 0)) || (func_15022A8C(var_s0) != 0)))
    {
      temp_a0 = var_s0->unk2D0;
      if ((temp_a0 != 0) && (var_s0->unk2FA != 0))
      {
        func_1507C170(temp_a0, var_s0->unk48, var_s0, arg0);
        if (&D_800D121C) // fakematch: permuter empty if
        {
        }
      }
    }
    if (1) // fakematch: permuter empty if
    {
    }
    var_s0++;
  }
  while (var_s0 != ((struct127 *) (&D_800D121C)));
}

void func_1507C700(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x2D0));
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x2D0));
    if ((temp_v0 != NULL) && (temp_v1 != NULL)) {
        (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x18)) - 1.0f;
        if (temp_f0 <= (*(f32 *)((u8 *)temp_v0 + 8))) {
            (*(f32 *)((u8 *)temp_v0 + 8)) = temp_f0;
        }
    }
}
