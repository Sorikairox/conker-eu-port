#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1507EF60(u8 *arg0, s32 *arg1, u8 arg2) {
    if ((*arg1 + 1) < 40) {
        arg0[*arg1] = arg2;
        (*arg1)++;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507EF98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F018.s")

void func_1507F238(u8 arg0, u8 *arg1) {
    func_1507F298(arg0, arg1);
    if (arg0 == 0x11) {
        func_1507F298(0x12, arg1);
    } else if (arg0 == 0x12) {
        func_1507F298(0x11, arg1);
    }
}

void func_1507F298(u8 arg0, u8 *arg1) {
    s32 i;

    for (i = 4; i > 0; i--) {
        arg1[i] = arg1[i - 1];
    }
    arg1[0] = arg0;
}

void func_1507F2D4(void)
{
  u8 *p;
  s32 type;
  p = (u8 *)D_800D154C->unk31C;
  type = p[0x64];
  p += 0x58;
  if (type == 0) {
    p[0xC] = 1;
    p[0xD] = 0;
  } else if (type == 1) {
    func_150ADA20();
    if (p[0xD] >= 3) {
      p[0xC] = 2;
      p[0xD] = 0;
    }
  } else {
    if (p[0xD] >= (func_150ADA20() & 3) + 8) {
      p[0xC] = 1;
      p[0xD] = 0;
    }
  }
}

void func_1507F380(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 4; i >= 0; i--) {
        if (arg0 == arg1[i]) {
            arg1[i] = 0;
            return;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F3B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F834.s")

s32 func_1507F8A0(s32 arg0) {
    s32 pad;
    s32 var_v1;
    u32 var_a0;

    if (arg0 == 0) {
        var_v1 = 0x96;
        var_a0 = 0x32;
        goto block_7;
    }
    if (D_800BE9F0 == 0x31) {
        return 0;
    }
    var_v1 = 0;
    if (arg0 == 1) {
        var_v1 = 0x32;
        var_a0 = 0x32;
    } else {
        var_a0 = 0x1E;
    }
block_7:
    return (func_150ADA20() % var_a0) + var_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F92C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F640.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1508000C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_150802A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1508039C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_150803E0.s")
