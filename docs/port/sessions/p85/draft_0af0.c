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
