#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150DE8A0(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DE8AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DE9D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DEC58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DED40.s")

s32 func_150DF04C(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg0 + 0x110)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg0 + 0x114)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg0 + 0x118)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x11C)) -= D_800BE9A4;
    if ((*(f32 *)((u8 *)arg0 + 0x11C)) < 0.0f) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DF0D8.s")

void func_150DF1A8(u8 arg0, s32 arg1);

void func_150DF160(s32 arg0) {
    u8 i;

    for (i = 0; i < 4; i++) {
        func_150DF1A8(i, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DF1A8.s")
