#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DFAA0/func_150B2290.s")

#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);
#else
s32 func_1509BE40(s32, s32, s32, s32);
#endif

void func_150B2300(u8 *arg0) {
    u8 *temp_v0;

    if (func_1509BE40(1, 0x4054, 6, 0x9000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x10000);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFFFEFFFF);
    }
    if ((func_1509BE40(1, 0x405C, 6, 0x9000) == 0) && (func_1509BE40(1, 0x405B, 6, 0x2000) != 0) && ((*(s32 *)((u8 *)arg0 + 0x2C)) != 0x40)) {
        temp_v0 = (*(u8 **)((u8 *)arg0 + 0x3D0));
        (*(f32 *)((u8 *)temp_v0 + 0x17C)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x180)) + 10.0f);
    }
}

void func_150B23C0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    typedef struct { s32 w[3]; } Blk12;
    struct {
        Blk12 unk0;
        f32 unkC;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = *(Blk12 *)arg1;
    tmp.unkC = 0.0f;
    temp_v0 = func_15149130((func_150ADA20() % 133U) + 69, -1, 0x49, -1, 1, 0, 0x10, arg0[0xC], arg0[0x1]);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

void func_150B2470(u8 *arg0) {
    struct {
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        f32 u90;
        f32 u94;
        f32 u98;
        s32 u9C;
        s32 uA0;
        s16 uA4;
        s16 uA6;
        s32 uA8;
        s32 uAC;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        u8 padF8[0x4];
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s8 u100;
        s8 u101;
    } sp;
    f32 temp_f16;
    f32 temp_f4;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((0.0786f + (func_150ADA68() * 0.0346f)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        sp.uB9 = 0x6C;
        sp.uA4 = 0x5103;
        sp.u9C = 0x200005;
        sp.uBA = 0x50;
        sp.uBC = 3;
        sp.uF4 = 0x90DE07;
        sp.uFC = 8;
        sp.uFD = 6;
        sp.uFE = 0x16;
        sp.u8C = 0;
        sp.u8D = 0;
        sp.uA0 = 0;
        sp.uA8 = 0;
        sp.uAC = 0;
        sp.uFF = -1;
        sp.u100 = -1;
        sp.u101 = 0;
        sp.uBE = 0x50;
        sp.uB0 = 0x67;
        sp.uB1 = 0x6C;
        sp.uB2 = 0x6C;
        sp.uB3 = 0xFF;
        sp.uB4 = 0x16;
        sp.uB5 = 0xB;
        sp.uB6 = 0;
        sp.uB8 = 0xFF;
        sp.u98 = 0.979401f;
        sp.uC0 = 1.016479f;
        (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0));
        (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s1 + 4));
        (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s1 + 8));
        sp.uD8 = 0.0f;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        do {
            sp.u8E = (func_150ADA20() % 5U) + 4;
            sp.u8F = (func_150ADA20() % 5U) + 4;
            sp.u90 = func_150ADA68() * 27.0f;
            sp.u94 = func_150ADA68() * 27.0f;
            temp_f4 = func_150ADA68() * 0.209f;
            sp.uF4 &= ~0xC0;
            sp.uF0 = temp_f4 + 0.135f;
            var_s0 = 0;
            if (func_150ADA20() & 1) {
                var_s0 = 0x80;
            }
            if (func_150ADA20() & 1) {
                var_v0 = 0x40;
            } else {
                var_v0 = 0;
            }
            sp.uF4 |= var_v0 | var_s0;
            sp.uB7 = (func_150ADA20() % 101U) + 0x64;
            sp.uA6 = (func_150ADA20() % 78U) + 0x7E;
            temp_f16 = (func_150ADA68() * 503.0f) + 405.0f;
            sp.uC8 = temp_f16;
            sp.uC4 = temp_f16;
            temp_v0 = func_151307F0(&sp.u9C, 1, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u8C, 0x10);
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DFAA0/func_150B2470.s")
#endif
#ifdef NON_MATCHING
/* P249: readable C for func_150B2820 (game_eu_DFAA0, 79 insns; compiled C, not hand asm: IDO prologue / delay slots). */
// view_progress_setup: configures a view record (+0x84 flags, +0x190, +0x348 / +0x34C / +0x374, +0x5F0) from the game
// progress queries func_1509BE40 (kind 0 = 3 arguments, kind 1 = 4). Query 0x5043 / 0x1A set: +0x84 |= 0x400000
// (and 0x4000 when 0x5045 / 0x1A is set too), +0x190 = 0; else 0x4030 (kind 1): +0x190 = 235; else +0x348 / +0x34C =
// 114, +0x374 = 384, +0x190 = 60. +0x5F0 bit 0x100 = (query (0x2007 / 0xB7 | 0x2000) / 0xBC != 0 and query
// 0x2000 / 0xBB != -1).
void func_150B2820(u8 *v) {
    s32 a;
    s32 b;

    a = func_1509BE40(0, func_1509BE40(0, 0x2007, 0xB7) | 0x2000, 0xBC);
    b = func_1509BE40(0, 0x2000, 0xBB);
    if (func_1509BE40(0, 0x5043, 0x1A) != 0) {
        if (func_1509BE40(0, 0x5045, 0x1A) != 0) {
            *(s32 *) (v + 0x84) |= 0x4000;
        }
        *(s32 *) (v + 0x84) |= 0x400000;
        *(f32 *) (v + 0x190) = 0.0f;
    } else if (func_1509BE40(1, 0x4030, 6, 0x2000) != 0) {
        *(f32 *) (v + 0x190) = 235.0f;
    } else {
        *(f32 *) (v + 0x348) = 114.0f;
        *(f32 *) (v + 0x34C) = 114.0f;
        *(f32 *) (v + 0x374) = 384.0f;
        *(f32 *) (v + 0x190) = 60.0f;
    }
    if (a != 0 && b != -1) {
        *(s32 *) (v + 0x5F0) |= 0x100;
    } else {
        *(s32 *) (v + 0x5F0) &= ~0x100;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DFAA0/func_150B2820.s")
#endif
