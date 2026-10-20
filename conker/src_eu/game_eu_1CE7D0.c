#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_151A177C(f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);


s32 func_1510FE4C(s32);

void func_151A0A10(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        u8 unkC;
        u8 padD[3];
        f32 unk10;
    } tmp;

    if (arg0 != NULL) {
        tmp.unk0 = *(f32 *)(arg0 + 0x14);
        tmp.unk8 = *(f32 *)(arg0 + 0x1C);
        if (D_800C35EA != 1) {
            tmp.unk4 = *(f32 *)(arg0 + 0x180);
            tmp.unk10 = 0.0f;
            switch (func_1510FE4C(*(s32 *)(arg0 + 0x184))) {
            case 0xA:
                tmp.unkC = 0;
                break;
            case 0xF:
            case 0x11:
                tmp.unkC = 1;
                break;
            default:
                tmp.unkC = 0;
                break;
            }
            temp_v0 = func_151491F4(arg1, -1, 1, 1, 0, 0x14, arg2, arg3);
            if (temp_v0 != NULL) {
                memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
            }
        }
    }
}

s32 func_1514CBE8(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
void func_151A10A8(u8 *arg0) {
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (0.17500001f * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        temp_s0 = arg0 + 0x28;
        do {
            func_1514CBE8((*(f32 *)temp_s0), (*(f32 *)((u8 *)temp_s0 + 4)), (*(s32 *)((u8 *)temp_s0 + 8)), (func_150ADA68() * 25.0f) + 15.0f, 0, 0xFF, 5, 4, (s32) (*(u8 *)((u8 *)temp_s0 + 0xC)), 0.0f, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)));
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A11BC.s")

void func_151A13F0(f32 arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    func_151A177C(arg0, arg1, arg2, 163.0f, 2.019f, 0xA0, 0x4B, 0x41F, 0x4F6, 1, 2.019f, 0x87, 0x44, 0x41F, 0x4F6, 2, 1, 2.019f, 0x46, 0x42, 0x41F, 0x4F6, 7, 0x41, 4, 1, arg3, arg4);
}

void func_151A14D8(f32 arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    func_151A177C(arg0, arg1, arg2, 163.0f, 2.019f, 0xA0, 0x4B, 0x41F, 0x4F6, 1, 2.019f, 0x87, 0x44, 0x41F, 0x4F6, 2, 1, 2.019f, 0x46, 0x42, 0x41F, 0x4F6, 7, 0x41, 4, 1, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A15C0.s")

void func_151A177C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, s32 argB, s32 argC, s32 argD, s32 argE, s32 argF, s32 arg10, f32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, u8 arg1A, s32 arg1B) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1D0C.s")

void func_151A1E8C(u8 *arg0) {
    typedef struct { s32 w[3]; } Blk12;
    struct260 *temp_v0;
    struct {
        Blk12 unk0;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        s16 unk18;
        s16 unk1A;
        s16 unk1C;
        s16 unk1E;
    } tmp;

    tmp.unk0 = *(Blk12 *)(arg0 + 0x28);
    tmp.unkC = *(f32 *)(arg0 + 0x34);
    tmp.unk10 = 0.0f;
    tmp.unk14 = *(f32 *)(arg0 + 0x38);
    tmp.unk18 = *(s16 *)(arg0 + 0x3E);
    tmp.unk1A = *(s16 *)(arg0 + 0x40);
    tmp.unk1C = *(s16 *)(arg0 + 0x42);
    tmp.unk1E = *(s16 *)(arg0 + 0x44);
    temp_v0 = func_151491F4(*(s16 *)(arg0 + 0x3C), -1, 3, 1, 0, 0x20, arg0[0xC], arg0[0x1]);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x20);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1F48.s")

void func_151A23E4(u8 *arg0)
{
  s16 temp_lo;
  u8 *new_var;
  s16 temp_lo_2;
  u8 *new_var2;
  s16 temp_v1;
  u8 *temp_v0;
  u8 *temp_v0_2;
  new_var = (0, arg0 + 0x50); // fakematch: (0, x) comma flips commutative operand order
  temp_v1 = *((s16 *) (((u8 *) arg0) + 0x38));
  temp_v0 = new_var;
  if ((*((s16 *) (((u8 *) arg0) + 0x54))) < temp_v1)
  {
    new_var2 = ((u8 *) temp_v0) + 2;
    *((s8 *) (((u8 *) arg0) + 0x3F)) = (s8) ((*((s16 *) (((u8 *) temp_v0) + 0))) * ((*((s16 *) new_var2)) - temp_v1));
  }
  temp_v0_2 = new_var;
  if ((*((s16 *) (((u8 *) temp_v0_2) + 0xA))) < temp_v1)
  {
    temp_lo = (*((s16 *) (((u8 *) temp_v0_2) + 6))) * ((*((s16 *) (((u8 *) temp_v0_2) + 8))) - temp_v1);
    *((s16 *) (((u8 *) arg0) + 0x36)) = temp_lo;
    *((s16 *) (((u8 *) arg0) + 0x34)) = temp_lo;
  }
  if (temp_v1 < (*((s16 *) (((u8 *) temp_v0_2) + 0xC))))
  {
    *((s8 *) (((u8 *) arg0) + 0x3F)) = (s8) ((*((s16 *) (((u8 *) temp_v0_2) + 0xE))) * (0, temp_v1)); // fakematch: (0, x) comma flips commutative operand order
  }
  if (temp_v1 < (*((s16 *) (((u8 *) temp_v0_2) - (-0x10)))))
  {
    temp_lo_2 = (*((s16 *) (((u8 *) arg0) + 0x36)) = (*((s16 *) (((u8 *) temp_v0_2) + 0x12))) * (0, temp_v1)); // fakematch: (0, x) comma flips commutative operand order
    *((s16 *) (((u8 *) arg0) + 0x34)) = temp_lo_2;
  }
}

void func_151A2498(u8 *arg0) {
    typedef struct { s32 w[3]; } Blk12;
    struct {
        Blk12 unk0;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        s16 unk18;
        s16 unk1A;
        s16 unk1C;
        s16 unk1E;
        s16 unk20;
        s16 unk22;
        u8 pad24[4];
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = *(Blk12 *)(arg0 + 0x28);
    tmp.unkC = *(f32 *)(arg0 + 0x34);
    tmp.unk10 = 0.0f;
    tmp.unk14 = *(f32 *)(arg0 + 0x38);
    tmp.unk18 = *(s16 *)(arg0 + 0x3E);
    tmp.unk1A = *(s16 *)(arg0 + 0x40);
    tmp.unk1C = *(s16 *)(arg0 + 0x42);
    tmp.unk1E = *(s16 *)(arg0 + 0x44);
    tmp.unk20 = *(s16 *)(arg0 + 0x46);
    tmp.unk22 = *(s16 *)(arg0 + 0x48);
    temp_v0 = func_151491F4(*(s16 *)(arg0 + 0x3C), -1, 4, 1, 0, 0x24, arg0[0xC], arg0[0x1]);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x24);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2564.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2A58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2B90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2F10.s")

s32 func_151A31D4(s32, s32, s16, s16, f32, f32, f32, s32, f32, f32, f32, f32, s16, s16, s16, s16, s16, s16, s8, u8, s32, u8);

s32 func_151A2FC4(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, s16 argB, s16 argC, s16 argD, s16 argE, s16 argF, s16 arg10, s8 arg11, u8 arg12, s32 arg13) {
    return func_151A31D4(arg0, 0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, argC, argD, argE, argF, arg10, arg11, arg12, arg13, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3084.s")

void func_151A3134(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 *arg5) {
    f32 temp_f0 = 1.0f - arg4;

    arg5[0] = arg0[0] * temp_f0;
    arg5[1] = arg0[1] * temp_f0;
    arg5[2] = arg0[2] * temp_f0;
}

s32 func_15143794(s16, s16, f32, s32);
void func_151A3180(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15143794(arg1, arg2, (1.0f - arg4) * arg3, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A31D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A34BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3700.s")
