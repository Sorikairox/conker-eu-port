#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8  pad0[0x8];
    s32 *unk8;
    u8  unkC;
} struct_eu_11CB90_60;

typedef struct {
    u8  pad0[0x12C];
    s32 unk12C[1];
} struct_eu_11CB90_elem;

void func_150F0820(void *arg0);
void func_150F0898(void *arg0);
void func_150F0900(void *arg0);
void func_150F0968(void *arg0);
void func_151617C4(void *arg0);
void func_151617E4(void *arg0);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EEE00.s")

void func_150EEF40(u8 *arg0, u8 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = arg1;
    func_151403A8(&tmp, 0x43);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EF500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EF90C.s")

s32 func_150EFD04(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0[4] == 0x28) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EFD30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EFDE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EFE90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150EFFCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0448.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F066C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0718.s")

void func_150F07E0(void *arg0) {
    func_150F0820(arg0);
}

void func_150F0800(void *arg0) {
    func_150F0820(arg0);
}

void func_150F0820(void *arg0) {
    struct_eu_11CB90_60 *temp_v0 = *(struct_eu_11CB90_60 **)((u8 *)arg0 + 0x60);
    s32 *temp_v1 = temp_v0->unk8;
    ((struct_eu_11CB90_elem *)temp_v1)->unk12C[temp_v0->unkC] = 0;
}

void func_150F0840(void *arg0) {
    func_150F0898(arg0);
    func_1514933C(arg0);
}

void func_150F086C(void *arg0) {
    func_150F0898(arg0);
    func_15149368(arg0);
}

void func_150F0898(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x28);
    *(s32 *)(temp_v0 + 0x134) = 0;
}

void func_150F08A8(void *arg0) {
    func_150F0900(arg0);
    func_151411A4(arg0);
}

void func_150F08D4(void *arg0) {
    func_150F0900(arg0);
    func_151411C4(arg0);
}

void func_150F0900(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x178);
    *(s32 *)(temp_v0 + 0x138) = 0;
}

void func_150F0910(void *arg0) {
    func_150F0968(arg0);
    func_151617C4(arg0);
}

void func_150F093C(void *arg0) {
    func_150F0968(arg0);
    func_151617E4(arg0);
}

void func_150F0968(void *arg0) {
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x18);
    *(s32 *)(temp_v0 + 0x13C) = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F03F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0D64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0E0C.s")

s32 func_15160A58(s32, u8, s32 *, u8, s16, s32, s32, s32, s32, s32, s32, s8, s32, u8, u8, s32);
extern s32 D_800A1A44;
extern s32 D_800A1A50;

void func_150F0EB8(s32 arg0) {
    func_15160A58(arg0, 0x25, &D_800A1A44, 2, 0x12C, 4, 0, 0xFF, 0, 0xFF, 0, -1, 0, 0, 0xFF, 1);
    func_15160A58(arg0, 2, &D_800A1A50, 2, 0x12C, 0xD, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0FA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F0BEC.s")

s32 func_150F13C8(u8 *arg0, s32 arg1)
{
  u8 *temp_s0;
  s32 pad;
  u8 *temp_v0;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0xA8));
  if ((*((u8 *) (((u8 *) arg0) + 0xAC))) != (*((u8 *) (((u8 *) temp_v0) + 0x3B))))
  {
    return 0;
  }
  *((f32 *) (((u8 *) arg0) + 0x40)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x14)));
  temp_s0 = arg0 + 0xA8;
  *((f32 *) (((u8 *) arg0) + 0x44)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x18)));
  if (arg0 && arg0)
  {
  }
  *((f32 *) (((u8 *) arg0) + 0x48)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x1C)));
  *((f32 *) (((u8 *) temp_s0) + 8)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 8))) + (0.263f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 0xC)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0xC))) + (0.303f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 0x10)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0x10))) + (0.25f * D_800BE9A4));
  *((f32 *) (((u8 *) temp_s0) + 8)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 8)));
  *((f32 *) (((u8 *) temp_s0) + 0xC)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 0xC)));
  *((f32 *) (((u8 *) temp_s0) + 0x10)) = func_15144B68(*((f32 *) (((u8 *) temp_s0) + 0x10)));
  *((f32 *) (((u8 *) arg0) + 0x38)) = (f32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 8))) * 243.0f) + 780.0f);
  *((f32 *) (((u8 *) arg0) + 0x3C)) = (f32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 0xC))) * 243.0f) + 780.0f);
  *((s8 *) (((u8 *) arg0) + 0x2B)) = (s8) ((u32) ((sinf(*((f32 *) (((u8 *) temp_s0) + 0x10))) * 50.0f) + 200.0f));
  return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F15A0.s")

void func_150F10D4(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    tmp.unkC = *(f32 *)(arg0 + 0x14);
    tmp.unk10 = *(f32 *)(arg0 + 0x18);
    tmp.unk14 = *(f32 *)(arg0 + 0x1C);
    temp_v0 = func_15149130(300, -1, 0x4C, -1, 0, 0x3A, 0x18, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x18);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F16F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F1B78.s")

void func_150F1C04(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *p = arg0 + 0x18;
    s32 id;
    if (arg2 == 0x43) {
        id = arg1[0];
        if (id == *(s32 *)p || p[4] == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11CB90/func_150F1C5C.s")
