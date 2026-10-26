#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);
void func_150498A0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
extern f32 D_80088C60; // tint red, green, blue (current)
extern f32 D_80088C64;
extern f32 D_80088C68;
extern f32 D_80088C6C; // tint target
extern f32 D_80088C70;
extern f32 D_80088C74;
extern f32 D_80088C78; // tint speed
extern f32 D_80088C7C;
extern f32 D_80088C80;

// player_tint_update: player state handler (D_80089A10 table). While event flag 0x9000/6/0x403D is set the player
// gets +0x84 bits 0x80021000 and the screen tint target becomes red-less (0x4043: 64, 255, 255), green-less (0x4044:
// 255, 64, 255), blue-less (0x4045: 255, 255, 64) or white; otherwise the target is white and +0x84 loses
// 0x80021000 and gains 8. The tint D_80088C60..68 eases toward the target (func_150498A0, rate 4, max 6, the
// player's +0x7B4 step) and is published as bytes in event flags 0x12/0x30F5..0x30F3 and 0x30FA..0x30F8.
void func_150D0DD0(u8 *obj) {
    if (func_1509BE40(1, 0x403D, 6, 0x9000) != 0) {
        *(s32 *) (obj + 0x84) |= 0x80021000;
        if (func_1509BE40(1, 0x4043, 6, 0x9000) != 0) {
            D_80088C6C = 64.0f;
            D_80088C70 = 255.0f;
            D_80088C74 = 255.0f;
        } else if (func_1509BE40(1, 0x4044, 6, 0x9000) != 0) {
            D_80088C6C = 255.0f;
            D_80088C70 = 64.0f;
            D_80088C74 = 255.0f;
        } else if (func_1509BE40(1, 0x4045, 6, 0x9000) != 0) {
            D_80088C6C = 255.0f;
            D_80088C70 = 255.0f;
            D_80088C74 = 64.0f;
        } else {
            D_80088C6C = 255.0f;
            D_80088C70 = 255.0f;
            D_80088C74 = 255.0f;
        }
    } else {
        D_80088C6C = 255.0f;
        D_80088C70 = 255.0f;
        D_80088C74 = 255.0f;
        *(s32 *) (obj + 0x84) &= ~0x80021000;
        *(s32 *) (obj + 0x84) |= 8;
    }
    func_150498A0(&D_80088C60, D_80088C6C, &D_80088C78, 4.0f, 6.0f, *(f32 *) (obj + 0x7B4));
    func_150498A0(&D_80088C64, D_80088C70, &D_80088C7C, 4.0f, 6.0f, *(f32 *) (obj + 0x7B4));
    func_150498A0(&D_80088C68, D_80088C74, &D_80088C80, 4.0f, 6.0f, *(f32 *) (obj + 0x7B4));
    func_1509BFB0(1, 0x30F5, 0x12, (u32) D_80088C60 & 0xFF);
    func_1509BFB0(1, 0x30F4, 0x12, (u32) D_80088C64 & 0xFF);
    func_1509BFB0(1, 0x30F3, 0x12, (u32) D_80088C68 & 0xFF);
    func_1509BFB0(1, 0x30FA, 0x12, (u32) D_80088C60 & 0xFF);
    func_1509BFB0(1, 0x30F9, 0x12, (u32) D_80088C64 & 0xFF);
    func_1509BFB0(1, 0x30F8, 0x12, (u32) D_80088C68 & 0xFF);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D0DD0.s")
#endif

#ifdef NON_MATCHING
extern s32 D_80088C30;
extern s32 D_80088C34;
extern s32 D_80088C38;
extern s32 D_80088C3C;
extern s32 *D_800DC3C4;
s32 func_151149AC(u8);
void func_15195750(struct127 *);
s32 object_hit_effects(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_1507CD64(struct127 *, s32);

// level_item_flags_update: advances the four scroll counters D_80088C30..3C by the frame step (x40, x-66, x-8, x92);
// unless the player's held object (object 0 +0x31C, byte 0x120) is busy: for items 0xFA..0xF8 with flag bit 0
// (func_151149AC entry index = (item - D_800DBEF4) / 160 into D_800DC3C4) calls func_15195750 on the player and plays
// sound 0x627; for item 0xFB plays it and resets the player (object_hit_effects, func_15145A50, mode 6 via func_1507CD64).
void func_150D13A0(s32 arg0) {
    s32 step = D_800BE9E4;
    s32 i;
    s32 item;

    D_80088C30 += step * 40;
    D_80088C34 += -step * 66;
    D_80088C38 += -step * 8;
    D_80088C3C += step * 92;
    if ((*(u8 **) ((u8 *) D_800CC2D0 + 0x31C))[0x120] != 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        item = func_151149AC(0xFA - i);
        if (D_800DC3C4[(item - (s32) D_800DBEF4) / 160] & 1) {
            func_15195750(D_800CC2D0);
            func_10010154(0x627, D_800CC2D0, 0x7FFF, 0xC8, 0x2BC);
        }
    }
    item = func_151149AC(0xFB);
    if (D_800DC3C4[(item - (s32) D_800DBEF4) / 160] & 1) {
        func_10010154(0x627, D_800CC2D0, 0x7FFF, 0xC8, 0x2BC);
        object_hit_effects(D_800CC2D0, 1, 1, 1, 1, 0, 0xFF, 1);
        func_15145A50(D_800CC2D0);
        func_1507CD64(D_800CC2D0, 6);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D13A0.s")
#endif

#ifdef NON_MATCHING
s32 bone_emitter_spawn(u8 *, s32);

void func_150D15F4(u8 *arg0, s32 arg1) {
    struct {
        u8 u1C;
        u8 pad1D[0x3];
        u8 * u20;
        s8 u24;
        u8 pad25[0x3];
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        s8 u40;
        u8 pad41[0x1];
        s16 u42;
        s16 u44;
        s16 u46;
        s16 u48;
        s8 u4A;
        s8 u4B;
        s8 u4C;
        u8 pad4D[0x3];
        f32 u50;
        s8 u54;
        s8 u55;
    } sp;

    sp.u20 = arg0;
    sp.u24 = 0;
    sp.u28 = 0.0f;
    sp.u2C = 0.0f;
    sp.u30 = 0.0f;
    sp.u34 = 0.0f;
    sp.u1C = (*(u8 *)((u8 *)arg0 + 0x3B));
    if (arg1 & 0xFF) {
        sp.u38 = -30.0f;
    } else {
        sp.u38 = 30.0f;
    }
    sp.u3C = 0.0f;
    sp.u40 = 2;
    sp.u42 = 0x32;
    sp.u44 = 0x16;
    sp.u46 = 0x7D0;
    sp.u48 = 0;
    sp.u4A = 6;
    sp.u4B = 7;
    sp.u4C = -1;
    sp.u54 = 0;
    sp.u55 = -1;
    sp.u50 = 0.35085f;
    bone_emitter_spawn(&sp.u1C, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FE5E0/func_150D15F4.s")
#endif
extern f32 D_800A0C64;

s32 func_150D16C4(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x74)) = (f32) (((func_150ADA68() * 150.0f) + 350.0f) * D_800A0C64);
    return 1;
}

#ifdef NON_MATCHING
s32 impact_tinted_particle_spawn(u8 arg0, u8 *arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s16 arg7, u8 arg8, s16 arg9, s16 argA, u8 argB, u8 argC, s32 argD);
#else
s32 impact_tinted_particle_spawn(s32, f32 *, f32 *, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32);
#endif

extern f32 D_800A0C68, D_800A0C6C, D_800A0C70, D_800A0C74;
void func_150D1714(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 arg4, u8 *arg5) {
    f32 a[3];
    f32 x;
    f32 y;
    f32 z;
    f32 d[3];
    s32 r4;
    s32 r3;
    f32 r2;
    f32 r1;

    a[0] = *(f32 *)(arg2 + 0) * arg4 + *(f32 *)(arg0 + 0);
    a[1] = *(f32 *)(arg2 + 4) * arg4 + *(f32 *)(arg0 + 4);
    a[2] = *(f32 *)(arg2 + 8) * arg4 + *(f32 *)(arg0 + 8);
    x = *(f32 *)(arg3 + 0) * arg4 + *(f32 *)(arg1 + 0);
    y = *(f32 *)(arg3 + 4) * arg4 + *(f32 *)(arg1 + 4);
    z = *(f32 *)(arg3 + 8) * arg4 + *(f32 *)(arg1 + 8);
    d[0] = *(f32 *)(arg5 + 0x74) * (x - a[0]);
    d[1] = *(f32 *)(arg5 + 0x74) * (y - a[1]);
    d[2] = *(f32 *)(arg5 + 0x74) * (z - a[2]);
    r1 = func_150ADA68();
    r2 = func_150ADA68();
    r3 = func_150ADA20();
    r4 = func_150ADA20();
    impact_tinted_particle_spawn(0, a, d, r1 * 61.0f + 60.0f, D_800A0C68, D_800A0C6C, r2 * D_800A0C70 + D_800A0C74, (r3 & 0xF) + 0x23, r4 % 156U + 0x64, 0x1E, 8, 0, arg5[0xC], arg5[1]);
}
