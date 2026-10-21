#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x000 */ u8 pad0[0x11B];
    /* 0x11B */ u8 unk11B;
} struct_eu_B2980_b;

typedef struct {
    /* 0x000 */ u8 pad0[0x31C];
    /* 0x31C */ struct_eu_B2980_b *unk31C;
} struct_eu_B2980;


#ifdef NON_MATCHING
extern s32 D_800875E0;
extern u8 D_8009DD24;

u8 func_15085170(u8 *arg0) {
    s32 var_a0;
    s32 var_v0;
    u8 *temp_a3;
    u8 *var_a1;
    u8 *var_t0;
    u8 temp_a2;
    u8 temp_v1;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 4));
    var_a1 = &D_8009DD24;
    var_v0 = 0;
loop_1:
    temp_a2 = *var_a1;
    var_a0 = 0;
    if ((s32) temp_a2 > 0) {
        temp_a3 = *(s32 *)((u8 *)&D_800875E0 + (var_v0 * 4));
        var_t0 = temp_a3;
loop_3:
        var_a0 += 1;
        if (temp_v1 == *var_t0) {
            return *temp_a3;
        }
        var_t0 += 1;
        if (var_a0 >= (s32) temp_a2) {
            goto block_6;
        }
        goto loop_3;
    }
block_6:
    var_v0 += 1;
    var_a1 += 1;
    if (var_v0 == 7) {
        return temp_v1;
    }
    goto loop_1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_15085170.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150851E0.s")

void func_15085880(struct_eu_B2980 *arg0, s32 arg1) {
    arg0->unk31C->unk11B = arg1;
}

u8 func_15085890(struct_eu_B2980 *arg0) {
    return arg0->unk31C->unk11B;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150858A0.s")

#ifdef NON_MATCHING
extern u16 D_8009015C;
extern s32 D_800D255C;
extern s32 D_800D2560;
extern s32 D_800D2564;
extern s32 D_800D2565;
extern s32 D_800D2566;
extern s32 D_800D2568;
extern s8 D_800E1050;

void func_15085710(s16 arg0, s16 arg1, s32 arg2) {
    s32 o;
    u8 *e;
    s8 b;
    s32 w;

    if (arg0 >= 0xFF || (u32)(s32)arg1 >= 12) {
        return;
    }
    o = arg0 * 0x1C;
    e = (u8 *)&D_800D2138 + o + 4;
    switch (arg1) {
        case 0: *(s32 *)((u8 *)&D_800D255C + o) = arg2; return;
        case 1: *(s32 *)((u8 *)&D_800D2560 + o) = arg2; return;
        case 2:
            if (D_8009015C & 1) {
                arg2 = 6;
            }
            *((u8 *)&D_800D2564 + o) = arg2;
            return;
        case 3:
            *(s8 *)(e + 8) = *(s8 *)(e + 8) + arg2;
            b = *(s8 *)(e + 8);
            *(s8 *)(e + 8) = (b >= 0x65) ? 0x64 : b;
            return;
        case 4:
            if (!(D_8009015C & 1)) {
                *(s8 *)(e + 8) = *(s8 *)(e + 8) - arg2;
            }
            return;
        case 5: *((u8 *)&D_800D2565 + o) = arg2; return;
        case 6:
            *(s8 *)(e + 9) = *(s8 *)(e + 9) + arg2;
            b = *(s8 *)(e + 9);
            *(s8 *)(e + 9) = (b >= 0x64) ? 0x63 : b;
            return;
        case 7:
            *(s8 *)(e + 9) = *(s8 *)(e + 9) - arg2;
            b = *(s8 *)(e + 9);
            *(s8 *)(e + 9) = (b < 0) ? 0 : b;
            return;
        case 8: *((u8 *)&D_800D2566 + o) = arg2; return;
        case 9: *(s32 *)((u8 *)&D_800D2568 + o) = arg2; return;
        case 10:
            if (D_800BE616 != 0 && D_800E1050 != 0) {
                return;
            }
            *(s32 *)(e + 0xC) += arg2;
            return;
        case 11:
            w = *(s32 *)(e + 0xC) - arg2;
            *(s32 *)(e + 0xC) = w;
            *(s32 *)(e + 0xC) = (w < 0) ? 0 : w;
            return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_15085710.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B2980/func_150859AC.s")

void func_15085ABC(s16 arg0)
{
  long var_s0;
  var_s0 = 0;
  if (D_800D18A8 == 0)
  {
    do
    {
      if ((1 << var_s0) & arg0)
      {
        func_15085710(var_s0, 5, (s32) D_800CC2D0[var_s0].health);
      }
      var_s0 += 1;
    }
    while (var_s0 != 4);
  }
}
