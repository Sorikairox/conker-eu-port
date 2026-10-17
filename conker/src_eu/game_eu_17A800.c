#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514CFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514D6CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514D880.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514D3B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DA28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DAD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DBBC.s")

void func_1514DEDC(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DEE8.s")

void func_1514DF64(struct127 *arg0) {
    func_1514DEE8(arg0);
    func_1514F18C(func_151AD010(arg0, 0x41A00000, 0), arg0, 0x14);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514DFA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E014.s")

void func_1514E088(struct127 *arg0) {
    s32 temp_v0 = func_15159140(arg0, 1, 0);
    if (temp_v0 != 0) {
        func_1514F18C(temp_v0, arg0, 0x13);
    }
}

void func_1514E0C8(s32 arg0) {
}

void func_1514E0D4(void) {
    if (D_800BE9F0 == 0x14) {
        func_151B2610();
    }
}

void func_1514E108(void) {
    func_1514F704();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E128.s")

void func_1514E1A8(struct127 *arg0) {
    func_1500EE18(arg0, 0xFF, 1);
}

void func_1514E1CC(s32 arg0) {
    func_151D1510(arg0, 0, 0xFF, 1);
}

void func_1514E1F4(u8 *arg0) {
    *(s32 *)(arg0 + 0x94) |= 2;
}

void func_1514E208(u8 *arg0) {
    *(s32 *)(arg0 + 0x94) |= 0x710;
}

void func_1514E21C(struct127 *arg0) {
    *(s32 *)((u8 *)arg0 + 0x9C) = 0x6000;
    func_15083568(arg0, 0x23, 1.0f, 0);
    func_15083568(arg0, 0x44, 1.0f, 0);
}

void func_1514E264(struct127 *arg0) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x31C);
    if (v != NULL) {
        v[0x94] = 1;
    }
    func_15083568(arg0, 0x17, 1.0f, 0);
}

void func_1514E29C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2BC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2DC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E2FC(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E31C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E33C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E35C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E37C(struct127 *arg0) {
    func_1514E21C(arg0);
}

void func_1514E39C(s32 arg0) {
}

void func_1514E3A8(s32 arg0) {
}

void func_1514E3B4(s32 arg0) {
}

void func_1514E3C0(struct127 *arg0) {
    if (((u8 *)D_800D2E4C)[0x11] & 8) {
        func_1514E21C(arg0);
    }
}

void func_1514E3F8(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E404.s")

void func_1514E540(u8 *arg0) {
    arg0[0x65] = func_15083FB0(9, arg0) + 1;
    arg0[0x101] |= 0x34;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E57C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514E88C.s")

u8 *func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u8 *func_1518D1C0(struct127 *, s32, s32, s32, s32, s32, u8 *);

void func_1514EA78(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CB0), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EB28(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CC4), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EBD8(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CD8), arg0, 0xD);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}


void func_1514EC88(struct127 *arg0) {
    f32 *temp_v1;

    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5CEC), arg0, 0xE);
    temp_v1 = &arg0->x_position;
    func_1514F18C(func_1515D5F8(-0x8000, (s32) temp_v1 >> 0x10, (s32) temp_v1 & 0xFFFF, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0), arg0, 0x18);
}

void func_1514ED38(struct127 *arg0) {
    func_1514F18C(func_1518D1C0(arg0, 7, 0, 1, 0xFF, 1, D_800A5D00), arg0, 0xF);
}

void func_1514ED94(s32 arg0) {
}

void func_1514EDA0(struct102 *arg0) {
    func_1516972C(arg0);
}

void func_1514EDC0(struct102 *arg0) {
    func_1518E878(arg0);
    func_1516972C(arg0);
}

void func_1514EDEC(void) {
    func_1515F10C();
}

s32 func_1514EE0C(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0:
        if (*(s32 *)(arg0 + 0x10) & 1) {
            *(s32 *)(arg0 + 0x10) &= ~1;
        } else {
            *(s32 *)(arg0 + 0x10) |= 1;
        }
        break;
    case 2:
        *(s32 *)(arg0 + 0x10) &= ~1;
        break;
    case 1:
        *(s32 *)(arg0 + 0x10) |= 1;
        break;
    default:
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514EE90.s")

s32 func_1514EF4C(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE90(arg0, arg1, arg2);
}

s32 func_1514EF6C(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE0C(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514EF8C.s")

s32 func_1514F0DC(u8 *arg0, s32 arg1, s32 arg2) {
    return func_1514EE0C(arg0, arg1, arg2);
}

s32 func_1514F0FC(s32 arg0, s32 arg1, s32 arg2) {
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F18C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F2AC.s")

s32 func_1514F2FC(u8 *arg0, u8 *arg1) {
    s32 sp1C;
    if (arg0 == *(u8 **)(arg1 + 0x2F4)) {
        *(u8 **)(arg1 + 0x2F4) = *(u8 **)(arg0 + 0x14);
    }
    if (*(u8 **)(arg0 + 0x14) != NULL) {
        *(u8 **)(*(u8 **)(arg0 + 0x14) + 0x18) = *(u8 **)(arg0 + 0x18);
    }
    if (*(u8 **)(arg0 + 0x18) != NULL) {
        *(u8 **)(*(u8 **)(arg0 + 0x18) + 0x14) = *(u8 **)(arg0 + 0x14);
    }
    sp1C = *(s32 *)(arg0 + 0x10);
    func_1516972C(arg0);
    return sp1C;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514EDF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F3E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F43C.s")

void func_1514F680(void) {
    func_1514F704();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F6A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514F878.s")

void func_1514F93C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x3A, -1, 0, 0x2B, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

void func_1514F9BC(struct127 *arg0) {
    func_1514F18C(func_1518D1C0(arg0, 5, 0, 1, 0xFF, 1, D_800A5D68), arg0, 0xD);
}

void func_1514FA18(s32 arg0) {
    func_151D7A60(arg0, 1, -1, 0xFF, 1);
}

void func_1514FA48(s32 arg0) {
    func_151D7A60(arg0, 2, 1, 0xFF, 1);
}

void func_1514FA78(s32 arg0) {
    func_151D7A60(arg0, 3, 0, 0xFF, 1);
}

void func_1514FAA8(s32 arg0) {
    func_151D7A60(arg0, 4, -1, 0xFF, 1);
}

void func_1514FAD8(s32 arg0) {
    func_150C4620(arg0, -1, 0xFF, 1);
}

void func_1514FB00(struct127 *arg0) {
    func_1501175C(arg0, 0xFF, 1);
    func_15011A78(arg0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_17A800/func_1514FB3C.s")
