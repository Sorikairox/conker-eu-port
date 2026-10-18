#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A5C10.s")

void func_151A62DC(u16);
void func_151A625C(struct260 *arg0)
{
  u16 *new_var;
  struct260 *p = arg0;
  new_var = (u16 *) (((u8 *) p) + 0x6C);
  if ((*new_var) != 0)
  {
    func_151A62DC(*new_var);
  }
  func_1514933C(p);
}

void func_151A62DC(u16);
void func_151A629C(struct260 *arg0)
{
  u16 *new_var;
  struct260 *p = arg0;
  new_var = (u16 *) (((u8 *) p) + 0x6C);
  if ((*new_var) != 0)
  {
    func_151A62DC(*new_var);
  }
  func_15149368(p);
}

void func_151A62DC(u16 arg0) {
    func_100111C8(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6308.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6520.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6618.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6900.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A6BB0.s")

void func_1000FD38(s32 (*)(struct57 *, struct57 *, s32 *, s32, s32, s32, u16 *), u8 *, s32, u8 *);

void func_151A7068(u8 *arg0) {
    struct102 *temp_a0;

    (*(s8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x110))) + 0x14)) = 1;
    func_1000FD38(func_1000EF40, (*(u8 **)((u8 *)arg0 + 0x110)), 0, arg0);
    temp_a0 = (*(struct102 **)((u8 *)arg0 + 0x120));
    if (temp_a0 != NULL) {
        func_1516972C(temp_a0);
    }
}

void func_151A70C0(struct210 * arg0) {
    func_151A7068(arg0);
    func_1513CA6C(arg0);
}

void func_151A70EC(struct210 * arg0) {
    func_151A7068(arg0);
    func_1513CAA0(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A7118.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A7188.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A7240.s")
