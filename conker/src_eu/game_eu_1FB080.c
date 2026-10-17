#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CD2C0.s")

void func_151CD90C(s32 arg0) {
    s32 tmp;
    if ((arg0 >= 0) && (arg0 < 4)) {
        tmp = arg0;
        func_151494E0(&tmp, 0x17);
    }
}

void func_151CD944(s32 arg0) {
    s32 tmp;
    if ((arg0 >= 0) && (arg0 < 4)) {
        tmp = arg0;
        func_151494E0(&tmp, 0x18);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CD97C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDA70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDC24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDD6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CE144.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CE3D0.s")

void func_151CEA2C(u8 *arg0) {
    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= ~2;
    *(u16 *)(arg0 + 0x1E) |= 8;
}

void func_151CEA4C(u8 *arg0) {
    s32 tmp;
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    tmp = *(s32 *)(temp_v0 + 0x48);
    func_151494E0(&tmp, 0x23);
    func_15147E64(arg0);
}

void func_151CEA8C(u8 *arg0) {
    s32 tmp;
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    tmp = *(s32 *)(temp_v0 + 0x48);
    func_151494E0(&tmp, 0x23);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEACC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEBE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEC80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEFD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF05C.s")

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} struct_151CF1C0;

s32 func_151CF1C0(struct_151CF1C0 *arg0, u8 *arg1, u8 *arg2) {
    if (arg2 != NULL) {
        *arg0 = *(struct_151CF1C0 *)(arg2 + 0x40);
    } else {
        arg0->x = ((struct_151CF1C0 *)(arg1 + 0x14))->x;
        arg0->y = ((struct_151CF1C0 *)(arg1 + 0x14))->y;
        arg0->z = ((struct_151CF1C0 *)(arg1 + 0x14))->z;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF204.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF6D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF930.s")

void func_151CFDF4(u8 *arg0, s32 arg1, u8 arg2) {
    s32 *temp_t7;
    s32 *sp24;

    temp_t7 = (*(s32 **)((u8 *)arg0 + 0x98));
    sp24 = temp_t7;
    if (*temp_t7 != 0) {
        func_15169850(arg1, arg2, (s32) temp_t7, (s32) temp_t7 + 4, (s32) arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CFE48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CFFFC.s")

void func_151D0024(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x18);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D0058.s")

void func_151D06D8(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);
    if (*(u16 *)(temp_v0 + 0x84) != *(u16 *)(arg0 + 0x2E)) {
        *(s16 *)(arg0 + 0xE) = -1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D06FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D0EA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D09A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1488.s")

void func_151D14B8(void *arg0) {
    func_151D1488(arg0);
    func_15131CAC(arg0);
}

void func_151D14E4(void *arg0) {
    func_151D1488(arg0);
    func_15131CCC(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1510.s")

s32 func_151D1624(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[0x14 / 4];
    arg1[1] = arg0[0x180 / 4] + 8.0f;
    arg1[2] = arg0[0x1C / 4];
    return 1;
}

void func_151D1654(s32 arg0, s32 arg1) {
    func_151D1694(arg0, arg1, 0);
}

void func_151D1674(s32 arg0, s32 arg1) {
    func_151D1694(arg0, arg1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1694.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D16E8.s")

void func_151D18D8(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_151D1918(void *arg0) {
    func_151D1990(arg0);
}

void func_151D1938(void *arg0) {
    func_151D1918(arg0);
    func_1514933C(arg0);
}

void func_151D1964(void *arg0) {
    func_151D1918(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D19F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1B80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1F2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D2248.s")

void func_151D27EC(u8 *arg0) {
    s32 **temp_v0 = *(s32 ***)(arg0 + 0x98);
    s32 *temp_v1 = *temp_v0;
    if (temp_v1 != NULL) {
        temp_v1[0x30 / 4] = 0;
    }
}

void func_151D2808(void *arg0) {
    func_151D27EC(arg0);
    func_15147E64(arg0);
}

void func_151D2834(void *arg0) {
    func_151D27EC(arg0);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D2860.s")
