#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503DE70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E1FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E238.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E4E4.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F5A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F6F4.s")
