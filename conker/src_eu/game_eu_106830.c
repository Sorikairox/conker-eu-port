#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D9020(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[5];
    arg1[1] = arg0[6] + 20.0f;
    arg1[2] = arg0[7];
}

void func_150D904C(s32 arg0, s32 arg1) {
    f32 sp34[3];
    f32 sp28[3];

    func_15145740(arg0, (s32)sp34, (s32)sp28, arg1, D_800BE616 ? D_800A0F10 : D_800A0F14);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D9098.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D9304.s")

void func_150D939C(u8 *arg0) {
    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= ~2;
    *(u16 *)(arg0 + 0x1E) |= 8;
    *(u16 *)(arg0 + 0x1E) |= 1;
    *(u16 *)(arg0 + 0x1C) = 0x28;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D93CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D952C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D99AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150DA1FC.s")

void func_150DAA04(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    u16 temp_a1 = *(u16 *)(temp_v0 + 0x30);

    if (temp_a1 != 0) {
        func_100111C8(temp_a1);
    }
}

void func_150DAA34(s32 arg0) {
    func_150DAA04(arg0);
    func_15147E64(arg0);
}

void func_150DAA60(s32 arg0) {
    func_150DAA04(arg0);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150DAA8C.s")

void func_150DAB6C(u8 *arg0, f32 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = arg1;
    func_151482D4(&tmp, 0x44);
}

s32 func_15131D98(s32, s32, u8 *, s32);
void func_15131EC8(s32, s32, u8 *);

s32 func_150DABA8(s32 arg0, s32 arg1) {
    u8 *sp20;
    u8 *temp_a2;

    temp_a2 = arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131D98(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, (*(s32 *)((u8 *)temp_a2 + 0xC)), temp_a2);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150DABFC.s")
