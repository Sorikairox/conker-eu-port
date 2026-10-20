#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150DFE40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150DFEA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0228.s")

void func_150E0324(u8 *arg0) {
    f32 *temp_v0 = (f32 *)(*(u8 **)(arg0 + 0x1D4) + 0x40);
    temp_v0[0x30 / 4] = *(f32 *)(arg0 + 0x14);
    temp_v0[0x34 / 4] = 2706.0f;
    temp_v0[0x38 / 4] = *(f32 *)(arg0 + 0x1C);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E047C.s")

void func_150E0840(u8 *arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_150E0880(void) {
    if (D_80088D20 == 0) {
        func_1515F170(6, 0);
        func_1513BAE8();
        D_80088D20 = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E08C8.s")

void func_15143794(s16, s16, f32, void *);
s32 func_151A2C9C(f32 *, f32 *, f32 *, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150E0978(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp6C[9];
    f32 temp_f2;

    sp6C[6] = arg0;
    sp6C[7] = arg1;
    sp6C[8] = arg2;
    func_15143794((s16) (func_150ADA20() & 0xFF), (s16) (((u32) func_150ADA20() % 65U) - 0x20), func_150ADA68() * 5.87f, &sp6C[3]);
    temp_f2 = (func_150ADA68() * 0.16900001f) + 0.186f;
    sp6C[0] = 0.0f;
    sp6C[1] = 0.0f;
    sp6C[2] = 0.0f;
    sp6C[3] += -arg3 * D_800BEDC8 * temp_f2;
    sp6C[4] += -arg4 * D_800BEDC8 * temp_f2;
    sp6C[5] += -arg5 * D_800BEDC8 * temp_f2;
    func_151A2C9C(&sp6C[6], sp6C, &sp6C[3], 0x3F7CA4E3, (func_150ADA68() * 0.23f) + -0.337f, (func_150ADA68() * 200.0f) + 150.0f, ((u32) func_150ADA20() % 26U) + 0x28, (func_150ADA20() % 201U) + 0x37, 0x1E, 0x14, 0, -1, 0x34, 0x35, 0x34, (s32) (*(u8 *)((u8 *)arg6 + 0xC)), (s32) (*(u8 *)((u8 *)arg6 + 1)));
}

void func_150E0B78(u8 *arg0)
{
  f32 temp_f0;
  f32 temp_f12;
  f32 temp_f14;
  f32 temp_f2;
  s32 var_v0;
  temp_f2 = D_800DBFF0->unk300 - ((f32) (*((s16 *) (((u8 *) arg0) + 0x14))));
  temp_f12 = D_800DBFF0->unk2F8 - ((f32) (*((s16 *) (((u8 *) arg0) + 0x10))));
  temp_f14 = D_800DBFF0->unk2FC - ((f32) (*((s16 *) (((u8 *) arg0) + 0x12))));
  temp_f0 = sqrtf((temp_f2 * temp_f2) + ((temp_f12 * temp_f12) + (temp_f14 * temp_f14)));
  if (temp_f0 <= 2570.0f)
  {
    var_v0 = 0xFF;
  }
  else
    if (temp_f0 >= 3850.0f)
  {
    var_v0 = 0;
  }
  else
  {
    temp_f14 = 2570.0f; // fakematch: temp reuse keeps 3850 - 2570 at run time (permuter)
    var_v0 = (s32) (255.0f - (((temp_f0 - 2570.0f) * (1.0f / (3850.0f - temp_f14))) * 255.f));
  }
  *((s8 *) (((u8 *) arg0) + 0x8A)) = (s8) var_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D650/func_150E0C58.s")
