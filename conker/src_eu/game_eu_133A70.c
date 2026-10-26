#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void arc_control_points_thirds(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void obj_attach_point_at_angles(u8 *arg0, s16 arg1, s16 arg2, u8 *arg3, u8 *arg4);
void obj_bone_point_transform(u8 *arg0, u8 arg1, void *arg2, void *arg3);
#endif


#ifdef NON_MATCHING
void bolt_arc_sample_curve(struct102 *);
void bolt_arc_jitter_points(struct102 *);
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 random_int(void);
void *memcpy(void *, const void *, unsigned int);

/* The 0x70-byte particle spec particle_spawn_ex gets for each arc end. */
typedef struct {
    s32 w00;            /* 0x00 0x200005 */
    s32 w04;            /* 0x04 0 */
    s16 h08;            /* 0x08 0x4404 */
    s16 life;           /* 0x0A 300 */
    s32 w0C, w10;       /* 0x0C 0 */
    u8 rgba0[4];        /* 0x14 FF FF FF FF */
    u8 rgba1[4];        /* 0x18 the arc's colour (spec +0x48..+0x4B) */
    u8 b1C, b1D;        /* 0x1C 0xFF 0x2B */
    s16 h1E, h20, h22;  /* 0x1E 1, 0xFF, 1 */
    f32 f24;            /* 0x24 1.0 */
    f32 size[2];        /* 0x28 width * (1 / 13) * 200 (both) */
    f32 pos[3];         /* 0x30 the arc end */
    f32 f3C[3];         /* 0x3C D_800A5860 */
    f32 f48[3];         /* 0x48 D_800A5860 */
    f32 f54;            /* 0x54 0 */
    s32 flags;          /* 0x58 bits 0x40 / 0x80 random */
    s32 w5C;            /* 0x5C 0 */
    u8 b60, b61;        /* 0x60 6 6 */
    s8 b62, b63, b64;   /* 0x62 -1 -1 -1 */
    u8 b65, b66;        /* 0x65 0 0xFF */
    s16 h68;            /* 0x68 0 */
    f32 f6C;            /* 0x6C 1000000.0 */
} ArcEndSpec;

// bolt_arc_spawn: creates a lightning arc object (type 0x40, node_alloc layer `layer` / `arg3`) from the 0x50-byte
// arc spec `spec` (copied to +0x10; +0x38 = segment count n, +0x40 width, +0x44 / +0x46 life base / random range,
// +0x48 colour). The object's data area (+0x60) follows its 0x88-byte header, n * 0x34 + (n + 2) * 0xC bytes in and
// `extra` more bytes are reserved for the caller. Sets the step 1 / (n + 1) (+0x64) and the life (+0x68), builds the
// points (bolt_arc_sample_curve, bolt_arc_jitter_points), clears +0x6C..+0x83, sets +0x84 = n * 0x30 + 0x60 and spawns one glow
// particle at each arc end (particle_spawn_ex, handles at +0x6C / +0x70). Returns the object (NULL when none is free).
/* was func_15106260 */
u8 *bolt_arc_spawn(s16 *spec, s32 extra, u8 layer, s32 arg3) {
    ArcEndSpec ps;
    u8 *p = (u8 *)spec;
    u8 *obj;
    s32 n = *(s32 *)(p + 0x38);
    s32 flags;
    u8 i;

    obj = node_alloc(0x40, arg3, n * 0x34 + (n + 2) * 0xC + extra + 0x88, 1, layer, 1);
    if (obj == NULL) {
        return NULL;
    }
    memcpy(obj + 0x10, p, 0x50);
    *(u8 **)(obj + 0x60) = obj + n * 0x34 + (n + 2) * 0xC + 0x88;
    *(f32 *)(obj + 0x64) = 1.0f / (f32)(*(s32 *)(p + 0x38) + 1);
    *(s16 *)(obj + 0x68) = (u32)random_int() % (u32)(*(s16 *)(p + 0x46) + 1) + *(s16 *)(p + 0x44);
    bolt_arc_sample_curve((struct102 *)obj);
    bolt_arc_jitter_points((struct102 *)obj);
    *(s32 *)(obj + 0x6C) = 0;
    *(s32 *)(obj + 0x70) = 0;
    bzero(obj + 0x74, 0x10);
    *(s32 *)(obj + 0x84) = *(s32 *)(obj + 0x48) * 0x30 + 0x60;

    ps.w00 = 0x200005;
    ps.w04 = 0;
    ps.h08 = 0x4404;
    ps.life = 300;
    ps.w0C = 0;
    ps.w10 = 0;
    ps.rgba0[0] = 0xFF;
    ps.rgba0[1] = 0xFF;
    ps.rgba0[2] = 0xFF;
    ps.rgba0[3] = 0xFF;
    ps.rgba1[0] = p[0x48];
    ps.rgba1[1] = p[0x49];
    ps.rgba1[2] = p[0x4A];
    ps.rgba1[3] = p[0x4B];
    ps.b1C = 0xFF;
    ps.b1D = 0x2B;
    ps.h1E = 1;
    ps.h20 = 0xFF;
    ps.h22 = 1;
    ps.f24 = 1.0f;
    ps.f3C[0] = ((f32 *) D_800A5860)[0];
    ps.f3C[1] = ((f32 *) D_800A5860)[1];
    ps.f3C[2] = ((f32 *) D_800A5860)[2];
    ps.f48[0] = ((f32 *) D_800A5860)[0];
    ps.f48[1] = ((f32 *) D_800A5860)[1];
    ps.f48[2] = ((f32 *) D_800A5860)[2];
    ps.f54 = 0.0f;
    ps.w5C = 0;
    ps.b60 = 6;
    ps.b61 = 6;
    ps.b62 = -1;
    ps.b63 = -1;
    ps.b64 = -1;
    ps.b65 = 0;
    ps.b66 = 0xFF;
    ps.h68 = 0;
    ps.f6C = 1000000.0f;
    ps.size[1] = *(f32 *)(p + 0x40) * 0.07692308f * 200.0f;
    ps.size[0] = ps.size[1];

    for (i = 0; i < 2; i++) {
        f32 *end = (f32 *)(p + (i == 0 ? 0x04 : 0x28));   /* the arc start, then its end */

        ps.pos[0] = end[0];
        ps.pos[1] = end[1];
        ps.pos[2] = end[2];
        flags = random_int() ? 0x40 : 0;
        ps.flags = (random_int() ? 0x80 : 0) | flags;
        *(s32 *)(obj + 0x6C + i * 4) = particle_spawn_ex((s32)&ps, 0, 0, 0, layer, arg3);
    }
    return obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/bolt_arc_spawn.s")
#endif

typedef struct { f32 x, y, z; } V3_133A70;
void bolt_arc_sample_curve(struct102 *);
void bolt_arc_jitter_points(struct102 *);
extern s32 D_80088FB0;

/* was func_1510660C */
void bolt_arc_update(struct102 *arg0) {
    s32 (*temp_v1)(struct102 *, u8 *);
    u8 sp2B;
    s8 temp_v0;
    u8 *temp_v0_3;

    sp2B = 0;
    temp_v0 = (*(s8 *)((u8 *)arg0 + 0x44));
    if (temp_v0 != -1) {
        temp_v1 = *(s32 *)((u8 *)&D_80088FB0 + (temp_v0 * 4));
        if ((temp_v1 != NULL) && (temp_v1(arg0, &sp2B) == 0)) {
            node_destroy(arg0);
        }
    }
    if (arg0->unk12 & 1) {
        arg0->unk10 -= D_800BE9E4;
        if (arg0->unk10 < 0) {
            node_destroy(arg0);
        }
    }
    if (sp2B != 0) {
        bolt_arc_sample_curve(arg0);
    }
    (*(s16 *)((u8 *)arg0 + 0x68)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x68)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)arg0 + 0x68)) < 0) {
        bolt_arc_jitter_points(arg0);
        (*(s16 *)((u8 *)arg0 + 0x68)) = (s16) (((*(s16 *)((u8 *)arg0 + 0x54)) + (random_int() % (u32) ((*(s16 *)((u8 *)arg0 + 0x56)) + 1))));
    }
    temp_v0_3 = (*(u8 **)((u8 *)arg0 + 0x6C));
    if (temp_v0_3 != NULL) {
        *(V3_133A70 *)(temp_v0_3 + 0x40) = *(V3_133A70 *)((u8 *)arg0 + 0x14);
    }
    temp_v0_3 = (*(u8 **)((u8 *)arg0 + 0x70));
    if (temp_v0_3 != NULL) {
        *(V3_133A70 *)(temp_v0_3 + 0x40) = *(V3_133A70 *)((u8 *)arg0 + 0x38);
    }
}

/* was func_15106760 */
s32 bolt_arc_samples_get(s32 arg0) {
    return arg0 + 0x88;
}

typedef struct {
    u8 pad0[0x34];
} struct_eu_133A70_elem;

typedef struct {
    u8 pad0[0x48];
    s32 unk48;
    u8 pad4C[0x3C];
    struct_eu_133A70_elem unk88[1];
} struct_eu_133A70;

/* was func_1510676C */
struct_eu_133A70_elem *bolt_arc_points_get(struct_eu_133A70 *arg0) {
    s32 temp_v1 = arg0->unk48;

    return &arg0->unk88[temp_v1];
}

#ifdef NON_MATCHING
s32 vec3_make_basis(f32 *, f32 *, f32 *);
f32 bezier_basis0(f32);
f32 bezier_basis1(f32);
f32 bezier_basis2(f32);
f32 bezier_basis3(f32);
f32 bezier_basis0_deriv(f32);
f32 bezier_basis1_deriv(f32);
f32 bezier_basis2_deriv(f32);
f32 bezier_basis3_deriv(f32);
// bolt_arc_sample_curve: samples the arc's cubic Bezier curve (control points +0x14, +0x20, +0x2C, +0x38) at the
// +0x48 points t = step, 2 * step, ... (step +0x64 = 1 / (n + 1)) into the 0x34-byte records at +0x88: t, the
// position (Bernstein weights bezier_basis0 / A5C / A90 / AC0), the tangent (derivatives bezier_basis0_deriv / B04 / B3C /
// B6C) and two side vectors at +0x1C / +0x28 from vec3_make_basis (zero when it fails, e.g. a zero tangent).
// The asm leaves a stale v0; the only caller (bolt_arc_spawn) ignores it, so the C is void.
/* was func_15106794 */
void bolt_arc_sample_curve(struct102 *arg0) {
    u8 *obj = (u8 *) arg0;
    f32 *rec;
    f32 *p0 = (f32 *) (obj + 0x14);
    f32 *p1 = (f32 *) (obj + 0x20);
    f32 *p2 = (f32 *) (obj + 0x2C);
    f32 *p3 = (f32 *) (obj + 0x38);
    f32 step;
    f32 t;
    f32 b0, b1, b2, b3;
    f32 d0, d1, d2, d3;
    s32 i;
    s32 k;

    rec = (f32 *) bolt_arc_samples_get((s32) arg0);
    step = *(f32 *) (obj + 0x64);
    t = step;
    for (i = 0; i < *(s32 *) (obj + 0x48); i++) {
        rec[0] = t;
        b0 = bezier_basis0(t);
        b1 = bezier_basis1(t);
        b2 = bezier_basis2(t);
        b3 = bezier_basis3(t);
        d0 = bezier_basis0_deriv(t);
        d1 = bezier_basis1_deriv(t);
        d2 = bezier_basis2_deriv(t);
        d3 = bezier_basis3_deriv(t);
        for (k = 0; k < 3; k++) {
            rec[1 + k] = p0[k] * b0 + p1[k] * b1 + p2[k] * b2 + p3[k] * b3;
        }
        for (k = 0; k < 3; k++) {
            rec[4 + k] = p0[k] * d0 + p1[k] * d1 + p2[k] * d2 + p3[k] * d3;
        }
        if (vec3_make_basis(rec + 4, rec + 7, rec + 10) == 0) {
            rec[7] = 0.0f;
            rec[8] = 0.0f;
            rec[9] = 0.0f;
            rec[10] = 0.0f;
            rec[11] = 0.0f;
            rec[12] = 0.0f;
        }
        rec += 13;
        t += step;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/bolt_arc_sample_curve.s")
#endif

/* was func_15106A34 */
f32 bezier_basis0(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return temp_f2 * temp_f2 * temp_f2;
}

/* was func_15106A5C */
f32 bezier_basis1(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return 3.0f * arg0 * temp_f2 * temp_f2;
}

/* was func_15106A90 */
f32 bezier_basis2(f32 arg0) {
    return 3.0f * arg0 * arg0 * (1.0f - arg0);
}

/* was func_15106AC0 */
f32 bezier_basis3(f32 arg0) {
    return arg0 * arg0 * arg0;
}

/* was func_15106AD8 */
f32 bezier_basis0_deriv(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return -3.0f * temp_f2 * temp_f2;
}

/* was func_15106B04 */
f32 bezier_basis1_deriv(f32 arg0) {
    return ((9.0f * arg0 * arg0) - (12.0f * arg0)) + 3.0f;
}

/* was func_15106B3C */
f32 bezier_basis2_deriv(f32 arg0) {
    return (-9.0f * arg0 * arg0) + (6.0f * arg0);
}

/* was func_15106B6C */
f32 bezier_basis3_deriv(f32 arg0) {
    return 3.0f * arg0 * arg0;
}

// PERMUTER CHANGED DECL: voidfunc_15106B90(struct102*) (base: voidfunc_15106B90(struct102*arg0))
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);

/* was func_15106B90 */
void bolt_arc_jitter_points(struct102 *arg0)
{
  s32 i;
  u8 *src;
  V3_133A70 *d;
  V3_133A70 *dst;
  u8 *q;
  src = (u8 *) bolt_arc_samples_get((s32) arg0);
  d = (V3_133A70 *) bolt_arc_points_get((struct_eu_133A70 *) arg0);
  d[0] = *((V3_133A70 *) (((u8 *) arg0) + 0x14));
  d[(*((s32 *) (((u8 *) arg0) + 0x48))) + 1] = *((V3_133A70 *) (((u8 *) arg0) + 0x38));
  for (i = 1; i < ((*((s32 *) (((u8 *) arg0) + 0x48))) + 1); i++)
  {
    s32 pad; // fakematch: frame slot below s, c
    f32 s;
    f32 c;
    dst = &d[i];
    q = src + ((i - 1) * 0x34);
    if (!arg0) { // fakematch: permuter (s-register order of i / dst / src)
    }
    vec2_from_angle_byte(random_int() & 0xFF, (*((f32 *) (((u8 *) arg0) + 0x4C))) * random_float(), &c, &s);
    dst->x = (*((f32 *) (q + 4))) + (((*((f32 *) (q + 0x28))) * s) + ((*((f32 *) (q + 0x1C))) * c));
    dst->y = (*((f32 *) (q + 8))) + (((*((f32 *) (q + 0x2C))) * s) + ((*((f32 *) (q + 0x20))) * c));
    dst->z = (*((f32 *) (q + 0xC))) + (((*((f32 *) (q + 0x30))) * s) + ((*((f32 *) (q + 0x24))) * c));
  }

}

#ifdef NON_MATCHING
void vtx_slot_buffer_get(s32 *, s16, s32, Vtx **, u8 *);
s32 gfx_load_texture_cached(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
s32 gfx_set_combine_mode(s32, u8, s8 *);
s32 gfx_geometry_mode_cached(s32, s32, s32);
s32 gfx_env_color_cached(s32, s32, s32, s32, s32, s8 *);
s32 gfx_other_mode_cached(s32, s32, s32, s8 *);
extern s32 D_80091120[];  /* ribbon texture descriptor */
extern s32 D_800D30BC;
extern s32 D_800A4EA8[];  /* render mode pairs (2 words each) */

/* rodata D_800A27E8 / D_800A27EC (bit-exact copies: the NM link drops this file's .late_rodata) */
static const f32 sRibbonMinLen2A[1] = { 0.0001f };  /* 0x38D1B717 */
static const f32 sRibbonMinLen2B[1] = { 0.0001f };  /* 0x38D1B717 */

#define RIBBON_VTX(vp, px, py, pz, s) \
    do { \
        (vp)->v.ob[0] = (s32) (px); \
        (vp)->v.ob[1] = (s32) (py); \
        (vp)->v.ob[2] = (s32) (pz); \
        (vp)->v.tc[0] = (s); \
        (vp)->v.tc[1] = 0; \
        (vp)++; \
    } while (0)

// ribbon_draw: draws the object's point chain (bolt_arc_points_get: obj +0x48 + 2 points) as a camera-facing ribbon of
// half width obj +0x50: each point gets 3 vertices (p + n, p, p - n with s = 0 / 0x200 / 0x400, n = the side normal of
// the segment and the camera of view id, camera_get_pos), each segment one 6-vertex load and 4 triangles. Vertices
// from vtx_slot_buffer_get (obj +0x74 pool, obj +0x84 count; nothing drawn without). Texture D_80091120 (combine 3), prim
// colour obj +0x58..+0x5B, geometry 0x200005 / 0x1F0600, combine 0x44, render mode 0x80000 | 0x2CA0 | D_800D30BC
// with the second D_800A4EA8 pair. Returns the display list end.
/* was func_15106D38 */
s32 bolt_arc_ribbon_draw(s32 gfx, u8 *obj, s16 id) {
    Vtx *vtx;
    f32 *cam;
    f32 *pts;
    f32 *cur;
    f32 prev[3];
    s8 flag;
    f32 dx, dy, dz;
    f32 ex, ey, ez;
    f32 cx, cy, cz;
    f32 nx, ny, nz;
    f32 len2;
    f32 k;
    s32 i;

    vtx_slot_buffer_get((s32 *) (obj + 0x74), id, *(s32 *) (obj + 0x84), &vtx, NULL);
    if (vtx == NULL) {
        return gfx;
    }
    cam = camera_get_pos(id);
    flag = 1;
    pts = (f32 *) bolt_arc_points_get((struct_eu_133A70 *) obj);
    gfx = gfx_load_texture_cached(gfx, D_80091120, 0, 0, 0, 0, 0x2C, 0, 0, &flag, 3);
    gfx = gfx_env_color_cached(gfx, obj[0x58], obj[0x59], obj[0x5A], obj[0x5B], &flag);
    gfx = gfx_geometry_mode_cached(gfx, 0x200005, 0x1F0600);
    gfx = gfx_set_combine_mode(gfx, 0x44, &flag);
    gfx = gfx_other_mode_cached(gfx, D_800D30BC | 0x80000 | 0x2CA0, D_800A4EA8[3] | D_800A4EA8[2], &flag);

    /* first point: side normal of the first segment */
    dx = pts[3] - pts[0];
    dy = pts[4] - pts[1];
    dz = pts[5] - pts[2];
    ex = pts[0] - cam[0];
    ey = pts[1] - cam[1];
    ez = pts[2] - cam[2];
    cx = dy * ez - ey * dz;
    cy = dz * ex - ez * dx;
    cz = dx * ey - ex * dy;
    len2 = cx * cx + cy * cy + cz * cz;
    if (sRibbonMinLen2A[0] < len2) {
        k = *(f32 *) (obj + 0x50) / sqrtf(len2);
        nx = cx * k;
        ny = cy * k;
        nz = cz * k;
    } else {
        nx = ny = nz = 0.0f;
    }
    RIBBON_VTX(vtx, pts[0] + nx, pts[1] + ny, pts[2] + nz, 0);
    RIBBON_VTX(vtx, pts[0], pts[1], pts[2], 0x200);
    RIBBON_VTX(vtx, pts[0] - nx, pts[1] - ny, pts[2] - nz, 0x400);
    prev[0] = pts[0];
    prev[1] = pts[1];
    prev[2] = pts[2];

    /* one segment per further point (the segment direction is reversed: cur -> prev) */
    for (i = 1; i < *(s32 *) (obj + 0x48) + 2; i++) {
        cur = &pts[i * 3];
        dx = prev[0] - cur[0];
        dy = prev[1] - cur[1];
        dz = prev[2] - cur[2];
        ex = cur[0] - cam[0];
        ey = cur[1] - cam[1];
        ez = cur[2] - cam[2];
        cx = dy * ez - ey * dz;
        cy = dz * ex - ez * dx;
        cz = dx * ey - ex * dy;
        len2 = cx * cx + cy * cy + cz * cz;
        if (sRibbonMinLen2B[0] < len2) {
            k = *(f32 *) (obj + 0x50) / sqrtf(len2);
            nx = cx * k;
            ny = cy * k;
            nz = cz * k;
        } else {
            nx = ny = nz = 0.0f;
        }
        RIBBON_VTX(vtx, cur[0] - nx, cur[1] - ny, cur[2] - nz, 0);
        RIBBON_VTX(vtx, cur[0], cur[1], cur[2], 0x200);
        RIBBON_VTX(vtx, cur[0] + nx, cur[1] + ny, cur[2] + nz, 0x400);
        ((s32 *) gfx)[0] = 0x0100600C; /* gSPVertex(vtx - 6, 6, 0) */
        ((s32 *) gfx)[1] = (s32) (vtx - 6);
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05000206; /* gSP1Triangle(0, 1, 3) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05020806; /* gSP1Triangle(1, 4, 3) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        ((s32 *) gfx)[0] = 0x0502040A; /* gSP1Triangle(1, 2, 5) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        ((s32 *) gfx)[0] = 0x05020A08; /* gSP1Triangle(1, 5, 4) */
        ((s32 *) gfx)[1] = 0;
        gfx += 8;
        prev[0] = cur[0];
        prev[1] = cur[1];
        prev[2] = cur[2];
    }
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/bolt_arc_ribbon_draw.s")
#endif

extern void (*D_80088FB8[])(u8 *);
/* was func_151073F8 */
void bolt_arc_free(u8 *arg0)
{
  void (*fn)(u8 *) = D_80088FB8[arg0[0x5C]];
  struct102 *a;
  struct102 *b;
  if (fn != NULL) {
    fn(arg0);
  }
  a = *(struct102 **)(arg0 + 0x6C);
  if (a != NULL) {
    node_destroy(a);
  }
  b = *(struct102 **)(arg0 + 0x70);
  if (b != NULL) {
    node_destroy(b);
  }
  vtx_slot_buffers_free(arg0 + 0x74);
}

/* was func_15107478 */
void bolt_arc_retire(struct102 *arg0) {
    bolt_arc_free(arg0);
    node_retire(arg0);
}

/* was func_151074A4 */
void bolt_arc_delete(struct102 * arg0) {
    bolt_arc_free(arg0);
    node_unlink_free(arg0);
}

/* was func_151074D0 */
void bolt_arc_handle_event(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_80088FC8[arg0[0x5C]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

#ifdef NON_MATCHING
typedef struct {
    s32 count;  // 0x00 points
    s32 u4;     // 0x04
    s32 u8;     // 0x08
    f32 *pts;   // 0x0C (set after the copy)
    f32 params[12]; // 0x10
    u8 kind;    // 0x40
} BoltSpec;     // copied to rec + 0x28
void bolt_points_subdivide(u8 *rec, s16 lo, s16 hi, f32 jitter);
void *memcpy(void *, const void *, unsigned int);

// bolt_spawn: spawns a bolt record (func_15149130 type 0x3E, 0x48-byte header + (2^depth + 1) points) whose block at
// +0x28 gets the point count, the 12 `params` words and `kind`; the point list (+0x28 + 0x48) runs from `start` to
// `end` and bolt_points_subdivide fills the inner points with midpoint displacement (`jitter`). Returns the record or 0.
/* was func_15107518 */
s32 bolt_spawn(f32 *start, f32 *end, s32 depth, f32 *params, f32 jitter, u8 kind, u8 arg6, s32 arg7) {
    BoltSpec spec;
    u8 *rec;
    f32 *pts;
    s32 i;

    spec.count = (1 << depth) + 1;
    spec.u8 = 0;
    spec.u4 = 0;
    for (i = 0; i < 12; i++) {
        spec.params[i] = params[i];
    }
    spec.kind = kind;
    // arg 6 is the record size (functions.h types it struct37 *)
    rec = (u8 *) func_15149130(0, -1, 0x3E, -1, 0, 0x30, (struct37 *) (spec.count * 12 + 0x48), arg6, arg7);
    if (rec != NULL) {
        memcpy(rec + 0x28, &spec, sizeof(BoltSpec));
        pts = (f32 *) (rec + 0x28 + 0x48);
        *(f32 **) (rec + 0x28 + 0xC) = pts;
        pts[0] = start[0];
        pts[1] = start[1];
        pts[2] = start[2];
        pts = *(f32 **) (rec + 0x28 + 0xC) + (spec.count - 1) * 3;
        pts[0] = end[0];
        pts[1] = end[1];
        pts[2] = end[2];
        bolt_points_subdivide(rec, 0, spec.count - 1, jitter);
    }
    return (s32) rec;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/bolt_spawn.s")
#endif

#ifdef NON_MATCHING
f32 random_float(void);

// bolt_subdivide: fills the points between `lo` and `hi` of a bolt record's point list (rec + 0x28 + 0xC, 12-byte
// x / y / z) by midpoint displacement: each midpoint lies on the segment at a random fraction 0.5 +- `jitter`
// (random_float), then the left half recurses and the right half loops.
/* was func_15107678 */
void bolt_points_subdivide(u8 *rec, s16 lo, s16 hi, f32 jitter) {
    f32 *a;
    f32 *b;
    f32 *m;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 t;
    s16 mid;

    while (hi - lo >= 2) {
        mid = lo + ((hi - lo) >> 1);
        a = *(f32 **) (rec + 0x34) + lo * 3;
        b = *(f32 **) (rec + 0x34) + hi * 3;
        dx = b[0] - a[0];
        dy = b[1] - a[1];
        dz = b[2] - a[2];
        t = random_float() * (jitter + jitter) + (0.5f - jitter);
        m = *(f32 **) (rec + 0x34) + mid * 3;
        m[0] = a[0] + dx * t;
        m = *(f32 **) (rec + 0x34) + mid * 3;
        m[1] = a[1] + dy * t;
        m = *(f32 **) (rec + 0x34) + mid * 3;
        m[2] = a[2] + dz * t;
        bolt_points_subdivide(rec, lo, mid, jitter);
        lo = mid;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/bolt_points_subdivide.s")
#endif

#ifdef NON_MATCHING
typedef struct {
    u8 *rec;      // 0x00 copied into the arc object (its +0x60 data) after the spawn
    s16 life;     // 0x04 <- passed to bolt_arc_spawn from here
    u8 u06;       // 0x06
    f32 a[3];     // 0x08 segment start
    f32 c1[3];    // 0x14 start + random offset
    f32 c2[3];    // 0x20 end + random offset
    f32 b[3];     // 0x2C segment end
    s8 u38;       // 0x38
    s32 u3C;      // 0x3C
    f32 u40;      // 0x40
    f32 u44;      // 0x44
    s16 u48;      // 0x48
    s16 u4A;      // 0x4A
    u8 rgb[3];    // 0x4C
    u8 u4F;       // 0x4F
    u8 u50;       // 0x50
} BoltArcSpawn;
u8 *bolt_arc_spawn(s16 *spec, s32 extra, u8 layer, s32 arg3);
s32 random_int(void);
f32 random_float(void);
void vec3_from_angles_byte(s16, s16, f32, u8 *);
void *memcpy(void *, const void *, unsigned int);

// bolt_record_update: record handler of the bolt spawned by bolt_spawn (type 0x3E). While no arc is alive
// (+0x30 == 0) it spawns the next segment arc (bolt_arc_spawn kind 4) between points +0x2C and +0x2D of the point list,
// with two control points pushed sideways by vec3_from_angles_byte (random angle, random pitch around -0x40) and life,
// colour, width and the other values from the bolt parameters (+0x38..); the arc gets the record pointer. When the
// last segment is done it marks the record finished (+0xE = -1, +0xD bit 0).
/* was func_1510783C */
void bolt_record_update(u8 *rec) {
    u8 *spec = rec + 0x28;  // BoltSpec: +0 count, +4 segment, +8 live arc, +0xC points, +0x10 params
    u8 *p = spec + 0x10;
    BoltArcSpawn s;
    f32 off[3];
    f32 *pt;
    u32 r1;
    u32 r2;
    s16 spread;
    u8 *arc;

    if (*(s32 *) (rec + 0x30) != 0) {
        return;
    }
    if (*(s32 *) (spec + 4) >= *(s32 *) spec - 1) {
        *(s16 *) (rec + 0xE) = -1;
        rec[0xD] |= 1;
        return;
    }
    s.rec = rec;
    s.u06 = 1;
    s.u38 = -1;
    s.u44 = random_float() * *(f32 *) (p + 4) + *(f32 *) p;
    s.u40 = *(f32 *) (p + 8);
    s.u48 = *(s16 *) (p + 0x16);
    s.u4A = *(s16 *) (p + 0x18);
    pt = *(f32 **) (spec + 0xC) + *(s32 *) (spec + 4) * 3;
    s.a[0] = pt[0];
    s.a[1] = pt[1];
    s.a[2] = pt[2];
    pt = *(f32 **) (spec + 0xC) + *(s32 *) (spec + 4) * 3;
    s.b[0] = pt[3];
    s.b[1] = pt[4];
    s.b[2] = pt[5];

    r1 = random_int();
    r2 = random_int();
    spread = *(s16 *) (p + 0x14);
    vec3_from_angles_byte((u8) r1, r2 % (u32) (spread + 1) - (spread >> 1) - 0x40,
                  random_float() * *(f32 *) (p + 0x10) + *(f32 *) (p + 0xC), (u8 *) off);
    s.c1[0] = s.a[0] + off[0];
    s.c1[1] = s.a[1] + off[1];
    s.c1[2] = s.a[2] + off[2];

    r1 = random_int();
    r2 = random_int();
    spread = *(s16 *) (p + 0x14);
    vec3_from_angles_byte((u8) r1, r2 % (u32) (spread + 1) - (spread >> 1) - 0x40,
                  random_float() * *(f32 *) (p + 0x10) + *(f32 *) (p + 0xC), (u8 *) off);
    s.c2[0] = s.b[0] + off[0];
    s.c2[1] = s.b[1] + off[1];
    s.c2[2] = s.b[2] + off[2];

    s.rgb[0] = p[0x28];
    s.rgb[1] = p[0x29];
    s.rgb[2] = p[0x2A];
    s.life = (u32) random_int() % (u32) (*(s16 *) (p + 0x1C) + 1) + *(s16 *) (p + 0x1A);
    s.u4F = (u32) random_int() % (u32) (p[0x2C] + 1) + p[0x2B];
    s.u50 = 1;
    s.u3C = (u32) random_int() % (u32) (*(s32 *) (p + 0x24) + 1) + *(s32 *) (p + 0x20);
    arc = (u8 *) bolt_arc_spawn(&s.life, 4, rec[0xC], rec[1]);
    *(u8 **) (spec + 8) = arc;
    if (arc != NULL) {
        memcpy(*(u8 **) (arc + 0x60), &s.rec, 4);
    }
    *(s32 *) (spec + 4) += 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/bolt_record_update.s")
#endif

/* was func_15107B84 */
void bolt_arc_unlink_from_bolt(s32 ***arg0) {
    s32 **temp_v0 = arg0[0x18];
    s32 *temp_v1 = *temp_v0;

    temp_v1 += 0x28 / 4;
    temp_v1[2] = 0;
}

/* was func_15107B9C */
void bolt_record_free(u8 *arg0) { u8 *p = arg0; if (*(s32 *)(p + 0x30) != 0) { node_destroy(*(struct102 **)(p + 0x30)); } }

/* was func_15107BCC */
void bolt_record_retire(struct260 * arg0) {
    bolt_record_free(arg0);
    func_1514933C(arg0);
}

/* was func_15107BF8 */
void bolt_record_delete(struct260 * arg0) {
    bolt_record_free(arg0);
    func_15149368(arg0);
}

extern void (*D_80088FD8[])(u8 *, s32, u8);
/* was func_15107C24 */
void bolt_record_handle_event(u8 *arg0, s32 arg1, u8 arg2)
{
  int new_var;
  void (**tab)(u8 *, s32, u8) = D_80088FD8;
  new_var = 0x68; // fakematch: constant index in a variable stops the CSE of the table index load
  if (tab[arg0[new_var]] != 0)
  {
    tab[arg0[new_var]](arg0, arg1, arg2);
  }
}

#ifdef NON_MATCHING
s32 ray_cast_world(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);

/* The 0x50-byte arc spec bolt_arc_spawn copies into the arc object (+0x10). */
typedef struct {
    /* 0x00 */ s16 life;        /* 300 when the caller passes -1 */
    /* 0x02 */ u8 u02;          /* 0 when the caller passes -1, else 1 */
    /* 0x04 */ f32 start[3];
    /* 0x10 */ f32 c1[3];       /* control points (arc_control_points_thirds: 1/3 and 2/3 of the way) */
    /* 0x1C */ f32 c2[3];
    /* 0x28 */ f32 end[3];
    /* 0x34 */ u8 u34;
    /* 0x38 */ s32 segments;
    /* 0x3C */ f32 jitter;
    /* 0x40 */ f32 width;
    /* 0x44 */ s16 lifeBase;
    /* 0x46 */ s16 lifeRange;
    /* 0x48 */ u8 rgba[4];
    /* 0x4C */ u8 u4C;          /* 2 */
} ArcSpec;

/* The 0xC-byte record the arc's data area (+0x60) gets: the object it hangs on and the attachment angles. */
typedef struct {
    u8 *obj;
    u8 id;                      /* obj[0x3B] */
    s16 angle0;
    s16 angle1;
} ArcLink;

// object_arc_to_surface_spawn: casts a ray (ray_cast_world) from the object's attachment point at angles
// (angle0, angle1) (obj_attach_point_at_angles) outwards from the object's centre and, when it hits something, spawns a lightning arc
// (bolt_arc_spawn, 0xC extra bytes for an ArcLink back to the object) from the point to the hit, with control points at
// 1/3 and 2/3 (arc_control_points_thirds). life -1 = 300 and spec +0x02 = 0. Returns the arc, 0 when the object has no +0x1D4, the
// ray hits nothing or no arc could be spawned.
/* was func_15107C80 */
s32 object_arc_to_surface_spawn(u8 *obj, s16 angle0, s16 angle1, s16 life, s32 segments, f32 jitter, f32 width, s32 lifeBase,
                  s32 lifeRange, s8 *rgba, s32 layer, s32 arg11) {
    u8 hit[0x64];
    f32 origin[3];
    ArcSpec spec;
    ArcLink link;
    u8 *arc;

    if (*(s32 *)(obj + 0x1D4) == 0) {
        return 0;
    }
    link.obj = obj;
    link.id = obj[0x3B];
    link.angle0 = angle0;
    link.angle1 = angle1;
    spec.life = (life == -1) ? 300 : life;
    spec.u02 = (life == -1) ? 0 : 1;
    spec.u34 = 0;
    spec.segments = segments;
    spec.jitter = jitter;
    spec.width = width;
    spec.lifeBase = lifeBase;
    spec.lifeRange = lifeRange;
    spec.rgba[0] = rgba[0];
    spec.rgba[1] = rgba[1];
    spec.rgba[2] = rgba[2];
    spec.rgba[3] = rgba[3];
    spec.u4C = 2;
    obj_attach_point_at_angles(obj, angle0, angle1, (u8 *)spec.start, (u8 *)origin);
    ray_cast_world((struct127 *)obj, spec.start[0], spec.start[1], spec.start[2], spec.start[0] - origin[0],
                  spec.start[1] - origin[1], spec.start[2] - origin[2], hit, 0.0f, 0, 1, 1, -1, 0, 0);
    if (hit[0x59] == 0) {
        return 0;
    }
    spec.end[0] = *(f32 *)(hit + 0x08);
    spec.end[1] = *(f32 *)(hit + 0x0C);
    spec.end[2] = *(f32 *)(hit + 0x10);
    arc_control_points_thirds(spec.start, spec.end, spec.c1, spec.c2);
    arc = bolt_arc_spawn(&spec.life, 0xC, layer, arg11);
    if (arc != NULL) {
        memcpy(*(u8 **)(arc + 0x60), &link, 0xC);
    }
    return (s32)arc;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/object_arc_to_surface_spawn.s")
#endif

/* was func_15107E64 */
void obj_arc_handle_event(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2 = *(s32 *)(arg0 + 0x60);

    node_handle_link_message(arg1, arg2, temp_a2, temp_a2 + 4, (s32)arg0);
}

#ifdef NON_MATCHING
/* was func_15107EA4 */
s32 obj_arc_follow_update(u8 *arg0, s8 *arg1) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        u8 * u38;
    } sp;
    u8 *sp28;
    u8 *temp_a3;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x60));
    temp_t6 = (*(u8 **)((u8 *)temp_v0 + 0));
    sp.u38 = temp_t6;
    if (((*(s32 *)((u8 *)temp_t6 + 0)) == 0) || (temp_a3 = arg0 + 0x14, ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_t6 + 0x3B))))) {
        return 0;
    }
    *arg1 = 0;
    (*(f32 *)((u8 *)(&sp.u2C) + 0)) = (*(f32 *)((u8 *)temp_a3 + 0));
    (*(s32 *)((u8 *)(&sp.u2C) + 4)) = (s32) (*(s32 *)((u8 *)temp_a3 + 4));
    (*(s32 *)((u8 *)(&sp.u2C) + 8)) = (s32) (*(s32 *)((u8 *)temp_a3 + 8));
    sp28 = temp_a3;
    obj_attach_point_at_angles(sp.u38, (*(s16 *)((u8 *)temp_v0 + 6)), (*(s16 *)((u8 *)temp_v0 + 8)), temp_a3, NULL);
    if ((sp.u2C != (*(f32 *)((u8 *)arg0 + 0x14))) || (sp.u30 != (*(f32 *)((u8 *)arg0 + 0x18))) || (sp.u34 != (*(f32 *)((u8 *)arg0 + 0x1C)))) {
        *arg1 = 1;
        arc_control_points_thirds((f32 *) sp28, arg0 + 0x38, arg0 + 0x20, arg0 + 0x2C);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/obj_arc_follow_update.s")
#endif
#ifdef NON_MATCHING
void vec3_from_angles_byte(s16, s16, f32, u8 *); /* P95: f32 (float bits were passed as an int) */
#else
s32 vec3_from_angles_byte(s16, s16, s32, u8 *);
#endif
s32 obj_get_fx_point_b(u8 *, f32 *, s32 *, s32 *);

/* was func_15107FA0 */
void obj_attach_point_at_angles(u8 *arg0, s16 arg1, s16 arg2, u8 *arg3, u8 *arg4) {
    f32 sp2C[3];
    s32 sp28;
    s32 sp24;

    obj_get_fx_point_b(arg0, sp2C, &sp28, &sp24);
#ifdef NON_MATCHING
    vec3_from_angles_byte(arg1, arg2, *(f32 *)&sp28, arg3); /* P95: f32 (float bits were passed as an int) */
#else
    vec3_from_angles_byte(arg1, arg2, sp28, arg3);
#endif
    *(f32 *)(arg3 + 4) *= *(f32 *)(arg0 + 0xF0);
    *(f32 *)(arg3 + 0) += sp2C[0];
    *(f32 *)(arg3 + 4) += sp2C[1];
    *(f32 *)(arg3 + 8) += sp2C[2];
    if (arg4 != NULL) {
        *(vertex *)arg4 = *(vertex *)sp2C;
    }
}

/* was func_15108060 */
void arc_control_points_thirds(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 dx = arg1[0] - arg0[0];
    f32 dy = arg1[1] - arg0[1];
    f32 dz = arg1[2] - arg0[2];

    arg2[0] = arg0[0] + dx * 0.333f;
    arg2[1] = arg0[1] + dy * 0.333f;
    arg2[2] = arg0[2] + dz * 0.333f;
    arg3[0] = arg0[0] + dx * 0.6667f;
    arg3[1] = arg0[1] + dy * 0.6667f;
    arg3[2] = arg0[2] + dz * 0.6667f;
}

/* was func_151080F8 */
void obj_angle_point_effect(u8 *arg0, s16 arg1, s16 arg2, u8 arg3, s32 arg4) {
    f32 sp2C[3];
    f32 sp20[3];
    s32 sp1C;
    s32 sp18;

    if (*(s32 *)(arg0 + 0x1D4) != 0) {
        obj_get_fx_point_b(arg0, sp20, &sp1C, &sp18);
#ifdef NON_MATCHING
        vec3_from_angles_byte(arg1, arg2, *(f32 *)&sp1C, sp2C); /* P95: f32 (float bits were passed as an int) */
#else
        vec3_from_angles_byte(arg1, arg2, sp1C, sp2C);
#endif
        sp2C[1] *= *(f32 *)(arg0 + 0xF0);
        sp2C[0] += sp20[0];
        sp2C[1] += sp20[1];
        sp2C[2] += sp20[2];
        fire_embers_spawn(sp2C, arg3, arg4);
    }
}

#ifdef NON_MATCHING
/* The 0x18-byte record the arc's data area (+0x60) gets: the object, a point and a kind byte. */
typedef struct {
    u8 *obj;
    u8 id;                      /* obj[0x3B] */
    f32 pos[3];                 /* 0x08 */
    u8 kind;                    /* 0x14 */
} ArcPointLink;

// object_arc_from_point_spawn: like object_arc_to_surface_spawn but from the object's point `pos` / `kind` (obj_bone_point_transform) in the
// direction of angles (angle0, angle1) (vec3_from_angles_byte, unit length): the ray (ray_cast_world, length 300) ends the
// arc at the hit, or 300 units out when it hits nothing. Spec +0x34 = 1, +0x4C = 3, 0x18 extra bytes for an
// ArcPointLink. Returns the arc, 0 when the object has no +0x1D4 or no arc could be spawned.
/* was func_1510819C */
s32 object_arc_from_point_spawn(u8 *obj, u8 kind, f32 *pos, s16 angle0, s16 angle1, s16 life, s32 segments, f32 jitter,
                  f32 width, s32 lifeBase, s32 lifeRange, s8 *rgba, s32 layer, s32 arg13) {
    u8 hit[0x64];
    f32 dir[3];
    ArcSpec spec;
    ArcPointLink link;
    u8 *arc;

    if (*(s32 *)(obj + 0x1D4) == 0) {
        return 0;
    }
    link.obj = obj;
    link.id = obj[0x3B];
    link.pos[0] = pos[0];
    link.pos[1] = pos[1];
    link.pos[2] = pos[2];
    link.kind = kind;
    spec.life = (life == -1) ? 300 : life;
    spec.u02 = (life == -1) ? 0 : 1;
    spec.u34 = 1;
    spec.segments = segments;
    spec.jitter = jitter;
    spec.width = width;
    spec.lifeBase = lifeBase;
    spec.lifeRange = lifeRange;
    spec.rgba[0] = rgba[0];
    spec.rgba[1] = rgba[1];
    spec.rgba[2] = rgba[2];
    spec.rgba[3] = rgba[3];
    spec.u4C = 3;
    obj_bone_point_transform(obj, kind, pos, spec.start);
    vec3_from_angles_byte(angle0, angle1, 1.0f, (u8 *)dir);
    ray_cast_world((struct127 *)obj, spec.start[0], spec.start[1], spec.start[2], dir[0], dir[1], dir[2], hit,
                  300.0f, 0, 1, 1, -1, 0, 0);
    if (hit[0x59] == 0) {
        spec.end[0] = spec.start[0] + dir[0] * 300.0f;
        spec.end[1] = spec.start[1] + dir[1] * 300.0f;
        spec.end[2] = spec.start[2] + dir[2] * 300.0f;
    } else {
        spec.end[0] = *(f32 *)(hit + 0x08);
        spec.end[1] = *(f32 *)(hit + 0x0C);
        spec.end[2] = *(f32 *)(hit + 0x10);
    }
    arc_control_points_thirds(spec.start, spec.end, spec.c1, spec.c2);
    arc = bolt_arc_spawn(&spec.life, 0x18, layer, arg13);
    if (arc != NULL) {
        memcpy(*(u8 **)(arc + 0x60), &link, 0x18);
    }
    return (s32)arc;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/object_arc_from_point_spawn.s")
#endif

#ifdef NON_MATCHING
/* was func_151083C8 */
s32 obj_point_arc_follow_update(u8 *arg0, s8 *arg1) {
    struct {
        f32 u24;
        f32 u28;
        f32 u2C;
    } sp;
    f32 *sp20;
    f32 *temp_a3;
    u8 *temp_s1;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x60));
    temp_s1 = (*(u8 **)((u8 *)temp_v0 + 0));
    if (((*(s32 *)((u8 *)temp_s1 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_s1 + 0x3B)))) {
        return 0;
    }
    temp_a3 = arg0 + 0x14;
    if ((*(s32 *)((u8 *)temp_s1 + 0x1D4)) == 0) {
        return 0;
    }
    *arg1 = 0;
    (*(f32 *)((u8 *)(&sp.u24) + 0)) = (*(f32 *)((u8 *)temp_a3 + 0));
    (*(s32 *)((u8 *)(&sp.u24) + 4)) = (s32) (*(s32 *)((u8 *)temp_a3 + 4));
    (*(s32 *)((u8 *)(&sp.u24) + 8)) = (s32) (*(s32 *)((u8 *)temp_a3 + 8));
    sp20 = temp_a3;
    obj_bone_point_transform(temp_s1, (*(u8 *)((u8 *)temp_v0 + 0x14)), temp_v0 + 8, temp_a3);
    if ((sp.u24 != (*(f32 *)((u8 *)arg0 + 0x14))) || (sp.u28 != (*(f32 *)((u8 *)arg0 + 0x18))) || (sp.u2C != (*(f32 *)((u8 *)arg0 + 0x1C)))) {
        *arg1 = 1;
        arc_control_points_thirds(sp20, arg0 + 0x38, arg0 + 0x20, arg0 + 0x2C);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/obj_point_arc_follow_update.s")
#endif
/* was func_151084D4 */
void obj_bone_point_transform(u8 *arg0, u8 arg1, void *arg2, void *arg3) {
    mtx_transform_point_or_origin(arg2, arg3, *(u8 **)(arg0 + 0x1D4) + (arg1 << 6));
}

/* was func_15108518 */
void obj_point_arc_handle_event(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2 = *(s32 *)(arg0 + 0x60);

    node_handle_link_message(arg1, arg2, temp_a2, temp_a2 + 4, (s32)arg0);
}
