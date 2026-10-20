#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503DE70.s")

void func_1503E1FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct106 *temp_v0;
    temp_v0 = &D_800C6660[arg0];
    temp_v0->unk4 |= arg2;
    temp_v0->unk8 |= arg3;
    temp_v0->pad[2] = arg1;
    temp_v0->unkF = 2;
}

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

void func_1503EF90(s32);
void func_1503F1B0(s32 arg0) {
    s32 temp_v0;
    struct106 *temp_v1;

    func_1503EF90(arg0);
    temp_v1 = &D_800C6660[arg0];
    temp_v0 = *(s16 *)((u8 *)temp_v1 + 0xC);
    temp_v0 = temp_v0 - D_800BE9E4; // fakematch: split load/subtract (permuter) gives the ref register order
    (*(s16 *)((u8 *)temp_v1 + 0xC)) = temp_v0;
    if (temp_v0 <= 0) {
        func_15060F28(&D_800CC2D0[arg0], 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F23C.s")

extern u8 D_80098CC4[];

void func_1503F2B4(s32 arg0) {
    struct106 *p;
    s32 n;
    s32 i;

    p = &D_800C6660[arg0];
    *(s16 *)&p->pad[0] = 0x78;
    n = D_80098CC4[(u8)p->pad[2]];
    for (i = 0; i < n; i++) {
        *(f32 *)(p->unk0 + i * 0x68 + 0x4C) = (s32)(func_150ADA20() % 20U) - 5;
    }
}

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

s32 func_1503E5F8(f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_1503F6F4(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    f32 sp30[16];
    if (D_800C42B0 != 0) {
        guMtxL2F((f32 (*)[4]) sp30, arg0);
    } else {
        memcpy(sp30, arg0, 0x40);
    }
    func_1503E5F8(sp30, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
