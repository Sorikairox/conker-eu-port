#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D7930(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D79EC(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D7A9C(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D7B40(s32 arg0) {
    if (arg0 == 0) {
        D_800D9D30 += D_800BE9E4 << 6;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7B6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7CA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7E38.s")
