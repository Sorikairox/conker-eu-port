#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506A9B0.s")

void func_1506AABC(s32 arg0, s32 arg1) {
    func_150E08C8(arg0, 0xFF, 1);
}

void func_1506AAE4(s32 arg0, s32 arg1) {
    func_151BBBCC(arg0, D_800D1980, D_eu_800D1990, 0xFF, 1);
}

void func_1506AB20(s32 arg0, s32 arg1) {
    func_151BC04C(arg0, D_800D1980, D_eu_800D1990, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506AB5C.s")

void func_1506ABFC(s32 arg0, s32 arg1) {
    func_151BC6B4(arg0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506AC24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506AD28.s")

void func_1506ADC8(s32 arg0, s32 arg1) {
    func_151B76F4(arg0, 0xFF, 1);
    func_151B68D0(arg0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506AE08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506AEA0.s")

void func_1506AF3C(struct127 *arg0, u8 *arg1) {
    func_151043C0(arg0, *(struct127 **)arg1, (f32 *)(arg1 + 4), 1, *(s32 *)(arg1 + 0x10), 0xFF, 1);
}

void func_1506AF84(struct127 *arg0, u8 *arg1) {
    func_151043C0(arg0, *(struct127 **)arg1, (f32 *)(arg1 + 4), 2, *(s32 *)(arg1 + 0x10), 0xFF, 1);
}

void func_1506AFCC(u8 *arg0, s32 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151B78D8(&tmp, 0, 8, 0xFF, 1);
}

void func_1506B018(s32 arg0, s32 arg1) {
    func_151CF05C(arg0, 0, 1, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506B04C.s")
