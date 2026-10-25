#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_150E2030(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, struct127 *, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);


#ifdef NON_MATCHING
float sqrtf(float);
f32 func_150484A0(f32, f32);
extern u8 *D_8008CDEC[];

// beam_effect_spawn: allocates a line / beam effect object (func_15167A68(0xB, 0, 0x100, 1, 0xFF, 1)) from
// (x0, y0, z0) to (x1, y1, z1): start +0x94, end +0xB0, yaw +0xA4 / pitch +0xA0 of the direction (func_150484A0),
// widths +0xA8 / +0xAC / +0xBC / +0xC0, texture D_8008CDEC[tex] (+0xD8) with two 4-vertex quads at +0x10 whose
// s / t span the texture size. mode (+0xD0) 0 = plain (+0xD6 = 1, +0xE0 = -1); otherwise it follows `target`
// (+0xDC, freed again with func_1516979C when NULL) with the extra parameters +0xD2 .. +0xF8. Returns the asm's
// leftover v0: 0 when the allocation fails, else obj + 0x80 (the quad loop pointer; no caller uses it); 0 on the
// func_1516979C path (the asm passes on that void call's v0).
s32 func_150E2030(s32 arg0, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 w0, f32 w1, f32 w2, f32 w3,
                  s32 kind, s32 tex, s32 mode, s32 d2, s32 d4, struct127 *target, s32 da, s32 e2, s32 e0, s32 fc,
                  s32 fe, f32 e4, f32 e8, f32 ec, f32 f0, f32 f4, f32 f8) {
    u8 *obj;
    s16 *vt;
    f32 dx, dz;
    s32 i, s, t;
    u8 *img;

    obj = func_15167A68(0xB, 0, 0x100, 1, 0xFF, 1);
    if (obj == NULL) {
        return 0;
    }
    *(s16 *) (obj + 0x90) = kind;
    *(f32 *) (obj + 0x94) = x0;
    *(f32 *) (obj + 0x98) = y0;
    *(f32 *) (obj + 0x9C) = z0;
    dx = x1 - x0;
    dz = z1 - z0;
    *(f32 *) (obj + 0xA4) = func_150484A0(-dx, -dz);
    *(f32 *) (obj + 0xA0) = func_150484A0(y1 - y0, sqrtf(dx * dx + dz * dz));
    *(f32 *) (obj + 0xC4) = 0.0f;
    *(f32 *) (obj + 0xC8) = 0.0f;
    *(f32 *) (obj + 0xCC) = 0.0f;
    *(f32 *) (obj + 0xB0) = x1;
    *(f32 *) (obj + 0xB4) = y1;
    *(f32 *) (obj + 0xB8) = z1;
    *(f32 *) (obj + 0xAC) = w1;
    *(f32 *) (obj + 0xA8) = w0;
    *(f32 *) (obj + 0xBC) = w2;
    *(f32 *) (obj + 0xC0) = w3;
    obj[0xE3] = 0;
    obj[0xFD] = 0;
    obj[0xFC] = fc;
    *(struct127 **) (obj + 0xDC) = target;
    obj[0xFE] = fe;
    *(u16 *) (obj + 0xD8) = tex;
    *(s8 *) (obj + 0xD0) = mode;
    if (*(s8 *) (obj + 0xD0) == 0) {
        *(s16 *) (obj + 0xD6) = 1;
        *(s16 *) (obj + 0xE0) = -1;
    } else if (target == NULL) {
        func_1516979C((struct102 *) obj);
        return 0;
    } else {
        *(s16 *) (obj + 0xD2) = d2;
        *(s16 *) (obj + 0xD6) = -(s16) d4;
        *(s16 *) (obj + 0xD4) = d4;
        obj[0xDA] = da;
        obj[0xE2] = e2;
        *(s16 *) (obj + 0xE0) = e0;
        *(f32 *) (obj + 0xE4) = e4;
        *(f32 *) (obj + 0xE8) = e8;
        *(f32 *) (obj + 0xEC) = ec;
        *(f32 *) (obj + 0xF0) = f0;
        *(f32 *) (obj + 0xF4) = f4;
        *(f32 *) (obj + 0xF8) = f8;
    }
    /* vertices 1..8 (16 bytes each from obj): flag 0, s / t = 0x2000 or 0x2000 + (size - 1) * 32 */
    vt = (s16 *) obj;
    for (i = 0; i < 2; i++) {
        img = D_8008CDEC[*(s16 *) (obj + 0xD8)];
        s = (*(u16 *) (img + 6) - 1) * 32 + 0x2000;
        t = (*(u16 *) (img + 8) - 1) * 32 + 0x2000;
        vt += 32; /* 4 vertices */
        vt[-4] = 0x2000;
        vt[-3] = 0x2000;
        vt[-5] = 0;
        vt[-20] = s;
        vt[-19] = 0x2000;
        vt[-21] = 0;
        vt[4] = 0x2000;
        vt[5] = t;
        vt[3] = 0;
        vt[-12] = s;
        vt[-11] = t;
        vt[-13] = 0;
    }
    obj[0xDB] = 0;
    return (s32) (obj + 0x80);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2030.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2294.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2E5C.s")

s32 func_150E3324(s32 arg0, s32 arg1) {
    return arg0;
}

void func_150E3334(s32 arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, s16 argA, s16 argB, u16 argC, u8 argD) {
    func_150E2030(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 400.0f, (s32) argC, 0x27, 1, (s32) argA, (s32) argB, (struct127 *)arg0, (s32) arg1, (s32) arg2, arg3, 0, (s32) argD, arg4, arg5, arg6, arg7, arg8, arg9);
}

void func_150E2EA4(struct127 *arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, s16 argA, s16 argB, u16 argC, f32 argD, f32 argE, u8 argF, f32 arg10) {
    func_150E2030(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, arg10, 0.0f, argD, argE, (s32) argC, 0x27, 1, (s32) argA, (s32) argB, arg0, (s32) arg1, (s32) arg2, arg3, 0, (s32) argF, arg4, arg5, arg6, arg7, arg8, arg9);
}

void func_150E3510(s32 arg0, s32 arg1, s16 arg2) {
    func_150E3324(arg0, arg2);
}

void func_150E3540(u8 *arg0, s32 *arg1, u8 arg2) {
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(arg0 + 0xDC)) {
            *(s32 *)(arg0 + 0xDC) = arg1[1];
            arg0[0xDA] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(arg0 + 0xDC)) {
            *(s32 *)(arg0 + 0xDC) = arg1[0];
            arg0[0xDA] = ((u8 *)arg1)[8];
        }
    }
}
