#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B70A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7170.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7214.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7258.s")

void func_150B72DC(u8 *arg0) {
    *(s16 *)(arg0 + 0x34) += D_800BE9E4 * 0x30;
    if (*(s16 *)(arg0 + 0x34) > 0x800) {
        *(s16 *)(arg0 + 0x34) = -0xC00;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B731C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B757C.s")

void func_150B7688(u8 *arg0) {
    if (*(s16 *)(arg0 + 0x38) != 0x1000) {
        *(s16 *)(arg0 + 0x38) += D_800BE9E4 << 8;
        if (*(s16 *)(arg0 + 0x38) > 0x1000) {
            *(s16 *)(arg0 + 0x38) = 0x1000;
        }
    } else if (*(s16 *)(arg0 + 0x3A) != 0x1000) {
        *(s16 *)(arg0 + 0x3A) += D_800BE9E4 << 8;
        if (*(s16 *)(arg0 + 0x3A) > 0x1000) {
            *(s16 *)(arg0 + 0x3A) = 0x1000;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B78D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7964.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7A40.s")

void func_150B7B3C(void) {
    func_150B7B9C(0x3C, 1);
    D_800D9CB0 = 3;
}

void func_150B7B6C(void) {
    func_150B7B9C(0xE6, 2);
    D_800D9CB0 = 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7B9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E48B0/func_150B7DFC.s")
