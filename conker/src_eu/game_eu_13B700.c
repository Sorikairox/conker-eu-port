#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
u8 *func_1510DEF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp28;
    s32 sp20;
    s32 temp_t0;
    s32 var_a0;
    s32 var_a0_2;
    u8 *temp_v0;
    u8 *var_v1;
    u8 *var_v1_2;

    temp_t0 = arg3 & 1;
    sp28 = 0x128;
    if (temp_t0 != 0) {
        sp28 = 0x13A;
    }
    sp20 = temp_t0;
    temp_v0 = func_15167A68(0x4B, 0, sp28, 1, 0xFFU, 1U);
    if (temp_v0 != NULL) {
        var_a0 = 0;
        var_v1 = temp_v0;
        do {
            var_a0 += 1;
            var_v1 += 0x40;
            (*(s16 *)((u8 *)var_v1 + 0x56)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x58)) = 0x800;
            (*(s16 *)((u8 *)var_v1 + 0x5A)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x66)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x68)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x6A)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x76)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x78)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x7A)) = 0x800;
            (*(s16 *)((u8 *)var_v1 + 0x86)) = 0;
            (*(s16 *)((u8 *)var_v1 + 0x88)) = 0x800;
            (*(s16 *)((u8 *)var_v1 + 0x8A)) = 0x800;
        } while (var_a0 < 2);
        var_a0_2 = 1;
        (*(s8 *)((u8 *)temp_v0 + 0x120)) = (s8) arg0;
        var_v1_2 = temp_v0 + 2;
        (*(s32 *)((u8 *)temp_v0 + 0x110)) = arg1;
        (*(s8 *)((u8 *)temp_v0 + 0x121)) = (s8) arg2;
        (*(s8 *)((u8 *)temp_v0 + 0x124)) = (s8) arg4;
        if (temp_t0 != 0) {
            (*(s16 *)((u8 *)temp_v0 + 0x128)) = 0x7FFF;
            do {
                var_a0_2 += 4;
                (*(s16 *)((u8 *)var_v1_2 + 0x12A)) = 0x7FFF;
                (*(s16 *)((u8 *)var_v1_2 + 0x12C)) = 0x7FFF;
                (*(s16 *)((u8 *)var_v1_2 + 0x12E)) = 0x7FFF;
                var_v1_2 += 8;
                (*(s16 *)((u8 *)var_v1_2 + 0x120)) = 0x7FFF;
            } while (var_a0_2 != 9);
        }
    }
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510DEF0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E6A0.s")

#ifdef NON_MATCHING
/*
 * P65: floor slope of a triangle, given as 3 vertex pointers (tris) or, when verts != NULL, as 3
 * packed s16 x/y/z vertices (verts, stride 6). Tries the corners in turn: P1 = v[i], edges e1 = v[i+1] - P1 and
 * e2 = v[i+2] - P1 (indices mod 3), i = 0..2, then the same three with e1 / e2 swapped, until
 * e1.x * e2.z != e2.x * e1.z and e2.x != 0. Then
 *   *outB = (e2.x * e1.y - e1.x * e2.y) / (e2.x * e1.z - e1.x * e2.z),  *outA = (e2.y - *outB * e2.z) / e2.x
 * and returns 1 (y = *outA * x + *outB * z on the plane, up to the offset). No triangle, or the 6th attempt (even a
 * good one, as the asm does): both 0, returns 0.
 */
s32 func_1510E908(s16 **tris, s16 *verts, f32 *outA, f32 *outB) {
    s32 attempt = 0;
    s32 state;
    s32 swap;
    s32 i0, i1, i2;
    s16 *p0, *p1, *p2;
    f32 e1x, e1y, e1z, e2x, e2y, e2z, t;
    f32 p, q;

    if (tris == NULL && verts == NULL) {
        *outB = 0.0f;
        *outA = 0.0f;
        return 0;
    }
    do {
        state = 1;
        swap = (attempt >= 3);
        i0 = swap ? attempt - 3 : attempt;
        i1 = (i0 == 2) ? 0 : i0 + 1;
        attempt++;
        i2 = (i1 == 2) ? 0 : i1 + 1;
        if (verts != NULL) {
            p0 = verts + i1 * 3;
            p1 = verts + i0 * 3;
            p2 = verts + i2 * 3;
        } else {
            p0 = tris[i1];
            p1 = tris[i0];
            p2 = tris[i2];
        }
        e1x = p0[0] - p1[0];
        e1y = p0[1] - p1[1];
        e1z = p0[2] - p1[2];
        e2x = p2[0] - p1[0];
        e2y = p2[1] - p1[1];
        e2z = p2[2] - p1[2];
        if (swap) {
            t = e1x; e1x = e2x; e2x = t;
            t = e1y; e1y = e2y; e2y = t;
            t = e1z; e1z = e2z; e2z = t;
        }
        p = e1x * e2z;
        q = e2x * e1z;
        if (p == q) {
            state = 0;
        }
        if (e2x == 0.0f) {
            state = 0;
        }
        if (attempt == 6) {
            state = 2;
        }
    } while (state == 0);

    if (state == 2) {
        *outA = 0.0f;
        *outB = 0.0f;
        return 0;
    }
    *outB = (e2x * e1y - e1x * e2y) / (q - p);
    *outA = (e2y - *outB * e2z) / e2x;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13B700/func_1510E908.s")
#endif

Gfx *func_1510EBB4(Gfx *gdl, s32 arg1, s32 arg2) {
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return gdl;
}
