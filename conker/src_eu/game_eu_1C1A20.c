#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194210.s")

void func_151942B0(s32 arg0, s32 arg1, s32 arg2) {
    func_15194210(arg1, 0, 0xFF, 1);
}

void func_15194858(s32 arg0, s32 arg1, s32 arg2) {
    func_15194210(arg1, 1, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194890.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194904.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194978.s")

void func_15194AF8(struct127 *arg0, struct127 *arg1, s32 arg2) {
    func_150C7520(arg0, 500, 0xFF, 1);
    func_15194978(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194B3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194D80.s")

void func_15194F50(s32 arg0, s32 arg1, s32 arg2) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15194F64.s")

void func_15194FD8(s32 arg0, s32 arg1, s32 arg2) {
    func_1507DE4C(arg1);
    func_15138BC0(arg1, 0xFF, 1);
    func_15194F64(0, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195024.s")

s32 func_15134070(s32);
s32 func_15136C3C(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15138120(s32, s32, s32);
s32 func_15195024(s32);

void func_1519508C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_15134070(arg0);
    if (temp_v0 != 0x63) {
        func_15138120(arg0, temp_v0, 0);
    }
    func_15136C3C(arg0, 1, 1, 1, 1, 1, 0xFF, 1);
    func_15195024(arg0);
}

void func_15195104(s32 arg0, u8 *arg1, s32 arg2) {
    if (arg1[4] == 0x53) {
        func_151942B0(arg0, arg1, arg2);
    } else {
        func_1519508C(arg1);
        func_15194F64(1, arg0, arg1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195160.s")

void func_151952F0(s32 arg0, s32 arg1, s32 arg2) {
    func_15195564(arg0, arg1, 0);
}

void func_15195314(s32 arg0, s32 arg1, s32 arg2) {
    func_15195564(arg0, arg1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195338.s")

void func_151953C4(s32 arg0, u8 *arg1, s32 arg2) {
    u8 v = arg1[4];

    if ((v == 0x3E) || (v == 0xA6)) {
        func_150B0B90(arg1, arg0, 0xFF, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195418.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_151954B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195564.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195A98.s")

void func_15195BC0(s32 arg0, s32 arg1, s32 arg2) {
    func_151B01B8(arg0, arg1);
    func_151B09BC(arg0, arg1, 1000, 0xFF, 0);
}

s32 func_1507CD64(struct127 *, s32);

void func_15195C08(u8 *arg0, struct127 *arg1, s32 arg2) {
    if ((arg1->health == 0) && (arg1->unk127 != 0xFF)) {
        func_15136C3C((s32) arg1, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50(arg1);
        func_1507CD64(arg1, 6);
    }
    if ((*(u8 *)((u8 *)arg0 + 4)) == 0x47) {
        (*(s8 *)((u8 *)arg0 + 0x1CA)) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1A20/func_15195CA8.s")
