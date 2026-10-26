#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_1516ACE0 */
s32 text_split_lines(u8 *arg0) {
    s32 n = 1;

    while (*arg0 != 0) {
        if (*arg0 == 0xBD) {
            *arg0 = 0;
            n++;
        }
        arg0++;
    }
    return n;
}

typedef struct { u8 *str; s32 pad; } StrEnt_1516CDE8;
extern StrEnt_1516CDE8 *D_800DD684;
extern StrEnt_1516CDE8 *D_800DD688;

/* P155 */
u8 *text_box_get_line(s32 *arg0, s32 arg1, s16 arg2);
void text_measure_string(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
extern f32 D_800A70B0; /* text box width scale */
extern f32 D_800A70B4; /* text box height scale */
extern u8 D_800CC8D3[]; /* per-player records, 0x32C bytes each */
typedef struct {
    s32 flags;  /* low 4 bits: box style; 2: large font; 0x7000 cleared on open */
    s32 str;    /* string table index, or the text itself for a caller-owned descriptor */
    u8 lines;   /* line count (counted by text_split_lines for a caller-owned descriptor) */
    u8 player;
    s8 bA;
    u8 padB[0x1B];
    u16 width;  /* +0x26 */
    u8 pad28[4];
    void (*callback)(s32, s32, s32); /* +0x2C */
} TextAD20;
// text_box_open: opens a text box (node_alloc kind 0x51, 0x74 bytes) for descriptor `text`, or, without it, for
// string id `id` (< 0x100: table D_800DD684, else D_800DD688[id - 0x100]); +0xD = source 0 / 1 / 2 (2 = caller
// descriptor, whose lines are then counted). Stores player / arg2 / callback in the descriptor, measures every line
// (text_measure_string) for the box size +0x38 / +0x3C (plus half / one line height of 18, 25 for the large font, scaled by
// D_800A70B0 / D_800A70B4), points +0x24 at the first line, clears the descriptor's 0x7000 bits and flags the
// player's record (+0xD3 of the 0x32C-byte entry). Returns the box record or NULL.
/* was func_1516AD20 */
s32 text_box_open(s32 id, s32 player, s32 arg2, void (*callback)(s32, s32, s32), s32 *text, s32 arg5) {
    u8 *box;
    TextAD20 *t;
    s32 i;
    s32 w;
    s32 h;
    s32 unused;
    f32 line;

    box = node_alloc(0x51, 0, 0x74, 0, arg5, 2);
    if (box == NULL) {
        return 0;
    }
    t = (TextAD20 *)text;
    if (text == NULL) {
        if ((u32)id >= 0x100) {
            t = (TextAD20 *)D_800DD688[id - 0x100].str;
        } else {
            t = (TextAD20 *)D_800DD684[id].str;
        }
    }
    if (text != NULL) {
        box[0xD] = 2;
    } else if ((u32)id >= 0x100) {
        box[0xD] = 1;
    } else {
        box[0xD] = 0;
    }
    t->player = player;
    t->bA = arg2;
    t->callback = callback;
    box[0xF] = t->flags & 0xF;
    *(TextAD20 **)(box + 0x10) = t;
    box[0x15] = 1;
    box[0x1F] = 0;
    if (text != NULL) {
        box[0x14] = 1;
        *(u16 *)(box + 0x16) = ((TextAD20 *)text)->width;
    } else {
        box[0x14] = 0;
        *(u16 *)(box + 0x16) = t->width >> 1;
    }
    *(s16 *)(box + 0x18) = 0;
    box[0x1A] = 0;
    *(f32 *)(box + 0x28) = 0.0f;
    *(f32 *)(box + 0x38) = 0.0f;
    *(f32 *)(box + 0x3C) = 0.0f;
    if (box[0xD] == 2) {
        t->lines = text_split_lines((u8 *)t->str);
    }
    for (i = 0; i < t->lines; i++) {
        text_measure_string(text_box_get_line((s32 *)t, i, box[0xD]), &w, &h, &unused);
        if (*(f32 *)(box + 0x38) < (f32)w) {
            *(f32 *)(box + 0x38) = w;
        }
        if (*(f32 *)(box + 0x3C) < (f32)h) {
            *(f32 *)(box + 0x3C) = h;
        }
    }
    line = (t->flags & 2) ? 25.0f : 18.0f;
    *(f32 *)(box + 0x38) = (*(f32 *)(box + 0x38) + line * 0.5f) * D_800A70B0;
    *(f32 *)(box + 0x3C) = (*(f32 *)(box + 0x3C) + line) * D_800A70B4;
    *(u8 **)(box + 0x24) = text_box_get_line((s32 *)t, 0, box[0xD]);
    box[0x20] = 0;
    t->flags &= ~0x7000;
    D_800CC8D3[t->player * 0x32C] = 1;
    box[0xE] = 0;
    return (s32)box;
}

s32 mp3_stream_get_state(void);
void text_box_place(u8 *box);
extern u16 D_800BEB30[]; /* buttons pressed this frame, per player (0x8000 A, 0x4000 B) */
extern f32 D_800A7138;   /* 1 / 3: open speed */

#define TB_T(box) (*(TextAD20 **)((box) + 0x10))
#define TB_S16(box, o) (*(s16 *)((box) + (o)))
#define TB_F32(box, o) (*(f32 *)((box) + (o)))

// text_box_update: per-frame update of a text box (D_8008B848 kind 0x51, record of text_box_open). Closes the box at
// once when the descriptor's +0x2B is set and D_800C35EA is not 1. +0x15 is the state: 1 open (style 2: the 3-dot
// "more" variant, starts at 8), 2 grow (+0x28 scale up by +0x2C per frame, line fades in after 0.75), 4 wait
// (45 per frame from 180), 8 the dots fade in one by one, 0x10 line fade-in, 0x20 shown (waits for A / B, the
// "no B" / "last line" / timed flags of the descriptor, or a +0x100 request), 0x40 line fade-out then the next line
// or 0x80, 0x80 shrink and close (callback with 0x1000, player's record flag cleared, box freed). Descriptor flag
// 0x400 skips the timed steps. The callback gets (descriptor, line, state) with 0x2000 (next line) / 0x4000 (shown)
// / 0x1000 (closed) set in the flags meanwhile. Always ends with text_box_place (screen position).
/* was func_1516AFE0 */
void text_box_update(u8 *box) {
    TextAD20 *t;
    u8 *pl;
    s32 skip;
    s32 w;
    s32 h;
    s32 unused;
    s32 flags;
    u16 pad;

    t = TB_T(box);
    pl = (u8 *) D_800DBFF0;
    skip = t->flags & 0x400;
    if (((u8 *) t)[0x2B] != 0 && D_800C35EA != 1) {
        ((u8 *) t)[8] = 0;
        node_destroy((struct102 *) box);
        return;
    }
    TB_F32(box, 0x40) = TB_F32(box, 0x5C);
    TB_F32(box, 0x44) = TB_F32(box, 0x60);
    switch (box[0x15]) {
    case 1:
        TB_S16(box, 0x16) = 0;
        TB_S16(box, 0x18) = 0;
        TB_F32(box, 0x2C) = skip ? 1.0f : D_800A7138;
        if (TB_T(box)->flags & 2) {
            box[0x1D] = 0;
            box[0x1C] = 0;
            box[0x1B] = 0;
            box[0x1E] = 2;
            TB_S16(box, 0x16) = 4;
            TB_S16(box, 0x18) = 10;
            box[0x15] = 8;
            TB_F32(box, 0x28) = 1.0f;
            text_box_place(box);
            box[0xE] = 1;
            TB_F32(box, 0x70) = TB_F32(box, 0x5C);
        } else {
            box[0x15] = 2;
        }
        TB_F32(box, 0x30) = 1.0f;
        TB_F32(box, 0x34) = 1.0f;
        box[0x1A] = 0;
        break;
    case 2:
        text_measure_string(*(u8 **) (box + 0x24), &w, &h, &unused);
        TB_F32(box, 0x30) = w >> 1;
        TB_F32(box, 0x34) = h >> 1;
        TB_F32(box, 0x28) = TB_F32(box, 0x28) + TB_F32(box, 0x2C) * D_800BE9A4;
        if (skip) {
            TB_S16(box, 0x18) = 0;
        }
        if (0.75f < TB_F32(box, 0x28) && TB_S16(box, 0x18) == 0) {
            TB_S16(box, 0x18) = 10;
        }
        if (TB_S16(box, 0x18) != 0) {
            TB_S16(box, 0x18) -= D_800BE9A0;
            if (TB_S16(box, 0x18) < 0) {
                TB_S16(box, 0x18) = 0;
            }
            box[0x1A] = (u32) ((10.0f - TB_S16(box, 0x18)) / 10.0f * 255.0f);
        }
        if (1.0f < TB_F32(box, 0x28)) {
            TB_F32(box, 0x28) = 1.0f;
            box[0x15] = 4;
            TB_S16(box, 0x16) = 180;
        }
        box[0xE] = 1;
        break;
    case 4:
        if (skip) {
            TB_S16(box, 0x16) = 0;
        }
        TB_S16(box, 0x16) -= D_800BE9A0 * 45;
        if (TB_S16(box, 0x16) < 0) {
            TB_S16(box, 0x16) = 0;
        }
        TB_S16(box, 0x18) -= D_800BE9A0;
        if (TB_S16(box, 0x18) < 0) {
            TB_S16(box, 0x18) = 0;
        }
        box[0x1A] = (u32) ((10.0f - TB_S16(box, 0x18)) / 10.0f * 255.0f);
        if (TB_S16(box, 0x16) == 0) {
            box[0x15] = 0x10;
        }
        break;
    case 8:
        TB_S16(box, 0x16) -= D_800BE9A0;
        if (TB_S16(box, 0x16) < 0) {
            TB_S16(box, 0x16) = 0;
        }
        box[0x1B + box[0x1E]] = (u32) ((4.0f - TB_S16(box, 0x16)) / 4.0f * 170.0f);
        if (TB_S16(box, 0x16) == 0) {
            box[0x1E]--;
            if (box[0x1E] < 101) {
                TB_S16(box, 0x16) = 4;
            } else {
                box[0x15] = 0x10;
                TB_S16(box, 0x18) = 10;
            }
        }
        break;
    case 0x40:
        TB_S16(box, 0x16) -= D_800BE9A0;
        if (TB_S16(box, 0x16) < 0) {
            TB_S16(box, 0x16) = 0;
        }
        if (skip) {
            TB_S16(box, 0x16) = 0;
        }
        box[0x1A] = (u32) (TB_S16(box, 0x16) / 10.0f * 255.0f);
        if (TB_S16(box, 0x16) == 0) {
            ((s8 *) box)[0x20]++;
            if (((s8 *) box)[0x20] < TB_T(box)->lines) {
                *(u8 **) (box + 0x24) = text_box_get_line((s32 *) TB_T(box), ((s8 *) box)[0x20], box[0xD]);
                TB_S16(box, 0x18) = 10;
                box[0x15] = 0x10;
                TB_T(box)->flags |= 0x2000;
                if (TB_T(box)->callback != NULL) {
                    TB_T(box)->callback((s32) TB_T(box), ((s8 *) box)[0x20] - 1, box[0x15]);
                }
                TB_T(box)->flags &= ~0x2000;
            } else {
                TB_S16(box, 0x18) = 5;
                box[0x15] = 0x80;
                TB_F32(box, 0x28) = 1.0f;
                TB_F32(box, 0x2C) = 0.25f;
            }
        }
        if (!skip) {
            break;
        }
        /* fallthrough: skipping goes on with the line fade-in */
    case 0x10:
        text_measure_string(*(u8 **) (box + 0x24), &w, &h, &unused);
        TB_F32(box, 0x30) = w >> 1;
        TB_F32(box, 0x34) = h >> 1;
        TB_S16(box, 0x18) -= D_800BE9A0;
        if (TB_S16(box, 0x18) < 0) {
            TB_S16(box, 0x18) = 0;
        }
        if (skip) {
            TB_S16(box, 0x18) = 0;
        }
        box[0x1A] = (u32) ((10.0f - TB_S16(box, 0x18)) / 10.0f * 255.0f);
        if (TB_S16(box, 0x18) == 0) {
            box[0x15] = 0x20;
            TB_S16(box, 0x16) = TB_T(box)->width;
            TB_T(box)->flags |= 0x4000;
        }
        if (!skip) {
            break;
        }
        /* fallthrough */
    case 0x20:
        skip = 0;
        if (TB_T(box)->flags & 0x4000) {
            if (TB_T(box)->callback != NULL) {
                TB_T(box)->callback((s32) TB_T(box), ((s8 *) box)[0x20], box[0x15]);
            }
            TB_T(box)->flags &= ~0x4000;
        }
        TB_S16(box, 0x16) -= D_800BE9A0;
        if (TB_S16(box, 0x16) < 0) {
            TB_S16(box, 0x16) = 0;
        }
        flags = TB_T(box)->flags;
        if ((flags & 0x10) && box[0x14] == 0) {
            if (flags & 0x20) {
                if (mp3_stream_get_state() != 0) {
                    goto request;
                }
                flags = TB_T(box)->flags;
            }
            if ((flags & 0x80) && TB_T(box)->lines == ((s8 *) box)[0x20] + 1) {
                pad = D_800BEB30[0];
                if (pad & 0x4000) {
                    box[0x20] = -1;
                    skip = 1;
                    D_800D1994 = 0;
                } else if (pad & 0x8000) {
                    skip = 1;
                }
            } else {
                pad = D_800BEB30[0];
                if (pad & 0x8000) {
                    skip = 1;
                } else if (!(flags & 0x40) && (pad & 0x4000)) {
                    box[0x20] = TB_T(box)->lines;
                    skip = 1;
                }
            }
        }
    request:
        flags = TB_T(box)->flags;
        if (flags & 0x100) {
            TB_T(box)->flags = flags & ~0x100;
            skip = 1;
            flags = TB_T(box)->flags;
        }
        if (!(flags & 0x200) && skip) {
            TB_S16(box, 0x16) = 10;
            box[0x15] = 0x40;
        }
        break;
    case 0x80:
        if (TB_T(box)->flags & 2) {
            TB_S16(box, 0x18) -= D_800BE9A0;
            if (TB_S16(box, 0x18) < 0) {
                TB_S16(box, 0x18) = 0;
            }
            box[0x1B] = box[0x1C] = box[0x1D] = (u32) (TB_S16(box, 0x18) / 5.0f * 85.0f);
        } else {
            TB_F32(box, 0x28) = TB_F32(box, 0x28) - TB_F32(box, 0x2C) * D_800BE9A4;
        }
        if (TB_F32(box, 0x28) < 0.0f || TB_S16(box, 0x18) == 0) {
            TB_F32(box, 0x28) = 0.0f;
            box[0x15] = 0;
            box[0x20] = 0;
            TB_T(box)->flags |= 0x1000;
            if (TB_T(box)->callback != NULL) {
                TB_T(box)->callback((s32) TB_T(box), ((s8 *) box)[0x20], box[0x15]);
            }
            TB_T(box)->flags &= ~0x1000;
            D_800CC8D3[TB_T(box)->player * 0x32C] = 0;
            *(s16 *) (pl + 0x6CC) = 0;
            ((u8 *) TB_T(box))[8] = 0;
            node_destroy((struct102 *) box); /* the box is freed; text_box_place below still runs on it, as on N64 */
        }
        break;
    }
    text_box_place(box);
}

/* P170 */
Gfx *sprite_load_texture(Gfx *gfx, u8 *header, s32 tmem, void *spr, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
Gfx *sprite_draw_at_screen(Gfx *gfx, void *spr, f32 x, f32 y);
Gfx *text_box_draw_text(Gfx *gfx, u8 *box, u8 r, u8 g, u8 b, u8 a);
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

/* sprite parameters for sprite_load_texture / sprite_draw_at_screen */
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

// text_box_draw: draws a text box (record of text_box_open; +0x28 scale, +0x38 / +0x3C size, +0x40 / +0x44 pointer
// tip, +0x58 pointer angle from text_box_place). First the shadow pass in black at a quarter alpha: the box sprite
// (D_8009090C, or D_8009091C with descriptor flag 2) 5 pixels right / up unless descriptor flag 4, then the pointer
// or, with flag 2, the two "thought" dots (D_8009093C; the first eases towards the tip in +0x70) - this pass also
// sets the box corner +0x48 / +0x4C. Then the colour pass in the descriptor's colour (+0x28..+0x2A into
// D_800D31C8..CA; black at alpha 0x55 with flag 4): pointer / dots (flag 8: the D_8009094C pointer), the box, and
// the text (text_box_draw_text). Alphas scale with the global fade D_800E100C (+1, / 256); the box's fade bytes are +0x1A
// (text), +0x1B (box), +0x1C / +0x1D (dots). Returns gfx unchanged when the box is hidden (+0xE == 0) or the fade is 0,
// and the original gfx (drops the box) when the frame display list fills up.
/* was func_1516BC2C */
Gfx *text_box_draw(Gfx *gfx, u8 *box, s16 arg2) {
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
        gfx = sprite_load_texture(gfx, D_8009091C, 0, &spr, 0, 0, 0, 2, 3);
    } else {
        gfx = sprite_load_texture(gfx, D_8009090C, 0, &spr, 0, 0, 0, 2, 3);
    }
    if (!plain) {
        gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x48) + 5.0f, TB_F(0x4C) + -5.0f);
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
        gfx = sprite_load_texture(gfx, D_8009093C, 0, &spr, 0, 0, 0, 2, 3);
        spr.alpha = (u32) ((f32) box[0x1C] * 64.0f / 255.0f);
        spr.alpha = (spr.alpha * fade) >> 8;
        if (1.57079637f < TB_F(0x58)) {
            TB_F(0x70) = TB_F(0x70) + (TB_F(0x40) + px - TB_F(0x70)) * 0.3f;
            gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x70), TB_F(0x44) - py);
        } else {
            TB_F(0x70) = TB_F(0x70) + (TB_F(0x40) - px - TB_F(0x70)) * 0.3f;
            gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x70), TB_F(0x44) - py);
        }
        spr.w /= 2;
        spr.h /= 2;
        spr.alpha = (u32) ((f32) box[0x1D] * 64.0f / 255.0f);
        spr.alpha = (spr.alpha * fade) >> 8;
        gfx = sprite_load_texture(gfx, D_8009093C, 0, &spr, 0, 0, 0, 2, 3);
        if (1.57079637f < TB_F(0x58)) {
            gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x40) - 2.5f, TB_F(0x44) + -2.5f);
        } else {
            gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x40) + 2.5f, TB_F(0x44) + -2.5f);
        }
    } else {
        gfx = sprite_load_texture(gfx, D_8009092C, 0, &spr, 0, 0, 0, 2, 3);
        if (!plain) {
            if (1.57079637f < TB_F(0x58)) {
                gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x40) + px - 2.5f, TB_F(0x44) - py + -2.5f);
            } else {
                gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x40) - px + 2.5f, TB_F(0x44) - py + -2.5f);
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
        gfx = sprite_load_texture(gfx, D_8009093C, 0, &spr, 0, 0, 0, 2, 3);
        spr.alpha = (box[0x1C] * fade) >> 8;
        gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x70), TB_F(0x44) - py);
        spr.w /= 2;
        spr.h /= 2;
        gfx = sprite_load_texture(gfx, D_8009093C, 0, &spr, 0, 0, 0, 2, 3);
        spr.alpha = (box[0x1D] * fade) >> 8;
        /* both sides draw the small dot at the tip */
        gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x40), TB_F(0x44));
    } else {
        if (TB_FLAGS & 8) {
            gfx = sprite_load_texture(gfx, D_8009094C, 0, &spr, 0, 0, 0, 2, 3);
        } else {
            gfx = sprite_load_texture(gfx, D_8009092C, 0, &spr, 0, 0, 0, 2, 3);
        }
        if (1.57079637f < TB_F(0x58)) {
            gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x40) + px, TB_F(0x44) - py);
        } else {
            gfx = sprite_draw_at_screen(gfx, &spr, TB_F(0x40) - px, TB_F(0x44) - py);
        }
    }

    /* colour pass: the box */
    spr.w = (s32) ((TB_F(0x38) + TB_F(0x38)) / (f32) *(u16 *) (D_8009090C + 6) * 2355.2f * TB_F(0x28));
    spr.h = (s32) (TB_F(0x3C) / (f32) *(u16 *) (D_8009090C + 8) * 4259.84f * TB_F(0x28));
    if (TB_FLAGS & 2) {
        spr.alpha = (box[0x1B] * fade) >> 8;
        gfx = sprite_load_texture(gfx, D_8009091C, 0, &spr, 0, 0, 0, 2, 3);
    } else {
        gfx = sprite_load_texture(gfx, D_8009090C, 0, &spr, 0, 0, 0, 2, 3);
    }
    gfx = sprite_draw_at_screen(gfx, &spr, (s32) TB_F(0x48), (s32) TB_F(0x4C));
    if (TB_DL_FULL(gfx)) {
        return start;
    }
    return text_box_draw_text(gfx, box, 0, 0, 0, (box[0x1A] * fade) >> 8);
}

/* was func_1516CDE8 */
u8 *text_box_get_line(s32 *arg0, s32 arg1, s16 arg2) {
    s32 i;
    u8 *p;

    switch (arg2) {
    case 0:
        p = D_800DD684[arg0[1]].str;
        break;
    case 1:
        p = D_800DD688[arg0[1]].str;
        break;
    case 2:
        p = (u8 *)arg0[1];
        break;
    }
    for (i = 0; i < arg1; i++) {
        while (*p != 0) {
            p++;
        }
        while (*p == 0) {
            p++;
        }
    }
    return p;
}

/* P170 */
Gfx *text_draw_string(Gfx *arg0, f32 arg1, f32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, s32 argA);
extern Gfx D_80085D30[]; /* text render state display list */

// text_box_draw_text: draws a text box's string (+0x24, lines split at '\n', leading newlines skipped) from the
// box's corner (+0x50 / +0x54 minus +0x30 / +0x34). Each line is measured (text_measure_string: width, height, advance)
// and printed by text_draw_string at 4096 x 4096 scale with its length: descriptor flag 0x20000 centres it on +0x30,
// flag 0x40000 prints it white one pixel right, flag 4 in colour r / g / b, otherwise black one pixel right.
// Returns the original gfx (drops the text) once the frame display list is full.
/* was func_1516CEA4 */
Gfx *text_box_draw_text(Gfx *gfx, u8 *box, u8 r, u8 g, u8 b, u8 a) {
    Gfx *start = gfx;
    u8 line[84];
    s32 width;
    s32 height;
    s32 advance;
    s32 i = 0;
    s32 n = 0;
    s32 first;
    s32 flags;
    u8 c;
    f32 x;
    f32 y;
    f32 dx;

    x = *(f32 *) (box + 0x50) - *(f32 *) (box + 0x30);
    y = *(f32 *) (box + 0x54) - *(f32 *) (box + 0x34);
    gSPDisplayList(gfx++, D_80085D30);
    first = 1;
    if ((*(u8 **) (box + 0x24))[0] == '\n') {
        do {
            i++;
        } while ((*(u8 **) (box + 0x24))[i] == '\n');
    }
    do {
        if (gfx - D_800BEDE8[D_800BE9C0] > D_800BEFC4) {
            return start;
        }
        c = (*(u8 **) (box + 0x24))[i];
        line[n] = c;
        if (c == '\n') {
            line[n] = 0;
            c = 0;
        }
        if (c != 0) {
            n++;
        } else {
            text_measure_string(line, &width, &height, &advance);
            if (!first) {
                y += (f32) height;
            } else {
                first = 0;
            }
            flags = **(s32 **) (box + 0x10);
            if (flags & 0x20000) {
                dx = *(f32 *) (box + 0x30) - (f32) (width >> 1) - 1.0f;
            } else {
                dx = 0.0f;
            }
            if (flags & 0x40000) {
                gfx = text_draw_string(gfx, x + dx + 1.0f, y, line, 0xFF, 0xFF, 0xFF, a, 4096.0f, 4096.0f, n);
            } else if (!(flags & 4)) {
                gfx = text_draw_string(gfx, x + dx + 1.0f, y, line, 0, 0, 0, a, 4096.0f, 4096.0f, n);
            } else {
                gfx = text_draw_string(gfx, x + dx, y, line, r, g, b, a, 4096.0f, 4096.0f, n);
            }
            n = 0;
            y += (f32) advance;
        }
    } while ((*(u8 **) (box + 0x24))[i++] != 0);
    return gfx;
}

void camera_world_to_screen(s32 arg0, f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz);
void text_box_clamp_to_screen(u8 *, f32 *, f32 *, s32);
extern u8 D_8009090C[]; /* box sprite header: u16 width +6, height +8 */
extern u8 D_8009092C[]; /* pointer sprite header: u16 width +6, height +8 */
extern u8 D_800CC730[]; /* per-player records (0x32C bytes): f32 heading at +0 */

// text_box_place: screen position of a text box (+0x5C / +0x60, copied to +0x40 / +0x44) and the angle +0x58 of
// its pointer (towards the speaker). Descriptor flag 0x8000: position from the descriptor's percentages (+0x18 /
// +0x1C words point at f32 x / y in %, +0x20 at the pointer angle in %, 55..125 degrees) scaled to the viewport
// (D_800BE628 +4 / +8), kept on screen by text_box_clamp_to_screen when flag 0x10000 is set. Otherwise the speaker's world
// point (descriptor +0xC..+0x14) projected once (camera_world_to_screen) and the angle from the player's heading relative to
// the camera (D_800DBFF0 +0x37C), always kept on screen. +0x50 / +0x54: the pointer's corner.
/* was func_1516D1C8 */
void text_box_place(u8 *box) {
    u8 *t;
    u8 *vp;
    f32 a;
    f32 sx;
    f32 sy;
    f32 sz;
    s32 ox;
    s32 oy;

    t = *(u8 **) (box + 0x10);
    if (*(s32 *) t & 0x8000) {
        vp = (u8 *) D_800BE628;
        *(f32 *) (box + 0x5C) = *(f32 *) (vp + 4) * ((*(f32 **) (t + 0x18))[0] * 0.01f);
        vp = (u8 *) D_800BE628;
        *(f32 *) (box + 0x60) = *(f32 *) (vp + 8) * (1.0f - (*(f32 **) (t + 0x1C))[0] * 0.01f);
        a = (*(f32 **) (t + 0x20))[0] * 0.01f;
        if (a < 0.0f) {
            a = 0.0f;
        } else if (1.0f < a) {
            a = 1.0f;
        }
        *(f32 *) (box + 0x58) = (70.0f * a + 55.0f) * 0.0174532924f;
        if (*(s32 *) t & 0x10000) {
            text_box_clamp_to_screen(box, (f32 *) (box + 0x5C), (f32 *) (box + 0x60), (s32) (box + 0x58));
        }
    } else {
        camera_world_to_screen(0, *(f32 *) (t + 0xC), *(f32 *) (t + 0x10), *(f32 *) (t + 0x14), &sx, &sy, &sz);
        if (box[0x1F] == 0) {
            *(f32 *) (box + 0x64) = sx;
            *(f32 *) (box + 0x68) = sy;
            box[0x1F] = 1;
            *(f32 *) (box + 0x6C) =
                *(f32 *) (D_800CC730 + t[9] * 0x32C) - *(f32 *) ((u8 *) D_800DBFF0 + 0x37C) - 180.0f;
        }
        a = *(f32 *) (box + 0x6C);
        *(f32 *) (box + 0x5C) = *(f32 *) (box + 0x64);
        *(f32 *) (box + 0x60) = *(f32 *) (box + 0x68);
        if (a < 0.0f) {
            a += 360.0f;
        }
        if (180.0f < a) {
            a -= 360.0f;
        }
        if (90.0f < a) {
            a = 180.0f - a;
        } else if ((f64) a < -90.0) {
            a = -180.0f - a;
        }
        *(f32 *) (box + 0x58) = (70.0f * (a / -180.0f + 0.5f) + 55.0f) * 0.0174532924f;
        text_box_clamp_to_screen(box, (f32 *) (box + 0x5C), (f32 *) (box + 0x60), (s32) (box + 0x58));
    }
    *(f32 *) (box + 0x40) = *(f32 *) (box + 0x5C);
    *(f32 *) (box + 0x44) = *(f32 *) (box + 0x60);
    ox = *(f32 *) (box + 0x38) / (f32) *(u16 *) (D_8009090C + 6) * (f32) *(u16 *) (D_8009092C + 6) * 0.25f;
    oy = *(f32 *) (box + 0x3C) / (f32) *(u16 *) (D_8009090C + 8) * (f32) *(u16 *) (D_8009092C + 8) * 0.5f;
    *(f32 *) (box + 0x50) =
        (s32) (cosf(*(f32 *) (box + 0x58) + 3.14159274f) * (*(f32 *) (box + 0x38) * 0.5f) * 1.15f
               + *(f32 *) (box + 0x5C) - (f32) ox);
    *(f32 *) (box + 0x54) =
        sinf(*(f32 *) (box + 0x58) + 3.14159274f) * (*(f32 *) (box + 0x3C) * 0.5f) * 1.04f + *(f32 *) (box + 0x60)
        - (f32) oy;
}

extern u16 D_80090912;
extern u16 D_80090932;

/* was func_1516D63C */
void text_box_clamp_to_screen(u8 *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f8;
    f32 var_f4;
    f32 var_f8;

    var_f8 = (f32) D_80090912;
    if ((s32) D_80090912 < 0) {
        var_f8 += 4294967296.0f;
    }
    var_f4 = (f32) D_80090932;
    if ((s32) D_80090932 < 0) {
        var_f4 += 4294967296.0f;
    }
    sp1C = ((*(f32 *)((u8 *)arg0 + 0x38)) / var_f8) * var_f4 * 0.25f * (*(f32 *)((u8 *)arg0 + 0x28));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x38)) * 0.5f;
    temp_f18 = (*(f32 *)((u8 *)arg0 + 0x3C));
    temp_f14 = *arg2;
    temp_f8 = cosf((*(f32 *)((u8 *)arg0 + 0x58)) + 3.1415927f) * temp_f2;
    sp28 = temp_f14;
    sp2C = temp_f14 - temp_f18;
    temp_f12 = ((temp_f8 * 1.15f * (*(f32 *)((u8 *)arg0 + 0x28))) + *arg1) - sp1C;
    sp24 = temp_f12 - temp_f2;
    sp20 = temp_f2 + temp_f12;
    if (arg0 != NULL) {
        temp_f0 = (*(f32 *)((u8 *)D_800BE628 + 0x24));
        if (sp2C < temp_f0) {
            *arg2 = temp_f0 + temp_f18;
        } else {
            temp_f0_2 = (*(f32 *)((u8 *)D_800BE628 + 0x28));
            if (temp_f0_2 < sp28) {
                *arg2 = temp_f0_2;
            }
        }
        temp_f0_3 = (*(f32 *)((u8 *)D_800BE628 + 0x2C));
        if (sp24 < temp_f0_3) {
            *arg1 -= sp24 - temp_f0_3;
        } else {
            temp_f0_4 = (*(f32 *)((u8 *)D_800BE628 + 0x30));
            if (temp_f0_4 < sp20) {
                *arg1 += temp_f0_4 - sp20;
            }
        }
        *arg1 = (f32) (s32) *arg1;
        *arg2 = (f32) (s32) *arg2;
    }
}
/* was func_1516D850 */
void text_box_close_now(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        (*(u8 **)(arg0 + 0x10))[8] = 0;
        node_destroy((struct102 *)arg0);
        arg0[0x15] = 0;
    }
}

/* was func_1516D898 */
void text_box_request_finish(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x100;
        **(s32 **)(arg0 + 0x10) &= ~0x400;
        arg0[0x20] = (*(u8 **)(arg0 + 0x10))[8];
    }
}

/* was func_1516D8E8 */
u8 *text_box_request_next(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x100;
        **(s32 **)(arg0 + 0x10) &= ~0x400;
        return arg0;
    }
    return NULL;
}

/* was func_1516D934 */
u8 *text_box_request_skip(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x500;
        return arg0;
    }
    return NULL;
}
