#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_15149AC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_15149DA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A164.s")

s32 func_1514A1C8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x2C));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x150));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x30));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (temp_f0 - (temp_f0 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (temp_f12 - (temp_f12 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0x50)) += ((*(f32 *)((u8 *)arg0 + 0x4C)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg0 + 0x50)) * D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x15C)) < (*(f32 *)((u8 *)arg0 + 0x38))) {
        return 0;
    }
    if (((*(f32 *)((u8 *)arg0 + 0x2C)) < 4.0f) || ((*(f32 *)((u8 *)arg0 + 0x30)) < 4.0f)) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A288.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A434.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A70C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1772D0/func_1514A8F0.s")

typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0xE];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x28];
    u8 unk5C;
    u8 pad5D[0xE7];
    f32 unk144;
    u8 pad148[0xE];
    s16 unk156;
    s16 unk158;
} struct_1514AA08;

s32 func_1514AA08(struct_1514AA08 *arg0) {
    arg0->unk30 -= arg0->unk30 * arg0->unk144;
    arg0->unk2C -= arg0->unk2C * arg0->unk144;
    if (arg0->unk1C < arg0->unk156) {
        arg0->unk5C = arg0->unk1C * arg0->unk158;
    }
    return 1;
}

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
