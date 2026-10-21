#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8AA0/func_1518B290.s")

s32 func_1518B71C(f32 *arg0) {
    if (arg0[0x3C / 4] < arg0[0x170 / 4]) {
        return 0;
    }
    return 1;
}

s32 func_1518B748(u8 *arg0) {
    f32 d;
    s32 a;
    s32 b;
    s32 c;

    d = *(f32 *)(arg0 + 0x3C) - *(f32 *)(arg0 + 0x170);
    if (d < 0.0f) {
        return 0;
    }
    b = *(s16 *)(arg0 + 0x64) * 4;
    if (b >= 0x100) {
        b = 0xFF;
    }
    c = (s32)d >> 1;
    if (c >= 0x100) {
        c = 0xFF;
    }
    a = (c < b) ? c : b;
    if (a < 0) {
        return 0;
    }
    arg0[0x70] = a;
    return 1;
}

void func_1518B7D4(s32 arg0, f32 arg1, f32 arg2, s32 arg3, u8 arg4) {
    func_1518B818(arg0, arg1, arg2, arg3, 4, 0xFF, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B8AA0/func_1518B818.s")
