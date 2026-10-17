#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} struct_eu_vec3;

typedef struct {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ struct_eu_vec3 unk34;
} struct_eu_1BAAA0_c;

typedef struct {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ struct_eu_1BAAA0_c *unk2C;
} struct_eu_1BAAA0_d;

typedef struct {
    /* 0x000 */ u8 pad0[0x1C];
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ u8 pad1E[0xE];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[0x28];
    /* 0x05C */ u8 unk5C;
    /* 0x05D */ u8 pad5D[0x2C];
    /* 0x089 */ s8 unk89;
    /* 0x08A */ u8 pad8A[0x9A];
    /* 0x124 */ s16 unk124;
    /* 0x126 */ s16 unk126;
    /* 0x128 */ u8 pad128[0x2C];
    /* 0x154 */ f32 unk154;
    /* 0x158 */ s16 unk158;
    /* 0x15A */ s16 unk15A;
} struct_eu_1BAAA0_e;

typedef struct {
    u8 unk0[4];
} struct_eu_bytes4b;

extern struct_eu_bytes4b D_800A78B4;

typedef struct {
    /* 0x00 */ u8 pad0[0x84];
    /* 0x84 */ s32 unk84;
} struct_eu_1BAAA0_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0x24];
    /* 0x40 */ struct_eu_1BAAA0_b *unk40;
} struct_eu_1BAAA0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518D290.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518D1C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518DC50.s")

s32 func_1518E808(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x1C));
    if ((temp_v1 != NULL) && ((*(s32 *)temp_v1) != 0)) {
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x14));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x18));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (s32) (*(f32 *)((u8 *)temp_v1 + 0x1C));
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518E878.s")

void func_1518E8EC(u8 *arg0, u8 arg1) {
    if (arg1 != arg0[0x22]) {
        func_1518E878(arg0);
        arg0[0x22] = arg1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518E934.s")

void func_1518EA10(struct_eu_1BAAA0 *arg0) {
    func_1518E878(arg0);
    func_1514EDF0(arg0, arg0->unk18);
}

void func_1518EA3C(void *arg0) {
    func_1518EA10(arg0);
    func_15169804(arg0);
}

void func_1518EA68(void *arg0) {
    func_1518EA10(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518EA94.s")

s32 func_151429E0(s32, s32, s32, s32);

void func_1518EB48(s8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, s16 *arg6) {
    s32 var_v0;

    if (func_150ADA20() & 1) {
        *arg1 |= 1;
    }
    *arg0 = 0x16;
    if (func_150ADA20() & 1) {
        var_v0 = 3;
    } else {
        var_v0 = 4;
    }
    func_151429E0(var_v0 & 0xFF, arg2, arg3, arg4);
    *arg5 = 0xC8;
    *arg6 = 0x401;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518EBDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518EC44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518ECAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518F080.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518F4C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518F5C8.s")

s32 func_1518F678(struct_eu_1BAAA0_e *arg0) {
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk154);
    arg0->unk2C = arg0->unk2C - (arg0->unk2C * arg0->unk154);
    if (arg0->unk1C < arg0->unk158) {
        arg0->unk5C = arg0->unk1C * arg0->unk15A;
    }
    return 1;
}

s32 func_1518F6CC(struct_eu_1BAAA0_e *arg0) {
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk154);
    if (arg0->unk1C < arg0->unk158) {
        arg0->unk5C = arg0->unk1C * arg0->unk15A;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518F710.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518F8F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518F9CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518FA0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518FA8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518FB40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518FD34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518FDC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518FE0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518FE50.s")

s32 func_15190174(struct_eu_1BAAA0_d *arg0, struct_eu_vec3 *arg1) {
    struct_eu_1BAAA0_c *temp_a0 = arg0->unk2C;

    temp_a0->unk34 = *arg1;
    func_1514C390(temp_a0, arg1, arg0);
    return 1;
}

s32 func_151901B4(struct_eu_1BAAA0_d *arg0, struct_eu_vec3 *arg1) {
    struct_eu_1BAAA0_c *temp_a0 = arg0->unk2C;

    temp_a0->unk34 = *arg1;
    func_1514C4C0(temp_a0, arg1, arg0);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_151901F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15190334.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_151905AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1519078C.s")

void func_15190940(u8 *arg0) {
    func_15163DEC(arg0, arg0 + 0x20);
    func_15163F50(arg0, arg0 + 0x18);
}

void func_15190970(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_a2;
    u8 temp_a3;

    if (arg2 == 0) {
        temp_v0 = *(s32 *)(arg0 + 0x18);
        temp_v1 = *(s32 *)arg1;
        temp_a2 = arg0[0x1C];
        temp_a3 = arg1[4];
        if ((temp_v0 == temp_v1) || (temp_a2 == temp_a3)) {
            func_1516972C(arg0);
        }
    }
}

void func_151909C4(struct_eu_1BAAA0 *arg0) {
    struct_eu_1BAAA0_b *temp_v0 = arg0->unk40;

    temp_v0->unk84 = 0;
}

void func_151909D4(void *arg0) {
    func_151909C4(arg0);
    func_151617C4(arg0);
}

void func_15190A00(void *arg0) {
    func_151909C4(arg0);
    func_151617E4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15190A2C.s")

void func_15190A88(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_1516944C(0x3E, (s32)&tmp, 0x2A);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15190AC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15190B2C.s")

void func_15190C34(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x10))) + 0x31C));
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 0x1AC)) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15190C50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1519072C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15190770.s")

void func_15190DB0(void *arg0) {
    func_15191970(arg0);
    func_15169804(arg0);
}

void func_15190DDC(void *arg0) {
    func_15191970(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15190E08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1519150C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_151915FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15191970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15191A90.s")

s32 func_15191DEC(struct_eu_1BAAA0_e *arg0) {
    s16 temp_v0 = arg0->unk1C;
    s32 temp_v1;

    if (temp_v0 < arg0->unk124) {
        temp_v1 = temp_v0 * arg0->unk126;
        if (temp_v1 < arg0->unk5C) {
            arg0->unk5C = temp_v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15191E2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15191EF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_15191FF4.s")

extern s32 D_800A83F0;

void func_151920FC(s32 arg0, u8 arg1) {
    s32 sp1C;

    sp1C = D_800A83F0;
    func_151494E0(arg0, arg1);
    func_15169260((s32) &sp1C, 1, arg0, arg1);
}
