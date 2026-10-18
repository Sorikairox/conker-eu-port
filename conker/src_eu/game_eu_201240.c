#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D3A30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4300.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D43B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D441C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D44C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D45A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4684.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4898.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D49B8.s")

void func_151D4668(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3C);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D469C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D4D44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D51E8.s")

s32 func_151D52B4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, *(s32 *)(p + 0xC));
    return 1;
}

void func_151D5308(s32 arg0) {
    func_151D469C(arg0, 0, 0x50, 0xFF, 1);
    func_151D469C(arg0, 1, 0x50, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D535C.s")

void func_151D56F8(u8 *arg0) {
    if (*(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x24) > 0) {
        *(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x24) -= 1;
    }
    *(s16 *)(*(u8 **)(arg0 + 0x31C) + 0x1AA) += 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5724.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D58E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5404.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5AC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5BF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5714.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5DA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D5FC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D611C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_201240/func_151D6310.s")

void func_151D5E30(s32 **arg0)
{
  s32 *new_var;
  u8 i;
  for (i = 0; i < 4; i++)
  {
    s32 *t = arg0[i];
    if (1)
    {
    }
    if (t)
    {
      new_var = arg0[i];
      func_100043B4(new_var, 3);
 } }
}
