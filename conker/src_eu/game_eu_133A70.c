#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106260.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_1510660C.s")

s32 func_15106760(s32 arg0) {
    return arg0 + 0x88;
}

typedef struct {
    u8 pad0[0x34];
} struct_eu_133A70_elem;

typedef struct {
    u8 pad0[0x48];
    s32 unk48;
    u8 pad4C[0x3C];
    struct_eu_133A70_elem unk88[1];
} struct_eu_133A70;

struct_eu_133A70_elem *func_1510676C(struct_eu_133A70 *arg0) {
    s32 temp_v1 = arg0->unk48;

    return &arg0->unk88[temp_v1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106794.s")

f32 func_15106A34(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return temp_f2 * temp_f2 * temp_f2;
}

f32 func_15106A5C(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return 3.0f * arg0 * temp_f2 * temp_f2;
}

f32 func_15106A90(f32 arg0) {
    return 3.0f * arg0 * arg0 * (1.0f - arg0);
}

f32 func_15106AC0(f32 arg0) {
    return arg0 * arg0 * arg0;
}

f32 func_15106AD8(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return -3.0f * temp_f2 * temp_f2;
}

f32 func_15106B04(f32 arg0) {
    return ((9.0f * arg0 * arg0) - (12.0f * arg0)) + 3.0f;
}

f32 func_15106B3C(f32 arg0) {
    return (-9.0f * arg0 * arg0) + (6.0f * arg0);
}

f32 func_15106B6C(f32 arg0) {
    return 3.0f * arg0 * arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106B90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106D38.s")

extern void (*D_80088FB8[])(u8 *);
void func_151073F8(u8 *arg0)
{
  void (*fn)(u8 *) = D_80088FB8[arg0[0x5C]];
  struct102 *a;
  struct102 *b;
  if (fn != NULL) {
    fn(arg0);
  }
  a = *(struct102 **)(arg0 + 0x6C);
  if (a != NULL) {
    func_1516972C(a);
  }
  b = *(struct102 **)(arg0 + 0x70);
  if (b != NULL) {
    func_1516972C(b);
  }
  func_151D5E30(arg0 + 0x74);
}

void func_15107478(struct102 *arg0) {
    func_151073F8(arg0);
    func_15169804(arg0);
}

void func_151074A4(struct102 * arg0) {
    func_151073F8(arg0);
    func_15169824(arg0);
}

void func_151074D0(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_80088FC8[arg0[0x5C]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107518.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_1510783C.s")

void func_15107B84(s32 ***arg0) {
    s32 **temp_v0 = arg0[0x18];
    s32 *temp_v1 = *temp_v0;

    temp_v1 += 0x28 / 4;
    temp_v1[2] = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107B9C.s")

void func_15107BCC(struct260 * arg0) {
    func_15107B9C(arg0);
    func_1514933C(arg0);
}

void func_15107BF8(struct260 * arg0) {
    func_15107B9C(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107C24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107C80.s")

void func_15107E64(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2 = *(s32 *)(arg0 + 0x60);

    func_15169850(arg1, arg2, temp_a2, temp_a2 + 4, (s32)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107EA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107FA0.s")

void func_15108060(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 dx = arg1[0] - arg0[0];
    f32 dy = arg1[1] - arg0[1];
    f32 dz = arg1[2] - arg0[2];

    arg2[0] = arg0[0] + dx * 0.333f;
    arg2[1] = arg0[1] + dy * 0.333f;
    arg2[2] = arg0[2] + dz * 0.333f;
    arg3[0] = arg0[0] + dx * 0.6667f;
    arg3[1] = arg0[1] + dy * 0.6667f;
    arg3[2] = arg0[2] + dz * 0.6667f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_151080F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_1510819C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_151083C8.s")

void func_151084D4(u8 *arg0, u8 arg1, void *arg2, void *arg3) {
    func_15143134(arg2, arg3, *(u8 **)(arg0 + 0x1D4) + (arg1 << 6));
}

void func_15108518(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2 = *(s32 *)(arg0 + 0x60);

    func_15169850(arg1, arg2, temp_a2, temp_a2 + 4, (s32)arg0);
}
