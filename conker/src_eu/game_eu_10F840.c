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

#ifdef NON_MATCHING
extern s32 D_800D30BC;
Gfx *func_15095380(Gfx *gfx, u8 *header, s32 tmem, void *spr, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);

// beam_effect_draw: draw handler of the beam objects of func_150E2030 (Gfx *(Gfx *, u8 *obj, s16 viewer)). With a
// texture (+0xD6 > 0) the beam from +0x94 along the direction +0xC4 times the length +0xC0 is drawn as one quad
// facing character `viewer` (D_800DBFF0 entry, position +0x2F8): at each end the offset cross(end - eye, dir) scaled
// to the half width +0xBC gives the two corners end +- offset (far end first). The corners go to this frame's 4
// vertices (obj + 0x10 + D_800BE9C0 * 0x40, s16 x / y / z), then texture D_8008CDEC[+0xD8] is loaded
// (func_15095380; its sprite-parameter pointer is an unset local, as in the asm), the render mode is set
// (func_15142FBC) and gSPVertex + 2 triangles are emitted; +0xDB = 1. Returns gfx unchanged without setting +0xDB
// when an end lies on the eye line (zero offset). The asm also computes the squared eye distances of both ends and
// an unused first offset; neither is read.
Gfx *func_150E2E5C(Gfx *gfx, u8 *obj, s16 viewer) {
    f32 ends[2][3];
    f32 verts[4][3];
    u8 spr[0x10];
    u8 flag;
    f32 *eye;
    f32 *dir;
    f32 *p;
    f32 e[3];
    f32 n[3];
    f32 len;
    f32 s;
    s32 i;
    s32 j;
    u32 *cmd;

    if (*(s16 *) (obj + 0xD6) <= 0) {
        obj[0xDB] = 1;
        return gfx;
    }
    dir = (f32 *) (obj + 0xC4);
    /* far end first */
    ends[0][0] = *(f32 *) (obj + 0x94) + *(f32 *) (obj + 0xC0) * dir[0];
    ends[0][1] = *(f32 *) (obj + 0x98) + *(f32 *) (obj + 0xC0) * dir[1];
    ends[0][2] = *(f32 *) (obj + 0x9C) + *(f32 *) (obj + 0xC0) * dir[2];
    ends[1][0] = *(f32 *) (obj + 0x94);
    ends[1][1] = *(f32 *) (obj + 0x98);
    ends[1][2] = *(f32 *) (obj + 0x9C);
    eye = (f32 *) ((u8 *) D_800DBFF0 + viewer * 0x9A0 + 0x2F8);
    for (i = 0; i < 2; i++) {
        p = ends[i];
        e[0] = p[0] - eye[0];
        e[1] = p[1] - eye[1];
        e[2] = p[2] - eye[2];
        n[0] = e[1] * dir[2] - e[2] * dir[1];
        n[1] = e[2] * dir[0] - e[0] * dir[2];
        n[2] = e[0] * dir[1] - e[1] * dir[0];
        len = sqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
        if (len == 0.0f) {
            return gfx;
        }
        s = *(f32 *) (obj + 0xBC) / len;
        n[0] *= s;
        n[1] *= s;
        n[2] *= s;
        verts[i * 2][0] = n[0] + p[0];
        verts[i * 2][1] = n[1] + p[1];
        verts[i * 2][2] = n[2] + p[2];
        verts[i * 2 + 1][0] = p[0] - n[0];
        verts[i * 2 + 1][1] = p[1] - n[1];
        verts[i * 2 + 1][2] = p[2] - n[2];
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            *(s16 *) (obj + D_800BE9C0 * 0x40 + i * 0x10 + 0x10 + j * 2) = (s32) verts[i][j];
        }
    }
    gfx = func_15095380(gfx, D_8008CDEC[*(s16 *) (obj + 0xD8)], 0, spr, 0, 0, 0, 2, 3);
    flag = 0;
    gfx = func_15142FBC(gfx, D_800D30BC | 0x82CA0, 0x504A50, &flag);
    cmd = (u32 *) gfx;
    cmd[0] = 0x01004008; /* gSPVertex(this frame's 4 vertices) */
    cmd[1] = (u32) (obj + D_800BE9C0 * 0x40 + 0x10);
    cmd[2] = 0x05000206; /* triangle 0 1 3 */
    cmd[3] = 0;
    cmd[4] = 0x05000604; /* triangle 0 3 2 */
    cmd[5] = 0;
    obj[0xDB] = 1;
    return gfx + 3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10F840/func_150E2E5C.s")
#endif

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
