#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15A210/func_1512C490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15A210/func_1512D5E0.s")

s32 func_1502B5C8(u32 *, s32, s32, s32);
extern s32 D_800DC6B0[];
extern s32 D_800DC6C0[];
void func_1512D7A8(void) {
    u32 sp3C;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800DC6B0[i] = func_1502B5C8(&sp3C, 2, 0x1B, i);
        D_800DC6C0[i] = sp3C / 24;
    }
}

void func_1512D854(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x850) = arg1;
    arg0[0x84D] = 1;
}

extern s32 D_800DC6C0[];
void func_1512D868(u8 *arg0) {
    switch (arg0[0x84D]) {
    case 1:
        arg0[0x84E] = 0;
        arg0[0x84D] = 2;
        break;
    case 2:
        arg0[0x84E] += D_800BE9E4;
        if (arg0[0x84E] >= D_800DC6C0[*(s32 *)(arg0 + 0x850)]) {
            arg0[0x84D] = 0;
        }
        break;
    }
}

void func_1512D8D8(s32 arg0) {
}
