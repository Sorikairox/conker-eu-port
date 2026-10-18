#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F500.s")

void func_1519F678(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    func_15147E64(arg0);
}

void func_1519F6D8(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F738.s")

s32 func_1519F738(s32, s32);
void func_1519F928(u8 *arg0) {
    s32 *p = (s32 *)(arg0 + 0x58);
    p[0] = func_1519F738(arg0, 6);
    p[1] = 0;
    p[2] = func_1519F738(arg0, 7);
    p[3] = 0;
}

void func_151A0E98(u8 *);
void func_1519F9FC(u8 *);

void func_1519F970(u8 *arg0) {
    u8 *v = arg0 + 0x58;

    if (*(s32 *)(arg0 + 0x58) != 0) {
        func_1519F9FC(*(u8 **)(arg0 + 0x58));
    }
    if (*(u8 **)(v + 8) != NULL) {
        func_1519F9FC(*(u8 **)(v + 8));
    }
    if (*(u8 **)(v + 4) != NULL) {
        func_151A0E98(*(u8 **)(v + 4));
        func_1516972C(*(struct102 **)(v + 4));
    }
    if (*(u8 **)(v + 0xC) != NULL) {
        func_151A0E98(*(u8 **)(v + 0xC));
        func_1516972C(*(struct102 **)(v + 0xC));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F9FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519FA60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519FD60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A03DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A0DBC.s")

void func_151A0E98(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x28) + 0x58;
    if (arg0[0x2C] == 6) {
        *(s32 *)(p + 4) = 0;
    } else {
        *(s32 *)(p + 0xC) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A0EC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A0F5C.s")
