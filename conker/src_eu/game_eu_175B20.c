#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 memcpy(u8 *, s32, s32);

/* was func_15148310 */
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE) {
    u8 *sp3C;
    u8 *sp38;
    u8 *temp_a0;
    u8 *temp_v0;

    (*(s32 *)((u8 *)arg0 + 0x10)) = 1;
    temp_v0 = fxrec_spawn(arg0, arg2 + 0x48, 0x14, 1, 0, 1, arg9, argA, argC, (u8) (s32) argD, argE);
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_a0 = (*(u8 **)((u8 *)temp_v0 + 0x98));
    sp3C = temp_v0;
    sp38 = temp_a0;
    memcpy(temp_a0, arg1, 0x20);
    (*(s8 *)((u8 *)temp_a0 + 0x20)) = (s8) arg3;
    (*(s8 *)((u8 *)temp_a0 + 0x21)) = (s8) arg4;
    (*(s8 *)((u8 *)temp_a0 + 0x22)) = (s8) arg5;
    (*(s8 *)((u8 *)temp_a0 + 0x23)) = (s8) arg6;
    (*(s8 *)((u8 *)temp_a0 + 0x24)) = (s8) arg7;
    (*(s8 *)((u8 *)temp_a0 + 0x25)) = (s8) arg8;
    (*(s32 *)((u8 *)temp_a0 + 0x28)) = (s32) (*(s32 *)((u8 *)argB + 0));
    (*(s32 *)((u8 *)temp_a0 + 0x2C)) = (s32) (*(s32 *)((u8 *)argB + 4));
    (*(s32 *)((u8 *)temp_a0 + 0x30)) = (s32) (*(s32 *)((u8 *)argB + 8));
    (*(s32 *)((u8 *)temp_a0 + 0x34)) = (s32) (*(s32 *)((u8 *)argB + 0xC));
    (*(s32 *)((u8 *)temp_a0 + 0x38)) = (s32) (*(s32 *)((u8 *)argB + 0x10));
    (*(s32 *)((u8 *)temp_a0 + 0x3C)) = (s32) (*(s32 *)((u8 *)argB + 0x14));
    (*(s32 *)((u8 *)temp_a0 + 0x40)) = (s32) (*(s32 *)((u8 *)argB + 0x18));
    (*(s32 *)((u8 *)temp_a0 + 0x44)) = (s32) (*(s32 *)((u8 *)argB + 0x1C));
    return sp3C;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/trail_spawn.s")
#endif
#ifdef NON_MATCHING
extern s32 (*D_8008A780[])(u8 *);
extern s32 (*D_8008A798[])(u8 *);
extern s32 (*D_8008A7CC[])(u8 *, s32, s32, s32, f32, s32); /* = D_8008A7D0 - 4: the hit handlers */

// trail_step: per-frame step of a trail particle (type table D_8008A5A0 entry 1).
/* obj +0x98 is the trail record (trail_spawn): +0x20 / +0x21 select the motion handlers (D_8008A780 / D_8008A798,
 * 0 = none), +0x22 the end handler (D_8008A7CC, the hit handler table D_8008A7D0 shifted by one); +0x18 flag 0x40 fades the alpha +0x1B in with the timer (obj +0x1C
 * times rate +0x1E, while the timer is below +0x1C). Stores the oldest point (index +0x2D of the +0x94 point list,
 * 0x14 bytes each) in obj +0x54, or 0 when the list is empty. Returns 0 when a handler ends the trail, else 1. */
/* was func_15148428 */
s32 trail_step(u8 *obj) {
    u8 *rec = *(u8 **)(obj + 0x98);
    s8 done = 0;
    s32 a;

    if (rec[0x20] != 0) {
        if (!D_8008A780[rec[0x20]](obj)) {
            done = 1;
        }
    }
    if (rec[0x21] != 0 && !done) {
        if (!D_8008A798[rec[0x21]](obj)) {
            done = 1;
        }
    }
    if ((rec[0x18] & 0x40) && !done && *(s16 *)(obj + 0x1C) < *(s16 *)(rec + 0x1C)) {
        a = *(s16 *)(obj + 0x1C) * *(s16 *)(rec + 0x1E);
        if (a < rec[0x1B]) {
            rec[0x1B] = a;
        }
    }
    if (done && rec[0x22] != 0) {
        /* the asm leaves a1 = 0 (the return value) and a2 = 1 (done) in the argument registers */
        D_8008A7CC[rec[0x22]](obj, 0, 1, 0, 0.0f, 0);
    }
    if (*(s8 *)(obj + 0x2C) > 0) {
        u8 *p = *(u8 **)(obj + 0x94) + *(s8 *)(obj + 0x2D) * 0x14;

        *(s32 *)(obj + 0x54) = *(s32 *)(p + 0);
        *(s32 *)(obj + 0x58) = *(s32 *)(p + 4);
        *(s32 *)(obj + 0x5C) = *(s32 *)(p + 8);
    } else {
        *(f32 *)(obj + 0x54) = 0.0f;
        *(f32 *)(obj + 0x58) = 0.0f;
        *(f32 *)(obj + 0x5C) = 0.0f;
    }
    return !done;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/trail_step.s")
#endif
#ifdef NON_MATCHING
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
f32 *camera_get_pos(s32 arg0);
s32 fx_material_tex_addr(s32, s32, s32, u8);
s32 gfx_load_texture_tile(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
void fx_calc_color_mode_a(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
void fx_calc_color_mode_b(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_env_color_cached(s32, s32, s32, s32, s32, s8 *);
s32 gfx_prim_color_cached(s32, s32, s32, s16, s32, s32, s32, s8 *);
s32 gfx_set_combine_mode(s32, u8, s8 *);
u8 *gfx_other_mode_cached(s32, s32, s32, s8 *);
f32 sqrtf(f32);
extern s32 D_80091914[];
extern s32 D_80091954[];
extern s32 D_800D30BC;
extern s32 D_800A4EA8[];

/* One strip vertex: position, flag 0, s = 0x43C0 (outer edge) or 0x4000 (inner edge), t = point +0x10 + 0x4000,
 * colour white. */
#define TRAIL_VTX(v, px, py, pz, s, t) \
    do { \
        *(s16 *)((v) + 0x0) = (s32)(px); \
        *(s16 *)((v) + 0x2) = (s32)(py); \
        *(s16 *)((v) + 0x4) = (s32)(pz); \
        *(s16 *)((v) + 0xA) = (t) + 0x4000; \
        *(s16 *)((v) + 0x8) = (s); \
        (v)[0xC] = 0xFF; \
        (v)[0xD] = 0xFF; \
        (v)[0xE] = 0xFF; \
        (v)[0xF] = 0xFF; \
        *(s16 *)((v) + 0x6) = 0; \
    } while (0)

// trail_draw: draws a trail particle as a camera-facing strip (type table D_8008A644 entry 1).
/* The points (obj +0x94, 0x14 bytes: x, y, z, vy, s16 texture t at +0x10) run from the newest (+0x2E - 1) back to
 * the oldest (+0x2D), ring of +0x25 entries. Each point gets two vertices, offset by +-n where n is the normal of
 * (point - camera) x (segment) scaled to the half width rec +0; each segment emits one 4-vertex load and two
 * triangles. Vertices come from vtx_slot_buffer_get (2 per point but the last, double-buffered on D_800BE9C0). Sets the
 * texture (gfx_load_texture_tile, only when it changed: D_800DD5E0), the colours rec +0x44 / +0x45 at alpha rec +0x1B,
 * the geometry mode rec +0x2C / +0x30, combine rec +0x3B and render mode rec +0x28 | +0x3C | +0x40 with the
 * D_800A4EA8 entry rec +0x34. Returns the display list end; draws nothing with fewer than 2 points. */
/* was func_151485AC */
s32 trail_draw(u8 *obj, s32 gfx, s16 arg2) {
    u8 *rec = *(u8 **)(obj + 0x98);
    u8 *pts;
    f32 *cam;
    u8 *v;
    u8 *p0;
    u8 *p1;
    s32 tex;
    s32 i;
    s32 j;
    s8 flag;
    s16 r0, g0, b0, a0;
    s16 r1, g1, b1, a1;
    f32 ax, ay, az;
    f32 bx, by, bz;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 cx, cy, cz;
    f32 nx, ny, nz;
    f32 len;
    f32 k;

    if (*(s8 *)(obj + 0x2C) < 2) {
        return gfx;
    }
    vtx_slot_buffer_get((s32 *)(obj + 0x84), arg2, obj[0x25] * 0x20 - 0x20, (s32 *)&v, NULL);
    if (v == NULL) {
        return gfx;
    }
    if (D_800BE9C0 != 0) {
        v += (obj[0x25] * 2 - 2) * 0x10;
    }
    flag = 1;
    cam = camera_get_pos(arg2);
    pts = *(u8 **)(obj + 0x94);
    tex = fx_material_tex_addr(0, rec[0x19], 0, 2);
    if (tex != D_800DD5E0) {
        D_80091954[0] = D_80091914[rec[0x19]];
        gfx = gfx_load_texture_tile(gfx, D_80091954, 0, 0, 0, 0, 2, 0x100, 0x100, (rec[0x18] & 0x80) ? 0x3E : 3);
        D_800DD5E0 = tex;
    }
    fx_calc_color_mode_a(&r0, &g0, &b0, &a0, 0, 0, 0, 0, 0, 0, 0, rec[0x1B], rec[0x1A], *(s8 *)(rec + 0x44));
    fx_calc_color_mode_b(&r1, &g1, &b1, &a1, 0, 0, 0, 0, 0, 0, 0, rec[0x1B], rec[0x1A], *(s8 *)(rec + 0x45));
    gfx = gfx_geometry_mode_cached(gfx, *(s32 *)(rec + 0x2C), *(s32 *)(rec + 0x30));
    gfx = gfx_env_color_cached(gfx, r1, g1, b1, a1, &flag);
    gfx = gfx_prim_color_cached(gfx, 0, 0, r0, g0, b0, a0, &flag);
    gfx = gfx_set_combine_mode(gfx, rec[0x3B], &flag);
    gfx = (s32)gfx_other_mode_cached(gfx, *(s32 *)(rec + 0x28) | 0x80000 | D_800D30BC | 0x2C00 | *(s32 *)(rec + 0x3C) | *(s32 *)(rec + 0x40),
                             D_800A4EA8[*(s32 *)(rec + 0x34) * 2 + 1] | D_800A4EA8[*(s32 *)(rec + 0x34) * 2], &flag);

    i = *(s8 *)(obj + 0x2E) - 1;
    if (i < 0) {
        i = obj[0x25] - 1;
    }
    j = i - 1;
    if (j < 0) {
        j = obj[0x25] - 1;
    }
    p0 = pts + i * 0x14;
    p1 = pts + j * 0x14;
    ax = *(f32 *)(p0 + 0);
    ay = *(f32 *)(p0 + 4);
    az = *(f32 *)(p0 + 8);
    bx = *(f32 *)(p1 + 0);
    by = *(f32 *)(p1 + 4);
    bz = *(f32 *)(p1 + 8);

    /* the newest point */
    dx = ax - cam[0];
    dy = ay - cam[1];
    dz = az - cam[2];
    ex = ax - bx;
    ey = ay - by;
    ez = az - bz;
    cx = ey * dz - dy * ez;
    cy = ez * dx - dz * ex;
    cz = ex * dy - dx * ey;
    len = sqrtf(cx * cx + cy * cy + cz * cz);
    if (len == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        k = *(f32 *)(rec + 0) / len;
        nx = cx * k;
        ny = cy * k;
        nz = cz * k;
    }
    TRAIL_VTX(v, ax + nx, ay + ny, az + nz, 0x43C0, *(u16 *)(p0 + 0x10));
    v += 0x10;
    TRAIL_VTX(v, ax - nx, ay - ny, az - nz, 0x4000, *(u16 *)(p0 + 0x10));
    v += 0x10;

    /* one segment per older point */
    do {
        i = j;
        j--;
        dx = bx - cam[0];
        dy = by - cam[1];
        dz = bz - cam[2];
        ex = ax - bx;
        ey = ay - by;
        ez = az - bz;
        cx = ey * dz - dy * ez;
        cy = ez * dx - dz * ex;
        cz = ex * dy - dx * ey;
        len = sqrtf(cx * cx + cy * cy + cz * cz);
        if (len == 0.0f) {
            nx = ny = nz = 0.0f;
        } else {
            k = *(f32 *)(rec + 0) / len;
            nx = cx * k;
            ny = cy * k;
            nz = cz * k;
        }
        TRAIL_VTX(v, bx + nx, by + ny, bz + nz, 0x43C0, *(u16 *)(p1 + 0x10));
        v += 0x10;
        TRAIL_VTX(v, bx - nx, by - ny, bz - nz, 0x4000, *(u16 *)(p1 + 0x10));
        v += 0x10;
        ((s32 *)gfx)[0] = 0x01004008;           /* gSPVertex(v - 4, 4, 0) */
        ((s32 *)gfx)[1] = (s32)(v - 0x40);
        gfx += 8;
        ((s32 *)gfx)[0] = 0x05000204;           /* gSP1Triangle(0, 1, 2) */
        ((s32 *)gfx)[1] = 0;
        gfx += 8;
        ((s32 *)gfx)[0] = 0x05020604;           /* gSP1Triangle(1, 3, 2) */
        ((s32 *)gfx)[1] = 0;
        gfx += 8;
        p1 -= 0x14;
        if (j < 0) {
            j = obj[0x25] - 1;
            p1 = pts + j * 0x14;
        }
        p0 = pts + i * 0x14;
        ax = *(f32 *)(p0 + 0);
        ay = *(f32 *)(p0 + 4);
        az = *(f32 *)(p0 + 8);
        bx = *(f32 *)(p1 + 0);
        by = *(f32 *)(p1 + 4);
        bz = *(f32 *)(p1 + 8);
    } while (i != *(s8 *)(obj + 0x2D));
    return gfx;
}
#undef TRAIL_VTX
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/trail_draw.s")
#endif
#ifdef NON_MATCHING
// trail_grow: motion handler 1 of a trail (D_8008A780): moves the points and adds one per frame until full.
/* Points obj +0x94 (0x14 bytes: x, y, z, vy, u16 t at +0x10) in a ring of +0x25 from the oldest +0x2D to the head
 * +0x2E (exclusive), count +0x2C. Each point falls by gravity rec +0x10 (rec = obj +0x98) into its vy and moves by
 * (rec +4, vy, rec +0xC) times the frame time D_800BE9A4. While the ring has room, the obj position (+0x10) is added
 * at the head with vy = rec +8 and the texture t of all points is ramped 0..0x1000 (0x1000..0 with rec +0x18 flag
 * 0x20); once full, rec +0x20 becomes 3 (trail_fall, if rec +0x18 & 0x17) or 2 (trail_move_points). Returns 1. */
/* was func_15148E34 */
s32 trail_grow(u8 *obj) {
    u8 *pts = *(u8 **)(obj + 0x94);
    u8 *rec = *(u8 **)(obj + 0x98);
    u8 *p;
    s32 i;
    s32 n;
    u16 t;
    u16 step;

    i = *(s8 *)(obj + 0x2D);
    while (i != *(s8 *)(obj + 0x2E)) {
        p = pts + i * 0x14;
        i++;
        *(f32 *)(p + 0xC) -= *(f32 *)(rec + 0x10) * D_800BE9A4;
        *(f32 *)(p + 0x0) += *(f32 *)(rec + 0x4) * D_800BE9A4;
        *(f32 *)(p + 0x4) += *(f32 *)(p + 0xC) * D_800BE9A4;
        *(f32 *)(p + 0x8) += *(f32 *)(rec + 0xC) * D_800BE9A4;
        if (i == obj[0x25]) {
            i = 0;
        }
    }
    n = *(s8 *)(obj + 0x2C);
    if (n >= obj[0x25] - 1) {
        rec[0x20] = (rec[0x18] & 0x17) ? 3 : 2;
        return 1;
    }
    t = (rec[0x18] & 0x20) ? 0x1000 : 0;
    step = 0; /* the asm leaves it unset for an empty trail (only the first point is then written) */
    if (n != 0) {
        step = 0x1000 / n;
    }
    obj[0x2C] = n + 1;
    p = pts + *(s8 *)(obj + 0x2E) * 0x14;
    *(s32 *)(p + 0) = *(s32 *)(obj + 0x10);
    *(s32 *)(p + 4) = *(s32 *)(obj + 0x14);
    *(s32 *)(p + 8) = *(s32 *)(obj + 0x18);
    *(f32 *)(pts + *(s8 *)(obj + 0x2E) * 0x14 + 0xC) = *(f32 *)(rec + 8);
    obj[0x2E]++;
    if (*(s8 *)(obj + 0x2E) == obj[0x25]) {
        obj[0x2E] = 0;
    }
    i = *(s8 *)(obj + 0x2D);
    if (i != *(s8 *)(obj + 0x2E)) {
        do {
            *(u16 *)(pts + i * 0x14 + 0x10) = t;
            if (rec[0x18] & 0x20) {
                t -= step;
            } else {
                t += step;
            }
            i++;
            if (i == obj[0x25]) {
                i = 0;
            }
        } while (i != *(s8 *)(obj + 0x2E));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/trail_grow.s")
#endif
typedef struct { f32 x; f32 y; f32 z; f32 vy; s16 a; s16 pad12; } Part9064;
/* was func_15149064 */
s32 trail_move_points(u8 *arg0) {
    Part9064 *base;
    f32 *v;
    s32 i;
    Part9064 *p;

    base = *(Part9064 **)(arg0 + 0x94);
    v = *(f32 **)(arg0 + 0x98);
    i = *(s8 *)(arg0 + 0x2E);
    do {
        i--;
        if (i < 0) {
            i = *(u8 *)(arg0 + 0x25) - 1;
        }
            base[i].vy -= v[4] * D_800BE9A4;
        base[i].x += v[1] * D_800BE9A4;
        base[i].y += base[i].vy * D_800BE9A4;
        base[i].z += v[3] * D_800BE9A4;
    } while (i != *(s8 *)(arg0 + 0x2D));
    return 1;
}

#ifdef NON_MATCHING
s32 collision_floor_probe(f32 *, s32, f32, u8 *);
s32 drip_stream_splash(u8 *, s32, s32, s32, f32);
s32 drip_stream_splash_dust(u8 *, s32, s32, s32, f32, s32);
s32 streak_on_land_debris(u8 *, s32, s32, s32, f32, s32);
s32 streak_on_land_burst(void *, s32, s32, s32, f32, s32);
extern s32 (*D_8008A7D0[])(u8 *, s32, s32, s32, f32, s32);
extern s32 (*D_8008A7F0[])(u8 *, s32, s32, s32, f32, s32);

// trail_fall: motion handler 3 of a full trail (D_8008A780): moves the points and checks the oldest for a hit.
/* Points as trail_grow (all of them, from the head +0x2E back to the oldest +0x2D). With rec +0x18 & 0x17 (rec =
 * obj +0x98) and the oldest point moving down, the segment from its old height to the new one is tested against
 * the collision (collision_floor_probe, result in obj +0x60..); on a hit the handler rec +0x24 (D_8008A7F0, when the hit
 * kind obj +0x7D is 3) or rec +0x23 (D_8008A7D0) gets the old position, the hit height +0x60 and obj +0x64.
 * Returns 0 when that handler does, else 1. */
/* was func_15149114 */
s32 trail_fall(u8 *obj) {
    u8 *rec = *(u8 **)(obj + 0x98);
    u8 *pts = *(u8 **)(obj + 0x94);
    s32 old[3]; /* the oldest point before the move (x, y, z as words) */
    f32 seg[3];
    u8 *p;
    s32 i;
    s32 k;

    if (rec[0x18] & 7) {
        p = pts + *(s8 *)(obj + 0x2D) * 0x14;
        old[0] = *(s32 *)(p + 0);
        old[1] = *(s32 *)(p + 4);
        old[2] = *(s32 *)(p + 8);
    } else {
        old[0] = old[1] = old[2] = 0; /* unset in the asm (only read when rec +0x18 has 0x10 but none of 7) */
    }
    i = *(s8 *)(obj + 0x2E);
    do {
        i--;
        if (i < 0) {
            i = obj[0x25] - 1;
        }
        p = pts + i * 0x14;
        *(f32 *)(p + 0xC) -= *(f32 *)(rec + 0x10) * D_800BE9A4;
        *(f32 *)(p + 0x0) += *(f32 *)(rec + 0x4) * D_800BE9A4;
        *(f32 *)(p + 0x4) += *(f32 *)(p + 0xC) * D_800BE9A4;
        *(f32 *)(p + 0x8) += *(f32 *)(rec + 0xC) * D_800BE9A4;
    } while (i != *(s8 *)(obj + 0x2D));

    if (!(rec[0x18] & 0x17)) {
        return 1;
    }
    p = pts + *(s8 *)(obj + 0x2D) * 0x14;
    if (!(*(f32 *)(p + 4) < *(f32 *)&old[1])) {
        return 1;
    }
    seg[0] = *(f32 *)(p + 0);
    seg[1] = *(f32 *)&old[1];
    seg[2] = *(f32 *)(pts + *(s8 *)(obj + 0x2D) * 0x14 + 8);
    if (!collision_floor_probe(seg, 0, *(f32 *)(pts + *(s8 *)(obj + 0x2D) * 0x14 + 4), obj + 0x60)) {
        return 1;
    }
    if (obj[0x7D] == 3) {
        k = rec[0x24];
        if (k == 0) {
            return 1;
        }
        return D_8008A7F0[k](obj, old[0], old[1], old[2], *(f32 *)(obj + 0x60), (s32)(obj + 0x64)) != 0;
    }
    k = rec[0x23];
    if (k == 0) {
        return 1;
    }
    return D_8008A7D0[k](obj, old[0], old[1], old[2], *(f32 *)(obj + 0x60), (s32)(obj + 0x64)) != 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/trail_fall.s")
#endif
#ifdef NON_MATCHING
// trail_shrink: motion handler 4 of a trail (D_8008A780): drops the newest point each frame and re-ramps the rest.
/* Count obj +0x2C, ring of +0x25 points obj +0x94 (0x14 bytes, u16 texture t at +0x10) from the oldest +0x2D to the
 * head +0x2E. Returns 0 (the trail ends) when fewer than 3 points are left; else removes the head point and sets
 * the texture t of the others to a 0..0x1000 ramp (0x1000..0 with rec +0x18 flag 0x20, rec = obj +0x98), returns 1. */
/* was func_15149350 */
s32 trail_shrink(u8 *obj) {
    u8 *rec;
    u8 *pts;
    s32 i;
    u16 t;
    u16 step;

    if (*(s8 *)(obj + 0x2C) < 3) {
        return 0;
    }
    obj[0x2C] = *(s8 *)(obj + 0x2C) - 1;
    rec = *(u8 **)(obj + 0x98);
    pts = *(u8 **)(obj + 0x94);
    step = 0x1000 / *(s8 *)(obj + 0x2C);
    t = (rec[0x18] & 0x20) ? 0x1000 : 0;
    i = *(s8 *)(obj + 0x2D);
    obj[0x2E] = *(s8 *)(obj + 0x2E) - 1;
    if (*(s8 *)(obj + 0x2E) < 0) {
        obj[0x2E] = obj[0x25] - 1;
    }
    if (i != *(s8 *)(obj + 0x2E)) {
        do {
            *(u16 *)(pts + i * 0x14 + 0x10) = t;
            if (rec[0x18] & 0x20) {
                t -= step;
            } else {
                t += step;
            }
            i++;
            if (i == obj[0x25]) {
                i = 0;
            }
        } while (i != *(s8 *)(obj + 0x2E));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/trail_shrink.s")
#endif
/* was func_15149468 */
s32 trail_start_shrink(u8 **arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp = arg0[0x98 / 4];
    temp[0x20] = 4;
    return 1;
}

#ifdef NON_MATCHING
/* P136 */
/*
 * trail_spawn_directed: spawns one trail particle (trail_spawn, kind 0, handler pair 1 / 0) of type n at
 * (x, y, z) with sprite `sprite` and tint tint + 3. Its velocity has length speed along the byte angles pitch /
 * yaw (angle_byte_cos = byte-angle sine): (speed sin(pitch) sin(yaw - 0x40), -speed sin(pitch - 0x40),
 * speed sin(pitch) sin(yaw)); motion block speed slot = drag, scale = scale, flags 8 (0x28 for type 0xA),
 * 0xFF / 0xFF; fixed render block (0, 1, 0x160600, mode 3 / 0x10 / 0x80 / 0x20, 0, 9). flag goes to argD.
 * The asm leaves some block bytes unwritten (spawn +0x14 / +0x18, motion floor +0x14 and timers +0x1C / +0x1E,
 * render +0x1E): the C clears them.
 */
/* was func_1514948C */
void trail_spawn_directed(u8 n, f32 x, f32 y, f32 z, s32 tint, s32 yaw, s32 pitch, f32 speed, s32 sprite, f32 drag, f32 scale,
                   u8 flag) {
    struct {
        s32 render[3]; /* sp4C */
        s32 mode[4];
        u8 b0;
        u8 b1;
        u8 pad[2];
    } rb;
    struct {
        f32 speed;     /* sp7C */
        f32 vel[3];
        f32 scale;
        f32 floor;
        u8 flags;
        u8 kind;
        u8 full;
        u8 alpha;
        s16 t0;
        s16 t1;
    } mb;
    struct {
        f32 pos[3];    /* sp9C */
        s16 sprite;
        s16 model;
        s32 count;
        s8 b14;
        u8 tint;
        s32 owner;
    } sb;
    f32 sp = angle_byte_cos((u8) pitch);
    f32 cp = angle_byte_cos((pitch - 0x40) & 0xFF);
    f32 sy = angle_byte_cos((u8) yaw);
    f32 cy = angle_byte_cos((yaw - 0x40) & 0xFF);
    f32 h;

    sb.count = 1;
    sb.model = 1;
    mb.full = 0xFF;
    mb.flags = (n == 0xA) ? 0x28 : 8;
    mb.kind = n;
    h = speed * sp;
    sb.pos[0] = x;
    sb.pos[1] = y;
    sb.pos[2] = z;
    mb.speed = drag;
    mb.scale = scale;
    sb.tint = tint + 3;
    mb.alpha = 0xFF;
    sb.sprite = sprite;
    mb.vel[0] = h * cy;
    mb.vel[1] = -speed * cp;
    mb.vel[2] = h * sy;
    sb.b14 = 0;
    sb.owner = 0;
    mb.floor = 0.0f;
    mb.t0 = 0;
    mb.t1 = 0;
    rb.render[0] = 0;
    rb.render[1] = 1;
    rb.render[2] = 0x160600;
    rb.mode[0] = 3;
    rb.mode[1] = 0x10;
    rb.mode[2] = 0x80;
    rb.mode[3] = 0x20;
    rb.b0 = 0;
    rb.b1 = 9;
    rb.pad[0] = rb.pad[1] = 0;
    trail_spawn((u8 *) &sb, (s32) &mb, 0, 1, 0, 0, 0, 0, 0, 0, 0, (u8 *) &rb, 0, flag, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/trail_spawn_directed.s")
#endif

/* was func_15149638 */
s32 trail_alpha_from_timer(u8 *arg0) {
    u8 *temp_v0;
    s32 temp_v1;

    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C) * 8;
    if (temp_v1 >= 256) {
        temp_v1 = 255;
    }
    temp_v0[0x1B] = temp_v1;
    if ((u8)temp_v1 < 0) {
        return 0;
    }
    return 1;
}

/* was func_15149674 */
void trail_die_retire(s32 arg0) {
    fxrec_die_retire(arg0);
}
