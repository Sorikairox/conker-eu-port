#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15095F18(s32, f32, f32, f32, s32, s32 *);
#endif

Gfx *func_15095350(Gfx *arg0) {
    gSPDisplayList(arg0++, D_80087770);
    D_800D30C0 = 0;
    return arg0;
}

void func_15095470(s32, s32, s32);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30B0;

#ifdef NON_MATCHING
/* NON_MATCHING: the matching void wrappers return the callee's v0 (the new display-list pointer), which callers use. */
s32 func_15095380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15095470(arg1, arg2, arg3);
    return func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, 0x100, 0x100, arg8);
}
#else
void func_15095380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15095470(arg1, arg2, arg3);
    func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, 0x100, 0x100, arg8);
}
#endif

void func_15095470(s32, s32, s32);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30B0;

#ifdef NON_MATCHING
/* NON_MATCHING: the matching void wrappers return the callee's v0 (the new display-list pointer), which callers use. */
s32 func_150953F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    func_15095470(arg1, arg2, arg3);
    return func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, arg8, arg9, argA);
}
#else
void func_150953F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    func_15095470(arg1, arg2, arg3);
    func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, arg8, arg9, argA);
}
#endif

void func_15095470(s32 arg0, s32 arg1, s32 arg2) {
    u32 temp_v0;
    if (arg2 != 0) {
        (*(s32 **)((u8 *)arg2 + 0x10)) = &D_800D30B0;
    }
    temp_v0 = (*(u32 *)((u8 *)arg0 + 0));
    if (temp_v0 < 0x10000000U) {
        (*(s32 *)((u8 *)(&D_800D30B0) + 0)) = (s32) temp_v0;
    } else {
        (*(s32 *)((u8 *)(&D_800D30B0) + 0)) = *(s32 *)((u8 *)((s32)temp_v0 + ((arg1 >> 8) * 4)));
    }
    (*(u16 *)((u8 *)(&D_800D30B0) + 4)) = (u16) (*(u16 *)((u8 *)arg0 + 6));
    (*(u16 *)((u8 *)(&D_800D30B0) + 6)) = (u16) (*(u16 *)((u8 *)arg0 + 8));
    (*(u8 *)((u8 *)(&D_800D30B0) + 8)) = (u8) (*(u8 *)((u8 *)arg0 + 0xA));
    (*(u8 *)((u8 *)(&D_800D30B0) + 9)) = (u8) (*(u8 *)((u8 *)arg0 + 0xB));
    (*(u8 *)((u8 *)(&D_800D30B0) + 0xA)) = (u8) (*(u8 *)((u8 *)arg0 + 4));
}

#ifdef NON_MATCHING
/* Texture loader behind func_15095380 / func_150953F8 (the sky quad, sprites, ...): appends the display-list
 * commands that load the texture `tex` into TMEM at `tmem` and set up render tile `tile`, and returns the new
 * display-list end. `tex` is the descriptor func_15095470 fills (D_800D30B0): +0 address, or an asset id below
 * 0x10000000 that the texture cache resolves (func_1510D66C with `age`), +4 width, +6 height, +8 format (G_IM_FMT_*;
 * 5 = RGBA texels followed by an I4 plane that goes to tile + 1), +9 texel size (G_IM_SIZ_*), +0xA animated flag
 * (`frame` selects one of several equal textures stored after each other; 0 when not animated). The address used
 * is kept in D_800D30C0. Clamp / mirror `cm` applies to s and t; the tile rectangle starts at (uls, ult) with the
 * s fraction `sfrac` (10.2). For CI textures the palette after the texels is loaded too (D_800D30BC = 0x8000,
 * the CI flag for the caller's render mode; 0 otherwise). Note the I4 tile's ult is not shifted by 2 (as the
 * original). */
s32 func_1510D66C(s32 id, s32 *outSize, s32 age, s32 addRef);
extern s32 D_800D30BC;

static const u8 s954E4_incr[4] = { G_IM_SIZ_4b_INCR, G_IM_SIZ_8b_INCR, G_IM_SIZ_16b_INCR, G_IM_SIZ_32b_INCR };
static const u8 s954E4_shift[4] = { G_IM_SIZ_4b_SHIFT, G_IM_SIZ_8b_SHIFT, G_IM_SIZ_16b_SHIFT, G_IM_SIZ_32b_SHIFT };
static const u8 s954E4_lineBytes[4] = { 1, 1, 2, 2 };   /* D_8009E288: line = (bytes * lineW + 7) / 8 */
static const u8 s954E4_loadSiz[4] = { G_IM_SIZ_4b_LOAD_BLOCK, G_IM_SIZ_8b_LOAD_BLOCK, G_IM_SIZ_16b_LOAD_BLOCK,
                                      G_IM_SIZ_32b_LOAD_BLOCK };

s32 func_150954E4(s32 gfxAddr, s32 *tex, s32 tmem, s32 tile, s32 frame, s32 sfrac, s32 cm, s32 uls, s32 ult,
                  s32 age) {
    Gfx *gfx = (Gfx *)gfxAddr;
    u8 *t = (u8 *)tex;
    s32 width, height, fmt, siz, imgFmt;
    s32 texels, words, lineW, masks, maskt, n, line, lrs, lrt, ulsFixed;
    s32 addr;
    s32 palBits, palCount;

    if (t[0xA] == 0) {
        frame = 0;
    }
    width = *(u16 *)(t + 4);
    height = *(u16 *)(t + 6);
    siz = t[9];
    texels = width * height;
    words = s954E4_incr[siz] + texels;
    if (t[8] == 5) {
        words += texels / 4;   /* the I4 plane */
    }
    words >>= s954E4_shift[siz];

    addr = *(s32 *)t;
    D_800D30C0 = addr;
    if ((u32)addr < 0x10000000) {
        D_800D30C0 = func_1510D66C(addr, NULL, age, 0);
        addr = D_800D30C0;
    }
    if (addr != (s32)0x80000000) {
        D_800D30C0 = addr + words * 2 * frame;
    }

    lineW = (siz == G_IM_SIZ_4b) ? width >> 1 : width;
    for (masks = 1, n = 2; n < width; n <<= 1) {
        masks++;
    }
    for (maskt = 1, n = 2; n < height; n <<= 1) {
        maskt++;
    }
    fmt = t[8];
    imgFmt = (fmt == 5) ? G_IM_FMT_RGBA : fmt;

    gDPPipeSync(gfx++);
    gDPSetTextureImage(gfx++, imgFmt, s954E4_loadSiz[t[9]], 1, D_800D30C0);
    gDPSetTile(gfx++, imgFmt, s954E4_loadSiz[t[9]], 0, tmem, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, words - 1, 0);
    siz = t[9];
    line = (s954E4_lineBytes[siz] * lineW + 7) >> 3;
    gDPSetTile(gfx++, imgFmt, siz, line, tmem, tile, 0, cm, maskt, 0, cm, masks, 0);
    ulsFixed = uls * 4 + sfrac;
    lrs = (*(u16 *)(t + 4) + uls - 1) * 4 + sfrac;
    lrt = (*(u16 *)(t + 6) + ult - 1) * 4;
    gDPSetTileSize(gfx++, tile, ulsFixed, ult * 4, lrs, lrt);
    if (t[8] == 5) {
        line = (s954E4_lineBytes[G_IM_SIZ_4b] * (lineW >> 1) + 7) >> 3;
        gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_4b, line, tmem + lineW * *(u16 *)(t + 6) / 4, tile + 1, 0, cm, maskt,
                   0, cm, masks, 0);
        lrs = (*(u16 *)(t + 4) + uls - 1) * 4 + sfrac;
        lrt = (*(u16 *)(t + 6) + ult - 1) * 4;
        gDPSetTileSize(gfx++, tile + 1, ulsFixed, ult, lrs, lrt);
    }
    if (t[8] == G_IM_FMT_CI) {
        if (t[9] == G_IM_SIZ_4b) {
            palBits = 4;
            palCount = 15;
        } else {
            palBits = 8;
            palCount = 255;
        }
        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,
                           D_800D30C0 + *(u16 *)(t + 4) * *(u16 *)(t + 6) * palBits / 8);
        gDPLoadSync(gfx++);
        gDPLoadTLUTCmd(gfx++, 6, palCount);
        D_800D30BC = 0x8000;
    } else {
        D_800D30BC = 0;
    }
    return (s32)gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_150954E4.s")
#endif

#ifdef NON_MATCHING
void func_150A7EE0(u8 *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern u8 D_800D30C8[][0x40];   /* view matrices per player */
extern f32 D_800D9F40;
#endif
#ifdef NON_MATCHING
/* Projects the world point (x, y, z) with the current player's view matrix D_800D30C8[D_80082FA4]
 * (func_150A7EE0 -> *sx, *sy, *sz, *w). Behind / too far (w >= far) or too near (w <= D_800D9F40): returns 0.
 * Else *sx / *sy become screen coordinates of that player's viewport (D_800BE628 + player * 0x180: half
 * sizes +0x0C / +0x10 (+ 5), centre +0x34 / +0x38; y points down) and it returns 1. */
s32 func_15095A4C(f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz, f32 *w, f32 far) {
    u8 *vp;
    f32 inv;
    f32 px;
    f32 py;

    func_150A7EE0(D_800D30C8[D_80082FA4], x, y, z, sx, sy, sz, w);
    if (far <= *w || *w <= D_800D9F40) {
        return 0;
    }
    inv = 1.0f / *w;
    vp = (u8 *)D_800BE628 + D_80082FA4 * 0x180;
    px = *sx;
    py = *sy;
    *sx = (*(f32 *)(vp + 0xC) + 5.0f) * px * inv + *(f32 *)(vp + 0x34);
    *sy = *(f32 *)(vp + 0x38) - (*(f32 *)(vp + 0x10) + 5.0f) * py * inv;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095A4C.s")
#endif

#ifdef NON_MATCHING
s32 func_15095A4C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);

u8 *func_15095B70(u8 *arg0, u8 *arg1) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
    } sp;
    u8 *temp_a0;
    u8 *temp_t0;

    if (func_15095A4C((f32) (*(s16 *)((u8 *)arg1 + 0)), (f32) (*(s16 *)((u8 *)arg1 + 2)), (f32) (*(s16 *)((u8 *)arg1 + 4)), &sp.u44, &sp.u40, &sp.u3C, &sp.u38, 4000.0f) == 0) {
        return arg0;
    }
    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_a0 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xEE000000;
    temp_t0 = D_800BE628 + (D_80082FA4 * 0x180) + (D_800BE9C0 * 0x10);
    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) ((s32) (((f32) (*(s16 *)((u8 *)temp_t0 + 0x4C)) + ((sp.u3C / sp.u38) * (f32) (*(s16 *)((u8 *)temp_t0 + 0x44)))) * 32.0f) << 0x10);
    return func_15095EA0((s32) (temp_a0 + 8), (s32) arg1, sp.u44, sp.u40, sp.u38, 1, 0, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095B70.s")
#endif
#ifdef NON_MATCHING
s32 func_15095A4C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);

u8 *func_15095CC0(u8 *arg0, u8 *arg1, s32 *arg2) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
    } sp;
    u8 *temp_s0;
    u8 *var_s0;

    var_s0 = arg0;
    if (func_15095A4C((f32) (*(s16 *)((u8 *)arg1 + 0)), (f32) (*(s16 *)((u8 *)arg1 + 2)), (f32) (*(s16 *)((u8 *)arg1 + 4)), &sp.u44, &sp.u40, &sp.u3C, &sp.u38, 4000.0f) == 0) {
        *arg2 = 0;
        return var_s0;
    }
    func_15095F18((s32) arg1, sp.u44, sp.u40, sp.u38, 1, arg2);
    if (*arg2 != 0) {
        temp_s0 = var_s0 + 8;
        (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)var_s0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_s0 + 0)) = 0xEE000000;
        var_s0 = temp_s0 + 8;
        (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) ((u32) (((sp.u3C / sp.u38) * 16352.0f) + 16352.0f) << 0x10);
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095CC0.s")
#endif
#ifdef NON_MATCHING
/* NON_MATCHING: the matching void wrappers return the callee's v0 (the new display-list pointer), which callers use. */
s32 func_15095EA0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
s32 func_15095E58(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    return func_15095EA0(arg0, arg1, arg2, arg3, 4096.0f, 0, 0, 0, 0);
}
#else
void func_15095E58(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    func_15095EA0(arg0, arg1, arg2, arg3, 4096.0f, 0, 0, 0, 0);
}
#endif

void func_15095F18(s32, f32, f32, f32, s32, s32 *);
s32 func_15096144(s32, s32, s32, s32, s32);
s32 func_15095EA0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 sp24;
    func_15095F18(arg1, arg2, arg3, arg4, arg5, &sp24);
    if (sp24 != 0) {
        arg0 = func_15096144(arg0, arg1, arg6, arg7, arg8);
    }
    return arg0;
}

#ifdef NON_MATCHING
/* P139 */
extern f32 D_80038400;     /* sprite size units -> screen x */
extern f32 D_80038404;     /* sprite size units -> screen y */
extern f32 D_800D3090;     /* last sprite rect: x scale */
extern f32 D_eu_800D3094;  /* y scale */
extern f32 D_800D309C;     /* top (D_800D3098 = left, declared as a struct array in variables.h) */
extern f32 D_800D30A0;     /* depth */
extern f32 D_800D30A4;     /* width */
extern f32 D_800D30A8;     /* height */

/*
 * sprite_screen_rect: screen rectangle of the sprite `spr` (s16 scale +6 / +8, texture +0x10 with u16 size +4 / +6)
 * centred on the screen point (sx, sy) at depth w, in the current player's viewport (D_800BE628 + D_80082FA4 *
 * 0x180; scales +0x14 / +0x18, or +0x1C / +0x20 when alt): width = tex w * (scale x * D_80038400 * vp scale) / w,
 * height likewise. *visible = 1 when the rectangle overlaps the viewport's clip box (x: +0x2C..+0x30, y:
 * +0x24..+0x28), else 0. The scales, corner, depth and size are left in D_800D3090..D_800D30A8 for the sprite
 * drawer. Nothing but *visible = 0 happens when a scale is 0. (void: the file prototypes said s32, no caller used it).
 */
void func_15095F18(s32 sprArg, f32 sx, f32 sy, f32 w, s32 alt, s32 *visible) {
    u8 *spr = (u8 *) sprArg;
    u8 *vp;
    u8 *tex;
    f32 scaleX;
    f32 scaleY;
    f32 inv;
    f32 width;
    f32 height;
    f32 left;
    f32 top;

    *visible = 0;
    if (*(s16 *) (spr + 6) == 0 || *(s16 *) (spr + 8) == 0) {
        return;
    }
    scaleX = (f32) *(s16 *) (spr + 6) * D_80038400;
    scaleY = (f32) *(s16 *) (spr + 8) * D_80038404;
    if (alt != 0) {
        vp = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
        scaleX *= *(f32 *) (vp + 0x1C);
        scaleY *= *(f32 *) (vp + 0x20);
    } else {
        vp = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
        scaleX *= *(f32 *) (vp + 0x14);
        scaleY *= *(f32 *) (vp + 0x18);
    }
    tex = *(u8 **) (spr + 0x10);
    inv = 1.0f / w;
    width = (f32) *(u16 *) (tex + 4) * scaleX * inv;
    height = (f32) *(u16 *) (tex + 6) * scaleY * inv;
    left = sx - width * 0.5f;
    top = sy - height * 0.5f;
    if (*(f32 *) (vp + 0x2C) <= left + width && left < *(f32 *) (vp + 0x30) && *(f32 *) (vp + 0x24) <= top + height &&
        top < *(f32 *) (vp + 0x28)) {
        *visible = 1;
    }
    D_800D3090 = scaleX;
    D_eu_800D3094 = scaleY;
    *(f32 *) D_800D3098 = left;
    D_800D309C = top;
    D_800D30A0 = w;
    D_800D30A4 = width;
    D_800D30A8 = height;
    return;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095F18.s")
#endif

#ifdef NON_MATCHING
/* NON_MATCHING: the matching void wrappers return the callee's v0 (the new display-list pointer), which callers use. */
s32 func_1509611C(s32 arg0, s32 arg1) {
    return func_15096144(arg0, arg1, 0, 0, 0);
}
#else
void func_1509611C(s32 arg0, s32 arg1) {
    func_15096144(arg0, arg1, 0, 0, 0);
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15096144.s")

#ifdef NON_MATCHING
/* P142 */
/* image_draw_tiled: draws the image described by img (the func_15095470 descriptor: +0 address or asset id, +4
 * animated flag, +6 tile width, +8 tile height, +0xA format, +0xB texel size) as a grid of textured rectangles.
 * The picture is w x h texels split into tiles of img's size whose asset ids follow each other (column-major,
 * frame * cols * rows first); with flags & 1 each tile has a 1-texel border on every side (the step is 2 smaller,
 * the s / t start skips the fraction). flags & 2 / & 4 mirror in x / y (negative dsdx / dtdy, s / t from the far
 * edge). (x, y) is the screen centre (10.2 units are made here), scaleX / scaleY are 4096-based (pixels per texel
 * * 4096); sOff is added to the s start, xAdd widens each rectangle's right edge. The top row and the right column
 * hold the remainders. Off-screen left / top edges are clipped with the matching s / t correction. Returns the new
 * display-list end. */
typedef struct {
    s32 tex;        // address or asset id
    u8 animated;
    u8 pad5;
    u16 width;
    u16 height;
    u8 fmt;
    u8 siz;
} ImageTileDesc;

// s / t start correction of a bordered tile: skips the sub-pixel part of the screen coordinate v (10.5 texels)
#define IMAGE_TILE_BORDER_FIX(v, scale) ((s32) (32.0f - ((v) - (f32) (s32) (v)) * 32.0f * (4096.0f / (scale))))

u32 *func_150966AC(u32 *gfx, ImageTileDesc *img, f32 scaleX, f32 scaleY, f32 x, f32 y, s32 w, s32 h, s32 flags, s32 sOff, s32 xAdd, s32 frame) {
    ImageTileDesc tile;
    s32 border;
    s32 tileW;
    s32 tileH;
    s32 s0;
    s32 t0;
    s32 dsdx;
    s32 dtdy;
    s32 cols;
    s32 rows;
    s32 colW;
    s32 topH;
    s32 i;
    s32 j;
    s32 sStart;
    s32 tStart;
    s32 xi;
    s32 yi;
    s32 uly;
    s32 sFix;
    s32 tFix;
    s16 ulx;
    s16 lrx;
    s16 lry;
    s16 clipX;
    s16 clipY;
    u32 dsdt;
    f32 nextX;
    f32 nextY;
    f32 curY;
    f32 rowScreenH;
    f32 topScreenH;

    tileW = img->width;
    tileH = img->height;
    border = flags & 1;
    if (border) {
        tileW -= 2;
        tileH -= 2;
    }
    if (flags & 2) {
        s0 = (img->width + 0xFF) << 5;
        dsdx = (s32) (-4194304.0f / scaleX) & 0xFFFF;
    } else {
        s0 = 0x2000;
        dsdx = (s32) (4194304.0f / scaleX);
    }
    if (flags & 4) {
        t0 = (img->height + 0xFF) << 5;
        dtdy = (s32) (-4194304.0f / scaleY) & 0xFFFF;
    } else {
        t0 = 0x2000;
        dtdy = (s32) (4194304.0f / scaleY);
    }
    cols = (w + tileW - 1) / tileW;
    rows = (h + tileH - 1) / tileH;
    x -= (f32) w * scaleX / 8192.0f;
    tile.tex = img->tex;
    tile.tex += frame * cols * rows;
    y -= (f32) h * scaleY / 8192.0f;
    tile.width = img->width;
    tile.fmt = img->fmt;
    tile.animated = 1;
    tile.siz = img->siz;
    topH = h - (rows - 1) * tileH;
    colW = tileW;
    topScreenH = (f32) topH * scaleY / 4096.0f;
    for (i = 0; i < cols; i++) {
        rowScreenH = topScreenH;
        curY = y;
        tile.height = topH;
        if (i + 1 == cols) {
            colW = w - (cols - 1) * tileW;
            tile.width = colW;
            if (border) {
                tile.width = (u16) colW + 2;
            }
        }
        sStart = s0;
        nextX = x + (f32) colW * scaleX / 4096.0f;
        if (border) {
            sStart = s0 + IMAGE_TILE_BORDER_FIX(x, scaleX);
        }
        sStart += sOff;
        if (border) {
            tile.height = topH + 2;
        }
        if (rows > 0) {
            dsdt = (dsdx << 16) | (dtdy & 0xFFFF);
            xi = (s32) x;
            ulx = xi * 4;
            lrx = ((s32) nextX + xAdd) * 4;
            for (j = 0; j < rows; j++) {
                nextY = curY + rowScreenH;
                tStart = t0;
                if (border) {
                    tStart = t0 + IMAGE_TILE_BORDER_FIX(curY, scaleY);
                }
                yi = (s32) curY;
                gfx = (u32 *) func_15095380((s32) gfx, (s32) &tile, 0, 0, 0, 0, 0, 2, 3);
                tile.tex++;
                uly = yi * 4;
                lry = (s32) nextY * 4;
                // gSPTextureRectangle (clamped at 0), then the s / t of the clipped left / top edge
                gfx[0] = 0xE4000000 | ((MAX(lrx, 0) & 0xFFF) << 12) | (MAX(lry, 0) & 0xFFF);
                clipY = uly;
                gfx[1] = ((MAX(ulx, 0) & 0xFFF) << 12) | (MAX(clipY, 0) & 0xFFF);
                gfx[2] = 0xE1000000;
                sFix = 0;
                if (ulx < 0) {
                    sFix = (ulx * (s16) dsdx) >> 7;
                    if ((s16) dsdx < 0) {
                        sFix = MAX(sFix, 0);
                    } else {
                        sFix = MIN(sFix, 0);
                    }
                }
                tFix = 0;
                if (uly < 0) {
                    tFix = (clipY * (s16) dtdy) >> 7;
                    if ((s16) dtdy < 0) {
                        tFix = MAX(tFix, 0);
                    } else {
                        tFix = MIN(tFix, 0);
                    }
                }
                gfx[3] = ((sStart - sFix) << 16) | ((tStart - tFix) & 0xFFFF);
                gfx[4] = 0xF1000000;
                gfx[5] = dsdt;
                gfx += 6;
                if (j == 0) {
                    // rows after the top one are whole tiles
                    tile.height = img->height;
                    rowScreenH = (f32) tileH * scaleY / 4096.0f;
                }
                curY = nextY;
            }
        }
        x = nextX;
    }
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_150966AC.s")
#endif

Gfx *func_15096D44(Gfx *arg0) {
    gSPDisplayList(arg0++, D_800877A8);
    D_800D31CB = 0;
    return arg0;
}
