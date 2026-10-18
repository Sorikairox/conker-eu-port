#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F1E30/func_150C4620.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F1E30/func_150C49A4.s")

void func_150C4FD8(u8 *arg0) { u8 *p = arg0; if (*(s32 *)(p + 0x34) != 0) { func_1516972C(*(struct102 **)(p + 0x34)); } }

void func_150C5008(struct260 *arg0) {
    func_150C4FD8(arg0);
    func_1514933C(arg0);
}

void func_150C5034(struct260 *arg0) {
    func_150C4FD8(arg0);
    func_15149368(arg0);
}

void func_150C5060(u8 *arg0, s32 arg1, u8 arg2) {
    u8 **q = &arg0; // fakematch: address-taken arg0 forces the home-slot reload (shape C)
    u8 *p;
    if (arg2 == 0x55) {
        p = *q + 0x28; p[0x16] = p[0x16] & 0xFFFD;
    } else if (arg2 == 0x56) {
        p = *q + 0x28; p[0x16] = p[0x16] | 2;
    } else {
        p = *q + 0x28;
        func_15149514(arg1, arg2, (s32)p, (s32)(p + 4), (s32)*q);
    }
}
