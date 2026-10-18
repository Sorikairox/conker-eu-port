#include <ultra64.h>
#include "functions.h"
#include "variables.h"


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
extern f32 D_800A90F0;

void func_151A10A8(u8 *arg0) {
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (D_800A90F0 * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        temp_s0 = arg0 + 0x28;
        do {
            func_1514CBE8((*(f32 *)temp_s0), (*(f32 *)((u8 *)temp_s0 + 4)), (*(s32 *)((u8 *)temp_s0 + 8)), (func_150ADA68() * 25.0f) + 15.0f, 0, 0xFF, 5, 4, (s32) (*(u8 *)((u8 *)temp_s0 + 0xC)), 0.0f, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)));
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A11BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A13F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A14D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A15C0.s")

void func_151A177C(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A23E4.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2FC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3084.s")

void func_151A3134(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 *arg5) {
    f32 temp_f0 = 1.0f - arg4;

    arg5[0] = arg0[0] * temp_f0;
    arg5[1] = arg0[1] * temp_f0;
    arg5[2] = arg0[2] * temp_f0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3180.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A31D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A34BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3700.s")
