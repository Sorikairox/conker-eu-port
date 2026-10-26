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
s32 obj_collision_cylinder(struct127 *, s16 *, s16 *, s16 *);
s32 floor_tri_height(f32, f32, s32, u8 *, f32 *);
void collision_find_floor_no_fallback(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, s32 argC, s32 argD, s32 argE);
void camera_update_state_flags(struct108 *); /* P68: void, v0 is undefined in the asm */
s32 camera_target_deep_in_water(struct108 *arg0);
void camera_calc_pitch(struct108 *arg0);
void camera_snap_to_object(struct108 *arg0, struct127 *arg1);
void math_spring_approach(f32 *, f32, f32 *, f32, f32, f32);

/* P43: camera eye base / floor height of the followed object (+0x3D0). Floor (+0x35C, triangle +0x648) from
 * floor_tri_height or the collision query collision_find_floor_no_fallback (also when the floor is lost: +0x84 |= 0x800000, 10000.0), water
 * level +0x360 (from +0x364), ceiling check camera_snap_to_object; then +0x354 (eye base) = floor, raised to +0x360 when the
 * object is between water and eye, to the object's y (+0x180) when that differs by more than +0x928 (mode +0x92C),
 * or to +0x2A8; +0x348 = eye height (+0x730 with +0x6C8, else +0x34C); +0x360 + 50 in water (+0xAD == 1) unless
 * camera_target_deep_in_water (flag 0x4000); flag 0x40 of +0x5F0: swim bob (+0x8C4 / +0x8CC eased by math_spring_approach, +0x8D0
 * direction, +0x848 latch, flag 0x10000000); eye y (+0x2FC) >= floor + 40 outside mode 0x100.
 * The asm's early test `(+0x84 == 0) & 0x40` is always false; the mode-0x80 branch after the 0x80 test is dead. */
#define A390_F(o) (*(f32 *)(p + (o)))
/* was func_1512A390 */
void camera_update_eye_base(struct108 *arg0) {
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
        obj_collision_cylinder((struct127 *)obj, &h0, &h1, &h2);
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
        || floor_tri_height(A390_F(0x2F8), A390_F(0x300), *(s32 *)(p + 0x644), (u8 *)floorTri, floorY) == 0) {
        collision_find_floor_no_fallback((s32)(p + 0x644), (s32)floorTri, (s32)floorY, (s32)(p + 0x360), (s32)(p + 0x640), 0,
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
    camera_update_state_flags(arg0);
    if (!(*(s32 *)(p + 0x84) & 0x10)) {
        t = *(u8 **)(p + 0x3D0);
        if (t[0x102] == 0 && D_800C3671 == 0 && p[0x92C] == 0 && *(f32 *)(t + 0x17C) < A390_F(0x35C)) {
            camera_snap_to_object(arg0, (struct127 *)t);
        }
    }
    if (A390_F(0x35C) == -10000.0f) {
        if (D_800BE616 != 0) {
            A390_F(0x35C) = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x180);
        } else {
            A390_F(0x35C) = 10000.0f;
            *(s32 *)(p + 0x84) |= 0x800000;
            f = A390_F(0x2FC);
            collision_find_floor_no_fallback((s32)(p + 0x644), (s32)floorTri, (s32)floorY, (s32)(p + 0x360), (s32)(p + 0x640), 0,
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
            camera_calc_pitch(arg0);
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
    if (!(*(s32 *)(p + 0x84) & 0x4000) || camera_target_deep_in_water(arg0) == 0) {
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
        math_spring_approach((f32 *)(p + 0x8CC), A390_F(0x8C4), (f32 *)(p + 0x8C8), 1.0f, 1.5f, A390_F(0x7B4));
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/camera_update_eye_base.s")
#endif

#ifdef NON_MATCHING
extern s16 D_80089930[4][4];      /* default viewport rects (x, y, w, h?) for slots 0..3 */
extern s16 D_800DC630[4][4][4];   /* per player count: the viewport rects */
extern u8 D_800DC4F0[];

/* Camera tables reset: copy the 4 default viewport rects into each of the 4 per-player-count tables, halving the
 * first two halfwords in split screen (1..3 extra players) and scaling them by 0.75 on levels 0x1B / 0x1E; clear D_800DC4F0. */
/* was func_1512B168 */
void camera_viewport_tables_reset(void) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/camera_viewport_tables_reset.s")
#endif
#ifdef NON_MATCHING
/* P96: freecam_auto_step */
extern f32 D_800DC620;   /* screen x of the eye (camera_world_to_screen) */
extern f32 D_800DC624;   /* screen y */
extern f32 D_800DC628;   /* depth */
extern f32 D_800DC62C;   /* drop (freecam_turn) */
s32 freecam_reset_countdown(u8 *);
void freecam_scan_depth(u8 *, s32, s32, s32);
s32 freecam_turn(u8 *, f32 *, f32 *);
void camera_world_to_screen(s32 arg0, f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz);
void vec_rotate_xz_about_point(u8 *, u8 *, f32, u8 *);
#endif
#ifdef NON_MATCHING
/* Free camera step of camera `arg0` (called by freecam_auto_update). Unless freecam_reset_countdown handles the frame, the eye
 * (+0x2BC / +0x2C0 / +0x2C4; the height kept 40 below the holder's ceiling +0x17C when it is above its floor
 * +0x180, unless +0x84 bit 0x10) is projected to the screen (camera_world_to_screen into D_800DC620 / 624 / 628). Off the
 * player's viewport (D_800BE628 entry +0x24..+0x30; x / y clamped first) +0x5F8 = 1 and +0x8B8 = 0. Else +0x8B8 = 1,
 * +0x8BA = y, freecam_scan_depth gets the clamped point and the depth, freecam_turn gives the turn +0x3EC and the drop
 * D_800DC62C: a turn above 3 rotates the target +0x2F8 about the eye (vec_rotate_xz_about_point) and eases it in (speed 6 / 8,
 * * 1.2 with buttons 3 of the input record), +0x5F8 = 0; else +0x5F8 = 1. The drop lowers +0x2FC; +0x240 == 1 is
 * cleared, +0x698 always. */
/* was func_1512B2C4 */
void freecam_auto_step(u8 *arg0) {
    u8 *p = arg0;
    u8 *hold;
    u8 *e;
    f32 y;
    f32 sp[3];
    f32 speed;
    f32 rate;
    s32 xi;
    s32 yi;
    s32 lo;
    s32 hi;
    s32 v;
    s32 depth;

    y = *(f32 *)(p + 0x2C0);
    if (freecam_reset_countdown(p) != 0) {
        return;
    }
    if (!(*(s32 *)(p + 0x84) & 0x10)) {
        hold = *(u8 **)(p + 0x3D0);
        if (*(f32 *)(hold + 0x180) < *(f32 *)(hold + 0x17C) && *(f32 *)(hold + 0x17C) - 40.0f <= y) {
            y = *(f32 *)(hold + 0x17C) - 40.0f;
        }
    }
    camera_world_to_screen(p[0x23D], *(f32 *)(p + 0x2BC), y, *(f32 *)(p + 0x2C4), &D_800DC620, &D_800DC624, &D_800DC628);
    e = (u8 *)D_800BE628 + p[0x23D] * 0x180;
    depth = (s32)D_800DC628;
    lo = (s32)*(f32 *)(e + 0x2C);
    v = (s32)D_800DC620;
    if (v < lo) {
        xi = lo;
    } else {
        hi = (s32)*(f32 *)(e + 0x30);
        xi = (hi < v) ? hi : v;
    }
    lo = (s32)*(f32 *)(e + 0x24);
    v = (s32)D_800DC624;
    if (v < lo) {
        yi = lo;
    } else {
        hi = (s32)*(f32 *)(e + 0x28);
        yi = (hi < v) ? hi : v;
    }
    if ((f32)xi < *(f32 *)(e + 0x2C) || *(f32 *)(e + 0x30) <= (f32)xi || (f32)yi < *(f32 *)(e + 0x24) ||
        *(f32 *)(e + 0x28) <= (f32)yi) {
        *(s16 *)(p + 0x5F8) = 1;
        p[0x8B8] = 0;
        return;
    }
    p[0x8B8] = 1;
    *(s16 *)(p + 0x8BA) = yi;
    freecam_scan_depth(p, xi, yi, depth);
    sp[0] = *(f32 *)(p + 0x2F8);
    sp[1] = *(f32 *)(p + 0x2FC);
    sp[2] = *(f32 *)(p + 0x300);
    freecam_turn(p, (f32 *)(p + 0x3EC), &D_800DC62C);
    if (3.0f < fabsf(*(f32 *)(p + 0x3EC))) {
        vec_rotate_xz_about_point((u8 *)sp, p + 0x2BC, *(f32 *)(p + 0x3EC), (u8 *)sp);
        speed = 6.0f;
        rate = 8.0f;
        if (**(u16 **)(p + 0x36C) & 3) {
            speed = 6.0f * 1.2f;
            rate = 8.0f * 1.2f;
        }
        math_spring_approach((f32 *)(p + 0x2F8), sp[0], (f32 *)(p + 0x3FC), speed, rate, *(f32 *)(p + 0x7B4));
        math_spring_approach((f32 *)(p + 0x2FC), sp[1], (f32 *)(p + 0x400), speed, rate, *(f32 *)(p + 0x7B4));
        math_spring_approach((f32 *)(p + 0x300), sp[2], (f32 *)(p + 0x404), speed, rate, *(f32 *)(p + 0x7B4));
        *(s16 *)(p + 0x5F8) = 0;
    } else {
        *(s16 *)(p + 0x5F8) = 1;
    }
    if (D_800DC62C != 0.0f) {
        *(f32 *)(p + 0x2FC) -= D_800DC62C;
    }
    if (*(s32 *)(p + 0x240) == 1) {
        *(s32 *)(p + 0x240) = 0;
    }
    *(s32 *)(p + 0x698) = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/freecam_auto_step.s")
#endif
#ifdef NON_MATCHING
void freecam_auto_step(u8 *arg0);
#else
s32 freecam_auto_step();
#endif

/* was func_1512B670 */
void freecam_auto_update(u8 *arg0) {
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
#ifdef NON_MATCHING
                    freecam_auto_step(arg0);   /* P77: the asm passes arg0 in a0 (the callee reads it) */
#else
                    freecam_auto_step();
#endif
                    return;
                }
            }
        }
        (*(s16 *)((u8 *)arg0 + 0x5F8)) = 1;
        (*(s16 *)((u8 *)arg0 + 0x5FC)) = 2;
        (*(s16 *)((u8 *)arg0 + 0x5FE)) = 0x32;
    }
}

#ifdef NON_MATCHING
s32 freecam_axis_threshold_test(u8 *cam, u8 *out, s32 lo, s32 hi, s32 value, s32 second);
extern s16 D_800DC630[4][4][4];
extern u8 D_800DC4F0[];
extern s32 D_800899D0[8][2];   /* z-buffer decode per exponent (code >> 13): {shift, add} */

/* free_camera_scan_depth: free-camera depth scan of camera `cam` at screen column `x` (called by freecam_auto_step;
 * `y` is not used). The scan width +0x60C and height +0x610 ease (0.05) toward the player's viewport rect
 * (D_800DC630[player][+0x1B4 slot], w / h); n = round(+0x60C). For i from n / 4 to n, left (x - i, while right of
 * the viewport's +0x2C) and then right (x + i, while left of +0x30): the z-buffer row +0x8BC is decoded
 * (D_800899D0) and depth - z goes to freecam_axis_threshold_test with the left / right axis record of D_800DC4F0[player]
 * (+0 / +0xC; threshold 3n / 4); a hit ends that side. (The asm also keeps every depth - z in a stack array
 * nobody reads; dropped.) */
/* was func_1512B728 */
void freecam_scan_depth(u8 *cam, s32 x, s32 y, s32 depth) {
    s16 *rect = D_800DC630[cam[0x23D]][*(s16 *)(cam + 0x1B4)];
    u8 *e;
    s32 n;
    s32 start;
    s32 i;
    u16 code;
    s32 lo;

    *(f32 *)(cam + 0x60C) += ((f32)rect[0] - *(f32 *)(cam + 0x60C)) * 0.05f;
    n = (s16)((f32)(s16)*(f32 *)(cam + 0x60C) + 0.5f);
    *(f32 *)(cam + 0x610) += ((f32)rect[1] - *(f32 *)(cam + 0x610)) * 0.05f;
    start = n / 4;
    for (i = start; i < n; i++) {
        e = (u8 *)D_800BE628 + cam[0x23D] * 0x180;
        if (*(f32 *)(e + 0x2C) < (f32)(x - i)) {
            code = (*(u16 **)(cam + 0x8BC))[x - i];
            lo = depth - ((u32)(D_800899D0[code >> 13][1] + (((code >> 2) & 0x7FF) << D_800899D0[code >> 13][0])) >> 3);
            if (freecam_axis_threshold_test(cam, D_800DC4F0 + cam[0x23D] * 0x4C, lo, i, n * 3 / 4, 0) != 0) {
                i = n;
            }
        }
    }
    for (i = start; i < n; i++) {
        e = (u8 *)D_800BE628 + cam[0x23D] * 0x180;
        if ((f32)(x + i) < *(f32 *)(e + 0x30)) {
            code = (*(u16 **)(cam + 0x8BC))[x + i];
            lo = depth - ((u32)(D_800899D0[code >> 13][1] + (((code >> 2) & 0x7FF) << D_800899D0[code >> 13][0])) >> 3);
            if (freecam_axis_threshold_test(cam, D_800DC4F0 + cam[0x23D] * 0x4C + 0xC, lo, i, n * 3 / 4, 0) != 0) {
                i = n;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/freecam_scan_depth.s")
#endif
#ifdef NON_MATCHING
/* Free-camera reset countdown (called by freecam_auto_step): while +0x5FC (frames) is set, mark +0x5F8, fill the first
 * ceil(n) halfwords of the +0x8BC buffer with 0xFFFC (n = +4 of the camera's player entry in D_800BE628, 0x180
 * bytes each), clear +0x60C and count +0x5FC down; returns 1 then, else 0. */
/* was func_1512BAAC */
s32 freecam_reset_countdown(u8 *cam) {
    s32 i;

    if (*(s16 *)(cam + 0x5FC) == 0) {
        return 0;
    }
    *(s16 *)(cam + 0x5F8) = 1;
    for (i = 0; (f32)i < *(f32 *)((u8 *)D_800BE628 + cam[0x23D] * 0x180 + 4); i++) {
        (*(s16 **)(cam + 0x8BC))[i] = 0xFFFC;
    }
    *(f32 *)(cam + 0x60C) = 0.0f;
    *(s16 *)(cam + 0x5FC) -= 1;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/freecam_reset_countdown.s")
#endif
/* was func_1512BB6C */
void freecam_axis_record_set(struct_eu_158110 *arg0, s32 arg1, s32 arg2) {
    arg0->unk2 = arg0->unk1;
    if (arg0->unk4 < arg1) {
        arg0->unk1 = 0;
    } else {
        arg0->unk1 = 1;
    }
    arg0->unk8 = arg2;
    arg0->unk4 = arg1;
}

#ifdef NON_MATCHING
void freecam_axis_record_set(struct_eu_158110 *arg0, s32 arg1, s32 arg2);
extern s16 D_800DC634[];
extern s16 D_800DC636[];

/* Stick threshold test for free-camera axis `out` (called twice by freecam_scan_depth): limit = the camera's player
 * table entry (D_800DC634 / D_800DC636 by `second`, 0x20 bytes per player, 8 per +0x1B4 slot), doubled with
 * +0x84 bit 0x8000. Below `lo` with `hi` past `value` on either side: direction 2 (hi > value) or 1 (hi < value),
 * freecam_axis_record_set(out, hi, lo) (it reads a2 = lo, which the asm leaves there), return 1. Otherwise the axis is reset
 * (+0 / +1 = 0, +8 = 0xFFFC) and 0 is returned. */
/* was func_1512BBA0 */
s32 freecam_axis_threshold_test(u8 *cam, u8 *out, s32 lo, s32 hi, s32 value, s32 second) {
    s32 v;
    s32 off = cam[0x23D] * 0x20 + *(s16 *)(cam + 0x1B4) * 8;

    if (second == 0) {
        v = *(s16 *)((u8 *)D_800DC634 + off);
    } else {
        v = *(s16 *)((u8 *)D_800DC636 + off);
    }
    if (*(s32 *)(cam + 0x84) & 0x8000) {
        v = (s16)(v << 1);
    }
    if (v < lo && hi < value) {
        out[0] = 2;
        freecam_axis_record_set((struct_eu_158110 *)out, hi, lo);
        return 1;
    }
    if (v < lo && value < hi) {
        out[0] = 1;
        freecam_axis_record_set((struct_eu_158110 *)out, hi, lo);
        return 1;
    }
    out[1] = 0;
    out[0] = 0;
    *(s32 *)(out + 8) = 0xFFFC;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/freecam_axis_threshold_test.s")
#endif
#ifdef NON_MATCHING
extern s16 D_800DC630[4][4][4];
extern u8 D_800DC4F0[];

/* free_camera_turn: turn of camera `cam` from its player's four free-camera axis records (D_800DC4F0, 0x4C per
 * player: left +0, right +0xC, +0x18, +0x24, each with direction byte +0 and position +4; last side +0x30). Called by
 * freecam_auto_step (`unused` is never read). Left only / right only sets the last side 0 / 1 (+0x18 / +0x24: 2 / 3).
 * With left or right blocked (direction 2): *turn = w - (left + 1) or (right + 1) - w (w = viewport width + 1); both
 * blocked: the nearer side (or the last one) decides, the countdown +0x5FE drops by D_800BE9E4 (unless the holder
 * +0x3D0 has +0xAD == 1 or +0x3D4 has +0x120 set) and +0x3F0 = 30 unless mode +0x2C is 0x80; +0x26C = 0.005,
 * returns 1. Neither: both directions = 4, *turn decays by 10 %, +0x5FE = 50, returns 0. While +0x3F0 counts down
 * the distances +0x374 / +0x348 are saved in +0x3F4 / +0x3F8 and set to 150 / 275, and restored after. */
/* was func_1512BCA0 */
s32 freecam_turn(u8 *cam, f32 *turn, f32 *unused) {
    u8 *e = D_800DC4F0 + cam[0x23D] * 0x4C;
    f32 left = (f32)*(s32 *)(e + 0x4) + 1.0f;
    f32 right = (f32)*(s32 *)(e + 0x10) + 1.0f;
    u8 dl = e[0x0];
    u8 dr = e[0xC];
    u8 d2 = e[0x18];
    u8 d3 = e[0x24];
    s32 hit = 0;
    f32 w;
    f32 saved;

    if (dl == 2 && dr != 2) {
        e[0x30] = 0;
    } else if (dl != 2 && dr == 2) {
        e[0x30] = 1;
    }
    if (d2 == 2 && d3 != 2) {
        e[0x30] = 2;
    } else if (d2 != 2 && d3 == 2) {
        e[0x30] = 3;
    }
    if (dl == 2 || dr == 2) {
        w = D_800DC630[cam[0x23D]][*(s16 *)(cam + 0x1B4)][0] + 1;
        if (dl == 2 && dr == 2) {
            if ((*(u8 **)(cam + 0x3D0))[0xAD] != 1 && (*(u8 **)(cam + 0x3D4))[0x120] == 0) {
                *(s16 *)(cam + 0x5FE) -= D_800BE9E4;
                if (*(s16 *)(cam + 0x5FE) < 0) {
                    *(s16 *)(cam + 0x5FE) = 0;
                }
            }
            if (*(s32 *)(cam + 0x2C) != 0x80) {
                *(s16 *)(cam + 0x3F0) = 30;
            }
            e = D_800DC4F0 + cam[0x23D] * 0x4C;
            if (*(s32 *)(e + 0x10) < *(s32 *)(e + 0x4)) {
                *turn = w - left;
            } else if (*(s32 *)(e + 0x4) < *(s32 *)(e + 0x10)) {
                *turn = right - w;
            } else if (e[0x30] == 0) {
                *turn = w - left;
            } else {
                *turn = right - w;
            }
        } else {
            *(s16 *)(cam + 0x3F0) = 0;
            *(s16 *)(cam + 0x5FE) = 50;
            e = D_800DC4F0 + cam[0x23D] * 0x4C;
            /* (the asm tests +0x23C here; both of its branches compute the same value) */
            if (e[0] == 2) {
                *turn = w - ((f32)*(s32 *)(e + 0x4) + 1.0f);
            } else {
                *turn = ((f32)*(s32 *)(e + 0x10) + 1.0f) - w;
            }
        }
        *(f32 *)(cam + 0x26C) = 0.005f;
        hit = 1;
    } else {
        e[0x0] = 4;
        e[0xC] = 4;
        *turn -= *turn * 0.1f;
        *(s16 *)(cam + 0x5FE) = 50;
    }
    if (*(s16 *)(cam + 0x3F0) != 0) {
        *(s16 *)(cam + 0x3F0) -= D_800BE9E4;
        if (*(s16 *)(cam + 0x3F0) < 0) {
            *(s16 *)(cam + 0x3F0) = 0;
        }
        if (*(f32 *)(cam + 0x3F4) == -1.0f) {
            *(f32 *)(cam + 0x3F4) = *(f32 *)(cam + 0x374);
            *(f32 *)(cam + 0x3F8) = *(f32 *)(cam + 0x348);
            *(f32 *)(cam + 0x374) = 150.0f;
            *(f32 *)(cam + 0x348) = 275.0f;
        }
    } else if (*(f32 *)(cam + 0x3F4) != -1.0f) {
        saved = *(f32 *)(cam + 0x3F8);
        *(f32 *)(cam + 0x374) = *(f32 *)(cam + 0x3F4);
        *(f32 *)(cam + 0x3F4) = -1.0f;
        *(f32 *)(cam + 0x3F8) = -1.0f;
        *(f32 *)(cam + 0x348) = saved;
    }
    return hit;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/freecam_turn.s")
#endif
#ifdef NON_MATCHING
/* Camera eye collision. Unless collision is off (+0x84 flags 0x40000 / 0x80 / 0x200, the followed object
 * +0x3D4 has +0x95 set, or mode +0x2C == 0x40: then +0x3E8 = 1), the eye's collision ellipsoid size
 * (+0x94C width, +0x950 height) is picked from the situation and eased into +0x95C / +0x960 (math_spring_approach,
 * speeds +0x954 / +0x958; set at once while +0x23C is set). A probe object (struct127, type 0x2D, camera
 * = this one) at the eye (+0x2F8; y raised by +0x18C with flag 0x800 of +0x5F0) is moved by collision_obj_walls
 * from the previous eye (+0x304) with the collision globals D_800CC1F2..F4 and D_800894C0[1..2] set for the
 * call and restored after it. The probe's final position is the new eye (y not in mode 0x100);
 * +0x3E8 = no collision, +0x26C eases to 1.0 (0.1 per frame) or drops to 0.005 on a hit. After a hit the
 * eye is kept 40 above the floor below it (collision_find_floor_no_fallback), except in level 0x1B and mode 0x100.
 * Always ends with camera_update_state_flags (state flags). The asm leaves v0 undefined: void under NM. */
extern u8 D_800894C0[];
extern u8 D_800CC1F2;
extern u8 D_800CC1F3;
extern u8 D_800CC1F4;
s32 collision_obj_walls(f32 fromX, f32 fromY, s32 fromZBits, struct127 *probe, s32 arg4, s32 arg5);
#define C080_F(o) (*(f32 *)(p + (o)))
#define C080_W(o) (*(s32 *)(p + (o)))
/* was func_1512C080 */
void camera_eye_collision(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    struct127 probe;      /* sp74 */
    f32 floorY;           /* sp60 */
    u8 *target = *(u8 **)(p + 0x3D4);
    u8 *followed;
    s32 small = FALSE;    /* t3: the size used is the small "close" one */
    s32 savedSlide;       /* D_800894C0[2] */
    s32 savedStep;        /* D_800894C0[1] */
    s32 saved1F3;
    s32 saved1F4;
    s32 hit;
    s16 view;

    if ((C080_W(0x84) & 0x40000) || target[0x95] != 0 || C080_W(0x2C) == 0x40 || (C080_W(0x84) & 0x80) ||
        (C080_W(0x84) & 0x200)) {
        p[0x3E8] = 1;
        camera_update_state_flags(arg0);
        return;
    }
    savedSlide = D_800894C0[2];
    savedStep = D_800894C0[1];

    /* collision size */
    if (C080_W(0x5F0) & 0x800) {
        C080_F(0x94C) = 20.0f;
        C080_F(0x950) = 40.0f;
    } else if (C080_W(0x5F0) & 0x10) {
        C080_F(0x94C) = 20.0f;
        C080_F(0x950) = 72.0f;
    } else if (580.0f < C080_F(0x374)) {
        C080_F(0x94C) = 70.0f;
        C080_F(0x950) = 140.0f;
    } else if (D_800BE9F0 == 0x31 && p[0x23E] == 3) {
        C080_F(0x94C) = 20.0f;
        C080_F(0x950) = 50.0f;
        small = TRUE;
    } else {
        view = *(s16 *)(p + 0x73C);
        followed = *(u8 **)(p + 0x3D0);
        if ((view == 0 || view == 1 || view == 3) &&
            (followed[0x102] == 0 || (C080_F(0x2B0) == *(f32 *)(followed + 0x14) &&
                                      C080_F(0x2B8) == *(f32 *)(followed + 0x1C))) &&
            target[0x1B3] == 0) {
            if (followed[0x102] != 0) {
                C080_F(0x94C) = 25.0f;
                C080_F(0x950) = 30.0f;
                small = TRUE;
            } else {
                C080_F(0x94C) = 30.0f;
                C080_F(0x950) = 60.0f;
            }
        } else {
            C080_F(0x94C) = 20.0f;
            C080_F(0x950) = 20.0f;
        }
    }
    if (p[0x23C] != 0) {
        C080_F(0x954) = 0.0f;
        C080_F(0x95C) = C080_F(0x94C);
        C080_F(0x958) = 0.0f;
        C080_F(0x960) = C080_F(0x950);
    } else {
        math_spring_approach((f32 *)(p + 0x95C), C080_F(0x94C), (f32 *)(p + 0x954), 4.0f, 6.0f, C080_F(0x7B4));
        math_spring_approach((f32 *)(p + 0x960), C080_F(0x950), (f32 *)(p + 0x958), 4.0f, 6.0f, C080_F(0x7B4));
    }

    /* the probe */
    probe.interaction_state = 0x2D;
    probe.camera = arg0;
    probe.x_position = C080_F(0x2F8);
    if (C080_W(0x5F0) & 0x800) {
        probe.y_position = C080_F(0x2FC) + C080_F(0x18C);
    } else {
        probe.y_position = C080_F(0x2FC);
    }
    probe.z_position = C080_F(0x300);
    probe.unk188 = C080_W(0x644);
    probe.unk28 = probe.y_position - C080_F(0x354);
    probe.y_velocity = 0.0f;
    probe.unk180 = C080_F(0x354);
    probe.unk40 = C080_F(0x37C);

    if ((C080_W(0x84) & 0x80000000) || D_800BE9F0 == 0x37) {
        D_800894C0[2] = 0;
    }
    if (C080_W(0x84) & 0x10000) {
        D_800894C0[1] = 0;
    }
    D_800CC1F2 = 1;
    saved1F3 = D_800CC1F3;
    D_800CC1F3 = (((u8 *)*(u8 **)(p + 0x3D0))[0x102] != 0) ? 1 : 0;
    saved1F4 = D_800CC1F4;
    D_800CC1F4 = (p[0x23C] != 0 || (C080_W(0x2C) == 0x100 && !small)) ? 1 : 0;
    hit = collision_obj_walls(C080_F(0x304), C080_F(0x308), C080_W(0x30C), &probe, 0, 0);
    D_800CC1F4 = saved1F4;
    D_800CC1F2 = 0;
    D_800CC1F3 = saved1F3;
    D_800894C0[2] = savedSlide;
    D_800894C0[1] = savedStep;

    if (hit != 0) {
        p[0x3E8] = 0;
        C080_F(0x26C) = 0.005f; /* D_800A3A68 */
    } else {
        p[0x3E8] = 1;
        C080_F(0x26C) = C080_F(0x26C) + (1.0f - C080_F(0x26C)) * 0.1f; /* D_800A3A6C */
    }
    C080_F(0x2F8) = probe.x_position;
    if (C080_W(0x2C) != 0x100) {
        if (C080_W(0x5F0) & 0x800) {
            C080_F(0x2FC) = probe.y_position - C080_F(0x18C);
        } else {
            C080_F(0x2FC) = probe.y_position;
        }
    }
    C080_F(0x300) = probe.z_position;
    if (D_800BE9F0 != 0x1B && hit != 0 && C080_W(0x2C) != 0x100) {
        collision_find_floor_no_fallback(0, 0, (s32)&floorY, 0, 0, 0, C080_F(0x2F8), C080_F(0x2FC), C080_F(0x300), C080_F(0x308), 0, 0,
                      0xC61C4000 /* -10000.0f, D_800A3A70 */, *(s32 *)(p + 0x2FC), 1);
        if (C080_F(0x2FC) < floorY + 40.0f) {
            C080_F(0x2FC) = floorY + 40.0f;
        }
    }
    camera_update_state_flags(arg0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/camera_eye_collision.s")
#endif

void camera_update_eye_orbit(u8 *);
s32 camera_yaw_fade_in(u8 *);

/* was func_1512C5D8 */
void camera_too_close_swing(u8 *arg0) {
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
            camera_update_eye_orbit(arg0);
            (*(s32 *)((u8 *)arg0 + 0x240)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x240)) | 2);
        }
    }
    camera_yaw_fade_in(arg0);
}

#ifdef NON_MATCHING
/* P43: fade-in of +0x5CC (+0.006 per call, up to 1.0); at 1.0 clears flag 2 of +0x240 and sets +0x384 = 999.0,
 * else +0x384 += math_angle_diff_deg(+0x384, +0x37C) * +0x5CC. The asm returns no value (callers ignore it). */
/* was func_1512C6C0 */
s32 camera_yaw_fade_in(u8 *arg0) {
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
    f = math_angle_diff_deg(*(f32 *)(arg0 + 0x384), *(f32 *)(arg0 + 0x37C));
    *(f32 *)(arg0 + 0x384) += f * *(f32 *)(arg0 + 0x5CC);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/camera_yaw_fade_in.s")
#endif

/* was func_1512C770 */
void camera_step_noop(s32 arg0) {
}

#ifdef NON_MATCHING
/* Camera collision with a cylinder (struct108 viewed as bytes, as the rest of this file does).
 * When the request flag +0x948 is set and the camera position (+0x2F8, a vec3) lies inside the circle of
 * radius +0x938 around (+0x93C, +0x944), the camera is pushed out onto the circle along the line from the
 * centre and turned 5 degrees around it (away from the side it came from) when the push direction is
 * within 35 degrees of the view direction. +0x930 = the new heading to the target (+0x2A4) or the old
 * heading +0x37C when outside; D_80089950 = horizontal distance to the target (0 when nothing was done).
 * The request flag is always cleared. The asm leaves v0 undefined: void under NM. */
extern f32 D_80089950;
void vec_rotate_xz_about_point(u8 *, u8 *, f32, u8 *);
#define C108_F32(o) (*(f32 *)(arg0 + (o)))
/* was func_1512C77C */
void camera_cylinder_push(u8 *arg0) {
    struct17 *camPos;
    struct17 *centre;
    struct17 pos;
    struct17 dir;
    struct17 toTarget;
    struct17 target;
    f32 dx, dz;
    f32 pushAngle;
    f32 heading;
    f32 delta;
    f32 targetDist;

    if (arg0[0x948] == 0) {
        D_80089950 = 0.0f;
        C108_F32(0x930) = 0.0f;
        arg0[0x948] = 0;
        return;
    }
    dx = C108_F32(0x2F8) - C108_F32(0x93C);
    dz = C108_F32(0x300) - C108_F32(0x944);
    camPos = (struct17 *)(arg0 + 0x2F8);
    pos = *camPos;
    if (!(sqrtf(dx * dx + dz * dz) < C108_F32(0x938))) {
        D_80089950 = 0.0f;
        C108_F32(0x930) = C108_F32(0x37C);
        arg0[0x948] = 0;
        return;
    }

    /* work in the horizontal plane */
    target = *(struct17 *)(arg0 + 0x2A4);
    target.unk4 = 0.0f;
    pos.unk4 = 0.0f;
    C108_F32(0x940) = 0.0f;
    centre = (struct17 *)(arg0 + 0x93C);

    vec3_dir_to(centre, &pos, &dir);
    pushAngle = vec3_heading_deg(&dir) - 180.0f;
    func_15048758(&pushAngle);
    vec3_dir_to(&target, &pos, &toTarget);

    /* onto the circle */
    vec3_scale(&dir, C108_F32(0x938), &dir);
    pos.unk0 = C108_F32(0x93C) + dir.unk0;
    pos.unk4 = 0.0f;
    pos.unk8 = C108_F32(0x944) + dir.unk8;
    dx = target.unk0 - pos.unk0;
    dz = target.unk8 - pos.unk8;
    targetDist = sqrtf(dx * dx + dz * dz);

    vec3_diff(&pos, &target, &dir);
    heading = vec3_heading_deg(&dir);
    func_15048758(&heading);
    C108_F32(0x930) = heading;

    delta = math_angle_diff_deg(pushAngle, heading);
    if (fabsf(delta) < 35.0f) {
        vec_rotate_xz_about_point((u8 *)&pos, (u8 *)centre, (delta <= 0.0f) ? 5.0f : -5.0f, (u8 *)&pos);
    }
    D_80089950 = targetDist;
    pos.unk4 = C108_F32(0x2FC);
    *camPos = pos;
    arg0[0x948] = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/camera_cylinder_push.s")
#endif

/* was func_1512C9EC */
s32 camera_always_true(s32 arg0) {
    return 1;
}
