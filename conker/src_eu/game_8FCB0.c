#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15058F24(struct127 *arg0, f32, f32);
u8   func_150599C8(struct127 *arg0, u8 arg1, u16 arg2);
void func_1505A250(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
f32  func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);

u8  func_1505B9C4(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
s32 func_1505C1E4(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

// EU: split from game_83300.c, EU pads to a file boundary before this.

#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15062800.s")

void func_15062AC4(struct127 *arg0) {
    if (arg0->unkE6 && arg0->unkE4) {
        f32 tmp = arg0->unkE4;
        arg0->unkEC = tmp / arg0->unkE6;
        arg0->unkF0 = arg0->unkE6 / tmp;
    } else {
        arg0->unkF0 = arg0->unkEC = 0.0f;
    }
}

void func_15062B1C(struct127 *arg0, f32 arg1) {
    arg0->unkE4 = arg0->xz_scale * arg1;
    func_15062AC4(arg0);
}

void func_15062B50(struct127 *arg0, f32 arg1) {
    arg0->unkE6 = arg0->y_scale * arg1;
    func_15062AC4(arg0);
}

void func_15062B84(struct127 *arg0) {
    if (arg0->unkD4 && arg0->unkD2) {
        f32 tmp = arg0->unkD2;
        arg0->unkDC = tmp / arg0->unkD4;
        arg0->unkE0 = arg0->unkD4 / tmp;
    } else {
        arg0->unkDC = 0.0f;
        arg0->unkE0 = 0.0f;
    }
}

void func_15062BDC(struct127 *arg0, f32 arg1, f32 arg2) {
    struct124 *temp_v0;

    arg0->xz_scale = arg1;
    arg0->y_scale = arg2;
    if (arg0->id != 255) {
        temp_v0 = D_800D1C90[arg0->id];
        arg0->unkD2 = (s32) (temp_v0->unk20 * arg0->xz_scale);
        arg0->unkD4 = (s32) (temp_v0->unk22 * arg0->y_scale);
        arg0->unkD6 = (s32) (temp_v0->unk24 * arg0->y_scale);
        arg0->unkE4 = (s32) (temp_v0->unk1A * arg0->xz_scale);
        arg0->unkE6 = (s32) (temp_v0->unk1C * arg0->y_scale);
        arg0->unkE8 = (s32) (temp_v0->unk1E * arg0->y_scale);
        func_15062AC4(arg0);
        func_15062B84(arg0);
    }
}

#ifdef NON_MATCHING
extern s32 D_800C48A8;

void func_15062D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;

    if ((&D_800D19A0)[arg0] != 0) {
        temp_a3 = *(s32 *)(*(s32 *)((u8 *)&D_800C48A8 + (arg0 * 4)) + (arg4 * 4)) + (arg1 * 8);
        temp_a2 = (*(s32 *)((u8 *)temp_a3 + 4));
        temp_v1 = ((temp_a2 >> 0xC) & 0xFFF) + 2;
        temp_a0 = (temp_a2 & 0xFFF) + 2;
        temp_a2_2 = (*(s32 *)((u8 *)temp_a3 + 0));
        if (arg5 != 0) {
            var_v0 = arg2 & 0xFFF;
        } else {
            temp_a1 = ((temp_a2_2 >> 0xC) & 0xFFF) + arg2;
            var_v0 = temp_a1;
            if (temp_v1 < temp_a1) {
                var_v0 = temp_a1 - temp_v1;
            } else if (temp_a1 < 0) {
                var_v0 = temp_a1 + temp_v1;
            }
        }
        if (arg5 != 0) {
            var_v1 = arg3 & 0xFFF;
        } else {
            temp_a1_2 = (temp_a2_2 & 0xFFF) + arg3;
            var_v1 = temp_a1_2;
            if (temp_a0 < temp_a1_2) {
                var_v1 = temp_a1_2 - temp_a0;
            } else if (temp_a1_2 < 0) {
                var_v1 = temp_a1_2 + temp_a0;
            }
        }
        (*(s32 *)((u8 *)temp_a3 + 0)) = (s32) ((temp_a2_2 & 0xFF000000) | (var_v1 & 0xFFF) | ((var_v0 & 0xFFF) << 0xC));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15062D10.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15062E24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15062FC0.s")
void func_15063168(struct127 *arg0) {
    s32 i;

    for (i = 0; i < D_8008FD8C; i++) {
        if ((i != (arg0 - D_800CC2D0)) && ((1 << i) & D_800CC268)) {
            if ((D_800CC2D0[i].unk31C != NULL) && (((u8 *)D_800CC2D0[i].unk31C)[0x1AC] == 0)) {
                func_15195564(arg0, &D_800CC2D0[i], 1);
            }
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15063254.s")
