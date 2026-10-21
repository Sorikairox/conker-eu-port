#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_151482D4(s32, s32);

void func_150B42B0(void) {
    s8 sp24[4];

    func_151482D4(0, 5);
    sp24[0] = 0;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 2;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 4;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 1;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 3;
    func_151494E0((s32) sp24, 0x18U);
    sp24[0] = 5;
    func_151494E0((s32) sp24, 0x18U);
}

s32 func_1000FC18(u16, s16, s16, s16, s32);
void func_15147E64(u8 *);

void func_150B4354(u8 *arg0) {
    func_1000FC18(0x221, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), 0xFA0);
    func_15147E64(arg0);
}

s32 func_1000FC18(u16, s16, s16, s16, s32);
void func_15147E98(u8 *);

void func_150B43C8(u8 *arg0) {
    func_1000FC18(0x221, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18)), 0xFA0);
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
s32 memcpy(s32 *, s32 *, s32);

u8 *func_150B443C(s32 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s32 u44;
        u8 pad48[0x3C];
        f32 u84;
        f32 u88;
        s8 u8C;
        u8 pad8D[0x3];
        f32 u90;
        s8 u94;
        u8 pad95[0x3];
        f32 u98;
        s32 u9C;
        u8 padA0[0x8];
        s16 uA8;
        s16 uAA;
        s32 uAC;
        u8 padB0[0x1];
        s8 uB1;
    } sp;
    u8 *sp40;
    u8 *temp_v0;

    memcpy(&sp.u44, arg0, 0x40);
    sp.u8C = 0;
    sp.uAA = 2;
    sp.uA8 = 0x1F4;
    sp.u88 = 0.0f;
    sp.uB1 = (s8) arg2;
    sp.u94 = 0;
    sp.u98 = 0.0f;
    sp.u90 = (*(f32 *)((u8 *)arg0 + 0x14)) + (*(f32 *)((u8 *)arg0 + 0x18));
    sp.u84 = sp.u90;
    (*(f32 *)((u8 *)(&sp.u9C) + 0)) = (f32) (*(f32 *)((u8 *)arg1 + 0));
    (*(f32 *)((u8 *)(&sp.u9C) + 4)) = (f32) (*(f32 *)((u8 *)arg1 + 4));
    (*(f32 *)((u8 *)(&sp.u9C) + 8)) = (f32) (*(f32 *)((u8 *)arg1 + 8));
    sp.uAC = 9;
    temp_v0 = func_15147FF0(&sp.u9C, 0x58, 0x24, 7, 7, 7, 0, 0, 0, 0xFFU, 1);
    sp40 = temp_v0;
    if (temp_v0 != NULL) {
        func_1000FA64(0x221U, (s16) (s32) (*(f32 *)((u8 *)arg1 + 0)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 4)), (s16) (s32) (*(f32 *)((u8 *)arg1 + 8)), 0x61A8, 0xFA0U, 0x258, (s32) func_1000EF40, NULL, 0, 8, func_150ADA20() & 0x40);
        memcpy((*(s32 **)((u8 *)sp40 + 0x98)), &sp.u44, 0x58);
    }
    return sp40;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B443C.s")
#endif
typedef struct { f32 x, y, z; } V3s64;
s32 func_150B45C8(u8 *arg0) {
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    u8 *temp_a3;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)temp_v0 + 0x1C)) & 1)) {
        return 0;
    }
    var_a2 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_a2 -= 1;
            var_a1 = 0;
            if (var_a2 < 0) {
                var_a2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_a3 = (0, temp_v1) + (var_a2 * 0x24); // fakematch: comma flips addu operand order
            (*(s16 *)((u8 *)temp_a3 + 0x1C)) = 0xFF;
            (*(s16 *)((u8 *)temp_a3 + 0x1E)) = (s16) ((*(s16 *)((u8 *)temp_a3 + 0x1E)) - D_800BE9E4);
            if ((*(s16 *)((u8 *)temp_a3 + 0x1E)) < 0) {
                var_a1 = 1;
            }
            (*(f32 *)((u8 *)temp_a3 + 0x10)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0xC)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0x10)));
            (*(f32 *)((u8 *)temp_a3 + 0)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0xC)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0)));
            (*(f32 *)((u8 *)temp_a3 + 4)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0x10)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 4)));
            (*(f32 *)((u8 *)temp_a3 + 8)) = (f32) (((*(f32 *)((u8 *)temp_a3 + 0x14)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 8)));
            (*(f32 *)((u8 *)temp_a3 + 0x18)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0x28)) * D_800BE9A4) + (*(f32 *)((u8 *)temp_a3 + 0x18)));
            if ((var_a1 != 0) && (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)))) {
                do {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                    if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                    }
                    (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
            }
        } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        *(V3s64 *)(arg0 + 0x54) = *(V3s64 *)(((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24) + (0, temp_v1)); // fakematch: comma flips addu operand order
    } else {
        (*(f32 *)((u8 *)arg0 + 0x54)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x58)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B4774.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B4BF0.s")

void func_150B5540(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);

    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= 0xFFFD;
    temp_v0[0x1C] |= 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E1AC0/func_150B5568.s")

void func_150B586C(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 5) {
        func_150B5540(arg0);
    }
}
