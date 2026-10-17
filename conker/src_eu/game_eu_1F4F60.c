#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C7750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C7B1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8448.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8880.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8C24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8C5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8D5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8D90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C8F4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C957C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9748.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9A84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9B88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9C8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9CBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151C9740.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CA070.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CA0E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CA114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CA150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CA398.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CA484.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CA4E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CAC50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CB07C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CB128.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CB2D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CB6C0.s")

void func_151CBA4C(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x18) == *arg1) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x18) == *(u8 **)(p + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CBAC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CBBAC.s")

void func_151CBEC8(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = arg0 + 0x70;
    if ((arg2 == 0x37) && (arg1[0] == temp_v0[0xE]) && (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0)) {
        *(f32 *)(temp_v0 + 0x10) = 0.0f;
        temp_v0[0xC] |= 1;
        *(f32 *)(temp_v0 + 0x14) = 0.0f;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CBF20.s")

void func_151CC11C(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x20) == *arg1) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x20) == *(u8 **)(p + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CC190.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CC210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CC784.s")

void func_151CC840(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_15155C9C((f32 *) &sp1C, 0x46);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CC86C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CCAD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CCD2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CCDF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CD2CC.s")

s32 func_151A5580(s32, s32, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, u8 **, s32);

void func_151CD444(u8 *arg0) {
    s32 temp_v0;
    u8 *sp28;

    if (D_800BE616 != 0) {
        sp28 = arg0;
        temp_v0 = func_151A5580(0, 0, 0, 0xFF, 0, (s32) (*(u8 *)((u8 *)arg0 + 0x23D)), 1, 4);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x20, &sp28, 4);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CD4B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F4F60/func_151CD7D4.s")
