#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D87C0(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D87CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D88E8.s")

s16 *func_150D8AA0(s16 *arg0, s32 arg1) {
    arg0[0] = 0x42;
    arg0[1] = 0;
    return arg0 + 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D8ABC.s")

s32 func_150D8DBC(u8 *arg0) {
    if ((*(u8 **)(arg0 + 0x18))[0x6F] != 0) {
        (*(u8 **)(arg0 + 0x14))[9] = 0;
    } else {
        (*(u8 **)(arg0 + 0x14))[9] = 1;
    }
    return 1;
}

s32 func_150D8DF0(f32 *arg0, u8 *arg1, u8 arg2) {
    s32 idx;
    f32 x;
    f32 y;
    f32 z;

    switch (arg2) {
    case 3:
        idx = 0x12;
        x = -7.0f;
        z = 30.0f;
        break;
    case 4:
        idx = 0x15;
        x = -4.0f;
        z = 35.0f;
        break;
    case 5:
        idx = 0xF;
        x = 5.0f;
        z = 20.0f;
        break;
    case 6:
        idx = 0x18;
        x = 5.0f;
        z = 31.0f;
        break;
    }
    y = 0.0f;
    func_150A7E40((f32 (*)[4]) (*(u8 **)(arg1 + 0x1D4) + (idx << 6)), x, 0.0f, z, &x, &y, &z);
    arg0[0] = x;
    arg0[1] = y;
    arg0[2] = z;
    return 1;
}

s32 func_150D8F30(s32 arg0, s32 arg1) {
    return 8;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105FD0/func_150D8F44.s")
