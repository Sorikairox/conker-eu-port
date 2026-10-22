#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} struct_eu_158110;


#ifdef NON_MATCHING
s32 func_1507C7C0(struct127 *, s16 *, s16 *, s16 *);
s32 func_150A44A4(f32, f32, s32, u8 *, f32 *);
void func_1510EE3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, s32 argC, s32 argD, s32 argE);
s32 func_151236D0(struct108 *);
s32 func_15125490(struct108 *arg0);
void func_1512523C(struct108 *arg0);
void func_15128774(struct108 *arg0, struct127 *arg1);
void func_150498A0(f32 *, f32, f32 *, f32, f32, f32);

/* P43: camera eye base / floor height of the followed object (+0x3D0). Floor (+0x35C, triangle +0x648) from
 * func_150A44A4 or the collision query func_1510EE3C (also when the floor is lost: +0x84 |= 0x800000, 10000.0), water
 * level +0x360 (from +0x364), ceiling check func_15128774; then +0x354 (eye base) = floor, raised to +0x360 when the
 * object is between water and eye, to the object's y (+0x180) when that differs by more than +0x928 (mode +0x92C),
 * or to +0x2A8; +0x348 = eye height (+0x730 with +0x6C8, else +0x34C); +0x360 + 50 in water (+0xAD == 1) unless
 * func_15125490 (flag 0x4000); flag 0x40 of +0x5F0: swim bob (+0x8C4 / +0x8CC eased by func_150498A0, +0x8D0
 * direction, +0x848 latch, flag 0x10000000); eye y (+0x2FC) >= floor + 40 outside mode 0x100.
 * The asm's early test `(+0x84 == 0) & 0x40` is always false; the mode-0x80 branch after the 0x80 test is dead. */
#define A390_F(o) (*(f32 *)(p + (o)))
void func_1512A390(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    f32 bob;           /* sp7C (written, unused) */
    s32 swim;          /* sp78 */
    s16 h0, h1, h2;    /* sp76, sp74, sp72 */
    f32 size;          /* sp6C */
    u8 *obj;           /* sp58 */
    s32 *floorTri;     /* sp54 = p + 0x648 */
    f32 *floorY;       /* sp50 = p + 0x35C */
    u8 *t;
    f32 f, g, lim;
    s32 flags;

    obj = *(u8 **)(p + 0x3D0);
    bob = *(f32 *)(obj + 0x28);
    t = *(u8 **)(p + 0x3D4);
    if (t != NULL) {
        swim = t[0x4E];
        size = *(s16 *)(t + 0x114);
    } else {
        swim = 0;
        func_1507C7C0((struct127 *)obj, &h0, &h1, &h2);
        size = h0;
    }
    flags = *(s32 *)(p + 0x84);
    if ((flags == 0) & 0x40) {  /* always false in the asm too */
        f = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x180);
        A390_F(0x354) = f;
        A390_F(0x35C) = f;
        return;
    }
    floorTri = (s32 *)(p + 0x648);
    floorY = (f32 *)(p + 0x35C);
    if (p[0x23C] != 0 || (flags & 0x400000) || (*(s32 *)(p + 0x5F0) & 0x40)
        || func_150A44A4(A390_F(0x2F8), A390_F(0x300), *(s32 *)(p + 0x644), (u8 *)floorTri, floorY) == 0) {
        func_1510EE3C((s32)(p + 0x644), (s32)floorTri, (s32)floorY, (s32)(p + 0x360), (s32)(p + 0x640), 0,
                      A390_F(0x2F8), A390_F(0x35C), A390_F(0x300), A390_F(0x308), 0, 0, 0xC61C4000,
                      *(s32 *)(p + 0x2FC), 1);
    }
    if (D_800BE9F0 == 0x28) {
        A390_F(0x364) = -10000.0f;
        A390_F(0x360) = -10000.0f;
    }
    if (A390_F(0x364) != -10000.0f) {
        A390_F(0x360) = A390_F(0x364);
    }
    func_151236D0(arg0);
    if (!(*(s32 *)(p + 0x84) & 0x10)) {
        t = *(u8 **)(p + 0x3D0);
        if (t[0x102] == 0 && D_800C3671 == 0 && p[0x92C] == 0 && *(f32 *)(t + 0x17C) < A390_F(0x35C)) {
            func_15128774(arg0, (struct127 *)t);
        }
    }
    if (A390_F(0x35C) == -10000.0f) {
        if (D_800BE616 != 0) {
            A390_F(0x35C) = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x180);
        } else {
            A390_F(0x35C) = 10000.0f;
            *(s32 *)(p + 0x84) |= 0x800000;
            f = A390_F(0x2FC);
            func_1510EE3C((s32)(p + 0x644), (s32)floorTri, (s32)floorY, (s32)(p + 0x360), (s32)(p + 0x640), 0,
                          A390_F(0x2F8), f, A390_F(0x300), A390_F(0x308), 0, 0, 0xC61C4000, *(s32 *)&f, 1);
        }
    } else {
        *(s32 *)(p + 0x84) &= ~0x800000;
    }
    if (A390_F(0x364) != -10000.0f) {
        A390_F(0x360) = A390_F(0x364);
    }
    t = *(u8 **)(p + 0x3D0);
    if (t[0x137] != 0) {
        f = *(f32 *)(t + 0x18);
        A390_F(0x354) = f;
        A390_F(0x35C) = f;
    }
    if (D_800C3671 != 0 || *(u16 *)(p + 0x7F4) != 0) {
        f = *(f32 *)(t + 0x180);
        A390_F(0x354) = f;
        A390_F(0x35C) = f;
        return;
    }
    if (((*(s32 *)(p + 0x2C) & 0x100) || *(s32 *)(p + 0x2C) != 0x80) && A390_F(0x35C) < A390_F(0x360)
        && A390_F(0x360) < A390_F(0x2FC)) {
        f = A390_F(0x360);
        A390_F(0x35C) = f;
        A390_F(0x354) = f;
    } else {
        A390_F(0x354) = A390_F(0x35C);
    }
    if (p[0x92C] != 0) {
        f = A390_F(0x354);
        if (f == -10000.0f && f < *(f32 *)(*(u8 **)(p + 0x3D0) + 0x180)) {
            A390_F(0x354) = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x180);
        } else {
            g = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x180);
            if (A390_F(0x928) < fabsf(f - g)) {
                A390_F(0x354) = g;
            }
        }
    } else if (D_800C3671 == 0) {
        flags = *(s32 *)(p + 0x84);
        if (!(flags & 0x20000000)) {
            if (flags & 0x10000000) {
                g = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x180);
                if (A390_F(0x354) < g) {
                    A390_F(0x354) = g;
                    A390_F(0x35C) = g;
                }
            }
            if (*(s32 *)(p + 0x2C) != 0x80
                || ((*(s32 *)(p + 0x5F0) & 0x80) && (*(u8 **)(p + 0x3D0))[0x81] != 0)
                || (*(s32 *)(p + 0x84) & 0x800)) {
                if (A390_F(0x354) < A390_F(0x2A8)) {
                    A390_F(0x354) = A390_F(0x2A8);
                }
            }
        }
    }
    if (!(*(s32 *)(p + 0x84) & 0x10000000) && *(s32 *)(p + 0x2C) != 0x80) {
        if ((*(s32 *)(p + 0x5F0) & 1) && swim != 0) {
            A390_F(0x35C) = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x118);
        }
        if (*(s32 *)(p + 0x2C) == 0x80) {  /* unreachable (tested just above), kept as in the asm */
            f = A390_F(0x354) + 30.0f;
            if (A390_F(0x2FC) < f) {
                A390_F(0x2FC) = f;
            }
            func_1512523C(arg0);
            return;
        }
        if (*(s32 *)(p + 0x6C8) != 0 && *(s16 *)(p + 0x730) != 0) {
            A390_F(0x348) = *(s16 *)(p + 0x730);
        } else {
            A390_F(0x348) = A390_F(0x34C);
        }
    } else {
        A390_F(0x354) = A390_F(0x35C);
    }
    f = A390_F(0x35C);
    A390_F(0x354) = f + (A390_F(0x354) - f);
    if (!(*(s32 *)(p + 0x84) & 0x4000) || func_15125490(arg0) == 0) {
        if ((*(u8 **)(p + 0x3D0))[0xAD] == 1 && *(s32 *)(p + 0x2C) != 0x80 && A390_F(0x360) != -10000.0f) {
            A390_F(0x354) = A390_F(0x360) + 50.0f;
        }
    }
    if ((*(s32 *)(p + 0x5F0) & 0x40) && (*(u8 **)(p + 0x3D0))[0x137] == 0) {
        f = A390_F(0x2A8) - A390_F(0x2B4);
        if (f < -5.0f) {
            *(s32 *)(p + 0x8D0) = 2;
            A390_F(0x8C4) += 10.0f;
        } else if (5.0f < f) {
            *(s32 *)(p + 0x8D0) = 1;
            A390_F(0x8C4) -= 10.0f;
        } else {
            *(s32 *)(p + 0x8D0) = 0;
            A390_F(0x8C4) = 0.0f;
        }
        g = A390_F(0x8C4);
        if (g < -300.0f) {
            A390_F(0x8C4) = -300.0f;
        } else {
            A390_F(0x8C4) = (300.0f < g) ? 300.0f : g;
        }
        func_150498A0((f32 *)(p + 0x8CC), A390_F(0x8C4), (f32 *)(p + 0x8C8), 1.0f, 1.5f, A390_F(0x7B4));
        f = A390_F(0x2A8) + A390_F(0x8CC) + size * 0.85f;
        A390_F(0x354) = f;
        lim = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x180) + A390_F(0x348);
        if (f < lim) {
            A390_F(0x354) = lim;
        } else {
            A390_F(0x354) = A390_F(0x354);
        }
        lim = A390_F(0x35C) + 50.0f;
        g = A390_F(0x354);
        A390_F(0x354) = (g < lim) ? lim : g;
        lim = A390_F(0x360) + 50.0f;
        g = A390_F(0x354);
        A390_F(0x354) = (g < lim) ? lim : g;
        A390_F(0x674) = 0.0f;
        p[0x848] = 1;
        *(s32 *)(p + 0x84) |= 0x10000000;
    } else if (p[0x848] != 0) {
        *(s32 *)(p + 0x84) &= ~0x10000000;
        *(s32 *)(p + 0x8D0) = 0;
        p[0x848] = 0;
        A390_F(0x674) = 1.0f;
    }
    if (*(s32 *)(p + 0x2C) != 0x100 && (*(u8 **)(p + 0x3D0))[0x137] == 0) {
        f = A390_F(0x35C) + 40.0f;
        if (A390_F(0x2FC) < f) {
            A390_F(0x2FC) = f;
        }
    }
}
#undef A390_F
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512A390.s")
#endif

#ifdef NON_MATCHING
extern s16 D_80089930[4][4];      /* default viewport rects (x, y, w, h?) for slots 0..3 */
extern s16 D_800DC630[4][4][4];   /* per player count: the viewport rects */
extern u8 D_800DC4F0[];

/* Camera tables reset: copy the 4 default viewport rects into each of the 4 per-player-count tables, halving the
 * first two halfwords in split screen (1..3 extra players) and scaling them by 0.75 on levels 0x1B / 0x1E; clear D_800DC4F0. */
void func_1512B168(void) {
    u8 i, j;
    s16 *r;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            r = D_800DC630[i][j];
            r[0] = D_80089930[j][0];
            r[1] = D_80089930[j][1];
            r[2] = D_80089930[j][2];
            r[3] = D_80089930[j][3];
            if (D_80082FA0 > 0 && D_80082FA0 < 4) {
                r[0] = (s32)(r[0] * 0.5f);
                r[1] = (s32)(r[1] * 0.5f);
            }
            if (D_800BE9F0 == 0x1B || D_800BE9F0 == 0x1E) {
                r[0] = (s32)(r[0] * 0.75f);
                r[1] = (s32)(r[1] * 0.75f);
            }
        }
    }
    bzero(D_800DC4F0, 0x130);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B168.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B2C4.s")

s32 func_1512B2C4();

void func_1512B670(u8 *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x2C));
    if ((temp_v0 & ~0x100) && (D_800BEAC0 == 0) && (D_800C3671 == 0)) {
        if (temp_v0 != 0x40) {
            temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x84));
            if ((temp_v0_2 & 8) && !(temp_v0_2 & 0x200) && ((*(u8 *)((u8 *)arg0 + 0x23C)) == 0)) {
                temp_v0_3 = (*(s32 *)((u8 *)arg0 + 0x5F0));
                if (!(temp_v0_3 & 0x80) && !(temp_v0_3 & 0x40)) {
                    func_1512B2C4();
                    return;
                }
            }
        }
        (*(s16 *)((u8 *)arg0 + 0x5F8)) = 1;
        (*(s16 *)((u8 *)arg0 + 0x5FC)) = 2;
        (*(s16 *)((u8 *)arg0 + 0x5FE)) = 0x32;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BAAC.s")

void func_1512BB6C(struct_eu_158110 *arg0, s32 arg1, s32 arg2) {
    arg0->unk2 = arg0->unk1;
    if (arg0->unk4 < arg1) {
        arg0->unk1 = 0;
    } else {
        arg0->unk1 = 1;
    }
    arg0->unk8 = arg2;
    arg0->unk4 = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BBA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BCA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C080.s")

void func_15123A54(u8 *);
s32 func_1512C6C0(u8 *);

void func_1512C5D8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    f32 var_f14;
    s32 temp_v0;

    if ((*(f32 *)((u8 *)arg0 + 0x390)) < 180.0f) {
        var_f14 = 2.0f;
    } else {
        var_f14 = -2.0f;
    }
    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x2C));
    if ((temp_v0 != 0x80) && (temp_v0 != 0x40)) {
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x2F8)) - (*(f32 *)((u8 *)arg0 + 0x2BC));
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x300)) - (*(f32 *)((u8 *)arg0 + 0x2C4));
        temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
        (*(f32 *)((u8 *)arg0 + 0x370)) = temp_f0;
        if (temp_f0 < 42.0f) {
            (*(f32 *)((u8 *)arg0 + 0x384)) = (*(f32 *)((u8 *)arg0 + 0x37C)) - 45.0f * var_f14;
            (*(f32 *)((u8 *)arg0 + 0x5CC)) = 0.0f;
            func_15123A54(arg0);
            (*(s32 *)((u8 *)arg0 + 0x240)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x240)) | 2);
        }
    }
    func_1512C6C0(arg0);
}

#ifdef NON_MATCHING
/* P43: fade-in of +0x5CC (+0.006 per call, up to 1.0); at 1.0 clears flag 2 of +0x240 and sets +0x384 = 999.0,
 * else +0x384 += func_15048A70(+0x384, +0x37C) * +0x5CC. The asm returns no value (callers ignore it). */
s32 func_1512C6C0(u8 *arg0) {
    f32 f;

    *(f32 *)(arg0 + 0x5CC) += 0.006f;
    f = *(f32 *)(arg0 + 0x5CC);
    if (f > 1.0f) {
        *(f32 *)(arg0 + 0x5CC) = 1.0f;
    } else {
        *(f32 *)(arg0 + 0x5CC) = f;
    }
    if (*(f32 *)(arg0 + 0x5CC) == 1.0f) {
        *(s32 *)(arg0 + 0x240) &= ~2;
        *(f32 *)(arg0 + 0x384) = 999.0f;
        return 0;
    }
    f = func_15048A70(*(f32 *)(arg0 + 0x384), *(f32 *)(arg0 + 0x37C));
    *(f32 *)(arg0 + 0x384) += f * *(f32 *)(arg0 + 0x5CC);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C6C0.s")
#endif

void func_1512C770(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C77C.s")

s32 func_1512C9EC(s32 arg0) {
    return 1;
}
