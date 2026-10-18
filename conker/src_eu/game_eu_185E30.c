#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15158F90(u8 *arg0);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158620.s")

s32 func_15158620(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);

void func_15158748(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    func_15158620(arg0, 0, 0, arg1, arg2, arg3, arg4);
}

extern s32 (*D_8008B1A0[])(void);
void func_15158794(u8 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0[0x10] & 1) != 0) {
        *(s16 *)(arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x14) < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (*(s8 *)(arg0 + 0x12) != -1) && (D_8008B1A0[*(s8 *)(arg0 + 0x12)]() == 0)) {
        ret = 1;
    }
    if (ret) {
        func_1516972C(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158838.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158AFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158BF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_185E30/func_15158E90.s")

void func_15158F90(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0xE0))[i]) {
            func_100043B4(((s32 *)(arg0 + 0xE0))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0xF0) != 0) {
        func_100043B4(*(s32 *)(arg0 + 0xF0), 4);
    }
}

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
