#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150F9BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA738.s")

void func_150FA9E8(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_t6;

    temp_t6 = arg2;
    if (temp_t6 == 0x4C) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        func_1515D4D4(0U, 0U, 0U, 0xFF);
        return;
    }
    if (temp_t6 == 0x4D) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = 0x1E;
        return;
    }
    if (temp_t6 == 0x4E) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        return;
    }
    if (temp_t6 == 0x4F) {
        (*(s8 *)((u8 *)arg0 + 0x11)) = -1;
        func_1515D4D4(0xFFU, 0xFFU, 0xFFU, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FA520.s")

extern u8 D_80088F00;

void func_150FAFC0(u8 arg0, s32 arg1) {
    struct {
        u8 *unk0;
        u8 *unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    if (D_80088F00 == 0) {
        tmp.unk0 = D_800D34B8 + 0x71C;
        tmp.unk4 = D_800D34B8 + 0x6E8;
        tmp.unk8 = 0.0f;
        temp_v0 = func_15149130(300, -1, 0x57, -1, 0, 0x46, 0xC, arg0, arg1);
        if (temp_v0 != NULL) {
            D_80088F00 = 1;
        }
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB06C.s")

void func_150FB264(struct102 *arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0x4E) || (arg2 == 0x4F)) {
        func_1516972C(arg0);
    }
}

void func_150FB2A8(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0((s32)(D_800D34B8 + 0x514), 0x30);
    func_151494E0(0, 0x4D);
}

void func_150FB2F8(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0((s32)(D_800D34B8 + 0x514), 0x31);
    func_151494E0(0, 0x4C);
}

void func_150FB348(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x53) {
        *(s32 *)(arg0 + 0x58) |= 2;
    } else if (arg2 == 0x54) {
        *(s32 *)(arg0 + 0x58) &= ~2;
    }
}

#ifdef NON_MATCHING
/* func_15157580's spec (0x58 bytes, the model effect it spawns). */
typedef struct {
    /* 0x00 */ u8 u00;
    /* 0x01 */ u8 u01;
    /* 0x02 */ u8 u02;
    /* 0x03 */ u8 u03;
    /* 0x04 */ u8 u04;
    /* 0x06 */ s16 span;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ s32 u10;
    /* 0x14 */ s32 flagsA;
    /* 0x18 */ s32 flagsB;
    /* 0x1C */ s32 u1C;
    /* 0x20 */ s32 u20;
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ u8 u2C;
    /* 0x2D */ u8 u2D;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ u8 col[8];
    /* 0x38 */ u8 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x41 */ u8 u41;
    /* 0x44 */ struct { s32 x, y, z; } angle;
    /* 0x50 */ u8 pad50[4];
    /* 0x54 */ s16 u54;
    /* 0x56 */ s16 u56;
} ModelFxSpecFB398;

/* func_151559FC's spec (0x58 bytes; same layout as game_eu_FCE60's SpawnSpecCFB90). */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scaleA;
    /* 0x0C */ f32 scaleB;
    /* 0x10 */ u8 kind;
    /* 0x12 */ s16 span;
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ u8 u1A;
    /* 0x1B */ u8 col[9];
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ s32 u2C;
    /* 0x30 */ s32 u30;
    /* 0x34 */ s32 u34;
    /* 0x38 */ s32 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x41 */ u8 u41;
    /* 0x42 */ u8 pad42[2];
    /* 0x44 */ u8 player;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
} SpriteSpecFB398;

s32 func_15157580(void *spec, s32, f32, s32, s32, s32, s32, s32);
s32 func_151559FC(void *spec, s32 list, s32, s32, s32, s32, s32);
extern s16 D_800A20F0[]; /* 8 sprite kinds: 0xCE, 0xC5, then 0xC4 */

// score_banner_spawn: spawns the model effect 0x61 (func_15157580) and a row of 8 sprites (list 0xE, kinds
// D_800A20F0, x = -65 + 24.75 * i, y = 62, scale 16) for `span`, copying `span` into each new record (+0x120 for the
// model effect, +0x70 for the sprites). `flag` / `owner` are passed through to both spawners.
void func_150FB398(s16 span, u8 flag, s32 owner) {
    ModelFxSpecFB398 fx;
    SpriteSpecFB398 spr;
    s32 rec;
    u8 i;

    fx.u00 = 0x61;
    fx.u01 = 3;
    fx.u02 = 4;
    fx.u03 = 2;
    fx.u04 = 0;
    fx.span = span;
    fx.u08 = 0xA5;
    fx.u0C = 0x17;
    fx.u10 = 0;
    fx.flagsA = 0x200405;
    fx.flagsB = 0x60200;
    fx.u1C = 1;
    fx.u20 = 0x38;
    fx.u24 = 0x80;
    fx.u28 = 0x20;
    fx.u2C = 0;
    fx.u2D = 8;
    for (i = 0; i < 8; i++) {
        fx.col[i] = 0xFF;
    }
    fx.u38 = 0;
    fx.u3C = 0;
    fx.u40 = 0;
    fx.u41 = 1;
    fx.angle.x = ((s32 *)D_800A5860)[0];
    fx.angle.y = ((s32 *)D_800A5860)[1];
    fx.angle.z = ((s32 *)D_800A5860)[2];
    fx.u54 = 0xA;
    fx.u56 = 0x19;
    rec = func_15157580(&fx, 0, 1.0f, 0, 0, 2, flag, owner);
    if (rec != 0) {
        memcpy((u8 *)rec + 0x120, &span, sizeof(span));
    }

    spr.y = 62.0f;
    spr.scaleA = 16.0f;
    spr.scaleB = 16.0f;
    spr.span = span;
    spr.u14 = 0x29;
    spr.u16 = 0xA;
    spr.u18 = 0x19;
    spr.u1A = 0;
    for (i = 0; i < 9; i++) {
        spr.col[i] = 0xFF;
    }
    spr.u24 = 0;
    spr.u28 = 0x200405;
    spr.u2C = 0x60200;
    spr.u30 = 0x19;
    spr.u34 = 0x22;
    spr.u38 = 0x80;
    spr.u3C = 0x20;
    spr.u40 = 0;
    spr.u41 = 7;
    spr.player = 0;
    spr.u48 = 1.0f;
    spr.u4C = 1.0f;
    spr.u50 = 0.0f;
    spr.u54 = 0.0f;
    for (i = 0; i < 8; i++) {
        spr.x = i * 24.75f + -65.0f;
        spr.kind = D_800A20F0[i];
        rec = func_151559FC(&spr, 0xE, 0, 0, 2, flag, owner);
        if (rec != 0) {
            memcpy((u8 *)rec + 0x70, &span, sizeof(span));
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB398.s")
#endif

#ifdef NON_MATCHING
void func_1515835C(u8 *arg0, u8 *arg1);

s32 func_150FB708(u8 *arg0) {
    struct {
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
    } sp;

    (*(f32 *)((u8 *)arg0 + 0x5C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x54)) = -95.0f;
    (*(f32 *)((u8 *)arg0 + 0x58)) = -80.0f;
    sp.u1C = 0.0f;
    sp.u20 = 0.0f;
    sp.u24 = 0.0f;
    sp.u28 = 0.3f;
    sp.u2C = 0.3f;
    func_1515835C(arg0, &sp.u1C);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB708.s")
#endif
s32 func_151584F0(s32, s32, s32, s32, s32);
s32 func_151D76BC(s32, s32, s32, s32, s32);
void func_150FB768(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_151584F0(func_151D76BC(arg0, arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}

void func_150FB7C0(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if ((arg2 - arg3) < arg1) {
        *arg0 = (arg2 - arg1) * arg4;
        return;
    }
    *arg0 = 0xFF;
}

s32 func_150FB81C(u8 *arg0) {
    func_150FB7C0(arg0 + 0x43, *(s16 *)(arg0 + 0x16), *(s16 *)(arg0 + 0x120), *(s16 *)(arg0 + 0x64), *(s16 *)(arg0 + 0x66));
    return 1;
}

s32 func_150FB860(u8 *arg0) {
    func_150FB7C0(arg0 + 0x2E, *(s16 *)(arg0 + 0x22), *(s16 *)(arg0 + 0x70), *(s16 *)(arg0 + 0x26), *(s16 *)(arg0 + 0x28));
    return 1;
}

#ifdef NON_MATCHING
void func_150FF1A8(s32, u8, s32, s32, s32, u8, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
void func_151D49B8(u8 *, u8 *, s32, u8 *, f32, u8, s32);
extern s32 D_800A2100;
extern s32 D_800A210C;
extern s32 D_800A2118;
extern s32 D_800A2124;

void func_150FB8A4(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 * u2C;
        f32 * u30;
        f32 * u34;
        s32 * u38;
        s32 * u3C;
        s32 * u40;
        s32 u44;
        u8 pad48[0x8];
        s32 u50;
        u8 pad54[0x8];
        s32 u5C;
        u8 pad60[0x8];
        s32 u68;
        u8 pad6C[0xC];
        s32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        s32 u94;
    } sp;
    s32 temp_a2;

    (*(s32 *)((u8 *)(&sp.u68) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 0));
    (*(s32 *)((u8 *)(&sp.u68) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 4));
    (*(s32 *)((u8 *)(&sp.u68) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2100) + 8));
    (*(s32 *)((u8 *)(&sp.u5C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 0));
    (*(s32 *)((u8 *)(&sp.u5C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 4));
    (*(s32 *)((u8 *)(&sp.u5C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A210C) + 8));
    (*(s32 *)((u8 *)(&sp.u50) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 0));
    (*(s32 *)((u8 *)(&sp.u50) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 4));
    (*(s32 *)((u8 *)(&sp.u50) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2118) + 8));
    (*(s32 *)((u8 *)(&sp.u44) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 0));
    (*(s32 *)((u8 *)(&sp.u44) + 4)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 4));
    (*(s32 *)((u8 *)(&sp.u44) + 8)) = (s32) (*(s32 *)((u8 *)(&D_800A2124) + 8));
    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        sp.u38 = &sp.u68;
        sp.u3C = &sp.u50;
        sp.u40 = &sp.u44;
        sp.u2C = &sp.u94;
        sp.u30 = &sp.u88;
        sp.u34 = &sp.u7C;
        temp_a2 = (*(s32 *)((u8 *)arg0 + 0x1D4)) + 0x380;
        sp.u78 = temp_a2;
        func_15145EA4(&sp.u38, &sp.u2C, temp_a2, 3);
        sp.u7C -= sp.u88;
        sp.u80 -= sp.u8C;
        sp.u84 -= sp.u90;
        func_150FF1A8(arg0, 0xE, &sp.u68, &sp.u5C, &sp.u94, (s32) arg1, arg2);
        func_151D49B8(&sp.u88, &sp.u7C, sp.u78, arg0, 1.0f, (s32) arg1, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB8A4.s")
#endif