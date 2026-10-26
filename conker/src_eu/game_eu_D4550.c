#include <ultra64.h>
#include "functions.h"
#include "variables.h"
/* The vertices are written and handed to the RSP through KSEG1 (uncached); wasm has no such segment. */
#ifdef PORT
#define SPRITE_UNCACHED(p) ((u32) (p))
#else
#define SPRITE_UNCACHED(p) ((u32) (p) | 0xA0000000)
#endif


/* P133 */
s32 sprite_load_texture(s32, s32, s32, s32, s32, s32, s32, s32, s32);
f32 math_sin_u8(u8);
f32 math_cos_u8(u8);
extern u8 *g_sprite_tex_descs[]; /* was D_8008CDEC */
extern f32 g_billboard_yaw_sincos[2]; /* camera yaw: [0] sin, [1] cos (node_billboard_draw's caller in game_1944C0.c); was D_800DD600 */
extern s32 g_sprite_last_tex;    /* last sprite texture: the hand asm keeps it in the upper half (lh / sh); was D_800DD5E4 */
extern s32 g_sprite_last_frame;    /* last sprite frame: upper half, as g_sprite_last_tex; was D_800DD5E4; was D_800DD5E8 */
extern s16 g_sprite_last_other_mode;    /* last sprite other-mode (1 / 2 / 3); was D_800DD5EC */
extern s32 g_gfx_tlut_mode;    /* TLUT bit of the last loaded texture (gfx_load_texture_tile); was D_800D30BC */

/* cvt.w.s with the default FCSR mode: round to nearest, ties to even (|f| < 2^31) */
#define SPRITE_RINT(f)                                                                                     \
    (((f) >= 8388608.0f || (f) <= -8388608.0f) ? (s32) (f)                                                 \
     : ((f) >= 0.0f) ? (s32) (((f) + 8388608.0f) - 8388608.0f)                                            \
                     : -(s32) ((-(f) + 8388608.0f) - 8388608.0f))
#define SPRITE_GFX(g, hi, lo) ((g)->words.w0 = (hi), (g)->words.w1 = (lo), (g)++)

/*
 * sprite_billboard_draw: draws a camera-facing sprite quad (hand asm). rec + 0x10 is the sprite: s16 frame
 * (+0x98, frame index = the value >> 8), s16 x/y/z (+0x9C/+0x9E/+0xA0), s16 half width (+0xA2) and half height
 * (+0xA4), u16 flags (+0xA8), u16 roll / pitch angles (+0xAC/+0xAE, byte angle in the upper byte), u8 sprite
 * index into g_sprite_tex_descs (+0xB0), u8 prim alpha (+0xB4); four Vtx per frame buffer at rec + 0x10 + g_dl_buf_index * 0x40.
 * Flags: 0x8000 hidden while bit 0 of word +0x5F0 of the 0x9A0 record idx is set (Rare's asm takes that record
 * from the address of g_player_views, not from the pointer it holds), 0x200 / 0x4000 quad above / below the origin,
 * 0x8 / 0x10 / 0x400 / 0x1000 / 0x2000 combine modes, 0x800 prim alpha, 0x20 / 0x2000 other modes.
 * Loads the texture (sprite_load_texture) when the texture or frame changed; the combine / other mode / alpha commands
 * only when they differ from the last sprite's (g_sprite_last_combine, g_sprite_last_other_mode, g_gfx_prim_a_cached); a pipe sync precedes the
 * first mode change when no texture load did. Then the 4 vertices (camera yaw g_billboard_yaw_sincos, optional roll and
 * pitch rotations, rounded, plus the position) and the triangles (0, 2, 1), (0, 3, 2).
 */
/* was func_150A6D40 */
Gfx *sprite_billboard_draw(Gfx *gfx, u8 *rec, s32 idx) {
    u8 *spr = rec + 0x10;
    u16 flags = *(u16 *) (spr + 0x98);
    s32 *desc;
    s32 tex, frame;
    s32 noLoad;
    s32 roll, pitch;
    f32 rollC, rollS, pitchC, pitchS;
    f32 v[4][3];
    f32 w, h, a, b, lo, hi, t;
    s16 *vtx;
    u32 vtxAddr;
    s32 px, py, pz;
    s32 i, mode;

    if ((flags & 0x8000) && (*(s32 *) ((u8 *) &g_player_views + idx * 0x9A0 + 0x5F0) & 1)) {
        return gfx;
    }

    /* texture: the descriptor's first word is a texture, or (>= 0x10000000) a table of one per frame */
    desc = (s32 *) g_sprite_tex_descs[spr[0xA0]];
    frame = (u32) (s32) *(s16 *) (spr + 0x88) >> 8;
    tex = desc[0];
    if (tex >= 0x10000000) {
        tex = ((s32 *) tex)[frame];
        frame = 0;
    }
    if (tex == (s16) (g_sprite_last_tex >> 16) && frame == (s16) (g_sprite_last_frame >> 16)) {
        noLoad = TRUE;
    } else {
        g_sprite_last_tex = (g_sprite_last_tex & 0xFFFF) | (tex << 16);
        noLoad = FALSE;
        g_sprite_last_frame = (g_sprite_last_frame & 0xFFFF) | (frame << 16);
        /* the asm leaves its caller's s0 (a KSEG0 pointer, so a negative age) as the 9th argument */
        gfx = (Gfx *) sprite_load_texture((s32) gfx, (s32) desc, *(s16 *) (spr + 0x88), 0, 0, 0, 0, 2, (s32) 0x80000000);
    }

    roll = *(u16 *) (spr + 0x9C) >> 8;
    pitch = *(u16 *) (spr + 0x9E) >> 8;
    if (roll != 0) {
        rollC = math_sin_u8(roll);
        rollS = math_cos_u8(roll);
    }
    if (pitch != 0) {
        pitchC = math_sin_u8(pitch);
        pitchS = math_cos_u8(pitch);
    }

    /* the quad in camera yaw: (a, -b) and (-a, b) horizontally, lo..hi vertically */
    w = *(s16 *) (spr + 0x92);
    a = w * g_billboard_yaw_sincos[1];
    b = w * g_billboard_yaw_sincos[0];
    h = *(s16 *) (spr + 0x94);
    if (flags & 0x200) {
        lo = 0.0f;
        hi = h * 2.0f;
    } else if (flags & 0x4000) {
        lo = h * -2.0f;
        hi = 0.0f;
    } else {
        lo = -h;
        hi = h;
    }
    v[0][0] = a;  v[0][1] = lo; v[0][2] = -b;
    v[1][0] = -a; v[1][1] = lo; v[1][2] = b;
    v[2][0] = -a; v[2][1] = hi; v[2][2] = b;
    v[3][0] = a;  v[3][1] = hi; v[3][2] = -b;
    if (roll != 0) {
        for (i = 0; i < 4; i++) {
            t = v[i][1] * rollS + v[i][2] * rollC;
            v[i][2] = v[i][2] * rollS - v[i][1] * rollC;
            v[i][1] = t;
        }
    }
    if (pitch != 0) {
        for (i = 0; i < 4; i++) {
            t = v[i][1] * pitchS + v[i][0] * pitchC;
            v[i][0] = v[i][0] * pitchS - v[i][1] * pitchC;
            v[i][1] = t;
        }
    }
    px = *(s16 *) (spr + 0x8C);
    py = *(s16 *) (spr + 0x8E);
    pz = *(s16 *) (spr + 0x90);
    vtx = (s16 *) (spr + (s8) g_dl_buf_index * 0x40);
    vtxAddr = SPRITE_UNCACHED(vtx);
    vtx = (s16 *) vtxAddr;
    for (i = 0; i < 4; i++) {
        vtx[i * 8 + 0] = SPRITE_RINT(v[i][0]) + px;
        vtx[i * 8 + 1] = SPRITE_RINT(v[i][1]) + py;
        vtx[i * 8 + 2] = SPRITE_RINT(v[i][2]) + pz;
        vtx[i * 8 + 3] = 0;
    }

    /* combine mode */
    if (flags & 8) {
        mode = 1;
    } else if (flags & 0x10) {
        mode = 2;
    } else if (flags & 0x400) {
        mode = 4;
    } else if (flags & 0x1000) {
        mode = 5;
    } else if (flags & 0x2000) {
        mode = 6;
    } else {
        mode = 0;
    }
    /* with no mode flag the asm compares a leftover 64-bit register, (u16) vtx[3].y << 32: equal only when 0 */
    if (g_sprite_last_combine != mode || (mode == 0 && vtx[3 * 8 + 1] != 0)) {
        g_sprite_last_combine = mode;
        if (noLoad) {
            SPRITE_GFX(gfx, 0xE7000000, 0); /* gDPPipeSync */
        }
        noLoad = FALSE;
        if (mode == 1) {
            SPRITE_GFX(gfx, 0xFC121824, 0xFF33FFFF); /* gDPSetCombine */
        } else if (mode == 2) {
            SPRITE_GFX(gfx, 0xFCFFFFFF, 0xFFFCF279);
        } else if (mode == 4) {
            SPRITE_GFX(gfx, 0xFC123224, 0xFF67FFFF);
        } else if (mode == 5) {
            SPRITE_GFX(gfx, 0xFCFFB3FF, 0xFF667F3F);
        } else if (mode == 6) {
            SPRITE_GFX(gfx, 0xEF182C0F, 0x0C184B50); /* gDPSetOtherMode */
            SPRITE_GFX(gfx, 0xFC1235FF, 0xFFFFFE38);
        } else {
            SPRITE_GFX(gfx, 0xFCFF99FF, 0xFF327F3F);
        }
    }

    /* prim alpha */
    if ((flags & 0x800) && g_gfx_prim_a_cached != spr[0xA4]) {
        g_gfx_prim_a_cached = spr[0xA4];
        SPRITE_GFX(gfx, 0xFA000000, spr[0xA4]); /* gDPSetPrimColor(0, 0, 0, 0, 0, alpha) */
    }

    /* other mode (with the texture's TLUT bit); mode 3 leaves the 0x2C other mode set above */
    if (flags & 0x20) {
        mode = 1;
    } else if (flags & 0x2000) {
        mode = 3;
    } else {
        mode = 2;
    }
    if (g_sprite_last_other_mode != mode) {
        g_sprite_last_other_mode = mode;
        if (mode != 3) {
            if (noLoad) {
                SPRITE_GFX(gfx, 0xE7000000, 0); /* gDPPipeSync */
            }
            if (mode == 1) {
                SPRITE_GFX(gfx, 0xEF082C0F | g_gfx_tlut_mode, 0x0F0A3238);
            } else {
                SPRITE_GFX(gfx, 0xEF082C0F | g_gfx_tlut_mode, 0x00504B50);
            }
        }
    }

    SPRITE_GFX(gfx, 0x01004008, vtxAddr); /* gSPVertex(vtx, 4, 0) */
    SPRITE_GFX(gfx, 0x05000402, 0);       /* gSP1Triangle(0, 2, 1) */
    SPRITE_GFX(gfx, 0x05000604, 0);       /* gSP1Triangle(0, 3, 2) */
    return gfx;
}
