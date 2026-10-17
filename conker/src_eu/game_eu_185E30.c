#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158620.s")

void func_15158620(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);

void func_15158748(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    func_15158620(arg0, 0, 0, arg1, arg2, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158838.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158AFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158BF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158E90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158F90.s")

void func_15159014(void *arg0) {
    func_15158F90(arg0);
    func_15169804(arg0);
}

void func_15159040(void *arg0) {
    func_15158F90(arg0);
    func_15169824(arg0);
}

s32 func_1515906C(u8 *arg0) {
    s32 temp_v1;
    if (*(s16 *)(arg0 + 0x14) < *(s16 *)(arg0 + 0xF8)) {
        temp_v1 = *(s32 *)(arg0 + 0xFC) * *(s16 *)(arg0 + 0x14);
        if (temp_v1 < arg0[0x3B]) {
            arg0[0x3B] = temp_v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_151590AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15159140.s")

void func_15159244(void **arg0) {
    func_1514EDF0(arg0, arg0[0x18 / 4]);
    func_15169804(arg0);
}

void func_15159270(void **arg0) {
    func_1514EDF0(arg0, arg0[0x18 / 4]);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515929C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15159514.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_151595F4.s")

s32 func_15159690(u8 *arg0, u8 arg1) {
    s32 r;
    if (arg1 == 2 || arg1 == 3) {
        r = 1;
    } else if (*(f32 *)(arg0 + 0x180) < *(f32 *)(arg0 + 0x118) - 35.0f) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_151596F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_151597A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15159828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_151598E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515999C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15159B04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15159C2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15159E00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515A120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515A178.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515A68C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515A7A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515AB7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515ACFC.s")

s32 func_1515AE90(u8 *arg0, u8 **arg1) {
    struct_eu_link *sp1C;
    u8 *temp_v1;

    if (func_1514F250(*(struct_eu_link **)(arg0 + 0x2F4), 0x13, &sp1C) == 0) {
        return 0;
    }
    temp_v1 = (u8 *)sp1C->unk10;
    *arg1 = temp_v1 + 0x34;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515AEE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515AFF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_1515B0F8.s")
