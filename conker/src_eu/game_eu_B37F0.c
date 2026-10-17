#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *func_1502B5C8(s32, s32, s32, s32);
s32 func_15086058();
extern s16 D_80087634;

void func_15085FE0(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = func_1502B5C8(0, 2, 0x19, arg0);
    if (temp_v0 == NULL) {
        D_80087630 = 0;
        D_80087634 = 0;
        D_800D2778 = NULL;
    } else {
        D_80087630 = (*(s16 *)temp_v0);
        D_80087634 = (*(s16 *)((u8 *)temp_v0 + 2));
        D_800D2778 = temp_v0 + 4;
    }
    func_15086058();
}

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

s32 func_1508712C(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if ((arg0 < 0) || (arg0 >= D_80087630)) {
        return 0;
    }
    *arg1 = (f32) D_800D2778[arg0].unk0;
    *arg2 = (f32) D_800D2778[arg0].unk2;
    *arg3 = (f32) D_800D2778[arg0].unk4;
    return 1;
}

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

s32 func_1508849C(struct_eu_80087640 *, struct127 *, s32, s32);
extern s8 D_800D27BA;

s32 func_15088568(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_a0;
    struct127 *temp_a1;
    s8 temp_v1;
    s32 var_a2;
    struct_eu_80087640 *sp1C;

    var_a2 = 0;
    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    temp_v1 = (s8) temp_a0->pad28[8];
    temp_a1 = &D_800CC2D0[(s8) temp_a0->unk31];
    if (temp_v1 == 0) {
        sp1C = temp_a0;
        var_a2 = func_1508849C(temp_a0, temp_a1, arg1, arg0);
    } else if (temp_v1 == 1) {
        temp_a0->pad28[8] = 2;
        temp_a1->immune = 0xFF;
    }
    temp_a0->pad28[2] = (u8) D_800D27BA;
    D_800D27BA += 1;
    return var_a2;
}

s32 func_1508863C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk0 * 256.0f;
}

s32 func_15088688(s32 arg0) {
    struct_eu_80087640 *temp_a0;
    s16 temp_a2;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    temp_a2 = temp_a0->unk24;
    return (temp_a2 * 16) + (s32)(temp_a0->unk8 * 16.0f);
}

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

s32 func_150889D8();
extern s32 D_800D27B4;
extern s8 D_800D27B8;

void func_15088BFC(void) {
    s32 temp_v0;

    if (D_80087640 != NULL) {
        temp_v0 = func_150889D8();
        D_80087640[temp_v0].unk31 = 0;
        D_800D27B4 &= ~(1 << (temp_v0 - D_800D27B8));
    }
}

s32 func_15088C74(void) {
    if (D_80087640 == NULL) {
        return 0;
    }
    return D_80087640->unk46 == 0xFF;
}

void func_15088CA0(u8 *arg0) {
    (*(s8 *)((u8 *)arg0 + 0x2B)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2C)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x28)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x20)) = -1;
    (*(s8 *)((u8 *)arg0 + 0x2F)) = 0;
    (*(f32 *)((u8 *)arg0 + 8)) = 0.0f;
    (*(f32 *)arg0) = 0.5f;
    (*(f32 *)((u8 *)arg0 + 4)) = 0.5f;
    (*(s16 *)((u8 *)arg0 + 0x24)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x26)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x27)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x31)) = 0;
    (*(f32 *)((u8 *)arg0 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x14)) = 0.0f;
    (*(s8 *)((u8 *)arg0 + 0x33)) = 2;
    (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2A)) = 0x7F;
    (*(s8 *)((u8 *)arg0 + 0x49)) = 0;
    (*(f32 *)((u8 *)arg0 + 0x10)) = 1.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088D24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088E84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150891D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150893AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150894F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089664.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089B68.s")
