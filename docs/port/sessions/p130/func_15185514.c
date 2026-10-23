extern u16 D_800DF500[];   /* [slot]: perspNorm of the shadow projection */
extern u8 D_800DF728[];    /* [slot][frame] Mtx (0x40 bytes) */
extern s32 D_800DF4B8;     /* shadow texture (64-byte aligned) */
extern s16 D_80083336;
extern u8 D_800BE9C0;      /* frame buffer index */
extern s32 D_8008D7E8;     /* static DLs / viewport / Mtx of the shadow pass */
extern s32 D_8008D788;
extern s32 D_89810;
Gfx *func_1501A680(Gfx *);
s32 func_1501A490(s32, s16, s32, s32, s32, s32);
Gfx *func_1502CFEC(Gfx *, s32, s32, s32, s32, s32 *, s32, s32);
s32 func_1506196C(struct127 *, s32);
u8 *func_1510BD34(u8 *, s32);

/* one GBI command: two words */
#define SHADOW_GFX(g, hi, lo) ((g)->words.w0 = (hi), (g)->words.w1 = (lo), (g)++)

// shadow_render_caster: starts the display list that renders object obj (light slot) into the shadow texture
// D_800DF4B8: pipe sync, colour image = the texture (16-bit, 64 wide), the static setup DL D_8008D7E8,
// perspNorm D_800DF500[slot], viewport D_8008D788, projection D_800DF728[slot][frame] and view D_89810, then the
// object's model (func_1502CFEC with an all-zero colour and the object's shadow level). Shadow level 0 / 1
// (unk1C8, + 1 when unk127 == 0xFF) blurs the texture twice / once with a 64x64 TEX rectangle over itself.
// Ends with geometry mode on (D9FFFFFF / 0x200001), then func_1501A680 / func_1501A490 / func_1510BD34
// restore the frame state. Marks the object (unk123 = 1). Returns the display list end.
u8 *func_15185514(u8 *dl, s32 obj, s32 slot, s32 arg3) {
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
    g = func_1502CFEC(g, obj, arg3, (s32) o->unk1D4, func_1506196C(o, arg3), col, 3, 1);
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
    dl = func_1510BD34((u8 *) func_1501A490((s32) func_1501A680(g), D_80083336, 0, 0, 0, 0), arg3);
    o->unk123 = 1;
    return dl;
}
