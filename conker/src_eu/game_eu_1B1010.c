#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1510DBB0(s16 *arg0);
void func_10004074(s32);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183800.s")

u8 *func_1502B6BC(s32, s32, s32, s32, s32, s32);
s32 func_1518403C(s32);
extern u8 D_800DE399;

void func_15183E20(s32 arg0) {
    u8 *temp_v0;

    if (*(s32 *)((u8 *)D_800DDE80 + arg0 * 0x14) == 0) {
        func_1518403C(arg0);
    }
    if (*(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x14) == 0) {
        temp_v0 = func_1502B6BC(0, 0, 0, 2, 9, arg0 + 0xAE);
        if (temp_v0 != NULL) {
            *(u8 **)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x14) = temp_v0;
            *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x18) = *(s32 *)(temp_v0 + 0);
            *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x1C) = *(s32 *)(temp_v0 + 8);
            *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x24) = 0;
            *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x20) = *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0xC);
            *(&D_800DE399 + arg0) = 1;
        }
    }
}

typedef struct { s32 a; s32 b; s32 c; s32 d; s32 e; } StructDDE80;
void func_15183EE4(s32 arg0) {
    if (((StructDDE80 *)D_800DDE80)[arg0].a == 0) {
        func_1518403C(arg0);
    }
    if (((StructDDE80 *)D_800DDE80)[arg0 + 1].a == 0) {
        func_1518403C(arg0 + 1);
        ((StructDDE80 *)D_800DDE80)[arg0 + 1].d = ((StructDDE80 *)D_800DDE80)[arg0].d;
    }
}

void func_15183F60(s32 arg0, s32 arg1)
{
  u8 *temp_v0;
  if ((*((s32 *) (((u8 *) D_800DDE80) + (arg0 * 0x14)))) == 0)
  {
    func_1518403C(arg0);
    if (1) // fakematch: empty block (permuter)
    {
    }
  }
  if ((*((s32 *) (((u8 *) D_800DDE80) + (arg0 * 0x14)))) != 0)
  {
    if ((*((s32 *) (((u8 *) D_800DDE80) + (arg1 * 0x14)))) == 0)
    {
      temp_v0 = func_1502B6BC(0, 0, 0, 2, 9, arg1 + 0xAD);
      if (temp_v0 != 0)
      {
        *((u8 **) (((u8 *) D_800DDE80) + (arg1 * 0x14))) = temp_v0;
        *((s32 *) ((((u8 *) D_800DDE80) + (arg1 * 0x14)) + 4)) = *((s32 *) (temp_v0 + 0));
        *((s32 *) ((((u8 *) D_800DDE80) + (arg1 * 0x14)) + 8)) = *((s32 *) (temp_v0 + 8));
        *((s32 *) ((((u8 *) D_800DDE80) + (arg1 * 0x14)) + 0xC)) = *((s32 *) (temp_v0 + 0x18));
        *((s32 *) ((((u8 *) D_800DDE80) + (arg1 * 0x14)) + 0x10)) = 0;
        D_800DDF68[arg1] = 1;
      }
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_1518403C.s")

extern u8 D_800A76B0[];
extern s32 D_800DDF78[];

Gfx *func_15184114(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 idx = -1;

    for (i = 0; i < 11; i++) {
        if (arg1 == D_800A76B0[i]) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        if (D_800DDF78[idx] != 0) {
            gSPDisplayList(gdl++, D_800DDF78[idx]);
        }
    }
    return gdl;
}

#ifdef NON_MATCHING
extern s32 D_800DE350;
extern s8 D_800DE3A0;
extern s8 D_800DE3A1;
extern s32 D_800DE3C8;

/* Release slot arg0 of the D_800DDE80 table (0x14-byte entries): its texture (word 0x10) through
 * func_1510DBB0 and its block (word 0) back to the allocator, clearing the slot's DL D_800DDF78[arg0].
 * Slot 8 keeps its block unless D_800DE3A1 == -2; slot 9 with D_800DE3A0 == -2 also frees D_800DE350.
 * (P15, hand C from the asm) */
void func_15184198(s32 arg0) {
    s32 *e = &D_800DDE80[arg0 * 5];

    if (e[4] != 0) {
        func_1510DBB0((s16 *)e[4]);
        e[4] = 0;
    }
    if (arg0 == 8) {
        if (D_800DE3A1 != -2) {
            return;
        }
    } else if (arg0 == 9 && D_800DE3A0 == -2 && D_800DE350 != 0) {
        func_10004074(D_800DE350);
        D_800DE350 = 0;
        D_800DE3C8 = 0;
    }
    if (e[0] != 0) {
        func_10004074(e[0]);
        e[0] = 0;
        D_800DDF78[arg0] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15184198.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15184298.s")

s32 func_15184688(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x31C);
    if ((temp_v0 != NULL) && (temp_v0[0x57] != 0)) {
        return 1;
    }
    return 0;
}
