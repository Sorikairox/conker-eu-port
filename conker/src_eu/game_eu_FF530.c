#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
Gfx *render_set_color_image(Gfx *);
Gfx *gfx_load_texture_tile(Gfx *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
void matrix_rotate_ypr(f32 (*)[4], f32, f32, f32);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern s32 D_800DC2E0;
extern Vtx *D_800DC2B8[][2];

/* P64: texture descriptor passed to gfx_load_texture_tile (the texture load) */
typedef struct {
    s32 image;   /* D_800DC2B0 */
    s16 fmt;     /* 4 */
    s16 width;   /* 0x100 */
    u8  b8;
    u8  b9;      /* 3 */
    u8  bA;
} TexDesc_D1D20;

/* P64: draws a scrolling textured quad over the view of player D_80082FA4 (word 0 = player index, half +2 = a
 * parameter of render_set_scissor): texture, pipe sync, other modes and combiner, render_set_scissor / render_set_color_image,
 * the texture load (gfx_load_texture_tile), then the player's view matrix (D_800BE628[p] +0xBC, 0x180-byte records)
 * multiplied by a Z rotation `angle` (matrix_rotate_ypr) into the frame's Mtx D_800DC2E0[p * 2 + D_800BE9C0],
 * D_80089810 as the projection, perspective normalisation D_800BE628[p] +0xB8 and the 4 vertices
 * D_800DC2B8[p][D_800BE9C0] whose t coordinates are scrolled by `scroll` * 81 (top / bottom rows depend on the
 * level D_800BE9F0: 0x32 / 0x33 / 0x3F use -0x62 / 0x27, else -0x13 / 0x65), drawn as two triangles. */
/* P243: D_80089578 camera callback: takes the dispatcher's 8 arguments (view_background_draw passes gdl, x, y, z, yaw, pitch,
 * roll, handle); only yaw (= scroll) and roll (= angle) are used. Was 7 arguments with s32 x / y / z / pitch: same o32
 * slots, but a wasm signature mismatch through the table. */
/* was func_150D1D20 */
Gfx *view_scroll_overlay_draw(Gfx *gdl, f32 x, f32 y, f32 z, f32 scroll, f32 pitch, f32 angle, s32 handle) {
    TexDesc_D1D20 tex;
    f32 view[4][4];
    f32 rot[4][4];
    s32 top, bottom;
    s32 t;
    s32 p;
    Vtx *v;
    Mtx *mtx;
    u8 *player;

    if (D_800BE9F0 == 0x33 || D_800BE9F0 == 0x32 || D_800BE9F0 == 0x3F) {
        top = -0x62;
        bottom = 0x27;
    } else {
        top = -0x13;
        bottom = 0x65;
    }
    tex.fmt = 4;
    tex.width = 0x100;
    tex.b8 = 0;
    tex.b9 = 3;
    tex.bA = 0;
    tex.image = D_800DC2B0;

    gdl->words.w0 = 0xD7000002; gdl->words.w1 = 0xFFFFFFFF; gdl++;    /* gSPTexture(0xFFFF, 0xFFFF, 0, 0, G_ON) */
    gdl->words.w0 = 0xE7000000; gdl->words.w1 = 0; gdl++;             /* gDPPipeSync */
    gdl->words.w0 = 0xEF082C0F; gdl->words.w1 = 0x0F0A4004; gdl++;    /* gDPSetOtherMode */
    gdl->words.w0 = 0xFCFFFFFF; gdl->words.w1 = 0xFFFCF279; gdl++;    /* gDPSetCombineMode */
    gdl = (Gfx *)render_set_scissor((s32)gdl, ((s16 *)&D_80082FA4)[1], 0, 0, 0, 0);
    gdl = render_set_color_image(gdl);
    gdl = gfx_load_texture_tile(gdl, &tex, 0, 0, 0, 0, 2, 0x100, 0x100, 3);

    matrix_rotate_ypr(rot, 0.0f, 0.0f, angle);
    p = D_80082FA4;
    player = (u8 *)D_800BE628 + p * 0x180;
    mtxf_mul(rot, (f32 (*)[4])(player + 0xBC), view);
    mtx = (Mtx *)D_800DC2E0 + (D_80082FA4 * 2 + D_800BE9C0);
    guMtxF2L(view, mtx);

    gdl->words.w0 = 0xDA380007; gdl->words.w1 = (u32)((Mtx *)D_800DC2E0 + (D_80082FA4 * 2 + D_800BE9C0)); gdl++;
    gdl->words.w0 = 0xDA380003; gdl->words.w1 = (u32)D_80089810; gdl++;                 /* gSPMatrix (projection) */
    gdl->words.w0 = 0xDB0E0000;                                                         /* gSPPerspNormalize */
    gdl->words.w1 = *(u16 *)((u8 *)D_800BE628 + D_80082FA4 * 0x180 + 0xB8);
    gdl++;

    t = (s32)(scroll * 81.0f);
    v = D_800DC2B8[D_80082FA4][D_800BE9C0];
    v[0].v.tc[1] = v[1].v.tc[1] = ((top + 0x100) << 5) + t;
    v[2].v.tc[1] = v[3].v.tc[1] = ((bottom + 0x1FF) << 5) + t;
    gdl->words.w0 = 0x01004008; gdl->words.w1 = (u32)v; gdl++;     /* gSPVertex(v, 4, 0) */
    gdl->words.w0 = 0x06000204; gdl->words.w1 = 0x406; gdl++;      /* gSP2Triangles(0,1,2, 0,2,3) */
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FF530/view_scroll_overlay_draw.s")
#endif
