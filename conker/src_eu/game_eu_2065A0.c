#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_800BED64[];
s32 func_151D8D90(u8 arg0) {
    u8 i;
    u8 t;
    for (i = 0; i < 4; i++) {
        if (arg0 & (1 << i)) {
            t = D_800843F0[i];
            if (t >= 4) {
                return 0;
            }
            if (D_800BED64[t] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

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

extern s8 D_eu_800E0E30;

void func_151D9398(void) {
    D_eu_800E0E30 = 1;
    func_151D9364(0, 0x58U);
}
