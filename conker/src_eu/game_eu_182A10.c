#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 (*D_8008B068[])(u8 *);

/* was func_15155200 */
void sprite2d_update(u8 *arg0)
{
  s32 pad; // fakematch: puts done at sp+0x1B
  s8 done = 0;
  u8 *p;
  u8 *q;
  s16 v;
  p = arg0;
  if ((*((u16 *) (p + 0x24))) & 1)
  {
    *((s16 *) (p + 0x22)) -= D_800BE9E4;
    if ((*((s16 *) (p + 0x22))) < 0)
    {
      done = 1;
    }
  }
  if ((p[0x68] & 0xF) && (!done))
  {
    if (D_8008B068[p[0x68] & 0xF](p) == 0)
    {
      done = 1;
    }
  }
  if ((*((u16 *) (p + 0x24))) & 8)
  {
    if ((*((s16 *) (p + 0x22))) < (*((s16 *) (p + 0x26))))
    {
    q = p; // fakematch: second name for the 0x22 reload
      v = (*((s16 *) (p + 0x28))) * (*((s16 *) (q + 0x22)));
      if (v < p[0x2E])
      {
        arg0[0x2E] = v;
      }
    }
  }
  if (done)
  {
    node_destroy((struct102 *) p);
  }
}

/* A 2D sprite drawn as one textured rectangle (HUD elements). Only the fields sprite2d_draw reads. */
typedef struct {
    u8  pad0[0x10];
    f32 x;              /* 0x10 centre, in view units */
    f32 y;              /* 0x14 */
    f32 halfW;          /* 0x18 */
    f32 halfH;          /* 0x1C */
    u8  tex;            /* 0x20 D_80090F10 index, 0xFF: no texture load */
    u8  pad21[3];
    u16 flags;          /* 0x24 SPRITE2D_* */
    u8  pad26[0x2B - 0x26];
    u8  colA[4];        /* 0x2B..0x2E */
    u8  colB[4];        /* 0x2F..0x32 */
    u8  colC;           /* 0x33 */
    s32 otherMode;      /* 0x34 */
    s32 geomSet;        /* 0x38 */
    s32 geomClear;      /* 0x3C */
    s32 renderMode;     /* 0x40 D_800A4EA8 pair index */
    u8  pad44[3];
    u8  combine;        /* 0x47 */
    s32 otherMode2;     /* 0x48 */
    s32 otherMode3;     /* 0x4C */
    s8  fadeA;          /* 0x50 */
    s8  fadeB;          /* 0x51 */
    u8  pad52[2];
    u8  player;         /* 0x54 */
    u8  pad55[3];
    f32 scaleS;         /* 0x58 */
    f32 scaleT;         /* 0x5C */
    f32 offsetS;        /* 0x60 */
    f32 offsetT;        /* 0x64 */
} Sprite2D;

#define SPRITE2D_FLIP_S      0x0002
#define SPRITE2D_FLIP_T      0x0004
#define SPRITE2D_ONE_PLAYER  0x0010 /* only drawn in the view of sprite->player */
#define SPRITE2D_HIDE_C35EA  0x0040 /* hidden while D_800C35EA == 1 */
#define SPRITE2D_SCALE_ST    0x0080
#define SPRITE2D_OFFSET_ST   0x0100
#define SPRITE2D_TEX_MODE0   0x0200 /* texture load mode 0 instead of 2 */
#define SPRITE2D_TEX_3E      0x0400 /* last texture load argument 0x3E instead of 3 */
/* bit 11 + view: only drawn while hud_lens_is_off(view) and screen_fade_alpha(view) <= 200 */

#define SPRITE_VIEW_F(v, off) (*(f32 *) ((v) + (off)))

extern struct_eu_80090F10 D_80090F10[];
extern u8 D_800A4EA8[];
extern s32 D_800D30BC;
s32 hud_lens_is_off(s32);
s32 screen_fade_alpha(s32);
Gfx *gfx_load_texture_cached(Gfx *, struct_eu_80090F10 *, s32, s32, s32, s32, s32, s32, s32, u8 *, s32);
Gfx *gfx_geometry_mode_cached(Gfx *, s32, s32);
void fx_calc_color_mode_a(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, s32);
void fx_calc_color_mode_b(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, s32);
Gfx *gfx_env_color_cached(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *gfx_prim_color_cached(Gfx *, s32, s32, s32, s32, s32, s32, u8 *);
Gfx *gfx_set_combine_mode(Gfx *, u8, u8 *);
Gfx *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);

/* Draws a 2D sprite in view `view`: texture, colours and render state through the helpers, then a scissored
 * texture rectangle around (x, y) +- (halfW, halfH) scaled to the view. */
/* was func_151552F0 */
Gfx *sprite2d_draw(Gfx *gdl, Sprite2D *spr, s16 view) {
    u8 ok;
    u8 *rec;
    s16 envR, envG, envB, envA;
    s16 primR, primG, primB, primA;
    struct_eu_80090F10 *tex;
    u32 *mode;
    f32 cx, cy, halfW, halfH, texW, texH;
    f32 right, left, bottom, top, w, h;
    s32 dsdx, dtdy, s, t;
    s32 xh, yh, xl, yl;

    ok = 1;
    rec = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
    if ((spr->flags & SPRITE2D_ONE_PLAYER) && spr->player != view) {
        return gdl;
    }
    if ((spr->flags & SPRITE2D_HIDE_C35EA) && D_800C35EA == 1) {
        return gdl;
    }
    if (spr->flags & (1 << (view + 11))) {
        if (hud_lens_is_off(view) == 0 || screen_fade_alpha(view) > 200) {
            return gdl;
        }
    }
    if (spr->tex != 0xFF) {
        gdl = gfx_load_texture_cached(gdl, &D_80090F10[spr->tex], 0, (spr->flags & SPRITE2D_TEX_MODE0) ? 0 : 2, 0, 0,
                            spr->tex, 0, 0, &ok, (spr->flags & SPRITE2D_TEX_3E) ? 0x3E : 3);
    }
    gdl = gfx_geometry_mode_cached(gdl, spr->geomSet, spr->geomClear);
    fx_calc_color_mode_a(&envR, &envG, &envB, &envA, spr->colB[0], spr->colB[1], spr->colB[2], spr->colB[3],
                  spr->colA[0], spr->colA[1], spr->colA[2], spr->colA[3], spr->colC, spr->fadeA);
    fx_calc_color_mode_b(&primR, &primG, &primB, &primA, spr->colB[0], spr->colB[1], spr->colB[2], spr->colB[3],
                  spr->colA[0], spr->colA[1], spr->colA[2], spr->colA[3], spr->colC, spr->fadeB);
    gdl = gfx_env_color_cached(gdl, primR, primG, primB, primA, &ok);
    gdl = gfx_prim_color_cached(gdl, 0, 0, envR, envG, envB, envA, &ok);
    gdl = gfx_set_combine_mode(gdl, spr->combine, &ok);
    mode = (u32 *) (D_800A4EA8 + spr->renderMode * 8);
    gdl = gfx_other_mode_cached(gdl, spr->otherMode | D_800D30BC | 0x2C00 | spr->otherMode2 | spr->otherMode3,
                        mode[1] | mode[0], &ok);

    cx = SPRITE_VIEW_F(rec, 0x34) + spr->x * SPRITE_VIEW_F(rec, 0x14);
    cy = SPRITE_VIEW_F(rec, 0x38) + spr->y * SPRITE_VIEW_F(rec, 0x18);
    halfW = spr->halfW * SPRITE_VIEW_F(rec, 0x14);
    halfH = spr->halfH * SPRITE_VIEW_F(rec, 0x18);
    tex = &D_80090F10[spr->tex];
    texW = tex->unk6;
    texH = tex->unk8;
    /* 10.2 fixed point corners */
    right = (cx + halfW) * 4.0f;
    left = (cx - halfW) * 4.0f;
    w = right - left + 1.0f;
    bottom = (cy + halfH) * 4.0f;
    top = (cy - halfH) * 4.0f;
    h = bottom - top + 1.0f;
    if (spr->flags & SPRITE2D_SCALE_ST) {
        w *= spr->scaleS;
        h *= spr->scaleT;
    }
    /* s5.10 steps */
    dsdx = (w == 0.0f) ? 0 : (s32) ((4096.0f * texW) / w);
    dtdy = (h == 0.0f) ? 0 : (s32) ((4096.0f * texH) / h);
    s = 0;
    t = 0;
    if (spr->flags & SPRITE2D_FLIP_S) {
        s = (tex->unk6 - 1) << 5;
        dsdx = -dsdx & 0xFFFF;
    }
    if (spr->flags & SPRITE2D_FLIP_T) {
        t = (tex->unk8 - 1) << 5;
        dtdy = -dtdy & 0xFFFF;
    }
    if (spr->flags & SPRITE2D_OFFSET_ST) {
        s = (s32) ((f32) s + spr->offsetS);
        t = (s32) ((f32) t + spr->offsetT);
    }
    xh = (s32) right;
    yh = (s32) bottom;
    xl = (s32) left;
    yl = (s32) top;
    gSPScisTextureRectangle(gdl++, xl, yl, xh, yh, G_TX_RENDERTILE, s, t, dsdx, dtdy);
    return gdl;
}

s32 sprite2d_find_overlap(u8 *, f32 *, s32, s32); /* P98: the asm reads a2 / a3 (the caller's arg2 / arg3, left in place) */
s32 memcpy(u8 *, u8 *, s32);

/* was func_151559FC */
u8 *sprite2d_spawn(u8 *arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    struct {
        f32 u2C;
        f32 u30;
        u8 * u34;
    } sp;
    s32 var_a0;
    u8 *temp_v0;

    if ((arg2 != 0) && (arg3 > 0)) {
        sp.u2C = (*(f32 *)((u8 *)arg0 + 8));
        sp.u30 = (*(f32 *)((u8 *)arg0 + 0xC));
        if (sprite2d_find_overlap(arg0, &sp.u2C, arg2, arg3) != 0) {
            return NULL;
        }
    }
    if ((*(u16 *)((u8 *)arg0 + 0x14)) & 0x20) {
        var_a0 = 0x57;
    } else {
        var_a0 = 0x5D;
    }
    temp_v0 = node_alloc(var_a0, arg6, arg4 + 0x70, 1, (u8) (s32) arg5, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp.u34 = temp_v0;
    memcpy(temp_v0 + 0x10, arg0, 0x58);
    (*(s8 *)((u8 *)sp.u34 + 0x68)) = 0;
    (*(s8 *)((u8 *)sp.u34 + 0x68)) = (s8) (0 | arg1);
    return sp.u34;
}
/* was func_15155AD4 */
void sprite2d_handle_message(u8 *arg0, s32 arg1, u8 arg2) {
    void (*fp)(void *, s32, u8) = D_8008B0A4[arg0[0x2A]];
    if (fp != NULL) {
        fp(arg0, arg1, arg2);
    }
}

// effect_overlap_find: whether a live effect of one of the `count` kinds in the s32 list `kinds` already overlaps the
// box around `spec` (centre spec +0 / +4, half sizes ext[0] / ext[1]): walks the effect lists 0x5D and 0x57 of both
// D_800DD280 banks; an effect (kind +0x2A, centre +0x10 / +0x14, half sizes +0x18 / +0x1C) overlaps when its centre
// lies within the summed half sizes on both axes (edges included). Returns 1 on the first overlap, else 0.
/* was func_15155B1C */
s32 sprite2d_find_overlap(u8 *spec, f32 *ext, s32 kinds, s32 count) {
    u8 *node;
    u8 *next;
    s32 bank;
    u8 j;
    s32 i;
    s32 found;
    f32 hx;
    f32 hy;
    f32 x;
    f32 y;

    for (bank = 0; bank < 2; bank++) {
        for (j = 0; j < 2; j++) {
            node = (u8 *) D_800DD280[bank][j == 0 ? 0x5D : 0x57]; // the asm copies {0x5D, 0x57} from .rodata
            while (node != NULL) {
                next = *(u8 **) (node + 8);
                found = 0;
                for (i = count; i > 0; i--) {
                    if (node[0x2A] == ((s32 *) kinds)[i - 1]) {
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    hx = *(f32 *) (node + 0x18) + ext[0];
                    hy = *(f32 *) (node + 0x1C) + ext[1];
                    x = *(f32 *) (spec + 0);
                    if (x - hx <= *(f32 *) (node + 0x10) && *(f32 *) (node + 0x10) <= x + hx) {
                        y = *(f32 *) (spec + 4);
                        if (y - hy <= *(f32 *) (node + 0x14) && *(f32 *) (node + 0x14) <= y + hy) {
                            return 1;
                        }
                    }
                }
                node = next;
            }
        }
    }
    return 0;
}

/* was func_15155C9C */
void sprite2d_broadcast(void *arg0, u8 arg1) {
    const s32 sp18[2] = {0x5D, 0x57};

    node_broadcast_types(sp18, 0x2, (s32)arg0, arg1);
}
