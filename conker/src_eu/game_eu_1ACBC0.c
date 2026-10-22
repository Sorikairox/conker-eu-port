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

/* Pulsing overlay: alpha D_800DE1BB (scaled by a 0..1 wave from func_15048A40 when D_800DE1BC is set),
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
        a = (f32)D_800DE1BB * ((func_15048A40(D_800DE1B9) + 1.0f) * 0.5f);
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FCCC.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FD84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FF64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1518010C.s")

#ifdef NON_MATCHING
extern Gfx D_8008D3B8[];
extern s32 D_80090648[];       /* scope textures: [1] lens I16, [2] rim IA16, [3..5] range finder frames RGBA16 */
extern f32 D_800A766C;         /* zoom scale */
extern f32 D_800A7670;         /* lens radius per zoom */
extern u8 D_800DE1A8[];        /* per view: range finder frame (0..2) */
extern f32 *D_800DE274;        /* zoom */
extern f32 *D_800DE278;        /* aim offset x */
extern f32 *D_800DE27C;        /* aim offset y */
s32 func_1510D66C(s32, s32, s32, s32);
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
        gDPSetTextureImage(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 1, func_1510D66C(D_80090648[1], 0, 3, 0));
        gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPLoadBlock(gdl++, G_TX_LOADTILE, 0, 0, 0x7FF, 0);
        gDPSetTile(gdl++, G_IM_FMT_I, G_IM_SIZ_8b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, 0, G_TX_CLAMP, 6, 0);
        gDPSetTileSize(gdl++, G_TX_RENDERTILE, 2, 2, 0xFE, 0xFE);
        gDPSetOtherMode(gdl++, 0x002CFF, 0x005011C4);
        gdl = func_1518010C(gdl, r, 0x40, 0.0f, 0.0f, view);
        if ((&D_800DDE1C)[view] != 0) {
            /* rim (IA16 loaded as a 64x64 IA8 tile), half size */
            gDPPipeSync(gdl++);
            gDPSetTextureImage(gdl++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, func_1510D66C(D_80090648[2], 0, 3, 0));
            gDPSetTile(gdl++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadBlock(gdl++, G_TX_LOADTILE, 0, 0, 0x7FF, 0);
            gDPSetTile(gdl++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, 0, G_TX_CLAMP, 6, 0);
            gdl = func_1518010C(gdl, r / 2, 0x40, 0.0f, 0.0f, view);
            if ((&D_800DDE1C)[view] == 2) {
                /* range finder: 32x32 RGBA16 frame, drawn twice */
                gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFCF279);
                gDPSetTextureImage(gdl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,
                                   func_1510D66C(D_80090648[3 + D_800DE1A8[view]], 0, 3, 0));
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15181A6C.s")

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
s32 func_1510D66C(s32, s32, s32, s32);
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
            (*(s32 *)((u8 *)spA8 + 4)) = func_1510D66C(D_80090678, 0, 3, 0);
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
            (*(s32 *)((u8 *)temp_s0_12 + 4)) = func_1510D66C(D_8009067C, 0, 3, 0);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182BE0.s")

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
