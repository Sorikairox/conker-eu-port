#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 model_joint_mtx_count(s32);

/* was func_151846C0 */
struct124 *shadow_obj_box_extents(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 sp3C;
    struct127 *sp1C;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f12;
    f32 var_f2;
    s32 temp_t2;
    s32 var_a0;
    s32 var_v0;
    struct127 *temp_t0;

    temp_t0 = &D_800CC2D0[arg0];
    sp3C = (s32) temp_t0->id;
    *arg3 = 0.0f;
    *arg2 = 0.0f;
    *arg1 = 0.0f;
    if ((temp_t0->unk1D4 == NULL) || (D_800C42B0 != 0)) {
        return NULL;
    }
    sp1C = temp_t0;
    var_v0 = model_joint_mtx_count(sp3C);
    if (var_v0 > 0) {
        var_a0 = 0;
        temp_t2 = var_v0 << 6;
        do {
            var_v0 = (s32) &temp_t0->unk1D4->pad0[var_a0];
            var_f0 = (*(f32 *)((u8 *)var_v0 + 0x30)) - temp_t0->x_position;
            var_a0 += 0x40;
            var_f2 = (*(f32 *)((u8 *)var_v0 + 0x34)) - temp_t0->y_position;
            var_f12 = (*(f32 *)((u8 *)var_v0 + 0x38)) - temp_t0->z_position;
            if (var_f0 < 0.0f) {
                var_f0 = -var_f0;
            }
            if (*arg1 < var_f0) {
                *arg1 = var_f0;
            }
            if (var_f2 < 0.0f) {
                var_f2 = -var_f2;
            }
            if (*arg2 < var_f2) {
                *arg2 = var_f2;
            }
            if (var_f12 < 0.0f) {
                var_f12 = -var_f12;
            }
            if (*arg3 < var_f12) {
                *arg3 = var_f12;
            }
        } while (var_a0 < temp_t2);
    }
    if ((*arg1 == 0.0f) || (*arg2 == 0.0f) || (*arg3 == 0.0f)) {
        temp_f2 = temp_t0->xz_scale * (f32) D_800D1C90[temp_t0->id]->unk1A;
        *arg3 = temp_f2;
        *arg1 = temp_f2;
        var_v0 = (s32) D_800D1C90[temp_t0->id];
        *arg2 = temp_t0->y_scale * (f32) ((*(s16 *)((u8 *)var_v0 + 0x1E)) + (*(s16 *)((u8 *)var_v0 + 0x1C)));
    }
    return (struct124 *) var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_obj_box_extents.s")
#endif
#ifdef NON_MATCHING
/* P122 */
/* Shadow light list (D_800DCD78): the lights an object's shadow can be cast from. */
typedef struct ShadowLight {
    struct ShadowLight *next; /* 0x00 */
    u8 off;                   /* 0x04: != 0: ignored */
    u8 pad5[4];
    u8 hidden;                /* 0x09: != 0: ignored */
    u8 padA[4];
    s16 x;                    /* 0x0E: position */
    s16 y;                    /* 0x10 */
    s16 z;                    /* 0x12 */
} ShadowLight;

extern s32 D_800DE464;        /* != 0: no point lights (only the default direction) */
extern f32 D_800DE440[3];     /* default light direction (reset to (100, 600, -200) when its y <= 0) */
extern f32 D_800DE46C;        /* world scale of the shadow distances */
extern s32 D_800DE468;        /* shadow detail level: >= 2 snaps the light positions */
extern f32 D_800DE3E0[][3];   /* per shadow slot: smoothed light position */
extern f32 D_800DFB28;        /* distance object -> light of the last projection */
extern s8 D_800DE470;         /* != 0: the minimum light height grows with the horizontal distance */
extern f32 D_800DE458;        /* far clip depth (before the scale) */
extern s8 D_800DF511;         /* != 0: flat shadows: y size / 4, half the far depth */
extern s32 D_800DF528;        /* [slot] f32 [4][4]: light view matrix */
extern s8 D_8008D798[8][3];   /* the 8 corners (+-1, +-1, +-1) of the object's box */
extern f32 D_800D3AA0[2];     /* projection x / y scale (>= 1) */
extern u16 D_800DF500[];      /* [slot]: perspNorm of the projection */
extern u8 D_800DF728[];       /* [slot][frame] Mtx (0x40 bytes): fixed-point projection */
extern u8 D_800DE478[];       /* shadow texture buffer (D_800DF4B8 = its 64-byte aligned start) */
extern s32 D_800DF4B8;
extern f32 D_800DE45C;        /* shadow alpha */
s32 approx_dist3_int(s32, s32, s32);
void mtxf_look_at_f(f32 mf[4][4], f32, f32, f32, f32, f32, f32, f32, f32, f32);
void mtxf_mul(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
void vec3_diff(struct17 *, struct17 *, struct17 *);
f32 vec3f_magnitude(f32 *);
void mtxf_transform_point(f32 mf[4][4], f32, f32, f32, f32 *, f32 *, f32 *);
void mtxf_scale(f32 mtx[4][4], s32, s32, s32);
f32 func_150484A0(f32, f32);

/* shadow_light_projection: sets up shadow slot `slot` of object record `obj` (box half sizes sx, sy, sz).
 * Light: unless D_800DE464, the nearest enabled light of the list D_800DCD78 whose integer distance
 * (approx_dist3_int) is above prev_dist and below 5000; with none, 0 is returned when prev_dist != 0, else the default
 * direction D_800DE440 (scaled by D_800DE46C) from the object is used with distance 1. The slot's light position
 * D_800DE3E0[slot] snaps to it (detail >= 2 or *D_800DBFF4) or moves 0.3 of the way. The light is pushed out to at
 * least 200 units and to a minimum height (10, or 0.57735 * the horizontal distance when D_800DE470); beyond
 * 5000 * scale nothing is cast. A look-at matrix from the light to the object (D_800DF528[slot]) projects the 8 box
 * corners; their largest |x / z|, |y / z| (>= 0.01, else nothing) give the projection scale D_800D3AA0 and the
 * nearest corner depth (< -1, else nothing) the near clip D_800D3AAC (far clip D_800D3AA8 = -(D_800DE458 * scale)
 * - distance, half that and y size / 4 when D_800DF511). A perspective (halved in scale until every element of
 * view * persp is below 32767) times a (0.5, 0.5, 1) scale goes to the Mtx D_800DF728[slot][D_800BE9C0]. The shadow
 * alpha D_800DE45C = 255 - (+0x1DD >> 1), at most 185, fades when +0xCC is below -10 (0 returned at <= 5).
 * Returns the light distance (1 for the default light), or 0 when no shadow is cast; D_800D3AA8 / D_800D3AAC are
 * cleared then (except for the early returns before the light is moved). */
/* was func_151848D8 */
f32 shadow_light_projection(s32 obj, s32 slot, f32 sx, f32 sy, f32 sz, f32 prev_dist) {
    struct127 *rec;
    ShadowLight *light;
    f32 pos[3];
    f32 target[3];
    f32 dir[3];
    f32 *lit;
    f32 (*view)[4];
    f32 mf[4][4];
    f32 scale_mf[4][4];
    f32 best;
    f32 lx, ly, lz;
    f32 d;
    f32 k;
    f32 min_h;
    f32 px, py, pz;
    f32 max_x, max_y, max_z;
    f32 persp_scale;
    f32 fovy;
    f32 m;
    f32 cc;
    s32 found;
    s32 done;
    s32 i;

    rec = &D_800CC2D0[obj];
    done = 0;
    best = 5000.0f;
    pos[0] = rec->x_position;
    persp_scale = 2.0f;
    pos[1] = rec->y_position;
    found = 0;
    pos[2] = rec->z_position;

    if (D_800DE464 == 0) {
        for (light = (ShadowLight *) D_800DCD78; light != NULL; light = light->next) {
            if (light->off != 0 || light->hidden != 0) {
                continue;
            }
            lx = light->x;
            ly = light->y;
            lz = light->z;
            d = approx_dist3_int((s32) (lx - pos[0]), (s32) (ly - pos[1]), (s32) (lz - pos[2]));
            if (d < best && prev_dist < d) {
                best = d;
                found++;
                target[0] = lx;
                target[1] = ly;
                target[2] = lz;
            }
        }
    }
    if (found == 0) {
        if (prev_dist != 0.0f) {
            return 0.0f;
        }
        if (D_800DE440[1] <= 0.0f) {
            D_800DE440[1] = 600.0f;
            D_800DE440[0] = 100.0f;
            D_800DE440[2] = -200.0f;
        }
        best = 1.0f;
        target[0] = D_800DE440[0] * D_800DE46C + pos[0];
        target[1] = D_800DE440[1] * D_800DE46C + pos[1];
        target[2] = D_800DE440[2] * D_800DE46C + pos[2];
    }

    lit = D_800DE3E0[slot];
    if (*(s32 *) D_800DBFF4 != 0 || D_800DE468 >= 2) {
        lit[0] = target[0];
        lit[1] = target[1];
        lit[2] = target[2];
    } else {
        lit[0] += (target[0] - lit[0]) * 0.3f;
        lit[1] += (target[1] - lit[1]) * 0.3f;
        lit[2] += (target[2] - lit[2]) * 0.3f;
    }

    vec3_diff((struct17 *) pos, (struct17 *) lit, (struct17 *) dir);
    D_800DFB28 = vec3f_magnitude(dir);
    if (D_800DFB28 < 200.0f) {
        /* at least 200 units away along the same direction */
        k = 200.0f / D_800DFB28;
        D_800DFB28 = 200.0f;
        for (i = 0; i < 3; i++) {
            d = dir[i] * k;
            lit[i] += d - dir[i];
            dir[i] = d;
        }
    }
    if (D_800DE470 != 0) {
        min_h = sqrtf(dir[0] * dir[0] + dir[2] * dir[2]) * 0.57735f;
        if (min_h < 10.0f) {
            min_h = 10.0f;
        }
    } else {
        min_h = 10.0f;
    }
    if (dir[1] < min_h) {
        /* raise the light, then rescale the offset to the old distance */
        lit[1] += min_h - dir[1];
        dir[1] = min_h;
        d = approx_dist3_int((s32) dir[0], (s32) dir[1], (s32) dir[2]);
        k = D_800DFB28 / d;
        D_800DFB28 = d;
        for (i = 0; i < 3; i++) {
            lit[i] += dir[i] * k - dir[i];
        }
    }
    if (5000.0f * D_800DE46C < D_800DFB28) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0.0f;
    }
    if (D_800DF511 != 0) {
        sy *= 0.25f;
        D_800D3AA8 = -(D_800DE458 * D_800DE46C * 0.5f) - D_800DFB28;
    } else {
        D_800D3AA8 = -D_800DE458 * D_800DE46C - D_800DFB28;
    }

    view = (f32 (*)[4]) ((u8 *) &D_800DF528 + slot * 0x40);
    mtxf_look_at_f(view, lit[0], lit[1], lit[2], pos[0], pos[1], pos[2], 0.0f, 1.0f, 0.0f);
    max_y = 0.0f;
    max_x = 0.0f;
    max_z = -1000000.0f;
    for (i = 0; i < 8; i++) {
        mtxf_transform_point(view, D_8008D798[i][0] * sx + pos[0], D_8008D798[i][1] * sy + pos[1],
                      D_8008D798[i][2] * sz + pos[2], &px, &py, &pz);
        if (pz == 0.0f) {
            pz = 0.0001f;
        }
        px = px / pz;
        py = py / pz;
        if (px < 0.0f) {
            px = -px;
        }
        if (max_x < px) {
            max_x = px;
        }
        if (py < 0.0f) {
            py = -py;
        }
        if (max_y < py) {
            max_y = py;
        }
        if (max_z < pz) {
            max_z = pz;
        }
    }
    if (max_x < 0.01f || max_y < 0.01f) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0.0f;
    }
    D_800D3AA0[0] = 1.0f / max_x;
    D_800D3AA0[1] = 1.0f / max_y;
    if (D_800D3AA0[0] < 1.0f) {
        D_800D3AA0[0] = 1.0f;
    }
    if (D_800D3AA0[1] < 1.0f) {
        D_800D3AA0[1] = 1.0f;
    }
    if (!(max_z < -1.0f)) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0.0f;
    }
    D_800D3AAC = max_z;
    do {
        m = 1.0f;
        fovy = func_150484A0(1.0f, D_800D3AA0[1]);
        guPerspectiveF(mf, &D_800DF500[slot], fovy * 57.295776f, func_150484A0(1.0f, D_800D3AA0[0]) * 57.295776f,
                       -D_800D3AAC, -D_800D3AA8, persp_scale);
        mtxf_mul(view, mf, mf);
        for (i = 0; i < 16; i++) {
            d = mf[i >> 2][i & 3];
            if (d < 0.0f) {
                d = -d;
            }
            if (m < d) {
                m = d;
            }
        }
        if (m < 32767.0f) {
            done = 1;
        } else {
            persp_scale *= 0.5f;
        }
    } while (done == 0);
    mtxf_scale(scale_mf, 0x3F000000, 0x3F000000, 0x3F800000); /* f32 bits: scale (0.5, 0.5, 1) */
    mtxf_mul(mf, scale_mf, mf);
    guMtxF2L(mf, (Mtx *) (D_800DF728 + slot * 0x80 + D_800BE9C0 * 0x40));
    D_800DF4B8 = ((s32) D_800DE478 + 0x3F) & ~0x3F;

    D_800DE45C = 0xFF - (rec->unk1DD >> 1);
    if (D_800DE45C > 185.0f) {
        D_800DE45C = 185.0f;
    }
    cc = rec->unkCC;
    if (cc < -10.0f) {
        D_800DE45C += D_800DE45C * (cc + 10.0f) * 0.02f;
        if (D_800DE45C <= 5.0f) {
            return 0.0f;
        }
    }
    return best;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_light_projection.s")
#endif

#ifdef NON_MATCHING
s32 approx_dist3_int(s32, s32, s32);

/* Aim offset from player `player` to object `obj`: d = distance (approx_dist3_int of the truncated delta between the
 * object position and the player's +0x2F8 vector). Beyond 2000 units, or when the offset shadow_obj_box_extents writes to
 * (*x, *y, *z) (scaled by 1.3, D_800A7758) has a zero component, the clip heights D_800D3AA8 / D_800D3AAC are
 * cleared and 0 is returned; else d. */
/* was func_15185360 */
s32 shadow_obj_light_distance(s32 obj, s32 player, f32 *x, f32 *y, f32 *z) {
    struct127 *o = &D_800CC2D0[obj];
    struct108 *p = &D_800DBFF0[player];
    s32 d;

    d = approx_dist3_int((s32) (o->x_position - p->unk2F8), (s32) (o->y_position - p->unk2FC),
                      (s32) (o->z_position - p->unk300));
    if (d > 2000) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0;
    }
    shadow_obj_box_extents(obj, x, y, z);
    *x *= 1.3f;
    *y *= 1.3f;
    *z *= 1.3f;
    if (*x == 0.0f || *y == 0.0f || *z == 0.0f) {
        D_800D3AA8 = 0.0f;
        D_800D3AAC = D_800D3AA8;
        return 0;
    }
    return d;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_obj_light_distance.s")
#endif

#ifdef NON_MATCHING
/* P130 */
extern u16 D_800DF500[];   /* [slot]: perspNorm of the shadow projection */
extern u8 D_800DF728[];    /* [slot][frame] Mtx (0x40 bytes) */
extern s32 D_800DF4B8;     /* shadow texture (64-byte aligned) */
extern s16 D_80083336;
extern u8 D_800BE9C0;      /* frame buffer index */
extern s32 D_8008D7E8;     /* static DLs / viewport / Mtx of the shadow pass */
extern s32 D_8008D788;
extern s32 D_89810;
Gfx *render_set_color_image(Gfx *);
s32 render_set_scissor(s32, s16, s32, s32, s32, s32);
Gfx *obj_draw_model_dl(Gfx *, s32, s32, s32, s32, s32 *, s32, s32);
s32 obj_get_player_alpha(struct127 *, s32);
u8 *view_dl_begin(u8 *, s32);

/* one GBI command: two words */
#define SHADOW_GFX(g, hi, lo) ((g)->words.w0 = (hi), (g)->words.w1 = (lo), (g)++)

// shadow_render_caster: starts the display list that renders object obj (light slot) into the shadow texture
// D_800DF4B8: pipe sync, colour image = the texture (16-bit, 64 wide), the static setup DL D_8008D7E8,
// perspNorm D_800DF500[slot], viewport D_8008D788, projection D_800DF728[slot][frame] and view D_89810, then the
// object's model (obj_draw_model_dl with an all-zero colour and the object's shadow level). Shadow level 0 / 1
// (unk1C8, + 1 when unk127 == 0xFF) blurs the texture twice / once with a 64x64 TEX rectangle over itself.
// Ends with geometry mode on (D9FFFFFF / 0x200001), then render_set_color_image / render_set_scissor / view_dl_begin
// restore the frame state. Marks the object (unk123 = 1). Returns the display list end.
/* was func_15185514 */
u8 *shadow_render_caster(u8 *dl, s32 obj, s32 slot, s32 arg3) {
    struct127 *o = &D_800CC2D0[obj];
    Gfx *g = (Gfx *) dl;
    s32 col[4];
    s32 level;
    s32 pass;

    if (o->unk127 == 0xFF) {
        level = o->unk1C8 + 1;
    } else {
        level = o->unk1C8;
    }
    SHADOW_GFX(g, 0xE7000000, 0);                                   /* gDPPipeSync */
    SHADOW_GFX(g, 0xFF48003F, D_800DF4B8);                          /* gDPSetColorImage RGBA16, 64 wide */
    SHADOW_GFX(g, 0xDE000000, (s32) &D_8008D7E8);                   /* gSPDisplayList */
    SHADOW_GFX(g, 0xDB0E0000, D_800DF500[slot]);                    /* gSPPerspNormalize */
    SHADOW_GFX(g, 0xDC080008, (s32) &D_8008D788);                   /* gSPViewport */
    SHADOW_GFX(g, 0xDA380007, (s32) &D_800DF728[slot * 0x80 + D_800BE9C0 * 0x40]); /* projection */
    SHADOW_GFX(g, 0xDA380003, (s32) &D_89810);                      /* gSPMatrix (identity view) */
    col[0] = 0;
    col[1] = 0;
    col[2] = 0;
    col[3] = level;
    g = obj_draw_model_dl(g, obj, arg3, (s32) o->unk1D4, obj_get_player_alpha(o, arg3), col, 3, 1);
    SHADOW_GFX(g, 0xD7000002, 0xFFFFFFFF);                          /* gSPTexture on */
    SHADOW_GFX(g, 0xE7000000, 0);
    if (level < 2) {
        SHADOW_GFX(g, 0xFCFFFFFF, 0xFFFCF87C);                      /* combine: texture */
        SHADOW_GFX(g, 0xFA000000, 0xFFFFFFFF);                      /* prim colour white */
        SHADOW_GFX(g, 0xEF003C3F, 0x0F0A4000);                      /* other mode: 1 cycle, average */
        pass = (level == 0) ? 2 : 1;
        for (;;) {
            SHADOW_GFX(g, 0xFD900000, D_800DF4B8);                  /* texture image = the shadow texture */
            SHADOW_GFX(g, 0xF5900000, 0x07018060);
            SHADOW_GFX(g, 0xE6000000, 0);                           /* load sync */
            SHADOW_GFX(g, 0xF3000000, 0x077FF100);                  /* load block */
            SHADOW_GFX(g, 0xE7000000, 0);
            SHADOW_GFX(g, 0xF5881000, 0x00018060);
            SHADOW_GFX(g, 0xF2000000, 0x000FC0FC);                  /* tile size 64x64 */
            SHADOW_GFX(g, 0xE40FC0FC, 0);                           /* texture rectangle 64x64 */
            SHADOW_GFX(g, 0xE1000000, 0x00100010);
            SHADOW_GFX(g, 0xF1000000, 0x04000400);
            if (--pass == 0) {
                break;
            }
            SHADOW_GFX(g, 0xE7000000, 0);
        }
        SHADOW_GFX(g, 0xE7000000, 0);
    }
    SHADOW_GFX(g, 0xD9FFFFFF, 0x00200001);                          /* geometry mode */
    dl = view_dl_begin((u8 *) render_set_scissor((s32) render_set_color_image(g), D_80083336, 0, 0, 0, 0), arg3);
    o->unk123 = 1;
    return dl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_render_caster.s")
#endif

/* was func_151859C4 */
u8 *shadow_clip_isect_ymin(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;
    f32 temp_f16;

    q = (*(f32 *)(arg0 + 8) - *(f32 *)(arg0 + 4)) / ((*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    temp_f16 = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = temp_f16;
    *(f32 *)(arg2 + 4) = temp_f16;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

/* was func_15185AC4 */
s32 shadow_clip_in_ymin(f32 *arg0) {
    return arg0[2] < arg0[1];
}

/* was func_15185AEC */
u8 *shadow_clip_isect_xmax(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) + *(f32 *)(arg0 + 0)) / ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)(arg0 + 0) - *(f32 *)(arg1 + 0)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)(arg2 + 0);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

/* was func_15185BEC */
s32 shadow_clip_in_xmax(f32 *arg0) {
    return arg0[0] < -arg0[2];
}

/* was func_15185C18 */
u8 *shadow_clip_isect_ymax(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) + *(f32 *)(arg0 + 4)) / ((*(f32 *)(arg0 + 8) - *(f32 *)(arg1 + 8)) + (*(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = -*(f32 *)(arg2 + 4);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

/* was func_15185D20 */
s32 shadow_clip_in_ymax(f32 *arg0) {
    return arg0[1] < -arg0[2];
}

/* was func_15185D4C */
u8 *shadow_clip_isect_xmin(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (*(f32 *)(arg0 + 8) - *(f32 *)(arg0 + 0)) / ((*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) - (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8)));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = *(f32 *)(arg2 + 0);
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

/* was func_15185E44 */
s32 shadow_clip_in_xmin(f32 *arg0) {
    return arg0[2] < arg0[0];
}

/* was func_15185E6C */
u8 *shadow_clip_isect_far(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (D_800D3AA8 - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D3AA8;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

/* was func_15185F6C */
s32 shadow_clip_in_far(f32 *arg0) {
    return D_800D3AA8 < arg0[2];
}

/* was func_15185F98 */
u8 *shadow_clip_isect_near(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 q;

    q = (D_800D3AAC - *(f32 *)(arg0 + 8)) / (*(f32 *)(arg1 + 8) - *(f32 *)(arg0 + 8));
    *(f32 *)(arg2 + 0) = (*(f32 *)(arg1 + 0) - *(f32 *)(arg0 + 0)) * q + *(f32 *)(arg0 + 0);
    *(f32 *)(arg2 + 4) = (*(f32 *)(arg1 + 4) - *(f32 *)(arg0 + 4)) * q + *(f32 *)(arg0 + 4);
    *(f32 *)(arg2 + 8) = D_800D3AAC;
    *(s16 *)(arg2 + 0xC) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xC) - *(s16 *)(arg0 + 0xC)) * q + (f32) *(s16 *)(arg0 + 0xC));
    *(s16 *)(arg2 + 0xE) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0xE) - *(s16 *)(arg0 + 0xE)) * q + (f32) *(s16 *)(arg0 + 0xE));
    *(s16 *)(arg2 + 0x10) = (s16) (s32) ((f32) (*(s16 *)(arg1 + 0x10) - *(s16 *)(arg0 + 0x10)) * q + (f32) *(s16 *)(arg0 + 0x10));
    return arg2 + 0x14;
}

/* was func_15186098 */
s32 shadow_clip_in_near(f32 *arg0) {
    return arg0[2] < D_800D3AAC;
}

typedef struct {
    f32 x, y, z;
    s16 s, t, u;
} ClipVtx_60C4;
/* was func_151860C4 */
ClipVtx_60C4 *shadow_clip_isect_x0(ClipVtx_60C4 *a, ClipVtx_60C4 *b, ClipVtx_60C4 *out) {
    f32 t;

    t = a->x / (a->x - b->x);
    out->x = 0.0f;
    out->y = a->y + (b->y - a->y) * t;
    out->z = a->z + (b->z - a->z) * t;
    out->s = a->s + (b->s - a->s) * t;
    out->t = a->t + (b->t - a->t) * t;
    out->u = a->u + (b->u - a->u) * t;
    return out + 1;
}

/* was func_151861B4 */
s32 shadow_clip_in_x_neg(f32 *arg0) {
    return *arg0 <= 0.0f;
}

/* was func_151861DC */
ClipVtx_60C4 *shadow_clip_isect_y0(ClipVtx_60C4 *a, ClipVtx_60C4 *b, ClipVtx_60C4 *out) {
    f32 t;

    t = a->y / (a->y - b->y);
    out->y = 0.0f;
    out->x = a->x + (b->x - a->x) * t;
    out->z = a->z + (b->z - a->z) * t;
    out->s = a->s + (b->s - a->s) * t;
    out->t = a->t + (b->t - a->t) * t;
    out->u = a->u + (b->u - a->u) * t;
    return out + 1;
}

/* was func_151862CC */
s32 shadow_clip_in_y_neg(f32 *arg0) {
    return arg0[1] <= 0.0f;
}

/* was func_151862F4 */
s32 shadow_clip_in_x_pos(f32 *arg0) {
    return *arg0 > 0.0f;
}

/* was func_1518631C */
s32 shadow_clip_in_y_pos(f32 *arg0) {
    return arg0[1] > 0.0f;
}

extern ClipVtx_60C4 *(*D_8008D838[])(ClipVtx_60C4 *, ClipVtx_60C4 *, ClipVtx_60C4 *);
extern s32 (*D_8008D860[])(ClipVtx_60C4 *);
/* was func_15186344 */
ClipVtx_60C4 *shadow_clip_polygon_plane(ClipVtx_60C4 *in, s32 n, s32 plane, ClipVtx_60C4 *out) {
    ClipVtx_60C4 *prev = &in[n - 1];
    ClipVtx_60C4 *(*isect)(ClipVtx_60C4 *, ClipVtx_60C4 *, ClipVtx_60C4 *) = D_8008D838[plane];
    s32 (*inside)(ClipVtx_60C4 *) = D_8008D860[plane];
    ClipVtx_60C4 *cur = in;
    s32 i;

    for (i = 0; i < n; i++) {
        if (inside(cur)) {
            if (inside(prev)) {
                *out++ = *cur;
            } else {
                out = isect(prev, cur, out);
                *out++ = *cur;
            }
        } else if (inside(prev)) {
            out = isect(prev, cur, out);
        }
        prev = cur;
        cur++;
    }
    return out;
}

#ifdef NON_MATCHING
/* P130 */
extern f32 D_800DE45C;  /* shadow alpha at the near depth */
ClipVtx_60C4 *shadow_clip_polygon_plane(ClipVtx_60C4 *in, s32 n, s32 plane, ClipVtx_60C4 *out);

// shadow_clip_triangle: clips one projected shadow polygon (n 20-byte shadow vertices at in: x, y, w, source
// vertex pointer) and converts it into 16-byte Vtx at out. The polygon (with the source vertex's s16 x / y / z
// as s / t / u) is clipped against planes 0..5 (|x| <= -w, |y| <= -w, near, far) in two ping-pong buffers. With
// split, planes 6 / 7 cut it into the halves x <= 0 / x > 0 and planes 8 / 9 cut each half into y > 0 / y <= 0:
// counts[0..4] are the start indices of the four quadrant pieces (A y>0, B y>0, A y<=0, B y<=0) and their end;
// without split all four pieces are the whole polygon (counts = 0, n, n, n, n). Each output vertex: position =
// the source vertex, texture s = 1024 - 1020 x / w, t = 1020 y / w + 1024, colour 0, alpha fading from
// D_800DE45C at the near depth D_800D3AAC to 0 at the far depth D_800D3AA8. Returns the number of vertices.
/* was func_15186494 */
s32 shadow_clip_triangle(s32 inAddr, s32 n, s32 unused, s32 outAddr, s32 *counts, s32 split) {
    u8 *in = (u8 *) inAddr;
    u8 *out = (u8 *) outAddr;
    ClipVtx_60C4 buf[2][26];
    s32 half[3];
    ClipVtx_60C4 *src;
    ClipVtx_60C4 *dst;
    ClipVtx_60C4 *v;
    s16 *pos;
    f32 k, a;
    s32 alpha;
    s32 plane;
    s32 i;

    for (i = 0; i < n; i++) {
        pos = *(s16 **) (in + i * 20 + 0xC);
        buf[0][i] = *(ClipVtx_60C4 *) (in + i * 20);
        buf[0][i].s = pos[0];
        buf[0][i].t = pos[1];
        buf[0][i].u = pos[2];
    }
    for (plane = 0; plane != 6; plane++) {
        dst = buf[(plane & 1) ^ 1];
        n = (u32) ((u8 *) shadow_clip_polygon_plane(buf[plane & 1], n, plane, dst) - (u8 *) dst) / 20;
    }
    half[0] = 0;
    counts[0] = 0;
    if (split != 0) {
        src = buf[plane & 1];
        dst = buf[(plane & 1) ^ 1];
        for (i = 0; i < 2; i++) {
            half[i + 1] = (u32) ((u8 *) shadow_clip_polygon_plane(src, n, i + 6, dst + half[i]) - (u8 *) dst) / 20;
        }
        plane++;
        src = buf[plane & 1];
        dst = buf[(plane & 1) ^ 1];
        for (i = 0; i < 4; i += 2) {
            counts[i + 1] = (u32) ((u8 *) shadow_clip_polygon_plane(src + half[0], half[1] - half[0], (i >> 1) + 8,
                                                        dst + counts[i]) - (u8 *) dst) / 20;
            counts[i + 2] = (u32) ((u8 *) shadow_clip_polygon_plane(src + half[1], half[2] - half[1], ((i + 1) >> 1) + 8,
                                                        dst + counts[i + 1]) - (u8 *) dst) / 20;
        }
        n = counts[4];
        plane++;
    } else {
        counts[4] = n;
        counts[3] = n;
        counts[2] = n;
        counts[1] = n;
    }
    v = buf[plane & 1];
    for (i = 0; i < n; i++, v++, out += 16) {
        *(s16 *) (out + 0) = v->s;
        *(s16 *) (out + 2) = v->t;
        *(s16 *) (out + 4) = v->u;
        k = 1020.0f / v->z;
        v->x = v->x * k;
        v->y = v->y * k;
        *(s16 *) (out + 8) = (s32) (1024.0f - v->x);
        out[0xC] = 0;
        out[0xD] = 0;
        out[0xE] = 0;
        *(s16 *) (out + 0xA) = (s32) (v->y + 1024.0f);
        a = D_800DE45C - ((v->z - D_800D3AAC) / (D_800D3AA8 - D_800D3AAC)) * D_800DE45C;
        /* IDO's float -> u32 (written out: NaN, <= -1 and >= 2^32 give 0xFFFFFFFF) */
        if (a != a || a <= -1.0f || a >= 4294967296.0f) {
            alpha = -1;
        } else if (a >= 2147483648.0f) {
            alpha = (s32) (a - 2147483648.0f);
        } else {
            alpha = (s32) a;
        }
        out[0xF] = alpha;
        *(s16 *) (out + 6) = 0;
    }
    return n;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_clip_triangle.s")
#endif

#ifdef NON_MATCHING
/* P130 */
extern s8 D_800DE471;   /* != 0: only level triangles whose D_800D3668 flag is 1 cast shadows */
extern s32 D_800D3AB0;  /* triangle table for shadow_level_triangles / shadow_object_triangles */
extern s32 D_800D3AB4;  /* end of the triangle bit mask */
extern s32 D_800DC26C;  /* level triangle table: 3 vertex pointers per triangle */
extern s32 D_800DF518;  /* shadow box x min, x max, z min, z max */
extern s32 D_800DF51C;
extern s32 D_800DF520;
extern s32 D_800DF524;
void collision_select_area(s32);
s32 zone_tree_collect_near(s32, s32, s32, u8 **);
s32 shadow_level_triangles(u32 *, s32, f32 *, s32);

// shadow_level_vertices: collects the level triangles under a shadow (box x / z +- r) and projects them.
// zone_tree_collect_near returns up to 16 level cells around (x, z); each cell holds at +0xE a 0-terminated triangle list
// (byte < 0x80: index += byte; else ((byte << 8) | next byte) & 0x7FFF is the index). The triangles (< 0x1760,
// and with flag 1 in D_800D3668 when D_800DE471) become bits of a stack mask; shadow_level_triangles projects them with the
// light matrix (4x4 f32) into the 20-byte shadow vertices at buf (up to end). Returns the number of vertices written.
/* was func_15186A9C */
s32 shadow_level_vertices(s32 x, s32 z, s32 r, s32 buf, u8 *light, s32 end) {
    u8 *cells[16];
    u32 mask[0x2EC / 4];
    s32 n;
    u8 *p;
    u32 tri, last;
    u32 c;

    last = 0;
    collision_select_area(0);
    n = zone_tree_collect_near(x, z, r, cells);
    if (n == 0) {
        return 0;
    }
    bzero(mask, sizeof(mask));
    while (n != 0) {
        n--;
        p = cells[n] + 0xE;
        tri = 0;
        while ((c = *p) != 0) {
            if (c & 0x80) {
                tri = ((c << 8) | p[1]) & 0x7FFF;
                p += 2;
            } else {
                tri += c;
                p += 1;
            }
            if (tri >= 0x1760) {
                continue;
            }
            if (D_800DE471 != 0 && ((u8 *) D_800D3668)[tri] != 1) {
                continue;
            }
            mask[tri >> 5] |= 1 << (tri & 0x1F);
            if (last < tri) {
                last = tri;
            }
        }
    }
    D_800D3AB0 = D_800DC26C;
    D_800D3AB4 = (s32) &mask[(last >> 5) + 1];
    D_800DF518 = x - r;
    D_800DF51C = x + r;
    D_800DF520 = z - r;
    D_800DF524 = z + r;
    return (shadow_level_triangles(mask, buf, (f32 *) light, end) - buf) / 20;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_level_vertices.s")
#endif

#ifdef NON_MATCHING
/* P38: shadow display list (m2c draft from P32, fixed by hand). UNVERIFIED: the strip emitter (TRI4 / TRI2 / TRI1 split, 16-vertex flushes); see P38.md */
s32 allocate_memory(s32, s32, s32, s32);
void heap_free();
s32 model_make_ready(struct127 *, u8, s32, s32);
u8 obj_current_part_model_idx(struct127 *, s32 *);
u8 *view_dl_begin(u8 *, s32);
f32 shadow_light_projection(s32, s32, f32, f32, f32, f32);
s32 shadow_obj_light_distance(s32, s32, f32 *, f32 *, f32 *);
u8 *shadow_render_caster(u8 *, s32, s32, s32);
s32 shadow_clip_triangle(s32, s32, s32, s32, s32 *, s32);
s32 shadow_level_vertices(s32, s32, s32, s32, u8 *, s32);
u32 shadow_object_vertices(s32, s32, s32, s32, u8 *, s32, s32);
s32 memcpy(u8 *, s32, s32);
extern s32 D_8008D780;
extern s32 D_8008D7B0;
extern s32 D_800BEFC4;
extern s32 D_800C4D10;
extern s32 D_800DE44C;
extern s32 D_800DE450;
extern s32 D_800DE454;
extern f32 D_800DE458;
extern s32 D_800DE460;
extern s32 D_800DE468;
extern s32 D_800DF4B8;
extern s32 D_800DF4C0;
extern u8 D_800DF510;
extern s8 D_800DF511;
extern s32 D_800DF528;

/* was func_15186D04 */
u8 *shadow_draw_all(u8 *arg0, s32 arg1) {
    s32 sp134;
    u32 sp130;
    s32 sp120;
    u32 sp11C;
    s32 spFC[5];
    s32 spF8;
    s32 spF4;
    u8 *spE8;
    s32 spE0;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    u8 *spC8;
    struct127 *sp74;
    u8 *sp6C;
    s32 *var_t4;
    f32 temp_f0;
    f32 var_f16;
    f32 var_f20;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_cond;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t3;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 var_fp;
    s32 var_s1_2;
    s32 var_s6;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    struct126 *temp_v0_3;
    struct127 *temp_v1_2;
    u16 temp_t6;
    u32 temp_v0_10;
    u32 temp_v0_5;
    u32 var_s7;
    u8 temp_a0;
    u8 temp_v0_4;
    u8 var_s1;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *temp_s1;
    u8 *temp_s1_2;
    u8 *temp_v0_11;
    u8 *temp_v0_6;
    u8 *var_s0;
    u8 *var_s0_2;
    u8 *var_s5;

    var_s0 = arg0;
    spF4 = 0;
    spC8 = var_s0;
    if (arg1 != 0) {
        goto block_88;
    }
    var_v0 = D_8008D780;
    if (D_800DE44C < var_v0) {
        D_8008D780 = D_800DE44C;
        var_v0 = D_800DE44C;
        D_800DE458 *= 0.8f;
    } else {
        if ((*(u16 *)((u8 *)D_800B0DF0 + 0x1E)) == 0) {
            (*(u16 *)((u8 *)D_800B0DF0 + 0x1E)) = 0x190U;
            var_v0 = D_8008D780;
        }
        if (var_v0 < D_800DE450) {
            temp_t6 = (*(u16 *)((u8 *)D_800B0DF0 + 0x1E));
            var_f16 = (f32) temp_t6;
            if ((s32) temp_t6 < 0) {
                var_f16 += 4294967296.0f;
            }
            D_800DE458 += (var_f16 - D_800DE458) * 0.95f;
        }
        if (var_v0 < D_800DE454) {
            D_8008D780 = D_800DE454;
            var_v0 = D_800DE454;
        }
    }
    temp_v0 = allocate_memory((var_v0 * 0x10) + 0x1C0, 3, 1, 1);
    var_s6 = temp_v0;
    if (temp_v0 == 0) {
        goto block_88;
    }
    temp_v0_2 = allocate_memory(D_8008D780 * 0x14, 2, 1, 1);
    sp134 = temp_v0_2;
    if (temp_v0_2 == 0) {
        heap_free(var_s6);
        goto block_88;
    }
    temp_s1 = (u8 *) &D_800DF4C0 + arg1 * 0x10;
    memcpy(temp_s1, D_800BE628 + (D_80082FA4 * 0x180) + (D_800BE9C0 * 0x10) + 0x40, 0x10);
    spE8 = var_s0;
    var_s7 = 0;
    sp74 = D_800CC2D0;
    spF8 = 0;
    (*(s16 *)((u8 *)temp_s1 + 0xC)) = (s16) ((s32) ((*(s16 *)((u8 *)temp_s1 + 0xC)) * D_800DE460) >> 0xA);
    do {
        if ((sp74->interaction_state == 0) || (sp74->unk1D4 == NULL) || (temp_a0 = sp74->unk74, temp_v1 = 1 << arg1, ((temp_a0 & temp_v1) != 0)) || (sp74->unk5 != 0) || ((sp74->unk66 & 0x10) != 0x10) || (temp_v1 == (temp_a0 & temp_v1)) || (sp74->unk84.uh == 0x2D8) || ((temp_v0_3 = sp74->unk31C, (temp_v0_3 != NULL)) && (((u8) temp_v0_3->unk95 != 0) || (temp_v0_3->pad98[0] != 0))) || (D_800DF510 & (1 << spF8))) {
            var_v0_2 = spF8 + 1;
        } else if ((sp74->unk65 != 0) && (sp74->id != 0x62)) {
            var_v0_2 = spF8 + 1;
        } else {
            if (sp74->unk2C8 != 0) {
                temp_v0_4 = obj_current_part_model_idx(sp74, &spE0);
                var_s1 = temp_v0_4;
                model_make_ready(sp74, temp_v0_4, spE0, 0);
            } else {
                var_s1 = sp74->id;
                spE0 = 0;
            }
            var_v0_2 = spF8 + 1;
            if (*(s32 *)((u8 *)&D_800C4D10 + (var_s1 * 4)) == 0) {

            } else {
                var_v0_2 = spF8 + 1;
                if (shadow_obj_light_distance(spF8, arg1, &spD8, &spD4, &spD0) == 0) {

                } else {
                    var_f20 = 0.0f;
                    sp11C = 0;
                    if ((D_800DE468 != 0) && (spF4 < 8) && (var_s7 < (u32) D_8008D780)) {
loop_42:
                        temp_f0 = shadow_light_projection(spF8, spF4, spD8, spD4, spD0, var_f20);
                        temp_cond = temp_f0 == 0.0f;
                        var_f20 = temp_f0;
                        if (!temp_cond) {
                            temp_s1_2 = (u8 *) &D_800DF528 + (spF4 << 6);
                            temp_v0_5 = shadow_object_vertices((s32) sp74->x_position, (s32) sp74->z_position, 0xE6, sp134, temp_s1_2, ((D_8008D780 * 0x14) + sp134) - 0x28, shadow_level_vertices((s32) sp74->x_position, (s32) sp74->z_position, 0xE6, sp134, temp_s1_2, ((D_8008D780 * 0x14) + sp134) - 0x28));
                            sp130 = temp_v0_5;
                            if (temp_v0_5 != 0) {
                                sp6C = (u8 *) &D_800DF4C0 + arg1 * 0x10;
                                var_fp = 0;
                                var_s1_2 = 0;
                                temp_v0_6 = shadow_render_caster(var_s0, spF8, spF4, arg1);
                                temp_s0 = temp_v0_6 + 8;
                                if ((sp74->unk127 != 0xFF) && ((s32) sp74->unk1C8 < 2)) {
                                    sp120 = 1;
                                } else {
                                    temp_v1_2 = &D_800CC2D0[sp74->unk124];
                                    if (((spF8 + 1) == temp_v1_2->unk65) && (temp_v1_2->unk127 != 0xFF) && (sp74->id == 0x53)) {
                                        sp120 = 1;
                                    } else {
                                        sp120 = 0;
                                    }
                                }
                                (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xDE000000;
                                (*(s32 **)((u8 *)temp_v0_6 + 4)) = &D_8008D7B0;
                                (*(s32 *)((u8 *)temp_s0 + 0)) = 0xDC080008;
                                temp_s0_2 = temp_s0 + 8;
                                (*(u8 **)((u8 *)temp_s0 + 4)) = sp6C;
                                (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xEF082C3F;
                                (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0x5049D8;
                                temp_s0_3 = temp_s0_2 + 8;
                                (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xFD900000;
                                temp_s0_4 = temp_s0_3 + 8;
                                (*(s32 *)((u8 *)temp_s0_3 + 4)) = (s32) D_800DF4B8;
                                (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xF5900000;
                                (*(s32 *)((u8 *)temp_s0_4 + 4)) = 0x07080200;
                                temp_s0_5 = temp_s0_4 + 8;
                                (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xE6000000;
                                (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0;
                                temp_s0_6 = temp_s0_5 + 8;
                                (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF3000000;
                                (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x077FF100;
                                temp_s0_7 = temp_s0_6 + 8;
                                (*(s32 *)((u8 *)temp_s0_7 + 0)) = 0xE7000000;
                                (*(s32 *)((u8 *)temp_s0_7 + 4)) = 0;
                                temp_s0_8 = temp_s0_7 + 8;
                                (*(s32 *)((u8 *)temp_s0_8 + 0)) = 0xF5881000;
                                (*(s32 *)((u8 *)temp_s0_8 + 4)) = 0x80200;
                                temp_s0_9 = temp_s0_8 + 8;
                                (*(s32 *)((u8 *)temp_s0_9 + 0)) = 0xF2000000;
                                (*(s32 *)((u8 *)temp_s0_9 + 4)) = 0xFC0FC;
                                temp_s0_10 = temp_s0_9 + 8;
                                var_s5 = temp_s0_10;
                                var_s0_2 = temp_s0_10 + 8;
                                if ((sp130 != 0) && (var_s7 < (u32) D_8008D780)) {
loop_54:
                                    if ((var_fp % 3) == 2) {
                                        shadow_clip_triangle(((var_fp * 0x14) + sp134) - 0x28, 3, 0x1A, var_s6, spFC, sp120);
                                        var_t4 = spFC;
                                        do {
                                            temp_t6_2 = (*(s32 *)((u8 *)var_t4 + 4));
                                            temp_t7 = (*(s32 *)((u8 *)var_t4 + 0));
                                            var_t4 += 1;
                                            temp_t2 = temp_t6_2 - temp_t7;
                                            var_s1_2 += temp_t2;
                                            var_s6 += temp_t2 * 0x10;
                                            var_s7 += temp_t2;
                                            if (var_s1_2 >= 0x11) {
                                                temp_v0_7 = var_s1_2 - temp_t2;
                                                (*(s32 *)((u8 *)var_s5 + 4)) = (s32) ((var_s1_2 * -0x10) + var_s6);
                                                (*(s32 *)((u8 *)var_s5 + 0)) = (s32) (((temp_v0_7 & 0xFF) << 0xC) | 0x01000000 | ((temp_v0_7 & 0x7F) * 2));
                                                var_s5 = var_s0_2;
                                                var_s0_2 += 8;
                                                var_s1_2 = temp_t2;
                                            }
                                            temp_t3 = var_s1_2 - temp_t2;
                                            var_t2 = temp_t2 - 2;
                                            var_v1 = temp_t3 + var_t2;
                                            if (var_t2 > 0) {
                                                do {
                                                    if (var_t2 >= 4) {
                                                        temp_t6_3 = (var_v1 - 1) & 0x1F;
                                                        temp_v0_8 = temp_t3 & 0x1F;
                                                        temp_a1 = var_v1 - 2;
                                                        temp_a2 = temp_v0_8 << 0xA;
                                                        (*(s32 *)((u8 *)var_s0_2 + 0)) = (s32) ((temp_v0_8 << 0x17) | 0x10000000 | (((var_v1 - 3) & 0x1F) << 0x12) | (((temp_a1 >> 2) & 7) << 0xF) | temp_a2 | ((temp_a1 & 0x1F) << 5) | temp_t6_3);
                                                        temp_t1 = var_v1 & 0x1F;
                                                        (*(s32 *)((u8 *)var_s0_2 + 4)) = (s32) ((temp_a1 << 0x1E) | (temp_v0_8 << 0x19) | (temp_t1 << 0x14) | (((var_v1 + 1) & 0x1F) << 0xF) | temp_a2 | (temp_t6_3 << 5) | temp_t1);
                                                        var_s0_2 += 8;
                                                        var_t2 -= 4;
                                                        var_v1 -= 4;
                                                    } else {
                                                        temp_t8 = ((temp_t3 * 2) & 0xFF) << 0x10;
                                                        temp_v0_9 = var_v1 * 2;
                                                        temp_a0_2 = temp_v0_9 + 2;
                                                        if (var_t2 >= 2) {
                                                            temp_a2_2 = temp_v0_9 & 0xFF;
                                                            (*(s32 *)((u8 *)var_s0_2 + 0)) = (s32) (temp_t8 | (temp_a2_2 << 8) | (temp_a0_2 & 0xFF) | 0x06000000);
                                                            (*(s32 *)((u8 *)var_s0_2 + 4)) = (s32) (temp_t8 | (((temp_v0_9 - 2) & 0xFF) << 8) | temp_a2_2);
                                                            var_s0_2 += 8;
                                                            var_t2 -= 2;
                                                            var_v1 -= 2;
                                                        } else {
                                                            (*(s32 *)((u8 *)var_s0_2 + 0)) = (s32) (temp_t8 | ((temp_v0_9 & 0xFF) << 8) | (temp_a0_2 & 0xFF) | 0x05000000);
                                                            (*(s32 *)((u8 *)var_s0_2 + 4)) = 0;
                                                            var_s0_2 += 8;
                                                            var_t2 -= 1;
                                                            var_v1 -= 1;
                                                        }
                                                    }
                                                } while (var_t2 > 0);
                                            }
                                        } while (var_t4 != &spFC[4]);
                                    }
                                    var_fp += 1;
                                    if (((u32) var_fp < sp130) && (var_s7 < (u32) D_8008D780)) {
                                        goto loop_54;
                                    }
                                }
                                if (var_s1_2 != 0) {
                                    (*(s32 *)((u8 *)var_s5 + 4)) = (s32) ((var_s1_2 * -0x10) + var_s6);
                                    (*(s32 *)((u8 *)var_s5 + 0)) = (s32) (((var_s1_2 & 0xFF) << 0xC) | 0x01000000 | ((var_s1_2 & 0x7F) * 2));
                                } else {
                                    var_s0_2 = var_s5;
                                }
                                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xE7000000;
                                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0;
                                var_s0 = var_s0_2 + 8;
                                spF4 += 1;
                            }
                            temp_v0_10 = sp11C + 1;
                            if ((temp_v0_10 < (u32) D_800DE468) && (spF4 < 8)) {
                                sp11C = temp_v0_10;
                                if (var_s7 < (u32) D_8008D780) {
                                    goto loop_42;
                                }
                            }
                        }
                    }
                    var_v0_2 = spF8 + 1;
                }
            }
        }
        spF8 = var_v0_2;
        sp74 = &sp74[1];
    } while (var_v0_2 != 0x19);
    if (spF4 != 0) {
        temp_v0_11 = view_dl_begin(var_s0, arg1);
        (*(s32 *)((u8 *)temp_v0_11 + 0)) = 0xDC080008;
        (*(s32 *)((u8 *)temp_v0_11 + 4)) = (s32) (D_800BE628 + (D_80082FA4 * 0x180) + (D_800BE9C0 * 0x10) + 0x40);
        var_s0 = temp_v0_11 + 8;
    } else {
        var_s0 = spE8;
    }
    if (var_s7 >= (u32) D_8008D780) {
        D_8008D780 = var_s7 + 0x30;
    } else {
        D_8008D780 = (s32) var_s7;
    }
    D_800DF510 = 0;
    D_800DF511 = 0;
    heap_free(sp134);
    if (D_800BEFC4 < (((s32) var_s0 - (s32) D_800BEDE8[D_800BE9C0]) >> 3)) {
        var_v0_3 = 1;
    } else {
        var_v0_3 = 0;
    }
    if (var_v0_3 != 0) {
        return spC8;
    }
block_88:
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_draw_all.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800DE44C;
extern s32 D_800DE450;
extern s32 D_800DE454;
extern s32 D_800DE460;
extern s32 D_800DE464;
extern s32 D_800DE468;
extern f32 D_800DE46C;
extern s8 D_800DE470;
extern s8 D_800DE471;

/* was func_15187820 */
void shadow_settings_for_level(s32 arg0) {
    D_800DE44C = 0x258;
    D_800DE450 = 0xB4;
    D_800DE454 = 0x5A;
    D_800DE460 = 0x3F8;
    D_800DE464 = 0;
    D_800DE468 = 1;
    D_800DE46C = 1.0f;
    D_800DE470 = 1;
    D_800DE471 = 1;
    switch (arg0) {                                 /* irregular */
    case 33:
        D_800DE44C = 0x12C0;
        D_800DE450 = 0x12BF;
        D_800DE454 = 0x12BE;
        D_800DE460 = 0x3F2;
        D_800DE464 = 1;
        D_800DE468 = 4;
        D_800DE470 = 0;
        return;
    case 34:
        D_800DE44C = 0x960;
        D_800DE450 = 0x95F;
        D_800DE454 = 0x95E;
        D_800DE468 = 4;
        D_800DE470 = 0;
        return;
    case 20:
        D_800DE471 = 0;
        return;
    case 41:
        D_800DE44C = 0x4B0;
        D_800DE450 = 0x258;
        D_800DE454 = 0x12C;
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_settings_for_level.s")
#endif
#ifdef NON_MATCHING
/* P130 */
extern s32 D_800D3AB0;
extern s32 D_800DC26C;
extern s32 D_800DF514;  /* number of world object ids for shadow_object_triangles */
extern s32 D_800DF518;
extern s32 D_800DF51C;
extern s32 D_800DF520;
extern s32 D_800DF524;
extern s16 D_800D3C00[]; /* visible world object ids */
void collision_select_area(s32);
s32 world_objects_transform_mesh(s32 count, s32 *idList, s32 force);
s32 shadow_object_triangles(u16 *, s32, f32 *, s32);

// shadow_object_vertices: adds the world objects' triangles under a shadow (box x / z +- r) after the count level
// shadow vertices at buf. Takes the D_800DC320 world objects (0xA0-byte records at D_800DBEF4) that are shown
// (+0x6E == 0, no 0x60 flag at +0x4F) and whose x / z (s16 +0x10 / +0x14) +- their size (max of u16 +0x50, +0x52)
// meet the box, refreshes their triangles (world_objects_transform_mesh) and projects them (shadow_object_triangles).
// Returns count plus the number of vertices added.
/* was func_15187954 */
u32 shadow_object_vertices(s32 x, s32 z, s32 r, s32 buf, u8 *light, s32 end, s32 count) {
    u8 *obj;
    s32 size;
    s32 i, n;

    if (D_800DC320 == 0) {
        return count;
    }
    collision_select_area(2);
    buf += count * 20;
    D_800DF518 = x - r;
    D_800DF51C = x + r;
    D_800DF520 = z - r;
    D_800DF524 = z + r;
    n = 0;
    obj = (u8 *) D_800DBEF4;
    for (i = 0; i < D_800DC320; i++, obj += 0xA0) {
        if (obj[0x6E] != 0 || (obj[0x4F] & 0x60)) {
            continue;
        }
        size = *(u16 *) (obj + 0x52);
        if (size < *(u16 *) (obj + 0x50)) {
            size = *(u16 *) (obj + 0x50);
        }
        if (D_800DF51C < *(s16 *) (obj + 0x10) - size || *(s16 *) (obj + 0x10) + size < D_800DF518 ||
            D_800DF524 < *(s16 *) (obj + 0x14) - size || *(s16 *) (obj + 0x14) + size < D_800DF520) {
            continue;
        }
        D_800D3C00[n++] = i;
    }
    if (n != 0) {
        world_objects_transform_mesh(n, (s32 *) D_800D3C00, 0);
        D_800D3AB0 = D_800DC26C;
        D_800DF514 = n;
        count += (shadow_object_triangles((u16 *) D_800D3C00, buf, (f32 *) light, end) - buf) / 20;
    }
    return count;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shadow_object_vertices.s")
#endif

#ifdef NON_MATCHING
s32 allocate_memory(s32, s32, s32, s32);

/* was func_15187B50 */
void shard_ring_spawn(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7) {
    f32 var_f10;
    f32 var_f16;
    f32 var_f18;
    f32 var_f18_2;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f8;
    f32 var_f8_2;
    s32 temp_t2;
    s32 temp_t3;
    s32 temp_t3_2;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s3;
    struct102 *temp_v0;
    u8 *temp_t0;

    temp_v0 = node_alloc(6, 0, 0xB0, 1, 0xFFU, 1U);
    if (temp_v0 != NULL) {
        temp_v0_2 = allocate_memory(0x780, 1, 2, 1);
        (*(s32 *)((u8 *)temp_v0 + 0xA4)) = temp_v0_2;
        if (temp_v0_2 == 0) {
            node_destroy(temp_v0);
            return;
        }
        (*(f32 *)((u8 *)temp_v0 + 0x90)) = arg0;
        var_s0 = 0;
        (*(f32 *)((u8 *)temp_v0 + 0x94)) = arg1;
        (*(s16 *)((u8 *)temp_v0 + 0xA8)) = 0;
        (*(s16 *)((u8 *)temp_v0 + 0xAA)) = (s16) arg4;
        (*(f32 *)((u8 *)temp_v0 + 0x98)) = arg2;
        var_s3 = 0;
        (*(f32 *)((u8 *)temp_v0 + 0x9C)) = arg6;
        (*(f32 *)((u8 *)temp_v0 + 0xA0)) = arg7;
        do {
            if (var_s3 < 0x168) {
                temp_t9 = 7 - (random_int() & 0xF);
                var_f18 = (f32) temp_t9;
                if (temp_t9 < 0) {
                    var_f18 += 4294967296.0f;
                }
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x80)) = var_f18;
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x84)) = 0.0f;
                temp_t5 = (random_int() & 0x3F) + (var_s3 - 0x1E);
                var_f8 = (f32) temp_t5;
                if (temp_t5 < 0) {
                    var_f8 += 4294967296.0f;
                }
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x88)) = var_f8;
                (*(s8 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x98)) = 0;
            } else if (var_s3 < 0x2D0) {
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x80)) = 0.0f;
                temp_t3 = (random_int() & 0x3F) + (var_s3 - 0x23A);
                var_f4 = (f32) temp_t3;
                if (temp_t3 < 0) {
                    var_f4 += 4294967296.0f;
                }
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x84)) = var_f4;
                temp_t7 = 7 - (random_int() & 0xF);
                var_f10 = (f32) temp_t7;
                if (temp_t7 < 0) {
                    var_f10 += 4294967296.0f;
                }
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x88)) = var_f10;
                (*(s8 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x98)) = 0;
            } else {
                temp_t3_2 = (random_int() & 0x3F) + (var_s3 - 0x1E);
                var_f18_2 = (f32) temp_t3_2;
                if (temp_t3_2 < 0) {
                    var_f18_2 += 4294967296.0f;
                }
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x80)) = var_f18_2;
                temp_t8 = 0x61 - (random_int() & 0xF);
                var_f8_2 = (f32) temp_t8;
                if (temp_t8 < 0) {
                    var_f8_2 += 4294967296.0f;
                }
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x84)) = var_f8_2;
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x88)) = 0.0f;
                (*(s8 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x98)) = 1;
            }
            if (arg3 >= 4) {
                temp_t6 = (random_int() % (u32) (arg3 >> 2)) + arg3;
                var_f4_2 = (f32) temp_t6;
                if (temp_t6 < 0) {
                    var_f4_2 += 4294967296.0f;
                }
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x8C)) = var_f4_2;
            } else {
                (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x8C)) = (f32) arg3;
            }
            temp_t2 = random_int() & 0xF;
            var_f16 = (f32) temp_t2;
            if (temp_t2 < 0) {
                var_f16 += 4294967296.0f;
            }
            (*(f32 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x90)) = var_f16;
            (*(s16 *)((u8 *)(((*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0)) + 0x94)) = 0;
            var_s3 += 0x5A;
            temp_t0 = (*(s32 *)((u8 *)temp_v0 + 0xA4)) + var_s0;
            var_s0 += 0xA0;
            (*(s16 *)((u8 *)temp_t0 + 0x96)) = (s16) (arg4 - (random_int() & arg5));
        } while (var_s3 != 0x438);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shard_ring_spawn.s")
#endif
#ifdef NON_MATCHING
/* was func_15187EE8 */
void shard_ring_tick(struct102 *arg0) {
    f32 temp_f0;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_a0;
    s16 var_v1;
    s32 var_a1;
    u8 *temp_v0_3;
    u8 *var_v0;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0xA8));
    if (temp_v0 < 0) {
        heap_free((*(s32 *)((u8 *)arg0 + 0xA4)), arg0);
        node_destroy(arg0);
        return;
    }
    (*(s16 *)((u8 *)arg0 + 0xA8)) = (s16) (temp_v0 + D_800BE9E4);
    temp_v0_2 = (*(s16 *)((u8 *)arg0 + 0xA8));
    if ((*(s16 *)((u8 *)arg0 + 0xAA)) < temp_v0_2) {
        (*(s16 *)((u8 *)arg0 + 0xA8)) = -0xA;
        return;
    }
    var_a1 = 0;
    if (temp_v0_2 >= 0) {
        do {
            temp_v0_3 = (*(s32 *)((u8 *)arg0 + 0xA4)) + var_a1;
            temp_v1 = (*(s16 *)((u8 *)temp_v0_3 + 0x94));
            if (temp_v1 < (*(s16 *)((u8 *)temp_v0_3 + 0x96))) {
                (*(s16 *)((u8 *)temp_v0_3 + 0x94)) = (s16) (temp_v1 + D_800BE9E4);
                var_v0 = (*(s32 *)((u8 *)arg0 + 0xA4)) + var_a1;
                var_a0 = (*(s16 *)((u8 *)var_v0 + 0x96));
                var_v1 = (*(s16 *)((u8 *)var_v0 + 0x94));
                if (var_a0 < var_v1) {
                    (*(s16 *)((u8 *)var_v0 + 0x94)) = var_a0;
                    var_v0 = (*(s32 *)((u8 *)arg0 + 0xA4)) + var_a1;
                    var_v1 = (*(s16 *)((u8 *)var_v0 + 0x94));
                    var_a0 = (*(s16 *)((u8 *)var_v0 + 0x96));
                }
                temp_f0 = (*(f32 *)((u8 *)var_v0 + 0x8C));
                (*(f32 *)((u8 *)var_v0 + 0x90)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0x90)) + (temp_f0 - (((temp_f0 / 3.0f) * (f32) var_v1) / (f32) var_a0)));
            }
            var_a1 += 0xA0;
        } while (var_a1 != 0x780);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shard_ring_tick.s")
#endif
#ifdef NON_MATCHING
void mtxf_translate(u8 *mtx, s32 x, s32 y, s32 z);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void mtxf_rotate_xyz_deg(f32 mtx[4][4], f32 arg1, f32 arg2, f32 arg3);
void shard_quad_rotation_matrix(u8 *arg0, f32 arg1, f32 arg2, f32 arg3);
void guMtxF2L2(float mf[4][4], Mtx *m);
extern u8 D_8008D8D8[];         /* the 4-vertex quad */

// shard_ring_draw: draw handler (table D_8008B988) of the twelve-quad ring built by shard_ring_spawn / stepped by
// shard_ring_tick; nothing (gfx returned unchanged) when obj + 0xA8 < 0. Loads the object matrix (translation obj
// + 0x90, this frame's Mtx at obj + 0x10 + D_800BE9C0 * 64), then for each 0xA0-byte quad record (obj + 0xA4):
// translation (rec + 0x90, 0, 0) scaled by obj + 0xA0 (x) / obj + 0x9C (y, z) times its rotation (rec + 0x80..0x88;
// mtxf_rotate_xyz_deg, or shard_quad_rotation_matrix when rec + 0x98 is set) into its own frame Mtx (rec + D_800BE9C0 * 64), prim alpha
// (life - age) * 255 / life (rec + 0x96 / + 0x94), and the quad D_8008D8D8 as two triangles. arg2 is unused.
/* was func_15188008 */
Gfx *shard_ring_draw(Gfx *gfx, u8 *obj, s32 arg2) {
    f32 mtx[4][4];
    f32 rot[4][4];
    u8 *rec;
    s32 i;

    if (*(s16 *) (obj + 0xA8) < 0) {
        return gfx;
    }
    mtxf_translate((u8 *) mtx, *(s32 *) (obj + 0x90), *(s32 *) (obj + 0x94), *(s32 *) (obj + 0x98));
    guMtxF2L2(mtx, (Mtx *) (obj + 0x10 + D_800BE9C0 * 64));
    for (i = 0; i < 12; i++) {
        /* gSPMatrix(load, modelview): the object matrix */
        gfx->words.w0 = 0xDA380003;
        gfx->words.w1 = (u32) (obj + 0x10 + D_800BE9C0 * 64);
        gfx++;
        rec = *(u8 **) (obj + 0xA4) + i * 0xA0;
        mtxf_translate((u8 *) mtx, *(s32 *) (rec + 0x90), 0, 0);
        mtx[0][0] *= *(f32 *) (obj + 0xA0);
        mtx[1][1] *= *(f32 *) (obj + 0x9C);
        mtx[2][2] *= *(f32 *) (obj + 0x9C);
        rec = *(u8 **) (obj + 0xA4) + i * 0xA0;
        if (rec[0x98] == 0) {
            mtxf_rotate_xyz_deg(rot, *(f32 *) (rec + 0x80), *(f32 *) (rec + 0x84), *(f32 *) (rec + 0x88));
        } else {
            shard_quad_rotation_matrix((u8 *) rot, *(f32 *) (rec + 0x80), *(f32 *) (rec + 0x84), *(f32 *) (rec + 0x88));
        }
        mtxf_mul(mtx, rot, mtx);
        guMtxF2L(mtx, (Mtx *) (*(u8 **) (obj + 0xA4) + i * 0xA0 + D_800BE9C0 * 64));
        rec = *(u8 **) (obj + 0xA4) + i * 0xA0;
        /* gDPSetPrimColor: white, alpha by remaining life */
        gfx->words.w1 = 0xFFFFFF00 |
                        (u8) (((*(s16 *) (rec + 0x96) - *(s16 *) (rec + 0x94)) * 255) / *(s16 *) (rec + 0x96));
        gfx->words.w0 = 0xFA000100;
        gfx++;
        /* gSPMatrix(mul, modelview): the quad matrix */
        gfx->words.w0 = 0xDA380001;
        gfx->words.w1 = (u32) (*(u8 **) (obj + 0xA4) + i * 0xA0 + D_800BE9C0 * 64);
        gfx++;
        /* gSPVertex(D_8008D8D8, 4, 0); triangles (0, 1, 2), (0, 1, 3), (0, 2, 3) */
        gfx->words.w0 = 0x01004008;
        gfx->words.w1 = (u32) D_8008D8D8;
        gfx++;
        gfx->words.w0 = 0x05000204;
        gfx->words.w1 = 0;
        gfx++;
        gfx->words.w0 = 0x05000206;
        gfx->words.w1 = 0;
        gfx++;
        gfx->words.w0 = 0x05000406;
        gfx->words.w1 = 0;
        gfx++;
    }
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shard_ring_draw.s")
#endif

#ifdef NON_MATCHING
s32 game_gu_mtx_ident_f(u8 *);
extern f32 D_8008D918;

/* was func_151882DC */
void shard_quad_rotation_matrix(u8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp44;
    f32 sp3C;
    f32 sp34;
    f32 sp30;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;

    temp_f12 = arg1 * D_8008D918;
    arg1 = temp_f12;
    arg2 *= D_8008D918;
    arg3 *= D_8008D918;
    sp44 = sinf(temp_f12);
    temp_f20 = cosf(arg1);
    temp_f22 = sinf(arg2);
    sp34 = cosf(arg2);
    sp3C = sinf(arg3);
    sp30 = cosf(arg3);
    game_gu_mtx_ident_f(arg0);
    temp_f0 = sp44 * temp_f22;
    (*(f32 *)((u8 *)arg0 + 0x18)) = sp44;
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((sp34 * sp30) - (temp_f0 * sp3C));
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((sp34 * sp3C) + (temp_f0 * sp30));
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) (-temp_f22 * temp_f20);
    temp_f0_2 = sp44 * sp34;
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (-temp_f20 * sp3C);
    (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) (temp_f20 * sp30);
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((temp_f22 * sp30) + (temp_f0_2 * sp3C));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (temp_f20 * sp34);
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((temp_f22 * sp3C) - (temp_f0_2 * sp30));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1ED0/shard_quad_rotation_matrix.s")
#endif