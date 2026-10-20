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

void func_151411E4(structEU_16DC80 *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x154) != 0) {
        func_1517E6A4(*(f32 **)((u8 *)arg0 + 0x154), arg0);
    }
    D_800DCE20 -= 1;
    D_8008A33C[arg0->unk168](arg0);
}

void func_15141250(structEU_16DC80 *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x154) != 0) {
        func_1517E6A4(*(f32 **)((u8 *)arg0 + 0x154), arg0);
    }
    D_800DCE20 -= 1;
    D_8008A384[arg0->unk168](arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151412BC.s")

s32 func_1514143C(u8 *arg0)
{
  u8 *p;
  if (*((s32 *) (arg0 + 0x154)))
  {
    p = arg0 + 0x111;
 if (0) { } // fakematch: empty if, scheduling
    p--;  // fakematch: dead addiu kept (p = arg0 + K+1; p--;)
    (*((f32 **) (p + 0x44)))[0] = *((f32 *) (arg0 + 0x34));
    (*((f32 **) (p + 0x44)))[1] = *((f32 *) (arg0 + 0x38));
    (*((f32 **) (p + 0x44)))[2] = *((f32 *) (arg0 + 0x3C));
  }
}

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

void func_1514182C(structEU_16DC80 *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5) {
    f32 z;
    f32 y;
    f32 x;
    f32 mf[4][4];

    func_150A8050(mf, arg4, 0.0f, arg5);
    mf[3][0] = ((f32 *)arg1)[0];
    mf[3][1] = ((f32 *)arg1)[1];
    mf[3][2] = ((f32 *)arg1)[2];
    func_150A7E40(mf, 0.0f, *(f32 *)&arg2, 0.0f, &arg0->unk34, &arg0->unk38, &arg0->unk3C);
    x = *(f32 *)&arg3 * (arg0->unk34 - ((f32 *)arg1)[0]);
    y = *(f32 *)&arg3 * (arg0->unk38 - ((f32 *)arg1)[1]);
    z = *(f32 *)&arg3 * (arg0->unk3C - ((f32 *)arg1)[2]);
    *(f32 *)((u8 *)arg0 + 0x40) = arg0->unk34 + x * 500.0f;
    *(f32 *)((u8 *)arg0 + 0x44) = arg0->unk38 + y * 500.0f;
    *(f32 *)((u8 *)arg0 + 0x48) = arg0->unk3C + z * 500.0f;
}
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
