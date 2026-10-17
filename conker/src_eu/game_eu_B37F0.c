#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15085FE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086058.s")

s32 func_15086218(f32 arg0) {
    s32 i = 0;

    while (D_800D2788[i] <= arg0) {
        i++;
    }
    return D_800D2770[i];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086268.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086508.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150867D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087040.s")

void func_150870E0(s32 arg0) {
    s32 temp_v1 = D_800D2778[arg0].unk4;

    func_150A3674(3, 0xB, D_800D2778[arg0].unk0, D_800D2778[arg0].unk2, temp_v1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_1508712C.s")

s32 func_150871B8(s32 arg0) {
    s32 i;

    for (i = 0; i < D_80087630; i++) {
        if (arg0 == D_800D2778[i].unk7) {
            return i;
        }
    }
    return 0xFF;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087204.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150877C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_1508823C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150882C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088360.s")

void func_15088434(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;

    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        temp_v1->unk31 = arg1;
    }
}

void func_1508845C(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;

    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        temp_v1->unk4 = arg1 * (1.0f / 256);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_1508849C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088568.s")

s32 func_1508863C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk0 * 256.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088688.s")

s32 func_150886E0(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk14 * D_8009DDD0;
}

s32 func_1508872C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk27;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_1508882C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150889D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088B08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088BFC.s")

s32 func_15088C74(void) {
    if (D_80087640 == NULL) {
        return 0;
    }
    return D_80087640->unk46 == 0xFF;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088CA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088D24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088E84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150891D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150893AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150894F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089664.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089B68.s")
