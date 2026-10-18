#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FCFB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD140.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD49C.s")

void func_150FD530(s32 arg0) {
    func_15103828();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FD554.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FDA94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FE08C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12A7C0/func_150FE120.s")

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
