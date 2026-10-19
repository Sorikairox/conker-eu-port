#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15100B80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15101610.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_151016C8.s")

void func_15101768(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x124) + 0x110;
    *(s32 *)(p + 0x28) = 0;
    func_1513CA6C(arg0);
}

void func_15101790(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x124) + 0x110;
    *(s32 *)(p + 0x28) = 0;
    func_1513CAA0(arg0);
}

void func_151017B8(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x18) + 0x110;
    *(s32 *)(p + 0x2C) = 0;
    func_151617C4(arg0);
}

void func_151017E0(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x18) + 0x110;
    *(s32 *)(p + 0x2C) = 0;
    func_151617E4(arg0);
}

void func_15101808(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0xD0) + 0x110;
    *(s32 *)(p + 0x24) = 0;
    func_15131CAC(arg0);
}

void func_15101830(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0xD0) + 0x110;
    *(s32 *)(p + 0x24) = 0;
    func_15131CCC(arg0);
}

void func_15101858(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x170) + 0x110;
    *(s32 *)(p + 0x30) = 0;
    func_151411A4(arg0);
}

void func_15101880(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x170) + 0x110;
    *(s32 *)(p + 0x30) = 0;
    func_151411C4(arg0);
}

void func_151018A8(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0xA8) + 0x110;
    *(s32 *)(p + 0x34) = 0;
    func_15131CAC(arg0);
}

void func_151018D0(struct210 *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0xA8) + 0x110;
    *(s32 *)(p + 0x34) = 0;
    func_15131CCC(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_151018F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15101F44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_151024D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_1510282C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15102B74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_12E390/func_15102C3C.s")

void func_151027E8(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151403A8(&tmp, 0x1A);
}

s32 func_15102D9C(u8 *arg0, s16 arg1) {
    u8 *p;
    u8 *q;
    p = *(u8 **)(arg0 + 0xD0);
    if (arg1 == p[0x132]) {
        p = p + 0x110;
        if (!arg0 && !arg0 && !arg0) {} // fakematch: permuter artifact, hoists the +0x110 above the compare
        q = *(u8 **)p;
        if (q == NULL || (*(u8 **)(q + 0x31C))[0x197] != 0) {
            return 0;
        }
    }
    if (!(arg0[0xD4] & 1)) {
        return 0;
    }
    return 1;
}

s32 func_15102E04(u8 *arg0, s32 arg1) {
    s32 ret = 1;
    if (!(arg0[0xAC] & 1)) {
        return 0;
    }
    return ret;
}

s32 func_15102E2C(u8 *arg0, s16 arg1) {
    u8 *p;
    u8 *q;
    p = *(u8 **)(arg0 + 0x170);
    if (arg1 == p[0x132]) {
        p = p + 0x110;
        if (!arg0 && !arg0 && !arg0) {} // fakematch: permuter artifact, hoists the +0x110 above the compare
        q = *(u8 **)p;
        if (q == NULL || (*(u8 **)(q + 0x31C))[0x197] != 0) {
            return 0;
        }
    }
    if (!(arg0[0x174] & 1)) {
        return 0;
    }
    return 1;
}
