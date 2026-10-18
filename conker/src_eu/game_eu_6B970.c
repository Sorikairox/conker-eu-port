#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503DE70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E1FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E238.s")

extern s32 D_800C6A84;
extern s32 D_800C6A88;
s32 func_1503E4E4(s32 arg0, s32 arg1)
{
  if (arg0 < 0x20) {
    if ((*(s32 *)((u8 *)&D_800C6A84 + arg1 * 0x10)) & (1 << arg0)) {
      return 1;
    }
  } else {
    if ((*(s32 *)((u8 *)&D_800C6A88 + arg1 * 0x10)) & (1 << arg0)) {
      return 1;
    }
  }
  return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E6B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E5F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503EB1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503ED44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503EE68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503EF90.s")

void func_1503F1A8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F1B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F23C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F2B4.s")

void func_1503F368(s32 arg0, s32 arg1) {
    func_1503EE68(arg0, 2.0f, 2.0f, 0);
}

void func_1503F39C(s32 arg0, s32 arg1) {
    func_1503EE68(arg0, 1.0f, 2.0f, 1);
}

void func_1503F3C8(s32 arg0, s32 arg1) {
    func_1503EE68(arg0, 2.06f, 3.0f, 1);
}

extern s32 D_800CC784;

void func_1503F3F8(s32 arg0) {
    struct106 *temp_v0;

    temp_v0 = &D_800C6660[arg0];
    (*(s16 *)((u8 *)temp_v0 + 0xC)) = 0x8C;
    *(s32 *)((u8 *)&D_800CC784 + (arg0 * 0x32C)) = 6;
    (*(f32 *)((u8 *)(temp_v0->unk0) + 0x1EC)) = 10.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F45C.s")

s32 func_1503E550(s32);
void func_1503EF90(s32);
s32 func_1503F23C(s32, s32, s32);

void func_1503F5A0(s32 arg0) {
    struct106 *temp_v0;
    struct127 *temp_v0_2;
    struct127 *temp_v0_3;
    struct127 *temp_v0_4;

    func_1503EF90(arg0);
    temp_v0 = &D_800C6660[arg0];
    (*(s16 *)((u8 *)temp_v0 + 0xC)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0xC)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)temp_v0 + 0xC)) <= 0) {
        func_1503E550(arg0);
        if (func_1503F23C(2, 0, arg0) != 0) {
            temp_v0_2 = &D_800CC2D0[arg0];
            temp_v0_2->unk94 |= 8;
        }
        if (func_1503F23C(2, 1, arg0) != 0) {
            temp_v0_3 = &D_800CC2D0[arg0];
            temp_v0_3->unk94 |= 4;
        }
        if (func_1503F23C(2, 2, arg0) != 0) {
            temp_v0_4 = &D_800CC2D0[arg0];
            temp_v0_4->unk94 |= 2;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F6F4.s")
