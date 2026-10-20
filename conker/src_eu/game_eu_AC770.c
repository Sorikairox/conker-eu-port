#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1507EF60(u8 *arg0, s32 *arg1, u8 arg2) {
    if ((*arg1 + 1) < 40) {
        arg0[*arg1] = arg2;
        (*arg1)++;
    }
}

extern u8 *D_80086FC4[];
extern u8 D_8009BFC0[];
void func_1507EF98(s32 arg0, s32 *arg1, s32 arg2) {
    u8 *src;
    s32 len;
    s32 v;
    src = D_80086FC4[arg2];
    len = D_8009BFC0[arg2];
    v = *arg1;
    if (v + len < 0x28) {
        bcopy(src, v + arg0, len);
        *arg1 += len;
    }
}

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

extern u8 D_800B89C4[];

void func_1507F92C(struct127 *arg0) {
    s32 v;

    if (arg0->unk13C >= 0x64) {
        switch (D_800B89C4[arg0->unk13C * 0x32C]) {
        case 0x57:
            v = 0x115;
            break;
        case 0x8C:
            v = 0x1A5;
            break;
        case 0xA8:
        case 0xA9:
            v = 0x1AF;
            break;
        case 0x89:
        case 0xBA:
            v = 0x1FA;
            break;
        default:
            v = 0xD8;
            break;
        }
        func_1505E650(arg0, v, 1.0f, 4.0f, 0.0f, 0.0f, 0);
    } else {
        func_1505E650(arg0, 0xF, 1.0f, 3.0f, 0.0f, 0.0f, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F640.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1508000C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_150802A8.s")

void func_1508039C(u8 *arg0)
{
  u8 *sp20[2];
  s32 sp1C;
  sp1C = 1;
  sp20[0] = arg0;
 if (0) { }
  if (sp1C)
  {
    sp1C = (s32) sp20;
    ((u8 *) sp20)[4] = arg0[0x3B];
    func_151920FC(sp1C, 0xD);
  }
  func_151494E0(0xFFFFFFFFFFFFFFFF & sp1C, 0xD);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_150803E0.s")
