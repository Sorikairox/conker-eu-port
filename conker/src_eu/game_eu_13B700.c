#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_1510DEF0 */
u8 *blob_shadow_create(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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
    temp_v0 = node_alloc(0x4B, 0, sp28, 1, 0xFFU, 1U);
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
/* P125 */
f32 math_cos_u8(u8);
f32 math_sin_u8(u8 arg0);
s32 floor_tri_height(f32 x, f32 z, s32 tri, u8 *packed, f32 *out);
s32 floor_triangle_slope(s16 **tris, s16 *verts, f32 *outA, f32 *outB);
void collision_find_floor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);

/* blob_shadow_update: per frame, the blob shadow record rec (blob_shadow_create) of its owner *(rec + 0x110):
 * rec[0x120] 0 = an object (f32 position +0x14..+0x1C, floor height +0x180 (id 0x25 uses it as its height), floor
 * triangles +0x188 / +0x18C, size u16 +0x160 * f32 +0x14C, facing u16 +0x7A), 1 = a node with s16 position +0x10..
 * +0x14 (skipped when its byte +0x6E is 1; its floor comes from floor_tri_height on the packed floor *(+0x94) + 0x128,
 * else collision_find_floor fills it; size (byte +0x4D * 4) * f32 +0x2C). Stores the floor point at +0x114..+0x11C; above
 * the floor, gets the floor slope (floor_triangle_slope), scales the shadow by size / clamp(200 + height, 800), sets the
 * alpha +0x122 (fade in by 5 per frame step when rec[0x124] & 1, else 32000 / distance up to 0xA0) and writes the
 * quad corners A, B, -A, -B (100 units along / across the facing, tilted onto the slope, normalised and scaled) into
 * the 4 vertices +0x90 of this frame's buffer (D_800BE9C0, 0x40 each); rec[0x123] = 1 when drawn.
 * Other rec[0x120] values are never created (the asm would use stale stack values); they do nothing here. */
/* was func_1510E004 */
void blob_shadow_update(u8 *rec) {
    u8 *o;
    s16 **tris;
    s16 *verts;
    u8 *packed;
    f32 a[3];
    f32 b[3];
    f32 x, y, z, floor_y;
    f32 size, dist, scale;
    f32 slope_x, slope_z;
    f32 s, c;
    f32 len_a, len_b;
    s32 alpha;
    u8 angle;
    s16 *vtx;
    s32 i;

    rec[0x123] = 0;
    if (rec[0x120] == 0) {
        o = *(u8 **) (rec + 0x110);
        x = *(f32 *) (o + 0x14);
        z = *(f32 *) (o + 0x1C);
        y = *(f32 *) (o + 0x18);
        floor_y = *(f32 *) (o + 0x180);
        if (o[4] == 0x25) {
            y = floor_y;
        }
        verts = (s16 *) (o + 0x18C);
        tris = *(s16 ***) (o + 0x188);
        size = *(u16 *) (o + 0x160) * *(f32 *) (o + 0x14C);
        angle = (*(u16 *) (o + 0x7A) >> 8) + 0x20;
    } else if (rec[0x120] == 1) {
        o = *(u8 **) (rec + 0x110);
        if (o[0x6E] == 1) {
            return;
        }
        packed = *(u8 **) (o + 0x94) + 0x128;
        if (floor_tri_height(*(s16 *) (o + 0x10), *(s16 *) (o + 0x14), 0, packed, &floor_y) == 0) {
            y = *(s16 *) (o + 0x12);
            collision_find_floor(0, (s32) packed, (s32) &floor_y, 0, 0, 0, *(s16 *) (o + 0x10), y, *(s16 *) (o + 0x14), y,
                          o[0x71] + 1, 0, -10000.0f, y);
        }
        tris = NULL;
        verts = (s16 *) packed;
        x = *(s16 *) (o + 0x10);
        y = *(s16 *) (o + 0x12);
        z = *(s16 *) (o + 0x14);
        angle = 0;
        size = (f32) (o[0x4D] * 4) * *(f32 *) (o + 0x2C);
    } else {
        return;
    }
    *(f32 *) (rec + 0x114) = x;
    *(f32 *) (rec + 0x118) = z;
    *(f32 *) (rec + 0x11C) = floor_y;
    if (y < floor_y) {
        return;
    }
    if (floor_triangle_slope(tris, verts, &slope_x, &slope_z) == 0) {
        return;
    }
    if (size == 0.0f) {
        size = 1.0f;
    }
    dist = 200.0f + (y - floor_y);
    if (dist == 0.0f) {
        dist = 0.0001f;
    }
    if (dist > 800.0f) {
        dist = 800.0f;
    }
    scale = size / dist;
    if (rec[0x124] & 1) {
        alpha = rec[0x122];
        if (alpha != 0xFF) {
            alpha += D_800BE9E4 * 5;
            if (alpha >= 0x100) {
                alpha = 0xFF;
            }
        }
    } else {
        alpha = (s32) (32000.0f / dist);
        if (alpha >= 0xA1) {
            alpha = 0xA0;
        }
    }
    rec[0x122] = alpha;

    /* A = (0, -100) and B = (-100, 0) in x / z, turned by the facing */
    a[0] = 0.0f;
    a[2] = -100.0f;
    if (angle != 0) {
        s = math_sin_u8(angle);
        c = math_cos_u8(angle);
        a[0] = 0.0f * c + -100.0f * s;
        a[2] = -100.0f * c - 0.0f * s;
    }
    a[1] = a[2] * slope_z + slope_x * a[0];
    b[0] = -100.0f;
    b[2] = 0.0f;
    if (angle != 0) {
        { /* P317: volatile zero: IDO folds `0.0f + x` (the asm adds, -0.0 -> +0.0; P310) */
            volatile f32 p317z = 0.0f;
            b[0] = -100.0f * c + p317z;
        }
        b[2] = 0.0f - -100.0f * s;
    }
    b[1] = b[2] * slope_z + slope_x * b[0];

    len_a = (a[0] * a[0] + a[1] * a[1]) + a[2] * a[2];
    if (1e8f < len_a) {
        len_a = 1e8f;
    }
    if (len_a < 10000.0f) {
        len_a = 10000.0f;
    }
    len_a = sqrtf(len_a);
    len_b = (b[0] * b[0] + b[1] * b[1]) + b[2] * b[2];
    if (1e8f < len_b) {
        len_b = 1e8f;
    }
    if (len_b < 10000.0f) {
        len_b = 10000.0f;
    }
    len_b = sqrtf(len_b);

    for (i = 0; i < 3; i++) {
        a[i] = a[i] * 100.0f * scale / len_a;
        b[i] = b[i] * 100.0f * scale / len_b;
        vtx = (s16 *) (rec + D_800BE9C0 * 0x40 + 0x90);
        vtx[i] = (s32) a[i];
        vtx[8 + i] = (s32) b[i];
        vtx[16 + i] = (s32) -a[i];
        vtx[24 + i] = (s32) -b[i];
    }
    rec[0x123] = 1;
}

/* P130 */
extern s32 D_800DD5E4;     /* texture of the last drawn blob shadow */
extern s32 D_80091B20[];   /* blob shadow texture ids */
void mtx_translate_fixed(s16 *mtx, f32 x, f32 y, f32 z);
s32 texture_cache_lookup(s32, s32 *, s32, s32);
s32 obj_get_player_alpha(struct127 *, s32);

// blob_shadow_draw: emits the display list of a blob shadow record rec (set up by blob_shadow_update this frame, which
// sets rec[0x123] when it is visible): its translation Mtx (this frame's +0x10 slot) to the floor point (+0x114 x,
// +0x11C floor y, +0x118 z), the texture D_80091B20[rec[0x121]] when it changed (D_800DD5E4), geometry mode off,
// the prim alpha rec[0x122] * owner alpha / 256 when it changed (D_800DD5F6) - owner alpha from obj_get_player_alpha for
// an object owner (rec[0x120] 0), else owner u8 +0x8A * u8 +0x8B[idx] / 256 - and the 4 vertices (+0x90 slot) as
// two triangles. Other owner kinds never get rec[0x123] (blob_shadow_update returns first). Returns the DL end.
/* was func_1510E6A0 */
Gfx *blob_shadow_draw(Gfx *g, u8 *rec, s16 idx) {
    s16 *mtx;
    u8 *owner;
    s32 tex;
    s32 alpha;

    if (rec[0x123] == 0) {
        return g;
    }
    mtx = (s16 *) (rec + D_800BE9C0 * 0x40 + 0x10);
    mtx_translate_fixed(mtx, *(f32 *) (rec + 0x114), *(f32 *) (rec + 0x11C), *(f32 *) (rec + 0x118));
    g->words.w0 = 0xDA380003;                     /* gSPMatrix modelview, load, push */
    g->words.w1 = (s32) mtx;
    g++;
    if (rec[0x121] != D_800DD5E4) {
        D_800DD5E4 = rec[0x121];
        tex = texture_cache_lookup(D_80091B20[rec[0x121]], NULL, 0x3E, 0);
        g->words.w0 = 0xE7000000;                 /* gDPPipeSync */
        g->words.w1 = 0;
        g++;
        g->words.w0 = 0xFD900000;                 /* gDPSetTextureImage */
        g->words.w1 = tex;
        g++;
        g->words.w0 = 0xF3000000;                 /* gDPLoadBlock */
        g->words.w1 = 0x077FF000;
        g++;
    }
    g->words.w0 = 0xE7000000;
    g->words.w1 = 0;
    g++;
    g->words.w0 = 0xD9FFF9FF;                     /* gSPClearGeometryMode */
    g->words.w1 = 0;
    g++;
    owner = *(u8 **) (rec + 0x110);
    if (rec[0x120] == 0) {
        alpha = obj_get_player_alpha((struct127 *) owner, idx);
    } else if (rec[0x120] == 1) {
        alpha = (owner[0x8B + idx] * owner[0x8A] + 0xFF) >> 8;
    } else {
        alpha = 0; /* not reached (the asm reads a stale stack word) */
    }
    alpha = (rec[0x122] * alpha + 0xFF) >> 8;
    if (alpha != D_800DD5F6) {
        D_800DD5F6 = alpha;
        g->words.w0 = 0xE7000000;
        g->words.w1 = 0;
        g++;
        g->words.w0 = 0xFA000100;                 /* gDPSetPrimColor: alpha */
        g->words.w1 = alpha & 0xFF;
        g++;
    }
    g->words.w0 = 0x01004008;                     /* gSPVertex: 4 vertices */
    g->words.w1 = (s32) (rec + D_800BE9C0 * 0x40 + 0x90);
    g++;
    g->words.w0 = 0x05000204;                     /* gSP1Triangle 0 1 2 */
    g->words.w1 = 0;
    g++;
    g->words.w0 = 0x05000406;                     /* gSP1Triangle 0 2 3 */
    g->words.w1 = 0;
    g++;
    g->words.w0 = 0xE7000000;
    g->words.w1 = 0;
    g++;
    return g;
}

/*
 * P65: floor slope of a triangle, given as 3 vertex pointers (tris) or, when verts != NULL, as 3
 * packed s16 x/y/z vertices (verts, stride 6). Tries the corners in turn: P1 = v[i], edges e1 = v[i+1] - P1 and
 * e2 = v[i+2] - P1 (indices mod 3), i = 0..2, then the same three with e1 / e2 swapped, until
 * e1.x * e2.z != e2.x * e1.z and e2.x != 0. Then
 *   *outB = (e2.x * e1.y - e1.x * e2.y) / (e2.x * e1.z - e1.x * e2.z),  *outA = (e2.y - *outB * e2.z) / e2.x
 * and returns 1 (y = *outA * x + *outB * z on the plane, up to the offset). No triangle, or the 6th attempt (even a
 * good one, as the asm does): both 0, returns 0.
 */
/* was func_1510E908 */
s32 floor_triangle_slope(s16 **tris, s16 *verts, f32 *outA, f32 *outB) {
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

/* was func_1510EBB4 */
Gfx *gfx_load_identity_modelview(Gfx *gdl, s32 arg1, s32 arg2) {
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return gdl;
}
