#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D5950(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(300, -1, 0x38, -1, 0, 0x28, 0xC, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D59D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D5E7C.s")

void func_150D5F3C(struct260 *arg0) {
    func_1514933C(arg0);
}

void func_150D5F5C(struct260 *arg0) {
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D5F7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D6898.s")

s32 func_15154DF4(s32, f32, f32, f32, u8, s32);
extern f32 D_800A0E80;
extern f32 D_800A0E84;

void func_150D6944(s32 arg0, u8 arg1, s32 arg2) {
    s32 pad;
    f32 sp28;
    f32 sp24;

    sp24 = func_150ADA68();
    sp28 = func_150ADA68();
    func_15154DF4(arg0, (sp24 * 3.0f) + 8.0f, (sp28 * D_800A0E80) + D_800A0E84, (func_150ADA68() * 50.0f) + 100.0f, (s32) arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D69F8.s")

s32 func_151A6308(f32, s32, s32, s32, s16, u8, u8, u8, s32);

void func_150D6B00(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp38;
    f32 sp34;

    sp34 = func_150ADA68();
    sp38 = func_150ADA20();
    func_151A6308((sp34 * 100.0f) + 150.0f, ((sp38 % 71U) + 0x82) & 0xFF, arg0, arg1, (func_150ADA20() % 31U) + 0x32, 0, 1, (s32) arg2, arg3);
}

s32 func_15182BE0(u8, u8, u8, s32, s16, u8, u8, s32); 

void func_150D6BB4(u8 arg0, u8 arg1, s32 arg2) {
    s32 pad;
    u32 sp28;

    sp28 = func_150ADA20();
    func_15182BE0(0xFF, 0xFF, 0xFF, ((sp28 % 56U) + 0xC8) & 0xFF, (func_150ADA20() % 6U) + 0x19, (s32) arg0, (s32) arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D6C40.s")

void func_150D71A8(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[5];
    arg1[1] = arg0[6] + 60.0f;
    arg1[2] = arg0[7];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D71D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D7370.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D741C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_103160/func_150D7578.s")
