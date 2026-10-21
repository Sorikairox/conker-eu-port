#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15103800(void) {
    bzero(D_800D9AB0, 8); // bzero
}

void func_15103828(void) {
    u16 temp_v1;
    s32 i;

    for (i = 0; i < 4; i++)
    {
        if (D_800D9AB0[i]) {
            if (D_800D9AB0[i] > D_800BE9E4)
            {
                D_800D9AB0[i] -= D_800BE9E4;
            } else {
              D_800D9AB0[i] = 0;
            }
        }
    }
}

// need to figure out the structs
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103910.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103AA0.s")
#ifdef NON_MATCHING
extern s32 func_15103910;
extern s32 func_15103AA0;

void func_15103C14(s32 arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4) {
    s32 sp48;
    u16 *sp40;
    s32 var_s1;
    struct127 *temp_v0_2;
    u16 *temp_v0;

    var_s1 = arg0;
    temp_v0 = &D_800D9AB0[arg3];
    sp48 = 0;
    if ((*temp_v0 == 0) || (var_s1 == 0x58D)) {
        sp40 = temp_v0;
        temp_v0_2 = func_1505EEF4(arg1);
        if ((temp_v0_2 != NULL) && (func_10010894(temp_v0_2) == 0)) {
            if (arg2 != 0) {
                if (arg4 != 0) {
                    var_s1 += (func_150ADA20() % arg2) * 2;
                } else {
                    var_s1 += func_150ADA20() % arg2;
                }
            }
            if (temp_v0_2->camera != NULL) {
                sp48 = 1;
            } else if (arg4 != 0) {
                var_s1 += 1;
            }
            if (sp48 != 0) {
                func_1000FA64(var_s1 & 0xFFFF, (s16) (s32) temp_v0_2->x_position, (s16) (s32) temp_v0_2->y_position, (s16) (s32) temp_v0_2->z_position, 0x7530, 0x7FFFU, 0x7FFE, (s32) &func_15103910, (u8 *)0x10, (s32) temp_v0_2, 0x100, 0);
            } else {
                func_1000FA64(var_s1 & 0xFFFF, (s16) (s32) temp_v0_2->x_position, (s16) (s32) temp_v0_2->y_position, (s16) (s32) temp_v0_2->z_position, 0x7FBC, 0x7FFFU, 0x7FFE, (s32) &func_15103AA0, (u8 *) ((arg4 << 0xF) | 0x10), (s32) temp_v0_2, 0x100, 0);
            }
            *sp40 = 0x1F4;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103C14.s")
#endif