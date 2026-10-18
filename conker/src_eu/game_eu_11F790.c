#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8  pad0[0x8];
    s32 *unk8;
    u8  unkC;
} struct_eu_11CB90_60;

typedef struct {
    u8  pad0[0x12C];
    s32 unk12C[1];
} struct_eu_11CB90_elem;

void func_150F0820(void *arg0);
void func_150F0898(void *arg0);
void func_150F0900(void *arg0);
void func_150F0968(void *arg0);
void func_151617C4(void *arg0);
void func_151617E4(void *arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11F790/func_150F1F80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11F790/func_150F20C8.s")

void func_eu_150F2230(u8 *arg0) {
    if ((*(u16 *)((u8 *)arg0 + 0x84)) == 0x14) {
        (*(u8 *)((u8 *)arg0 + 0x68)) = 0x1B;
    } else {
        (*(u8 *)((u8 *)arg0 + 0x68)) = 0xC;
    }
    (*(u8 *)((u8 *)arg0 + 0x69)) = 0x13;
    if (((*(s32 *)((u8 *)arg0 + 0x2E4)) & 3) == 3) {
        (*(u8 *)((u8 *)arg0 + 0x69)) = 0x14;
    }
    if (((*(s32 *)((u8 *)arg0 + 0x2E4)) & 0xC) == 0xC) {
        (*(u8 *)((u8 *)arg0 + 0x69)) = 0x17;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11F790/func_150F2290.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11F790/func_150F2670.s")

s32 func_15143874(s16, s32, f32 *, f32 *);

void func_150F2230(u8 *arg0, u8 arg1, s32 arg2) {
    f32 sp2C[3];
    s32 sp20[3];

    if ((*(s32 *)(arg0 + 0x1D4) != 0) && ((*(u8 *)(arg0 + 0x74) & 0xF) != 0xF)) {
        sp2C[0] = 0.0f;
        sp2C[1] = 0.0f;
        sp2C[2] = 0.0f;
        func_15143874(func_150ADA20() & 0xFF, 0x42C80000, sp2C, &sp2C[2]);
        func_15143134(sp2C, sp20, *(s32 *)(arg0 + 0x1D4) + 0x4C0);
        func_151C384C(sp20, arg1, arg2);
    }
}
