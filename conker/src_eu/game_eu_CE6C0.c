#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A09D0.s")

extern f32 D_8009F970;
extern f32 D_8009F974;
void func_150A11F4(u8 *arg0)
{
  f32 temp_f20;
  temp_f20 = (*((f32 *) (((u8 *) arg0) + 0xC))) * D_8009F970;
  *((f32 *) (((u8 *) arg0) + 0x24)) = func_150AD78C(temp_f20);
  *((f32 *) (((u8 *) arg0) + 0x28)) = func_150AD780(temp_f20);
  temp_f20 = (*((f32 *) (((u8 *) arg0) + 0x10))) * D_8009F974;
  *((f32 *) (((u8 *) arg0) + 0x2C)) = func_150AD78C(temp_f20);
  *((f32 *) (((u8 *) arg0) + 0x30)) = func_150AD780(temp_f20);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A126C.s")

u8 *func_150A1520(u8 *arg0) {
    return arg0 + 0x400;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A152C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A16A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2280.s")

void func_150A28C4(u8 *arg0)
{
  int new_var;
  s32 var_t0;
  s32 var_v1;
  u32 temp_v0;
  u8 temp_t1;
  if ((*((s32 *) (((u8 *) arg0) + 0x20))) == 0)
  {
    var_v1 = 0;
    var_t0 = 8;
    if (!((*((u8 *) (((u8 *) arg0) + 0x15))) & 3))
    {
      var_v1 = 0x8000;
    }
    temp_t1 = *((u8 *) (((u8 *) arg0) + 0x17));
    if ((((s32) temp_t1) >> (new_var = 7)) != 0)
    {
      var_t0 = 0x108;
    }
    temp_v0 = *((u32 *) (((u8 *) arg0) + 0x1C));
    func_1000FA64((temp_v0 >> 0x10) & ((short) 0xFFFF), *((s16 *) (((u8 *) arg0) + 0)), *((s16 *) (((u8 *) arg0) + 2)), *((s16 *) (((u8 *) arg0) + 4)), (temp_t1 & 0x7F) * 0x147, (u16) ((*((s32 *) (((u8 *) arg0) + 0x18))) | var_v1), (s16) (temp_v0 & 0xFFFF), 0, 0, 0, var_t0, 0);
    *((s32 *) (((u8 *) arg0) + 0x20)) = 1;
 dummy_label_636436: ;
    return;
  }
  *((s32 *) (((u8 *) arg0) + 0x20)) = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A29A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2AB4.s")

s32 func_150A2280(u8 *, u8 *, s32);
s32 func_151733EC(u8 *, u8, s32);

void func_150A2C6C(u8 *arg0)
{
  int new_var;
  s32 var_s0;
  u32 var_s1;
  u8 *temp_v0;
  if ((*((u8 *) (((u8 *) arg0) + 0x65))) == 0)
  {
    var_s1 = 0;
    var_s0 = 0;
    if (D_800D3094 != 0)
    {
      do
      {
        new_var = var_s0 ^ 0;
        if (((((s32) (*((u8 *) (((u8 *) (&D_800D34B8[new_var])) + 0x15)))) >> 2) == 8) && (func_150A2280(arg0, &D_800D34B8[var_s0 & 0xFFFFFFFF], 0) == 0))
        {
          temp_v0 = &D_800D34B8[var_s0];
          func_151733EC(arg0, *((u8 *) (((u8 *) temp_v0) + 0x17)), *((s32 *) (((u8 *) temp_v0) + 0x18)));
        }
        var_s1 += 1;
        var_s0 += 0x34;
      }
      while (var_s1 < ((u32) D_800D3094));
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2D44.s")

void func_150A2E20(s32 arg0, s32 arg1, int arg2)
{
  s32 temp_v0;
  int new_var;
  int new_var2;
  new_var = 1;
  arg0 = arg0 & 0xFFF;
  if (arg0 < ((u32) D_800D3094))
  {
    new_var2 = -new_var;
    if (arg1 != (-new_var))
    {
      *((s32 *) (((u8 *) (D_800D34B8 + ((13 * arg0) * 4))) + 0x18)) = arg1;
    }
    temp_v0 = arg0 * 0x34;
    if (arg2 != new_var2)
    {
      *((s8 *) (((u8 *) (D_800D34B8 + temp_v0)) + 0x17)) = arg2;
    }
    *((s32 *) (((u8 *) (D_800D34B8 + temp_v0)) + 0x1C)) = 0;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A29C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3264.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A332C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A33C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3484.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3538.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3674.s")

s32 func_150A3794(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct127 sp24;
    u8 *new_var; // fakematch: pointer to the local struct for the 0x180 store
    s32 pad[2];
    sp24.x_position = (sp24.old_x_position = (f32)arg1);
    sp24.y_position = (sp24.old_y_position = (f32)arg2);
    sp24.z_position = (sp24.old_z_position = (f32)arg3);
    new_var = (u8 *)&sp24;
    *(f32 *)(new_var + 0x180) = sp24.y_position;
    if (0 == func_150A2280((u8 *)&sp24, arg0, 0)) {
        return (unsigned int)1; // fakematch: permuter artifact (cast)
    }
    return 0;
}

void func_150A3810(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *arg1 = (s32) (*(u8 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x17));
    *arg2 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x18));
    *arg3 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x1C));
    *arg4 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x20));
}

void func_150A3878(s32 arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 & 1) {
        *(s8 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x17) = arg2;
    }
    if (arg1 & 2) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x18) = arg3;
    }
    if (arg1 & 4) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x1C) = arg4;
    }
    if (arg1 & 8) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x20) = arg5;
    }
}

void func_150A3924(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *(s16 *)(D_800D34B8 + temp_v0) = arg1;
    (*(s16 *)((u8 *)((D_800D34B8 + temp_v0)) + 2)) = arg2;
    (*(s16 *)((u8 *)((D_800D34B8 + temp_v0)) + 4)) = arg3;
}

s32 func_150A39E4();

s32 func_150A3990(u8 *arg0) {
    if (arg0[0x14] == 1) {
        return 0;
    }
    if (!(arg0[0x15] & 3)) {
        return func_150A39E4();
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A39E4.s")
