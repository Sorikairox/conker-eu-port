#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A0C80;
extern f32 D_800A0C84;
extern f32 D_800A0C88;
void func_15059C84(u8 *);
void func_150D18B0(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f2;
    temp_f0 = *(f32 *)(arg0 + 0xBC);
    temp_f2 = *(f32 *)(arg0 + 0x148);
    *(f32 *)(arg0 + 0xB8) += temp_f0;
    *(f32 *)(arg0 + 0xBC) = temp_f0 * D_800A0C80;
    *(f32 *)(arg0 + 0x3C) *= D_800A0C84;
    *(f32 *)(arg0 + 0xC4) += temp_f2;
    *(f32 *)(arg0 + 0x148) = temp_f2 * D_800A0C88;
    func_15059C84(arg0);
}

u8 *func_151149AC(s32);
void func_150D1920(u8 *arg0) {
    u8 *temp_v0;
    temp_v0 = func_151149AC(0xF9);
    if (temp_v0 != NULL) {
        if ((arg0 - (u8 *)D_800CC2D0) / 0x32C == 0) {
            temp_v0[0x6E] = 1;
        } else {
            temp_v0[0x6E] = 0;
        }
    }
}

void func_150D197C(s32 arg0) {
    u8 *temp_v0 = func_151149AC(0xF9);
    if (temp_v0 != NULL) {
        temp_v0[0x6E] = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FF0C0/func_150D19AC.s")
