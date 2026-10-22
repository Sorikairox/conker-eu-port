#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1504715C(s32, u8 *);
s32 func_15046F70(f32 *, s32, f32, s32);
s32 func_15142314(s32, s32, f32 *);

s32 func_150BEEB0(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 var_a1;

    switch (arg3) {
    case 4:
        var_a1 = 0x17;
        break;
    case 5:
        var_a1 = 0x14;
        break;
    case 6:
        var_a1 = 0xC;
        break;
    case 7:
    default:
        var_a1 = 0x10;
        break;
    }
    func_15142314(*(s32 *)(arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 10.0f;
    sp2C[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046F70(sp2C, 0, arg0[1] - 50.0f, arg2);
}

s32 func_150BEFA8(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x11;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EC6C0/func_150BEFCC.s")


s32 func_150BF130(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 var_a1;

    switch (arg3) {
    case 4:
        var_a1 = 0x19;
        break;
    case 5:
        var_a1 = 0x16;
        break;
    case 6:
        var_a1 = 0xC;
        break;
    case 7:
    default:
        var_a1 = 0x10;
        break;
    }
    func_15142314(*(s32 *)(arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 10.0f;
    sp2C[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046F70(sp2C, 0, arg0[1] - 50.0f, arg2);
}

s32 func_150BF228(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x12;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EC6C0/func_150BF24C.s")

#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);
#else
s32 func_1509BE40(s32, s32, s32, s32);
#endif

void func_150BF3B0(u8 *arg0) {
    if ((func_1509BE40(1, 0x4063, 6, 0x2000) != 0) || (func_1509BE40(1, 0x4001, 6, 0x9000) != 0)) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x1010);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x1010);
    }
    if (func_1509BE40(1, 0x4069, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x01000000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFEFFFFFF);
}
