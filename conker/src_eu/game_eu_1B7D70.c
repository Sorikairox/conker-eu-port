#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7D70/func_1518A560.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B7D70/func_1518A604.s")

extern f32 D_800A77A0;
extern f32 D_800A77A4;
extern f32 D_800A77A8;
s32 func_1518A784(u8 *arg0, u8 *arg1) {
    s32 off; // fakematch: offset in a variable keeps v = arg0 + 0x110 in a register
    u8 *v;
    f32 f;

    off = 0x110;
    switch (*(u8 *)(*(u8 **)(arg0 + 0x188) + 0x68) - 0xF) {
    default:
        f = D_800A77A0;
        v = arg0 + off;
        *(f32 *)(v + 0x18) = f;
        *(f32 *)(v + 0x1C) = f;
        arg0[0x2A] = 0;
        arg0[0x29] = 0;
        arg0[0x28] = 0xFF;
        *arg1 = 1;
        break;
    case 0:
        *(s32 *)(arg0 + 0x58) &= ~2;
        *arg1 = 0;
        break;
    case 1:
        f = D_800A77A4;
        v = arg0 + off;
        *(f32 *)(v + 0x18) = f;
        *(f32 *)(v + 0x1C) = f;
        arg0[0x28] = 0x80;
        arg0[0x29] = 0;
        arg0[0x2A] = 0;
        *arg1 = 1;
        break;
    case 2:
        f = D_800A77A8;
        v = arg0 + off;
        *(f32 *)(v + 0x18) = f;
        *(f32 *)(v + 0x1C) = f;
        arg0[0x28] = 0xFF;
        arg0[0x29] = 0;
        arg0[0x2A] = 0;
        *arg1 = 1;
        break;
    }
    return 1;
}

s32 func_1518A858(u8 *arg0, u8 *arg1) {
    if ((*(u8 **)(arg0 + 0x188))[0x6A] != 0) {
        *(s32 *)(arg0 + 0x58) &= ~2;
        *arg1 = 0;
    } else {
        *arg1 = 1;
    }
    return 1;
}

s32 func_1518A894(u8 *arg0, u8 *arg1) {
    if ((*(u8 **)(arg0 + 0x188))[0x6F] == 0) {
        *(s32 *)(arg0 + 0x58) &= ~2;
        *arg1 = 0;
    } else {
        *arg1 = 1;
    }
    return 1;
}

void func_1518A8D0(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x170;
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(p + 0x18)) {
            *(s32 *)(p + 0x18) = arg1[1];
            p[0x1D] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(p + 0x18)) {
            *(s32 *)(p + 0x18) = arg1[0];
            p[0x1D] = ((u8 *)arg1)[8];
        }
    }
}
