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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516AFE0.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1984F0/func_1516D1C8.s")

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
