#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_15149AC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_15149DA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A164.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A1C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A288.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A434.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A70C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A8F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AA08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AA5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AB04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514AC10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B30C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B4E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B5A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514B8D4.s")

s32 func_1514BDB4(u8 *arg0) {
    u8 *temp_v0;
    s16 temp_v1;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C);
    if (temp_v1 < 16) {
        if ((temp_v1 << 4) < temp_v0[0x1B]) {
            temp_v0[0x1B] = temp_v1 << 4;
        }
    }
    return 1;
}

s32 func_1514BDEC(f32 *arg0) {
    f32 temp_f0 = arg0[0x4C / 4] * D_800BE9A4;
    arg0[0x2C / 4] += temp_f0;
    arg0[0x30 / 4] += temp_f0;
    return 1;
}

s32 func_1514BE20(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    if (temp_v0 < 16) {
        if ((temp_v0 << 4) < arg0[0x5C]) {
            arg0[0x5C] = temp_v0 << 4;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514BE54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C178.s")

void func_1514C370(u8 *arg0) {
    func_1514C178(arg0, arg0 + 0x110);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C390.s")

void func_1514C4C0(f32 *arg0) {
    arg0[0x40 / 4] = arg0[0x34 / 4];
    arg0[0x44 / 4] = arg0[0x38 / 4] + 100.0f;
    arg0[0x48 / 4] = arg0[0x3C / 4];
}

void func_1514C4EC(u8 *arg0) {
    func_1514C178(arg0, arg0 + 0x110);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C50C.s")

s32 func_1514C7C8(void *arg0) {
    func_1514C50C(arg0);
    func_1514C390(arg0);
    return 1;
}

s32 func_1514C7F8(void *arg0) {
    func_1514C50C(arg0);
    func_1514C4C0(arg0);
    return 1;
}

s32 func_1514C828(u8 *arg0) {
    arg0[0x72] = 0;
    arg0[0x71] = 0x24;
    *(s16 *)(arg0 + 0x1C) = *(s16 *)(arg0 + 0x164);
    *(s32 *)(arg0 + 0x58) |= 0x08000000;
    *(f32 *)(arg0 + 0x154) = *(f32 *)(arg0 + 0x160);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C860.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514C9E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514CBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514CDC8.s")
