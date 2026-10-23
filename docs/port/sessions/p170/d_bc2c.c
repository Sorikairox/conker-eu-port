Gfx *func_15095380(Gfx *gfx, u8 *header, s32 tmem, void *spr, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
Gfx *func_15095E58(Gfx *gfx, void *spr, f32 x, f32 y);
Gfx *func_1516CEA4(Gfx *gfx, u8 *box, u8 r, u8 g, u8 b, u8 a);
extern u8 D_800E100C;     /* text box fade, 0 = hidden */
extern u8 D_800D31C8;     /* sprite primitive colour r, g, b */
extern u8 D_800D31C9;
extern u8 D_800D31CA;
extern s32 D_800BEFC4;    /* display list capacity, in Gfx commands */
extern u8 D_800A4EA8[];   /* render mode pairs, 8 bytes each */
extern u8 D_8009090C[];   /* box sprite header: u16 width +6, height +8 */
extern u8 D_8009091C[];   /* box sprite, "thought" variant (descriptor flag 2) */
extern u8 D_8009092C[];   /* pointer sprite header */
extern u8 D_8009093C[];   /* thought dot sprite */
extern u8 D_8009094C[];   /* pointer sprite, descriptor flag 8 */

/* sprite parameters for func_15095380 / func_15095E58 */
typedef struct {
    u8 unk0[6];
    s16 w;      /* +6: x scale (1024 = 1) */
    s16 h;      /* +8: y scale */
    u8 alpha;   /* +A */
    u8 unkB[2];
    u8 flip;    /* +D: bit 0 mirror x, bit 1 mirror y */
    u8 unkE[2];
} TextBoxSprite;

#define TB_F(off) (*(f32 *) (box + (off)))
#define TB_FLAGS (**(s32 **) (box + 0x10))
#define TB_DL_FULL(g) ((g) - D_800BEDE8[D_800BE9C0] > D_800BEFC4)

// text_box_draw: draws a text box (record of func_1516AD20; +0x28 scale, +0x38 / +0x3C size, +0x40 / +0x44 pointer
// tip, +0x58 pointer angle from func_1516D1C8). First the shadow pass in black at a quarter alpha: the box sprite
// (D_8009090C, or D_8009091C with descriptor flag 2) 5 pixels right / up unless descriptor flag 4, then the pointer
// or, with flag 2, the two "thought" dots (D_8009093C; the first eases towards the tip in +0x70) - this pass also
// sets the box corner +0x48 / +0x4C. Then the colour pass in the descriptor's colour (+0x28..+0x2A into
// D_800D31C8..CA; black at alpha 0x55 with flag 4): pointer / dots (flag 8: the D_8009094C pointer), the box, and
// the text (func_1516CEA4). Alphas scale with the global fade D_800E100C (+1, / 256); the box's fade bytes are +0x1A
// (text), +0x1B (box), +0x1C / +0x1D (dots). Returns gfx unchanged when the box is hidden (+0xE == 0) or the fade is 0,
// and the original gfx (drops the box) when the frame display list fills up.
Gfx *func_1516BC2C(Gfx *gfx, u8 *box, s16 arg2) {
    Gfx *start = gfx;
    TextBoxSprite spr;
    s32 plain;
    s32 fade;
    f32 bw;
    f32 bh;
    f32 px;
    f32 py;
    u32 *rm;

    plain = (TB_FLAGS & 4) ? 1 : 0;
    if (box[0xE] == 0) {
        return gfx;
    }
    if (D_800E100C == 0) {
        return gfx;
    }
    D_800D31CA = 0;
    D_800D31C9 = 0;
    D_800D31C8 = 0;
    fade = D_800E100C + 1;
    spr.flip = 0;
    spr.alpha = (fade * 64) >> 8;

    /* shadow pass: box sprite scale, pointer offset, box corner */
    bw = *(u16 *) (D_8009090C + 6);
    spr.w = (s32) ((TB_F(0x38) + TB_F(0x38) + 1.0f) / bw * 2355.2f * TB_F(0x28));
    bh = *(u16 *) (D_8009090C + 8);
    spr.h = (s32) ((TB_F(0x3C) + 1.0f) / bh * 4259.84f * TB_F(0x28));
    px = TB_F(0x38) / bw * *(u16 *) (D_8009092C + 6) * 0.25f * TB_F(0x28);
    py = TB_F(0x3C) / bh * *(u16 *) (D_8009092C + 8) * 0.5f * TB_F(0x28);
    TB_F(0x48) =
        cosf(TB_F(0x58) + 3.14159274f) * (TB_F(0x38) * 0.5f) * 1.15f * TB_F(0x28) + TB_F(0x40) - px;
    TB_F(0x4C) =
        sinf(TB_F(0x58) + 3.14159274f) * (TB_F(0x3C) * 0.5f) * 1.04f * TB_F(0x28) + TB_F(0x44) - py;

    rm = (u32 *) (D_800A4EA8 + 0x19 * 8);
    gDPPipeSync(gfx++);
    gfx->words.w0 = 0xFC30B261; /* combine: primitive colour, texture alpha x primitive alpha */
    gfx->words.w1 = 0xFF67FFFF;
    gfx++;
    gfx->words.w0 = 0xEF002C0F; /* other mode */
    gfx->words.w1 = rm[0] | rm[1] | 4;
    gfx++;
    if (TB_FLAGS & 2) {
        spr.alpha = (u32) ((f32) box[0x1B] * 64.0f / 255.0f);
        spr.alpha = (spr.alpha * fade) >> 8;
        gfx = func_15095380(gfx, D_8009091C, 0, &spr, 0, 0, 0, 2, 3);
    } else {
        gfx = func_15095380(gfx, D_8009090C, 0, &spr, 0, 0, 0, 2, 3);
    }
    if (!plain) {
        gfx = func_15095E58(gfx, &spr, TB_F(0x48) + 5.0f, TB_F(0x4C) + -5.0f);
    }
    if (0.0f < TB_F(0x58) && TB_F(0x58) < 3.14159274f) {
        spr.flip &= ~2;
    } else {
        spr.flip |= 2;
    }
    if (1.57079637f < TB_F(0x58) && TB_F(0x58) < 4.71238899f) {
        spr.flip |= 1;
    } else {
        spr.flip &= ~1;
    }
    if (TB_DL_FULL(gfx)) {
        return start;
    }

    /* shadow pass: pointer or thought dots */
    if (TB_FLAGS & 2) {
        if (box[0x15] == 1) {
            TB_F(0x70) = TB_F(0x5C);
        }
        gfx = func_15095380(gfx, D_8009093C, 0, &spr, 0, 0, 0, 2, 3);
        spr.alpha = (u32) ((f32) box[0x1C] * 64.0f / 255.0f);
        spr.alpha = (spr.alpha * fade) >> 8;
        if (1.57079637f < TB_F(0x58)) {
            TB_F(0x70) = TB_F(0x70) + (TB_F(0x40) + px - TB_F(0x70)) * 0.3f;
            gfx = func_15095E58(gfx, &spr, TB_F(0x70), TB_F(0x44) - py);
        } else {
            TB_F(0x70) = TB_F(0x70) + (TB_F(0x40) - px - TB_F(0x70)) * 0.3f;
            gfx = func_15095E58(gfx, &spr, TB_F(0x70), TB_F(0x44) - py);
        }
        spr.w /= 2;
        spr.h /= 2;
        spr.alpha = (u32) ((f32) box[0x1D] * 64.0f / 255.0f);
        spr.alpha = (spr.alpha * fade) >> 8;
        gfx = func_15095380(gfx, D_8009093C, 0, &spr, 0, 0, 0, 2, 3);
        if (1.57079637f < TB_F(0x58)) {
            gfx = func_15095E58(gfx, &spr, TB_F(0x40) - 2.5f, TB_F(0x44) + -2.5f);
        } else {
            gfx = func_15095E58(gfx, &spr, TB_F(0x40) + 2.5f, TB_F(0x44) + -2.5f);
        }
    } else {
        gfx = func_15095380(gfx, D_8009092C, 0, &spr, 0, 0, 0, 2, 3);
        if (!plain) {
            if (1.57079637f < TB_F(0x58)) {
                gfx = func_15095E58(gfx, &spr, TB_F(0x40) + px - 2.5f, TB_F(0x44) - py + -2.5f);
            } else {
                gfx = func_15095E58(gfx, &spr, TB_F(0x40) - px + 2.5f, TB_F(0x44) - py + -2.5f);
            }
        }
    }
    if (TB_DL_FULL(gfx)) {
        return start;
    }

    /* colour pass */
    if (plain) {
        D_800D31CA = 0;
        D_800D31C9 = 0;
        D_800D31C8 = 0;
    } else {
        D_800D31C8 = (*(u8 **) (box + 0x10))[0x28];
        D_800D31C9 = (*(u8 **) (box + 0x10))[0x29];
        D_800D31CA = (*(u8 **) (box + 0x10))[0x2A];
    }
    spr.flip = 0;
    if (plain) {
        spr.alpha = 0x55;
    } else {
        spr.alpha = 0xFF;
    }
    spr.alpha = (spr.alpha * fade) >> 8;
    rm = (u32 *) (D_800A4EA8 + 0x19 * 8);
    gDPPipeSync(gfx++);
    gfx->words.w0 = 0xFC30B261;
    gfx->words.w1 = 0xFF67FFFF;
    gfx++;
    gfx->words.w0 = 0xEF002C0F;
    gfx->words.w1 = rm[0] | rm[1] | 4;
    gfx++;
    if (0.0f < TB_F(0x58) && TB_F(0x58) < 3.14159274f) {
        spr.flip &= ~2;
    } else {
        spr.flip |= 2;
    }
    if (1.57079637f < TB_F(0x58) && TB_F(0x58) < 4.71238899f) {
        spr.flip |= 1;
    } else {
        spr.flip &= ~1;
    }
    spr.w = (s32) (TB_F(0x38) / (f32) *(u16 *) (D_8009090C + 6) * 2355.2f * TB_F(0x28));
    spr.h = (s32) (TB_F(0x3C) / (f32) *(u16 *) (D_8009090C + 8) * 4259.84f * TB_F(0x28));
    if (TB_FLAGS & 2) {
        gfx = func_15095380(gfx, D_8009093C, 0, &spr, 0, 0, 0, 2, 3);
        spr.alpha = (box[0x1C] * fade) >> 8;
        gfx = func_15095E58(gfx, &spr, TB_F(0x70), TB_F(0x44) - py);
        spr.w /= 2;
        spr.h /= 2;
        gfx = func_15095380(gfx, D_8009093C, 0, &spr, 0, 0, 0, 2, 3);
        spr.alpha = (box[0x1D] * fade) >> 8;
        /* both sides draw the small dot at the tip */
        gfx = func_15095E58(gfx, &spr, TB_F(0x40), TB_F(0x44));
    } else {
        if (TB_FLAGS & 8) {
            gfx = func_15095380(gfx, D_8009094C, 0, &spr, 0, 0, 0, 2, 3);
        } else {
            gfx = func_15095380(gfx, D_8009092C, 0, &spr, 0, 0, 0, 2, 3);
        }
        if (1.57079637f < TB_F(0x58)) {
            gfx = func_15095E58(gfx, &spr, TB_F(0x40) + px, TB_F(0x44) - py);
        } else {
            gfx = func_15095E58(gfx, &spr, TB_F(0x40) - px, TB_F(0x44) - py);
        }
    }

    /* colour pass: the box */
    spr.w = (s32) ((TB_F(0x38) + TB_F(0x38)) / (f32) *(u16 *) (D_8009090C + 6) * 2355.2f * TB_F(0x28));
    spr.h = (s32) (TB_F(0x3C) / (f32) *(u16 *) (D_8009090C + 8) * 4259.84f * TB_F(0x28));
    if (TB_FLAGS & 2) {
        spr.alpha = (box[0x1B] * fade) >> 8;
        gfx = func_15095380(gfx, D_8009091C, 0, &spr, 0, 0, 0, 2, 3);
    } else {
        gfx = func_15095380(gfx, D_8009090C, 0, &spr, 0, 0, 0, 2, 3);
    }
    gfx = func_15095E58(gfx, &spr, (s32) TB_F(0x48), (s32) TB_F(0x4C));
    if (TB_DL_FULL(gfx)) {
        return start;
    }
    return func_1516CEA4(gfx, box, 0, 0, 0, (box[0x1A] * fade) >> 8);
}
