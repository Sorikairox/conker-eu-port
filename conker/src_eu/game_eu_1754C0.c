#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1754C0/func_15147CB0.s")

void func_15147E40(u8 *arg0) {
    func_151D5E30(arg0 + 0x84, arg0);
}

void func_15147E64(void *arg0) {
    func_15147E40(arg0);
    func_15147ECC(arg0);
    func_15169804(arg0);
}

void func_15147E98(void *arg0) {
    func_15147E40(arg0);
    func_15147ECC(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1754C0/func_15147ECC.s")

void func_15147F50(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x20);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 20) {
        idx = 0;
    }
    D_8008A690[idx]();
}

void func_15147FA0(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x20);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 20) {
        idx = 0;
    }
    D_8008A6E0[idx]();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1754C0/func_15147FF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1754C0/func_151481BC.s")

void func_1514828C(u8 *arg0, s32 arg1, u8 arg2) {
    void (*func)(void *, s32, u8) = D_8008A730[*(s32 *)(arg0 + 0x20)];

    if (func != NULL) {
        func(arg0, arg1, arg2);
    }
}

void func_151482D4(s32 arg0, u8 arg1) {
    func_15169260((s32)D_800A5B40, 2, arg0, arg1);
}
