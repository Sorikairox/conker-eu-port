#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 allocate_memory(s32, s32, s32, s32);
s32 func_10004074(s32);
s32 func_1502DB14(u8 *, s32, s32);
s32 func_1507C170(u8 *, f32, s32, s32);
s32 func_150A86B0(s32 *, s32, u8 *, s32, s32, s16 *, s32, s32);
s32 func_150A9E64(s32, u8);

void func_1503F7A0(u8 *arg0)
{
  s32 sp44;
  s16 sp40[2];
  int new_var;
  s32 sp38;
  s32 temp_v0;
  u8 *temp_v0_2;
  sp44 = 0;
  if ((*((s32 *) (((u8 *) ((u8 *) (((u32) arg0) + (D_800BE9C0 * 4)))) + 0x3E0))) != 0)
  {
    temp_v0 = allocate_memory(0x320, 1, 2, 2);
    sp44 = temp_v0;
    func_1502DB14(arg0, 0, temp_v0);
    sp40[0] = 0x1000;
    if (arg0) // fakematch: empty if from the permuter
    {
    }
    temp_v0_2 = (u8 *) (((u32) arg0) + (D_800BE9C0 * 4));
    temp_v0 = *((s32 *) (((u8 *) temp_v0_2) + 0x3E0));
    sp38 = *((s32 *) (((u8 *) temp_v0_2) + 0x3E8));
    func_150A86B0(&sp38, temp_v0, arg0, *((s32 *) (((u8 *) arg0) + 0x3F0)), (s32) (*((u8 *) (((u8 *) arg0) + 0x3F4))), sp40, 0, 0);
    func_150A9E64(*((s32 *) (((u8 *) ((u8 *) (((u32) arg0) + (D_800BE9C0 * 4)))) + 0x3E8)), *((u8 *) (((u8 *) arg0) + 0x3F4)));
    *((s8 *) (((u8 *) arg0) + 0x3F6)) = 1;
  }
  func_1507C170(arg0, D_800BE9A4, 0, 0);
  if (sp44 != 0)
  {
    func_10004074(sp44);
  }
}

s32 func_1505E0C4(struct127 *, s32, u8 *, s32, s32, s32, s32, f32, f32, f32, f32, s32);
void func_1503F8A8(u8 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_1505E0C4(0, 0, arg0, 0, arg1, arg2, (s32) (*(u8 *)((u8 *)arg0 + 0x3F5)), arg3, arg4, 0.0f, 0.0f, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6CFB0/func_1503F91C.s")

void func_1503FAA8(u8 *arg0) {
    func_100043B4(*(s32 **)(arg0 + 0x3E8), 4);
    func_100043B4(*(s32 **)(arg0 + 0x3EC), 4);
    func_10004074(arg0);
}
