#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1517F470();

typedef struct {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x1B];
    /* 0x2B */ s8 unk2B;
    /* 0x2C */ u8 pad2C[0x2];
    /* 0x2E */ s16 unk2E;
} struct_eu_1ACBC0;


extern u8 D_800DE1D0[][3];
extern u8 D_800DE1F0[];
void func_1517F3B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, s32 arg5) {
    s8 *p;
    p = &((s8 *)&D_800DDDAC)[arg5];
    if ((arg4 != *p) || (((s32 *)&D_800DDDB0)[arg5] < ((s32 *)&D_800DDE28)[arg5]) || (D_800DE1F0[arg5] != 0)) {
        D_800DE1D0[arg5][1] = arg1;
        D_800DE1D0[arg5][2] = arg2;
        D_800DE1D0[arg5][0] = arg0;
        ((s32 *)&D_800DDE28)[arg5] = arg3;
        ((s32 *)&D_800DDDB0)[arg5] = 0;
        *p = arg4;
        D_800DE1F0[arg5] = 0;
    }
}

extern u8 D_800DE1F0[];
s32 func_1517F470(arg0)
s32 arg0;
{
    s32 d;
    s32 *new_var; // fakematch: base pointer temp
    s32 r;
    s32 b;

    r = (((s32 *)&D_800DDDB0)[arg0] * 0xFF) / d; // fakematch: dead store (d unset), permuter artifact that fixes the register roles
    b = D_800DE1F0[arg0];
    if (b != 0) {
        r = b;
    } else {
        d = (new_var = (s32 *)&D_800DDE28)[arg0];
        if (d != 0) {
            r = (((s32 *)&D_800DDDB0)[arg0] * 0xFF) / d;
            if (r >= 0x100) {
                r = 0xFF;
            }
        } else {
            r = 0xFF;
        }
        if (((s8 *)&D_800DDDAC)[arg0] == 0) {
            r = 0xFF - r;
        }
    }
    return r;
}

#ifdef NON_MATCHING
/* func_1517F470 takes one argument; the matching code passes a1-a3 through unused */
s32 func_1517F51C(s32 arg0) {
    if (func_1517F470(arg0) == 0xFF) {
#else
s32 func_1517F51C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_1517F470(arg0, arg1, arg2, arg3) == 0xFF) {
#endif
        return 1;
    }
    return 0;
}

s32 func_1517F54C(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = -1;
    var_s0 = 0;
    if (D_80082FA0 >= 0) {
        do {
            if ((func_1517F470(var_s0) > 0) || ((&D_800DDDC8)[var_s0] > 0.0f)) {
                var_s1 += 1;
            }
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
    if (var_s1 == D_80082FA0) {
        return 1;
    }
    return 0;
}

#define VP(i, o) (*(f32 *)((u8 *)D_800BE628 + (i) * 0x180 + (o)))
Gfx *func_1517F5FC(Gfx *gfx, s32 a, s32 r, s32 g, s32 b, s32 i) {
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, r, g, b, a);
    gDPSetOtherMode(gfx++, 0x2CFF, 0x504344);
    gDPFillRectangle(gfx++, VP(i, 0x2C), VP(i, 0x24), VP(i, 0x30), VP(i, 0x28));
    return gfx;
}

#ifdef NON_MATCHING
Gfx *func_1517F910(Gfx *gdl, s32 arg1) {
    s32 r = func_1517F470(arg1);

    if (r == 0) {
        return gdl;
    }
    return func_1517F5FC(gdl, r, D_800DE1D0[arg1][0], D_800DE1D0[arg1][1], D_800DE1D0[arg1][2], arg1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517F910.s")
#endif
s32 func_1517F40C(s32 arg0) {
    if ((&D_800DDDB0)[arg0] >= (&D_800DDE28)[arg0]) {
        return 1;
    }
    return 0;
}

void func_1517F448(s32 arg0) {
    if ((&D_800DDDB0)[arg0] != (&D_800DDE28)[arg0]) {
        (&D_800DDDB0)[arg0] += D_800BE9E4;
    }
}

void func_1517F9F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *temp_v0 = D_800DE1C0[arg5];

    temp_v0[0] = arg0;
    temp_v0[1] = arg1;
    temp_v0[2] = arg2;
    D_800DE1CC[arg5] = arg3;
    D_800DE240[arg5] = arg4;
}

Gfx *func_1517F5FC(Gfx *, s32, s32, s32, s32, s32);
s32 func_1517FA48(s32 arg0, s32 arg1) {
    u8 *temp_v0;
    s32 temp_a1;
    if ((u16)D_800DE240[arg1] == 0) {
        return arg0;
    }
    temp_a1 = D_800DE1CC[arg1];
    if (temp_a1 == 0) {
        return arg0;
    }
    temp_v0 = D_800DE1C0[arg1];
    return (s32)func_1517F5FC((u8 *)arg0, temp_a1, temp_v0[0], temp_v0[1], temp_v0[2], arg1);
}

#ifdef NON_MATCHING
extern u8 D_8008D3B0[][6];

/* Pulsing overlay: alpha D_800DE1BB (scaled by a 0..1 wave from math_sin_u8 when D_800DE1BC is set),
 * colour D_8008D3B0[D_800DE1BA] (first of its two RGB triples). */
Gfx *func_1517FAD4(Gfx *gdl) {
    u8 *c;
    s32 a;
    f32 t;

    if (D_800DDE08 == 0) {
        return gdl;
    }
    a = D_800DE1BB;
    if (a == 0) {
        return gdl;
    }
    /* the asm leaves t uninitialised (a stale stack word) when D_800DE1BC == 0 and sets 0 on the wave path:
     * use 0 on both paths (UNVERIFIED for the non-wave path) */
    t = 0.0f;
    if (D_800DE1BC != 0) {
        a = (f32)D_800DE1BB * ((math_sin_u8(D_800DE1B9) + 1.0f) * 0.5f);
    }
    c = D_8008D3B0[D_800DE1BA];
    return func_1517F5FC(gdl, a, (s32)((c[3] - c[0]) * t + c[0]), (s32)((c[4] - c[1]) * t + c[1]),
                         (s32)((c[5] - c[2]) * t + c[2]), 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FAD4.s")
#endif
void func_1517FC90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    D_800DDE08 = arg1;
    D_800DE1B8 = arg2;
    D_800DE1B9 = 0;
    D_800DE1BA = arg0;
    D_800DE1BB = arg3;
    D_800DE1BC = arg4;
}

#ifdef NON_MATCHING
/* P95: per-frame countdown of the D_800DE240[0..D_80082FA0] timers by the frame time D_800BE9E4 (clamped at 0). */
void func_1517FCCC(void) {
    u16 *p = (u16 *) D_800DE240;
    u16 *end;
    s32 dt;

    if (D_80082FA0 < 0) {
        return;
    }
    end = (u16 *) &D_800DE240[D_80082FA0];
    dt = D_800BE9E4;
    do {
        if (dt < *p) {
            *p -= dt;
        } else {
            *p = 0;
        }
        p++;
    } while (p <= end);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FCCC.s")
#endif

void func_1517FD24(void)
{
  s32 new_var;
  if (D_800DDE08 != 0)
  {
    if (D_800BE9E4 < ((s32) D_800DDE08))
    {
      new_var = D_800BE9E4;
      D_800DDE08 -= new_var;
    }
    else
    {
      D_800DDE08 = 0;
    }
    D_800DE1B9 += D_800DE1B8 * D_800BE9E4;
  }
}

#ifdef NON_MATCHING
extern u8 D_800DA130[];   /* per player: 0x40-byte HUD projection matrix */
void func_150A7EE0(u8 *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);

/* hud_lens_set_target: sets the player's lens / zoom centre D_800DE218[player] (offset from the viewport centre
 * +0x0C / +0x10 of D_800BE628 + player * 0x180). With project == 0, (x, y, z) is a world point: projected with
 * D_800DA130[player] (func_150A7EE0; w 0 counts as 1) to viewport coordinates (+0x2C / +0x24 added, y down);
 * else x / y are taken as they are. Both are clamped to [-10000, 10000] (rodata D_800A7660..68). */
void func_1517FD84(s32 project, f32 x, f32 y, f32 z, s32 player) {
    f32 sx;
    f32 sy;
    f32 sz;
    f32 w;
    u8 *vp;

    if (project == 0) {
        func_150A7EE0(D_800DA130 + player * 0x40, x, y, z, &sx, &sy, &sz, &w);
        if (w == 0.0f) {
            w = 1.0f;
        }
        vp = (u8 *) D_800BE628 + player * 0x180;
        sx = *(f32 *) (vp + 0xC) * sx / w;
        sy = *(f32 *) (vp + 0x10) * sy / w;
        sx = sx + *(f32 *) (vp + 0xC);
        sy = *(f32 *) (vp + 0x10) - sy;
        sx = sx + *(f32 *) (vp + 0x2C);
        sy = sy + *(f32 *) (vp + 0x24);
    } else {
        sx = x;
        sy = y;
        vp = (u8 *) D_800BE628 + player * 0x180;
    }
    if (sx > 10000.0f) {
        sx = 10000.0f;
    } else if (sx < -10000.0f) {
        sx = -10000.0f;
    }
    if (sy > 10000.0f) {
        sy = 10000.0f;
    } else if (sy < -10000.0f) {
        sy = -10000.0f;
    }
    D_800DE218[player][0] = sx - *(f32 *) (vp + 0xC);
    D_800DE218[player][1] = sy - *(f32 *) (vp + 0x10);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FD84.s")
#endif

#ifdef NON_MATCHING
/* P130 */
// view_fill_rect: appends a G_FILLRECT (F6) for the rectangle (x0, y0) - (x1, y1) (either corner order) clipped
// to view's screen box (camera D_800BE628 + view * 0x180: f32 left +0x2C, top +0x24, right +0x30, bottom +0x28,
// truncated); nothing when it lies outside (touching counts as outside). Returns the DL end.
u8 *func_1517FF64(u8 *dl, s32 x0, s32 y0, s32 x1, s32 y1, s32 view) {
    u8 *cam;
    s32 left, top, right, bottom;
    s32 t;

    if (x1 < x0) {
        t = x0;
        x0 = x1;
        x1 = t;
    }
    if (y1 < y0) {
        t = y0;
        y0 = y1;
        y1 = t;
    }
    cam = (u8 *) D_800BE628 + view * 0x180;
    left = *(f32 *) (cam + 0x2C);
    top = *(f32 *) (cam + 0x24);
    bottom = *(f32 *) (cam + 0x28);
    right = *(f32 *) (cam + 0x30);
    if (!(y0 < bottom && top < y1 && x0 < right && left < x1)) {
        return dl;
    }
    x0 = (x0 < left) ? left : (right < x0) ? right : x0;
    y0 = (y0 < top) ? top : (bottom < y0) ? bottom : y0;
    x1 = (x1 < left) ? left : (right < x1) ? right : x1;
    y1 = (y1 < top) ? top : (bottom < y1) ? bottom : y1;
    ((s32 *) dl)[1] = ((x0 & 0x3FF) << 14) | ((y0 & 0x3FF) << 2);
    ((s32 *) dl)[0] = 0xF6000000 | ((x1 & 0x3FF) << 14) | ((y1 & 0x3FF) << 2);
    return dl + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FF64.s")
#endif

#ifdef NON_MATCHING
/* P136 */
/*
 * scope_lens_draw: draws the four quadrants of a round lens / range-finder texture (tex x tex texels, tile 0
 * already loaded by the caller) as mirrored scissored texture rectangles of size x size pixels around the view's
 * lens centre (viewport centre +0x0C / +0x10 of D_800BE628 + view * 0x180, plus D_800DE218[view]). (dx, dy) moves
 * the lower-right quadrant to (cx + dx, cy + dy) and the upper-left one to (cx - dx, cy - dy); the other two take
 * one coordinate from each. Texture steps are +-tex / size in s5.10; the quadrants on the +x / +y side start at
 * texel tex and step backwards, the others start at 0, each with the sub-pixel fraction of its corner
 * (s10.5 = the corner's fraction * 32). Returns the display list after the 4 * 3 commands.
 */
Gfx *func_1518010C(Gfx *gdl, s32 size, s32 tex, f32 dx, f32 dy, s32 view) {
    u8 *vp = (u8 *) D_800BE628 + view * 0x180;
    f32 *lens = D_800DE218[view];
    f32 cx = *(f32 *) (vp + 0x0C) + lens[0];
    f32 cy = *(f32 *) (vp + 0x10) + lens[1];
    f32 r = (f32) size;
    f32 x0 = cx + dx; /* +x side: x0 .. x0 + r */
    f32 y0 = cy + dy; /* +y side: y0 .. y0 + r */
    f32 x1 = cx - dx; /* -x side: x1 - r .. x1 */
    f32 y1 = cy - dy; /* -y side: y1 - r .. y1 */
    s32 ts = tex << 5;
    s32 k = (u32) ((f32) tex / r * 1024.0f) & 0xFFFF;

    /* lower right: mirrored in s and t */
    gSPScisTextureRectangle(gdl++, (s32) x0 * 4, (s32) y0 * 4, (s32) (x0 + r) * 4, (s32) (y0 + r) * 4, 0,
                            ts + ((s32) (x0 * 32.0f) & 0x1F), ts + ((s32) (y0 * 32.0f) & 0x1F), -k, -k);
    /* upper left: forward in s and t */
    gSPScisTextureRectangle(gdl++, (s32) (x1 - r) * 4, (s32) (y1 - r) * 4, (s32) x1 * 4, (s32) y1 * 4, 0,
                            0x1F - ((s32) ((x1 - r) * 32.0f) & 0x1F), 0x1F - ((s32) ((y1 - r) * 32.0f) & 0x1F), k, k);
    /* upper right: mirrored in s */
    gSPScisTextureRectangle(gdl++, (s32) x0 * 4, (s32) (y1 - r) * 4, (s32) (x0 + r) * 4, (s32) y1 * 4, 0,
                            ts + ((s32) (x0 * 32.0f) & 0x1F), 0x1F - ((s32) ((y1 - r) * 32.0f) & 0x1F), -k, k);
    /* lower left: mirrored in t */
    gSPScisTextureRectangle(gdl++, (s32) (x1 - r) * 4, (s32) y0 * 4, (s32) x1 * 4, (s32) (y0 + r) * 4, 0,
                            0x1F - ((s32) ((x1 - r) * 32.0f) & 0x1F), ts + ((s32) (y0 * 32.0f) & 0x1F), k, -k);
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1518010C.s")
#endif

#ifdef NON_MATCHING
extern Gfx D_8008D3B8[];
extern s32 D_80090648[];       /* scope textures: [1] lens I16, [2] rim IA16, [3..5] range finder frames RGBA16 */
extern f32 D_800A766C;         /* zoom scale */
extern f32 D_800A7670;         /* lens radius per zoom */
extern u8 D_800DE1A8[];        /* per view: range finder frame (0..2) */
extern f32 *D_800DE274;        /* zoom */
extern f32 *D_800DE278;        /* aim offset x */
extern f32 *D_800DE27C;        /* aim offset y */
s32 texture_cache_lookup(s32, s32, s32, s32);
u8 *func_1517FF64(u8 *, s32, s32, s32, s32, s32); /* P85: the callee compares full words (callers pass s16 values) */
Gfx *func_1518010C(Gfx *, s32, s32, f32, f32, s32);

/* field of the record of view `view` (0x180 bytes): +0xC / +0x10 centre x / y, +0x24..+0x30 top / bottom / left / right */
#define SCOPE_VIEW_F(view, off) (*(f32 *) ((u8 *) D_800BE628 + (view) * 0x180 + (off)))
/* a filled black / white rectangle clipped to the view (func_1517FF64 orders the corners) */
/* float -> s16 through s32 (out-of-range floats keep the low half of the 32-bit conversion) */
#define S16F(f) ((s16) (s32) (f))
#define SCOPE_RECT(x0, y0, x1, y1) gdl = (Gfx *) func_1517FF64((u8 *) gdl, x0, y0, x1, y1, view)

/*
 * P85: sniper scope overlay of view `view`. The lens size follows the zoom (D_800DE274 when D_800DDE40 is set and
 * D_800C35EA == 1, which also moves the lens centre D_800DE218[view] with the aim offsets D_800DE278 / D_800DE27C
 * in view 0's scale; 1.0 when D_800DE40 is set otherwise; else D_800DDDC8[view]). Zoom 0: nothing. Zoom < 1: the
 * view outside the lens square is filled black, an optional cross hair (D_800DDE1C[view] != 0: black then white
 * pass, 1 pixel wider each) with corner brackets around the lens (mode 1), then the lens texture (D_80090648[1]),
 * the rim (mode != 0) and the range finder (mode 2, animated frame D_800DE1A8[view]) via func_1518010C.
 * Zoom >= 1: the whole view is filled (fill colour 0x00010001).
 */
Gfx *func_15180AF0(Gfx *gdl, s32 view) {
    f32 *centre;
    f32 k;
    f32 zoom;
    f32 fr;
    s32 i;
    s32 cx;
    s32 cy;
    s16 r;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s32 left; /* s16 values, widened by the cross hair passes */
    s32 top;
    s32 right;
    s32 bottom;

    if (D_800DDE40 != 0) {
        if (D_800C35EA == 1) {
            k = D_800A766C;
            zoom = *D_800DE274 * k;
            if (zoom > 1.0f) {
                zoom = 1.0f;
            } else if (zoom < 0.0f) {
                zoom = 0.0f;
            }
            D_800DE218[view][0] = *(f32 *) ((u8 *) D_800BE628 + 4) * (*D_800DE278 * k);
            D_800DE218[view][1] = *(f32 *) ((u8 *) D_800BE628 + 8) * -(*D_800DE27C * k);
        } else {
            zoom = 1.0f;
        }
    } else {
        zoom = (&D_800DDDC8)[view];
    }
    if (zoom == 0.0f) {
        return gdl;
    }
    gSPDisplayList(gdl++, D_8008D3B8);
    gDPPipeSync(gdl++);
    gDPSetFillColor(gdl++, 0x00010001);
    gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFDF6FB);
    gDPSetOtherMode(gdl++, 0x000CFF, 0x0F0A4004);
    gSPGeometryMode(gdl++, 0x1F0001, 0);
    gSPGeometryMode(gdl++, 0, 0x200004);
    if (zoom < 1.0f) {
        left = S16F(SCOPE_VIEW_F(view, 0x2C));
        bottom = S16F(SCOPE_VIEW_F(view, 0x28));
        top = S16F(SCOPE_VIEW_F(view, 0x24));
        right = S16F(SCOPE_VIEW_F(view, 0x30));
        r = S16F(D_800A7670 * zoom + 400.0f);
        fr = r;
        centre = D_800DE218[view];
        /* black outside the lens square */
        y0 = SCOPE_VIEW_F(view, 0x10) + centre[1] - fr;
        SCOPE_RECT(left, top, right, y0);
        y1 = SCOPE_VIEW_F(view, 0x10) + centre[1] + fr;
        SCOPE_RECT(left, y1, right, bottom);
        y0 = SCOPE_VIEW_F(view, 0x10) + centre[1] - fr;
        y1 = SCOPE_VIEW_F(view, 0x10) + centre[1] + fr;
        x1 = SCOPE_VIEW_F(view, 0xC) + centre[0] - fr;
        SCOPE_RECT(left, y0, x1, y1);
        y0 = SCOPE_VIEW_F(view, 0x10) + centre[1] - fr;
        x0 = SCOPE_VIEW_F(view, 0xC) + centre[0] + fr;
        y1 = SCOPE_VIEW_F(view, 0x10) + centre[1] + fr;
        SCOPE_RECT(x0, y0, right, y1);
        if ((&D_800DDE1C)[view] != 0) {
            gDPPipeSync(gdl++);
            gDPSetOtherMode(gdl++, 0x002C0F, 0x0F0A4004);
            gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFDF6FB);
            gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, 0xFF);
            /* cross hair: pass 0 black and one pixel wider, pass 1 white */
            for (i = 0; i < 2; i++) {
                y0 = SCOPE_VIEW_F(view, 0x10) - 1.0f;
                y1 = SCOPE_VIEW_F(view, 0x10) + 1.0f;
                SCOPE_RECT(left, y0 - i, right, y1 + i);
                x0 = SCOPE_VIEW_F(view, 0xC) - 1.0f;
                x1 = SCOPE_VIEW_F(view, 0xC) + 1.0f;
                SCOPE_RECT(x0 - i, top, x1 + i, bottom);
                if ((&D_800DDE1C)[view] == 1) {
                    /* corner brackets 60 pixels from the lens centre */
                    cx = SCOPE_VIEW_F(view, 0xC) + centre[0];
                    cy = SCOPE_VIEW_F(view, 0x10) + centre[1];
                    SCOPE_RECT((s16) (cx - 60) - i, (s16) (cy - 60) - i, (s16) (cx - 30) + i, (s16) (cy - 58) + i);
                    SCOPE_RECT((s16) (cx - 60) - i, (s16) (cy - 60) - i, (s16) (cx - 58) + i, (s16) (cy - 30) + i);
                    SCOPE_RECT((s16) (cx + 58) - i, (s16) (cy - 30) - i, (s16) (cx + 60) + i, (s16) (cy - 60) + i);
                    SCOPE_RECT((s16) (cx + 30) - i, (s16) (cy - 58) - i, (s16) (cx + 60) + i, (s16) (cy - 60) + i);
                    SCOPE_RECT((s16) (cx + 60) - i, (s16) (cy + 60) - i, (s16) (cx + 58) + i, (s16) (cy + 30) + i);
                    SCOPE_RECT((s16) (cx + 60) - i, (s16) (cy + 60) - i, (s16) (cx + 30) + i, (s16) (cy + 58) + i);
                    SCOPE_RECT((s16) (cx - 60) - i, (s16) (cy + 60) - i, (s16) (cx - 58) + i, (s16) (cy + 30) + i);
                    SCOPE_RECT((s16) (cx - 60) - i, (s16) (cy + 60) - i, (s16) (cx - 30) + i, (s16) (cy + 58) + i);
                }
                if (i == 0) {
                    gDPPipeSync(gdl++);
                    gDPSetOtherMode(gdl++, 0x002C0F, 0x00504244);
                    gDPSetFillColor(gdl++, 0);
                    gDPSetPrimColor(gdl++, 0, 0, 0xFF, 0xFF, 0xFF, 0);
                }
                left--;
                right++;
                top--;
                bottom++;
            }
        }
        /* lens (I16 loaded as a 64x64 I8 tile) */
        gDPPipeSync(gdl++);
        gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFFF3F9);
        gSPTexture(gdl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetTextureImage(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 1, texture_cache_lookup(D_80090648[1], 0, 3, 0));
        gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPLoadBlock(gdl++, G_TX_LOADTILE, 0, 0, 0x7FF, 0);
        gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_8b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, 0, G_TX_CLAMP, 6, 0);
        gDPSetTileSize(gdl++, G_TX_RENDERTILE, 2, 2, 0xFE, 0xFE);
        gDPSetOtherMode(gdl++, 0x002CFF, 0x005011C4);
        gdl = func_1518010C(gdl, r, 0x40, 0.0f, 0.0f, view);
        if ((&D_800DDE1C)[view] != 0) {
            /* rim (IA16 loaded as a 64x64 IA8 tile), half size */
            gDPPipeSync(gdl++);
            gDPSetTextureImage(gdl++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, texture_cache_lookup(D_80090648[2], 0, 3, 0));
            gDPSetTile(gdl++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadBlock(gdl++, G_TX_LOADTILE, 0, 0, 0x7FF, 0);
            gDPSetTile(gdl++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, 0, G_TX_CLAMP, 6, 0);
            gdl = func_1518010C(gdl, r / 2, 0x40, 0.0f, 0.0f, view);
            if ((&D_800DDE1C)[view] == 2) {
                /* range finder: 32x32 RGBA16 frame, drawn twice */
                gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFCF279);
                gDPSetTextureImage(gdl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,
                                   texture_cache_lookup(D_80090648[3 + D_800DE1A8[view]], 0, 3, 0));
                gDPSetTile(gdl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                gDPLoadBlock(gdl++, G_TX_LOADTILE, 0, 0, 0x3FF, 0);
                gDPSetTile(gdl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, 0, G_TX_CLAMP,
                           5, 0);
                gdl = func_1518010C(gdl, r / 4, 0x20, 32.0f, 28.0f, view);
                gdl = func_1518010C(gdl, r / 4, 0x20, 28.0f, 32.0f, view);
                if (D_800DE1A8[view] < 2) {
                    D_800DE1A8[view]++;
                } else {
                    D_800DE1A8[view] = 0;
                }
            }
        }
    } else {
        gDPFillRectangle(gdl++, SCOPE_VIEW_F(view, 0x2C), SCOPE_VIEW_F(view, 0x24), SCOPE_VIEW_F(view, 0x30),
                         SCOPE_VIEW_F(view, 0x28));
    }
    gSPGeometryMode(gdl++, 0, 1);
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15180AF0.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800DDDC8;   /* [4] per player: HUD lens zoom (1 = none) */
extern f32 D_800DDDD8;   /* [4] per player: zoom rate per frame step */
extern u8 D_800DDE20;    /* [4] per player: scripted zoom (driven by the object's +0x31C state +0x120) */
extern u8 D_800DDE3C;    /* [4] per player: lens state 1..4 (0 = off) */
extern u8 D_800DE1A0[];  /* per player: wobble timer */
extern u8 D_800DE1A4[];  /* per player: wobble angle */
extern u16 D_800DE1B0[]; /* per player: hold timer of lens state 3 */
extern u8 D_800BE9B4;
f32 math_sin_u8(u8);
void func_150A7E40(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_1517FD84(s32 project, f32 x, f32 y, f32 z, s32 player);

/* hud_lens_update: per frame (world_update path) for every player: zoom D_800DDDC8[p] += rate D_800DDDD8[p] * step
 * (D_800BE9E4). Scripted zoom (D_800DDE20[p]) follows the player object's +0x31C record state +0x120 (no record:
 * zoom 1): 3 zooms in to the rest zoom (0.8 one player, 0.9 split screen) -> 4 (wobble 30 frames); 4 wobbles
 * sin(angle) * 0.01 (fading over the last 30 frames) around the rest zoom -> 5 (holds it); 6 zooms in at 0.009 to
 * 0.965 -> 7 (+0x124 = 30); 8 zooms out at 0.004 to 1 -> 9. Otherwise, with the lens on (D_800DDE3C[p]), its centre
 * D_800DE218[p] eases (factor 0.05, 1 with D_800BE9B4; at most 15 / 11.25 per frame) to the projection
 * (func_1517FD84) of a point 40 * y_scale above the object (its joint matrix +0x1D4, +0x300 when +0x00 == 1, else
 * its position); states: 1 zooming in to 0.9 -> 2 (wobble, angle running backwards) -> 3 (hold 50) -> 4 zooming
 * out at 0.009 -> 0 at zoom 0. Lens off: a non-zero rate runs the zoom up to 1 / down to 0 and stops there. */
void func_15181A6C(void) {
    static const f32 restZoom[4] = { 0.8f, 0.9f, 0.9f, 0.9f };
    static const f32 nearZoom[4] = { 0.965f, 0.965f, 0.965f, 0.965f };
    s32 p;
    f32 *zoom;
    f32 *rate;
    u8 *lens;
    u8 *rec;
    struct127 *obj;
    f32 amp;
    f32 px;
    f32 py;
    f32 pz;
    f32 ox;
    f32 oy;
    f32 dx;
    f32 dy;
    f32 k;
    u8 *mtx;

    for (p = 0; p <= D_80082FA0; p++) {
        zoom = &(&D_800DDDC8)[p];
        rate = &(&D_800DDDD8)[p];
        lens = &(&D_800DDE3C)[p];
        if ((&D_800DDE20)[p] != 0) {
            obj = &D_800CC2D0[p];
            *zoom += *rate * (f32) D_800BE9E4;
            rec = (u8 *) obj->unk31C;
            if (rec == NULL) {
                *zoom = 1.0f;
            } else if (rec[0x120] == 3) {
                if (restZoom[D_80082FA0] <= *zoom) {
                    *zoom = restZoom[D_80082FA0];
                    ((u8 *) obj->unk31C)[0x120] = 4;
                    D_800DE1A0[p] = 30;
                    D_800DE1A4[p] = 0;
                }
            } else if (rec[0x120] == 4) {
                if (D_800DE1A0[p] != 0) {
                    D_800DE1A0[p] = (D_800DE1A0[p] < D_800BE9E4) ? 0 : D_800DE1A0[p] - D_800BE9E4;
                    D_800DE1A4[p] += D_800BE9E4 * 20;
                    amp = (D_800DE1A0[p] < 30) ? D_800DE1A0[p] * 0.01f / 30.0f : 0.01f;
                    *zoom = math_sin_u8(D_800DE1A4[p]) * amp + restZoom[D_80082FA0];
                } else {
                    *zoom = restZoom[D_80082FA0];
                    ((u8 *) obj->unk31C)[0x120] = 5;
                }
            } else if (rec[0x120] == 5) {
                *zoom = restZoom[D_80082FA0];
            } else if (rec[0x120] == 6) {
                *rate = 0.009f;
                if (nearZoom[D_80082FA0] <= *zoom) {
                    *zoom = nearZoom[D_80082FA0];
                    ((u8 *) obj->unk31C)[0x120] = 7;
                    *(u16 *) ((u8 *) obj->unk31C + 0x124) = 30;
                    *rate = 0.0f;
                }
            } else if (rec[0x120] == 8) {
                *rate = 0.004f;
                if (1.0f <= *zoom) {
                    *zoom = 1.0f;
                    ((u8 *) obj->unk31C)[0x120] = 9;
                }
            }
        } else if (*lens != 0) {
            obj = &D_800CC2D0[p];
            *zoom += *rate * (f32) D_800BE9E4;
            if (obj->unk1D4 != NULL) {
                mtx = (u8 *) obj->unk1D4;
                if (obj->interaction_state == 1) {
                    mtx += 0x300;
                }
                func_150A7E40((f32 (*)[4]) mtx, 0.0f, obj->y_scale * 40.0f, 0.0f, &px, &py, &pz);
            } else {
                px = obj->x_position;
                py = obj->y_position;
                pz = obj->z_position;
            }
            ox = D_800DE218[p][0];
            oy = D_800DE218[p][1];
            func_1517FD84(0, px, py, pz, p);
            px = D_800DE218[p][0];
            py = D_800DE218[p][1];
            k = (D_800BE9B4 != 0) ? 1.0f : 0.05f;
            dx = px - ox;
            if (fabsf(dx) > 15.0f) {
                dx = ((dx < 0.0f) ? -1 : 1) * 15.0f;
                ox = px - dx;
            }
            dy = py - oy;
            if (fabsf(dy) > 11.25f) {
                dy = ((dy < 0.0f) ? -1 : 1) * 11.25f;
                oy = py - dy;
            }
            D_800DE218[p][0] = ox + dx * k;
            D_800DE218[p][1] = oy + dy * k;
            if (*lens == 1) {
                if (*zoom <= 0.9f) {
                    D_800DE1A0[p] = 30;
                    *zoom = 0.9f;
                    *rate = 0.0f;
                    *lens = 2;
                }
            } else if (*lens == 2) {
                if (D_800DE1A0[p] != 0) {
                    D_800DE1A0[p] = (D_800DE1A0[p] < D_800BE9E4) ? 0 : D_800DE1A0[p] - D_800BE9E4;
                    D_800DE1A4[p] -= D_800BE9E4 * 20;
                    amp = (D_800DE1A0[p] < 30) ? D_800DE1A0[p] * 0.01f / 30.0f : 0.01f;
                    *zoom = math_sin_u8(D_800DE1A4[p]) * amp + 0.9f;
                } else {
                    *zoom = 0.9f;
                    *lens = 3;
                    D_800DE1B0[p] = 50;
                }
            } else if (*lens == 3) {
                if (D_800BE9E4 < D_800DE1B0[p]) {
                    D_800DE1B0[p] -= D_800BE9E4;
                } else {
                    *lens = 4;
                    *rate = -0.009f;
                }
            } else if (*zoom <= 0.0f) {
                *lens = 0;
                *zoom = 0.0f;
            }
        } else if (*rate != 0.0f) {
            if (*rate > 0.0f) {
                if (*zoom >= 1.0f) {
                    *rate = 0.0f;
                    *zoom = 1.0f;
                }
            } else if (*zoom <= 0.0f) {
                *rate = 0.0f;
                *zoom = 0.0f;
            }
            *zoom += *rate * (f32) D_800BE9E4;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15181A6C.s")
#endif

s32 func_15182238(s32 arg0) {
    if ((&D_800DDDC8)[arg0] == 0.0f) {
        return 1;
    }
    return 0;
}

extern f32 D_800A768C;

void func_15182270(s32 arg0, s32 arg1) {
    f32 *p;

    if (arg1 == 0) {
        (&D_800DDDC8)[arg0] = 0.0f;
    } else {
        (&D_800DDDD8)[arg0] = 0.0f;
        p = D_800DE218[arg0];
        (&D_800DDDC8)[arg0] = D_800A768C;
        p[0] = 0.0f;
        p[1] = 0.0f;
    }
    (&D_800DDE1C)[arg0] = arg1;
}

extern f32 D_800A7690;

void func_15181D70(s32 arg0) {
    f32 *temp_v1;

    (&D_800DDDD8)[arg0] = D_800A7690;
    (&D_800DDDC8)[arg0] = 0.0f;
    temp_v1 = D_800DE218[arg0];
    (*(f32 *)temp_v1) = 0.0f;
    temp_v1[1] = 0.0f;
    (&D_800DDE20)[arg0] = 1;
}

void func_15182338(s32 arg0) {
    (&D_800DDDD8)[arg0] = 0.0;
    (&D_800DDDC8)[arg0] = 0.0f;
    D_800DE218[arg0][0] = 0.0f;
    D_800DE218[arg0][1] = 0.0f;
    (&D_800DDE20)[arg0] = 0;
}

extern u8 D_800DE1D0[][3];
extern u8 D_800DE1F0[];
extern f32 D_800A7694;
void func_15182388(s32 arg0) {
    f32 *p;
    if (D_800BE616 != 0) {
        D_800DE1D0[arg0][0] = 0;
        D_800DE1D0[arg0][1] = 0;
        D_800DE1D0[arg0][2] = 0;
        ((s32 *)&D_800DDE28)[arg0] = 0x19;
        ((s32 *)&D_800DDDB0)[arg0] = 0;
        ((u8 *)&D_800DDDAC)[arg0] = 0;
        D_800DE1F0[arg0] = 0;
        return;
    }
    (&D_800DDE3C)[arg0] = 1;
    (&D_800DDDC8)[arg0] = 1.0f;
    p = D_800DE218[arg0];
    p[0] = 0.0f;
    p[1] = 0.0f;
    (&D_800DDDD8)[arg0] = D_800A7694;
}

#ifdef NON_MATCHING
/* P38: m2c draft (ctx K&R header fixed), func_1517FF64 calls fixed by hand */
s32 texture_cache_lookup(s32, s32, s32, s32);
u8 *func_1517FF64(u8 *, s32, s32, s32, s32, s32); /* P85: the callee compares full words (callers pass s16 values) */
extern s32 D_80090678;
extern s32 D_8009067C;

u8 *func_15182450(u8 *arg0) {
    s16 spF4;
    s16 spF2;
    s16 spF0;
    s32 spEC;
    s32 spE8;
    s32 spDC;
    f32 spD0;
    u8 *spA8;
    u8 *sp88;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp2C;
    f32 temp_f12;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f2;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_t6;
    s16 temp_t7;
    s16 temp_t8;
    s16 temp_t8_2;
    s16 temp_t9_3;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_3;
    s16 var_v0_4;
    s16 var_v1;
    s16 var_v1_2;
    s16 var_v1_5;
    s16 var_v1_6;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f16;
    s32 temp_f4;
    s32 temp_f6;
    s32 temp_f8;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_t9_4;
    s32 var_t3;
    s32 var_t3_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_7;
    s32 var_v1_8;
    u8 *temp_a0;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_11;
    u8 *temp_s0_12;
    u8 *temp_s0_13;
    u8 *temp_s0_14;
    u8 *temp_s0_15;
    u8 *temp_s0_16;
    u8 *temp_s0_17;
    u8 *temp_s0_18;
    u8 *temp_s0_19;
    u8 *temp_s0_20;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *temp_v0;
    u8 *var_s0;

    var_s0 = arg0;
    if (D_800DDE18 == 0) {

    } else {
        temp_f2 = *(f32 *) D_800DDE18 * 0.01f;
        if (temp_f2 < 0.0f) {
            var_f2 = 0.0f;
        } else {
            if (temp_f2 > 1.0f) {
                var_f0 = 1.0f;
            } else {
                var_f0 = temp_f2;
            }
            var_f2 = var_f0;
        }
        if (var_f2 == 0.0f) {

        } else {
            temp_s0 = var_s0 + 8;
            (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)var_s0 + 4)) = 0;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xF7000000;
            (*(s32 *)((u8 *)temp_s0 + 4)) = 0x10001;
            temp_s0_2 = temp_s0 + 8;
            (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xD9E0FFFE;
            (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
            temp_s0_3 = temp_s0_2 + 8;
            (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xD9FFFFFF;
            (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0x200004;
            temp_s0_4 = temp_s0_3 + 8;
            (*(s32 *)((u8 *)temp_s0_4 + 4)) = 4;
            (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xEF302C0F;
            temp_f12 = (*(f32 *)((u8 *)D_800BE628 + 0x24));
            temp_f4 = (s32) (*(f32 *)((u8 *)D_800BE628 + 0x28));
            temp_f16 = (s32) (*(f32 *)((u8 *)D_800BE628 + 0x2C));
            spF2 = (s16) temp_f4;
            spF4 = (s16) temp_f16;
            temp_f8 = (s32) (*(f32 *)((u8 *)D_800BE628 + 0x30));
            spD0 = var_f2;
            spF0 = (s16) temp_f8;
            temp_f6 = (s32) ((temp_f12 - 30.0f) + ((((*(f32 *)((u8 *)D_800BE628 + 8)) * 0.7f) + 30.0f) * var_f2));
            sp40 = (s32) (s16) temp_f6;
            spEC = temp_f6;
            temp_a0 = func_1517FF64(temp_s0_4 + 8, (s16) temp_f16, (s16) (s32) temp_f12, (s16) temp_f8, (s16) temp_f6, 0);
            temp_f10 = (s32) (((*(f32 *)((u8 *)D_800BE628 + 0x28)) + 30.0f) - ((((*(f32 *)((u8 *)D_800BE628 + 8)) * (1.0f - 0.7f)) + 30.0f) * var_f2));
            sp3C = (s32) (s16) temp_f10;
            spE8 = temp_f10;
            temp_v0 = func_1517FF64(temp_a0, spF4, (s16) temp_f10, spF0, spF2, 0);
            (*(s32 *)((u8 *)temp_v0 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)temp_v0 + 4)) = 0;
            (*(s32 *)((u8 *)temp_v0 + 0xC)) = -1;
            (*(s32 *)((u8 *)temp_v0 + 8)) = 0xD7000002;
            (*(s32 *)((u8 *)temp_v0 + 0x10)) = 0xEF002CFF;
            (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0x5011C4;
            (*(s32 *)((u8 *)temp_v0 + 0x1C)) = -0xC07;
            (*(s32 *)((u8 *)temp_v0 + 0x18)) = 0xFCFFFFFF;
            spA8 = temp_v0 + 0x20;
            (*(s32 *)((u8 *)temp_v0 + 0x20)) = 0xFD900000;
            temp_s0_5 = temp_v0 + 0x28;
            (*(s32 *)((u8 *)spA8 + 4)) = texture_cache_lookup(D_80090678, 0, 3, 0);
            (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x07000000;
            (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xF5900000;
            temp_s0_6 = temp_s0_5 + 8;
            (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF3000000;
            (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x077FF000;
            temp_s0_7 = temp_s0_6 + 8;
            (*(s32 *)((u8 *)temp_s0_7 + 0)) = 0xF5801000;
            (*(s32 *)((u8 *)temp_s0_7 + 4)) = 0x9C270;
            temp_s0_8 = temp_s0_7 + 8;
            (*(s32 *)((u8 *)temp_s0_8 + 0)) = 0xF2002002;
            (*(s32 *)((u8 *)temp_s0_8 + 4)) = 0x1FE0FE;
            temp_s0_9 = temp_s0_8 + 8;
            temp_s0_10 = temp_s0_9 + 8;
            temp_t7 = (s16) temp_f8 * 4;
            temp_s0_11 = temp_s0_10 + 8;
            temp_f10_2 = (s32) ((128.0f / (*(f32 *)((u8 *)D_800BE628 + 4))) * 1024.0f);
            if (temp_t7 > 0) {
                var_v0 = temp_t7;
            } else {
                var_v0 = 0;
            }
            temp_t8 = (spEC + 0x1E) * 4;
            if (temp_t8 > 0) {
                var_v1 = temp_t8;
            } else {
                var_v1 = 0;
            }
            temp_t6 = spF4 * 4;
            (*(s32 *)((u8 *)temp_s0_9 + 0)) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_v0 & 0xFFF) << 0xC));
            if (temp_t6 > 0) {
                var_v0_2 = temp_t6;
            } else {
                var_v0_2 = 0;
            }
            temp_t8_2 = sp40 * 4;
            if (temp_t8_2 > 0) {
                var_v1_2 = temp_t8_2;
            } else {
                var_v1_2 = 0;
            }
            (*(s32 *)((u8 *)temp_s0_9 + 4)) = (s32) ((var_v1_2 & 0xFFF) | ((var_v0_2 & 0xFFF) << 0xC));
            (*(s32 *)((u8 *)temp_s0_10 + 0)) = 0xE1000000;
            if (temp_t6 < 0) {
                if ((s16) temp_f10_2 < 0) {
                    temp_t8_3 = (s32) (temp_t6 * (s16) temp_f10_2) >> 7;
                    if (temp_t8_3 > 0) {
                        var_t3 = temp_t8_3;
                    } else {
                        var_t3 = 0;
                    }
                } else {
                    var_v1_3 = 0;
                    temp_t9 = (s32) (temp_t6 * (s16) temp_f10_2) >> 7;
                    if (temp_t9 < 0) {
                        var_v1_3 = temp_t9;
                    }
                    var_t3 = var_v1_3;
                }
            } else {
                var_t3 = 0;
            }
            if (sp40 & 0x20000000) {
                temp_t6_2 = (s32) (temp_t8_2 * 0x222) >> 7;
                var_v1_4 = 0;
                if (temp_t6_2 < 0) {
                    var_v1_4 = temp_t6_2;
                }
            } else {
                var_v1_4 = 0;
            }
            (*(s32 *)((u8 *)temp_s0_10 + 4)) = (s32) ((-var_v1_4 & 0xFFFF) | (var_t3 * -0x10000));
            temp_t9_2 = (temp_f10_2 << 0x10) | 0x222;
            (*(s32 *)((u8 *)temp_s0_11 + 0)) = 0xF1000000;
            sp2C = temp_t9_2;
            (*(s32 *)((u8 *)temp_s0_11 + 4)) = temp_t9_2;
            temp_s0_12 = temp_s0_11 + 8;
            (*(s32 *)((u8 *)temp_s0_12 + 0)) = 0xFD900000;
            spDC = temp_f10_2;
            sp38 = (s32) temp_t7;
            sp34 = (s32) temp_t6;
            sp88 = temp_s0_12;
            temp_s0_13 = temp_s0_12 + 8;
            (*(s32 *)((u8 *)temp_s0_12 + 4)) = texture_cache_lookup(D_8009067C, 0, 3, 0);
            (*(s32 *)((u8 *)temp_s0_13 + 4)) = 0x07000000;
            (*(s32 *)((u8 *)temp_s0_13 + 0)) = 0xF5900000;
            temp_s0_14 = temp_s0_13 + 8;
            (*(s32 *)((u8 *)temp_s0_14 + 0)) = 0xF3000000;
            (*(s32 *)((u8 *)temp_s0_14 + 4)) = 0x077FF000;
            temp_s0_15 = temp_s0_14 + 8;
            (*(s32 *)((u8 *)temp_s0_15 + 0)) = 0xF5801000;
            (*(s32 *)((u8 *)temp_s0_15 + 4)) = 0x9C270;
            temp_s0_16 = temp_s0_15 + 8;
            (*(s32 *)((u8 *)temp_s0_16 + 0)) = 0xF2002002;
            (*(s32 *)((u8 *)temp_s0_16 + 4)) = 0x1FE0FE;
            temp_s0_17 = temp_s0_16 + 8;
            temp_s0_18 = temp_s0_17 + 8;
            if (temp_t7 > 0) {
                var_v0_3 = temp_t7;
            } else {
                var_v0_3 = 0;
            }
            temp_t9_3 = sp3C * 4;
            if (temp_t9_3 > 0) {
                var_v1_5 = temp_t9_3;
            } else {
                var_v1_5 = 0;
            }
            (*(s32 *)((u8 *)temp_s0_17 + 0)) = (s32) ((var_v1_5 & 0xFFF) | 0xE4000000 | ((var_v0_3 & 0xFFF) << 0xC));
            if (temp_t6 > 0) {
                var_v0_4 = temp_t6;
            } else {
                var_v0_4 = 0;
            }
            temp_s0_19 = temp_s0_18 + 8;
            var_v1_6 = 0;
            temp_a2 = spE8 - 0x1E;
            temp_a2_2 = temp_a2 * 4;
            if (temp_a2_2 > 0) {
                var_v1_6 = temp_a2_2;
            }
            (*(s32 *)((u8 *)temp_s0_17 + 4)) = (s32) ((var_v1_6 & 0xFFF) | ((var_v0_4 & 0xFFF) << 0xC));
            (*(s32 *)((u8 *)temp_s0_18 + 0)) = 0xE1000000;
            if (temp_t6 < 0) {
                temp_t9_4 = (s32) (temp_t6 * (s16) temp_f10_2) >> 7;
                if ((s16) temp_f10_2 < 0) {
                    if (temp_t9_4 > 0) {
                        var_t3_2 = temp_t9_4;
                    } else {
                        var_t3_2 = 0;
                    }
                } else {
                    var_v1_7 = 0;
                    if (temp_t9_4 < 0) {
                        var_v1_7 = temp_t9_4;
                    }
                    var_t3_2 = var_v1_7;
                }
            } else {
                var_t3_2 = 0;
            }
            var_v1_8 = 0;
            if (temp_a2 & 0x20000000) {
                temp_t6_3 = (s32) (temp_a2_2 * 0x222) >> 7;
                var_v1_8 = 0;
                if (temp_t6_3 < 0) {
                    var_v1_8 = temp_t6_3;
                }
            }
            (*(s32 *)((u8 *)temp_s0_18 + 4)) = (s32) ((-var_v1_8 & 0xFFFF) | (var_t3_2 * -0x10000));
            (*(s32 *)((u8 *)temp_s0_19 + 0)) = 0xF1000000;
            temp_s0_20 = temp_s0_19 + 8;
            (*(s32 *)((u8 *)temp_s0_19 + 4)) = sp2C;
            (*(s32 *)((u8 *)temp_s0_20 + 4)) = 1;
            (*(s32 *)((u8 *)temp_s0_20 + 0)) = 0xD9FFFFFF;
            var_s0 = temp_s0_20 + 8;
        }
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182450.s")
#endif
#ifdef NON_MATCHING
/* P133 */
void *memcpy(void *, const void *, size_t);

/*
 * colour_fade_start: starts a colour fade effect (func_15149130 type 0x39, 8-byte payload, lasting `frames`) with
 * the colour (r, g, b, a), the byte `mode` and the per-frame alpha step a / frames; arg6 / arg7 go to
 * func_15149130 as they are. Nothing when frames <= 0 or no effect slot is free. The asm leaves payload byte 5
 * uninitialised (stack garbage); the C writes 0 there.
 */
s32 func_15182BE0(u8 r, u8 g, u8 b, u8 a, s16 frames, u8 mode, u8 arg6, s32 arg7) {
    struct {
        u8 r, g, b, a, mode, pad;
        s16 step;
    } fade;
    struct260 *e;

    if (frames > 0) {
        fade.r = r;
        fade.step = a / frames;
        fade.a = a;
        fade.g = g;
        fade.b = b;
        fade.mode = mode;
        fade.pad = 0;
        e = func_15149130(frames, -1, 0x39, 3, 1, 0, (struct37 *) 8, arg6, arg7);
        if (e != NULL) {
            memcpy((u8 *) e + 0x28, &fade, 8);
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182BE0.s")
#endif

void func_15182CB8(struct_eu_1ACBC0 *arg0) {
    arg0->unk2B = arg0->unk2E * arg0->unkE;
}

Gfx *func_1517F5FC(Gfx *, s32, s32, s32, s32, s32);
u8 *func_15182CD8(u8 *arg0, u8 *arg1, s16 arg2) {
    u8 *v;
    v = arg1 + 0x28;
    if (arg2 == arg1[0x2C]) {
        arg0 = func_1517F5FC(arg0, v[3], v[0], v[1], v[2], v[4]);
    }
    return arg0;
}
