#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B2C20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3668.s")

#ifdef NON_MATCHING
s32 func_150B3B8C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t1;
    s32 temp_t7;
    s32 temp_t9;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x48));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) + arg4);
    if ((*(f32 *)((u8 *)arg0 + 0x170)) < temp_f0) {
        temp_t7 = (*(s32 *)((u8 *)arg0 + 0x60)) & ~7;
        temp_t9 = temp_t7 & ~8;
        temp_t1 = temp_t9 & ~0x40;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t7;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t9;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t1;
        (*(s32 *)((u8 *)arg0 + 0x60)) = (s32) (temp_t1 & ~0x20);
        (*(f32 *)((u8 *)arg0 + 0x44)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x48)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x4C)) = 0.0f;
        if ((*(s16 *)((u8 *)arg0 + 0x64)) >= 0x21) {
            (*(s16 *)((u8 *)arg0 + 0x64)) = 0x20;
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (-temp_f0 * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x4C)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x50)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x54)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x58)) * temp_f2);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3B8C.s")
#endif
s32 func_150B3C6C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 16;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = var_v1;
    }
    return 1;
}

#ifdef NON_MATCHING
struct210 *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD);
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern s16 D_80088AA0[3];   /* splash colours (15, 16, 17) */

/* trail_hit_splash: trail hit handler (D_8008A7D0 [5]) of particle `obj` hitting the ground at height `y`: the trail
 * record (obj +0x98) goes to state 4 (shrink); a splash sprite (func_1513C73C kind 0x11, life 150, a random colour
 * of D_80088AA0, size 50..100, the record's alpha bytes +0x1A / +0x1B) at the trail's current point (obj +0x94,
 * 20-byte points, index +0x2D) and a falling child trail (func_15148310: 3/4 of the record's +0 width, +4, random
 * length 15..30, +0xC / +0x10, colour bytes +0x19..+0x1B, life 60, the obj's +0x25) are spawned. Returns 1. */
s32 func_150B3CA8(u8 *obj, s32 arg1, s32 arg2, s32 arg3, f32 y, s32 arg5) {
    u8 *pts = *(u8 **)(obj + 0x94);
    u8 *rec = *(u8 **)(obj + 0x98);
    s16 colours[3];
    f32 size;
    s32 r1;
    s32 r2;
    s32 r3;
    struct {
        s32 kind;       /* 0x00 */
        s16 life;       /* 0x04 */
        u8 colour;      /* 0x06 */
        s32 u8_;        /* 0x08 */
        s32 uC;         /* 0x0C */
        u8 alpha0;      /* 0x10 */
        u8 alpha1;      /* 0x11 */
        u8 u12;
        u8 u13;
        u8 u14;
        u8 u15;         /* 0x15 = 0xFF */
        s32 flags;      /* 0x18 */
    } splash;
    struct {
        s32 w[7];       /* 0x00 */
        u8 b1C;
        u8 b1D;
    } style;
    struct {
        f32 width;      /* 0x00 */
        f32 v4;
        f32 length;
        f32 vC;
        f32 v10;
        f32 v14;
        u8 b18;
        u8 col[3];      /* 0x19..0x1B */
    } shape;
    struct {
        f32 x;          /* 0x00 */
        f32 y;
        f32 z;
        s16 life;       /* 0x0C */
        s16 sE;
        s32 s10;
        u8 b14;
        u8 b15;
    } at;

    colours[0] = D_80088AA0[0];
    colours[1] = D_80088AA0[1];
    colours[2] = D_80088AA0[2];
    rec[0x20] = 4;
    size = func_150ADA68() * 50.0f + 50.0f;
    splash.colour = colours[(u32)func_150ADA20() % 3];
    splash.u8_ = 0;
    splash.uC = 0;
    splash.kind = 0x11;
    splash.life = 150;
    splash.alpha0 = rec[0x1B];
    splash.u12 = 0;
    splash.u13 = 0;
    splash.u14 = 0;
    splash.u15 = 0xFF;
    splash.flags = 0x30002;
    splash.alpha1 = rec[0x1A];
    r1 = func_150ADA20();
    r2 = func_150ADA20();
    r3 = func_150ADA20();
    func_1513C73C((s32)&splash, 1, 0, arg5, *(f32 *)(pts + (s8)obj[0x2D] * 20), y,
                  *(f32 *)(pts + (s8)obj[0x2D] * 20 + 8), size, size, r1 & 0xFF, (r3 & 1) + (r2 & 1), 0, obj[0xC],
                  obj[1]);

    style.w[0] = 0;
    style.w[1] = 1;
    style.w[2] = 0x160600;
    style.w[3] = 3;
    style.w[4] = 0x10;
    style.w[5] = 0x80;
    style.w[6] = 0x20;
    style.b1C = 0;
    style.b1D = 9;
    at.s10 = 1;
    at.sE = 1;
    shape.col[0] = rec[0x19];
    shape.b18 = 8;
    shape.col[1] = rec[0x1A];
    shape.col[2] = rec[0x1B];
    at.y = y;
    at.x = *(f32 *)(pts + (s8)obj[0x2D] * 20);
    at.z = *(f32 *)(pts + (s8)obj[0x2D] * 20 + 8);
    at.life = 60;
    at.b15 = obj[0x25];
    shape.width = *(f32 *)(rec + 0x0) * 0.75f;
    shape.v10 = *(f32 *)(rec + 0x10);
    shape.v4 = *(f32 *)(rec + 0x4);
    shape.length = func_150ADA68() * 15.0f + 15.0f;
    shape.vC = *(f32 *)(rec + 0xC);
    func_15148310((u8 *)&at, (s32)&shape, 0, 1, 7, 0, 0, 0, 0, 0, 0, (u8 *)&style, 0, obj[0xC], obj[1]);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/func_150B3CA8.s")
#endif