#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_8002AE18;
extern u64 D_8002C060;
extern OSMesgQueue D_8003B578;
extern OSTimer D_800BEB00;
void func_1501BB20(void) {
    if (D_8002AE18 != 0) {
        osSetTimer(&D_800BEB00, (25ULL * D_8002C060) / 1000000ULL, 0, &D_8003B578, (void *)6);
        D_8002AE18 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501BBB8.s")

extern f32 D_80096D10;
void func_1501C0D0(u8, f32, f32);
void func_1501BFF0(u8 arg0, u8 arg1)
{
  f32 t;
  f32 a;
  f32 b;
  if (arg1 >= 9) {
    arg1 = 8;
  }
  if (arg1 == 8) {
    a = 20.0f;
    b = 0.0f;
  } else if (arg1 == 0) {
    a = 0.0f;
    b = 99.0f;
  } else {
    t = ((f32)(u32)arg1 - 1) * D_80096D10 * 5.0f;
    a = t + 2.0f;
    b = 7.0f - t;
  }
  func_1501C0D0(arg0, a, b);
}

extern u8 D_800BED64[];
extern f32 D_800BED70[];
extern f32 D_800BED80[];
extern f32 D_800BED90[];
extern f32 D_800BEDA0[];
void func_1501C0D0(u8 arg0, f32 arg1, f32 arg2) {
    s32 idx;
    idx = D_800843F0[arg0];
    if (idx < 4 && D_800BED64[idx] != 0) {
        D_800BED5C[idx] = 1;
        D_800BED70[idx] = 0.0f;
        D_800BED80[idx] = arg1;
        D_800BED90[idx] = arg2;
        D_800BEDA0[idx] = arg1 + arg2;
    }
}

void func_1501C15C(u8 arg0) {
    s32 temp_v0 = D_800843F0[arg0];

    if (temp_v0 < 4) {
        D_800BED5C[temp_v0] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C1B0.s")

void func_1501C51C(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        func_1501C15C(i);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_49310/func_1501C55C.s")
