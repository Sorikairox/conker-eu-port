#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_150498A0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
extern s32 D_800D2DB4;
extern f32 D_80089890[][5]; /* camera lean presets: {k0, k1, k2, k3, base} per +0x134 index */

/* camera_lean_from_heading: computes the camera's two lean offsets from its heading +0x390 (degrees) and the
 * lean preset D_80089890[+0x134] (+0x134 is forced to 0 for this call when +0x2C & 0x40, then restored).
 * The second offset scales with the speed term s = (+0x3D0)->+0x3C capped at 30 (0 when +0x23C is set or k0 == k2).
 *  - With D_800D2DB4 set, or when mode +0x73C is 0 / 3 and (+0x3D4)->+0x120 is set, both offsets ease back to 0
 *    (+0x5E8 / +0x660 at 6 / 9, +0x3A8 / +0x65C at 1.5 / 2.5) and the function returns (+0x134 not restored).
 *  - Offset A (heading folded to -90..90 around the side): a = h * k0 / 90 - h * s * k2 / 2700 + base (0 when
 *    +0x2C & 0x100); goes to *outA, else is snapped into +0x3A8 (+0x65C = 0) when +0x23C, else eased (1.5 / 2.5).
 *  - Offset B (heading folded to -90..90 around the front): b = -h * k1 / 90 - h * s * k3 / 2700; goes to *outB,
 *    else snapped into +0x5E8 (+0x660 = 0) when +0x23C, else eased (6 / 9 when +0x2C & 0x100, else 1.5 / 2.5).
 * Called per frame by func_15122C5C / func_15128030 (NULL, NULL) and func_1512EE50 mode 2. */
void func_15128D50(struct108 *arg0, f32 *outB, f32 *outA) {
    u8 *p = (u8 *)arg0;
    s32 saved = *(s32 *)(p + 0x134);
    f32 *e;
    f32 k0;
    f32 speed;
    f32 h;
    f32 dir;
    f32 a;
    f32 b;
    s16 mode;

    if (*(s32 *)(p + 0x2C) & 0x40) {
        *(s32 *)(p + 0x134) = 0;
    }
    if (D_800D2DB4 != 0 || ((mode = *(s16 *)(p + 0x73C)) != 0 && mode != 3)
        || (*(u8 **)(p + 0x3D4))[0x120] != 0) {
        func_150498A0((f32 *)(p + 0x5E8), 0.0f, (f32 *)(p + 0x660), 6.0f, 9.0f, *(f32 *)(p + 0x7B4));
        func_150498A0((f32 *)(p + 0x3A8), 0.0f, (f32 *)(p + 0x65C), 1.5f, 2.5f, *(f32 *)(p + 0x7B4));
        return;
    }
    e = D_80089890[*(s32 *)(p + 0x134)];
    k0 = e[0];
    if (p[0x23C] != 0 || k0 == e[2]) {
        speed = 0.0f;
    } else {
        speed = *(f32 *)(*(u8 **)(p + 0x3D0) + 0x3C);
    }
    if (speed > 30.0f) {
        speed = 30.0f;
    }

    /* offset A: heading folded to the side */
    h = *(f32 *)(p + 0x390);
    if (*(s32 *)(p + 0x6C8) != 0 && (*(s32 *)(p + 0x6FC) == 0xA || *(s32 *)(p + 0x6FC) == 0xE)) {
        h = fabsf(h);
    }
    while (h > 180.0f) {
        h = 360.0f - h;
    }
    if (h < 90.0f) {
        h = -180.0f + h;
    }
    dir = (h < 0.0f) ? -1.0f : 1.0f;
    h -= 90.0f * dir;
    a = h * 0.011111111f * k0 - h * speed * 0.00037037037f * e[2] + e[4];
    if (*(s32 *)(p + 0x2C) & 0x100) {
        a = 0.0f;
    }
    if (outA != NULL) {
        *outA = a;
    } else if (p[0x23C] != 0) {
        *(f32 *)(p + 0x3A8) = a;
        *(f32 *)(p + 0x65C) = 0.0f;
    } else {
        func_150498A0((f32 *)(p + 0x3A8), a, (f32 *)(p + 0x65C), 1.5f, 2.5f, *(f32 *)(p + 0x7B4));
    }

    /* offset B: heading folded to the front */
    h = *(f32 *)(p + 0x390);
    while (h > 180.0f) {
        h -= 360.0f;
    }
    if (h > 90.0f) {
        h = 180.0f - h;
    } else if (h < -90.0f) {
        h = -180.0f - h;
    }
    b = -(h * 0.011111111f * e[1]) - h * speed * 0.00037037037f * e[3];
    if (outB != NULL) {
        *outB = b;
    } else if (p[0x23C] != 0) {
        *(f32 *)(p + 0x660) = 0.0f;
        *(f32 *)(p + 0x5E8) = b;
    } else if (*(s32 *)(p + 0x2C) & 0x100) {
        func_150498A0((f32 *)(p + 0x5E8), b, (f32 *)(p + 0x660), 6.0f, 9.0f, *(f32 *)(p + 0x7B4));
    } else {
        func_150498A0((f32 *)(p + 0x5E8), b, (f32 *)(p + 0x660), 1.5f, 2.5f, *(f32 *)(p + 0x7B4));
    }
    *(s32 *)(p + 0x134) = saved;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_156560/func_15128D50.s")
#endif
