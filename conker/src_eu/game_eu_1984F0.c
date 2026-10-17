#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1516ACE0(u8 *arg0) {
    s32 n = 1;

    while (*arg0 != 0) {
        if (*arg0 == 0xBD) {
            *arg0 = 0;
            n++;
        }
        arg0++;
    }
    return n;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516AD20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516AFE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516BC2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516CDE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516CEA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516D1C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516D63C.s")

void func_1516D850(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        (*(u8 **)(arg0 + 0x10))[8] = 0;
        func_1516972C((struct102 *)arg0);
        arg0[0x15] = 0;
    }
}

void func_1516D898(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x100;
        **(s32 **)(arg0 + 0x10) &= ~0x400;
        arg0[0x20] = (*(u8 **)(arg0 + 0x10))[8];
    }
}

u8 *func_1516D8E8(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x100;
        **(s32 **)(arg0 + 0x10) &= ~0x400;
        return arg0;
    }
    return NULL;
}

u8 *func_1516D934(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x500;
        return arg0;
    }
    return NULL;
}
