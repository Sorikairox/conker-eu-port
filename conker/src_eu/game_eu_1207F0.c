#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A1D20[];
#endif


#ifdef NON_MATCHING
extern u8 D_800CC82C;
extern u8 D_800CC8BA;
extern s32 *D_800DC3C4;
s32 func_151149AC(u8);
s32 func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_1507CD64(struct127 *, s32);
void func_15196888(u8 *, s32, s32);

// player_item_drop_check: unless the player's held object (D_800CCA0C, byte 0x120) is busy, checks items 0xFA and
// 0xF9 (func_151149AC; entry index = (item - D_800DBEF4) / 160 into the flag words at D_800DC3C4). The first one
// with bit 0 set: releases the player's current carried object (func_15060F28), clears D_800CC8BA and resets the
// player (func_15136C3C, sound 0x627 via func_10010630, func_15145A50, mode 6 via func_1507CD64). Then the four
// D_800BE4F0 nodes are offset by +-object 0xE's +0x2E4 value (func_15196888).
void func_150F2FE0(s32 arg0) {
    struct127 *o;
    s32 off;
    s32 i;
    s32 item;

    if (D_800CCA0C == NULL || D_800CCA0C[0x120] != 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        item = func_151149AC(0xFA - i);
        if (D_800DC3C4[(item - (s32) D_800DBEF4) / 160] & 1) {
            if (D_800CC82C != 0) {
                func_15060F28((struct127 *) ((u8 *) D_800CC2D0 + (D_800CC82C - 100) * 0x32C), 0);
            }
            D_800CC8BA = 0;
            func_15136C3C(D_800CC2D0, 0, 0, 1, 1, 0, 0xFF, 1);
            func_10010630(0x627, D_800CC2D0, 0x6D60, 0x1F4, 0x3E8);
            func_15145A50(D_800CC2D0);
            func_1507CD64(D_800CC2D0, 6);
            break;
        }
    }
    o = func_15083E90(0xE);
    off = (o != NULL) ? *(s32 *) ((u8 *) o + 0x2E4) : 0;
    func_15196888(((u8 **) D_800BE4F0)[0], off, 0);
    func_15196888(((u8 **) D_800BE4F0)[1], 0, -off);
    func_15196888(((u8 **) D_800BE4F0)[2], off, 0);
    func_15196888(((u8 **) D_800BE4F0)[3], -off, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F2FE0.s")
#endif

void func_150F320C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        f32 unk8;
        u8 unkC;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = 0;
    tmp.unk8 = 0.0f;
    tmp.unkC = 0;
    temp_v0 = func_15149130(300, -1, 0x5C, -1, 0, 0x44, 0x10, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3294.s")

void func_150F3714(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_150F3754(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

#ifdef NON_MATCHING
s32 func_150F3794(u8 *arg0) {
    u8 *sp18;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_t0;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x110));
    temp_v0 = arg0 + 0x110;
    if (((*(s32 *)((u8 *)temp_v1 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_v1 + 0x3B))) || (temp_t0 = (*(s32 *)((u8 *)temp_v1 + 0x1D4)), (temp_t0 == 0))) {
        return 0;
    }
    sp18 = temp_v0;
    func_15143134(((u8 *)&D_800A1D20), arg0 + 0x34, temp_t0 + 0x3C0);
    temp_f2 = sqrtf((*(f32 *)((u8 *)temp_v0 + 8))) * (*(f32 *)((u8 *)temp_v0 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x30)) = temp_f2;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = temp_f2;
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
    (*(s8 *)((u8 *)arg0 + 0x5C)) = (s8) (u32) ((*(f32 *)((u8 *)temp_v0 + 0x14)) - ((*(f32 *)((u8 *)temp_v0 + 0x18)) * temp_f12 * temp_f12));
    (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) + D_800BE9A4);
    var_v0 = 1;
    if ((*(f32 *)((u8 *)temp_v0 + 0xC)) < (*(f32 *)((u8 *)temp_v0 + 8))) {
        var_v0 = 0;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3794.s")
#endif
s32 func_15140410();

/* P224: draw table D_8008A1BC entry; the asm returns func_15140410's v0 and the dispatcher uses it. */
u8 *func_150F38FC(u8 *arg0, s16 arg1) {
    return (u8 *) func_15140410(arg0, arg0 + 0x12C, arg0 + 0x138, arg1);
}

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F_7 : 7;
    u8 unk4F_0 : 1;
} struct_eu_150F3930;

void func_150F3930(struct_eu_150F3930 *arg0) {
    if (*(f32 *)((u8 *)D_800DBFF0 + 0x300) < -2000.0f) {
        arg0->unk4F_0 = 0;
        return;
    }
    arg0->unk4F_0 = 1;
}

extern f32 D_800A1D40;

void func_150F3978(s32 arg0) {
    u8 *e = (u8 *)D_800DBFF0 + arg0 * 0x9A0;

    if (*(f32 *)(e + 0x300) < D_800A1D40) {
        if (*(f32 *)(e + 0x2FC) > 840.0f) {
            **(s16 **)&D_800D9A40 = **(s16 **)&D_800D9A40 | (1 << arg0); // fakematch: D_800D9A40 is declared s32 but holds a pointer; inline casts, no local
            return;
        }
        **(s16 **)&D_800D9A40 = **(s16 **)&D_800D9A40 & ~(1 << arg0);
    }
}

extern f32 D_800A1D50;
extern f32 D_800A1D54;

f32 func_150F3A20(s32 arg0, f32 arg1) {
    f32 var_f2;

    if (arg1 < -5.0f) {
        var_f2 = (arg1 * D_800A1D50) + D_800A1D54;
    } else {
        var_f2 = 0.75f;
    }
    return var_f2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3A74.s")

#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);

void func_150F4970(struct108 *arg0) {
    s32 temp_t0;

    if (arg0->unk23E == 0x3B) {
        func_1509BFB0(0, 0x405C, 1);
        if ((arg0->unk2C != 0x100) && (arg0->unk6C8 == 0)) {
            if (func_15123934(arg0, 8, 0, 0, 0) != 0) {
                temp_t0 = arg0->unk84 | 0x300000;
                arg0->unk84 = temp_t0;
                arg0->unk84 = temp_t0 & ~4;
                arg0->unk1B4 = 1;
                arg0->unk1E0 = 3;
                func_15124B18(arg0);
            }
            arg0->unk134 = 0;
            arg0->unk348 = 125.0f;
            arg0->unk34C = 125.0f;
            arg0->unk374 = 220.0f;
            arg0->unk190 = 30.0f;
        } else {
            arg0->unk190 = 0.0f;
        }
    } else if ((arg0->unk2C == 8) && (arg0->unk6C8 == 0)) {
        func_151239CC(arg0, 0);
        func_1509BFB0(0, 0x405C, 0);
    }
    if ((func_1509BE40(1, 0x4054, 6, 0x9000) != 0) && (func_1509BE40(1, 0x405E, 6, 0x9000) == 0)) {
        arg0->unk84 |= 0x80000000;
        return;
    }
    arg0->unk84 &= 0x7FFFFFFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F4970.s")
#endif