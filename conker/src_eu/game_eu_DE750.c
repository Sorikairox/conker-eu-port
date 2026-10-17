#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DE750/func_150B0F40.s")

void func_150B1114(u8 *arg0) {
    func_150B1138(arg0, 0xFF, 1);
}

void func_150B1138(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x58, -1, 0, 0x43, 0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

void func_150B11C0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DE750/func_150B1200.s")
