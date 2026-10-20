#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_150FD140(s32);
s32 func_1516547C(s32, s32, s32, s32, s32);
extern s32 func_1000EC24;

void func_150FCFB0(void) {
    s32 var_s0;
    struct { s8 u44; s8 u45; s16 u46; s8 u48; s8 u49; s8 u4A; } sp;

    func_150FD140(0);
    func_150FD140(1);
    func_150FD140(2);
    func_1000FA64(0x2B8U, -0x7F6, 0x618, -0xA47, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, (u8 *)0x2D, 0, 0, 0);
    func_1000FA64(0x2B7U, -0x13F, -0x111, -0xD5B, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, NULL, 0, 0, 0);
    func_1000FA64(0x2B6U, 0x5EF, 0x3B3, -0xA49, 0x6D60, 0x2328U, 0x1B58, (s32) &func_1000EC24, (u8 *)0x5A, 0, 0, 0);
    var_s0 = 0;
    if ((D_80082FA0 + 1) > 0) {
        do {
            func_1516547C(4, var_s0 & 0xFF, 0, 0xFF, 1);
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
    sp.u44 = 1;
    sp.u46 = 0x64;
    sp.u49 = 0xF;
    sp.u48 = 8;
    sp.u4A = -1;
    func_151D8E18((structEU_151D8E18 *) &sp, 0, 0xFFU, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD140.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD49C.s")

void func_150FD530(s32 arg0) {
    func_15103828();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD554.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FDA94.s")

void func_150FE08C(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 new_var2; // fakematch: permuter temp
  u8 new_var; // fakematch: permuter temp
  u8 *v = arg0 + 0x110;
  if (arg2 == 0x2D)
  {
    if ((*((s32 *) arg1)) == (*((s32 *) v)))
    {
      *((s32 *) v) = *((s32 *) (arg1 + 4));
      v[4] = arg1[9];
      return;
    }
    if ((*((s32 *) (arg1 + 4))) == (*((s32 *) v)))
    {
      *((s32 *) v) = *((s32 *) arg1);
      v[4] = arg1[8];
      dummy_label_617528: // fakematch: permuter artifact (unused label)
      ;

      ;
      ;
    }
  }
  else
    if (arg2 == 0)
  {
    new_var2 = *((s32 *) arg1);
    if ((new_var2 == (*((s32 *) v))) || ((new_var = v[4] ^ 0) == arg1[4])) // fakematch: ^ 0
    {
      *((s32 *) v) = 0;
    }
  }
}

u8 *func_150FE120(u8 *arg0, s16 arg1) {
    u8 *v = (u8 *)func_1513EDE4((s32)arg0, arg1);
    if (v != NULL) {
        *(s16 *)(v + 0x8) = *(f32 *)(arg0 + 0x124);
        *(s16 *)(v + 0x18) = *(f32 *)(arg0 + 0x128);
        *(s16 *)(v + 0x28) = *(f32 *)(arg0 + 0x128);
        *(s16 *)(v + 0x38) = *(f32 *)(arg0 + 0x124);
    }
    return v;
}

void func_150FE1AC(u8 *arg0)
{
  u8 *v = arg0 + 0x110; // fakematch: v defined first so IDO keeps it as a separate pointer (not folded)
  
  if (*(s32 *)(arg0 + 0x134) != 0) { func_1516972C(*(struct102 **)(arg0 + 0x134)); }
  if (*(struct102 **)(v + 0x28)) { func_1516972C(*(struct102 **)(v + 0x28)); } // fakematch: pointer-typed test gives one load (s32 test double-loads like line above)
  if (*(u16 *)(v + 0x54) != 0) { func_100111C8(*(u16 *)(v + 0x54)); }
  if (*(u16 *)(v + 0x56) != 0) func_100111C8(*(u16 *)(v + 0x56));
}

void func_150FE22C(void *arg0) {
    func_150FE1AC(arg0);
    func_1513CA6C(arg0);
}

void func_150FE258(void *arg0) {
    func_150FE1AC(arg0);
    func_1513CAA0(arg0);
}
