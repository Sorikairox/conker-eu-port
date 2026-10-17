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

void func_15190DB0(void *arg0) {
    func_15191970(arg0);
    func_15169804(arg0);
}

void func_15190DDC(void *arg0) {
    func_15191970(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15190E08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_1519150C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_151915FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191A90.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191E2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191EF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191FF4.s")

extern s32 D_800A83F0;

void func_151920FC(s32 arg0, u8 arg1) {
    s32 sp1C;

    sp1C = D_800A83F0;
    func_151494E0(arg0, arg1);
    func_15169260((s32) &sp1C, 1, arg0, arg1);
}
