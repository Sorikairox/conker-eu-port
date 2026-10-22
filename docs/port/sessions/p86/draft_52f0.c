/* A 2D sprite drawn as one textured rectangle (HUD elements). Only the fields func_151552F0 reads. */
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
/* bit 11 + view: only drawn while func_15182238(view) and func_1517F470(view) <= 200 */

#define SPRITE_VIEW_F(v, off) (*(f32 *) ((v) + (off)))

extern struct_eu_80090F10 D_80090F10[];
extern u8 D_800A4EA8[];
extern s32 D_800D30BC;
s32 func_15182238(s32);
s32 func_1517F470(s32);
Gfx *func_15142E24(Gfx *, struct_eu_80090F10 *, s32, s32, s32, s32, s32, s32, s32, u8 *, s32);
Gfx *func_15142B7C(Gfx *, s32, s32);
void func_151441A4(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, s32);
void func_151442FC(s16 *, s16 *, s16 *, s16 *, u8, u8, u8, u8, u8, u8, u8, u8, u8, s32);
Gfx *func_15142C10(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *func_15142CF0(Gfx *, s32, s32, s32, s32, s32, s32, u8 *);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);

/* Draws a 2D sprite in view `view`: texture, colours and render state through the helpers, then a scissored
 * texture rectangle around (x, y) +- (halfW, halfH) scaled to the view. */
Gfx *func_151552F0(Gfx *gdl, Sprite2D *spr, s16 view) {
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
        if (func_15182238(view) == 0 || func_1517F470(view) > 200) {
            return gdl;
        }
    }
    if (spr->tex != 0xFF) {
        gdl = func_15142E24(gdl, &D_80090F10[spr->tex], 0, (spr->flags & SPRITE2D_TEX_MODE0) ? 0 : 2, 0, 0,
                            spr->tex, 0, 0, &ok, (spr->flags & SPRITE2D_TEX_3E) ? 0x3E : 3);
    }
    gdl = func_15142B7C(gdl, spr->geomSet, spr->geomClear);
    func_151441A4(&envR, &envG, &envB, &envA, spr->colB[0], spr->colB[1], spr->colB[2], spr->colB[3],
                  spr->colA[0], spr->colA[1], spr->colA[2], spr->colA[3], spr->colC, spr->fadeA);
    func_151442FC(&primR, &primG, &primB, &primA, spr->colB[0], spr->colB[1], spr->colB[2], spr->colB[3],
                  spr->colA[0], spr->colA[1], spr->colA[2], spr->colA[3], spr->colC, spr->fadeB);
    gdl = func_15142C10(gdl, primR, primG, primB, primA, &ok);
    gdl = func_15142CF0(gdl, 0, 0, envR, envG, envB, envA, &ok);
    gdl = func_1513F4E4(gdl, spr->combine, &ok);
    mode = (u32 *) (D_800A4EA8 + spr->renderMode * 8);
    gdl = func_15142FBC(gdl, spr->otherMode | D_800D30BC | 0x2C00 | spr->otherMode2 | spr->otherMode3,
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
