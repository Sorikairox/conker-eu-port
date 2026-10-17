#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_151D8D90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_151D8E18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_eu_151D8FD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_151D90D4.s")

void func_151D9138(void *arg0) {
    func_151D90D4(arg0);
    func_15169804(arg0);
}

void func_151D9164(void *arg0) {
    func_151D90D4(arg0);
    func_15169824(arg0);
}

void func_151D9190(u8 *arg0) {
    func_151D91B0(arg0, arg0 + 0x18);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_151D91B0.s")

void func_151D930C(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x58) {
        func_1516972C(arg0);
    } else if (arg2 == 0x47) {
        func_1516972C(arg0);
    }
}

void func_151D9364(s32 arg0, u8 arg1) {
    func_15169260(&D_800AB6E0, 1, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_2065A0/func_151D9398.s")
