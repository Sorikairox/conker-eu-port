#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1510DBB0(s16 *arg0);
void func_10004074(s32);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15183800.s")

u8 *func_1502B6BC(s32, s32, s32, s32, s32, s32);
void func_1518403C(s32);
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

#ifdef NON_MATCHING
/* P133 */
s32 func_1510D3E0(Gfx *, s32, s32, s32, s16 **);

/*
 * hud_model_load: loads model idx once (asset 9, id idx + 0xAD, through func_1502B6BC) into the 0x14-byte slot
 * D_800DDE80[idx]: +0 the asset, +4 / +8 / +0xC its words 0 / 2 / 6, +0x10 the vertex list func_1510D3E0 fills
 * while relocating the asset's display list (word 4, also kept in D_800DDF78[idx]); D_800DDF68[idx] = 1 marks it
 * loaded. Nothing when the slot is already set or the asset is missing.
 */
void func_1518403C(s32 idx) {
    s32 *slot = (s32 *) ((u8 *) D_800DDE80 + idx * 0x14);
    s32 *asset;

    if (slot[0] != 0) {
        return;
    }
    asset = (s32 *) func_1502B6BC(0, 0, 0, 2, 9, idx + 0xAD);
    if (asset == NULL) {
        return;
    }
    slot[0] = (s32) asset;
    slot[1] = asset[0];
    slot[2] = asset[2];
    slot[3] = asset[6];
    D_800DDF78[idx] = asset[4];
    func_1510D3E0((Gfx *) asset[4], 0, 1, 0x3E, (s16 **) &slot[4]);
    D_800DDF68[idx] = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_1518403C.s")
#endif

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
#ifdef NON_MATCHING
/* P125 */
extern u8 D_8008D450[];
extern u8 *D_8008D760[];
void func_151661F0(f32 *angle, s16 *vtx, f32 amp, f32 *speed, f32 max, f32 min, u8 *rows, u8 n);
void func_1517A320(u8 i);
void func_151777CC(u8 arg0);
void func_15184198(s32 arg0);

/* anim_meshes_update: per frame, the 11 animated mesh slots (D_800DDE80: 5 words each, block +0, Vtx buffers +4 /
 * +8; display list D_800DDF78[i]; state D_800DDF68[i]: 1 = just set up, then 0, -1, -2 = gone).
 * A live slot that lost its block or display list becomes -2. The four byte timers D_800DDF60[0..3] count down by
 * the frame step. Slots 0..6 that are newly active swing buffer +8 (func_151661F0 with D_8008D450[i]: angle +0x18,
 * speed +0x24, max +0x28, min +0x2C, amplitude +0x30, rows D_8008D760[i], 2 * pairs), slots 2..4 also swing
 * buffer +4 with entry i + 9; slot 7 runs func_151777CC(7) and sets slot 10's state to 1; slots 8 / 9 wave
 * (func_1517A320); gone slots that still hold a block are released (func_15184198). Then every state ages:
 * > 0 -> 0, 0 / -1 -> one lower, -2 stays. */
void func_15184298(void) {
    static const u8 pairs[7] = { 2, 2, 2, 2, 2, 2, 4 };
    u8 *e;
    s32 v;
    s32 i;

    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] >= -1 && (D_800DDE80[i * 5] == 0 || D_800DDF78[i] == 0)) {
            D_800DDF68[i] = -2;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_800DDF60[i] > 0) {
            v = D_800DDF60[i] - D_800BE9E4;
            if (v < 0) {
                v = 0;
            }
            D_800DDF60[i] = v;
        }
    }
    for (i = 0; i < 7; i++) {
        if (D_800DDF68[i] == 1) {
            e = D_8008D450 + i * 0x38;
            func_151661F0((f32 *) (e + 0x18), (s16 *) D_800DDE80[i * 5 + 2], *(f32 *) (e + 0x30), (f32 *) (e + 0x24),
                          *(f32 *) (e + 0x28), *(f32 *) (e + 0x2C), D_8008D760[i], pairs[i]);
        }
    }
    for (i = 2; i < 5; i++) {
        if (D_800DDF68[i] == 1) {
            e = D_8008D450 + (i + 9) * 0x38;
            func_151661F0((f32 *) (e + 0x18), (s16 *) D_800DDE80[i * 5 + 1], *(f32 *) (e + 0x30), (f32 *) (e + 0x24),
                          *(f32 *) (e + 0x28), *(f32 *) (e + 0x2C), D_8008D760[i], pairs[i]);
        }
    }
    if (D_800DDF68[7] == 1) {
        func_151777CC(7);
    }
    for (i = 0; i < 2; i++) {
        if (D_800DDF68[8 + i] == 1) {
            func_1517A320(i + 8);
        }
    }
    if (D_800DDF68[7] == 1) {
        D_800DDF68[10] = 1;
    }
    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] == -2 && D_800DDE80[i * 5] != 0) {
            func_15184198(i);
        }
    }
    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] > 0) {
            D_800DDF68[i] = 0;
        } else if (D_800DDF68[i] >= -1) {
            D_800DDF68[i]--;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/func_15184298.s")
#endif

s32 func_15184688(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x31C);
    if ((temp_v0 != NULL) && (temp_v0[0x57] != 0)) {
        return 1;
    }
    return 0;
}
