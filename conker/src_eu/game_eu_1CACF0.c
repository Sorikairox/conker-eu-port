#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D4E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D510.s")

void func_1519D540(u8 *arg0) {
    s32 *p = *(s32 **)(arg0 + 0x98);
    func_1514EDF0(arg0, *p);
    func_15147E64(arg0);
}

void func_1519D570(u8 *arg0) {
    s32 *p = *(s32 **)(arg0 + 0x98);
    func_1514EDF0(arg0, *p);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D5A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D7B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D9C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519DF64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E874.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E92C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E9D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519EAE0.s")

void func_1519EB8C(struct102 *arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0) || (arg2 == 9)) {
        func_1516972C(arg0);
    }
}

void func_1519EBCC(s32 arg0) {
    func_1519D4E0(3);
    func_1519D4E0(4);
}

void func_1519E688(void) {
    func_1519D4E0(3);
    func_1519D4E0(4);
    func_151482D4(0, 9);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E6BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519ECC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519ED88.s")

void func_1519EE3C(struct260 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_1514933C(arg0);
}

void func_1519EE68(struct260 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_15149368(arg0);
}

void func_1519EE94(struct260 *arg0) {
    D_800E0D50 = 0;
    func_1514933C(arg0);
}

void func_1519EEB8(struct260 *arg0) {
    D_800E0D50 = 0;
    func_15149368(arg0);
}
