#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E61C0/func_151B89B0.s")

s32 func_151B8B5C(u8 *arg0)
{
    u8 *p = *(u8 **)(arg0 + 0x110);
    if (p != NULL) {
        *(vertex *)(arg0 + 0x34) = *(vertex *)(p + 0x38);
        *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
        *(f32 *)(arg0 + 0x44) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
        *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    } else {
        *(s32 *)(arg0 + 0x58) |= 1;
    }
    return 1;
}

void func_151B8BEC(s32 arg0, s16 arg1) {
    func_1513FA70(arg0, arg1);
}

extern f32 D_800DCE54;
void func_151B8C18(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *p;
    struct_eu_EF410 sp18;

    p = arg0;

    sp18.unk0 = (s32) (p + 0x38);
    sp18.unk4 = (s32) (p + 0x3C);
    sp18.unk8 = (s32) (p + 0x40);
    sp18.unkC = 10.0f;
    sp18.unk10 = 0.2075f * D_800DCE54;
    sp18.unk14 = 300;
    sp18.unk16 = 0;
    sp18.unk17 = 3;
    sp18.unk18 = 0;
    func_15134908(&sp18, 0, arg1, arg2);
}

void func_15143794(s16, s16, f32, void *);
s32 func_151A2C9C(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151B8CA4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    func_15143794((s16) (func_150ADA20() & 0xFF), (s16) ((func_150ADA20() % 65U) - 0x20), func_150ADA68() * 945.0f * 0.01f, &sp6C[3]);
    temp_f2 = (func_150ADA68() * 157.0f) + 604.0f;
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    temp_f2 = temp_f2 * 0.001f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * D_800BEDC8 * temp_f2;
    sp6C[4] += -arg4 * D_800BEDC8 * temp_f2;
    sp6C[5] += -arg5 * D_800BEDC8 * temp_f2;
    func_151A2C9C(&sp6C[6], sp6C, &sp6C[3], 0x3F800000, ((func_150ADA68() * 157.0f) + -151.0f) * 0.001f, (func_150ADA68() * 55.0f) + 75.0f, (func_150ADA20() % 26U) + 0x19, (func_150ADA20() % 101U) + 0x64, 0xA, 0x19, 0, -1, 0, 0, 0, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1)));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E61C0/func_151B8EB8.s")
