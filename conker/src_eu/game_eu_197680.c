#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *func_15169E70(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x5E, 0, 0x4C, 0, (u8) arg1, 1U);
    if (temp_v0 != NULL) {
        bcopy(arg0, temp_v0 + 0x10, 0x3C);
    }
    return temp_v0;
}

void func_15169ED8(s32 arg0) {
    func_15169E70(arg0, 0xFF);
}

void func_15169EF8(u8 *arg0) {
    s32 v;
    s32 r;
    s32 t;

    if (*(s8 *)(arg0 + 0x40) != 0) {
        ((void (*)(u8 *))D_8008CDC0[*(s8 *)(arg0 + 0x40)])(arg0);
    }
    v = *(s16 *)(arg0 + 0x26);
    v += *(s16 *)(arg0 + 0x28) * D_800BE9E4;
    r = arg0[0x41] << 8;
    if (v >= r) {
        v -= r;
    } else if (v < 0) {
        v += r;
    }
    *(s16 *)(arg0 + 0x26) = v;
    t = *(s16 *)(arg0 + 0x24);
    if (t != 0) {
        t -= D_800BE9E4;
        if (t <= 0) {
            func_1516972C((struct102 *)arg0);
        } else {
            *(s16 *)(arg0 + 0x24) = t;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_197680/func_15169FB8.s")
