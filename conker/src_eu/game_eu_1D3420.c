#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A5C10.s")

void func_151A62DC(u16);
void func_151A625C(struct260 *arg0)
{
  u16 *new_var;
  struct260 *p = arg0;
  new_var = (u16 *) (((u8 *) p) + 0x6C); // fakematch: re-load of the field (no andi)
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
  new_var = (u16 *) (((u8 *) p) + 0x6C); // fakematch: re-load of the field (no andi)
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

u8 *func_151A7188(s32);
s32 func_1505D024();
void func_151A7118(u8 *arg0, s32 arg1) {
    s32 pad; // fakematch: unused local moves v to sp18
    struct127 *v = NULL;
    u8 *t;
    s32 a3;
    t = func_151A7188(arg1);
    if (t != NULL) {
        v = *(struct127 **)(t + 0x38);
    }
    if (v != NULL) {
        a3 = v - D_800CC2D0;
    } else {
        a3 = -1;
    }
    func_1505D024(arg0, 0x60034, *(u16 *)(arg0 + 0x7A), a3);
}

u8 *func_151A7188(s32 arg0) {
    u8 i;
    u8 j;
    struct_eu_node *p;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (p = D_800DD280[j][(&D_800A5770)[i]]; p != NULL; p = p->next) {
                if ((*(u8 *)((u8 *)p + 0x13) == 0x2C) && (arg0 == *(s32 *)((u8 *)p + 0x28))) {
                    return (u8 *)p;
                }
            next: ; // fakematch: label at the end of the inner loop body moves the j/i increments into the exit block
            }
        }
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D3420/func_151A7240.s")
