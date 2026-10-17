#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150BE390(s32 arg0, u8 arg1, s32 arg2) {
    struct {
        s32 unk0;
        s16 unk4;
    } sp38;
    struct260 *temp_v0;

    sp38.unk4 = 0;
    sp38.unk0 = arg0;
    temp_v0 = func_15149130(0x12C, -1, 0x4F, -1, 0, 0x3C, 8, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &sp38, 8);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBBA0/func_150BE40C.s")

void func_150BE650(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x28) == *arg1) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x28) == *(u8 **)(p + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

s32 func_150BE6C4(f32 *arg0) {
    arg0[5] += arg0[0x20] * D_800BE9A4;
    if (arg0[5] > 120.0f) {
        return 0;
    }
    return 1;
}
