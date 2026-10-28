#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void math_spring_approach(f32 *, f32, f32 *, f32, f32, f32);
extern f32 g_camera_orbit_height; /* was D_800DC434 */
#ifdef PORT
f32 free_camera_wanted_height(u8 *cam, f32 h); /* P347 game_eu_1501C0.c */
s32 free_camera_turning(u8 *cam);
#endif

/* P43: camera eye height. dy = eye.y (+0x2FC) - base (+0x354) eases (math_spring_approach) towards the target height h:
 * +0x348 (95.0 with flag 0x10 of +0x5F0 and of *+0x36C), x1.5 with flag 0x400, cut below a ceiling of the followed
 * object (+0x3D0: +0x17C - 40, then the fast rate 5 / 9 is used), clamped to [+0x6F0, +0x6F4] when both are set,
 * g_camera_orbit_height when +0x7F4; 0 with flag 0x40 outside mode 0x100 or with mode bit 0x01000000. +0x23C: dy = h at once
 * (+0x25C = 0). No update (early return) when the object is more than 600 above +0x180 and idle (the 0x400 / 0xAD /
 * 0x102 / +0x3D4 / 0x137 / 0x84 == 0x194 / 0x80 tests all clear). Then eye.y = base + dy, +0x344 = eye.y - base,
 * and with object +0xAD == 1 and +0x73C, eye.y >= +0x360 + 5 (unless +0x360 == -10000).
 * sp44 (ceiling) is stale stack in the asm when the ceiling test is skipped; C starts it at 0. */
/* was func_1512E6B0 */
void camera_update_eye_height(u8 *arg0) {
    f32 dy;       /* sp48 */
    s32 ceiling;  /* sp44 */
    f32 h;
    f32 lo, hi;
    f32 top;
    f32 eye;
    s32 flags;
    s32 crouch;
    s32 mode;
    s32 fast;
    u8 *t;
    u8 *t2;

    ceiling = 0;
    if (g_cutscene_restart_transition != 0) {
        return;
    }
    if (!((*(s32 *)(arg0 + 0x2C) & 0x100) || arg0[0x92C] == 0 || (*(u16 *)(arg0 + 0x920) & 8))) {
        return;
    }
    dy = *(f32 *)(arg0 + 0x2FC) - *(f32 *)(arg0 + 0x354);
    flags = *(s32 *)(arg0 + 0x5F0);
    crouch = flags & 0x400;
    if ((flags & 0x10) && (**(u16 **)(arg0 + 0x36C) & 0x10)) {
        h = 95.0f;
    } else {
        h = *(f32 *)(arg0 + 0x348);
    }
    if (crouch) {
        h *= 1.5f;
    }
#ifdef PORT
    h = free_camera_wanted_height(arg0, h);   /* P347 option "Free camera": the pitched eye's height; unchanged when off */
#endif
    if (!(*(s32 *)(arg0 + 0x84) & 0x10)) {
        t = *(u8 **)(arg0 + 0x3D0);
        if (*(f32 *)(t + 0x180) < *(f32 *)(t + 0x17C)) {
            top = *(f32 *)(t + 0x17C) - 40.0f;
            eye = *(f32 *)(arg0 + 0x354);
            if (top < eye + h && eye < top) {
                h = top - eye;
                ceiling = 1;
            } else {
                ceiling = 0;
            }
        }
    }
    lo = *(f32 *)(arg0 + 0x6F0);
    if (lo != 0.0f) {
        hi = *(f32 *)(arg0 + 0x6F4);
        if (hi != 0.0f) {
            if (h < lo) {
                h = lo;
            } else if (hi < h) {
                h = hi;
            }
        }
    }
    if (*(u16 *)(arg0 + 0x7F4) != 0) {
        h = g_camera_orbit_height;
    }
    if (arg0[0x23C] != 0) {
        *(f32 *)(arg0 + 0x25C) = 0.0f;
        dy = h;
    } else {
        mode = *(s32 *)(arg0 + 0x2C);
        if ((flags & 0x40) && mode != 0x100) {
            h = 0.0f;
        } else if (mode & 0x01000000) {
            h = 0.0f;
        } else {
            t = *(u8 **)(arg0 + 0x3D0);
            if (*(f32 *)(t + 0x18) - *(f32 *)(t + 0x180) > 600.0f && crouch == 0 && t[0xAD] == 0 && t[0x102] == 0) {
                t2 = *(u8 **)(arg0 + 0x3D4);
                if (*(s32 *)(t2 + 0x9C) == 0 && t2[0x95] == 0 && t[0x137] == 0 && *(u16 *)(t + 0x84) != 0x194
                    && !(flags & 0x80)) {
                    return;
                }
            }
        }
        fast = mode & 0x100;
#ifdef PORT
        if (free_camera_turning(arg0)) {
            fast = 1;   /* P347: follow the player's pitch with the fast rates */
        }
#endif
        if (fast != 0 || ceiling != 0) {
            math_spring_approach(&dy, h, (f32 *)(arg0 + 0x25C), 5.0f, 9.0f, *(f32 *)(arg0 + 0x7B4));
        } else {
            math_spring_approach(&dy, h, (f32 *)(arg0 + 0x25C), *(f32 *)(arg0 + 0x3B4), *(f32 *)(arg0 + 0x3B8),
                          *(f32 *)(arg0 + 0x7B4));
        }
    }
    eye = *(f32 *)(arg0 + 0x354);
    *(f32 *)(arg0 + 0x2FC) = eye + dy;
    top = *(f32 *)(arg0 + 0x2FC);
    *(f32 *)(arg0 + 0x344) = top - eye;
    if ((*(u8 **)(arg0 + 0x3D0))[0xAD] == 1 && *(s16 *)(arg0 + 0x73C) != 0) {
        lo = *(f32 *)(arg0 + 0x360);
        if (lo != -10000.0f && top < lo + 5.0f) {
            *(f32 *)(arg0 + 0x2FC) = lo + 5.0f;
            *(f32 *)(arg0 + 0x344) = 5.0f;
        }
    }
}
