#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15036F60(u8 *arg0) {
    s32 i;

    *(f32 **)(arg0 + 0x324) = allocate_memory(0x48, 1, 0, 0);
    bzero(*(f32 **)(arg0 + 0x324), 0x48);
    for (i = 0; i < 3; i++) {
        (*(f32 **)(arg0 + 0x324))[i] = -99999.0f;
        (*(f32 **)(arg0 + 0x324))[i + 3] = -99999.0f;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15036FD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037988.s")
extern s32 D_800C4414;

s32 func_15037B70(s32 arg0, u8 *arg1) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t8;
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg0];
    temp_t8 = temp_v0->unk2F8 & 7;
    if (temp_t8 == 1) {
        (*(f32 *)arg1) = (f32) D_800DBFF0->unk2F8;
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) D_800DBFF0->unk2FC;
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) D_800DBFF0->unk300;
        return 1;
    }
    if (temp_t8 == 2) {
        if (temp_v0->unk5 == 4) {
            temp_f0 = temp_v0->x_position - (f32) (*(s16 *)((u8 *)(&D_800C4414) + 0));
            temp_f2 = temp_v0->z_position - (f32) (*(s16 *)((u8 *)(&D_800C4414) + 4));
            if (62500.0f < ((temp_f0 * temp_f0) + (temp_f2 * temp_f2))) {
                return 1;
            }
        }
        (*(f32 *)arg1) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 0));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 2));
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) (*(s16 *)((u8 *)(&D_800C4414) + 4));
        return 1;
    }
    if (temp_t8 == 3) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15037CCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_150383B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15038758.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15038910.s")

void *func_15039D44(s32 arg0, s32 arg1) {
    return &D_80098418[arg1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15039D68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_15039CC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A1C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A37C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A8FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503A968.s")

s32 func_15037224();
s32 func_1503A968();
extern u8 D_800C441A;

void func_1503AAE0(void) {
    s32 sp1C;

    sp1C = D_800C441A;
    D_800C441A = 0;
    func_15037224();
    D_800C441A = sp1C;
    func_1503A968();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_64770/func_1503AB20.s")

s32 func_150383B0(u8 *, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern s32 D_800C43F0;

void func_1503B9F8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    (*(f32 *)((u8 *)arg0 + 0)) = -99999.0f;
    (*(f32 *)((u8 *)arg0 + 4)) = -99999.0f;
    (*(f32 *)((u8 *)arg0 + 8)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 0)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 4)) = -99999.0f;
    (*(f32 *)((u8 *)(&D_800C43F0) + 8)) = -99999.0f;
    if (func_15037B70(arg3, arg0) == 0) {
        func_150383B0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
    }
}
