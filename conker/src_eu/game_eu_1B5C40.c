#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B5C40/func_15187EC0.s")

void func_15188500(void) {
    bzero(D_800DFB30, 0xB4);
    D_800DFBE4 = 0;
}

void func_15188530(s32 arg0, s32 *arg1) {
    if ((arg0 < D_800DFBE4) && (arg0 >= 0)) {
        struct_eu_800DFB30 *temp_v0 = &D_800DFB30[arg0];
        arg1[0] = temp_v0->unk6;
        arg1[1] = temp_v0->unk7;
        arg1[2] = temp_v0->unk8;
    }
}

void func_15188580(s32 arg0, f32 *arg1) {
    if ((arg0 < D_800DFBE4) && (arg0 >= 0)) {
        *arg1 = D_800DFB30[arg0].unkC;
    }
}

extern f32 D_800DFB3C[][9];
void func_151885BC(s32 arg0, f32 arg1) {
    if (arg0 < D_800DFBE4 && arg0 >= 0) {
        if (arg1 > 1.0f) {
            arg1 = 1.0f;
        } else if (arg1 < 0.0f) {
            arg1 = 0.0f;
        }
        D_800DFB3C[arg0][0] = arg1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B5C40/func_15188630.s")
