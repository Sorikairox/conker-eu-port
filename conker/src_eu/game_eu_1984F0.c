#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1516ACE0(u8 *arg0) {
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

#ifdef NON_MATCHING
/* P155 */
u8 *func_1516CDE8(s32 *arg0, s32 arg1, s16 arg2);
void func_15042BC4(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
extern f32 D_800A70B0; /* text box width scale */
extern f32 D_800A70B4; /* text box height scale */
extern u8 D_800CC8D3[]; /* per-player records, 0x32C bytes each */
typedef struct {
    s32 flags;  /* low 4 bits: box style; 2: large font; 0x7000 cleared on open */
    s32 str;    /* string table index, or the text itself for a caller-owned descriptor */
    u8 lines;   /* line count (counted by func_1516ACE0 for a caller-owned descriptor) */
    u8 player;
    s8 bA;
    u8 padB[0x1B];
    u16 width;  /* +0x26 */
    u8 pad28[4];
    void (*callback)(s32, s32, s32); /* +0x2C */
} TextAD20;
// text_box_open: opens a text box (func_15167A68 kind 0x51, 0x74 bytes) for descriptor `text`, or, without it, for
// string id `id` (< 0x100: table D_800DD684, else D_800DD688[id - 0x100]); +0xD = source 0 / 1 / 2 (2 = caller
// descriptor, whose lines are then counted). Stores player / arg2 / callback in the descriptor, measures every line
// (func_15042BC4) for the box size +0x38 / +0x3C (plus half / one line height of 18, 25 for the large font, scaled by
// D_800A70B0 / D_800A70B4), points +0x24 at the first line, clears the descriptor's 0x7000 bits and flags the
// player's record (+0xD3 of the 0x32C-byte entry). Returns the box record or NULL.
s32 func_1516AD20(s32 id, s32 player, s32 arg2, void (*callback)(s32, s32, s32), s32 *text, s32 arg5) {
    u8 *box;
    TextAD20 *t;
    s32 i;
    s32 w;
    s32 h;
    s32 unused;
    f32 line;

    box = func_15167A68(0x51, 0, 0x74, 0, arg5, 2);
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
        t->lines = func_1516ACE0((u8 *)t->str);
    }
    for (i = 0; i < t->lines; i++) {
        func_15042BC4(func_1516CDE8((s32 *)t, i, box[0xD]), &w, &h, &unused);
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
    *(u8 **)(box + 0x24) = func_1516CDE8((s32 *)t, 0, box[0xD]);
    box[0x20] = 0;
    t->flags &= ~0x7000;
    D_800CC8D3[t->player * 0x32C] = 1;
    box[0xE] = 0;
    return (s32)box;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516AD20.s")
#endif

#ifdef NON_MATCHING
s32 func_151F2CDC(void);
void func_1516D1C8(u8 *box);
extern u16 D_800BEB30[]; /* buttons pressed this frame, per player (0x8000 A, 0x4000 B) */
extern f32 D_800A7138;   /* 1 / 3: open speed */

#define TB_T(box) (*(TextAD20 **)((box) + 0x10))
#define TB_S16(box, o) (*(s16 *)((box) + (o)))
#define TB_F32(box, o) (*(f32 *)((box) + (o)))

// text_box_update: per-frame update of a text box (D_8008B848 kind 0x51, record of func_1516AD20). Closes the box at
// once when the descriptor's +0x2B is set and D_800C35EA is not 1. +0x15 is the state: 1 open (style 2: the 3-dot
// "more" variant, starts at 8), 2 grow (+0x28 scale up by +0x2C per frame, line fades in after 0.75), 4 wait
// (45 per frame from 180), 8 the dots fade in one by one, 0x10 line fade-in, 0x20 shown (waits for A / B, the
// "no B" / "last line" / timed flags of the descriptor, or a +0x100 request), 0x40 line fade-out then the next line
// or 0x80, 0x80 shrink and close (callback with 0x1000, player's record flag cleared, box freed). Descriptor flag
// 0x400 skips the timed steps. The callback gets (descriptor, line, state) with 0x2000 (next line) / 0x4000 (shown)
// / 0x1000 (closed) set in the flags meanwhile. Always ends with func_1516D1C8 (screen position).
void func_1516AFE0(u8 *box) {
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
        func_1516972C((struct102 *) box);
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
            func_1516D1C8(box);
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
        func_15042BC4(*(u8 **) (box + 0x24), &w, &h, &unused);
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
                *(u8 **) (box + 0x24) = func_1516CDE8((s32 *) TB_T(box), ((s8 *) box)[0x20], box[0xD]);
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
        func_15042BC4(*(u8 **) (box + 0x24), &w, &h, &unused);
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
                if (func_151F2CDC() != 0) {
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
            func_1516972C((struct102 *) box); /* the box is freed; func_1516D1C8 below still runs on it, as on N64 */
        }
        break;
    }
    func_1516D1C8(box);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516AFE0.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516BC2C.s")

u8 *func_1516CDE8(s32 *arg0, s32 arg1, s16 arg2) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516CEA4.s")

#ifdef NON_MATCHING
void func_1501A764(s32 arg0, f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz);
void func_1516D63C(u8 *, f32 *, f32 *, s32);
extern u8 D_8009090C[]; /* box sprite header: u16 width +6, height +8 */
extern u8 D_8009092C[]; /* pointer sprite header: u16 width +6, height +8 */
extern u8 D_800CC730[]; /* per-player records (0x32C bytes): f32 heading at +0 */

// text_box_place: screen position of a text box (+0x5C / +0x60, copied to +0x40 / +0x44) and the angle +0x58 of
// its pointer (towards the speaker). Descriptor flag 0x8000: position from the descriptor's percentages (+0x18 /
// +0x1C words point at f32 x / y in %, +0x20 at the pointer angle in %, 55..125 degrees) scaled to the viewport
// (D_800BE628 +4 / +8), kept on screen by func_1516D63C when flag 0x10000 is set. Otherwise the speaker's world
// point (descriptor +0xC..+0x14) projected once (func_1501A764) and the angle from the player's heading relative to
// the camera (D_800DBFF0 +0x37C), always kept on screen. +0x50 / +0x54: the pointer's corner.
void func_1516D1C8(u8 *box) {
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
            func_1516D63C(box, (f32 *) (box + 0x5C), (f32 *) (box + 0x60), (s32) (box + 0x58));
        }
    } else {
        func_1501A764(0, *(f32 *) (t + 0xC), *(f32 *) (t + 0x10), *(f32 *) (t + 0x14), &sx, &sy, &sz);
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
        func_1516D63C(box, (f32 *) (box + 0x5C), (f32 *) (box + 0x60), (s32) (box + 0x58));
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516D1C8.s")
#endif

#ifdef NON_MATCHING
extern u16 D_80090912;
extern u16 D_80090932;

void func_1516D63C(u8 *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516D63C.s")
#endif
void func_1516D850(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        (*(u8 **)(arg0 + 0x10))[8] = 0;
        func_1516972C((struct102 *)arg0);
        arg0[0x15] = 0;
    }
}

void func_1516D898(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x100;
        **(s32 **)(arg0 + 0x10) &= ~0x400;
        arg0[0x20] = (*(u8 **)(arg0 + 0x10))[8];
    }
}

u8 *func_1516D8E8(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x100;
        **(s32 **)(arg0 + 0x10) &= ~0x400;
        return arg0;
    }
    return NULL;
}

u8 *func_1516D934(u8 *arg0) {
    if ((arg0 != NULL) && (arg0[0] == 0x51)) {
        **(s32 **)(arg0 + 0x10) |= 0x500;
        return arg0;
    }
    return NULL;
}
