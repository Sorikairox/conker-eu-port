#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151407D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151408A4.s")

void func_151411A4(struct210 *arg0) {
    func_1513CA6C(arg0);
}

void func_151411C4(struct210 *arg0) {
    func_1513CAA0(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151411E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_15141250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151412BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_1514143C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_15141478.s")

s32 func_15141564(structEU_16DC80 *arg0) {
    struct { f32 unk0; f32 unk4; f32 unk8; f32 unkC; } *temp = &arg0->unk170.f;
    f32 s;
    s32 pad;

    s = sinf(temp->unk8);
    arg0->unk158 = temp->unk0 + (temp->unk4 * s);
    temp->unk8 += temp->unkC * D_800BE9A4;
    temp->unk8 = func_15144B68(temp->unk8);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151415D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151416E8.s")

// ???
void func_151417C4(u8 arg0, u8 arg1) {
    u8 sp24[4];
    s32 sp1C[2] = {0x1C, 0x56};

    sp24[0] = arg0;
    func_15169260(sp1C, 2, (s32)sp24, arg1);
}

s32 func_15141818(s32 arg0, s32 arg1) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_1514182C.s")
// f32 func_1514182C(void *arg0, void *arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
//     f32 sp6C;
//     f32 sp68;
//     f32 sp64;
//     ? sp34;
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f2;
//
//     func_150A8050(&sp34, arg4, 0, arg5);
//     sp64 = arg1->unk0;
//     sp68 = arg1->unk4;
//     sp6C = arg1->unk8;
//     func_150A7960(&sp34, 0, arg2, 0, arg0 + 0x34, arg0 + 0x38, arg0 + 0x3C);
//     temp_f0 = arg0->unk34;
//     temp_f2 = arg0->unk38;
//     temp_f12 = arg0->unk3C;
//     arg0->unk40 = (f32) (temp_f0 + ((temp_f0 - arg1->unk0) * arg3 * 500.0f));
//     arg0->unk44 = (f32) (temp_f2 + ((temp_f2 - arg1->unk4) * arg3 * 500.0f));
//     arg0->unk48 = (f32) (temp_f12 + ((temp_f12 - arg1->unk8) * arg3 * 500.0f));
//     return temp_f0;
// }

s32 func_15141928(structEU_16DC80 *arg0) {
    f32 *temp_v0 = arg0->unk170.i.unk8;

    func_1514182C(arg0, arg0->unk170.i.unkC, arg0->unk170.i.unk0, arg0->unk170.i.unk4, temp_v0[0], temp_v0[2]);
    return 1;
}
// s32 func_15141928(void *arg0) {
//     void *temp_v0 = arg0->unk178;
//     func_1514182C(arg0, arg0->unk17C, arg0->unk170, arg0->unk174, temp_v0->unk0, temp_v0->unk8);
//     return 1;
// }
